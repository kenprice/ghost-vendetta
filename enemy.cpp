#include "enemy.h"
#include "player.h"
#include "level.h"
#include "brick.h"
#include "bitmap.h"
#include "globals.h"

Enemy enemies[ENEMIES_MAX];

typedef void (*FunctionPointer) (Enemy& enemy);
const FunctionPointer PROGMEM enemyUpdates[] =
{
  updateSnake
};

void clearEnemies() {
  for (int i = 0; i < ENEMIES_MAX; i++) {
    enemies[i].active = false;
    enemies[i].id = ENEMY_SNAKE;
  }
}

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
  bool nearPlayer;

  do {
    x = random(0, BOARD_DIM);
    y = random(0, BOARD_DIM);
    tile = getTile(x, y);
    nearPlayer = x <= player.x / 16 + 1 && x >= player.x / 16 - 1 && y <= player.y / 16 + 1 && y >= player.y / 16 - 1;
  } while ((tile != FLOOR && tile != BRICK_SPAWN) || isBrick(x, y) || nearPlayer);

  return addEnemy(x, y);
}

void drawEnemies() {
  int cam_x_offset = 128/2-8;
  int cam_y_offset = 64/2-8;

  for (int i = 0; i < ENEMIES_MAX; i++) {
    if (!enemies[i].active) continue;
    int wx = enemies[i].x + cam_x_offset - player.x;
    int wy = enemies[i].y + cam_y_offset - player.y;
    arduboy.drawBitmap(wx, wy, sprites + SNAKE_SPRITES_OFFSET + (game_frame / 20 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE); 
  }
}

bool enemyCollidedWith(Enemy enemy, int bx, int by) {
  return enemy.x < bx + 13 && enemy.x + 13 > bx && enemy.y < by + 13 && enemy.y + 13 > by;
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
      if (enemyCollidedWith(enemy, i * 16, j * 16) && (getTile(i, j) == WALL || isBrick(i, j))) {
        return true;
      }
      if (enemyCollidedWith(enemy, player.x, player.y)) {
        killPlayer();
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
    ((FunctionPointer) pgm_read_word (&enemyUpdates[enemies[i].id]))(enemies[i]);
  }
}

