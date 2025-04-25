#include <Arduino.h>

#include "Radio.h"
#include "Engine.h"
#include "FlightControls.h"
#include "Lighting.h"

Radio radio(17, 5);
FlightControls flightControls(14, 12, 13);
Engine engine(27);
Lighting lighting(26, 25);

bool isRunning = true;

void setup()
{
  Serial.begin(115200);
  
  Serial.println("Setting up plane...");
  
  try
  {
    // start radio
    radio.setup();

    // start flight controls and reset surface position
    flightControls.setup();
    flightControls.resetSurfaces();

    // start engine and calibrate
    engine.setup();
    engine.calibrate();
    engine.turnOn();

    // start lights
    lighting.setup();
    lighting.setNav(true);
    lighting.setStrobe(true);
  }
  catch (const std::exception &e)
  {
    Serial.println(e.what());
    isRunning = false;
  }
}

void loop()
{
  uint64_t currentMillis = millis();

  if (!isRunning)
    return;

  // update lights
  lighting.tick(currentMillis);

  // fill packet with data received
  radio.peek();

  // get packet and treat data
  auto& radioData = radio.getData();

  // map data from 0/255 to -1.0/1.0  (I dont know if I'll maintain 0/255 because of precision)
  float aileronMovement = (radioData.joy1_x / (255.0f / 2.0f)) - 1.0f;
  float elevatorMovement = (radioData.joy1_y / (255.0f / 2.0f)) - 1.0f;
  float rudderMovement = (radioData.joy2_x / (255.0f / 2.0f)) - 1.0f;

  // map pot data to throttle between 0.0 and 1.0
  float throttle = (radioData.pot / 255.0f);

  flightControls.setAileron(aileronMovement);
  flightControls.setElevator(elevatorMovement);
  flightControls.setRudder(rudderMovement);

  engine.setThrottle(throttle);
}