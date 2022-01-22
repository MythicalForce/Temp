#pragma once

#include "LEDController/pattern.h"

//
//
// NOT WORKING YET!
//
//

void LEDPattern::ColorStacking()
{
	const uint16_t TotalLength = _NumLeds;
  const uint16_t BlockSize = 2;
	
	uint16_t end = TotalLength;

  for( int block = 0; block < TotalLength/BlockSize; block++ )
  {
    const CRGB color = CHSV( random(0, 255), 255, 255 );

    for ( int i = 0; i < end; i++ )
    {
      _Leds.data()[ i ] = color;
      if( i >= BlockSize )
      {
        _Leds.data()[ i - BlockSize ] = CRGB::Black;
      }
    }

    end -= BlockSize;
  }
}
