#include <Arduino.h>

#define FASTLED_ALLOW_INTERRUPTS 0

#include "globals.h"
#include "secrets.h"
#include "network.h"
#include "debugger.h"
#include "Websocket/websocket.h"
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

//
// Task Handles to our running threads
//

TaskHandle_t g_taskDraw   = nullptr;
TaskHandle_t g_taskRelay  = nullptr;
TaskHandle_t g_taskNet    = nullptr;
TaskHandle_t g_taskSocket = nullptr;

std::vector<LEDSettings> ledsettings { {}, {}, {}, {}, {}, {}, {}, {}, {} };

#if NUM_CHANNELS >= 1
  LEDController<LED_PIN1, LED_AMOUNT_PER_PIN, Config[DEVICE].NUMLED[0]> Strip1{ledsettings[0]};
#endif

#if NUM_CHANNELS >= 2
  LEDController<LED_PIN2, LED_AMOUNT_PER_PIN, Config[DEVICE].NUMLED[1]> Strip2{ledsettings[1]};
#endif

#if NUM_CHANNELS >= 3
  LEDController<LED_PIN3, LED_AMOUNT_PER_PIN, Config[DEVICE].NUMLED[2]> Strip3{ledsettings[2]};
#endif

#if NUM_CHANNELS >= 4
  LEDController<LED_PIN4, LED_AMOUNT_PER_PIN, Config[DEVICE].NUMLED[3]> Strip4{ledsettings[3]};
#endif

#if NUM_CHANNELS >= 5
  LEDController<LED_PIN5, LED_AMOUNT_PER_PIN, Config[DEVICE].NUMLED[4]> Strip5{ledsettings[4]};
#endif

#if NUM_CHANNELS >= 6
  LEDController<LED_PIN6, LED_AMOUNT_PER_PIN, Config[DEVICE].NUMLED[5]> Strip6{ledsettings[5]};
#endif

#if NUM_CHANNELS >= 7
  LEDController<LED_PIN7, LED_AMOUNT_PER_PIN, Config[DEVICE].NUMLED[6]> Strip7{ledsettings[6]};
#endif

#if NUM_CHANNELS >= 8
  LEDController<LED_PIN8, LED_AMOUNT_PER_PIN, Config[DEVICE].NUMLED[7]> Strip8{ledsettings[7]};
#endif

LEDPattern *Strips[] =
{
  #if NUM_CHANNELS >= 1
    &Strip1,
  #endif
  #if NUM_CHANNELS >= 2
    &Strip2,
  #endif
  #if NUM_CHANNELS >= 3 
    &Strip3,
  #endif
  #if NUM_CHANNELS >= 4
    &Strip4,
  #endif
  #if NUM_CHANNELS >= 5
    &Strip5,
  #endif 
  #if NUM_CHANNELS >= 6
    &Strip6,
  #endif
  #if NUM_CHANNELS >= 7
    &Strip7,
  #endif
  #if NUM_CHANNELS >= 8
    &Strip8
  #endif
  };

void IRAM_ATTR SocketServerTaskEntry(void *)
{
    for (;;)
    {
        if (WiFi.isConnected())
        {
          websocket::loop();
        }
    }
}

void IRAM_ATTR DrawLoopTaskEntry(void *)
{
  for (;;)
  {
    TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
    TIMERG0.wdt_feed=1;
    TIMERG0.wdt_wprotect=0;

    switch (websocket::selectedstrip)
    {
      #if NUM_CHANNELS >= 1
        case 0: Strip1.setSettings(ledsettings[0]); break;
      #endif

      #if NUM_CHANNELS >= 2
        case 1: Strip2.setSettings(ledsettings[1]); break;
      #endif

      #if NUM_CHANNELS >= 3
        case 2: Strip3.setSettings(ledsettings[2]); break;
      #endif

      #if NUM_CHANNELS >= 4
        case 3: Strip4.setSettings(ledsettings[3]); break;
      #endif

      #if NUM_CHANNELS >= 5
        case 4: Strip5.setSettings(ledsettings[4]); break;
      #endif

      #if NUM_CHANNELS >= 6
        case 5: Strip6.setSettings(ledsettings[5]); break;
      #endif

      #if NUM_CHANNELS >= 7
        case 6: Strip7.setSettings(ledsettings[6]); break;
      #endif

      #if NUM_CHANNELS >= 8
        case 7: Strip8.setSettings(ledsettings[7]); break;
      #endif

      case 8: 
      #if NUM_CHANNELS >= 1
        Strip1.setSettings(ledsettings[8]);
      #endif

      #if NUM_CHANNELS >= 2
        Strip2.setSettings(ledsettings[8]);
      #endif

      #if NUM_CHANNELS >= 3
        Strip3.setSettings(ledsettings[8]);
      #endif

      #if NUM_CHANNELS >= 4
        Strip4.setSettings(ledsettings[8]);
      #endif

      #if NUM_CHANNELS >= 5
        Strip5.setSettings(ledsettings[8]);
      #endif

      #if NUM_CHANNELS >= 6
        Strip6.setSettings(ledsettings[8]);
      #endif

      #if NUM_CHANNELS >= 7
        Strip7.setSettings(ledsettings[8]);
      #endif

      #if NUM_CHANNELS >= 8
        Strip8.setSettings(ledsettings[8]);
      #endif

      break;
      
      default:
          break;
    }

    #if NUM_CHANNELS >= 1
      if ( ledsettings[0].TimeToUpdatePattern() )
      {
        //ledsettings[0].IncrementPatternPosition();
        Strip1.IncrementPatternPosition();
        Strip1.Update();
      }
    #endif

    #if NUM_CHANNELS >= 2
      if ( ledsettings[1].TimeToUpdatePattern() )
      {
        //ledsettings[1].IncrementPatternPosition();
        Strip2.IncrementPatternPosition();
        Strip2.Update();
      }
    #endif

    #if NUM_CHANNELS >= 3
      if ( ledsettings[2].TimeToUpdatePattern() )
      {
        //ledsettings[2].IncrementPatternPosition();
        Strip3.IncrementPatternPosition();
        Strip3.Update();
      }
    #endif

    #if NUM_CHANNELS >= 4
      if ( ledsettings[3].TimeToUpdatePattern() )
      {
        //ledsettings[3].IncrementPatternPosition();
        Strip4.IncrementPatternPosition();
        Strip4.Update();
      }
    #endif

    #if NUM_CHANNELS >= 5
      if ( ledsettings[4].TimeToUpdatePattern() )
      {
        //ledsettings[4].IncrementPatternPosition();
        Strip5.IncrementPatternPosition();
        Strip5.Update();
      }
    #endif
    
    #if NUM_CHANNELS >= 6
      if ( ledsettings[5].TimeToUpdatePattern() )
      {
        //ledsettings[5].IncrementPatternPosition();
        Strip6.IncrementPatternPosition();
        Strip6.Update();
      }
    #endif

    #if NUM_CHANNELS >= 7
      if ( ledsettings[6].TimeToUpdatePattern() )
      {
        //ledsettings[6].IncrementPatternPosition();
        Strip7.IncrementPatternPosition();
        Strip7.Update();
      }
    #endif

    #if NUM_CHANNELS >= 8
      if ( ledsettings[7].TimeToUpdatePattern() )
      {
        //ledsettings[7].IncrementPatternPosition();
        Strip8.IncrementPatternPosition();
        Strip8.Update();
      }
    #endif

    if ( ledsettings[8].TimeToUpdatePattern() )
    {
      #if NUM_CHANNELS >= 1
        Strip1.Update(); Strip1.IncrementPatternPosition();
      #endif

      #if NUM_CHANNELS >= 2
        Strip2.Update(); Strip2.IncrementPatternPosition();
      #endif

      #if NUM_CHANNELS >= 3
        Strip3.Update(); Strip3.IncrementPatternPosition();
      #endif

      #if NUM_CHANNELS >= 4
        Strip4.Update(); Strip4.IncrementPatternPosition();
      #endif

      #if NUM_CHANNELS >= 5
        Strip5.Update(); Strip5.IncrementPatternPosition();
      #endif

      #if NUM_CHANNELS >= 6
        Strip6.Update(); Strip6.IncrementPatternPosition();
      #endif

      #if NUM_CHANNELS >= 7
        Strip7.Update(); Strip7.IncrementPatternPosition();
      #endif

      #if NUM_CHANNELS >= 8
        Strip8.Update(); Strip8.IncrementPatternPosition();
      #endif
    }

    #if NUM_CHANNELS >= 1
      if ( ledsettings[0].TimeToUpdatePalette() )
      {
        Strip1.IncrementPalettePosition();
      }
    #endif

    #if NUM_CHANNELS >= 2
      if ( ledsettings[1].TimeToUpdatePalette() )
      {
        Strip2.IncrementPalettePosition();
      }
    #endif

    #if NUM_CHANNELS >= 3
      if ( ledsettings[2].TimeToUpdatePalette() )
      {
        Strip3.IncrementPalettePosition();
      }
    #endif

    #if NUM_CHANNELS >= 4
      if ( ledsettings[3].TimeToUpdatePalette() )
      {
        Strip4.IncrementPalettePosition();
      }
    #endif

    #if NUM_CHANNELS >= 5
      if ( ledsettings[4].TimeToUpdatePalette() )
      {
        Strip5.IncrementPalettePosition();
      }
    #endif

    #if NUM_CHANNELS >= 6
      if ( ledsettings[5].TimeToUpdatePalette() )
      {
        Strip6.IncrementPalettePosition();
      }
    #endif

    #if NUM_CHANNELS >= 7
      if ( ledsettings[6].TimeToUpdatePalette() )
      {
        Strip7.IncrementPalettePosition();
      }
    #endif

    #if NUM_CHANNELS >= 8
      if ( ledsettings[7].TimeToUpdatePalette() )
      {
        Strip8.IncrementPalettePosition();
      }
    #endif

    if ( ledsettings[8].TimeToUpdatePalette() )
    {
      #if NUM_CHANNELS >= 1
        Strip1.IncrementPalettePosition();
      #endif

      #if NUM_CHANNELS >= 2
        Strip2.IncrementPalettePosition();
      #endif

      #if NUM_CHANNELS >= 3
        Strip3.IncrementPalettePosition();
      #endif

      #if NUM_CHANNELS >= 4
        Strip4.IncrementPalettePosition();
      #endif

      #if NUM_CHANNELS >= 5
        Strip5.IncrementPalettePosition();
      #endif

      #if NUM_CHANNELS >= 6
        Strip6.IncrementPalettePosition();
      #endif

      #if NUM_CHANNELS >= 7
        Strip7.IncrementPalettePosition();
      #endif

      #if NUM_CHANNELS >= 8
        Strip8.IncrementPalettePosition();
      #endif
    }

    #if NUM_CHANNELS >= 1
      Strip1.controller->show(Strip1._Leds.data(), Strip1._NumLeds, 255);
    #endif

    #if NUM_CHANNELS >= 2
      Strip2.controller->show(Strip2._Leds.data(), Strip2._NumLeds, 255);
    #endif

    #if NUM_CHANNELS >= 3
      Strip3.controller->show(Strip3._Leds.data(), Strip3._NumLeds, 255);
    #endif

    #if NUM_CHANNELS >= 4
      Strip4.controller->show(Strip4._Leds.data(), Strip4._NumLeds, 255);
    #endif

    #if NUM_CHANNELS >= 5
      Strip5.controller->show(Strip5._Leds.data(), Strip5._NumLeds, 255);
    #endif

    #if NUM_CHANNELS >= 6
      Strip6.controller->show(Strip6._Leds.data(), Strip6._NumLeds, 255);
    #endif

    #if NUM_CHANNELS >= 7
      Strip7.controller->show(Strip7._Leds.data(), Strip7._NumLeds, 255);
    #endif

    #if NUM_CHANNELS >= 8
      Strip8.controller->show(Strip8._Leds.data(), Strip8._NumLeds, 255);
    #endif
  }
}

void setup()
{
  Serial.begin(115200);

  debug.clearMonitor();

  debug.text("------------------------------------------------------------------------------------- \n");
  debug.text("- Mythical Neon Controller                                                  Startup - \n");
  debug.text("------------------------------------------------------------------------------------- \n");

  debug.info("[MAIN]", "[INFO]", "Software Version : %u", FLASH_VERSION);
  debug.info("[MAIN]", "[INFO]", "ESP32 Free Memory : %u", ESP.getFreeHeap());
  debug.info("[MAIN]", "[INFO]", "PSRAM : %u", ESP.getPsramSize());
  debug.info("[MAIN]", "[INFO]", "PSRAM Free : %u", ESP.getFreePsram());
  debug.info("[MAIN]", "[INFO]", "ESP32 Clock Freq : %d MHz", ESP.getCpuFreqMHz());
  debug.success("[MAIN]", "[INFO]", "Startup complete!");
  debug.newline();

  debug.text("------------------------------------------------------------------------------------- \n");
  debug.text("- FASTLED                                                                   Startup - \n");
  debug.text("------------------------------------------------------------------------------------- \n");
  #if NUM_CHANNELS >= 1
    debug.info("[FASTLED]", "[SETUP]", "Strip 1 ACTIVE on pin %d with %d/%d LEDs", LED_PIN1, Config[DEVICE].NUMLED[0], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 2
    debug.info("[FASTLED]", "[SETUP]", "Strip 2 ACTIVE on pin %d with %d/%d LEDs", LED_PIN2, Config[DEVICE].NUMLED[1], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 3
    debug.info("[FASTLED]", "[SETUP]", "Strip 3 ACTIVE on pin %d with %d/%d LEDs", LED_PIN3, Config[DEVICE].NUMLED[2], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 4
    debug.info("[FASTLED]", "[SETUP]", "Strip 4 ACTIVE on pin %d with %d/%d LEDs", LED_PIN4, Config[DEVICE].NUMLED[3], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 5
    debug.info("[FASTLED]", "[SETUP]", "Strip 5 ACTIVE on pin %d with %d/%d LEDs", LED_PIN5, Config[DEVICE].NUMLED[4], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 6
    debug.info("[FASTLED]", "[SETUP]", "Strip 6 ACTIVE on pin %d with %d/%d LEDs", LED_PIN6, Config[DEVICE].NUMLED[5], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 7
    debug.info("[FASTLED]", "[SETUP]", "Strip 7 ACTIVE on pin %d with %d/%d LEDs", LED_PIN7, Config[DEVICE].NUMLED[6], LED_AMOUNT_PER_PIN);
  #endif

  #if NUM_CHANNELS >= 8
    debug.info("[FASTLED]", "[SETUP]", "Strip 8 ACTIVE on pin %d with %d/%d LEDs", LED_PIN8, Config[DEVICE].NUMLED[7], LED_AMOUNT_PER_PIN);
  #endif
  debug.newline();

  debug.text("------------------------------------------------------------------------------------- \n");
  debug.text("- RELAY                                                                     Startup - \n");
  debug.text("------------------------------------------------------------------------------------- \n");
  relay::begin();
  debug.newline();

  debug.text("------------------------------------------------------------------------------------- \n");
  debug.text("- NETWORK                                                                   Startup - \n");
  debug.text("------------------------------------------------------------------------------------- \n");

  network::wifi::begin();
  network::ble::begin();
  debug.newline();

  debug.text("------------------------------------------------------------------------------------- \n");
  debug.text("- Websocket                                                                 Startup - \n");
  debug.text("------------------------------------------------------------------------------------- \n");

  websocket::begin();
  debug.newline();

  xTaskCreatePinnedToCore(DrawLoopTaskEntry, "Draw Loop", STACK_SIZE, nullptr, DRAWING_PRIORITY, &g_taskDraw, DRAWING_CORE);
  //xTaskCreatePinnedToCore(NetworkHandlingLoopEntry, "Network Handling Loop", STACK_SIZE, nullptr, NET_PRIORITY, &g_taskNet, NET_CORE);
  xTaskCreatePinnedToCore(SocketServerTaskEntry, "Socket Server Loop", STACK_SIZE, nullptr, SOCKET_PRIORITY, &g_taskSocket, SOCKET_CORE);
}

void loop()
{
  relay::loop();
}