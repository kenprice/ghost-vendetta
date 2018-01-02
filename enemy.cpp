#include "enemy.h"
#include "player.h"
#include "level.h"
#include "brick.h"
#include "bitmap.h"
#include "globals.h"
#include "collision.h"
#include "obstacle.h"

Enemy enemies[MAX_ENEMIES];

typedef void (*FunctionPointer) (Enemy& enemy);
const FunctionPointer PROGMEM enemyUpdates[] =
{
  updateSnake,
  updateHardSnake
};

void clearEnemies() {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    enemies[i].active = false;
    enemies[i].id = ENEMY_SNAKE;
  }
}

void setEnemy(Enemy& enemy, byte x, byte y, byte id) {
  enemy.x = x;
  enemy.y = y;
  enemy.active = true;
  enemy.state = ENEMY_STATE_STOPPED;
  enemy.id = id;
}

/**
 * Add new enemy at tile coordinates
 */
bool addEnemy(byte x, byte y, byte id) { 
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemies[i].active) continue;
    setEnemy(enemies[i], x * 16, y * 16, id);
    return true;
  }

  return false;
}

/**
 * Kill all enemies at the tile coordinates
 */
void killEnemiesAt(byte x, byte y) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!enemies[i].active) continue;
    if (collidedWith(enemies[i].x, enemies[i].y, x * 16, y * 16, 3)) {
      enemies[i].active = false;
    }
  }
}

bool spawnEnemy(byte id) {
  if (id == NULL) return true;

  byte x;
  byte y;
  byte tile;
  bool nearPlayer;

  do {
    x = random(0, BOARD_DIM);
    y = random(0, BOARD_DIM);
    tile = getTile(x, y);
    nearPlayer = x <= player.x / 16 + 1 && x >= player.x / 16 - 1 && y <= player.y / 16 + 1 && y >= player.y / 16 - 1;
  } while ((tile != FLOOR && tile != BRICK_SPAWN) || isBrick(x, y) || nearPlayer);

  return addEnemy(x, y, id);
}

void spawnEnemies() {
  clearEnemies();
  for (int i = 0; i < MAX_ENEMIES; i++) {
    //Serial.println(pgm_read_byte(&enemySpawns[level-1][i]));
    spawnEnemy(pgm_read_byte(&enemySpawns[level-1][i]));
  }
}

void drawEnemies() {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!enemies[i].active) continue;
    int wx = enemies[i].x + CAM_X_OFFSET - player.x;
    int wy = enemies[i].y + CAM_Y_OFFSET - player.y;

    // TODO: Account for different enemy sizes in the future
    int smallEnemyPadding = 4;
    switch (enemies[i].id) {
      case ENEMY_HARD_SNAKE:
      case ENEMY_SNAKE:
        arduboy.drawBitmap(wx + smallEnemyPadding, wy + smallEnemyPadding, SPRITES_8 + SNAKE_SPRITE_OFFSET + ((gameFrame / 20 % 2) ? 0 : SPRITE_8_COL_OFFSET), 8, 8, WHITE);
        break;
    }
  }
}

/**
 * Checks if enemy collided with a solid object
 */
bool enemyCheckCollision(Enemy enemy, int dx, int dy) {
  int x = enemy.x;
  int y = enemy.y;
  int startX = enemy.x / 16 - 1 < 0 ? 0 : enemy.x / 16 - 1;
  int startY = enemy.y / 16 - 1 < 0 ? 0 : enemy.y / 16 - 1;
  int endX = enemy.x / 16 + 1 > BOARD_DIM - 1 ? BOARD_DIM - 1 : enemy.x / 16 + 1;
  int endY = enemy.y / 16 + 1 > BOARD_DIM - 1 ? BOARD_DIM - 1 : enemy.y / 16 + 1;

  for (byte i = startX; i <= endX; i++) {
    for (byte j = startY; j <= endY; j++) {
      bool isSnakeAndBoulder = getObstacleType(i, j) == OBS_BOULDER && enemy.id == ENEMY_SNAKE;
      if (collidedWith(enemy.x, enemy.y, i * 16, j * 16, 3) && (getTile(i, j) == WALL || isBrick(i, j) || isSnakeAndBoulder)) {
        return true;
      }
      if (collidedWith(enemy.x, enemy.y, player.x, player.y, 3)) {
        damagePlayer();
      }
    }
  }
  return false;
}

void updateSnakeBase(Enemy& enemy) {
  if (enemy.state == ENEMY_STATE_MOVING) {
    int dx = 0;
    int dy = 0;
    if (enemy.direction == ENEMY_FACING_EAST)  dx = 1;
    if (enemy.direction == ENEMY_FACING_WEST)  dx = -1;
    if (enemy.direction == ENEMY_FACING_SOUTH) dy = 1;
    if (enemy.direction == ENEMY_FACING_NORTH) dy = -1;

    enemy.x += dx;
    enemy.y += dy;
    
    if (enemyCheckCollision(enemy, dx, dy)) {
      enemy.state = ENEMY_STATE_STOPPED;
      enemy.x -= dx;
      enemy.y -= dy;
      return;
    }

    if ((enemy.x + 4) % 16 == 0 || (enemy.y + 4) % 16 == 0) {
      enemy.state = ENEMY_STATE_STOPPED;
    }
  }
}

void updateSnake(Enemy& enemy) {
  if (!arduboy.everyXFrames(10)) return;
  updateSnakeBase(enemy);
  if (enemy.state != ENEMY_STATE_STOPPED) return;
  enemy.direction = random(4);
  enemy.state = ENEMY_STATE_MOVING;
}

void updateHardSnake(Enemy& enemy) {
  if (!arduboy.everyXFrames(5)) return;
  updateSnakeBase(enemy);
  if (enemy.state != ENEMY_STATE_STOPPED) return;
  char dx = (player.x / 16) - (enemy.x / 16);
  char dy = (player.y / 16) - (enemy.y / 16);

  enemy.state = ENEMY_STATE_MOVING;

  if (dx > 0) {
    enemy.direction = ENEMY_FACING_EAST;
  }
  if (dx < 0) {
    enemy.direction = ENEMY_FACING_WEST;
  }
  if (dx != 0 && enemyCheckCollision(enemy, enemy.x + dx, enemy.y)) {
    enemy.direction = random(4);
    return;
  }
  
  if (dy > 0) {
    enemy.direction = ENEMY_FACING_SOUTH;
  }
  if (dy < 0) {
    enemy.direction = ENEMY_FACING_NORTH;
  }
  if (dy != 0 && enemyCheckCollision(enemy, enemy.x, enemy.y + dy)) {
    enemy.direction = random(4);
  }
}

void updateEnemies() {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!enemies[i].active || enemies[i].id < 1) continue;
    ((FunctionPointer) pgm_read_word (&enemyUpdates[enemies[i].id-1]))(enemies[i]);
  }
}

