#pragma once

#include <globals.h>
#include <WebSocketsServer.h>
#include <MsgPack.h>
#include "msgpack.h"
#include "enum.h"
#include "LEDController/config.h"
#include "LEDController/controller.h"
#include "relay.h"
#include "ArduinoJson.h"

WebSocketsServer webSocket = WebSocketsServer( 80 );

extern std::vector<LEDSettings> ledsettings;

extern LEDPattern *Strips[];

namespace websocket
{
  int selectedstrip;

  void webSocketEvent( uint8_t num, WStype_t type, uint8_t * payload, size_t length )
  {
    IPAddress ip = webSocket.remoteIP( num );

    StaticJsonDocument<256> inData;
    deserializeJson(inData, payload);

    DynamicJsonDocument outData(256);
    String outJsonData;

    switch ( type )
    {
      case WStype_CONNECTED:
        debug.success( "[SOCKET]", "[CLIENTCONNECT]", "[%u] from %d.%d.%d.%d url: %s", num, ip[0], ip[1], ip[2], ip[3], payload );
      break;

      case WStype_DISCONNECTED: 
        debug.info( "[SOCKET]", "[CLIENTDISCONNECT]", "[%u] Disconnected!", num );
      break;

      case WStype_ERROR:
        debug.error( "[SOCKET]", "[ERROR]", "Oh Shit!" );
        debug.error( "[SOCKET]", "[ERROR]", "[%u] Disconnected!", payload );
      break;

      case WStype_BIN:
      case WStype_TEXT:
        if ( inData.containsKey("reqDeviceInfo") )
        {
          Serial.println("Someone requested info!");
          outData["devicetype"]        = Config[DEVICE].Device_Type;
          outData["devicename"]        = Config[DEVICE].Device_Name;
          outData["ledtype"]           = Config[DEVICE].LED_Type;
          //outData["stripnumled"] 
          outData["patternActive"]     = ledsettings[selectedstrip]._pattern_active;
          outData["brightness"]        = ledsettings[selectedstrip]._pattern_brightness;
          outData["patternDelay"]      = ledsettings[selectedstrip]._pattern_delay;
          //outData["patternSpacing"]
          outData["patternDirection"]  = ledsettings[selectedstrip]._pattern_direction;
          outData["patternTail"]       = ledsettings[selectedstrip]._pattern_tail;
          outData["patternFadeAmount"] = ledsettings[selectedstrip]._pattern_fade_amount;
          outData["patternWrapAround"] = ledsettings[selectedstrip]._pattern_wrap_around;
          outData["colorPicker"]       = ledsettings[selectedstrip]._palette_picker;
          outData["paletteMode"]       = ledsettings[selectedstrip]._palette_mode;
          outData["selectedPalette"]   = ledsettings[selectedstrip]._palette_selected;
          outData["paletteBlendMode"]  = ledsettings[selectedstrip]._palette_blend;

          serializeJson(outData, outJsonData);
          webSocket.sendTXT(num, outJsonData);
        }

        if ( inData.containsKey("EnableUV") )
        {
          relay::enableRelay = (bool)inData["EnableUV"];
        }
        if ( inData.containsKey("selectedstrip") )
        {
          selectedstrip = inData["selectedstrip"];
        }
        if ( inData.containsKey("brightness") )
        {
          ledsettings[selectedstrip]._pattern_brightness = inData["brightness"];
        }
        if ( inData.containsKey("patternActive") )
        {
          ledsettings[selectedstrip]._pattern_active = (E_Patterns)inData["patternActive"];
        }
        if ( inData.containsKey("patternDirection") )
        {
          ledsettings[selectedstrip]._pattern_direction = (E_Direction)inData["patternDirection"];
        }
        if ( inData.containsKey("patternDelay") )
        {
          ledsettings[selectedstrip]._pattern_delay = (int)inData["patternDelay"];
        }
        /*if ( inData.containsKey("patternSpacing") )
        {
          Strips[selectedstrip]->_pattern_spacing = (int)inData["patternSpacing"];
        }*/
        if ( inData.containsKey("patternTail") )
        {
          ledsettings[selectedstrip]._pattern_tail = (E_Tail)inData["patternTail"];
        }
        if ( inData.containsKey("patternFadeAmount") )
        {
          ledsettings[selectedstrip]._pattern_fade_amount = (int)inData["patternFadeAmount"];
        }
        if ( inData.containsKey("patternWrapAround") )
        {
          ledsettings[selectedstrip]._pattern_wrap_around = (E_WrapAround)inData["patternWrapAround"];
        }
        if ( inData.containsKey("paletteActive") )
        {
          ledsettings[selectedstrip]._palette_selected = (E_Palette)inData["paletteActive"];
        }
        if ( inData.containsKey("paletteSpeed") )
        {
          ledsettings[selectedstrip]._palette_delay = (int)inData["paletteSpeed"];
        }
        if ( inData.containsKey("paletteDirection") )
        {
          ledsettings[selectedstrip]._palette_direction = (E_Direction)inData["paletteDirection"];
        }
        if ( inData.containsKey("paletteMode") )
        {
          ledsettings[selectedstrip]._palette_mode = (E_PaletteMode)inData["paletteMode"];
        }
        if ( inData.containsKey("colorPicker") )
        {
          ledsettings[selectedstrip]._palette_picker = (int)inData["colorPicker"];
        }
        if ( inData.containsKey("paletteBlendMode") )
        {
          ledsettings[selectedstrip]._palette_blend = (TBlendType)inData["paletteBlendMode"];
        }
        if ( inData.containsKey("rgbArray") )
        {
          ledsettings[selectedstrip].copyPaletteArray(inData["rgbArray"].as<JsonArray>());
        }
      break;
      case WStype_FRAGMENT_TEXT_START:
      case WStype_FRAGMENT_BIN_START:
      case WStype_FRAGMENT:
      case WStype_FRAGMENT_FIN:
      case WStype_PING:
      case WStype_PONG:
      break;
    }
  }

  void begin()
  {    
    webSocket.begin();
    webSocket.onEvent( webSocketEvent );

    debug.success("[SOCKET]", "[STATUS]", "Websocket Online!");
  }

  void loop()
  {
    webSocket.loop();
  }
}