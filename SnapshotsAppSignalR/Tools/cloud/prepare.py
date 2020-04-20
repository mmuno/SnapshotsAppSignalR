"""
Prepare the project for runtime
"""

from tqdm import tqdm
import subprocess
import shutil
import sys
import os
import cloud.common.python.configloader as config

daemons  = config.get_daemons_config()
logs_dir = 'cloud/logs'
logs     = 'cloud/logs/build.log'

def create_folders():
    if not os.path.isdir('cloud/logs'):
        os.mkdir('cloud/logs')

def clean():
    """
    Clean the compiled sources
    """
    
    logs_f = open(logs, 'w')
    for daemon_name, daemon_config in daemons.items():
        curwd   = os.getcwd()
        
        if daemon_config['type'] == 'native':
            os.chdir(daemon_config['directory'])

            proc    = subprocess.Popen(['make', 'fclean'],
                    stderr=subprocess.STDOUT,
                    stdout=logs_f)

            if proc.wait() != 0:
                print('error')

            os.chdir(curwd)
    
    for path, folders, files in os.walk('.'):
        if '__pycache__' in folders:
            shutil.rmtree(os.path.join(path, '__pycache__'))
    shutil.rmtree(logs_dir)

def build():
    """
    Compile everything and prepare the project
    for the supervisor
    """

    logs_f = open(logs, 'w')

    for daemon_name, daemon_config in daemons.items():
        curwd   = os.getcwd()
        
        if daemon_config['type'] == 'native':
            print(f'Compiling {daemon_name}')
            os.chdir(daemon_config['directory'])

            proc    = subprocess.Popen(['make', '-j8'],
                    stderr=subprocess.STDOUT,
                    stdout=logs_f)

            if proc.wait() != 0:
                print('error')

            os.chdir(curwd)
