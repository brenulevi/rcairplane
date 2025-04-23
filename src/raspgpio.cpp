#include "raspgpio.h"

int RASPGPIO::m_instance = 0;

void RASPGPIO::init()
{
    m_instance = pigpio_start(nullptr, nullptr);
    if(m_instance < 0)
    {
        std::cerr << "Unable to connect to pigpio daemon, check if its running!!!\n";
        return;
    }
}

void RASPGPIO::shutdown()
{
    pigpio_stop(m_instance);
}

void RASPGPIO::setMode(uint32_t pin, int mode)
{
    set_mode(m_instance, pin, mode);
}

void RASPGPIO::setServoPulse(uint32_t pin, uint32_t width)
{
    set_servo_pulsewidth(m_instance, pin, width);
}
