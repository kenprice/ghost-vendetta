#ifndef _BRICK
#define _BRICK
#include "level.h"

extern byte bricks[NUM_LEVEL_TILES/8];

void generateBricks();

bool isBrick(unsigned int posX, unsigned int posY);

void setBrick(unsigned int posX, unsigned int posY, bool placeBrick);

void drawBricks(int posX, int posY);
#endif
