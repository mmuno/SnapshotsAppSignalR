"""
Contains useful function for python messaging
"""

import zmq
import logging

## logger of the package: utils.messaging
logger = logging.getLogger(__name__)

def publish_tcpsocket(context, port, addr='*'):
    logger.debug("create socket mode PUB")
    sock = context.socket(zmq.PUB)
    uri = 'tcp://%s:%d' % (addr, port)
    logger.debug("TCP bind on: %s...", uri)
    sock.bind(uri)
    return sock

def subscribe_tcpsocket(context, port, addr='127.0.0.1', conflate=False):
    logger.debug("create socket mode SUB")
    sock = context.socket(zmq.SUB)
    if conflate:
        sock.setsockopt(zmq.CONFLATE, 1)

    uri = 'tcp://%s:%d' % (addr, port)
    logger.debug("connection to: %s...", uri)
    sock.connect(uri)
    sock.setsockopt(zmq.SUBSCRIBE, b"")
    logger.debug("connection: success")
    return sock

def publish_ipcsocket(context, addr):
    sock = context.socket(zmq.PUB)
    sock.bind('ipc:///%s' % (addr))
    return sock

def subscribe_ipcsocket(context, addr, conflate=False):
    sock = context.socket(zmq.SUB)
    if conflate:
        sock.setsockopt(zmq.CONFLATE, 1)
    sock.connect('ipc:///%s' % addr)
    sock.setsockopt(zmq.SUBSCRIBE, b"")
    return sock
