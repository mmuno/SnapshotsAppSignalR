"""
The orbit tab allow the vizualization of unbalance
"""

from bokeh.models.widgets import Panel, Select
from bokeh.models import ColumnDataSource
from bokeh.plotting import figure
from bokeh.layouts import gridplot, grid
from utils.messaging import subscribe_tcpsocket
from utils.configloader import get_tcpservices_mapping
import threading
import functools
import tornado
import numpy
import zmq
import logging
import yaml

logger = logging.getLogger(__name__)
context = zmq.Context()
sensors = get_tcpservices_mapping()['sensors']
source  = ColumnDataSource(data={'x': [], 'y': []})
x_lock = threading.Lock()
y_lock = threading.Lock()

@tornado.gen.coroutine
def update_orbit(x, y, rollover):
    source.stream({'x': x, 'y': y}, rollover=rollover)

## calculate engineering value for full scale.
# @param self pointer
# @param value full scale value
# @param dtype type of scale (default=uint16)
# @return engineering value
def calculate_eng(value, dtype=numpy.uint16):
    min_type = numpy.iinfo(dtype).min
    max_type = numpy.iinfo(dtype).max
    hi_scale = 400
    lo_scale = -400
    delta_scale = hi_scale - lo_scale
    delta_type = max_type - min_type
    return ((value - min_type) / delta_type) * delta_scale + lo_scale

def pull_orbit(queue):
    #subscribe to all positions 
    global positions
    global dsockets
    global x_socket
    global y_socket
    try:
        dsockets = dict([(s, subscribe_tcpsocket(context, addr=sensors[s]['ip'], port=sensors[s]['port'], conflate=True)) for s in positions])
        x_socket = dsockets[positions[0]]
        y_socket = dsockets[positions[1]]

        datas = list()
        buffers = list()

        while True:
            x_lock.acquire()
            x_data = x_socket.recv()
            x_lock.release()

            y_lock.acquire()
            y_data = y_socket.recv()
            y_lock.release()
            
            x_buffer = numpy.frombuffer(x_data, dtype=numpy.uint16)
            y_buffer = numpy.frombuffer(y_data, dtype=numpy.uint16)

            x = [calculate_eng(v) for v in x_buffer]
            y = [calculate_eng(v) for v in y_buffer]

            update_orbit_partial = functools.partial(update_orbit, x=x, y=y, rollover=x_buffer.shape[0])
            queue.put(update_orbit_partial)
    except Exception as e:
        logger.fatal('exception: %s', e)

def x_axis_on_change(value, old, new):
    global dsockets
    global x_socket
    logger.debug("X-Axis value: old='%s' new='%s'", old, new)
    x_lock.acquire()
    x_socket = dsockets[new]
    x_lock.release()

def y_axis_on_change(value, old, new):
    global dsockets
    global y_socket
    logger.debug("Y-Axis value: '%s'='%s'", old, new)
    y_lock.acquire()
    y_socket = dsockets[new]
    y_lock.release()    

def orbit_panel(doc, queue):
    global positions
    try:
        #load configuration
        logger.info("load configuration...")
        sconf = open('config/signal.yaml', 'r')
        config = yaml.safe_load(sconf)
        positions = config["options"]["positions"]

        #load figure
        fig                 = figure(y_range=(-400,400), x_range=(-400,400), tools='pan,wheel_zoom,box_zoom,save,reset', output_backend='webgl', toolbar_location='above')
        plot                = fig.circle(x='x', y='y', source=source)
        fig.toolbar.logo    = None

        x_axis_select = Select(title="X-Axis", value=positions[0], options=positions)
        y_axis_select = Select(title="Y-Axis", value=positions[1], options=positions)
        
        x_axis_select.on_change("value", x_axis_on_change)
        y_axis_select.on_change("value", y_axis_on_change)
        selects = grid([x_axis_select, y_axis_select])

        layout = grid([[selects, fig]])
        poller = threading.Thread(target=functools.partial(pull_orbit, queue=queue))
    except Exception as e:
        logger.fatal("exception: %s", e)
    return layout, [poller]
    
    
