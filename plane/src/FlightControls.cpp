#include "FlightControls.h"

#include <Arduino.h>

FlightControls::FlightControls(uint8_t aileronPin, uint8_t elevatorPin, uint8_t rudderPin)
    : m_aileronPin(aileronPin), m_elevatorPin(elevatorPin), m_rudderPin(rudderPin)
{
}

void FlightControls::setup()
{
    if (!m_aileron.attach(m_aileronPin))
        throw std::runtime_error("Aileron servos error to attach pin");

    if (!m_elevator.attach(m_elevatorPin))
        throw std::runtime_error("Elevator servo error to attach pin");

    if (!m_rudder.attach(m_rudderPin))
        throw std::runtime_error("Rudder servo error to attach pin");
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
