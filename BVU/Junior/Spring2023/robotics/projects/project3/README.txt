Programmer : Jed Richards
Date : 3/15/2023
Description : 
  This is a README file that describes this project, Environment Scanner.

REQUIREMENTS: 
  This program requires libraries for the PWM Board, Numpy, and Matplotlib.

EXECUTION:
  python3 mapper.py 
  Running the program saves the plot produced with matplotlib as a png file.
  The name is 'scan.png'.

Pin Outs for Ultrasonic Rangefinder and PWM Board:
  Ultrasonic Sensor:
    trigPin = 23    # GPIO 23 using BCM
    echoPin = 24    # GPIO 24 using BCM

  PWM Board:
    Servo on channel 0.
    
Scanner.py:
  This file describes a class in which when constructed the object will have
  functionality of the Servo and Ultrasonic Range Finder along with more
  functions to plot. This file requires Matplotlib.

UltraSonic.py:
  This file describes a class that has functionality to take sonar readings.
  This file requires the use of Numpy. Pin outs stated above.

Servo.py:
  This file describes a class with functionality of a servo and use of a 
  PWM board. This file requires libraries for the PWM Board.

mapper.py:
  This is the executable code that will be run to produce a plot of the 
  environement.
