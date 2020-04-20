"""
This bokeh tab allow signal vizualization
from the bearing
"""

from bokeh.models.widgets import Panel, MultiSelect, Paragraph, Div, Select
from bokeh.models import ColumnDataSource, Grid, LinearAxis, Plot, MultiLine
from bokeh.models.annotations import Title
from bokeh.layouts import column, grid
from bokeh.plotting import figure
from bokeh.io import curdoc
from utils.configloader import get_tcpservices_mapping
from utils.messaging import subscribe_tcpsocket
from functools import partial
from tornado import gen
from threading import Thread, Lock
import matplotlib.pyplot as plt
import numpy as np
import zmq
import queue

figures = []
context = zmq.Context()
signals = get_tcpservices_mapping()['sensors']

positions_to_display = [
    ('PositionV13', 'line'),
    ('PositionW13', 'line'),
    ('PositionV24', 'line')
#    ('PositionW24', 'circle'),
#    ('PositionV57', 'circle'),
#    ('PositionW57', 'circle'),
]


@gen.coroutine
def update(x, y, source, rollover):
    source.data['x'] = x
    source.data['y'] = y
#    source.stream({'x': x, 'y': y}, rollover=rollover)

def pull_update(ip, port, source, queue):
    socket = subscribe_tcpsocket(context, addr=ip, port=port, conflate=True)

    while True:
        data = socket.recv()

        y   = np.frombuffer(data, dtype=np.uint16)
        x   = np.linspace(0, 50, num=y.shape[0])
        
        update_partial = partial(update, x=x, y=y, source=source, rollover=y.shape[0])
        queue.put(update_partial)

def ml_panel(doc, queue):
    pollers = []

    for position, plot_type in positions_to_display:
        fig = figure(y_range=(0, 65535), tools='pan,wheel_zoom,box_zoom,reset', output_backend='webgl')
        fig.toolbar.logo = None

        title       = Title()
        title.text  = position
        fig.title   = title

        source = ColumnDataSource(dict(x=[], y=[]))
        
        if plot_type == 'circle':
            fig.circle(x='x', y='y', source=source)
        elif plot_type == 'line':
            fig.line(x='x', y='y', source=source)
        else:
            continue
        
        ## Setup the poller for this graph
        
        ip      = '172.16.30.71'
        port    = signals[position]['port']
        poller  = Thread(target=pull_update, args=[ip, port, source, queue])
        
        figures.append(fig)
        pollers.append(poller)

    
    layout  = grid(figures, ncols=3, sizing_mode='stretch_width')
    panel   = Panel(child=layout, title='Machine learning')

    return panel, pollers
