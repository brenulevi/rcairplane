#include "ads1115.h"

#include "i2c/i2cbus.h"

ADS1115::ADS1115(unsigned int address)
    : m_device(I2CBus::createDevice(address))
{
    m_config.MUX = ADS1115_CONFIG_MUX_AIN0_AIN1;
    m_config.PGA = ADS1115_CONFIG_PGA_2048V;
    m_config.MODE = ADS1115_CONFIG_MODE_SINGLESHOT;
    m_config.DATARATE = ADS1115_CONFIG_DATARATE_128SPS;
    m_config.COMP_MODE = ADS1115_CONFIG_COMPARATOR_TRADITIONAL;
    m_config.COMP_POLARITY = ADS1115_CONFIG_COMPARATOR_POLARITY_LOW;
    m_config.COMP_LATCHING = ADS1115_CONFIG_COMPARATOR_LATCHING_OFF;
    m_config.COMP_QUEUE_DISABLE = ADS1115_CONFIG_COMPARATOR_DISABLE;

    sendConfig(false);
}

void ADS1115::setMUX(uint8_t mux)
{
    m_config.MUX = mux;
    sendConfig(false);
}

void ADS1115::setPGA(uint8_t pga)
{
    m_config.PGA = pga;
    sendConfig(false);
}

void ADS1115::setMode(uint8_t mode)
{
    m_config.MODE = mode;
    sendConfig(false);
}

void ADS1115::setDataRate(uint8_t datarate)
{
    m_config.DATARATE = datarate;
    sendConfig(false);
}

void ADS1115::sendConfig(bool startingConversion)
{
    uint16_t reg;
    if(startingConversion)
        reg |= (1 << 15);
    else
        reg |= (0 << 15);
    reg |= (m_config.MUX & 0b111) << 12;
    reg |= (m_config.PGA & 0b111) << 9;
    reg |= (m_config.MODE & 0b1 << 8);
    reg |= (m_config.DATARATE & 0b111) << 5;
    reg |= (m_config.COMP_MODE & 0b1) << 4;
    reg |= (m_config.COMP_POLARITY & 0b1) << 3;
    reg |= (m_config.COMP_LATCHING & 0b1) << 2;
    reg |= (m_config.COMP_QUEUE_DISABLE & 0b11) << 0;

    uint8_t buffer[3];
    buffer[0] = ADS1115_CONFIG_REGISTER;
    buffer[1] = (reg >> 8) & 0xFF;
    buffer[2] = reg & 0xFF;

    I2CBus::writeBytes(m_device, buffer, 3);
}

void ADS1115::startConversion()
{
    sendConfig(true);
}

int16_t ADS1115::readValue()
{
    uint8_t data[2];
    I2CBus::readBytes(m_device, data, 2);
    int16_t value = (data[0] << 8) | data[1];
    return value;
}
