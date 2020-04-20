import psutil
import cloud.common.python.configloader as config
import cloud.common.python.messaging as messaging
import zmq
import time

ipcmapping = config.get_services_mapping()

class GetPcInfos(object):
    """
        Class to get computer informations like
        temperature, cpu load, etc...
    """
    def __init__(self):
        self.cpu_load = 0
        self.cpu_freq = 0
        self.virt_mem_tot = 0
        self.virt_mem_avail = 0
        self.disk_usage = 0


    def _print_infos(self):
        """
        Print the PC informations
        """

        print("cpu_load:", self.cpu_load)
        print("cpu_freq:", self.cpu_freq)
        print("virt_mem_tot:", self.virt_mem_tot)
        print("virt_mem_avail:", self.virt_mem_avail)
        print("disk_usage:", self.disk_usage)

    def _get_cpu(self):
        """
        Get the CPU usage between 2 interval
        """
        self.cpu_load = psutil.cpu_percent(interval=None, percpu=False)
        self.cpu_freq = psutil.cpu_freq(percpu=False).current

    def _get_ram(self):
        """
        Get the ram usage at **t** moment
        """
        self.virt_mem_tot, self.virt_mem_avail, *_ = psutil.virtual_memory()

    def _get_disk(self):
        """
        Get the disk usage. This data is usefull to know if
        the shared memory are causing problems.
        """
        self.disk_usage = psutil.disk_usage("/").percent

    def run(self):
        """
        Get all the informations and returns them
        """
        self._get_cpu()
        self._get_ram()
        self._get_disk()
        self._print_infos()
        return self.cpu_load ,self.cpu_freq ,self.virt_mem_tot ,self.virt_mem_avail ,self.disk_usage

def _publish_data(ipc_sockets, infos):
    """
    Publish the computer informations into shared memory via ZeroMQ publish-susbcribe IPC protocol
    """

    cpu_load, cpu_freq, virt_mem_tot, virt_mem_avail, disk_usage = infos.run()
    ipc_sockets['CpuLoad'].send_string(str(cpu_load))
    ipc_sockets['CpuFreq'].send_string(str(cpu_freq))
    ipc_sockets['VirtMemTot'].send_string(str(virt_mem_tot) + " Bytes")
    ipc_sockets['VirtMemAvail'].send_string(str(virt_mem_avail) + " Bytes")
    ipc_sockets['DiskUsage'].send_string(str(disk_usage))

def run():
    """
    Run the computer information class and call the publish function
    """
    try:
        ipc_sockets = {}
        infos = GetPcInfos()
        context = zmq.Context()

        print('starting metric', flush=True)
        for metric_value, metric_key in ipcmapping['metrics'].items():
            ipc_sockets[metric_value] = messaging.publish_ipcsocket(context, metric_key)

        while 1:
            _publish_data(ipc_sockets, infos)
            time.sleep(0.1)
    except Exception as e:
        print(e, flush=True)
