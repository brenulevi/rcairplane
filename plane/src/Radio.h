#pragma once

#include <RF24.h>

#define RADIO_CHANNEL 34
#define RADIO_ADDRESS 0xFFFFA

class Radio
{
public:
    struct Packet
    {
        uint8_t joy1_x;
        uint8_t joy1_y;
        uint8_t joy2_x;
        uint8_t joy2_y;
        uint8_t pot;
    };

public:
    Radio(uint8_t cePin, uint8_t csnPin);

    void setup();

    void peek();

    inline Packet& getData() { return m_data; }

private:
    RF24 m_rf24;
    Packet m_data;
};