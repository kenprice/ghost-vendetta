#include "globals.h"

#ifndef _GAME_STATE
#define _GAME_STATE

unsigned char game_frame;

game_object objects[BOARD_DIM][BOARD_DIM];

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
} actor_t;

actor_t player;

#endif
