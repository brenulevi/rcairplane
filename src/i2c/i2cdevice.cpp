#include <pch.h>
#include "i2cdevice.h"

bool I2CDevice::operator!=(I2CDevice &other)
{
    return this->address != other.address;
}