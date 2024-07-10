#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <Adafruit_DotStar.h>

// Define your DotStar strip object
Adafruit_DotStar dots = Adafruit_DotStar(144, DOTSTAR_BGR);

// Helper function to generate a random color
uint32_t randomColor() {
    uint8_t r = random() % 8 * 32;
    uint8_t g = random() % 8 * 32;
    uint8_t b = random() % 8 * 32;
    return dots.Color(r, g, b);
}

// Function to set all LEDs to a random color
void idle() {
    for (int dot = 0; dot < dots.numPixels(); dot++) {
        dots.setPixelColor(dot, randomColor());
    }
    dots.show();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

// Function to turn on all LEDs to white
void turnOn() {
    for (int dot = 0; dot < dots.numPixels(); dot++) {
        dots.setPixelColor(dot, dots.Color(255, 255, 255));
    }
    dots.show();
}

// Function to turn off all LEDs
void turnOff() {
    for (int dot = 0; dot < dots.numPixels(); dot++) {
        dots.setPixelColor(dot, dots.Color(0, 0, 0));
    }
    dots.show();
}

int main() {
    // Initialize the DotStar strip
    dots.begin();
    dots.setBrightness(20);  // Adjust brightness if needed (0-255)

    // Main loop
    while (true) {
        // Randomly change colors on all LEDs
        idle();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        // Uncomment below if you want to test turnOn and turnOff functions
        // turnOn();
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        // turnOff();
        // std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
