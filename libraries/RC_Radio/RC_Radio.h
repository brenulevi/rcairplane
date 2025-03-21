#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

struct RC_Data
{
    byte left_joystick_x;
    byte left_joystick_y;
};

class RC_Radio
{
public:
    RC_Radio(unsigned int ce_pin, unsigned int csn_pin);

    void setup();
    void test_radio();
    void peek();

    RC_Data& get_data();

private:
    RF24 _rf24;

    RC_Data _data;

    static const byte _address[6];
};