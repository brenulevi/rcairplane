#include <Arduino.h>

#include "Radio.h"
#include "Engine.h"
#include "FlightControls.h"

Radio radio(0, 0);
FlightControls flightControls(0, 0, 0);
Engine engine(0);

bool isRunning = true;

void setup()
{
  Serial.begin(115200);

  Serial.println("Setting up plane...");
  
  try
  {
    // start and configure radio
    radio.setup();

    // start flight controls and reset surface position
    flightControls.setup();
    flightControls.resetSurfaces();

    // start engine and calibrate
    engine.setup();
    engine.calibrate();
    engine.turnOn();
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

  // fill packet with data received
  radio.peek();

  // get packet and treat data
  auto& radioData = radio.getData();

  // map data from 0/255 to -1.0/1.0  (I dont know if I'll maintain 0/255 because of precision)
  float aileronMovement = (radioData.joy1_x / (255.0f / 2.0f)) - 1.0f;
  float elevatorMovement = (radioData.joy1_y / (255.0f / 2.0f)) - 1.0f;
  float rudderMovement = (radioData.joy2_x / (255.0f / 2.0f)) - 1.0f;

  float throttle = (radioData.pot / 255.0f);

  flightControls.setAileron(aileronMovement);
  flightControls.setElevator(elevatorMovement);
  flightControls.setRudder(rudderMovement);

  engine.setThrottle(throttle);
}