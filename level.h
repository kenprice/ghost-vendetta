#ifndef _LEVEL_H_
#define _LEVEL

#include <Arduino.h>
#define TILE_BLANK = 0
#define TILE_WALL = 1

#define BOARD_DIM 7
#define FIRE 1
#define EXPLOSION 2
#define WALL 10
#define BRICK 11

extern byte level;
extern byte displayLevel;

typedef struct {
  unsigned char id;
  unsigned char lifetime;
  unsigned int x;
  unsigned int y;
} GameObject;

extern GameObject gameObjects[BOARD_DIM][BOARD_DIM];

#endif
