#!/usr/bin/env python3
###############################################################################
# Programmer : Jed Richards
# Date : 3/15/2023
# Filename : Scanner.py
# Description : Class for Scanner that packages Ultrasonic Sensor and Servo 
#               into one class with extra functionality.
###############################################################################

############################ Imported Modules #################################
import time 
import math
import matplotlib.pyplot as plt

# For Ultrasonic
import RPi.GPIO as GPIO
import numpy as np

# For Servo
from board import SCL, SDA
import busio
from adafruit_motor import servo
from adafruit_pca9685 import PCA9685

from UltraSonic import Ultrasonic
from Servo import Servo_S51
###############################################################################

################################## Ultrasonic #################################
trigPin = 23    # GPIO 23
echoPin = 24    # GPIO 24
MAX_DISTANCE = 500  
timeOut = MAX_DISTANCE*60 # Calculate timeout according to the maximum measuring
    # distance. This is in micro seconds it takes for sound to travel MAX_DISTANCE
###############################################################################

###################################### Servo ##################################
i2c = busio.I2C(SCL, SDA) # Construct i2c object
pca = PCA9685(i2c) # Create a simple PCA9685 class instance
pca.frequency = 50  # set pulse width frequency 50hz 

# Construct Servo Motor
servo0 = servo.Servo(pca.channels[0], min_pulse=500, max_pulse=2400) # SG90  (S51)
###############################################################################

# Pi constant
PI = np.pi

class Scanner:
    # Construct Servo and Ultrasonic sensor
    def __init__(self):
        self.servo = Servo_S51(i2c, pca, servo0)
        self.ultrasonic = Ultrasonic(trigPin, echoPin, MAX_DISTANCE)
        print("Scanner Initialized")

    # Setup Servo and Ultrasonic Sensor
    def setup(self):
        self.ultrasonic.setup()
        self.servo.setup()

    # Functionallity to turn the servo to angle
    # Calls servo.turn(angle)
    def turn(self, angle):
        self.servo.turn(angle)

    # Convert degerees to radians
    def radians(self, theta):
        return (theta*PI)/180

    # Convert polar cordinates to cartestian (units: cm)
    def cartesian(self, r, theta):
        theta = self.radians(theta) 
        x = r*math.cos(theta)
        y = r*math.sin(theta)
        return x,y

    # Here is the magic.
    # Do a scan from 0-180 by 3 degree increments and get a sonar reading.
    # Then append the reading, in cartestian, to an x_list and y_list. 
    # Finally, plot the x and y arrays as a scatter plot with matplotlib.
    def scan(self):
        x_list = []
        y_list = []
        for i in range(0, 183, 3):
            self.turn(i)

            # Take a sonar reading with .01 secs per reading
            mean, std, var = self.ultrasonic.getReading(0.01)

            # Only take reading if variance is less than 1
            if var < 1:
                distance = mean
                # Only take reading if distance is 1 meter or less.
                if distance <= 100:
                    x,y = self.cartesian(distance, i)
                    # Only take values if the point is not  +-(0,0) 
                    if not ((x == 0 or x == -0) and (y == 0 or y == -0)):
                        x_list.append(x)
                        y_list.append(y)

        # Generate Plot
        plt.scatter(0, 0, s=1000, c="blue")   # Big blue circle at (0,0) is the Scanner
        plt.scatter(x_list, y_list, c="red")  # Plot points as red points
        plt.xlabel('X (cm)')
        plt.ylabel('Y (cm)')
        plt.title('Environment Scan')
        plt.axis([-100, 100, 0, 100])  # Set axis as x = (-100, 100) and y = (0, 100)
        plt.grid()

        plt.savefig('scan.png')  # Save the plot as 'scan.png' file

    def destroy(self):
        self.servo.destroy()
        self.ultrasonic.destroy()

