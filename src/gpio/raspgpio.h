#pragma once

#include <pigpiod_if2.h>

#define CHECK(x) {int error = x; if(error != 0) printError(error, __FILE__, __LINE__); }

#define RASPGPIO_PIN_INPUT PI_INPUT
#define RASPGPIO_PIN_OUTPUT PI_OUTPUT

#define RASPGPIO_PIN_HIGH 1
#define RASPGPIO_PIN_LOW 0

/**
 * This class uses PIGPIO Daemon as interface to communication with GPIO Hardware.
 * Call init() to begin using and terminate with shutdown()
 */
class RASPGPIO
{
private:
    RASPGPIO() = default;
public:
    static int init();
    static void shutdown();

    static void printDetails();

    static void setPinMode(unsigned int pin, unsigned int mode);

    static bool readDigitalPin(unsigned int pin);
    static void writeDigitalPin(unsigned int pin, bool value);

    static unsigned int readPWMServoPin(unsigned int pin);
    static void writePWMServoPin(unsigned int pin, unsigned int value);

    /**
     * Get time in microseconds since pigpio daemon was initialized has a resolution of 2^32 so it wraps around after 72 minutes
     */
    static uint32_t getTime();

private:
    static void printError(int error, const char* file, int line);

private:
    static int m_instance;
};