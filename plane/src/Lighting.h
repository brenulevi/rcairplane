#pragma once

#include <cstdint>

#define LIGHTING_DEFAULT_STROBE_TIME 1000
#define LIGHTING_DEFAULT_STROBE_BLINK_TIME 50

class Lighting
{
public:
    Lighting(uint8_t strobePin, uint8_t navPin);

    void setup();
    void tick(uint64_t currentMillis);

    void setStrobe(bool enabled);
    void setNav(bool enabled);

    inline void setStrobeTime(uint16_t time) { m_strobeTime = time; }
    inline void setStrobeBlinkTime(uint16_t time) { m_strobeBlinkTime = time; }

private:
    uint8_t m_strobePin;
    uint8_t m_navPin;

    bool m_strobeEnabled;
    bool m_navEnabled;

    uint64_t m_strobeMillis;
    uint8_t m_strobeStep;

    uint16_t m_strobeTime;
    uint16_t m_strobeBlinkTime;
};