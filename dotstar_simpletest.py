# SPDX-FileCopyrightText: 2021 ladyada for Adafruit Industries
# SPDX-License-Identifier: MIT

import time
import random
import board
import adafruit_dotstar as dotstar

# On-board DotStar for boards including Gemma, Trinket, and ItsyBitsy
#dots = dotstar.DotStar(board.APA102_SCK, board.APA102_MOSI, 1, brightness=0.2)

# Using a DotStar Digital LED Strip with 30 LEDs connected to hardware SPI
dots = dotstar.DotStar(board.SCK, board.MOSI, 144, brightness=0.2)

# Using a DotStar Digital LED Strip with 30 LEDs connected to digital pins
#dots = dotstar.DotStar(board.D6, board.D5, 30, brightness=0.2)

n_dots = len(dots)

# HELPERS
# a random color 0 -> 192
def random_color():
    return random.randrange(0, 7) * 32

def idle():
    for dot in range(n_dots):
        dots[dot] = (random_color(), random_color(), random_color())
        time.sleep(0.0001)            
        
def turn_on():
    for dot in range(n_dots):
        dots[dot] = (255, 255, 255)

def turn_off():
    for dot in range(n_dots):
        dots[dot] = (0, 0, 0)
idle()

# MAIN LOOP
#n_dots = len(dots)
#while True:
    # Fill each dot with a random color
#    for dot in range(n_dots):
#        dots[dot] = (random_color(), random_color(), random_color())
#        dots[dot] = (0, 0, 0)
#        dots[dot] = (192, 192, 192)
#    time.sleep(0.25)
