#include <wiringPi.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <cstring>
#include <cstdlib>
#include "led.h"  // Include your LED header file

// Set up your GPIO pins for buttons, LEDs, etc.
const int Button = 21; // GPIO 21
const int LED = 4;     // GPIO 4

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
    tty.c_cflag &= ~PARENB; // Clear parity bit
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
    tty.c_cflag &= ~CSIZE;  // Clear data size setting
    tty.c_cflag |= CS8;     // Set 8 data bits

    tty.c_cflag &= ~CRTSCTS; // No hardware flow control
    tty.c_cflag |= CREAD | CLOCAL; // Enable receiver

    tcflush(serial_port, TCIFLUSH);
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        std::cerr << "Error setting termios attributes!" << std::endl;
        exit(1);
    }
}

void sendText(int serial_port, const char* message) {
    write(serial_port, message, strlen(message));
}

void printImageCommand(const char* image_path) {
    // Print the image using `lp` with fit-to-page option
    std::string cmd = "lp -o fit-to-page " + std::string(image_path);
    system(cmd.c_str());
}

int main() {
    wiringPiSetupGpio(); // Set up wiringPi
    pinMode(Button, INPUT);
    pullUpDnControl(Button, PUD_UP); // Enable internal pull-up resistor
    pinMode(LED, OUTPUT);

    setup_LEDs();  // Set up LEDs for countdown

    int serial_port;
    setupSerial(serial_port); // Set up UART serial communication with the thermal printer

    while (true) {
        int button_state = digitalRead(Button);
        std::cout << button_state << std::endl;

        if (button_state == 0) {
            count_down();  // Perform the LED countdown

            // Capture image using raspistill
            system("raspistill -n -t 200 -w 512 -h 384 -o /tmp/photo.jpg");

            // Send the image to the thermal printer using `lp`
            printImageCommand("/tmp/photo.jpg", "~/Downloads/cs50_duck.bmp");

            // Wait until the button is released
            while (digitalRead(Button) == 0) {
                usleep(100000); // Sleep for 100 ms
            }
            digitalWrite(LED, LOW);
        }

        sleep(1); // Sleep for 1 second
    }

    // Close the serial port when done
    close(serial_port);
    return 0;
}
