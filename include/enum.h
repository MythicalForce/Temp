#pragma once

enum E_Device
{
    STUDIOLIGHTS,
    NEONHEAVEN,
    VITRINESKAP,
    THESUN,
    VOODOOMASK,
    SMASURE,
    TESTMACHINE,
    COMPUTERDESK,
    HAALANDSMARKA,
    SMOKEMACHINE
};

enum E_Patterns
{
    SOLIDCOLOR = 0,
    THEATHERCHASE = 1,
    JUGGLE = 2,
    RUNNINGLIGHT = 3,
    CYLON = 4,
    MITOSIS = 5,
    TWINKLE = 6,
    COLORSTACKING = 7
};
enum E_Direction
{
    FORWARD = 1,
    REVERSE = 0,
};
enum E_WrapAround
{
    NO = 0,
    YES = 1
};
enum E_Tail
{
    DUST  = 1,
    SOLID = 2
};
enum E_ColorMode
{
    COLOR    = 1,
    FADE     = 2,
    GRADIENT = 3,
    RAINBOW  = 4
};
enum E_Color
{
    RED = 0,
    ORANGE = 32,
    YELLOW = 64,
    GREEN = 96,
    AQUA = 128,
    BLUE = 160,
    PURPLE = 192,
    PINK = 224
};

enum E_Level
{
    NONE = 0,
    INFO = 1,
    SUCCESS = 2,
    WARNING = 3,
    ERROR = 4
};

enum E_Palette
{
    palSUNSETREAL = 1,
    palSUMMERSUNSET =2,
    palRAINBOW = 3,
    palCHRISTMASCANDY = 4,
    palDARKSPACE = 5,
    palDEEPOCEAN = 6,
    palFIRE = 7,
    palBHW128 = 8,
    palBHW119 = 9,
    palBHW222 = 10,
    palGREENMAN = 11,
    palBHW102 = 12,
    palBHW113 = 13
};

enum E_PaletteMode
{
    ONECOLOR = 1,
    FULLPALETTE = 2,
    FULLPALETTEMOVING = 3
};

enum E_GameState
{
    GAME_START,
    GAME_RUNNING,
    GAME_FINISHED,
    GAME_WINNER
};

enum E_GameType
{
    GAME_PICKASTRIP,
    GAME_HORSERACE,
    GAME_COLORTETRIS
};
enum E_LEDBlinkRate
{
    CONNECTING = 1000,
    SETUPMODE = 1000
};