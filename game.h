#ifndef _GAME_STATE
#define _GAME_STATE
#include <Arduino.h>
#include "globals.h"

void stateGamePrepareLevel();
void stateGameNextLevel();
void stateGamePlaying();
void stateGameOver();
#endif
