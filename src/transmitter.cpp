#include <RF24/RF24.h>
#include <iostream>
#include <unistd.h>

RF24 radio(22, 0);

const uint8_t address[6] = "00001";

int main()
{
    std::cout << radio.begin() << std::endl;
    std::cout << radio.isChipConnected() << std::endl;
    std::cout << radio.isValid() << std::endl;
}