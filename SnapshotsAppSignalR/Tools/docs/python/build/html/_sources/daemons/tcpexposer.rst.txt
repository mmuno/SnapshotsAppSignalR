
tcpexposer
***************************

Kraft is designed to be efficient, which is why all inter-process communication is done locally using ZeroMQ IPCs.
Sometimes, some processes require the ability to subscribe to the result of one of these socket remotely wia TCP sockets and this is the role of the TCP Exposer.
This daemon takes a configuration file that associates an IPC socket with a TCP port and simply redistributes the result to that socket.

As 80% of Kraft is based on publish-subscribe socket, this approach consumes almost no resources.

------

.. automodule:: cloud.daemons.tcpexposer.main
        :members:
        :private-members:
        :special-members:
