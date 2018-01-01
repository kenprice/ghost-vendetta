#ifndef _OBSTACLE
#define _OBSTACLE

#include <Arduino.h>

/*********************************************************************************
 * Obstacles
 * Special objects that aren't bricks. Can be destructable.
 *********************************************************************************/

// constants /////////////////////////////////////////////////////////////////
#define MAX_OBSTACLES 32
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
  byte state : 4;
} Obstacle;

// globals ///////////////////////////////////////////////////////////////////
extern Obstacle obstacles[MAX_OBSTACLES];

// functions /////////////////////////////////////////////////////////////////
void spawnObstacles();
void drawObstacles(int posX, int posY);

#endif
