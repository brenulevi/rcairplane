#include <RC_FlightControls.h>
#include <RC_Lighting.h>

unsigned int ailerons_pins[2] = { 4, 5 };
RC_FlightControls flight_controls(ailerons_pins, 6, 7);

unsigned int strobe_pins[2] = { 8, 9 };
unsigned int collision_pins[2] = { 12, 13 };
RC_Lighting lighting(strobe_pins, 10, 11, collision_pins);

void setup() {

  Serial.begin(9600);
  Serial.println("Starting aircraft...");

  flight_controls.setup();

  lighting.setup();
  lighting.set_strobe(true);
  lighting.set_nav(true);
  lighting.set_collision(true);
}

void loop() {
  unsigned long current_millis = millis();

  flight_controls.move_left_aileron(map(analogRead(A0), 0, 1023, 0, 180));
  
  lighting.loop(current_millis);
}
