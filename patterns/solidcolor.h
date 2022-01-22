#pragma once

#include "LEDController/pattern.h"

void LEDPattern::SolidColor()
{
    fadeToBlackBy(_Leds.data(), _NumLeds, 255);

    for(float i = 0; i < _NumLeds; i++)
    {   
        DrawPixels(i, 1, PaletteMode(i));
    }
}
