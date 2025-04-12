#include <RF24/RF24.h>
#include <iostream>
#include <unistd.h>

RF24 radio(22, 0);

const uint8_t address[6] = "00001";

int main()
{
    if(!radio.begin())
    {
        std::cerr << "Failed to initialize nRF24L01" << std::endl;
        return 1;
    }

    if(!radio.isChipConnected())
    {
        std::cerr << "Chip isn't connect to SPI bus correctly" << std::endl;
        return 1;
    }

    radio.setPALevel(RF24_PA_HIGH);
    radio.setDataRate(RF24_250KBPS);
    radio.setChannel(45);

    radio.openReadingPipe(0, address);
    radio.startListening();

    while(true)
    {
        if(radio.available())
        {
            char msg[32];
            radio.read(&msg, sizeof(msg));
            std::cout << msg << std::endl;
        }

        usleep(1000);
    }

    return 0;
}