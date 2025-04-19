#include "servo.h"

#include <iostream>

#include "raspgpio.h"

Servo::Servo(uint8_t pin)
    : m_pin(pin), m_rangeMin(500), m_rangeMax(2500)
{
}

void Servo::moveDegrees(uint16_t degrees)
{
    uint16_t width = (degrees / 180) * (m_rangeMax - m_rangeMin) + m_rangeMin;
    RASPGPIO::writePWMServoPin(m_pin, width);
}

void Servo::movePulseWidth(uint16_t width)
{
    if (width < m_rangeMin || width > m_rangeMax)
    {
        std::cerr << "Caution: Pulsing " << width << " is out of range\n";
        return;
    }

    RASPGPIO::writePWMServoPin(m_pin, width);
}

void Servo::setPulseRange(uint16_t min, uint16_t max)
{
    m_rangeMin = min;
    m_rangeMax = max;
}
