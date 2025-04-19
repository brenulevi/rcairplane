#pragma once

#include <cstdint>

struct I2CDevice
{
    uint8_t address;

    bool operator!=(I2CDevice& other);
};