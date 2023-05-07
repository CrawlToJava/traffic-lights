#include <Arduino.h>
#include "entity/TrafficLighter.h"

#define CAR_RED_LIGHT 5
#define CAR_YELLOW_LIGHT 4
#define CAR_GREEN_LIGHT 3

#define PERSON_RED_LIGHT 2
#define PERSON_YELLOW_LIGHT 1
#define PERSON_GREEN_LIGHT 0

unsigned long timer = 0;
unsigned long stopTimer = 0;
bool flag;
int countStopValue = 0;
int countValue = 0;
TrafficLighter carTrafficLighter;
TrafficLighter personTrafficLighter;

void timerFunc(unsigned long *timer, unsigned long delay, int *countValue)
{
  if (millis() - *timer >= delay)
  {
    *timer = millis();
    *countValue = *countValue + 1;
  }
}

void setup()
{
  Serial.begin(9600);
  DDRB = 0b111111;
  DDRC = 0b000000;
  PORTC |= (1 << 0);
}

void loop()
{
  if (0 == (PINC & (1 << 0)))
  {
    flag = 1;
  }
  if (flag == 1)
  {
    timerFunc(&stopTimer, 500, &countStopValue);
    if (countStopValue <= 6)
    {
      carTrafficLighter.redLight(CAR_RED_LIGHT, CAR_YELLOW_LIGHT, CAR_GREEN_LIGHT);
      personTrafficLighter.greenLight(PERSON_GREEN_LIGHT, PERSON_YELLOW_LIGHT, PERSON_RED_LIGHT);
    }

    if (countStopValue > 6)
    {
      flag = 0;
      countStopValue = 0;
      countValue = 17;
    }
  }
  else
  {
    timerFunc(&timer, 500, &countValue);
    if (countValue == 0 && countValue <= 6)
    {
      carTrafficLighter.greenLight(CAR_GREEN_LIGHT, CAR_YELLOW_LIGHT, CAR_RED_LIGHT);
      personTrafficLighter.redLight(PERSON_RED_LIGHT, PERSON_YELLOW_LIGHT, PERSON_GREEN_LIGHT);
    }
    if (countValue > 6 && countValue <= 10)
    {
      carTrafficLighter.yellowLight(CAR_YELLOW_LIGHT, CAR_RED_LIGHT, CAR_GREEN_LIGHT);
      personTrafficLighter.yellowLight(PERSON_YELLOW_LIGHT, PERSON_RED_LIGHT, PERSON_GREEN_LIGHT);
    }
    if (countValue > 10 && countValue <= 16)
    {
      carTrafficLighter.redLight(CAR_RED_LIGHT, CAR_YELLOW_LIGHT, CAR_GREEN_LIGHT);
      personTrafficLighter.greenLight(PERSON_GREEN_LIGHT, PERSON_YELLOW_LIGHT, PERSON_RED_LIGHT);
    }
    if (countValue > 16 && countValue < 18)
    {
      carTrafficLighter.yellowLight(CAR_YELLOW_LIGHT, CAR_RED_LIGHT, CAR_GREEN_LIGHT);
      personTrafficLighter.noLight(PERSON_GREEN_LIGHT, PERSON_YELLOW_LIGHT, PERSON_RED_LIGHT);
    }
    if (countValue > 17 && countValue < 19)
    {
      carTrafficLighter.yellowLight(CAR_YELLOW_LIGHT, CAR_RED_LIGHT, CAR_GREEN_LIGHT);
      personTrafficLighter.greenLight(PERSON_GREEN_LIGHT, PERSON_YELLOW_LIGHT, PERSON_RED_LIGHT);
    }
    if (countValue == 19)
    {
      carTrafficLighter.yellowLight(CAR_YELLOW_LIGHT, CAR_RED_LIGHT, CAR_GREEN_LIGHT);
      personTrafficLighter.noLight(PERSON_GREEN_LIGHT, PERSON_YELLOW_LIGHT, PERSON_RED_LIGHT);
    }
    if (countValue == 20)
    {
      carTrafficLighter.yellowLight(CAR_YELLOW_LIGHT, CAR_RED_LIGHT, CAR_GREEN_LIGHT);
      personTrafficLighter.greenLight(PERSON_GREEN_LIGHT, PERSON_YELLOW_LIGHT, PERSON_RED_LIGHT);
    }
    if (countValue == 21)
    {
      carTrafficLighter.yellowLight(CAR_YELLOW_LIGHT, CAR_RED_LIGHT, CAR_GREEN_LIGHT);
      personTrafficLighter.noLight(PERSON_GREEN_LIGHT, PERSON_YELLOW_LIGHT, PERSON_RED_LIGHT);
    }
    if (countValue > 21)
    {
      countValue = 0;
    }
  }
}