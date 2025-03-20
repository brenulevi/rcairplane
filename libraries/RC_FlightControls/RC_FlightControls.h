#pragma once

#include <Arduino.h>
#include <Servo.h>

class RC_FlightControls
{
public:
  RC_FlightControls(unsigned int* ailerons_pins, unsigned int elevator_pin, unsigned int rudder_pin);

  void setup();
  
  void move_left_aileron(unsigned int degrees);
  void move_right_aileron(unsigned int degrees);
  void move_elevator(unsigned int degrees);
  void move_rudder(unsigned int degrees);

  unsigned int get_left_aileron_position();
  unsigned int get_right_aileron_position();
  unsigned int get_elevator_position();
  unsigned int get_rudder_position();

private:
  unsigned int* _ailerons_pins;
  unsigned int _elevator_pin;
  unsigned int _rudder_pin;

  Servo _left_aileron;
  Servo _right_aileron;
  Servo _elevator;
  Servo _rudder;
};