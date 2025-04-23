#pragma once

class Math
{
private:
    Math() = default;

public:
    static uint32_t map(uint32_t value, uint32_t inMin, uint32_t inMax, uint32_t outMin, uint32_t outMax);
    static float map(float value, float inMin, float inMax, float outMin, float outMax);
};