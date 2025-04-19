#include <pch.h>
#include "lighting.h"

Lighting::Lighting(uint8_t strobeGPIOPin, uint8_t navGPIOPin)
    : m_strobeGPIOPin(strobeGPIOPin), m_navGPIOPin(navGPIOPin), m_isStrobeEnabled(false), m_isNavEnabled(false)
{
    RASPGPIO::setPinMode(m_strobeGPIOPin, RASPGPIO_PIN_OUTPUT);
    RASPGPIO::setPinMode(m_navGPIOPin, RASPGPIO_PIN_OUTPUT);

    m_strobeTime = 0;
    m_strobeBlinkInterval = LIGHTING_STROBE_BLINK_INTERVAL;
    m_strobeBlinkDuration = LIGHTING_STROBE_BLINK_DURATION;
    m_blinkStep = 0;
}

void Lighting::tick(uint32_t time)
{
    if(m_isStrobeEnabled)
    {
        if(time - m_strobeTime >= m_strobeBlinkInterval && m_blinkStep == 0)
        {
            RASPGPIO::writeDigitalPin(m_strobeGPIOPin, RASPGPIO_PIN_HIGH);
            m_blinkStep++;
        }
        if(time - m_strobeTime >= m_strobeBlinkDuration && m_blinkStep == 1)
        {
            RASPGPIO::writeDigitalPin(m_strobeGPIOPin, RASPGPIO_PIN_LOW);
            m_blinkStep++;
        }
        if(time - m_strobeTime >= m_strobeBlinkDuration && m_blinkStep == 2)
        {
            RASPGPIO::writeDigitalPin(m_strobeGPIOPin, RASPGPIO_PIN_HIGH);
            m_blinkStep++;
        }
        if(time - m_strobeTime >= m_strobeBlinkDuration && m_blinkStep == 3)
        {
            RASPGPIO::writeDigitalPin(m_strobeGPIOPin, RASPGPIO_PIN_LOW);
            m_blinkStep = 0;
        }
    }

    m_strobeTime = time;
}
