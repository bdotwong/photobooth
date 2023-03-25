import RPi.GPIO as GPIO
from time import sleep
import dotstar_simpletest as dotstar
import os
import serial

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
#Set Button and LED pins
Button = 21
LED = 4

GPIO.setup(Button,GPIO.IN,pull_up_down=GPIO.PUD_UP)
GPIO.setup(LED,GPIO.OUT)

#while True:
#    button_state = GPIO.input(Button)
#    print(button_state)
#    dotstar.idle()
def button():
    try:
        if button_state == 0:
            GPIO.output(LED,GPIO.HIGH)
            print("Turning LED ON")
    try:
        if button_state == 1:
            GPIO.output(LED,GPIO.LOW)
            print("Turning LED OFF")
    except:
        print("Wait")
button()