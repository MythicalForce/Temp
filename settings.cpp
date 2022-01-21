#include "LEDController/settings.h"

bool LEDSettings::TimeToUpdatePattern()
{
    if ( millis() - _pattern_update >= _pattern_delay )
    {
        _pattern_update = millis();
        return true;
    }
    else
    {
        return false;
    }
}
bool LEDSettings::TimeToUpdatePalette()
{
    if ( millis() - _palette_update >= _palette_delay )
    {
        _palette_update = millis();
        return true;
    }
    else
    {
        return false;
    }
}
