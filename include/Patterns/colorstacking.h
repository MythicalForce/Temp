#pragma once

#include "LEDController/pattern.h"

// STATE: This is working in its current state!
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
  /*
  const uint16_t TotalLength = _NumLeds;
  const uint16_t BlockSize = 2;

  static uint16_t end = TotalLength;
  static int block = 0;
  static CRGB color = 0;
  static int i = 0;  

  // reset after each full sequence
  if ( block >= TotalLength / BlockSize )
  {
    block = 0;
    end = TotalLength;
    color = CHSV( random( 0, 255 ), 255, 255 );
    i = 0;
  }

  _Leds.data()[ i ] = color;
  if ( i >= BlockSize )
  {
    _Leds.data()[ i - BlockSize ].fadeToBlackBy( 255 );
  }

  if ( ++i >= end )
  {
    i = 0;
    end -= BlockSize;
    color = CHSV( random( 0, 255 ), 255, 255 );
    block++;
  }
  */
}