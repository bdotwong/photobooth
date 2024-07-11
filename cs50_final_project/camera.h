#include <wiringPi.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

const int SHUTTER = 16;
const int HALT = 21;
const int LED = 5;

void flashLED(int pin, int times, int delay_ms) {
    for (int i = 0; i < times; ++i) {
        digitalWrite(pin, HIGH);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        digitalWrite(pin, LOW);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}

int main() {
    if (wiringPiSetupGpio() == -1) {
        std::cerr << "Error setting up wiringPi" << std::endl;
        return 1;
    }

    pinMode(SHUTTER, INPUT);
    pullUpDnControl(SHUTTER, PUD_UP);
    pinMode(HALT, INPUT);
    pullUpDnControl(HALT, PUD_UP);
    pinMode(LED, OUTPUT);

    flashLED(LED, 5, 200);

    while (true) {
        if (digitalRead(SHUTTER) == LOW) {
            digitalWrite(LED, HIGH);
            system("raspistill -n -t 200 -w 512 -h 384 -o - | lp");

            std::this_thread::sleep_for(std::chrono::seconds(1));
            while (digitalRead(SHUTTER) == LOW) {
                continue;
            }
            digitalWrite(LED, LOW);
        }

        if (digitalRead(HALT) == LOW) {
            auto starttime = std::chrono::system_clock::now();
            while (digitalRead(HALT) == LOW) {
                auto now = std::chrono::system_clock::now();
                if (std::chrono::duration_cast<std::chrono::seconds>(now - starttime).count() >= 2) {
                    digitalWrite(LED, HIGH);
                    system("shutdown -h now");
                }
            }
        }
    }

    return 0;
}
