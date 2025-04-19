#include <iostream>
#include "raspgpio.h"
#include <chrono>
#include <csignal>

#include <RF24/RF24.h>

#include "i2c/i2cbus.h"

bool isRunning = true;

void shutdown(int signum)
{
    std::cout << "\nShutdowing...\n";
    isRunning = false;
}

int main()
{
    std::cout << "Hello, Plane!" << std::endl;

    RASPGPIO::init();
    I2CBus::init();

    RASPGPIO::setPinMode(17, GPIO_PIN_OUTPUT);

    unsigned long lastTime = 0;
    bool turnOn = true;
    while(isRunning)
    {
        signal(SIGINT, shutdown);

        if(RASPGPIO::getTime() - lastTime > 2000000 && turnOn)
        {
            RASPGPIO::writeDigitalPin(17, 1);
            RASPGPIO::writePWMServoPin(27, 500);
            RASPGPIO::writePWMServoPin(22, 500);
            lastTime = RASPGPIO::getTime();
            turnOn = false;
        }
        else if (RASPGPIO::getTime() - lastTime > 2000000 && !turnOn)
        {
            RASPGPIO::writeDigitalPin(17, 0);
            RASPGPIO::writePWMServoPin(27, 2000);
            RASPGPIO::writePWMServoPin(22, 2500);
            lastTime = RASPGPIO::getTime();
            turnOn = true;
        }

    }

    RASPGPIO::writePWMServoPin(27, 1500);
    RASPGPIO::writePWMServoPin(22, 1500);

    I2CBus::shutdown();
    RASPGPIO::shutdown();

    return 0;
}
