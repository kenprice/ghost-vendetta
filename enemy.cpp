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
  updateGenericEnemy,
  updateHardSnake,
  updateSlime,
  updateGenericEnemy,
  updateZombie
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
int addEnemy(byte x, byte y, byte id) { 
  if (isBrick(x, y) || getObstacleType(x, y)) return false;

  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (enemies[i].active) continue;
    setEnemy(enemies[i], x * 16, y * 16, id);
    return i;
  }

  return -1;
}

/**
 * Kill all enemies at the tile coordinates
 */
void killEnemiesAt(byte x, byte y) {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!enemies[i].active || enemies[i].state == ENEMY_STATE_FLASHING) continue;
    if (collidedWith(enemies[i].x, enemies[i].y, x * 16, y * 16, 3)) {
      enemies[i].state = ENEMY_STATE_KILLED;
    }
  }
}

void spawnEnemy(byte id) {
  if (id == NULL) return;

  byte x;
  byte y;
  byte tile;
  bool nearPlayer;

  do {
    x = random(0, BOARD_DIM);
    y = random(0, BOARD_DIM);
    tile = getTile(x, y);
    nearPlayer = x <= player.x / 16 + 1 && x >= player.x / 16 - 1 && y <= player.y / 16 + 1 && y >= player.y / 16 - 1;
  } while ((tile != FLOOR && tile != BRICK_SPAWN) || isBrick(x, y) || getObstacleType(x, y) || nearPlayer);

  addEnemy(x, y, id);
}

void spawnEnemies() {
  clearEnemies();
  for (int i = 0; i < MAX_INIT_ENEMIES; i++) {
    spawnEnemy(pgm_read_byte(&enemySpawns[level-1][i]));
  }
}

void drawEnemies() {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!enemies[i].active) continue;
    int wx = enemies[i].x + camera.xOffset - player.x;
    int wy = enemies[i].y + camera.yOffset - player.y;

    int smallEnemyPadding = 4;
    switch (enemies[i].id) {
      case ENEMY_HARD_SNAKE:
      case ENEMY_SNAKE:
        arduboy.drawBitmap(
          wx + smallEnemyPadding,
          wy + smallEnemyPadding,
          SPRITES_8 + SNAKE_SPRITE_OFFSET + ((gameFrame / 20 % 2) ? 0 : SPRITE_8_COL_OFFSET),
          8,
          8,
          WHITE
        );
        break;
      case ENEMY_SLIME:
        ardbitmap.drawBitmap(
          wx + smallEnemyPadding,
          wy + smallEnemyPadding,
          SPRITES_8 + SLIME_SPRITE_OFFSET + (enemies[i].direction == ENEMY_FACING_NORTH ? SPRITE_8_COL_OFFSET : 0),
          8,
          8,
          WHITE,
          ALIGN_NONE,
          (gameFrame / 20 % 2) ? MIRROR_HORIZONTAL : MIRROR_NONE
        );
        break;
      case ENEMY_SLIME_CHILD:
        ardbitmap.drawBitmap(
          wx + smallEnemyPadding + ((gameFrame / 40 % 2) ? random(2) - 1 : 0),
          wy + smallEnemyPadding + ((gameFrame / 40 % 2) ? random(2) - 1 : 0),
          SPRITES_8 + SLIME_CHILD_SPRITE_OFFSET,
          8,
          8,
          WHITE,
          ALIGN_NONE,
          MIRROR_NONE
        );
        break;
      case ENEMY_ZOMBIE:
        // Invisible unless near player
        bool isNearPlayer = enemies[i].x < player.x - 32 + 80 &&
            enemies[i].x + 8 > player.x - 32 &&
            enemies[i].y < player.y - 32 + 80 &&
            8 + enemies[i].y > player.y - 32;

        if (!isNearPlayer) continue;

        ardbitmap.drawBitmap(
          wx + smallEnemyPadding,
          wy + smallEnemyPadding,
          SPRITES_8 + ZOMBIE_SPRITE_OFFSET + ((gameFrame / 20 % 3) * SPRITE_8_COL_OFFSET),
          8,
          8,
          WHITE,
          ALIGN_NONE,
          enemies[i].direction == ENEMY_FACING_EAST ? MIRROR_HORIZONTAL : MIRROR_NONE
        );
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
      bool isSnakeAndBoulder = getObstacleType(i, j) == OBS_BOULDER && (enemy.id == ENEMY_SNAKE || enemy.id == ENEMY_HARD_SNAKE);
      if (collidedWith(enemy.x, enemy.y, i * 16, j * 16, 3) && (getTile(i, j) == WALL || isBrick(i, j) || isSnakeAndBoulder)) {
        return true;
      }
      if (collidedWith(enemy.x, enemy.y, player.x, player.y, 5)) {
        damagePlayer();
      }
    }
  }
  return false;
}

void updateEnemyBase(Enemy& enemy) {
  if (enemy.state == ENEMY_STATE_FLASHING) {
    enemy.flashFrame--;
    if (enemy.flashFrame <= 0) {
      enemy.state = ENEMY_STATE_STOPPED;
    }
  }
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

void updateGenericEnemy(Enemy& enemy) {
  if (!arduboy.everyXFrames(10)) return;
  if (enemy.state == ENEMY_STATE_KILLED) {
    enemy.active = false;
    return;
  }
  updateEnemyBase(enemy);
  if (enemy.state != ENEMY_STATE_STOPPED) return;
  enemy.direction = random(4);
  enemy.state = ENEMY_STATE_MOVING;
}

void updateEnemyPathfindMove(Enemy& enemy) {
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

void updateHardSnake(Enemy& enemy) {
  if (!arduboy.everyXFrames(5)) return;
  if (enemy.state == ENEMY_STATE_KILLED) {
    enemy.active = false;
    return;
  }
  updateEnemyBase(enemy);
  if (enemy.state != ENEMY_STATE_STOPPED) return;
  updateEnemyPathfindMove(enemy);
}

void spawnChildSlimes(Enemy enemy, int numSpawns) {
  for (int i = 0; i < numSpawns; i++) {
    int j = addEnemy(enemy.x / 16, enemy.y / 16, ENEMY_SLIME_CHILD);
    enemies[j].x = enemy.x;
    enemies[j].y = enemy.y;
    enemies[j].state = ENEMY_STATE_FLASHING;
    enemies[j].flashFrame = ENEMY_FLASHING_FRAMES;
  }
}

void updateSlime(Enemy& enemy) {
  if (!arduboy.everyXFrames(5)) return;
  if (enemy.state == ENEMY_STATE_KILLED) {
    spawnChildSlimes(enemy, 2);
    enemy.active = false;
    return;
  }
  updateEnemyBase(enemy);
  if (enemy.state != ENEMY_STATE_STOPPED) return;
  updateEnemyPathfindMove(enemy);
}

void updateZombie(Enemy& enemy) {
  if (!arduboy.everyXFrames(3)) return;
  if (enemy.state == ENEMY_STATE_KILLED) {
    enemy.active = false;
    return;
  }
  updateEnemyBase(enemy);
  if (enemy.state != ENEMY_STATE_STOPPED) return;
  enemy.direction = random(4);
  if (enemy.direction == random(4)) {
    updateEnemyPathfindMove(enemy);
  }
  enemy.state = ENEMY_STATE_MOVING;
}

void updateEnemies() {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!enemies[i].active || enemies[i].id < 1) continue;
    ((FunctionPointer) pgm_read_word (&enemyUpdates[enemies[i].id-1]))(enemies[i]);
  }
}

