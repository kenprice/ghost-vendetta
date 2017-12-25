#ifndef _GAME_STATE
#define _GAME_STATE
#include <Arduino.h>
#include "globals.h"

#define BOARD_DIM 7
#define FIRE 1
#define EXPLOSION 2
#define WALL 10
#define BRICK 11

extern byte level;
extern byte displayLevel;

extern unsigned char game_frame;

typedef struct {
  unsigned char id;
  unsigned char lifetime;
} GameObject;

extern GameObject gameObjects[BOARD_DIM][BOARD_DIM];

enum alive_state { ALIVE, DYING };

typedef struct {
  int x;
  int y;
  int last_x;
  int last_y;
  int dx;
  int dy;
  unsigned char frame;
  enum alive_state state;
} Actor;

extern Actor player;

void stateGamePrepareLevel();
void stateGameNextLevel();
void stateGamePlaying();
#endif
