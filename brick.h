#ifndef _BRICK
#define _BRICK
#include "level.h"

// constants /////////////////////////////////////////////////////////////////
#define MAX_DESTROYED_BRICKS  10

// structures ////////////////////////////////////////////////////////////////
typedef struct {
  byte lifetime : 4;
  byte x : 4;
  byte y : 4;
  bool active : 4;
} DestroyedBrick;

// globals ///////////////////////////////////////////////////////////////////
extern byte bricks[NUM_LEVEL_TILES/8];
extern DestroyedBrick destroyedBricks[MAX_DESTROYED_BRICKS];

// functions /////////////////////////////////////////////////////////////////
void generateBricks();
bool isBrick(byte x, byte y);
void updateBricks();
void setBrick(byte x, byte y, bool placeBrick);
void drawBricks(int posX, int posY);
bool destroyBrick(byte x, byte y);
void addDestroyedBrick(byte x, byte ysY);
bool isDestroyedBrick(byte x, byte y);
#endif
