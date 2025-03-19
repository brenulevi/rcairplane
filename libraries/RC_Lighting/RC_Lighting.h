#pragma once

#include <Arduino.h>

class RC_Lighting
{
public:
  RC_Lighting(unsigned int* strobe_pins, unsigned int left_nav_pin, unsigned int right_nav_pin, unsigned int* collision_pins);

  void setup();
  void loop(unsigned long current_millis);

  void set_strobe(bool enabled);
  void set_nav(bool enabled);
  void set_collision(bool enabled);

  void set_strobe_wait_interval(unsigned int interval);
  void set_strobe_blink_interval(unsigned int interval);

  void set_collision_interval(unsigned int interval);
  void set_collision_duration(unsigned int duration);

private:
  void strobe_loop(unsigned long current_millis);
  void nav_loop();
  void collision_loop(unsigned long current_millis);

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