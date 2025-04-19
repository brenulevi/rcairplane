#pragma once

#include <cstdint>

#include "i2cdevice.h"

class I2CBus
{
private:
    I2CBus();

public:
    static int init();
    static void shutdown();

    static I2CDevice createDevice(unsigned int address);
    static int writeBytes(I2CDevice& device, uint8_t* data, unsigned int size);
    static int readBytes(I2CDevice& device, uint8_t* data, unsigned int size);

    static int bindDevice(I2CDevice& device);

private:
    static int m_bus;
    static I2CDevice* m_currentDevice;
};