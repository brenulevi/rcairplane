#include <RC_Radio.h>
#include <RC_FlightControls.h>
#include <RC_Lighting.h>
#include <printf.h>

enum AircraftState
{
  GROUND,
  AIR_MANUAL,
  AIR_AUTOPILOT
};

AircraftState state = GROUND;

RC_Radio radio_control(7, 8);

unsigned int ailerons_pins[2] = { 22, 23 };
RC_FlightControls flight_controls(ailerons_pins, 24, 25);

unsigned int strobe_pins[2] = { 26, 27 };
unsigned int collision_pins[2] = { 30, 31 };
RC_Lighting lighting(strobe_pins, 28, 29, collision_pins);

void setup() {
  Serial.begin(9600);
  printf_begin();
  Serial.println("Starting aircraft...");

  radio_control.setup();

  flight_controls.setup();

  lighting.setup();
  lighting.set_strobe(true);
  lighting.set_nav(true);
  lighting.set_collision(true);
}

void loop() {
  unsigned long current_millis = millis();

  radio_control.peek();

  // RC_Data& radio_control_data = radio_control.get_data();
  
  lighting.loop(current_millis);
}
