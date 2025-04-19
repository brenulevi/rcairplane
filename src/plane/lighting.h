#pragma once

#include "gpio/raspgpio.h"

#define LIGHTING_STROBE_BLINK_INTERVAL 1000000  // In microseconds
#define LIGHTING_STROBE_BLINK_DURATION 250000   // In microseconds

class Lighting
{
public:
    Lighting(uint8_t strobeGPIOPin, uint8_t navGPIOPin);

    void tick(uint32_t time);

    inline void setStrobeEnabled(bool enabled) { m_isStrobeEnabled = enabled; }
    inline void setNavEnabled(bool enabled) { m_isNavEnabled = enabled; RASPGPIO::writeDigitalPin(m_navGPIOPin, enabled); }

    inline void setStrobeBlinkInterval(uint32_t interval) { m_strobeBlinkInterval = interval; }
    inline void SetStrobeBlinkDuration(uint32_t duration) { m_strobeBlinkDuration = duration; }

private:
    uint8_t m_strobeGPIOPin;
    uint8_t m_navGPIOPin;

    bool m_isStrobeEnabled;
    bool m_isNavEnabled;
    
    uint32_t m_strobeTime;
    uint32_t m_strobeBlinkInterval;
    uint32_t m_strobeBlinkDuration;
    int m_blinkStep;
};