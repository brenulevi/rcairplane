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
    if(m_instance < 0)
    {
        std::cerr << "Failed to connect to pigpio daemon, verify if its running\n";
        return;
    }

    std::cout << "PIGPIO VERSION: " << get_pigpio_version(m_instance) << std::endl;
    std::cout << "HARDWARE: " << get_hardware_revision(m_instance) << std::endl;
    std::cout << "PIGPIOD_IF2 VERSION: " << pigpiod_if_version() << std::endl;
}

void GPIO::shutdown()
{
    pigpio_stop(m_instance);
}

void GPIO::setPinMode(unsigned int pin, unsigned int mode)
{
    CHECK(set_mode(m_instance, pin, mode));
}

bool GPIO::readDigitalPin(unsigned int pin)
{
    return gpio_read(m_instance, pin);
}

void GPIO::writeDigitalPin(unsigned int pin, bool value)
{
    CHECK(gpio_write(m_instance, pin, value));
}

unsigned int GPIO::readPWMServoPin(unsigned int pin)
{
    return get_servo_pulsewidth(m_instance, pin);
}

void GPIO::writePWMServoPin(unsigned int pin, unsigned int value)
{
    CHECK(set_servo_pulsewidth(m_instance, pin, value));
}

unsigned long GPIO::getTime()
{
    return get_current_tick(m_instance);
}

void GPIO::printError(int error, const char* file, int line)
{
    std::cerr << "GPIO ERROR::" << line << "::" << file << std::endl;
    std::cerr << pigpio_error(error) << std::endl;
}
