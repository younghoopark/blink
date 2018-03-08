#include "Arduino.h"

class Blink
{
  public:
    Blink(int pin);
    void on();
    void off();
  private:
    int _pin;
};

