#pragma once

#include "LEDController/pattern.h"

void LEDPattern::Juggle()
{
    TailMode();
    int dothue = 0;
    int balls = 8;

    for (uint16_t i = 0; i < balls; ++i)
    {
        //_Leds.data()[beatsin16(i + 7, 0, _NumLeds - 1)] |= CHSV(dothue, 200, _ledsettings._pattern_brightness);
        DrawPixels(beatsin16(i + 7, 0, _NumLeds - 1), 1, CHSV(dothue, 255, _ledsettings._pattern_brightness));
        dothue += 32;
    }
}