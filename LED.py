#import libraries
import RPi.GPIO as GPIO
import time

#GPIO Basic initialization
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

#Use a variable for the Pin to use
#If you followed my pictures, it's port 7 => BCM 4
led = 4
led2 = 22
led3 = 23
#Initialize your pin
GPIO.setup(led,GPIO.OUT)
GPIO.setup(led2,GPIO.OUT)
GPIO.setup(led3,GPIO.OUT)

def turn_LED_off():
    GPIO.output(led,0)
    GPIO.output(led2,0)
    GPIO.output(led3,0)
    
#Turn on the LED
def count_down():
    GPIO.output(led,1)
    time.sleep(1)    
    GPIO.output(led2,1)
    time.sleep(1)
    GPIO.output(led3,1)
    time.sleep(2)
    turn_LED_off()

count_down()