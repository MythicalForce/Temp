#pragma once

#include <Arduino.h>
#include "enum.h"

#define COLOR_RESET "\x1B[0m"

#define COLOR_BLACK "\x1B[0;30m"
#define COLOR_RED "\x1B[0;31m"
#define COLOR_GREEN "\x1B[0;32m"
#define COLOR_YELLOW "\x1B[0;33m"
#define COLOR_BLUE "\x1B[0;34m"
#define COLOR_MAGENTA "\x1B[0;35m"
#define COLOR_CYAN "\x1B[0;36m"
#define COLOR_WHITE "\x1B[0;37m"

#define COLOR_DARK_BLACK "\x1B[1;30m"

#define COLOR_LIGHT_RED "\x1B[1;31m"
#define COLOR_LIGHT_GREEN "\x1B[1;32m"
#define COLOR_LIGHT_YELLOW "\x1B[1;33m"
#define COLOR_LIGHT_BLUE "\x1B[1;34m"
#define COLOR_LIGHT_MAGENTA "\x1B[1;35m"
#define COLOR_LIGHT_CYAN "\x1B[1;36m"
#define COLOR_LIGHT_WHITE "\x1B[1;37m"

// used to debug HEAP MEMORY | PSRAM | SKETCH SPACE
//SettingsDebug.LevelInfo("[ESP32]", "[HEAP]", "%d", ESP.getFreeHeap());
//SettingsDebug.LevelInfo("[ESP32]", "[PSRAM]", "%d", ESP.getFreePsram());
//SettingsDebug.LevelInfo("[ESP32]", "[SKETCHSPACE]", "%d", ESP.getFreeSketchSpace());

/**
 * @brief Mythical Debugger
 * @param LevelInfo Print out Information (low level stuff)
 * @param LevelSuccess Print out Successful information (low level stuff)
 * @param LevelWarn Print out Warnings (medium level stuff)
 * @param LevelError Print out Errors (high level stuff)
 */
class Debugger
{
    private:
        E_Level m_LogLevel = INFO;

    public:
        char s[50];
        /**
         * @brief Mythical Debugger
         * @param level NONE | INFO | SUCCESS | WARNING | ERROR
         */
        Debugger(E_Level level): m_LogLevel( level ) {}

        void clearMonitor()
        {
            Serial.write(27);       // ESC command
            Serial.print("[2J");    // clear screen command
            Serial.write(27);
            Serial.print("[H");     // cursor to home command
        }

        void newline()
        {
        if(m_LogLevel >= INFO)
            Serial.printf("\n");
        }

        /**
         * @brief Mythical Debugger
         * @param text In what file/function/class is this debug located
         */
        void text(const char* text)
        {
        if(m_LogLevel >= INFO)
            Serial.printf(COLOR_MAGENTA "%s" COLOR_RESET, text);
        }

        /**
         * @brief Mythical Debugger
         * @param from In what file/function/class is this debug located
         * @param desc A short description of the debug
         * @param format Variables (args)
         */
        void info(const char* from, const char* desc, const char* format, ...)
        {
        va_list args;
        va_start(args, format);
        char buffer[250];
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);

        if(m_LogLevel >= INFO)
            Serial.printf(COLOR_CYAN "[I]%s%s %s \n" COLOR_RESET, from, desc, buffer);
        }
        
        /**
         * @brief Mythical Debugger
         * @param from In what file/function/class is this debug located
         * @param desc A short description of the debug
         * @param format Variables (args)
         */
        void success(const char* from, const char* desc, const char* format, ...)
        {
            va_list args;
            va_start(args, format);
            char buffer[250];
            vsnprintf(buffer, sizeof(buffer), format, args);
            va_end(args);

            if(m_LogLevel >= SUCCESS)
                Serial.printf(COLOR_GREEN "[S]%s%s %s \n" COLOR_RESET, from, desc, buffer);
        }
        /**
         * @brief Mythical Debugger
         * @param from In what file/function/class is this debug located
         * @param desc A short description of the debug
         * @param format Variables (args)
         */
        void warning(const char* from,  const char* desc, const char* format, ...)
        {
            va_list args;
            va_start(args, format);
            char buffer[250];
            vsnprintf(buffer, sizeof(buffer), format, args);
            va_end(args);

            if(m_LogLevel >= WARNING)
                Serial.printf(COLOR_YELLOW "[W]%s%s %s \n" COLOR_RESET, from, desc, buffer);
        }
        /**
         * @brief Mythical Debugger
         * @param from In what file/function/class is this debug located
         * @param desc A short description of the debug
         * @param format Variables (args)
         */
        void error(const char* from, const char* desc, const char* format, ...)
        {
            va_list args;
            va_start(args, format);
            char buffer[250];
            vsnprintf(buffer, sizeof(buffer), format, args);
            va_end(args);

            if(m_LogLevel >= ERROR)
                Serial.printf(COLOR_RED "[E]%s%s %s \n" COLOR_RESET, from, desc, buffer);
        }
};