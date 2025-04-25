#include "FlightControls.h"

#include <Arduino.h>

FlightControls::FlightControls(uint8_t aileronPin, uint8_t elevatorPin, uint8_t rudderPin)
    : m_aileronPin(aileronPin), m_elevatorPin(elevatorPin), m_rudderPin(rudderPin)
{
}

void FlightControls::setup()
{
    m_aileron.setPeriodHertz(50);
    m_elevator.setPeriodHertz(50);
    m_rudder.setPeriodHertz(50);

    m_aileron.attach(m_aileronPin, 500, 2400);
    m_elevator.attach(m_elevatorPin, 500, 2400);
    m_rudder.attach(m_rudderPin, 500, 2400);
}

void FlightControls::resetSurfaces()
{
    m_aileron.write(90);
    m_elevator.write(90);
    m_rudder.write(90);
}

void FlightControls::setAileron(float value)
{
    if(value > 1.0f)
        value = 1.0f;
    else if (value < -1.0f)
        value = -1.0f;

    uint16_t center = (SURFACE_MAX_PULSE + SURFACE_MIN_PULSE) / 2.0f;
    uint16_t pulse = center + (SURFACE_MAX_PULSE - center) * value;
    m_aileron.writeMicroseconds(pulse);
}

void FlightControls::setElevator(float value)
{
    if(value > 1.0f)
        value = 1.0f;
    else if (value < -1.0f)
        value = -1.0f;

    uint16_t center = (SURFACE_MAX_PULSE + SURFACE_MIN_PULSE) / 2.0f;
    uint16_t pulse = center + (SURFACE_MAX_PULSE - center) * value;
    m_aileron.writeMicroseconds(pulse);
}

void FlightControls::setRudder(float value)
{
    if(value > 1.0f)
        value = 1.0f;
    else if (value < -1.0f)
        value = -1.0f;

    uint16_t center = (SURFACE_MAX_PULSE + SURFACE_MIN_PULSE) / 2.0f;
    uint16_t pulse = center + (SURFACE_MAX_PULSE - center) * value;
    m_aileron.writeMicroseconds(pulse);
}
