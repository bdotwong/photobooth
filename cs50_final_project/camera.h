#ifndef CAMERA_H
#define CAMERA_H

#include <wiringPi.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

const int SHUTTER = 16;
const int HALT = 21;
const int LED = 5;

void flashLED(int pin, int times, int delay_ms);
void setupCamera();
void handleCameraShutter();
void handleHaltButton();

#endif // CAMERA_H
