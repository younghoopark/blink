#include "Arduino.h"
#include "Blink.h"

Blink::Blink(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Blink::on(int a)
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(1000);
}

void Blink::off(int b)
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(1000);
}

