#include "gpio.h"

#include <iostream>

int GPIO::m_instance = 0;

GPIO::GPIO()
{
    std::cerr << "This is a static class (singleton) use the static methods!!!\n";
}

void GPIO::init()
{
    m_instance = pigpio_start(nullptr, nullptr);
    std::cout << "PIGPIO VERSION: " << get_pigpio_version(m_instance) << std::endl;
    std::cout << "HARDWARE: " << get_hardware_revision(m_instance) << std::endl;
    std::cout << "PIGPIOD_IF2 VERSION: " << pigpiod_if_version() << std::endl;
}

void GPIO::shutdown()
{
    pigpio_stop(m_instance);
}
