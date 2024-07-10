#include <wiringPi.h>
#include <iostream>
#include <unistd.h>

const int led = 4;   // GPIO 4 (WiringPi pin 7)
const int led2 = 22; // GPIO 22 (WiringPi pin 3)
const int led3 = 23; // GPIO 23 (WiringPi pin 4)

void turn_LED_off() {
    digitalWrite(led, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
}

void count_down() {
    digitalWrite(led, HIGH);
    sleep(1);
    digitalWrite(led2, HIGH);
    sleep(1);
    digitalWrite(led3, HIGH);
    sleep(2);
    turn_LED_off();
}

int main() {
    if (wiringPiSetupGpio() == -1) {
        std::cerr << "Error setting up wiringPi" << std::endl;
        return 1;
    }

    pinMode(led, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);

    count_down();

    turn_LED_off();
    return 0;
}
