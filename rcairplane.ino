#include "modules/flightscontrols.h"
#include "modules/lighting.h"

unsigned int ailerons_pins[2] = { 4, 5 };
FlightControls flight_controls(ailerons_pins, 6, 7);

unsigned int strobe_pins[2] = { 8, 9 };
unsigned int collision_pins[2] = { 12, 13 };
Lighting lighting(strobe_pins, 10, 11, collision_pins);

void setup() {

  flight_controls.setup();

  lighting.setup();
  lighting.set_strobe(true);
  lighting.set_nav(true);
  lighting.set_collision(true);
}

void loop() {
  unsigned long current_millis = millis();

  flight_controls.loop(current_millis);
  lighting.loop(current_millis);
}
