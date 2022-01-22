#pragma once

#include "LEDController/pattern.h"

void LEDPattern::RunningLight()
{
    fadeToBlackBy(_Leds.data(), _NumLeds, 255);
    
    for (uint16_t i = 0; i < _NumLeds; i++)
    {
        uint16_t a = 2 * (i + _pattern_position) * 255 / (_NumLeds - 1);
        uint16_t ni = (_NumLeds - 1) - i;
        DrawPixels(ni, 1, PaletteMode(ni, sin8(a) * _ledsettings._pattern_brightness / 255));
    }
} 
