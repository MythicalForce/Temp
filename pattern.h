#pragma once

#include <Arduino.h>
#include "settings.h"
#include <map>

using namespace std;

class LEDPattern : public LEDSettings
{
    public:
        LEDSettings&        _ledsettings;
        std::vector<CRGB>   _Leds;
        unsigned int        _NumLeds;
        const unsigned int  _MaxLeds;
        float               _pattern_position;  // used be INT
        uint16_t            _pattern_directionFF;
        uint16_t            _pattern_spacing;

        uint16_t       _palette_position;

        void SolidColor();
        void Rainbow();
        void TheaterChase();
        void Juggle();
        void RunningLight();
        void Cylon();
        void Mitosis();
        void Twinkle();
        void Firework();
        void ColorStacking();

        typedef void (LEDPattern::*sig_ptr)(void);

        struct PattList
        {
            int Num;
            string name;
            sig_ptr funcPointer;
        };

        std::map<String, sig_ptr> _PatterList;

        sig_ptr SC = &LEDPattern::SolidColor;
        sig_ptr TC = &LEDPattern::TheaterChase;
        sig_ptr J = &LEDPattern::Juggle;
        sig_ptr RL = &LEDPattern::RunningLight;
        sig_ptr C = &LEDPattern::Cylon;
        sig_ptr M = &LEDPattern::Mitosis;
        sig_ptr T = &LEDPattern::Twinkle;
        sig_ptr CS = &LEDPattern::ColorStacking;

        PattList pattList[20] = 
        {
            { 0, "SolidColor", SC },
            { 1, "TheaterChase", TC },
            { 2, "Juggle", J },
            { 3, "RunningLight", RL },
            { 4, "Cylon", C },
            { 5, "Mitosis", M },
            { 6, "Twinkle", T },
            { 7, "ColorStacking", CS }
        };

        CRGB ColorFraction(CRGB colorIn, float fraction);
        void DrawPixels(float fPos, float count, CRGB color);
        CRGB PaletteMode( int Index, int Brightness=0 );
        void TailMode();
        void IncrementPatternPosition();
        void IncrementPalettePosition();
        void setNumLeds(unsigned int nl)
        {
            _NumLeds = nl;
        }
        void Update();

        void setSettings( LEDSettings& s )
        {
            _ledsettings = s;
        }

        LEDPattern( unsigned int num_leds, LEDSettings& s ) : _ledsettings( s ), _NumLeds( num_leds ), _MaxLeds( num_leds - 1 )
        {
            _Leds.resize( num_leds );
            _pattern_position        = 0.0f;
            _pattern_directionFF     = 1;
            _pattern_spacing         = 3;

            _palette_position        = 0;

            _PatterList["SolidColor"] = SC;
            _PatterList["TheaterChase"] = TC;
            _PatterList["Juggle"] = J;
            _PatterList["RunningLight"] = RL;
            _PatterList["Cylon"] = C;
            _PatterList["Mitosis"] = M;
            _PatterList["Twinkle"] = T;
            _PatterList["ColorStacking"] = CS;
        }

};
