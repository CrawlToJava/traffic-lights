#include <Arduino.h>
#include "entity/TrafficLighter.h"
#include "entity/SemiSegmentDisplay.h"

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

int nums[11] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111, 0b01000000};

TrafficLighter carTrafficLighter;
TrafficLighter personTrafficLighter;
SemiSegmentDisplay semiSegmentDisplay;

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
  DDRD = 0b11111111;
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
    if (countStopValue == 0 && countStopValue <= 8)
    {
      carTrafficLighter.redLight(CAR_RED_LIGHT, CAR_YELLOW_LIGHT, CAR_GREEN_LIGHT);
      personTrafficLighter.greenLight(PERSON_GREEN_LIGHT, PERSON_YELLOW_LIGHT, PERSON_RED_LIGHT);
    }
    if (countStopValue >= 0 && countStopValue <= 2)
    {
      semiSegmentDisplay.displayNumber(nums, 7);
    }
    if (countStopValue > 2 && countStopValue <= 4)
    {
      semiSegmentDisplay.displayNumber(nums, 6);
    }
    if (countStopValue > 4 && countStopValue <= 6)
    {
      semiSegmentDisplay.displayNumber(nums, 5);
    }
    if (countStopValue > 6 && countStopValue < 8)
    {
      semiSegmentDisplay.displayNumber(nums, 4);
    }
    if (countStopValue > 8)
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
      semiSegmentDisplay.displayNumber(nums, 10);
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

    if (countValue >= 10 && countValue <= 12)
    {
      semiSegmentDisplay.displayNumber(nums, 7);
    }
    if (countValue > 12 && countValue <= 14)
    {
      semiSegmentDisplay.displayNumber(nums, 6);
    }
    if (countValue > 14 && countValue <= 16)
    {
      semiSegmentDisplay.displayNumber(nums, 5);
    }
    if (countValue > 16 && countValue < 18)
    {
      semiSegmentDisplay.displayNumber(nums, 4);
    }
    if (countValue > 17 && countValue < 19)
    {
      semiSegmentDisplay.displayNumber(nums, 3);
    }
    if (countValue == 19)
    {
      semiSegmentDisplay.displayNumber(nums, 2);
    }
    if (countValue == 20)
    {
      semiSegmentDisplay.displayNumber(nums, 1);
    }
    if (countValue == 21)
    {
      semiSegmentDisplay.displayNumber(nums, 0);
    }
  }
}