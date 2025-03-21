#include "RC_Radio.h"

const byte RC_Radio::_address[6] = "00001";

RC_Radio::RC_Radio(unsigned int ce_pin, unsigned int csn_pin)
    : _rf24(ce_pin, csn_pin)
{
}

void RC_Radio::setup()
{
    _rf24.begin();

    _rf24.setPALevel(RF24_PA_HIGH);
    _rf24.setDataRate(RF24_250KBPS);
    _rf24.openReadingPipe(0, _address);
}

void RC_Radio::test_radio()
{
    _rf24.printPrettyDetails();

    Serial.print("Is radio valid: ");
    Serial.println(_rf24.isValid());

    Serial.print("Is chip connected: ");
    Serial.println(_rf24.isChipConnected());

    Serial.print("Is p variant: ");
    Serial.println(_rf24.isPVariant());
}

void RC_Radio::peek()
{
    if(_rf24.available())
    {
        _rf24.read(&_data, sizeof(RC_Data));
    }
}

RC_Data &RC_Radio::get_data()
{
    return _data;
}
