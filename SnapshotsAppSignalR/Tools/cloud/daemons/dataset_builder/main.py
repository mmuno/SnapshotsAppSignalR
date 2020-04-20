"""
Small daemon to build a dataset
"""

import cloud.common.python.configloader as config
import cloud.common.python.messaging as messaging
import schedule
import numpy
import pandas
import zmq
import time
import avro.schema
from avro.datafile import DataFileReader, DataFileWriter
from avro.io import DatumReader, DatumWriter

services = config.get_tcpservices_mapping()
targets = ['PositionV13']
           #'PositionW13',
        #    'PositionV24', 
        #    'PositionW24',
        #    'PositionV57',
        #    'PositionW57',
        #    'Positionz1',
        #    'PositionZ12',
        #    'CurrentV1',
        #    'CurrentV3',
        #    'CurrentV2',
        #    'CurrentV4',
        #    'CurrentV5',
        #    'CurrentV7',
        #    'CurrentW1',
        #    'CurrentW3',
        #    'CurrentW2',
        #    'CurrentW4',
        #    'CurrentW5',
        #    'CurrentW7',
        #    'CurrentZ1',
        #    'CurrentZ2',
        #    'CurrentZ3',
        #    'CurrentZ4']

zctx = zmq.Context()
sockets_mapping = {}
df = pandas.DataFrame(columns=targets)
schema = avro.schema.parse(open("user.avsc", "rb").read())

def record():
    toto = {}
    for sock_name, sock in sockets_mapping.items():
        data = sock.recv()
        df[sock_name] = data
        buffer = numpy.frombuffer(data, dtype=numpy.uint16)
        
        writer = DataFileWriter(open("users.avro", "wb"), DatumWriter(), schema)
        writer.append({"name": sock_name, "data": buffer})
        writer.close()

        #print('==== new salve ====', flush=True)
        #print(sock_name, flush=True)
        #print(buffer, flush=True)

    ##df = pandas.DataFrame(toto, columns=targets)
    df.to_csv('dataset.csv', index=False, header=True)


def run():
    for target in targets:
        addr = "172.16.30.71"
        port = 41000
        sock = messaging.subscribe_tcpsocket(context=zctx, addr=addr, port=port, conflate=True)
        sockets_mapping[target] = sock

    schedule.every(1).seconds.do(record)

    while True:
        schedule.run_pending()
        time.sleep(0.1)
