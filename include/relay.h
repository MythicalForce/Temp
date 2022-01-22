#pragma once

#include <Arduino.h>
#include "globals.h"

namespace relay
{
    bool enableRelay = false;

    void begin()
    {
        pinMode(RELAY_PIN, OUTPUT);
        debug.success("[RELAY]", "[SETUP]", "Setting pinMode to Output on pin %d", RELAY_PIN);
    }

    void loop()
    {
        if ( enableRelay == true )
        {
            digitalWrite(RELAY_PIN, HIGH);
        }
        else
        {
            digitalWrite(RELAY_PIN, LOW);
        }
    }
};