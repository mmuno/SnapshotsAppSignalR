"""
main.py
=========================
The TCP Exposer service.

Its used to expose IPC sockets.
to the world using TCP sockets.
"""

import cloud.common.python.configloader as config
import cloud.common.python.messaging as messaging
import signal
import zmq
import sys
import time
import threading

tcpmapping = config.get_tcpservices_mapping()
ipcmapping = config.get_services_mapping()

class ConfigExposer(threading.Thread):
    def __init__(self, context):

        super().__init__()
        self.running = 1
        self.context = context
        self.tcp_port = 6666
        self.rep = messaging.reply_tcpsocket(self.context, port=self.tcp_port)

    def run(self):
        try:
            data = str(tcpmapping)
            while self.running:
                self.rep.recv()
                self.rep.send_string(data)
        except Exception as e:
            print("ConfigExposer Thread fail:", e)

class TCPExposer(threading.Thread):
    """
    TCPExposer is a Thread subclass.
    Take an IPC path as input, subscribe to it using
    ZeroMQ socket and publish what is received from
    this socket to a TCP Socket bind to 'tcp_port'
    """

    def __init__(self, context, ipc_path, tcp_port):
        """
        Init method:

            1. Subscribe to IPC Socket
            2. Publish to TCP Socket

        parameters:
            context: A zmq context
            ipc_path: An absolute path to the ipc
            tcp_port: A port used to bind the tcp socket
        """

        super().__init__()
        self.running = 1
        self.context = context
        self.ipc_path = ipc_path
        self.tcp_port = tcp_port
        self.sub = messaging.subscribe_ipcsocket(self.context, ipc_path)
        self.pub = messaging.publish_tcpsocket(self.context, port=tcp_port)

    def run(self):
        """
        The run method pull the data from 'self.sub'
        using zmq.Socket.recv() and send it to 'self.pub'
        using zmq.Socket.send()
        
        parameters:
            None
        """
        while self.running:
            data = self.sub.recv()
            self.pub.send(data)


signal.signal(signal.SIGINT, lambda: _terminate_threads())
threads = []

def run():
    """
    Take the configuration files 'ipc_mapping.yaml'
    and 'tcp_mapping' contained at cloud/conf.
    Parse them and expose the channels requested
    in tcp_mapping.yaml.
    If you don't want to expose in tcp a specific IPC Socket, just
    comment it in 'tcp_mapping.yaml' config file.

    parameters:
        None
    """
    
    print('Starting TCPExposer', flush=True)
    context = zmq.Context()

    test = ConfigExposer(context=context)
    test.start()
    threads.append([test, tcpmapping.items(), "ConfigExposer"])
    for namespace, mapping in tcpmapping.items():
        for pub_name, pub_info in mapping.items():
            exposer = TCPExposer(
                            context=context,
                            ipc_path=ipcmapping[namespace][pub_name],
                            tcp_port=pub_info['port']
                        )

            exposer.start()
            threads.append([exposer, namespace, pub_name])
    time.sleep(5)
    _print_state()
    _join_threads()


def _join_threads():
    """
    Join all the TCPExpose threads.

    parameters:
    None
    """
    for thread, namespace, name in threads:
        thread.join()

def _terminate_threads():
    """
    Terminate the job of all the TCPExpose
    threads and join them.

    parameters:
    None
    """
    for thread, namespace, name in threads:
        thread.running = 0
        thread.join()

def _print_state():
    """
    Take all the TCPExpose threads that are
    started and print their state.

    parameters:
    None
    """
    for thread, namespace, name in threads:
        print(f'[{namespace}] {name}: {thread}', flush=True)

