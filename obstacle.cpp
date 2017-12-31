#include "obstacle.h"
#include "level.h"

Obstacle obstacles[MAX_OBSTACLES];

void clearObstacles() {
  for (int i = 0; i < MAX_OBSTACLES; i++) {
    obstacles[i].id = NULL;
    obstacles[i].state = OBS_STATE_UNDAMAGED;
  }
}

void spawnShrub(byte x, byte y) {
  int i = 0;
  while (obstacles[i].id && i < MAX_OBSTACLES) {
    i++;
  }
  obstacles[i].id = OBS_SHRUB;
  obstacles[i].x = x;
  obstacles[i].y = y;
}

void spawnBoulder(byte x, byte y) {
  int i = 0;
  while (obstacles[i].id && i < MAX_OBSTACLES) {
    i++;
  }
  obstacles[i].id = OBS_BOULDER;
  obstacles[i].x = x;
  obstacles[i].y = y;
}

void spawnObstacles() {
  clearObstacles();
  for (byte i = 0; i < BOARD_DIM; i++) {
    for (byte j= 0; j < BOARD_DIM; j++) {
      if (getTile(i, j) != BOULDER_SPAWN && getTile(i, j) != SHRUB_SPAWN) continue;
      switch (getTile(i, j)) {
        case BOULDER_SPAWN: spawnShrub(i, j);    break;
        case SHRUB_SPAWN:   spawnBoulder(i, j);  break;
      }
    }
  }
}

