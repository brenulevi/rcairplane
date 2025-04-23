#include "math.h"

uint32_t Math::map(uint32_t value, uint32_t inMin, uint32_t inMax, uint32_t outMin, uint32_t outMax)
{
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

float Math::map(float value, float inMin, float inMax, float outMin, float outMax)
{
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}
