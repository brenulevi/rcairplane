#include "modules/lighting.h"

unsigned int strobe_pins[2] = { 8, 9 };
unsigned int collision_pins[2] = { 12, 13 };
Lighting lighting(strobe_pins, 10, 11, collision_pins);

void setup() {
  lighting.setup();
  lighting.set_strobe(true);
  lighting.set_nav(true);
  lighting.set_collision(true);
}

void loop() {
  unsigned long current_millis = millis();

  lighting.loop(current_millis);
}
