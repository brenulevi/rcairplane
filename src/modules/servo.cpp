#include "servo.h"

#include "raspgpio.h"

Servo::Servo(uint32_t pin)
    : m_pin(pin), m_min(500), m_max(2500)
{
    RASPGPIO::setMode(pin, PI_OUTPUT);
}

void Servo::pulse(uint32_t width)
{
    uint32_t w = (width > m_max) ? m_max : (width < m_min) ? m_min : width;
    RASPGPIO::setServoPulse(m_pin, w);
}

void Servo::setRange(uint32_t min, uint32_t max)
{
    m_min = min;
    m_max = max;
}
