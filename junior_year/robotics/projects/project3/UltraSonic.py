#!/usr/bin/env python3
###############################################################################
# Programmer : Jed Richards
# Date : 3/15/2023
# Filename : UltraSonic.py
# Description : Class for Ultrasonic Rangefinder Sensor with functionality.
#
# Citations : www.freenove.com
#             Dr. Shawn Stone
###############################################################################

import RPi.GPIO as GPIO
import time
import numpy as np

class Ultrasonic:
    # Construct Ultrasonic Sensor
    def __init__(self, trigPin, echoPin, max_distance):
        self.trigPin = trigPin
        self.echoPin = echoPin
        self.max_distance = max_distance
        self.timeOut = self.max_distance*60
        print('Ultrasonic Initialized')

    def setup(self):
        GPIO.setmode(GPIO.BCM) # use Broadcom pin numbers
        GPIO.setup(self.trigPin, GPIO.OUT) # set trigPin to OUTPUT mode
        GPIO.setup(self.echoPin, GPIO.IN)  # set echoPin to INPUT mode

    def pulseIn(self ,pin, level, timeOut): # obtain pulse time of a pin under timeOut
        t0 = time.time()
        while (GPIO.input(pin) != level):
            if ((time.time() - t0) > timeOut*0.000001):
                return 0
        t0 = time.time()
        while (GPIO.input(pin) == level):
            if ((time.time() - t0) > timeOut*0.000001):
                return 0
        pulseTime = (time.time() - t0)*1000000
        return pulseTime

    # Returns a single sonar reading
    def getSonar(self): 
        # make sure trigPin is low and sleep a short time to let sound waves die out
        GPIO.output(self.trigPin, GPIO.LOW) 
        time.sleep(0.000002)

        # Shoot sonar
        GPIO.output(self.trigPin, GPIO.HIGH) # make trigPin output 10us HIGH level
        time.sleep(0.00001) # 10 us

        # Turn off sonar
        GPIO.output(self.trigPin, GPIO.LOW)  # make trigPin output LOW level

        # Check pulse time
        pingTime = self.pulseIn(self.echoPin, GPIO.HIGH, self.timeOut) # read pulse time of echoPin

        # Calculate distance with speed of sound = 340m/s and pingTime in microseconds
        distance = pingTime * 340.0 / 2.0 / 10000.0  

        return distance

    # Returns a complete sonar reading with its statistics
    def getReading(self, t=0):
        distances = []
        for i in range(10):
            distances.append(self.getSonar())
            time.sleep(t) # lets echos die down
        mean = np.mean(distances)
        std = np.std(distances)
        var = np.var(distances)  # variance is how closely clustered the data is
                                 # a small variance means the data is close together
                                 # a large variance means the data is spread out

        return mean, std, var

    def destroy(self):
        GPIO.cleanup() # release GPIO resource


