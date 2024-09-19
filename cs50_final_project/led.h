#ifndef LED_H
#define LED_H

#include <wiringPi.h>

// Define GPIO pin numbers for LEDs
const int led = 4;   // GPIO 4 (WiringPi pin 7)
const int led2 = 22; // GPIO 22 (WiringPi pin 3)
const int led3 = 23; // GPIO 23 (WiringPi pin 4)

// Function declarations
void turn_LED_off();
void count_down();
void setup_LEDs();

#endif // LED_H

