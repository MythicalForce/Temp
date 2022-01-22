#pragma once

#include "LEDController/pattern.h"

// STATE: This is working in its current state!
void LEDPattern::Cylon()
{
    
    //fadeToBlackBy(_Leds.data(), _NumLeds, 255);

    for ( float i = 0; i < _ledsettings._pattern_lead_pixel_size; i++ )
    {  
        float pi = _pattern_position + i - _ledsettings._pattern_lead_pixel_size;
        static int pic;
        if ((int)pi >= 0 && (int)pi < _NumLeds) { pic = (int)pi; }
        DrawPixels(pi, 1, PaletteMode( pic ) );
    }
    TailMode();
}