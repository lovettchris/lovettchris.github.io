#!/usr/bin/env python3
# ####################################################################################################
#
# Project:  Wireless remote light switch
# File:     Lights.py
# Authors:  Chris Lovett
#
# Requires: Python 3.5+
#
####################################################################################################
import argparse
from datetime import datetime
import time
import sys
import serial
import serial.tools.list_ports

from astral import Location

class Log:
    def __init__(self):
         self.logfile = open("lights.log", "w")
        
    def write(self, msg):
        self.logfile.write(msg)
        print(msg, end='')
        self.logfile.flush()

    def writeln(self, msg):
        self.logfile.write(msg)
        self.logfile.write("\n")
        print(msg)        
        self.logfile.flush()


class LightController:
    def __init__(self, port, log):
        
        self.southLights = 0; # 4; # south lights
        self.northLights = 12; # north lights        

        self.southFrequency = 1 # new remote
        self.northFrequency = 2.77 # old remote is slower.

        self.log = log
        self.port = port
        self.serial = serial.Serial()
        self.serial.port = port
        self.baudrate = 115200
        self.serial.open()
        retries = 5
        self.connected = False
        while self.serial.isOpen() and retries > 0:
            self.serial.write("\r".encode())
            response = self.serial.readline().decode().strip()
            response2 = self.serial.readline().decode().strip()
            if response == "Remote Light Controller" or response2 == "Remote Light Controller":
                self.log.writeln("connected")
                self.connected = True
                break
            retries -= 1

        if not self.connected:
            self.log.writeln("Unexpected response from controller: {}".format(response2))
            sys.exit(1)

    def run(self):
        while True:
            secondsToNextEvent = self.checkLights()
            time.sleep(secondsToNextEvent)

    def sendCommand(self, cmd):
        self.serial.write(cmd.encode())
        # we are expecting an echo response
        response = self.serial.readline().decode()
        # and a command response
        response = self.serial.readline().decode()
        return response.strip()

    def setFrequency(self, freq):    
        response = self.sendCommand("freq:{}\r".format(freq))
        self.log.writeln("frequency:" + response)

    def turnOff(self):    
        for i in range(3):
            response = self.sendCommand("off:{},freq:{}\r".format(self.southLights, self.southFrequency))
            self.log.writeln("south:" + response)
            time.sleep(1)
        time.sleep(2)
        for i in range(3):
            response = self.sendCommand("off:{},freq:{}\r".format(self.northLights, self.northFrequency))
            self.log.writeln("north:" + response)
            time.sleep(1)

    def turnOn(self):        
        for i in range(3):
            response = self.sendCommand("on:{},freq:{}\r".format(self.southLights, self.southFrequency))
            self.log.writeln("south:" + response)
            time.sleep(1)
        time.sleep(2)
        for i in range(3):
            response = self.sendCommand("on:{},freq:{}\r".format(self.northLights, self.northFrequency))
            self.log.writeln("north:" + response)
            time.sleep(1)

    def checkLights(self):
        # Get sunrise and sunset for Woodinville, WA
        l = Location()
        l.latitude =  47.763212
        l.longitude =  -122.068400
        l.timezone = 'US/Pacific'

        sunrise = l.sun()['dawn']
        sunrise = sunrise.replace(tzinfo=None)
        sunrise_hour = sunrise.strftime('%H')
        sunrise_minute = sunrise.strftime('%M')
        self.log.writeln('sunrise {}:{}'.format(sunrise_hour, sunrise_minute))

        sunset = l.sun()['sunset']
        sunset = sunset.replace(tzinfo=None)
        sunset_hour = sunset.strftime('%H')
        sunset_minute = sunset.strftime('%M')
        self.log.writeln('sunset {}:{}'.format(sunset_hour, sunset_minute))

        current_time = datetime.now()
        current_hour = current_time.hour
        current_minute = current_time.minute

        self.log.writeln('current time={}:{}'.format(current_hour, current_minute))

        sunrise_delta = sunrise - current_time
        sunrise_seconds = sunrise_delta.total_seconds()
        self.log.writeln('time till sunrise is {} seconds'.format(sunrise_seconds))

        sunset_delta = sunset - current_time
        sunset_seconds = sunset_delta.total_seconds()
        self.log.writeln('time till sunset is {} seconds'.format(sunset_seconds))

        if sunrise_seconds < 0 and sunset_seconds <= 0:
            self.log.writeln("Turning on the lights")
            self.turnOn()
            self.log.writeln("Turning off the lights in {} seconds".format(-sunrise_seconds))
            return -sunrise_seconds
        elif sunrise_seconds > 0 and sunset_seconds > 0:
            self.log.writeln("Turning on the lights")
            self.turnOn()
            self.log.writeln("Turning off the lights in {} seconds".format(sunrise_seconds))
            return sunrise_seconds
        elif sunrise_seconds <= 0 and sunset_seconds > 0:
            self.log.writeln("Turning off the lights")
            self.turnOff()
            self.log.writeln("Turning on the lights in {} seconds".format(sunset_seconds))
            return sunset_seconds
        
if __name__ == "__main__":    
    parser = argparse.ArgumentParser("Control the lights on given serial port so they turn on at sunset and off at sunrise")
    parser.add_argument("--port", help="Name of COM port to talk to Arduino (default is first Arduino device found)", default=None)
    parser.add_argument("--on", help="Turn on the lights", action="store_true")
    parser.add_argument("--off", help="Turn off the lights", action="store_true")
    args = parser.parse_args()    

    log = Log()

    port = args.port
    if port is None:
        ports = list(serial.tools.list_ports.comports())
        for p in ports:
            if "Arduino" in p.manufacturer:                
                port = p.device                
                break
    
    if port is None:
        log.writeln("### Error: No port found connected to an Arduino")
    else:
        log.writeln("Using COM port: {}".format(port))
        controller = LightController(port, log)
        if args.on:
            controller.turnOn()
        elif args.off:
            controller.turnOff()
        else:
            controller.run()
