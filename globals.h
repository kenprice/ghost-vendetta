#define BOARD_DIM 7

#ifndef _GLOBALS
#define _GLOBALS

const unsigned char FIRE = 1;
const unsigned char EXPLOSION = 2;
const unsigned char WALL = 10;
const unsigned char BRICK = 11;

typedef struct {
  unsigned char id;
  unsigned char lifetime;
} game_object;
#endif
