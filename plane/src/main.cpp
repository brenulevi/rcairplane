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
    engine.startCalibration();
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

  // initialization was successfull

  if (!engine.isCalibrated())
  {
    engine.tickCalibration(currentMillis);
    return;
  }

  // engine calibrated
}