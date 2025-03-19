#pragma once

#include <Arduino.h>

class Lighting
{
public:
  Lighting(unsigned int* strobe_pins, unsigned int left_nav_pin, unsigned int right_nav_pin, unsigned int* collision_pins)
    : _strobe_pins(strobe_pins), _left_nav_pin(left_nav_pin), _right_nav_pin(right_nav_pin), _collision_pins(collision_pins),
      _strobe_enabled(false), _nav_enabled(false), _collision_enabled(false),
      _strobe_millis(0), _collision_millis(0),
      _strobe_wait_interval(1000), _strobe_blink_interval(75), _strobe_step(0),
      _collision_interval(1000), _collision_duration(100), _is_collision_high(false)
  {
  }

  void setup()
  {
    pinMode(_strobe_pins[0], OUTPUT);
    pinMode(_strobe_pins[1], OUTPUT);
    pinMode(_left_nav_pin, OUTPUT);
    pinMode(_right_nav_pin, OUTPUT);
    pinMode(_collision_pins[0], OUTPUT);
    pinMode(_collision_pins[1], OUTPUT);
  }

  void loop(unsigned long current_millis)
  {
    if(_strobe_enabled)
      strobe_loop(current_millis);

    if(_nav_enabled)
      nav_loop();

    if(_collision_enabled)
      collision_loop(current_millis);
  }

  void set_strobe(bool enabled) { _strobe_enabled = enabled; }
  void set_nav(bool enabled) { _nav_enabled = enabled; }
  void set_collision(bool enabled) { _collision_enabled = enabled; }

  void set_strobe_wait_interval(unsigned int interval) { _strobe_wait_interval = interval; }
  void set_strobe_blink_interval(unsigned int interval) { _strobe_blink_interval = interval; }

  void set_collision_interval(unsigned int interval) { _collision_interval = interval; }
  void set_collision_duration(unsigned int duration) { _collision_duration = duration; }

private:
  void strobe_loop(unsigned long current_millis)
  {
    if(current_millis - _strobe_millis > _strobe_wait_interval && _strobe_step == 0)
    {
      digitalWrite(_strobe_pins[0], HIGH);
      digitalWrite(_strobe_pins[1], HIGH);
      _strobe_step++;
      _strobe_millis = current_millis;
    }
    else if(current_millis - _strobe_millis > _strobe_blink_interval && _strobe_step == 1)
    {
      digitalWrite(_strobe_pins[0], LOW);
      digitalWrite(_strobe_pins[1], LOW);
      _strobe_step++;
      _strobe_millis = current_millis;
    }
    else if(current_millis - _strobe_millis > _strobe_blink_interval && _strobe_step == 2)
    {
      digitalWrite(_strobe_pins[0], HIGH);
      digitalWrite(_strobe_pins[1], HIGH);
      _strobe_step++;
      _strobe_millis = current_millis;
    }
    else if(current_millis - _strobe_millis > _strobe_blink_interval && _strobe_step == 3)
    {
      digitalWrite(_strobe_pins[0], LOW);
      digitalWrite(_strobe_pins[1], LOW);
      _strobe_step = 0;
      _strobe_millis = current_millis;
    }
  }

  void nav_loop()
  {
    digitalWrite(_left_nav_pin, HIGH);
    digitalWrite(_right_nav_pin, HIGH);
  }

  void collision_loop(unsigned long current_millis)
  {
    if(current_millis - _collision_millis > _collision_interval && !_is_collision_high)
    {
      digitalWrite(_collision_pins[0], HIGH);
      digitalWrite(_collision_pins[1], HIGH);
      _is_collision_high = true;
      _collision_millis = current_millis;
    }
    else if (current_millis - _collision_millis > _collision_duration && _is_collision_high)
    {
      digitalWrite(_collision_pins[0], LOW);
      digitalWrite(_collision_pins[1], LOW);
      _is_collision_high = false;
      _collision_millis = current_millis;
    }
  }

private:
  unsigned int* _strobe_pins;
  unsigned int _left_nav_pin;
  unsigned int _right_nav_pin;
  unsigned int* _collision_pins;

  bool _strobe_enabled;
  bool _nav_enabled;
  bool _collision_enabled;

  unsigned int _strobe_step;
  unsigned int _strobe_wait_interval;
  unsigned int _strobe_blink_interval;

  unsigned int _collision_interval;
  unsigned int _collision_duration;
  bool _is_collision_high;

  unsigned long _strobe_millis;
  unsigned long _collision_millis;

};