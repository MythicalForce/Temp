#include <Arduino.h>

unsigned long  _update;

bool TimeToUpdate(int _delay)
{
    if ( millis() - _update >= _delay )
    {
        _update = millis();
        return true;
    }
    else
    {
        return false;
    }
}
