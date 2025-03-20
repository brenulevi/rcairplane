#include "RC_FlightControls.h"

RC_FlightControls::RC_FlightControls(unsigned int* ailerons_pins, unsigned int elevator_pin, unsigned int rudder_pin)
    :   _ailerons_pins(ailerons_pins), _elevator_pin(elevator_pin), _rudder_pin(rudder_pin)
{
}

void RC_FlightControls::setup()
{
    _left_aileron.attach(_ailerons_pins[0]);
    _right_aileron.attach(_ailerons_pins[1]);
    _elevator.attach(_elevator_pin);
    _rudder.attach(_rudder_pin);

    // reset surface positions
    _left_aileron.write(90);
    _right_aileron.write(90);
    _elevator.write(90);
    _rudder.write(90);
}

void RC_FlightControls::move_left_aileron(unsigned int degrees)
{
    _left_aileron.write(degrees);
}

void RC_FlightControls::move_right_aileron(unsigned int degrees)
{
    _right_aileron.write(degrees);
}

void RC_FlightControls::move_elevator(unsigned int degrees)
{
    _elevator.write(degrees);
}

void RC_FlightControls::move_rudder(unsigned int degrees)
{
    _rudder.write(degrees);
}

unsigned int RC_FlightControls::get_left_aileron_position()
{
    return _left_aileron.read();
}

unsigned int RC_FlightControls::get_right_aileron_position()
{
    return _right_aileron.read();
}

unsigned int RC_FlightControls::get_elevator_position()
{
    return _elevator.read();
}

unsigned int RC_FlightControls::get_rudder_position()
{
    return _rudder.read();
}
