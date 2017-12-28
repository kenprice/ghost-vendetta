#include "enemy.h"
#include "player.h"
#include "level.h"
#include "brick.h"
#include "bitmap.h"
#include "globals.h"

#include <Arduboy2.h>
Arduboy2 arduboy2;

Enemy enemies[ENEMIES_MAX];

typedef void (*FunctionPointer) (Enemy& enemy);
const FunctionPointer PROGMEM enemyUpdates[] =
{
  updateSnake
};

void setEnemy(Enemy& enemy, byte x, byte y) {
  enemy.x = x;
  enemy.y = y;
  enemy.active = true;
  enemy.state = ENEMY_STATE_STOPPED;
}

/**
 * Add new enemy at tile coordinates
 */
bool addEnemy(byte x, byte y) { 
  for (int i = 0; i < ENEMIES_MAX; i++) {
    if (enemies[i].active) continue;
    setEnemy(enemies[i], x * 16, y * 16);
    return true;
  }

  return false;
}

bool spawnEnemy() {
  byte x;
  byte y;
  byte tile;

  do {
    x = random(0, BOARD_DIM);
    y = random(0, BOARD_DIM);
    tile = getTile(x, y);
  } while ((tile != FLOOR && tile != BRICK_SPAWN) || isBrick(x, y));

  if ((x < player.x / 16) || (x > player.x / 16) || (y < player.y / 16) || (y > player.y / 16))
  {
    return addEnemy(x, y);
  }

  return false;
}

void drawEnemies() {
  int cam_x_offset = 128/2-8;
  int cam_y_offset = 64/2-8;

  for (int i = 0; i < ENEMIES_MAX; i++) {
    if (!enemies[i].active) continue;
    int wx = enemies[i].x + cam_x_offset - player.x;
    int wy = enemies[i].y + cam_y_offset - player.y;
    arduboy.drawBitmap(wx, wy, sprites + SNAKE_SPRITES_OFFSET + (game_frame / 20 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE); 

    arduboy2.setCursor(96, 0);
    arduboy2.print(enemies[i].direction);
    arduboy2.setCursor(112, 0);
    arduboy2.print(enemies[i].state);
    
    arduboy2.setCursor(0, 0);
    arduboy2.print(enemies[i].x);
    arduboy2.setCursor(18, 0);
    arduboy2.print(enemies[i].y);
  }
}

bool enemyCollidedWith(Enemy enemy, int bx, int by) {
  return enemy.x < bx * 16 + 13 && enemy.x + 13 > bx * 16 && enemy.y < by * 16 + 13 && enemy.y + 16 > by * 13;
}

/**
 * Checks if enemy collided with a solid object
 */
bool enemyCheckCollision(Enemy enemy, int dx, int dy) {
  int x = enemy.x;
  int y = enemy.y;
  int start_x = enemy.x / 16 - 1 < 0 ? 0 : enemy.x / 16 - 1;
  int start_y = enemy.y / 16 - 1 < 0 ? 0 : enemy.y / 16 - 1;
  int end_x = enemy.x / 16 + 1 > BOARD_DIM - 1 ? BOARD_DIM - 1 : enemy.x / 16 + 1;
  int end_y = enemy.y / 16 + 1 > BOARD_DIM - 1 ? BOARD_DIM - 1 : enemy.y / 16 + 1;

  for (int i = start_x; i <= end_x; i++) {
    for (int j = start_y; j <= end_y; j++) {
      if (enemyCollidedWith(enemy, i, j) && (getTile(i, j) == WALL || isBrick(i, j))) {
        return true;
      }
    }
  }
  return false;
}

void updateSnake(Enemy& enemy) {
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

    if (enemy.x % 16 == 0 && enemy.y % 16 == 0) {
      enemy.state = ENEMY_STATE_STOPPED;
    }
  }
  if (enemy.state == ENEMY_STATE_STOPPED) {
    enemy.direction = random(4);
    enemy.state = ENEMY_STATE_MOVING;
  }
}

void updateEnemies() {
  if (!arduboy.everyXFrames(10)) return;
  for (int i = 0; i < ENEMIES_MAX; i++) {
    if (!enemies[i].active) continue;
    updateSnake(enemies[i]);
    //((FunctionPointer) pgm_read_word (&enemyUpdates[enemies[i].id]))(enemies[i]);
  }
}

