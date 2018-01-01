#include "obstacle.h"
#include "level.h"
#include "globals.h"
#include "bitmap.h"

Obstacle obstacles[MAX_OBSTACLES];

void clearObstacles() {
  for (int i = 0; i < MAX_OBSTACLES; i++) {
    obstacles[i].id = NULL;
    obstacles[i].state = OBS_STATE_UNDAMAGED;
  }
}

void spawnObstacles() {
  clearObstacles();

  for (byte i = 0; i < BOARD_DIM; i++) {
    for (byte j= 0; j < BOARD_DIM; j++) {
      
      byte tile = getTile(i, j);
      byte obstacleType = NULL;
      if (tile == BOULDER_SPAWN) obstacleType = OBS_BOULDER;
      if (tile == SHRUB_SPAWN)   obstacleType = OBS_SHRUB;
      if (!obstacleType) continue;

      int k = 0;
      while (obstacles[k].id != NULL && k < MAX_OBSTACLES) {
        k++;
      }

      if (random(10) <= brickDensity[level-1]) {
        obstacles[k].id = obstacleType;
        obstacles[k].x = i;
        obstacles[k].y = j;
      }
    }
  }
}

void drawObstacles(int posX, int posY) {
  for (int i = 0; i < MAX_OBSTACLES; i++) {
    if (!obstacles[i].id) continue;
    int wx = obstacles[i].x * 16 + CAM_X_OFFSET - posX;
    int wy = obstacles[i].y * 16 + CAM_Y_OFFSET - posY;
  
    switch (obstacles[i].id) {
      case OBS_BOULDER:
        arduboy.drawBitmap(wx, wy, SPRITES + BOULDER_SPRITE_OFFSET, 16, 16, WHITE);
        break;
      case OBS_SHRUB:
        arduboy.drawBitmap(wx, wy, SPRITES + SHRUB_SPRITE_OFFSET, 16, 16, WHITE);
        break;
    }
  }
}

