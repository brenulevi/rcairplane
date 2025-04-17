#include <iostream>
#include <gpio.h>
#include <chrono>
#include <csignal>

bool isRunning = true;

void shutdown(int signum)
{
    std::cout << "\nShutdowing...\n";
    isRunning = false;
}

int main()
{
    std::cout << "Hello, Plane!" << std::endl;

    GPIO::init();

    GPIO::setPinMode(17, GPIO_PIN_OUTPUT);

    unsigned long lastTime = 0;
    bool turnOn = true;
    while(isRunning)
    {
        signal(SIGINT, shutdown);

        if(GPIO::getTime() - lastTime > 2000000 && turnOn)
        {
            GPIO::writeDigitalPin(17, 1);
            GPIO::writePWMServoPin(27, 500);
            GPIO::writePWMServoPin(22, 500);
            lastTime = GPIO::getTime();
            turnOn = false;
        }
        else if (GPIO::getTime() - lastTime > 2000000 && !turnOn)
        {
            GPIO::writeDigitalPin(17, 0);
            GPIO::writePWMServoPin(27, 2000);
            GPIO::writePWMServoPin(22, 2500);
            lastTime = GPIO::getTime();
            turnOn = true;
        }

    }

    GPIO::writePWMServoPin(27, 1500);
    GPIO::writePWMServoPin(22, 1500);

    GPIO::shutdown();

    return 0;
}
