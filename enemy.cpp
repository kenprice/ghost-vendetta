#include "enemy.h"
#include "player.h"
#include "level.h"
#include "bitmap.h"
#include "globals.h"

Enemy enemies[ENEMIES_MAX];

void setEnemy(Enemy& enemy, byte x, byte y) {
  enemy.x = x;
  enemy.y = y;
  enemy.active = true;
}

bool addEnemy(byte x, byte y) {
  for (int i = 0; i < ENEMIES_MAX; i++) {
    if (enemies[i].active) continue;
    setEnemy(enemies[i], x, y);
    return true;
  }

  return false;
}

bool spawnEnemy() {
  byte x;
  byte y;

  while (getTile(x, y) != FLOOR) {
    x = random(0, BOARD_DIM);
    y = random(0, BOARD_DIM);
  }

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
    int wx = enemies[i].x * 16 + cam_x_offset - player.x;
    int wy = enemies[i].y * 16 + cam_y_offset - player.y;
    arduboy.drawBitmap(wx, wy, sprites + SNAKE_SPRITES_OFFSET + (game_frame / 20 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE); 
    return true;
  }
}

