"""
This bokeh tab allow signal vizualization
from the bearing
"""

from bokeh.models.widgets import RadioButtonGroup, CheckboxGroup, DataTable, DateFormatter, TableColumn, TextInput, Select
from bokeh.models.mappers import LinearColorMapper
from bokeh.palettes import Spectral6
from bokeh.layouts import grid
from bokeh.plotting import figure
from utils.configloader import get_tcpservices_mapping
import functools
import logging
import yaml
import numpy

from .plotter import Plotter

## logger of the package: panels.signal
logger = logging.getLogger(__name__)
tcpservices = get_tcpservices_mapping()['sensors']
selected_option = 0 

def radio_button_options_on_click(new):
    global selected_option
    global doptions

    selected_option = new
    logger.debug("new selected option: %d", selected_option)
    for grid in doptions.values():
        logger.debug("grid: '%s' visibility=False", grid)
        grid.visible = False
    logger.debug("grid: '%s' visibility=True", doptions[selected_option])
    doptions[selected_option].visible = True

def on_click_checkbox(active):
    global lsignals
    global plotters

    try:
        logger.debug("active signals idx: %s", active)
        lactives = [lsignals[idx] for idx in active]
        logger.debug("active signals names: %s", lactives)

        for plotter in plotters:
            if plotter.name in lactives:
                logger.debug("plotter=%s activated", plotter.name)
                plotter.plot()
                plotter.data_line.visible = True
                plotter.fft_line.visible = True
                plotter.spectro_line.visible = True
            else:
                logger.debug("plotter=%s unactivated", plotter.name)
                plotter.unplot()
                plotter.data_line.visible = False
                plotter.fft_line.visible = False
                plotter.spectro_line.visible = False

    except Exception as e:
        logger.fatal("exception: %s", e)

def on_change_statistics_plotter(value, old, new, plotter=None):
    global selected_signal
    global grid_tb

    if plotter is None:
        return

    if (plotter.name == selected_signal):
        grid_tb.children[0][0].value = str(new["min"][0])
        grid_tb.children[1][0].value = str(new["max"][0])
        grid_tb.children[2][0].value = str(new["average"][0])
        grid_tb.children[3][0].value = str(new["median"][0])
        grid_tb.children[4][0].value = str(new["rms"][0])

def on_change_statistics_select_button(value, old, new):
    global selected_signal

    logger.debug("call statistics for: '%s'", new)
    selected_signal = new

def signal_panel(doc, queue):
    global selected_option
    global lsignals
    global doptions
    global plotters
    global selected_signal
    global grid_tb

    # load configuration
    logger.info("load configuration...")
    sconf = open('config/signal.yaml', 'r')
    config = yaml.safe_load(sconf)

    # load figure
    logger.info("load figure...")
    lines = list()
    figtemp = figure(y_range=(-400, 400), tools='pan,wheel_zoom,box_zoom,save,reset', output_backend='webgl', title="time domain",sizing_mode="stretch_both")
    figfreq = figure(y_range=(0, 400), tools='pan,wheel_zoom,box_zoom,save,reset', output_backend='webgl', title="frequency domain",sizing_mode="stretch_both")
    figspectro = figure(title="waterfall", sizing_mode="stretch_both")
    figtemp.toolbar.logo = None
    figfreq.toolbar.logo = None
    figspectro.toolbar.logo = None    

    # load options
    selected_option = 0
    grid_signals = grid()
    grid_statistics = grid()
    doptions = {0: grid_signals, 1: grid_statistics}
    radio_button_options = RadioButtonGroup(labels=["signals", "statistics"], active=selected_option, width=300)
    radio_button_options.on_click(radio_button_options_on_click)

    # load signals grid
    logger.info("load checkboxes...")
    lgroups = list(config["options"].values())
    lsignals = list()
    lcheckboxes = list()
    plotters = list()
    for group in lgroups: 
        for sname in group:
            lsignals.append(sname)
            ip = tcpservices[sname]["ip"]
            port = tcpservices[sname]["port"]
            scales = config["scales"][sname]
            color = config["colors"][sname]
            try:
                plotter = Plotter(sname, ip, port, scales, queue)
                plotter.data_line = figtemp.line(x='x', y='y', name=sname, source=plotter.source, line_color=color, visible=False, line_width=3, legend=sname)
                plotter.fft_line = figfreq.line(x='freq', y='amp', name=sname, source=plotter.fft, line_color=color, visible=False, line_width=3, legend=sname) 
                #low=numpy.min(Sxx), high=numpy.max(Sxx)
                mapper = LinearColorMapper(palette=Spectral6, low=0, high=0.4)
                plotter.spectro_line = figspectro.circle(x='time', y='freq', source=plotter.spectro, fill_color={'field': 'sxx', 'transform': mapper}, visible=False)
                plotter.statistics.on_change("data", functools.partial(on_change_statistics_plotter, plotter=plotter))
                plotter.start()
                logger.info("adding plotter: %s tcp://%s:%d", sname, ip, port)
                plotters.append(plotter)
            except Exception as e:
                logger.error("exception: %s", e)

    checkboxgroup = CheckboxGroup(labels=lsignals, width=250)
    checkboxgroup.on_click(on_click_checkbox)
    lcheckboxes.append(checkboxgroup)

    grid_signals = grid(lcheckboxes)   
    grid_signals.visible = True
    doptions[0] = grid_signals

    # load statitics grid
    logger.info("load statistics...")
    selected_signal = plotters[0].name
    statistics_select_button = Select(title="signals:", value=selected_signal, options=[plotter.name for plotter in plotters], width=250)
    statistics_select_button.on_change("value", on_change_statistics_select_button)
    tb_min = TextInput(value="", title="min", disabled=True, width=250)
    tb_max = TextInput(value="", title="max", disabled=True, width=250)
    tb_average = TextInput(value="", title="average", disabled=True, width=250)
    tb_median = TextInput(value="", title="median", disabled=True, width=250)
    tb_rms = TextInput(value="", title="rms", disabled=True, width=250)
    grid_tb = grid([tb_min, tb_max, tb_average, tb_median, tb_rms])
    grid_statistics = grid([statistics_select_button, grid_tb])
    grid_statistics.visible = True
    doptions[1] = grid_statistics

    # load layout
    logger.info("layout: OK")
    layout  = grid([[[grid_signals, grid_statistics], figtemp, figfreq]])
    return layout
