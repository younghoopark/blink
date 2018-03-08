#include "Arduino.h"

class Blink
{
  public:
    Blink(int pin);
    void on(int a);
    void off(int b);
  private:
    int _pin;
};

