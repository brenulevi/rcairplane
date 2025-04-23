#pragma once

#include <pigpiod_if2.h>

class RASPGPIO
{
private:
    RASPGPIO() = default;
public:
    static void init();
    static void shutdown();

    static void setMode(uint32_t pin, int mode);

    static void setServoPulse(uint32_t pin, uint32_t width);

private:
    static int m_instance;
};