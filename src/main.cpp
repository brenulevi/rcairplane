#include <iostream>
#include <pigpio.h>

int main()
{
    if(!gpioInitialise() < 0)
    {
        std::cerr << "Failed to initialized pigpio" << std::endl;
        return 1;
    }

    std::cout << "Hello World" << std::endl;

    gpioSetMode(13, PI_OUTPUT);

    gpioWrite(13, PI_HIGH);

    gpioDelay(10000);

    gpioWrite(13, PI_HIGH);

    gpioTerminate();

    return 0;
}