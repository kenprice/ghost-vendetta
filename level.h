#ifndef _LEVEL_H_
#define _LEVEL

#include <Arduino.h>
#define TILE_BLANK = 0
#define TILE_WALL = 1

#define NULL 0
#define FIRE 1
#define EXPLOSION 2

#define BRICK_SPAWN 0x09        // Tile that spawns bricks at beginning of level
#define WALL        0x0A
#define BRICK       0x0B

#define BLOCK_DIM 4             // Block dimensions = n where blocks have n*n tiles
#define MAP_DIM 8               // Map dimensions = n where maps have n*n blocks
#define NUM_LEVEL_TILES 1024    // Number of possible tiles per level
#define BOARD_DIM (BLOCK_DIM * MAP_DIM)

extern byte level;

byte getTile(unsigned int posX, unsigned int posY);

void drawLevel(int posX, int posY);

extern PROGMEM const byte blocks[10][16];

extern PROGMEM const byte maps[][MAP_DIM*MAP_DIM];
#endif
