###############################################################################
# Programmer: Jed Richards
# Date: 3/3/2023
# Description:
#   This is the main code base for an environment scanner using an Ultrasonic
#   Rangefinder, PWM Board (motor controller), and a Servo (0-180 degrees).
#   The goal is to map out a space that depicts the environment of around the
#   sensor with an arc of radius 1 meter from 0-180 degrees. We will eventually 
#   use this as a component on a robot to create a map of its surroundings.
###############################################################################

############################ Imported Modules #################################
import time 
import math

# For Ultrasonic
import RPi.GPIO as GPIO
import numpy as np

# For Servo
from board import SCL, SDA
import busio
from adafruit_motor import servo
from adafruit_pca9685 import PCA9685

# For Scanner (full component)
from Scanner import Scanner
###############################################################################

if __name__ == '__main__':      # Program entrance
    print('Program is starting...')
    Scanner = Scanner()   # create scanner
    Scanner.setup()       # setup scanner
    try:
        Scanner.scan()    # conduct scan
        Scanner.destroy() # destroy scanner
    except KeyboardInterrupt:   # press ctrl-c to end the program.
        Scanner.destroy()
