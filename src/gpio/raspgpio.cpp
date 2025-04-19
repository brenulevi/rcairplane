#include <pch.h>
#include "raspgpio.h"

int RASPGPIO::m_instance = 0;

int RASPGPIO::init()
{
    m_instance = pigpio_start(nullptr, nullptr);
    if(m_instance < 0)
    {
        std::cerr << "Failed to connect to pigpio daemon, verify if its running\n";
        return -1;
    }

    return 0;
}

void RASPGPIO::shutdown()
{
    pigpio_stop(m_instance);
}

void RASPGPIO::printDetails()
{
    std::cout << "PIGPIO VERSION: " << get_pigpio_version(m_instance) << std::endl;
    std::cout << "HARDWARE: " << get_hardware_revision(m_instance) << std::endl;
    std::cout << "PIGPIOD_IF2 VERSION: " << pigpiod_if_version() << std::endl;
}

void RASPGPIO::setPinMode(unsigned int pin, unsigned int mode)
{
    CHECK(set_mode(m_instance, pin, mode));
}

bool RASPGPIO::readDigitalPin(unsigned int pin)
{
    return gpio_read(m_instance, pin);
}

void RASPGPIO::writeDigitalPin(unsigned int pin, bool value)
{
    CHECK(gpio_write(m_instance, pin, value));
}

unsigned int RASPGPIO::readPWMServoPin(unsigned int pin)
{
    return get_servo_pulsewidth(m_instance, pin);
}

void RASPGPIO::writePWMServoPin(unsigned int pin, unsigned int value)
{
    CHECK(set_servo_pulsewidth(m_instance, pin, value));
}

uint32_t RASPGPIO::getTime()
{
    return get_current_tick(m_instance);
}

void RASPGPIO::printError(int error, const char* file, int line)
{
    std::cerr << "GPIO ERROR::" << line << "::" << file << std::endl;
    std::cerr << pigpio_error(error) << std::endl;
}
