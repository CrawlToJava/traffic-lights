#include "TrafficLighter.h"
#include <Arduino.h>

void TrafficLighter::redLight(int redLight, int yellowLight, int greenLight)
{
    PORTB &= ~((1 << yellowLight) | (1 << greenLight));
    PORTB |= (1 << redLight);
}

void TrafficLighter::yellowLight(int yellowLight, int redLight, int greenLight)
{
    PORTB &= ~((1 << redLight) | (1 << greenLight));
    PORTB |= (1 << yellowLight);
}

void TrafficLighter::greenLight(int greenLight, int yellowLight, int redLight)
{
    PORTB &= ~((1 << redLight) | (1 << yellowLight));
    PORTB |= (1 << greenLight);
}

void TrafficLighter::noLight(int greenLight, int yellowLight, int redLight)
{
    PORTB &= ~((1 << redLight) | (1 << yellowLight) | (1 << greenLight));
}
