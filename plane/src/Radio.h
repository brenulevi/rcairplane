#pragma once

#include <RF24.h>

#define RADIO_CHANNEL 34
#define RADIO_ADDRESS 0xFFFFA

class Radio
{
public:
    Radio(uint8_t cePin, uint8_t csnPin);

    void setup();

private:
    RF24 m_rf24;
};