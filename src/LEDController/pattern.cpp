#include "LEDController/pattern.h"
#include "palette.h"

#include "Patterns/solidcolor.h"
#include "Patterns/theaterchase.h"
#include "Patterns/juggle.h"
#include "Patterns/runninglights.h"
#include "Patterns/cylon.h"
#include "Patterns/mitosis.h"
#include "Patterns/twinkle.h"
#include "Patterns/colorstacking.h"

CRGB LEDPattern::ColorFraction(CRGB colorIn, float fraction)
{
   fraction = min(1.0f, fraction);
   return CRGB(colorIn).fadeToBlackBy(255 * (1.0f - fraction));
}

void LEDPattern::DrawPixels(float fPos, float count, CRGB color)
{
    float availFirstPixel = 1.0f - (fPos - (long)(fPos));
    float amtFirstPixel = min(availFirstPixel, count);
    float remaining = min(count, _NumLeds-fPos);
    int iPos = fPos;

    if (remaining > 0.0f)
    {
        CRGB c = ColorFraction(color, amtFirstPixel);
        CRGB& p = _Leds.data()[iPos++];
        p.r = max(p.r, c.r);
        p.g = max(p.g, c.g);
        p.b = max(p.b, c.b);
        remaining -= amtFirstPixel;
    }

   // Now draw any full pixels in the middle

    while (remaining > 1.0f)
    {
        _Leds.data()[iPos++] += color;
        remaining--;
    }

   // Draw tail pixel, up to a single full pixel

    if (remaining > 0.0f)
    {
        //_Leds.data()[iPos] += ColorFraction(color, remaining);

        CRGB c = ColorFraction(color, remaining);
        CRGB& p = _Leds.data()[iPos];
        p.r = max(p.r, c.r);
        p.g = max(p.g, c.g);
        p.b = max(p.b, c.b);
    }
}

CRGB LEDPattern::PaletteMode(int Index, int Brightness)
{
    if (Brightness == 0)
    {
        Brightness = _ledsettings._pattern_brightness;
    }

    switch ( _ledsettings._palette_mode )
    {
        case          ONECOLOR: return ColorFromPalette(_ledsettings._palette_current, _ledsettings._palette_picker, Brightness, _ledsettings._palette_blend); break;
        case       FULLPALETTE: return ColorFromPalette(_ledsettings._palette_current, Index * 255 / _NumLeds, Brightness, _ledsettings._palette_blend); break;
        case FULLPALETTEMOVING: return ColorFromPalette(_ledsettings._palette_current, (_palette_position * 255 / _NumLeds) - (Index * 255 / _NumLeds), Brightness, _ledsettings._palette_blend); break;
    
        default: break;
    }

    return CRGB();
}

void LEDPattern::TailMode()
{ 
    switch (_ledsettings._pattern_tail)
    {
    case DUST:
        for (int j = 0; j < _NumLeds; j++)
        {
            if (random(10) == 1)
            {
                //_Leds.data()[j] = _Leds.data()[j].fadeToBlackBy(_ledsettings._pattern_fade_amount);
                _Leds.data()[j].fadeToBlackBy(_ledsettings._pattern_fade_amount);
            }
        }
    break;
    case SOLID:
        //fadeToBlackBy(_Leds.data(), _NumLeds, _ledsettings._pattern_fade_amount);
        fadeToBlackBy(_Leds.data(), _NumLeds, 255);
    break;
    
    default:
    break;
    }
}

void LEDPattern::IncrementPatternPosition()
{
    if ( _ledsettings._pattern_wrap_around == YES && _ledsettings._pattern_direction == FORWARD )
    {
        _pattern_position += 0.1f;

        if ( _ledsettings._pattern_active == THEATHERCHASE )
        {
            if ( _pattern_position >= 3 )
                _pattern_position = 0.0f;
        }
        else if ( _ledsettings._pattern_active == CYLON )
        {
            if ( _pattern_position >= (_NumLeds + _ledsettings._pattern_lead_pixel_size) )
                _pattern_position = 0.0f;
        }
        else if ( _ledsettings._pattern_active == MITOSIS )
        {
            if ( _pattern_position > _NumLeds / 2 - 1 + _ledsettings._pattern_lead_pixel_size )
                _pattern_position = 0.0f;
        }
        else
        {
            if ( _pattern_position >= _NumLeds )
                _pattern_position = 0.0f;
        }

        /*
        if ( _ledsettings._pattern_active == THEATHERCHASE )
            if ( _pattern_position >= _NumLeds )
                _pattern_position = _NumLeds % _pattern_spacing;

        else if ( _ledsettings._pattern_active == CYLON )
            if ( _pattern_position > _NumLeds + _ledsettings._pattern_lead_pixel_size )
                _pattern_position = 0;

        else if ( _ledsettings._pattern_active == MITOSIS )
            if ( _pattern_position > _NumLeds / 2 - 1 + _ledsettings._pattern_lead_pixel_size )
                _pattern_position = 0;

        else
            if ( _pattern_position >= _NumLeds )
                _pattern_position = 0;
        */
    }
    else if ( _ledsettings._pattern_wrap_around == YES && _ledsettings._pattern_direction == REVERSE )
    {
        _pattern_position  -= 0.1f;

        if ( _ledsettings._pattern_active == THEATHERCHASE )
        {
            if ( _pattern_position <= 0 )
                _pattern_position = 3;
        }
        else if ( _ledsettings._pattern_active == CYLON )
        {
            if ( _pattern_position < 0 )
                _pattern_position = (_NumLeds + _ledsettings._pattern_lead_pixel_size);
        }
        else if ( _ledsettings._pattern_active == MITOSIS )
        {
            if ( _pattern_position < 0 )
                _pattern_position = _NumLeds / 2 - 1 + _ledsettings._pattern_lead_pixel_size;
        }
        else
        {
            if ( _pattern_position <= 0 )
                _pattern_position = _NumLeds;
        }
        /*
        if ( _ledsettings._pattern_active == THEATHERCHASE )
            if ( _pattern_position <= 0 )
                _pattern_position = _pattern_spacing;

        else if ( _ledsettings._pattern_active == CYLON )
            if ( _pattern_position < 0 )
                _pattern_position = _NumLeds + _ledsettings._pattern_lead_pixel_size;

        else if ( _ledsettings._pattern_active == MITOSIS )
            if ( _pattern_position < 0 )
                _pattern_position = _NumLeds / 2 - 1 + _ledsettings._pattern_lead_pixel_size;
 
        else
            if ( _pattern_position <= 0 )
                _pattern_position = _NumLeds;
        */
    }

    // FIXME: Crashes if position is "out of bounds"! do a check for that befor enabling bounce effects!
    if ( _ledsettings._pattern_wrap_around == NO && _ledsettings._pattern_active == CYLON )
    {
        if ( _pattern_directionFF == 1)
        {
            _pattern_position += 0.1f;
        }
        else
        {
            _pattern_position -= 0.1f;
        }

        if ( _pattern_position >= _NumLeds || _pattern_position <= 4.0f )
        {
            _pattern_directionFF *= -1;
        }
    }

    // FIX: Reset WrapAround to "YES" if ActivePattern is anything else than "Cylon = 5"
    if ( _ledsettings._pattern_wrap_around == NO ) { if ( _ledsettings._pattern_active != CYLON ) { _ledsettings._pattern_wrap_around = YES; } }
}

void LEDPattern::IncrementPalettePosition()
{
if ( _ledsettings._palette_direction == FORWARD )
    {
        _palette_position++;
        if ( _palette_position >= _NumLeds )
        {
            _palette_position = 0;
        }
    }
    else if ( _ledsettings._palette_direction == REVERSE )
    {
        --_palette_position;
        if ( _palette_position <= 0 )
        {
            _palette_position = _NumLeds;
        }
    }
}

void LEDPattern::Update()
{
    switch ( _ledsettings._palette_selected )
    {
        case     palSUNSETREAL: _ledsettings._palette_current = Sunset_Real_gp;     break;
        case   palSUMMERSUNSET: _ledsettings._palette_current = SummerSunset_gp;    break;
        case        palRAINBOW: _ledsettings._palette_current = rainbow_gp;         break;
        case palCHRISTMASCANDY: _ledsettings._palette_current = christmas_candy_gp; break;
        case      palDARKSPACE: _ledsettings._palette_current = darkspace_gp;       break;
        case      palDEEPOCEAN: _ledsettings._palette_current = deepocean_gp;       break;
        case           palFIRE: _ledsettings._palette_current = fire_gp;            break;
        case         palBHW128: _ledsettings._palette_current = bhw1_28_gp;         break;
        case         palBHW119: _ledsettings._palette_current = bhw1_19_gp;         break;
        case         palBHW222: _ledsettings._palette_current = bhw2_22_gp;         break;
        case       palGREENMAN: _ledsettings._palette_current = bhw2_greenman_gp;   break;
        case         palBHW102: _ledsettings._palette_current = bhw1_02_gp;         break;
        case         palBHW113: _ledsettings._palette_current = bhw1_13_gp;         break;
        
        default: break;
    }
    
    switch ( _ledsettings._pattern_active )
    {
        case 0: SolidColor();    break;
        case 1: TheaterChase();  break;
        case 2: Juggle();        break;
        case 3: RunningLight();  break;
        case 4: Cylon();         break;
        case 5: Mitosis();       break;
        case 6: Twinkle();       break;
        case 7: ColorStacking(); break;
        
        default: break;
    }
}