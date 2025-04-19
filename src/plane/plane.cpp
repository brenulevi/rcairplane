#include <pch.h>
#include "plane.h"

Lighting* Plane::m_lighting = nullptr;

void Plane::init()
{
    m_lighting = new Lighting(PLANE_LIGHTING_STROBE_GPIOPIN, PLANE_LIGHTING_NAV_GPIOPIN);
}

void Plane::tick(uint32_t time)
{
    m_lighting->tick(time);
}

void Plane::shutdown()
{
    delete m_lighting;
}