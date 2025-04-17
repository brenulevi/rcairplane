#pragma once

#include <pigpiod_if2.h>

/**
 * This class uses PIGPIO Daemon as interface to communication with GPIO Hardware.
 * Call init() to begin using and terminate with shutdown()
 */
class GPIO
{
private:
    GPIO();
public:
    static void init();
    static void shutdown();

private:
    static int m_instance;
};