#include "Lighting.h"

#include <Arduino.h>

Lighting::Lighting(uint8_t strobePin, uint8_t navPin)
    :   m_strobePin(strobePin), m_navPin(navPin), m_strobeEnabled(false), m_navEnabled(false),
        m_strobeMillis(0), m_strobeStep(0), m_strobeTime(LIGHTING_DEFAULT_STROBE_TIME), m_strobeBlinkTime(LIGHTING_DEFAULT_STROBE_BLINK_TIME)
{
}

void Lighting::setup()
{
    pinMode(m_strobePin, OUTPUT);
    pinMode(m_navPin, OUTPUT);
}

void Lighting::tick(uint64_t currentMillis)
{
    if(m_strobeEnabled)
    {
        if(m_strobeStep == 0 && currentMillis - m_strobeMillis >= m_strobeTime)
        {
            digitalWrite(m_strobePin, HIGH);
            m_strobeStep++;
            m_strobeMillis = currentMillis;
        }
        else if (m_strobeStep == 1 && currentMillis - m_strobeMillis >= m_strobeBlinkTime)
        {
            digitalWrite(m_strobePin, LOW);
            m_strobeStep++;
            m_strobeMillis = currentMillis;
        }
        else if (m_strobeStep == 2 && currentMillis - m_strobeMillis >= m_strobeBlinkTime)
        {
            digitalWrite(m_strobePin, HIGH);
            m_strobeStep++;
            m_strobeMillis = currentMillis;
        }
        else if (m_strobeStep == 3 && currentMillis - m_strobeMillis >= m_strobeBlinkTime)
        {
            digitalWrite(m_strobePin, LOW);
            m_strobeStep = 0;
            m_strobeMillis = currentMillis;
        }
    }
}

void Lighting::setStrobe(bool enabled)
{
    m_strobeEnabled = enabled;
}

void Lighting::setNav(bool enabled)
{
    digitalWrite(m_navPin, enabled);
    m_navEnabled = enabled;
}
