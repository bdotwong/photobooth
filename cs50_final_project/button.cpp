#include "button.h"

void setupButtonAndLED() {
    wiringPiSetupGpio(); // Use BCM GPIO numbering
    pinMode(Button, INPUT);
    pullUpDnControl(Button, PUD_UP);
    pinMode(LED, OUTPUT);
}

void handleButtonPress() {
    while (true) {
        int button_state = digitalRead(Button);
        std::cout << button_state << std::endl;

        if (button_state == 0) {
            digitalWrite(LED, HIGH);
        } else {
            digitalWrite(LED, LOW);
        }

        sleep(1);
    }
}
