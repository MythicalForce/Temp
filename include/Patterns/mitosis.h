#pragma once

#include "LEDController/pattern.h"

// STATE: This is working in its current state!
void LEDPattern::Mitosis()
{
  TailMode();

  for ( float i = 0; i < _ledsettings._pattern_lead_pixel_size; i++ )
  {
    float pi = _pattern_position + i - _ledsettings._pattern_lead_pixel_size;
    static int pic;
    if ((int)pi >= 0 && (int)pi < _NumLeds) { pic = (int)pi; }

    float ni = ( _NumLeds - 1 ) - pi;

    if ( pi >= 0 && pi <= (_NumLeds / 2) - 1 )
    {
      DrawPixels(pi, 1, PaletteMode( pic ) );
      DrawPixels(ni, 1, PaletteMode( ni ) );
    }
  }
}