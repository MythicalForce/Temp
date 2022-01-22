#pragma once

#include <debugger.h>

#define DEVICE TESTMACHINE                                 // What device to upload to

#define FLASH_VERSION 0001                                  // Upate ONLY this to increment the version number

#if defined(DEVICE) && DEVICE != COMPUTERDESK
    #define LED_PIN1 23                                     // PIN 1
    #define LED_PIN2 16                                     // PIN 2
    #define LED_PIN3 17                                     // PIN 3
    #define LED_PIN4 18                                     // PIN 4
    #define LED_PIN5 19                                     // PIN 5
    #define LED_PIN6 21                                     // PIN 6
    #define LED_PIN7 22                                     // PIN 7
    #define LED_PIN8 15                                     // PIN 8
#else
    #define LED_PIN1 15                                     // PIN 1
    #define LED_PIN2 16                                     // PIN 2
    #define LED_PIN3 17                                     // PIN 3
    #define LED_PIN4 18                                     // PIN 4
    #define LED_PIN5 19                                     // PIN 5
    #define LED_PIN6 21                                     // PIN 6
    #define LED_PIN7 22                                     // PIN 7
    #define LED_PIN8 23                                     // PIN 8
#endif

#define NUM_CHANNELS 8                                      // how many channels are on the board (1 to 8)

#define LED_AMOUNT_PER_PIN 300                              // Pre set amount of LED`s per pin

#define ARRAYSIZE(a)		(sizeof(a)/sizeof(a[0]))		// Returns the number of elements in an array
#define PERIOD_FROM_FREQ(f) (round(1000000 * (1.0 / f)))	// Calculate period in microseconds (us) from frequency in Hz
#define FREQ_FROM_PERIOD(p) (1.0 / p * 1000000)				// Calculate frequency in Hz given the priod in microseconds (us)

#define STACK_SIZE (ESP_TASK_MAIN_STACK)

#define DRAWING_PRIORITY        tskIDLE_PRIORITY+3
#define SOCKET_PRIORITY         tskIDLE_PRIORITY+2
#define NET_PRIORITY            tskIDLE_PRIORITY+2

#define DRAWING_CORE            1
#define NET_CORE                0
#define SOCKET_CORE             0

#define FASTLED_INTERNAL 1                                  // Silence FastLED build banners

#define WIFI_LED_PIN     32                                 // WiFi LED PIN

#define RELAY_PIN        33                                 // Relay PIN

#define ENABLE_WIFI      1                                  // Connect to WiFi
#define ENABLE_BLE       0                                  // Connect to Bluetooth
#define ENABLE_OTA       0                                  // Accept over the air flash updates
#define MSGPACK_DEBUGLOG_ENABLE 0                           // Enable msgpack debuglog

Debugger debug( ERROR );                                    // Let everyone in the project know about it.  If you don't have it, delete this