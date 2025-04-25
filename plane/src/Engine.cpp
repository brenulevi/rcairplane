#include "Engine.h"

#include <Arduino.h>

Engine::Engine(uint8_t pin)
    : m_pin(pin), m_calibrationMillis(0), m_isCalibrated(false)
{
}

void Engine::setup()
{
    if (!m_servo.attach(m_pin))
        throw std::runtime_error("Engine servo error to attach pin");
}

void Engine::setThrottle(float value)
{
    if (value > 1.0f)
        value = 1.0f;
    else if (value < 0.0f)
        value = 0.0f;

    uint16_t pulse = ENGINE_MIN_PULSE + (ENGINE_MAX_PULSE - ENGINE_MIN_PULSE) * value;
    m_servo.writeMicroseconds(pulse);
}

void Engine::startCalibration()
{
    m_servo.writeMicroseconds(ENGINE_MIN_PULSE);
    m_calibrationMillis = millis();
}

void Engine::tickCalibration(uint64_t currentMillis)
{
    if (currentMillis - m_calibrationMillis > ENGINE_CALIBRATION_WAIT_TIME)
    {
        m_isCalibrated = true;
    }
}
