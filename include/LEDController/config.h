#pragma once

#include "enum.h"

struct DeviceConfig
{
    int NUMLED[9];
    const char *Device_Name;
    const char *Device_Type;
    const char *LED_Type;
    const char *Wifi_DNS;
};

static constexpr DeviceConfig Config[] =
{
    { {199,4,4,4,4,4,4,4},        "Studio Lights", "ESP32", "STRIP", "studiolights" },
    { {32,32,32,32,32,32,32,32},  "Neon Heaven",   "ESP32", "STRIP", "neonheaven" },
    { {28,28,28,28,28,28,28,28},  "Vitrineskap",   "ESP32", "STRIP", "vitrineskap" },
    { {70,70,70,70,70,70,70,70},  "The Sun",       "ESP32", "STRIP", "thesun" },
    { {19,18,10,10,10,10,19,18},  "Voodoo Mask",   "ESP32", "STRIP", "voodoomask" },
    { {4,4,4,4,4,4,4,4},          "Små Sure",      "ESP32", "STRIP", "smasure" },
    { {96,96,96,96,96,96,96,96},  "Test Device",   "ESP32", "STRIP", "testmachine" },
    { {186,186,186,186,186,186,186,186}, "Computer Desk", "ESP32", "STRIP", "computerdesk" },
    { {72,32,96,32,32,32,32,32},  "HaalandsMarka", "ESP32", "STRIP", "haalandsmarka" },
    { {45,4,4,4,4,4,4,4},         "Røyk Maskin",   "ESP32", "STRIP", "smokemachine" }
};