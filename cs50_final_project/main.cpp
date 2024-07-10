#include <wiringPi.h>
#include <iostream>
#include <unistd.h>

const int Button = 21; // GPIO 21
const int LED = 4;     // GPIO 4

int main() {
    wiringPiSetupGpio(); //

    pinMode(Button, INPUT);
    pullUpDnControl(Button, PUD_UP);
    pinMode(LED, OUTPUT);

    while (true) {
        int button_state = digitalRead(Button);
        std::cout << button_state << std::endl;

        if (button_state == 0) {
            digitalWrite(LED, HIGH);
        } else {
            digitalWrite(LED, LOW);
        }

        sleep(1); // Sleep for 1 second

        /*
        if (button_state == 0) {
            sleep(0.5);
            if (flag == 0) {
                flag = 1;
            } else {
                flag = 0;
            }
        }
        if (flag == 1) {
            digitalWrite(LED, HIGH);
        } else {
            digitalWrite(LED, LOW);
        }
        */
    }

    return 0;
}
