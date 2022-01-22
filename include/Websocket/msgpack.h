#pragma once

#include <MsgPack.h>
#include "ArduinoJson.h"

MsgPack::Packer packer;
MsgPack::Unpacker unpacker;
MsgPack::map_t<String, MsgPack::arr_t<int>> mIndata;

struct MyNestedClass
{
    MsgPack::str_t key_DeviceType;      MsgPack::str_t Value_DeviceType;
    MsgPack::str_t key_DeviceName;      MsgPack::str_t Value_DeviceName;
    MsgPack::str_t key_LEDType;         MsgPack::str_t Value_LEDType;
    MsgPack::str_t key_NumLeds;         int Value_NumLeds;
    MsgPack::str_t key_ActivePattern;   int Value_ActivePattern;
    MsgPack::str_t key_Brightness;      int Value_Brightness;
    MsgPack::str_t key_Delay;           int Value_Delay;
    MsgPack::str_t key_Spacing;         int Value_Spacing;
    MsgPack::str_t key_Direction;       int Value_Direction;
    MsgPack::str_t key_Tail;            int Value_Tail;
    MsgPack::str_t key_FadeAmt;         int Value_FadeAmt; 
    MsgPack::str_t key_WrapAround;      int Value_WrapAround;
    MsgPack::str_t key_ColorPicker;     int Value_ColorPicker;
    MsgPack::str_t key_PaletteMode;     int Value_PaletteMode;  
    MsgPack::str_t key_SelectedPalette; int Value_SelectedPalette;
    MsgPack::str_t key_BlendMode;       int Value_BlendMode;
    MsgPack::str_t Key_rgbArray;        MsgPack::arr_t<int> Value_rgbArray;
    MSGPACK_DEFINE_MAP(
                        key_DeviceType,      Value_DeviceType,
                        key_DeviceName,      Value_DeviceName,
                        key_LEDType,         Value_LEDType,
                        key_NumLeds,         Value_NumLeds,
                        key_ActivePattern,   Value_ActivePattern,
                        key_Brightness,      Value_Brightness,
                        key_Delay,           Value_Delay,
                        key_Spacing,         Value_Spacing,
                        key_Direction,       Value_Direction,
                        key_Tail,            Value_Tail,
                        key_FadeAmt,         Value_FadeAmt,
                        key_WrapAround,      Value_WrapAround,
                        key_ColorPicker,     Value_ColorPicker,
                        key_PaletteMode,     Value_PaletteMode,
                        key_SelectedPalette, Value_SelectedPalette,
                        key_BlendMode,       Value_BlendMode,
                        Key_rgbArray,        Value_rgbArray
                    );
};

MyNestedClass c;

/*
        if (unpacker.feed( payload, length ))
        {
          unpacker.deserialize( mIndata, doc );
          unpacker.clear();

          if ( mIndata.find("reqDeviceInfo") != mIndata.end() )
          {
            c.key_DeviceType      = "devicetype";
            c.key_DeviceName      = "devicename";
            c.key_LEDType         = "ledtype";
            c.key_NumLeds         = "stripnumled";
            c.key_ActivePattern   = "patternActive";
            c.key_Brightness      = "brightness";
            c.key_Delay           = "patternDelay";
            c.key_Spacing         = "patternSpacing";
            c.key_Direction       = "patternDirection";
            c.key_Tail            = "patternTail";
            c.key_FadeAmt         = "patternFadeAmount";
            c.key_WrapAround      = "patternWrapAround";
            c.key_ColorPicker     = "colorPicker";
            c.key_PaletteMode     = "paletteMode";
            c.key_SelectedPalette = "selectedPalette";
            c.key_BlendMode       = "paletteBlendMode";

            c.Value_DeviceType      = Config[DEVICE].Device_Type;
            c.Value_DeviceName      = Config[DEVICE].Device_Name;
            c.Value_LEDType         = Config[DEVICE].LED_Type;
            c.Value_ActivePattern   = ledsettings[selectedstrip]._pattern_active;
            c.Value_Brightness      = ledsettings[selectedstrip]._pattern_brightness;
            c.Value_Delay           = ledsettings[selectedstrip]._pattern_delay;
            c.Value_Direction       = ledsettings[selectedstrip]._pattern_direction;
            c.Value_Tail            = ledsettings[selectedstrip]._pattern_tail;
            c.Value_FadeAmt         = ledsettings[selectedstrip]._pattern_fade_amount;
            c.Value_WrapAround      = ledsettings[selectedstrip]._pattern_wrap_around;
            c.Value_ColorPicker     = ledsettings[selectedstrip]._palette_picker;
            c.Value_PaletteMode     = ledsettings[selectedstrip]._palette_mode;
            c.Value_SelectedPalette = ledsettings[selectedstrip]._palette_selected;
            c.Value_BlendMode       = ledsettings[selectedstrip]._palette_blend;

            packer.clear();
            packer.serialize(c);

            webSocket.sendBIN(num, packer.data(), packer.size());
          }
*/