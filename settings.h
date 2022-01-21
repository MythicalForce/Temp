#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include "enum.h"

class LEDSettings
{
public:
    // Pattern Settings
    uint8_t        _pattern_brightness;
    E_Patterns     _pattern_active;
    E_Direction    _pattern_direction;
    uint8_t        _pattern_delay;
    E_Tail         _pattern_tail;
    uint8_t        _pattern_lead_pixel_size;
    uint8_t        _pattern_fade_amount;
    E_WrapAround   _pattern_wrap_around;

    // Palette Settings
    uint8_t        _palette_delay;
    E_Direction    _palette_direction;
    E_PaletteMode  _palette_mode;
    uint8_t        _palette_picker;
    E_Palette      _palette_selected;
    CRGBPalette256 _palette_current;
    TBlendType     _palette_blend;
    CRGBPalette256 _myPal;
    uint8_t        _paletteBuffer[256];

    // Update Settings
    unsigned long  _pattern_update;
    unsigned long  _palette_update;

    LEDSettings()
    {
        // Pattern Settings
        _pattern_brightness      = 64;
        _pattern_active          = CYLON;
        _pattern_direction       = FORWARD;
        _pattern_delay           = 127;
        _pattern_tail            = DUST;
        _pattern_lead_pixel_size = 4;
        _pattern_fade_amount     = 128;
        _pattern_wrap_around     = YES;

        // Palette Settings
        _palette_delay           = 70;
        _palette_direction       = FORWARD;
        _palette_mode            = ONECOLOR;
        _palette_picker          = 0;
        _palette_selected        = palSUNSETREAL;
        _palette_blend           = LINEARBLEND;

        // Update Settings
        _pattern_update        = 0;
        _palette_update        = 0;
    }

    // Functions
    bool TimeToUpdatePattern();
    bool TimeToUpdatePalette();
    void UpdateCurrentPalette();
    void update();
};
