#pragma once

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <globals.h>
#include <secrets.h>
#include "BluetoothSerial.h"
#include "LEDController/config.h"

namespace network
{
    #if ENABLE_WIFI
    namespace wifi
    {
        void begin()
        {
            pinMode( WIFI_LED_PIN, OUTPUT );

            WiFi.mode( WIFI_STA );
            WiFi.setSleep ( false );

            WiFi.setHostname( Config[DEVICE].Wifi_DNS );

            WiFi.begin( WIFI_SSID, WIFI_PASS );

            for (uint iPass = 0; iPass < 10; iPass++)
            {
                if( WiFi.status() == WL_CONNECTED )
                {
                    debug.success("[NETWORK]", "[WIFI]", "WiFi Online!");
                    debug.info("[NETWORK]", "[WIFI]", "IP : %s", WiFi.localIP().toString().c_str());
                    debug.info("[NETWORK]", "[WIFI]", "Hostname : %s", WiFi.getHostname());
                    digitalWrite( WIFI_LED_PIN, HIGH );
                    break;
                }
                else
                {
                    delay( 500 );
                    digitalWrite( WIFI_LED_PIN, HIGH );
                    delay ( 500 );
                    digitalWrite( WIFI_LED_PIN, LOW );
                }
            }            
        }
    }
    #endif

    namespace ble
    {

        #if ENABLE_BLE
        #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
        #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
        #endif

        BluetoothSerial BLE_SERIAL;
        #endif

        void begin()
        {
            #if ENABLE_BLE
            if( BLE_SERIAL.begin(BLE_HOSTNAME) )
            {
                debug.info("[NETWORK]", "[BLE]", "Online");
            }
            #endif
        }
        void loop()
        {
            #if ENABLE_BLE
            if (Serial.available())
            {
                BLE_SERIAL.write(Serial.read());
            }
            if (BLE_SERIAL.available())
            {
                Serial.write(BLE_SERIAL.read());
            }
            #endif
        }
    }
    
}