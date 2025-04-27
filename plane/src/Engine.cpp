#include "Engine.h"

#include <Arduino.h>

Engine::Engine(uint8_t pin)
    : m_pin(pin), m_isOn(false), m_lastPulse(0)
{
}

void Engine::setup()
{
    m_servo.attach(m_pin);
}

void Engine::setThrottle(float value)
{
    if(!m_isOn)
        return;

    if (value > 1.0f)
        value = 1.0f;
    else if (value < 0.0f)
        value = 0.0f;

    uint16_t pulse = ENGINE_IDLE_PULSE + (ENGINE_MAX_PULSE - ENGINE_IDLE_PULSE) * value;

    /** 
     * quickly change in throttle
     * reject this
     * (probably noise in radio or miswiring)
     * (HAHAHAHAHAHA I HOPE MY AIRPLANE DONT BROKE AGAIN WITH THIS CODE BECAUSE NOW ITS SAFE AND SOUND)
    */
    if(pulse - m_lastPulse > ENGINE_MAX_THROTTLE_STEP)
        return;

    m_servo.writeMicroseconds(pulse);
    m_lastPulse = pulse;
}

void Engine::calibrate()
{
    m_servo.writeMicroseconds(ENGINE_MIN_PULSE);
    m_lastPulse = ENGINE_MIN_PULSE;
    delay(2000);
}

void Engine::turnOn()
{
    m_servo.writeMicroseconds(ENGINE_IDLE_PULSE);
    m_lastPulse = ENGINE_IDLE_PULSE;
    m_isOn = true;
}

void Engine::turnOff()
{
    m_servo.writeMicroseconds(ENGINE_MIN_PULSE);
    m_isOn = false;
}
