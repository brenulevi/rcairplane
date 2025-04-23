#pragma once

class Servo
{
public:
    Servo(uint32_t pin);

    void pulse(uint32_t width);

    void setRange(uint32_t min, uint32_t max);

private:
    uint32_t m_pin;
    uint32_t m_min, m_max;
};