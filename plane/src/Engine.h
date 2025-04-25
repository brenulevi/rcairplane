#pragma once

#include <cstdint>
#include <ESP32Servo.h>

#define ENGINE_CALIBRATION_WAIT_TIME 2000

#define ENGINE_MIN_PULSE 1000
#define ENGINE_MAX_PULSE 2000

class Engine
{
public:
    Engine(uint8_t pin);

    void setup();

    void setThrottle(float value);

    void startCalibration();
    void tickCalibration(uint64_t currentMillis);

    inline bool isCalibrated() { return m_isCalibrated; }

private:
    uint8_t m_pin;
    Servo m_servo;

    uint64_t m_calibrationMillis;
    bool m_isCalibrated;
};