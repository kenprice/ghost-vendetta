#include "globals.h"

Arduboy2Base arduboy;
ArduboyTones sound(arduboy.audio.enabled);
byte gameState = STATE_MENU_MAIN;

byte gameFrame;
