#ifndef _BRICK
#define _BRICK
#include "level.h"

// constants /////////////////////////////////////////////////////////////////
#define MAX_DESTROYED_BRICKS  10

// structures ////////////////////////////////////////////////////////////////
typedef struct {
  int lifetime;
  byte x;
  byte y;
  bool active;
} DestroyedBrick;

// globals ///////////////////////////////////////////////////////////////////
extern byte bricks[NUM_LEVEL_TILES/8];
extern DestroyedBrick destroyedBricks[MAX_DESTROYED_BRICKS];

// functions /////////////////////////////////////////////////////////////////
void generateBricks();
bool isBrick(unsigned int posX, unsigned int posY);
void updateBricks();
void setBrick(unsigned int posX, unsigned int posY, bool placeBrick);
void drawBricks(int posX, int posY);
void addDestroyedBrick(byte x, byte ysY);
bool isDestroyedBrick(byte x, byte y);
#endif
