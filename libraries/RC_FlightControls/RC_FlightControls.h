#pragma once

#include <Arduino.h>
#include <Servo.h>

class RC_FlightControls
{
public:
  RC_FlightControls(unsigned int* ailerons_pins, unsigned int elevator_pin, unsigned int rudder_pin);

  void setup();
  void loop(unsigned long current_millis);

private:
  unsigned int* _ailerons_pins;
  unsigned int _elevator_pin;
  unsigned int _rudder_pin;

  Servo _left_aileron;
  Servo _right_aileron;
  Servo _elevator;
  Servo _rudder;

  //temp
  unsigned long _last_millis = 0;
  bool _state = false;
};