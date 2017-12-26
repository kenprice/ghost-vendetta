#include "globals.h"
#include "bitmap.h"
#include "bomb.h"
#include "player.h"
#include "level.h"

Bomb bombs[MAX_BOMBS];

void initializeBombs() {
  for (int i = 0; i < MAX_BOMBS; i++) {
    bombs[i].active = false;
    bombs[i].exploding = false;
  }
}

void explosion(int x, int y);

void destroy(int x, int y) {
  if (gameObjects[x][y].id == BRICK) {
    gameObjects[x][y].id = 0;
  }
  // TODO: Implement chain explosions
  if (playerCollidedWith(x, y)) {
    killPlayer();
  }
}

void explosion(int x, int y) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (abs(i) == abs(j) && i != 0) continue;
      destroy(x + i, y + j);
    }
  }
}

/**
 * Place bomb on grid at grid coordinates.
 */
void placeBomb(int x, int y) {
  int i = 0;
  while (bombs[i].active && i < MAX_BOMBS) {
    i++;
  }
  bombs[i].x = x;
  bombs[i].y = y;
  bombs[i].active = true;
  bombs[i].lifetime = 0;
}
    
void updateBomb(Bomb& bomb) {  
  bomb.lifetime++;
  if (!bomb.exploding && bomb.lifetime > 200) {
    bomb.lifetime = 0;
    bomb.exploding = true;
  }
  if (bomb.exploding) {
    explosion(bomb.x, bomb.y);    
  }
  if (bomb.exploding && bomb.lifetime > 25) {
    bomb.active = false;
    bomb.exploding = false;
  }
}

void updateBombs() {
  for (int i = 0; i < MAX_BOMBS; i++) {
    if (!bombs[i].active) continue;
    updateBomb(bombs[i]);
  }
}

void drawBomb(Bomb bomb) {
  int cam_x_offset = 128/2-8;
  int cam_y_offset = 64/2-8;
  int wx = bomb.x * 16 + cam_x_offset - player.x;
  int wy = bomb.y * 16 + cam_y_offset - player.y;
  // bomb
  if (bomb.active) {
    arduboy.drawBitmap(wx, wy, sprites + FIRE_SPRITES_OFFSET + (game_frame / 20 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE); 
  } else {
    arduboy.drawBitmap(wx, wy, sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
  }
}

void drawBombs() {
  for (int i = 0; i < MAX_BOMBS; i++) {
    if (!bombs[i].active) continue;
    drawBomb(bombs[i]);
  }
}

