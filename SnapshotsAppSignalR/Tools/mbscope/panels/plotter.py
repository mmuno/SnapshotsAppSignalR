import bokeh.models
import tornado
import utils.messaging
import numpy
import threading
import logging
import functools
import zmq
import time
import queue
import statistics
import math
from scipy import signal
import pandas

import matplotlib.pyplot as plt

logger = logging.getLogger(__name__)
context = zmq.Context()

## Signa class description
# used to manage multi signals acquisition
# inherits: threading.Thread
class Plotter(threading.Thread):
    ## constructor.
    # @param self pointer
    # @param name name of the signal
    # @param ipaddr ip address of the TCP exposer channel for this signal
    # @param port port number of the TCP exposer channel for this signal
    # @param scales scales values for the signal
    # @param queue queue instance to update view
    def __init__(self, name, ipaddr, port, scales, queue):
        threading.Thread.__init__(self)
        self.name = name
        self.queue = queue
        self.scales = scales
        self.ipaddr = ipaddr
        self.port = port
        self.stopevent = threading.Event()
        self.socket = None
        self.data_line = None
        self.fft_line = None
        self.spectro_line = None
        self.updating = False
        self.time_series = list()
        self.source = bokeh.models.ColumnDataSource(data={'x':[], 'y': []})
        self.statistics = bokeh.models.ColumnDataSource(data={'min':[], 'max': [], 'average': [], 'median': [], "rms": []})
        self.fft = bokeh.models.ColumnDataSource(data={'freq':[], "amp":[]})
        self.spectro = bokeh.models.ColumnDataSource(data={'time':[], "freq":[], "sxx": []})        

    ## start to plot.
    # @param self pointer
    def plot(self):
        self.updating = True

    ## stop to plot.
    # @param self pointer
    def unplot(self):
        self.updating = False

    ## stop the thread.
    # set event to unlock the thread.
    # @param self pointer
    def stop(self):
        logger.info("[%s] stopping thread...", self.name)
        self.stopevent.set()         

    @tornado.gen.coroutine
    ## update source stream.
    # @param self pointer
    # @param x Axis-X Data
    # @param y Axis-Y Data
    # @param rollover 
    def update(self, x, y, rollover):
        logger.debug("[%s] updating stream...", self.name)
        try:
            
            """
            df = self.calculate_spectro(y)
            logger.info("df: %s", df)
            if (df is not None):
                self.spectro.stream(dict(sxx=df['sxx'],freq=df['f'],time=df['t']), rollover=None)
            """
            
            self.statistics.stream({'min': [min(y)], 'max': [max(y)], "average": [statistics.mean(y)], "median": [statistics.median(y)], "rms": [self.calculate_rms(y)]}, rollover=1)
            
            (amp, freq) = self.calculate_fft(y)
            self.fft.stream({'freq': freq, 'amp': amp}, rollover=len(freq))
            
            self.source.stream({'x': x, 'y': y}, rollover=rollover)
        except Exception as e:
            logger.fatal("exception: %s", e)

    def calculate_spectro(self, data, fs=14000):
        try:
            if (len(self.time_series) < 1400):
                logger.info("add data: len=%d", len(data))
                self.time_series.extend(data)
                logger.info("time series size: %d", len(self.time_series))
                return None
            else:
                
                x = numpy.asarray(self.time_series)
                f, t, Sxx = signal.spectrogram(x, fs)

                quadmesh = plt.pcolormesh(t, numpy.fft.fftshift(f), numpy.fft.fftshift(Sxx, axes=0))
                logger.info(quadmesh[0][0])

                return None
                """
                df = pandas.DataFrame(columns=["f", "t", "sxx"])
            
                i=0
                for freq in range(f.shape[0]):
                    for time in range(t.shape[0]):
                        df.loc[i] = [f[freq], t[time], Sxx[freq][time]]
                        i = i+1

                self.time_series = list()
                
                return df
                """
        except Exception as e:    
                logger.fatal("exception: %s", e)
                return None

    def calculate_fft(self, signal, timestep=1.0/14000):
        n = len(signal)
        fft = numpy.fft.fft(signal)
        abs_fft = [2*numpy.absolute(v)/n for v in fft]
        freq = numpy.fft.fftfreq(n, d=timestep)
        return (abs_fft[:int(n/2)], freq[:int(n/2)])

    def calculate_rms(self, arr): 
        n = len(arr)
        square = 0
        mean = 0.0
        root = 0.0
        
        #Calculate square 
        for i in range(0,n): 
            square += (arr[i]**2) 
        
        #Calculate Mean    
        mean = (square / (float)(n)) 
        
        #Calculate Root 
        root = math.sqrt(mean) 
        
        return root 

    ## calculate engineering value for full scale.
    # @param self pointer
    # @param value full scale value
    # @param dtype type of scale (default=uint16)
    # @return engineering value
    def calculate_eng(self, value, dtype=numpy.uint16):
        min_type = numpy.iinfo(dtype).min
        max_type = numpy.iinfo(dtype).max
        hi_scale = self.scales[1]
        lo_scale = self.scales[0]
        delta_scale = hi_scale - lo_scale
        delta_type = max_type - min_type
        return ((value - min_type) / delta_type) * delta_scale + lo_scale

    ## run function.
    # called by the start method.
    # loop of sending message with a period.
    # @param self pointer
    def run(self):
        logger.info("[%s] starts!", self.name)

        if self.socket is None:
            self.socket = utils.messaging.subscribe_tcpsocket(context, port=self.port, addr=self.ipaddr)

        try:
            while not self.stopevent.isSet():  
                logger.debug("[%s] waiting data...", self.name)
                data = self.socket.recv()
                logger.debug("[%s] data received", self.name)
                buffer = numpy.frombuffer(data, dtype=numpy.uint16)
                y = [self.calculate_eng(v) for v in buffer]
                x = numpy.linspace(0, 0.1, num=len(y))

                if self.updating:
                    logger.debug("[%s] streaming...", self.name)
                    signal_update_partial = functools.partial(self.update, x=x, y=y, rollover=buffer.shape[0])
                    self.queue.put(signal_update_partial)
                else:
                    logger.debug("[%s] not streaming...", self.name)
                    time.sleep(0.5)

        except Exception as e:
            logger.fatal("[%s] throw exception: \n%s", self.name, e)
        
        logger.info("[%s] closing socket...", self.name)
        self.socket.close()
        logger.info("[%s] socket closed!", self.name)
        logger.info("[%s] stopped succesfully!", self.name)