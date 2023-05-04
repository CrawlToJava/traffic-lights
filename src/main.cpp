#include <Arduino.h>

unsigned long timer = 0;
unsigned long stopTimer = 0;
bool flag;
int countStopValue = 0;
int countValue = 0;

void carRedLight()
{
  PORTB &= ~((1 << 4) | (1 << 3));
  PORTB |= (1 << 5);
}

void carYellowLight()
{
  PORTB &= ~((1 << 5) | (1 << 3));
  PORTB |= (1 << 4);
}

void carGreenLight()
{
  PORTB &= ~((1 << 5) | (1 << 4));
  PORTB |= (1 << 3);
}

void carNoLight()
{
  PORTB &= ~((1 << 5) | (1 << 4) | (1 << 3));
}

void personRedLight()
{
  PORTB &= ~((1 << 1) | (1 << 0));
  PORTB |= (1 << 2);
}

void personYellowLight()
{
  PORTB &= ~((1 << 0) | (1 << 2));
  PORTB |= (1 << 1);
}

void personGreenLight()
{
  PORTB &= ~((1 << 1) | (1 << 2));
  PORTB |= (1 << 0);
}

void personNoLight()
{
  PORTB &= ~((1 << 1) | (1 << 2) | (1 << 0));
}

void redLight()
{
  PORTB &= ~((1 << 4) | (1 << 3) | (1 << 1) | (1 << 0));
  PORTB |= (1 << 5) | (1 << 2);
}

void yellowLight()
{
  PORTB &= ~((1 << 5) | (1 << 3) | (1 << 2) | (1 << 0));
  PORTB |= (1 << 4) | (1 << 1);
}

void greenLight()
{
  PORTB &= ~((1 << 5) | (1 << 4) | (1 << 2) | (1 << 1));
  PORTB |= (1 << 0) | (1 << 3);
}

void noLight()
{
  PORTB &= ~((1 << 4) | (1 << 3) | (1 << 1) | (1 << 0) | (1 << 5) | (1 << 2));
}

void pederstianModeFunc()
{
  PORTB &= ~((1 << 0) | (1 << 1) | (1 << 4) | (1 << 5));
  PORTB |= (1 << 3) | (1 << 2);
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
    if (millis() - stopTimer >= 500)
    {
      stopTimer = millis();
      countStopValue++;
    }
    if (countStopValue == 2 && countStopValue <= 6)
    {
      pederstianModeFunc();
    }
    if (countStopValue == 7)
    {
      PORTB &= ~((1 << 5) | (1 << 4) | (1 << 2) | (1 << 0) | (1 << 3));
      PORTB |= (1 << 1);
    }
    if (countStopValue == 8)
    {
      PORTB &= ~((1 << 5) | (1 << 4) | (1 << 2) | (1 << 0));
      PORTB |= (1 << 3);
    }
    if (countValue == 9)
    {
      PORTB &= ~((1 << 5) | (1 << 4) | (1 << 2) | (1 << 0) | (1 << 3));
      PORTB |= (1 << 1);
    }
    if (countStopValue == 10)
    {
      PORTB &= ~((1 << 5) | (1 << 4) | (1 << 2) | (1 << 0));
      PORTB |= (1 << 3);
    }
    if (countStopValue == 11)
    {
      PORTB &= ~((1 << 5) | (1 << 4) | (1 << 2) | (1 << 0) | (1 << 3));
      PORTB |= (1 << 1);
    }
    if (countStopValue == 12)
    {
      PORTB &= ~((1 << 5) | (1 << 4) | (1 << 2) | (1 << 0));
      PORTB |= (1 << 3);
    }
    if (countValue == 13)
    {
      PORTB &= ~((1 << 5) | (1 << 4) | (1 << 2) | (1 << 0) | (1 << 3));
      PORTB |= (1 << 1);
    }
    if (countStopValue == 14)
    {
      PORTB &= ~((1 << 5) | (1 << 4) | (1 << 2) | (1 << 0));
      PORTB |= (1 << 3);
    }
    if (countStopValue > 14)
    {
      flag = 0;
      countStopValue = 0;
      countValue = 9;
    }
  }
  else
  {
    if (millis() - timer >= 500)
    {
      timer = millis();
      countValue++;
    }
    if (countValue == 0 && countValue <= 4)
    {
      carGreenLight();
      personRedLight();
    }
    if (countValue == 5)
    {
      personNoLight();
      carNoLight();
    }
    if (countValue == 6)
    {
      carGreenLight();
      personRedLight();
    }
    if (countValue == 7)
    {
      personNoLight();
      carNoLight();
    }
    if (countValue == 8)
    {
      carGreenLight();
      personRedLight();
    }
    if (countValue >= 9 && countValue <= 10)
    {
      carYellowLight();
      personYellowLight();
    }
    if (countValue > 10 && countValue <= 14)
    {
      carRedLight();
      personGreenLight();
    }
    if (countValue >= 15 && countValue <= 16)
    {
      carYellowLight();
      personYellowLight();
    }
    if (countValue > 16)
    {
      countValue = 0;
    }
  }
}