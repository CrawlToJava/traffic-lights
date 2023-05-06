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
      carRedLight();
      personGreenLight();
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
      carGreenLight();
      personRedLight();
    }
    if (countValue > 6 && countValue <= 10)
    {
      carYellowLight();
      personYellowLight();
    }
    if (countValue > 10 && countValue <= 16)
    {
      carRedLight();
      personGreenLight();
    }
    if (countValue > 16 && countValue < 18)
    {
      carYellowLight();
      personNoLight();
    }
    if (countValue > 17 && countValue < 19)
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
    if (countValue == 21)
    {
      carYellowLight();
      personNoLight();
    }
    if (countValue > 21)
    {
      countValue = 0;
    }
  }
}