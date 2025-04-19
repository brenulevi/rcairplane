#pragma once

#include <cstdint>

#include "i2c/i2cdevice.h"

#define ADS1115_CONVERSION_REGISTER         0b00
#define ADS1115_CONFIG_REGISTER             0b01

#define ADS1115_CONFIG_MUX_AIN0_AIN1        0b000
#define ADS1115_CONFIG_MUX_AIN0_AIN3        0b001
#define ADS1115_CONFIG_MUX_AIN1_AIN1        0b010
#define ADS1115_CONFIG_MUX_AIN2_AIN1        0b011
#define ADS1115_CONFIG_MUX_AIN0_GND         0b100
#define ADS1115_CONFIG_MUX_AIN1_GND         0b101
#define ADS1115_CONFIG_MUX_AIN2_GND         0b110
#define ADS1115_CONFIG_MUX_AIN3_GND         0b111

#define ADS1115_CONFIG_PGA_6144V            0b000
#define ADS1115_CONFIG_PGA_4096V            0b001
#define ADS1115_CONFIG_PGA_2048V            0b010
#define ADS1115_CONFIG_PGA_1024V            0b011
#define ADS1115_CONFIG_PGA_0512V            0b100
#define ADS1115_CONFIG_PGA_0256V            0b101

#define ADS1115_CONFIG_MODE_CONTINUOUS      0b0
#define ADS1115_CONFIG_MODE_SINGLESHOT      0b1

#define ADS1115_CONFIG_DATARATE_8SPS        0b000
#define ADS1115_CONFIG_DATARATE_16SPS       0b001
#define ADS1115_CONFIG_DATARATE_32SPS       0b010
#define ADS1115_CONFIG_DATARATE_64SPS       0b011
#define ADS1115_CONFIG_DATARATE_128SPS      0b100
#define ADS1115_CONFIG_DATARATE_250SPS      0b101
#define ADS1115_CONFIG_DATARATE_475SPS      0b110
#define ADS1115_CONFIG_DATARATE_860SPS      0b111

#define ADS1115_CONFIG_COMPARATOR_TRADITIONAL       0b0
#define ADS1115_CONFIG_COMPARATOR_WINDOW            0b1

#define ADS1115_CONFIG_COMPARATOR_POLARITY_LOW      0b0
#define ADS1115_CONFIG_COMPARATOR_POLARITY_HIGH     0b1

#define ADS1115_CONFIG_COMPARATOR_LATCHING_OFF      0b0
#define ADS1115_CONFIG_COMPARATOR_LATCHING_ON       0b0

#define ADS1115_CONFIG_COMPARATOR_QUEUE_ONE         0b00
#define ADS1115_CONFIG_COMPARATOR_QUEUE_TWO         0b01
#define ADS1115_CONFIG_COMPARATOR_QUEUE_FOUR        0b10
#define ADS1115_CONFIG_COMPARATOR_DISABLE           0b11


struct ADS1115Config
{
    uint8_t MUX;
    uint8_t PGA;
    uint8_t MODE;
    uint8_t DATARATE;
    uint8_t COMP_MODE;
    uint8_t COMP_POLARITY;
    uint8_t COMP_LATCHING;
    uint8_t COMP_QUEUE_DISABLE;
};

class ADS1115
{
public:
    ADS1115(unsigned int address);

    void setMUX(uint8_t mux);
    void setPGA(uint8_t pga);
    void setMode(uint8_t mode);
    void setDataRate(uint8_t datarate);

    /**
     * Start conversion when in SS mode.
     * Period to wait finish conversion depends of datarate but using 128SPS estimate 8ms
     */
    void startConversion();

    int16_t readValue(); 
    
private:
    void sendConfig(bool startingConversion);

private:
    ADS1115Config m_config;
    I2CDevice m_device;
};