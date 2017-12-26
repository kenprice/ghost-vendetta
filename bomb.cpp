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
    bombs[i].blastRadius = 1;
  }
}

/**
 * Attempt to destroy brick at tile coordinates, returns true if brick destroyed.
 */
bool destroyBrick(int x, int y) {
  /*
  if (gameObjects[x][y].id == BRICK) {
    gameObjects[x][y].id = 0;
    return true;
  }
  */
  return false;
}

bool destroyPlayer(int x, int y) {
  if (playerCollidedWith(x, y)) {
    killPlayer();
  }  
}

void destroyBricks(Bomb bomb) {
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (destroyBrick(bomb.x + i, bomb.y) || getTile(bomb.x + i, bomb.y) == WALL) break;
  }
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (destroyBrick(bomb.x - i, bomb.y) || getTile(bomb.x - i, bomb.y) == WALL) break;
  }
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (destroyBrick(bomb.x, bomb.y + 1) || getTile(bomb.x, bomb.y + i) == WALL) break;
  }
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (destroyBrick(bomb.x, bomb.y - 1) || getTile(bomb.x, bomb.y - i) == WALL) break;
  }
}

void explosion(Bomb bomb) {
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (getTile(bomb.x + i, bomb.y) == WALL) break;
    destroyPlayer(bomb.x + i, bomb.y);
  }
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (getTile(bomb.x - 1, bomb.y) == WALL) break;
    destroyPlayer(bomb.x - i, bomb.y);
  }
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (getTile(bomb.x, bomb.y + i) == WALL) break;
    destroyPlayer(bomb.x, bomb.y + i);
  }
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (getTile(bomb.x, bomb.y - i) == WALL) break;
    destroyPlayer(bomb.x, bomb.y- i);
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
    destroyBricks(bomb);
  }
  if (bomb.exploding) {
    explosion(bomb);
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

  if (bomb.exploding) {
    arduboy.drawBitmap(wx, wy, sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
    for (int i = 1; i <= bomb.blastRadius; i++) {
      if (bomb.x + i > BOARD_DIM || getTile(bomb.x + i, bomb.y) >= WALL) break;
      arduboy.drawBitmap(wx + (i * 16), wy, sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
    }
    for (int i = 1; i <= bomb.blastRadius; i++) {
      if (bomb.x - i < 0 || getTile(bomb.x - i, bomb.y) >= WALL) break;
      arduboy.drawBitmap(wx - (i * 16), wy, sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
    }
    for (int i = 1; i <= bomb.blastRadius; i++) {
      if (bomb.y + i > BOARD_DIM || getTile(bomb.x, bomb.y + i) >= WALL) break;
      arduboy.drawBitmap(wx, wy + (i * 16), sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
    }
    for (int i = 1; i <= bomb.blastRadius; i++) {
      if (bomb.y - i < 0 || getTile(bomb.x, bomb.y - i) >= WALL) break;
      arduboy.drawBitmap(wx, wy - (i * 16), sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
    }
  } else {
    arduboy.drawBitmap(wx, wy, sprites + FIRE_SPRITES_OFFSET + (game_frame / 20 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE); 
  }
}

void drawBombs() {
  for (int i = 0; i < MAX_BOMBS; i++) {
    if (!bombs[i].active) continue;
    drawBomb(bombs[i]);
  }
}

