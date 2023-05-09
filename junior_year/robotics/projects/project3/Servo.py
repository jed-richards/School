#!/usr/bin/env python3
###############################################################################
# Programmer : Jed Richards
# Date : 3/15/2023
# Filename : Scanner.py
# Description : Class for Scanner that packages Ultrasonic Sensor and Servo 
#               into one class with extra functionality.
###############################################################################

import time
from board import SCL, SDA
import busio
from adafruit_motor import servo
from adafruit_pca9685 import PCA9685

class Servo_S51:
    # Construct servo object
    def __init__(self, i2c, pca, servo):
        # Construct i2c object
        self.i2c = i2c

        # Create a simple PCA9685 class instance
        self.pca = pca

        # Construct Servo Motors in channels 0 and 4
        self.servo0 = servo
        
        print("Servo Initialized")

    # On setup set angle to 0
    def setup(self):
        self.servo0.angle = 0

    # Functionality to turn. 
    def turn(self, angle):
        if (angle < 0):
            self.servo0.angle = 0
        elif (angle > 180):
            self.servo0.angle = 180
        else:
            self.servo0.angle = angle

    # De-initialize pca object and turn servo motor off.
    def destroy(self):
        self.servo0.angle = None
        self.pca.deinit()

