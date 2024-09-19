#include "led.h"
#include <wiringPi.h>
#include <iostream>
#include <unistd.h>

const int Button = 21; // GPIO 21
const int LED = 4;     // GPIO 4

int main() {
    wiringPiSetupGpio(); // Use BCM GPIO numbering
    setup_LEDs();        // Set up LEDs

    pinMode(Button, INPUT);
    pullUpDnControl(Button, PUD_UP);
    pinMode(LED, OUTPUT);

    while (true) {
        int button_state = digitalRead(Button);
        std::cout << button_state << std::endl;

        if (button_state == 0) {
            digitalWrite(LED, HIGH);
            count_down();  // Use the countdown sequence when the button is pressed
        } else {
            digitalWrite(LED, LOW);
        }

        sleep(1); // Sleep for 1 second
    }

    return 0;
}
