#include "led.h"
#include <iostream>
#include <unistd.h>

// Function to turn off the LEDs
void turn_LED_off() {
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
}

// Function to perform a countdown sequence by turning on LEDs one by one
void count_down() {
    digitalWrite(led, HIGH);
    sleep(1);
    digitalWrite(led2, HIGH);
    sleep(1);
    digitalWrite(led3, HIGH);
    sleep(2);
    turn_LED_off();
}

// Function to set up the LED pins as outputs
void setup_LEDs() {
    if (wiringPiSetupGpio() == -1) {
        std::cerr << "Error setting up wiringPi" << std::endl;
        exit(1);
    }

    pinMode(led, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
}
