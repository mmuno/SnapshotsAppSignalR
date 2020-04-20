"""
Contains useful function for python messaging
"""

import zmq


def publish_tcpsocket(context, port, addr='*'):
    sock = context.socket(zmq.PUB)
    sock.bind('tcp://%s:%d' % (addr, port))
    return sock

def subscribe_tcpsocket(context, port, addr='127.0.0.1', conflate=False):
    sock = context.socket(zmq.SUB)
    if conflate:
        sock.setsockopt(zmq.CONFLATE, 1)
    sock.connect('tcp://%s:%d' % (addr, port))
    sock.setsockopt(zmq.SUBSCRIBE, b"")
    return sock

def reply_tcpsocket(context, port, addr='*'):
    sock = context.socket(zmq.REP)
    sock.bind('tcp://%s:%d' % (addr, port))
    return sock

def request_tcpsocket(context, port, addr='127.0.0.1', conflate=False):
    sock = context.socket(zmq.REQ)
    if conflate:
        sock.setsockopt(zmq.CONFLATE, 1)
    sock.connect('tcp://%s:%d' % (addr, port))
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
