#include <wiringPi.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>

#include "led.h"     // Include the header file for LED functions
#include "camera.h"  // Include the header file for camera functions

// Set up your GPIO pins for buttons, LEDs, etc.
const int Button = 21; // GPIO 21 for Button
const int LED = 4;     // GPIO 4 for an additional LED if needed

// Serial port setup for the thermal printer
void setupSerial(int &serial_port) {
    serial_port = open("/dev/serial0", O_RDWR | O_NOCTTY);
    if (serial_port < 0) {
        std::cerr << "Error opening serial port!" << std::endl;
        exit(1);
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    if (tcgetattr(serial_port, &tty) != 0) {
        std::cerr << "Error getting termios attributes!" << std::endl;
        exit(1);
    }

    // Set baud rate to 19200 (default for thermal printer)
    cfsetospeed(&tty, B19200);
    cfsetispeed(&tty, B19200);

    // 8N1 (8 bits, no parity, 1 stop bit)
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;

    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;

    tcflush(serial_port, TCIFLUSH);
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        std::cerr << "Error setting termios attributes!" << std::endl;
        exit(1);
    }
}

int main() {
    wiringPiSetupGpio();  // Set up wiringPi
    pinMode(Button, INPUT);
    pullUpDnControl(Button, PUD_UP); // Enable internal pull-up resistor for button
    pinMode(LED, OUTPUT);

    setup_LEDs();  // Set up LEDs for countdown

    int serial_port;
    setupSerial(serial_port); // Set up UART serial communication with the thermal printer

    setupCamera();  // Set up camera pins and perform any camera-related initialization

    while (true) {
        int button_state = digitalRead(Button);
        std::cout << button_state << std::endl;

        if (button_state == 0) {
            count_down();  // Perform the LED countdown before taking the picture

            handleCameraShutter();  // Capture the image using raspistill and print it via lp

            // Send another image to the thermal printer (such as cs50_duck.bmp)
            printImageCommand(serial_port, "~/Downloads/cs50_duck.bmp");

            // Wait until the button is released
            while (digitalRead(Button) == 0) {
                usleep(100000);  // Sleep for 100 ms
            }
            digitalWrite(LED, LOW);
        }

        sleep(1);  // Sleep for 1 second before checking the button state again
    }

    close(serial_port);  // Close the serial port when done
    return 0;
}
