#pragma once

#include <Arduino.h>
#include <Servo.h>

class FlightControls
{
public:
  FlightControls(unsigned int* ailerons_pins, unsigned int elevator_pin, unsigned int rudder_pin)
    : _ailerons_pins(ailerons_pins), _elevator_pin(elevator_pin), _rudder_pin(rudder_pin)
  {
  }

  void setup()
  {
    _left_aileron.attach(_ailerons_pins[0]);
    _right_aileron.attach(_ailerons_pins[1]);
    _elevator.attach(_elevator_pin);
    _rudder.attach(_rudder_pin);

    // reset surface positions
    _left_aileron.write(0);
    _right_aileron.write(0);
    _elevator.write(0);
    _rudder.write(0);
  }

  void loop(unsigned long current_millis)
  {
    if(current_millis - _last_millis > 1000 && _state )
    {
      _left_aileron.write(180);
      _right_aileron.write(180);
      _elevator.write(180);
      _rudder.write(180);
      _last_millis = current_millis;
      _state = false;
    }
    if(current_millis - _last_millis > 1000 & !_state)
    {
      _left_aileron.write(0);
      _right_aileron.write(0);
      _elevator.write(0);
      _rudder.write(0);
      _last_millis = current_millis;
      _state = true;
    }
  }

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