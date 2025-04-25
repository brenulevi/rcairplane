#include "Radio.h"

#include <Arduino.h>

Radio::Radio(uint8_t cePin, uint8_t csnPin)
    : m_rf24(cePin, csnPin)
{
}

void Radio::setup()
{
    if (!m_rf24.begin() || !m_rf24.isChipConnected())
        throw std::runtime_error("Failed to communicate with nRF24L01+, check wiring");

    m_rf24.setPALevel(RF24_PA_HIGH);
    m_rf24.setDataRate(RF24_250KBPS);
    m_rf24.setChannel(RADIO_CHANNEL);

    m_rf24.openReadingPipe(0, RADIO_ADDRESS);
    m_rf24.startListening();
}
