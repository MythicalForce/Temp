#pragma once

#include "LEDController/pattern.h"

void LEDPattern::TheaterChase()
{
    fadeToBlackBy(_Leds.data(), _NumLeds, 255);

    for (float i = _pattern_position; i < _NumLeds; i+= 3)
    {
        DrawPixels(i, 1, PaletteMode(i));
    }
}
