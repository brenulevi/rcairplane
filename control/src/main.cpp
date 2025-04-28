#include <Arduino.h>
#include <RF24.h>

#define RADIO_CHANNEL 34
#define RADIO_ADDRESS 0xFFFFA

RF24 radio(9, 10);

struct Packet
{
    uint8_t joy1_x;
    uint8_t joy1_y;
    uint8_t joy2_x;
    uint8_t joy2_y;
    uint8_t pot;
};

bool setupSuccessful = true;

void setup()
{
    Serial.begin(9600);

    if (!radio.begin() || !radio.isChipConnected())
    {
        Serial.println("Couldn't communication with radio, check wiring");
        setupSuccessful = false;
        return;
    }

    radio.setPALevel(RF24_PA_HIGH);
    radio.setDataRate(RF24_250KBPS);
    radio.setChannel(RADIO_CHANNEL);
    radio.setCRCLength(RF24_CRC_16);

    radio.openWritingPipe(RADIO_ADDRESS);
    radio.stopListening();
}

void loop()
{
    Packet data;
    data.joy1_x = map(analogRead(A0), 0, 1023, 0, 255);
    data.joy1_y = map(analogRead(A1), 0, 1023, 0, 255);
    data.joy2_x = map(analogRead(A2), 0, 1023, 0, 255);
    data.joy2_y = map(analogRead(A3), 0, 1023, 0, 255);
    data.pot = map(analogRead(A4), 0, 1023, 0, 255);

    radio.write(&data, sizeof(data));
}