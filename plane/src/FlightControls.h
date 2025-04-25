#pragma once

#include <cstdint>
#include <ESP32Servo.h>

#define SURFACE_MIN_PULSE 1000
#define SURFACE_MAX_PULSE 2000

class FlightControls
{
public:
    FlightControls(uint8_t aileronPin, uint8_t elevatorPin, uint8_t rudderPin);

    void setup();

    void resetSurfaces();

    void setAileron(float value);
    void setElevator(float value);
    void setRudder(float value);

private:
    uint8_t m_aileronPin;
    uint8_t m_elevatorPin;
    uint8_t m_rudderPin;

    Servo m_aileron;
    Servo m_elevator;
    Servo m_rudder;
};