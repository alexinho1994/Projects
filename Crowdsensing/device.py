"""
This module represents a device.

Computer Systems Architecture Course
Assignment 1
March 2016
"""

from threading import Event, Thread
from barrier import *


class Workpool:
    def __init__(self, scripts):
    	self.scripts = scripts
    	self.nrThreads = 8
    	self.done = 0
    	self.lock = Lock()

    def getWork(self):
    	script = None
    	self.lock.acquire()
    	if self.done < len(self.scripts):
    		self.done = self.done + 1
    		script = self.scripts[self.done-1]
    	self.lock.release()
    	return script


class ScriptThread(Thread):
    def __init__(self, i, device, neighbours, wp):
    	Thread.__init__(self, name="Script Thread %d" % i)
    	self.device = device
    	self.script = None
    	self.neighbours = neighbours
    	self.wp = wp

    def run(self):
    	while True:
    		self.script = self.wp.getWork()
    		if self.script == None:
    			break
    		self.device.locationLock[self.script[1]].acquire()
    		script_data = []
    		# collect data from current neighbours
    		for device in self.neighbours:
    			device.lock.acquire()
    			data = device.get_data(self.script[1])
    			device.lock.release()
    			if data is not None:
    				script_data.append(data)

    		if script_data != []:
                	# run script on data
    			result = self.script[0].run(script_data)

    			self.device.lock.acquire()
                	# update data of neighbours, hope no one is updating at the same time
    			for device in self.neighbours:
    				device.set_data(self.script[1], result)
                	# update our data, hope no one is updating at the same time
    			device.set_data(self.script[1], result)
    			self.device.lock.release()
    		self.device.locationLock[self.script[1]].release()


class Device(object):
    """
    Class that represents a device.
    """

    def __init__(self, device_id, sensor_data, supervisor):
        """
        Constructor.

        @type device_id: Integer
        @param device_id: the unique id of this node; between 0 and N-1

        @type sensor_data: List of (Integer, Float)
        @param sensor_data: a list containing (location, data) as measured by this device

        @type supervisor: Supervisor
        @param supervisor: the testing infrastructure's control and validation component
        """
        self.device_id = device_id
        self.sensor_data = sensor_data
        self.supervisor = supervisor
        self.script_received = Event()
        self.scripts = []
        self.barr = None
        self.lock = None
        if device_id == 0:
        	self.locationLock = [Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock(), Lock()]
        else:
        	self.locationLock = []
        self.timepoint_done = Event()
        self.thread = DeviceThread(self)
        self.thread.start()

    def __str__(self):
        """
        Pretty prints this device.

        @rtype: String
        @return: a string containing the id of this device
        """
        return "Device %d" % self.device_id

    def setup_devices(self, devices):
        """
        Setup the devices before simulation begins.

        @type devices: List of Device
        @param devices: list containing all devices
        """

        dev = None
        for device in devices:
        	if device.device_id == 0:
        		dev = device
        		device.lock = Lock()
        		device.barr = ReusableBarrierCond(len(devices))
        for device in devices:
        	device.barr = dev.barr
        	device.lock = dev.lock
        	device.locationLock = dev.locationLock
        # we don't need no stinkin' setup

    def assign_script(self, script, location):
        """
        Provide a script for the device to execute.

        @type script: Script
        @param script: the script to execute from now on at each timepoint; None if the
            current timepoint has ended

        @type location: Integer
        @param location: the location for which the script is interested in
        """
        if script is not None:
            self.scripts.append((script, location))
            self.script_received.set()
            self.timepoint_done.set()
        else:
            self.timepoint_done.set()

    def get_data(self, location):
        """
        Returns the pollution value this device has for the given location.

        @type location: Integer
        @param location: a location for which obtain the data

        @rtype: Float
        @return: the pollution value
        """
        return self.sensor_data[location] if location in self.sensor_data else None

    def set_data(self, location, data):
        """
        Sets the pollution value stored by this device for the given location.

        @type location: Integer
        @param location: a location for which to set the data

        @type data: Float
        @param data: the pollution value
        """
        if location in self.sensor_data:
            self.sensor_data[location] = data

    def shutdown(self):
        """
        Instructs the device to shutdown (terminate all threads). This method
        is invoked by the tester. This method must block until all the threads
        started by this device terminate.
        """
        self.thread.join()
        del(self.thread)


class DeviceThread(Thread):
    """
    Class that implements the device's worker thread.
    """

    def __init__(self, device):
        """
        Constructor.

        @type device: Device
        @param device: the device which owns this thread
        """
        Thread.__init__(self, name="Device Thread %d" % device.device_id)
        self.device = device

    def run(self):
        # hope there is only one timepoint, as multiple iterations of the loop are not supported
        while True:
            # get the current neighbourhood
            neighbours = self.device.supervisor.get_neighbours()
            if neighbours is None:
                break

            self.device.timepoint_done.wait()

            self.wp = Workpool(self.device.scripts)
            threads = []

            # run scripts received until now
            for i in range(8):
            	threads.append(ScriptThread(i, self.device, neighbours, self.wp))
            	threads[i].start()

            for thread in threads:
            	thread.join()
            	del(thread)
            # hope we don't get more than one script
            self.device.barr.wait()
            self.device.timepoint_done.clear()
