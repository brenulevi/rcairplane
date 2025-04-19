#pragma onces

class Servo
{
public:
    Servo(uint8_t pin);

    void moveDegrees(uint16_t degrees);
    void movePulseWidth(uint16_t width);

    void setPulseRange(uint16_t min, uint16_t max);

private:
    uint8_t m_pin;
    
    uint16_t m_rangeMin;
    uint16_t m_rangeMax;
};