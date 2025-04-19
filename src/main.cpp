#include <iostream>
#include <chrono>
#include <csignal>

#include <RF24/RF24.h>

#include "raspgpio.h"
#include "i2c/i2cbus.h"
#include "modules/ads1115.h"
#include "plane/rcplane.h"
#include "modules/servo.h"

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

    ADS1115 ads1115(0b1001000);
    ads1115.startConversion();

    usleep(10000);

    uint16_t value = ads1115.readValue();

    Servo servo1(27);
    Servo servo2(22);

    RASPGPIO::setPinMode(17, GPIO_PIN_OUTPUT);

    RCPlane::init();

    unsigned long lastTime = 0;
    bool turnOn = true;
    while(isRunning)
    {
        signal(SIGINT, shutdown);

        if(RASPGPIO::getTime() - lastTime > 2000000 && turnOn)
        {
            RASPGPIO::writeDigitalPin(17, 1);
            servo1.moveDegrees(0);
            servo2.movePulseWidth(500);
            lastTime = RASPGPIO::getTime();
            turnOn = false;
        }
        else if (RASPGPIO::getTime() - lastTime > 2000000 && !turnOn)
        {
            RASPGPIO::writeDigitalPin(17, 0);

            servo1.moveDegrees(180);
            servo2.movePulseWidth(2500);

            lastTime = RASPGPIO::getTime();
            turnOn = true;
        }

        RCPlane::tick();
    }

    RCPlane::shutdown();

    servo1.moveDegrees(90);
    servo2.movePulseWidth(1500);

    I2CBus::shutdown();
    RASPGPIO::shutdown();

    return 0;
}
