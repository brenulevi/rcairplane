#include <RF24/RF24.h>
#include <signal.h>

#include "raspgpio.h"
#include "modules/servo.h"
#include "math/math.h"

#define RADIO_ADDRESS 0xFFFFA

struct RadioPacket
{
    float joy1_x;    // 4
    float joy1_y;    // 4
    // float joy2_x;    // 4
    // float joy2_y;    // 4
    // float pot;       // 4
};

bool isRunning = true;

void shutdown(int signal) { isRunning = false; }

int main()
{
    std::cout << "Hello Plane!!!\n";

    RASPGPIO::init();

    RF24 radio(25, 0);
    RadioPacket data;

    Servo aileron(17);
    Servo elevator(27);
    Servo rudder(22);

    elevator.setRange(500, 1800);

    if (!radio.begin())
    {
        std::cerr << "Failed to initialize radio!!\n";
        return 1;
    }

    if (!radio.isChipConnected())
    {
        std::cerr << "Radio chip isn't connected\n";
        return 1;
    }

    radio.setChannel(55);
    radio.setPALevel(RF24_PA_HIGH);
    radio.setDataRate(RF24_250KBPS);

    radio.openReadingPipe(0, RADIO_ADDRESS);
    radio.startListening();

    aileron.pulse(1500);
    elevator.pulse(1500);
    rudder.pulse(1500);

    while (isRunning)
    {
        signal(SIGINT, &shutdown);

        if (radio.available())
        {
            radio.read(&data, sizeof(data));

            rudder.pulse((int)Math::map(data.joy1_x, 0.0f, 1.0f, 500.0f, 2500.0f));
            elevator.pulse((int)Math::map(data.joy1_y, 0.0f, 1.0f, 500.0f, 2500.0f));
        }
    }

    aileron.pulse(1500);
    elevator.pulse(1500);
    rudder.pulse(1500);

    std::cout << "Shutdowing...\n";

    RASPGPIO::shutdown();

    return 0;
}