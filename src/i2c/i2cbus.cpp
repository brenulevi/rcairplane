#include "i2cbus.h"

#include <iostream>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdint>
#include <fcntl.h>

#include <utils.h>

int I2CBus::m_bus;
I2CDevice* I2CBus::m_currentDevice = nullptr;

I2CBus::I2CBus()
{
    std::cerr << "This is a static class (singleton) use the static methods!!!\n";
}

int I2CBus::init()
{
    m_bus = open("/dev/i2c-1", O_RDWR);
    if(m_bus < 0)
    {
        std::cerr << "Failed to acquire I2C Bus 1, check if its enabled in interface options";
        return -1;
    }

    return 0;
}

void I2CBus::shutdown()
{
    close(m_bus);
}

I2CDevice I2CBus::createDevice(unsigned int address)
{
    I2CDevice device;
    device.address = address;
    return device;
}

int I2CBus::writeBytes(I2CDevice &device, uint8_t *data, unsigned int size)
{
    if(device != *m_currentDevice)
        bindDevice(device);

    if(write(m_bus, data, size) != size)
    {
        std::cerr << "Failed to write device with address 0x" << Utils::decToHex(device.address) << " via I2C Bus 1" << std::endl;
        return -1;
    }

    return 0;
}

int I2CBus::readBytes(I2CDevice &device, uint8_t *data, unsigned int size)
{
    if(device != *m_currentDevice)
        bindDevice(device);

    if(read(m_bus, data, size) != size)
    {
        std::cerr << "Failed to read device with address 0x" << Utils::decToHex(device.address) << " via I2C Bus 1" << std::endl;
        return -1;
    }

    return 0;
}

int I2CBus::bindDevice(I2CDevice &device)
{
    if(ioctl(m_bus, I2C_SLAVE, device.address) < 0)
    {
        std::cerr << "Failed to bind device with address 0x" << Utils::decToHex(device.address) << std::endl;
        return -1;
    }

    m_currentDevice = &device;

    return 0;
}
