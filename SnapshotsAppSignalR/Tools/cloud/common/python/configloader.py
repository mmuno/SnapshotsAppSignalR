"""
Project functions to manage the configuration
"""

import os
import yaml

DAEMONS_CONFIG_PATH         = os.path.abspath('cloud/conf/daemons.yaml')
SERVICES_MAPPING_PATH       = os.path.abspath('cloud/conf/ipc_mapping.yaml')
TCPSERVICES_MAPPING_PATH    = os.path.abspath('cloud/conf/tcp_mapping.yaml')

def get_daemons_config():
    """
    Returns the parsed config file for the daemons
    """
    
    try:
        stream = open(DAEMONS_CONFIG_PATH, 'r')
        config = yaml.safe_load(stream)
    except yaml.YAMLError as e:
        raise Exception('Could not parse daemons config file, check syntax')
    except FileNotFoundError as e:
        raise Exception('Could not open config file, check if %s exist' % DAEMONS_CONFIG_PATH)
    except Exception as e:
        raise Exception('Unknown error when parsing config file')

    return config


def get_services_mapping():
    """
    Returns the parsed config file for the services
    mapping
    """

    try:
        stream = open(SERVICES_MAPPING_PATH, 'r')
        config = yaml.safe_load(stream)
    except yaml.YAMLError as e:
        print(e)
        raise Exception('Could not parse services mapping file, check syntax')
    except FileNotFoundError as e:
        print(e)
        raise Exception('Could not open config file, check if %s exist' % SERVICES_MAPPING_PATH)
    except Exception as e:
        print(e)
        raise Exception('Unknown error when parsing config file')

    return config

def get_tcpservices_mapping():
    """
    Returns the parsed config file for the services
    mapping
    """

    try:
        stream = open(TCPSERVICES_MAPPING_PATH, 'r')
        config = yaml.safe_load(stream)
    except yaml.YAMLError as e:
        print(e)
        raise Exception('Could not parse TCP services mapping file, check syntax')
    except FileNotFoundError as e:
        print(e)
        raise Exception('Could not open config file, check if %s exist' % SERVICES_MAPPING_PATH)
    except Exception as e:
        print(e)
        raise Exception('Unknown error when parsing config file')

    return config

