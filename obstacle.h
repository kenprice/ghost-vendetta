#ifndef _OBSTACLE
#define _OBSTACLE

#include <Arduino.h>

/*********************************************************************************
 * Obstacles
 * Special objects that aren't bricks. Can be destructable.
 * 
 * Shrubs - Snakes can walk through it. Bombs blasts can go through it. Character cannot.
 * Boulder - Solid, like brick. But can take two hits before destroyed.
 *********************************************************************************/

// constants /////////////////////////////////////////////////////////////////
#define MAX_OBSTACLES 20
#define OBS_SHRUB     1
#define OBS_BOULDER   2

#define OBS_STATE_UNDAMAGED 0
#define OBS_STATE_DAMAGED   1
#define OBS_STATE_DESTROYED 2

// structures ////////////////////////////////////////////////////////////////
typedef struct {
  byte id : 4;
  byte x : 4;
  byte y : 4;
  byte state : 2;
  byte spriteFrame : 2;     // Sprite frame for animations
} Obstacle;

// globals ///////////////////////////////////////////////////////////////////
extern Obstacle obstacles[MAX_OBSTACLES];

// functions /////////////////////////////////////////////////////////////////
void spawnObstacles();
void updateObstacles();
void drawObstacles(int posX, int posY);
byte getObstacleType(byte x, byte y);
void damageObstacle(byte x, byte y);

#endif
