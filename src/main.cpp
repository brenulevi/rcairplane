#include <pch.h>

#include "gpio/raspgpio.h"
#include "i2c/i2cbus.h"
#include "plane/plane.h"
#include "modules/ads1115.h"

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
    Plane::init();

    RASPGPIO::printDetails();

    while(isRunning)
    {
        signal(SIGINT, shutdown);

        uint32_t current_time = RASPGPIO::getTime();

        Plane::tick(current_time);
    }

    Plane::shutdown();
    I2CBus::shutdown();
    RASPGPIO::shutdown();

    return 0;
}
