import RPi.GPIO as GPIO
from time import sleep
import dotstar_simpletest as dotstar
import os
import serial


os.system("./permissions.sh")
uart = serial.Serial("/dev/serial0", baudrate=19200, timeout=3000)

import adafruit_thermal_printer
ThermalPrinter = adafruit_thermal_printer.get_printer_class(2.16)
printer = ThermalPrinter(uart)

#Set warnings off (optional)
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
#Set Button and LED pins
Button = 21
LED = 4

GPIO.setup(Button,GPIO.IN,pull_up_down=GPIO.PUD_UP)
GPIO.setup(LED,GPIO.OUT)

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

def print_title():
    printer.double_height = True
    printer.size = adafruit_thermal_printer.SIZE_LARGE
    printer.justify = adafruit_thermal_printer.JUSTIFY_CENTER
    printer.print("BRYAN")
    printer.print("AND")
    printer.print("KACIE")
    printer.double_height = False
    

while True:
    button_state = GPIO.input(Button)
    turn_LED_off()
    print(button_state)
#    dotstar.idle()

    if button_state == 0:
        GPIO.output(LED,GPIO.HIGH)
        dotstar.turn_on()
        count_down()
        print_title()
        os.system("raspistill -n -t 200 -w 512 -h 384 -o - | lp")
        sleep(6)
        
    if button_state == 1:
        GPIO.output(LED,GPIO.LOW)
        dotstar.idle()
    sleep(1)