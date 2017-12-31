#ifndef _OBSTACLE
#define _OBSTACLE

#include <Arduino.h>

/*********************************************************************************
 * Obstacles
 * Special objects that aren't bricks. Can be destructable.
 *********************************************************************************/

// constants /////////////////////////////////////////////////////////////////
#define MAX_OBSTACLES 10
#define OBS_SHRUB     1
#define OBS_BOULDER   2

// structures ////////////////////////////////////////////////////////////////
typedef enum ObstacleState{ OBS_STATE_UNDAMAGED, OBS_STATE_DAMAGED, OBS_STATE_DESTROYED };

typedef struct {
  byte id;
  byte x;
  byte y;
  ObstacleState state;
} Obstacle;

// globals ///////////////////////////////////////////////////////////////////
extern Obstacle obstacles[MAX_OBSTACLES];

// functions /////////////////////////////////////////////////////////////////
void spawnObstacles();

#endif
