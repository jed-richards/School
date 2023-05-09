#!/usr/bin/env python3
###############################################################################
# Filename : UltrasonicRangeTest.py
# Description : Get distance via Ultrasonic Range Sensor
# Author : www.freenove.com
# Modification : 2019/12/08
# Modified by Stone 2023
###############################################################################

import RPi.GPIO as GPIO
import time

trigPin = 23    # GPIO 23
echoPin = 24    # GPIO 24
MAX_DISTANCE = 220  # Define the maximum measuring distance, units: cm
                    # Might play with 220 later

timeOut = MAX_DISTANCE*60 # Calculate timeout according to the maximum measuring
    # distance. This is in micro seconds it takes for sound to travel MAX_DISTANCE

def pulseIn(pin, level, timeOut): # obtain puls time of a pin under timeOut
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

def getSonar(): # get the measurement results of ultrasonic module, with unit: cm
    GPIO.output(trigPin, GPIO.HIGH) # make trigPin output 10us HIGH level
    time.sleep(0.00001) # 10 us
    GPIO.output(trigPin, GPIO.LOW)  # make trigPin output LOW level
    pingTime = pulseIn(echoPin, GPIO.HIGH, timeOut) # read pulse time of echoPin
    distance = pingTime * 340.0 / 2.0 / 10000.0  # calculate distanc with sound 340m/s
                                                 # and pingTime in microseconds
    return distance

def setup():
    GPIO.setmode(GPIO.BCM) # use Broadcom pin numbers
    GPIO.setup(trigPin, GPIO.OUT) # set trigPin to OUTPUT mode
    GPIO.setup(echoPin, GPIO.IN)  # set echoPin to INPUT mode

def loop():
    #values = []
    for i in range(100):
        distance = getSonar() # get distance
        print('%.2f' %(distance)) # output the distance to 2 decimal places

        #values.append(distance)

        # output the distance to a file from the command line by redirection
        # for example: python3 UltrasonicRangeTest.py >> output.txt
        time.sleep(1) # lets echos die down
        #time.sleep(.1) # lets echos die down
        #time.sleep(.01) # lets echos die down
        #time.sleep(.001) # lets echos die down

    #[print(i) for i in values]  # prints values using list comprehension

    GPIO.cleanup() # exit nicely

if __name__ == '__main__': # program entrance
    setup()
    try:
        loop()
    except KeyboardInterrupt: # press ctrl-c to end program
        GPIO.cleanup() # release GPIO resource
