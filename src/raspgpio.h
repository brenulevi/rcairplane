#pragma once

#include <pigpiod_if2.h>

#define CHECK(x) {int error = x; if(error != 0) printError(error, __FILE__, __LINE__); }

#define GPIO_PIN_INPUT PI_INPUT
#define GPIO_PIN_OUTPUT PI_OUTPUT

/**
 * This class uses PIGPIO Daemon as interface to communication with GPIO Hardware.
 * Call init() to begin using and terminate with shutdown()
 */
class RASPGPIO
{
private:
    RASPGPIO();
public:
    static int init();
    static void shutdown();

    static void printDetails();

    static void setPinMode(unsigned int pin, unsigned int mode);

    static bool readDigitalPin(unsigned int pin);
    static void writeDigitalPin(unsigned int pin, bool value);

    static unsigned int readPWMServoPin(unsigned int pin);
    static void writePWMServoPin(unsigned int pin, unsigned int value);

    static unsigned long getTime();

private:
    static void printError(int error, const char* file, int line);

private:
    static int m_instance;
};