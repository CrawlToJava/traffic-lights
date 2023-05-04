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
    carRedLight();
    personGreenLight();
    if (countStopValue == 3)
    {
      flag = 0;
      countStopValue = 0;
    }
  }
  else
  {
    if (millis() - timer >= 500)
    {
      timer = millis();
      countValue++;
    }
    if (countValue == 0 && countValue <= 6)
    {
      carGreenLight();
      personRedLight();
    }
    if (countValue == 7 && countValue >= 10)
    {
      carYellowLight();
      personYellowLight();
    }
    if (countValue > 10 && countValue <= 16)
    {
      carRedLight();
      personGreenLight();
    }
    if (countValue == 17)
    {
      carYellowLight();
      personNoLight();
    }
    if (countValue == 18)
    {
      carYellowLight();
      personGreenLight();
    }
    if (countValue == 19)
    {
      carYellowLight();
      personNoLight();
    }
    if (countValue == 20)
    {
      carYellowLight();
      personGreenLight();
    }
    if (countValue > 20)
    {
      countValue = 0;
    }
  }
}