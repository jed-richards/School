#lab09 : this code gets a plot of click/second vs duty cycle.

import RPi.GPIO as GPIO
import time
import random

#pins for the motors

motor1Pin1 = 17
motor1Pin2 = 27
enablePin1 = 22

motor2Pin1 = 18
motor2Pin2 = 23
enablePin2 = 24

# encoder pins
CLK= 5    # The AC switch of the encoder input to Pi
DT= 6    # The BC switch of the encoder input to pi
def setup():
    
    global p1 # global to use in functions external to setup
    global p2
    
    GPIO.setmode(GPIO.BCM)   
    GPIO.setup(motor1Pin1,GPIO.OUT)   # set pins to OUTPUT mode
    GPIO.setup(motor1Pin2,GPIO.OUT)
    GPIO.setup(enablePin1,GPIO.OUT)
        
    p1 = GPIO.PWM(enablePin1,1000) # creat PWM and set Frequence to 1KHz
    p1.start(0)

    GPIO.setup(motor2Pin1,GPIO.OUT)   # set pins to OUTPUT mode
    GPIO.setup(motor2Pin2,GPIO.OUT)
    GPIO.setup(enablePin2,GPIO.OUT)
        
    p2 = GPIO.PWM(enablePin2,1000) # creat PWM and set Frequence to 1KHz
    p2.start(0)

    GPIO.setup(CLK, GPIO.IN, pull_up_down=GPIO.PUD_UP)   # set pin 17 to input
    
    GPIO.setup(DT, GPIO.IN, pull_up_down=GPIO.PUD_UP)    # set pin 27 to input

	

def motor(speed,tm,direction):
    if direction=="f":
        GPIO.output(motor1Pin1,GPIO.HIGH)  # Forward
        GPIO.output(motor1Pin2,GPIO.LOW)   
        GPIO.output(motor2Pin1,GPIO.HIGH)  
        GPIO.output(motor2Pin2,GPIO.LOW)   
        p1.start(speed)
        p2.start(speed)
    
        time.sleep(tm)
        

    else:
        GPIO.output(motor1Pin1,GPIO.LOW)  # backward
        GPIO.output(motor1Pin2,GPIO.HIGH)  
        GPIO.output(motor2Pin1,GPIO.LOW)  
        GPIO.output(motor2Pin2,GPIO.HIGH)  
        p1.start(speed)
        p2.start(speed)
        time.sleep(tm)
        
# cmpare returns true if two gray codes are equal and false otherwise    
def cmpare(one,two):
    if one[0] != two[0]:
        return False

    if one[1] != two[1]:
        return False
    return True

def clicks(tinterval):
    transition=[[1,1],[1,1],[1,1],[1,1]] # each sequence has four gray codes
    SM1=[1,1] # State Minus 1 resting code
    SM0=[1,1] # State Minus 0 resting code
    t=0 # the transition number
    clicks=0
    t1=time.time()
    while (time.time()-t1)<tinterval:
        
        if t==4: # if 4 transitions have been detected then it is time to test the encoder sequence
            # CCW test
            if cmpare(transition[0],[1,0]) and cmpare(transition[1],[0,0]) and cmpare(transition[2],[0,1]) and cmpare(transition[3],[1,1]):
                clicks=clicks-1
            # CW test
            elif cmpare(transition[0],[0,1]) and cmpare(transition[1],[0,0]) and cmpare(transition[2],[1,0]) and cmpare(transition[3],[1,1]):
                clicks=clicks+1
            # it is a bounce state
            else: 
                

                if clicks<0:
                    clicks=click-1
                else:
                    clicks=clicks+1
                        


            # reset for next detection
            SM1=[1,1]
            SM0=[1,1]
            transition=[[1,1],[1,1],[1,1],[1,1]]
            t=0
        time.sleep(random.randrange(10)/10000)
        # read encoder pins
        CLK_STATE=GPIO.input(CLK)
        DT_STATE=GPIO.input(DT)
        
        # store current state
        SM0=[CLK_STATE,DT_STATE]
        # detect a change
        if not cmpare(SM0,SM1):
            transition[t]=SM0 # a change in state is detected and stored
            SM1=SM0 # update old state
            t=t+1 # advance transition number


    return clicks
def destroy():
    p1.stop()  # stop PWM
    p2.stop()
    GPIO.cleanup()




if __name__ == '__main__':  # Program entrance
   
    setup()
    #smooth test
    
    print("Enter speed:")
    speed=int(input())
    print("enter direction:")
    d=input()
    

    print("Enter time is seconds:")
    t=int(input())
    motor(speed,0,d)
    print(clicks(t)/t)
        
    
        
    p1.stop()
    p2.stop()
    
    destroy()



