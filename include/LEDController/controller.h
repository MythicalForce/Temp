#pragma once

#include <FastLED.h>
#include "settings.h"
#include "pattern.h"

template <unsigned int PIN_OF_LED, unsigned int NUM_LEDS, unsigned int REAL_NUM_LEDS>
class LEDController : public LEDPattern
{
    public:
        CLEDController* controller;

        LEDController( LEDSettings& s ) : LEDPattern( REAL_NUM_LEDS, s )
        {
            controller = &FastLED.addLeds<WS2812B, PIN_OF_LED, GRB>( _Leds.data(), NUM_LEDS ).setCorrection( TypicalLEDStrip );
        }
};