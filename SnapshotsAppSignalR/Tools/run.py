"""
This script start the whole project.

Take the daemons.yaml file, parse it and start the daemons accordingly
"""

import sys
import argparse
import cloud.supervisor
import cloud.prepare

parser = argparse.ArgumentParser()
parser.add_argument('--clean', action='store_true')
parser.add_argument('--rebuild', action='store_true')

args = parser.parse_args()

if __name__ == '__main__':
    if args.clean:
        cloud.prepare.clean()
        sys.exit(0)

    if args.rebuild:
        cloud.prepare.clean()
    
    cloud.prepare.create_folders()
    cloud.prepare.build()
    cloud.supervisor.start()
