#pragma once

#include "lighting.h"

#define PLANE_LIGHTING_STROBE_GPIOPIN 22
#define PLANE_LIGHTING_NAV_GPIOPIN 23

class Plane
{
private:
    Plane() = default;

public:
    static void init();

    static void tick(uint32_t time);
    static void shutdown();

private:
    static Lighting* m_lighting;
};