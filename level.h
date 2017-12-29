#ifndef _LEVEL_H_
#define _LEVEL

#include <Arduino.h>

// constants /////////////////////////////////////////////////////////////////
#define FLOOR         0x01        // Walkable floor tile
#define BRICK_SPAWN   0x09        // Tile that spawns bricks at beginning of level
#define WALL          0x0A

#define BLOCK_DIM         4       // Block dimensions = n where blocks have n*n tiles
#define MAP_DIM           4       // Map dimensions = n where maps have n*n blocks
#define NUM_LEVEL_TILES   256     // Number of possible tiles per level
#define BOARD_DIM         (BLOCK_DIM * MAP_DIM)

// globals ///////////////////////////////////////////////////////////////////
extern byte level;
extern PROGMEM const byte blocks[][16];
extern PROGMEM const byte maps[][MAP_DIM*MAP_DIM];
extern PROGMEM const byte itemSpawnLocations[][10];

// functions /////////////////////////////////////////////////////////////////
byte getTile(unsigned int posX, unsigned int posY);
void drawLevel(int posX, int posY);

#endif
