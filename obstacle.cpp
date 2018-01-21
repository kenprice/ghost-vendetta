#include "obstacle.h"
#include "level.h"
#include "globals.h"
#include "bitmap.h"

Obstacle obstacles[MAX_OBSTACLES];

void clearObstacles() {
  for (byte i = 0; i < MAX_OBSTACLES; i++) {
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

      if (random(10) <= brickDensity[(level-1)%NUM_LEVELS]) {
        obstacles[k].id = obstacleType;
        obstacles[k].x = i;
        obstacles[k].y = j;
      }
    }
  }
}

void updateObstacle(Obstacle& obstacle) {
  if (arduboy.everyXFrames(10) && obstacle.spriteFrame > 0) {
    obstacle.spriteFrame--;
  }
  if (obstacle.state == OBS_STATE_DESTROYED && obstacle.spriteFrame == 0) {
    obstacle.id = NULL;
  }
}

void updateObstacles() {
  for (byte i = 0; i < MAX_OBSTACLES; i++) {
    if (!obstacles[i].id) continue;
    updateObstacle(obstacles[i]);
  }
}

void drawObstacles(int posX, int posY) {
  for (byte i = 0; i < MAX_OBSTACLES; i++) {
    if (!obstacles[i].id) continue;
    char wx = obstacles[i].x * 16 + camera.xOffset - posX;
    char wy = obstacles[i].y * 16 + camera.yOffset - posY;
  
    switch (obstacles[i].id) {
      case OBS_BOULDER:
        arduboy.fillRect(wx, wy, 16, 16, BLACK);
        arduboy.drawBitmap(wx, wy, SPRITES + BOULDER_SPRITE_OFFSET + (obstacles[i].state * SPRITE_COL_OFFSET), 16, 16, WHITE);
        break;
      case OBS_SHRUB:
        arduboy.drawBitmap(wx, wy, SPRITES + SHRUB_SPRITE_OFFSET + (obstacles[i].state == OBS_STATE_DESTROYED ? SPRITE_COL_OFFSET : 0), 16, 16, WHITE);
        break;
    }
  }
}

byte getObstacleType(byte x, byte y) {
  for (byte i = 0; i < MAX_OBSTACLES; i++) {
    if (!obstacles[i].id) continue;
    if (obstacles[i].x == x && obstacles[i].y == y) return obstacles[i].id;
  }
  return NULL;
}

void damageObstacle(byte x, byte y) {
  for (byte i = 0; i < MAX_OBSTACLES; i++) {
    if (!obstacles[i].id || (obstacles[i].x != x || obstacles[i].y != y)) continue;
    if (obstacles[i].id == OBS_SHRUB && obstacles[i].state == OBS_STATE_UNDAMAGED) {
      obstacles[i].state = OBS_STATE_DESTROYED;
      obstacles[i].spriteFrame = 3;
    }
    if (obstacles[i].id == OBS_BOULDER && obstacles[i].state == OBS_STATE_DAMAGED) {
      obstacles[i].state = OBS_STATE_DESTROYED;
      obstacles[i].spriteFrame = 3;
    }
    if (obstacles[i].id == OBS_BOULDER && obstacles[i].state == OBS_STATE_UNDAMAGED) {
      obstacles[i].state = OBS_STATE_DAMAGED;
    }
  }
  return NULL;
}

