#pragma once

#include "LEDController/pattern.h"

void LEDPattern::Twinkle()
{
    fadeToBlackBy(_Leds.data(), _NumLeds, _ledsettings._pattern_fade_amount);
    int i = random8(0, _NumLeds - 1);
    //_Leds.data()[i] = PaletteMode(i);
    DrawPixels(i, 1, PaletteMode(i));
}