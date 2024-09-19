#ifndef BUTTON_H
#define BUTTON_H

#include <wiringPi.h>
#include <iostream>
#include <unistd.h>

const int Button = 21; // GPIO 21
const int LED = 4;     // GPIO 4

void setupButtonAndLED();
void handleButtonPress();

#endif // BUTTON_H
