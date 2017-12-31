#include "globals.h"

Arduboy2Base arduboy;
ArduboyTones sound(arduboy.audio.enabled);
ArdBitmap<WIDTH, HEIGHT> ardbitmap;
byte gameState = STATE_MENU_MAIN;

unsigned char game_frame;
