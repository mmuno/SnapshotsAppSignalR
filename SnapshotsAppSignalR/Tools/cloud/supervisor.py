"""
The supervisor is a function that start the daemons and manages their
health.
"""

import os
import sys
import time
import signal
import schedule
import importlib
import psutil
import multiprocessing
import cloud.common.python.configloader as config

# Define the processes to start
daemons_config  = config.get_daemons_config()

started_daemons = {}
daemons_states  = {}
restart_count   = {}

def redirect_out_daemon(daemon_name):
    """
    Redirect daemon name into file
    """
    pass

def start_python_daemon(daemon_name, module_path):
    """
    Start a python daemon and call his run() method
    """
    
    try:
        sys.stdout = open(f'cloud/logs/{daemon_name}.stdout', 'a')
        sys.stderr = open(f'cloud/logs/{daemon_name}.stderr', 'a')
        daemon = importlib.import_module(module_path)
        daemon.run()
    except Exception as e:
        print(e)
        pass

def start_native_daemon(daemon_name, directory, args):
    """
    Start a native daemons using directory and binary_name
    """
    
    try:
        rstdout = os.open(f'cloud/logs/{daemon_name}.stdout', os.O_WRONLY | os.O_TRUNC | os.O_CREAT)
        rstderr = os.open(f'cloud/logs/{daemon_name}.stderr', os.O_WRONLY | os.O_TRUNC | os.O_CREAT)
        
        os.dup2(rstdout, sys.stdout.fileno())
        os.dup2(rstderr, sys.stderr.fileno())

        os.close(rstdout)
        os.close(rstderr)

        os.chdir(directory)
        os.execv(args[0], args)
    except Exception as e:
        print(e)

def start_daemon(daemon_name):
    """
    Start the daemon using the daemon name and
    daemon params
    """
    
    daemon_params   = daemons_config[daemon_name]
    daemon_type     = daemon_params['type']
    proc            = None
    
    if daemon_type.lower() == 'python':
        proc = multiprocessing.Process(name=daemon_name,
                daemon=True,
                target=start_python_daemon,
                args=(daemon_name, daemon_params['module'],))

    elif daemon_type.lower() == 'native':
        proc = multiprocessing.Process(name=daemon_name,
                daemon=True,
                target=start_native_daemon,
                args=(daemon_name,
                    daemon_params['directory'],
                    daemon_params['args']))
    
    # Start the process
    proc.start()

    return proc

def start():
    """
    Starts the supervisor.
    """

    for daemon_name in daemons_config:
        if daemons_config[daemon_name]['start']:
            time.sleep(daemons_config[daemon_name]['waitfor'])
            started_daemons[daemon_name] = start_daemon(daemon_name)

    _supervise()

def _join_daemons(timeout=None):
    """
    Join all the daemons
    """
    
    for started_daemon in started_daemons.items():
        started_daemon[1].join(timeout)

def _kill_daemons():
    """
    Kill all the daemon and then join them.
    """
    
    for started_daemon in started_daemons.items():
        started_daemon[1].terminate()
        started_daemon[1].join()

def _kill_daemons_and_die():
    """
    Kill all the daemons, join them and then
    stop the program
    """
    _kill_daemons()
    sys.exit(0)

############ SUPERVISION TASKS ###########

signal.signal(signal.SIGINT, lambda signum,frame: _kill_daemons_and_die())
max_restarts    = 3

def _restart_dead_daemons():
        for daemon_name, daemon_process in started_daemons.items():
            for restart_id in range(3):
                if daemon_process.is_alive() is False:
                    started_daemons[daemon_name] = start_daemon(daemon_name)
                else:
                    break

            if restart_id+1 >= max_restarts:
                if daemons_config[daemon_name]['critical']:
                    _kill_daemons_and_die()

def _print_daemons_state():
        print('%10s | %10s | %10s' % ('Name', 'Pid', 'State'))
        print('-------------------------------------------')

        for i, (daemon_name, daemon_process) in enumerate(started_daemons.items()):
            alive   = 'alive' if daemon_process.is_alive() else 'dead'
            pid     = daemon_process.pid
            print('%10s | %10s | %10s' % (daemon_name, pid, alive))
        print('\n')

        sys.stdout.write('\033[%sA' % str(i+5))

def _delete_logs():

    logs_path = 'cloud/logs'

    for log_file in os.listdir(logs_path):
        to_remove = os.path.join(logs_path, log_file)
        os.remove(to_remove)

def _supervise():
    """
    Start the supervision of the started daemon
    """
    
#    schedule.every(5).seconds.do(_restart_dead_daemons)
    schedule.every(1).seconds.do(_print_daemons_state)
    schedule.every(5).minutes.do(_delete_logs)

    while 1:
        schedule.run_pending()
        time.sleep(1)
    
    
