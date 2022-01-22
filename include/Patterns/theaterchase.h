#pragma once

#include "LEDController/pattern.h"

// STATE: This is working in its current state!
void LEDPattern::TheaterChase()
{
    fadeToBlackBy(_Leds.data(), _NumLeds, 255);

    for (float i = _pattern_position; i < _NumLeds; i+= 3)
    {
        DrawPixels(i, 1, PaletteMode(i));
    }
    
    /*
    for (int i = 0; i < _NumLeds; i++)
    {
        if ( ( i + _pattern_position ) % 3 == 0 )
        {
            _Leds.data()[i] = PaletteMode(i);
            
        }
    }
    */
}