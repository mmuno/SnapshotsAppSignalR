"""
Start the bokeh server, create all the plots
"""


from bokeh.io import curdoc
from bokeh.embed import components
from bokeh.models.widgets.markups import Div
from bokeh.models.widgets import Tabs, Panel
from bokeh.server.server import Server
from bokeh.layouts import grid
from bokeh.themes import Theme
from panels.signal import signal_panel
from panels.orbit import orbit_panel
from panels.ml import ml_panel
from threading import Thread
import queue
import yaml
import logging.config
import logging

# logging config
logging.config.dictConfig(yaml.safe_load(open('config/logging.conf', 'r')))
logger = logging.getLogger("signal.main")

def push_update(queue):
    while True:
        update = queue.get(block=True, timeout=None)
        doc.add_next_tick_callback(update)

try:
    doc             = curdoc()
    update_queue    = queue.Queue()

    orbit, orbit_pollers = orbit_panel(doc, update_queue)
    signal = signal_panel(doc, update_queue)
    #signal, signal_pollers = signal_panel(doc, update_queue)
    #ml, ml_pollers = ml_panel(doc, update_queue)
    #pollers = [*orbit_pollers, *signal_pollers, *ml_pollers]
    pollers = [*orbit_pollers]

    #tabs        = Tabs(tabs=[signal, orbit, ml])
    #tabs = Tabs(tabs=[orbit])
    layout      = grid([[signal]])

    doc.title = "Signal"
    doc.theme = Theme(filename='config/theme.yaml')
    doc.add_root(layout)

    #for poller in pollers:
    #    poller.daemon = True
    #    poller.start()

    update_thread = Thread(target=push_update, args=[update_queue])
    update_thread.daemon = True
    update_thread.start()
except Exception as e:
    logger.fatal("main exception: %s", e)
