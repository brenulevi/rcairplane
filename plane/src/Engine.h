#pragma once

#include <cstdint>
#include <ESP32Servo.h>

#define ENGINE_CALIBRATION_WAIT_TIME 2000

#define ENGINE_MIN_PULSE 1000
#define ENGINE_IDLE_PULSE 1200
#define ENGINE_MAX_PULSE 2000

#define ENGINE_MAX_THROTTLE_STEP 500

class Engine
{
public:
    Engine(uint8_t pin);

    void setup();
    void calibrate();

    void turnOn();
    void turnOff();

    void setThrottle(float value);

    inline bool isOn() { return m_isOn; }

private:
    uint8_t m_pin;
    Servo m_servo;
    bool m_isOn;
    uint16_t m_lastPulse;
};