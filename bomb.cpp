#include "globals.h"
#include "bitmap.h"
#include "bomb.h"
#include "player.h"
#include "level.h"
#include "brick.h"
#include "enemy.h"

Bomb bombs[MAX_BOMBS];

void initializeBombs() {
  for (int i = 0; i < MAX_BOMBS; i++) {
    bombs[i].active = false;
    bombs[i].exploding = false;
    bombs[i].blastRadius = 2;
  }
}

/**
 * Attempt to destroy brick at tile coordinates, returns true if brick destroyed.
 */
bool destroyBrick(int x, int y) {
  if (isBrick(x, y)) {
    setBrick(x, y, false);
    return true;
  }
  return false;
}

bool destroyPlayer(int x, int y) {
  if (playerCollidedWith(x, y)) {
    killPlayer();
  }  
}

void destroyBricks(Bomb& bomb) {
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (getTile(bomb.x + i, bomb.y) == WALL) {
      bomb.blastEast = i - 1;
      break;
    }
    if (destroyBrick(bomb.x + i, bomb.y)) {
      bomb.blastEast = i;
      break;
    }
  }
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (getTile(bomb.x - i, bomb.y) == WALL) {
      bomb.blastWest = i - 1;
      break;
    }
    if (destroyBrick(bomb.x - i, bomb.y)) {
      bomb.blastWest = i;
      break;
    }
  }
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (getTile(bomb.x, bomb.y + i) == WALL) {
      bomb.blastSouth = i - 1;
      break;
    }
    if (destroyBrick(bomb.x, bomb.y + 1)) {
      bomb.blastSouth = i;
      break;
    }
  }
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (getTile(bomb.x, bomb.y - i) == WALL) {
      bomb.blastNorth = i - 1;
      break;
    }
    if (destroyBrick(bomb.x, bomb.y - 1)) {
      bomb.blastNorth = i;
      break;
    }
  }
}

void explosion(Bomb bomb) {
  for (int i = 1; i <= bomb.blastEast; i++) {
    destroyPlayer(bomb.x + i, bomb.y);
    killEnemiesAt(bomb.x + i, bomb.y);
  }
  for (int i = 1; i <= bomb.blastWest; i++) {
    destroyPlayer(bomb.x - i, bomb.y);
    killEnemiesAt(bomb.x - i, bomb.y);
  }
  for (int i = 1; i <= bomb.blastSouth; i++) {
    destroyPlayer(bomb.x, bomb.y + i);
    killEnemiesAt(bomb.x, bomb.y + i);
  }
  for (int i = 1; i <= bomb.blastNorth; i++) {
    destroyPlayer(bomb.x, bomb.y - i);
    killEnemiesAt(bomb.x, bomb.y - i);
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
  bombs[i].blastNorth = bombs[i].blastRadius;
  bombs[i].blastSouth = bombs[i].blastRadius;
  bombs[i].blastEast = bombs[i].blastRadius;
  bombs[i].blastWest = bombs[i].blastRadius;
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
    for (int i = 1; i <= bomb.blastEast; i++) {
      arduboy.drawBitmap(wx + (i * 16), wy, sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
    }
    for (int i = 1; i <= bomb.blastWest; i++) {
      arduboy.drawBitmap(wx - (i * 16), wy, sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
    }
    for (int i = 1; i <= bomb.blastSouth; i++) {
      arduboy.drawBitmap(wx, wy + (i * 16), sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
    }
    for (int i = 1; i <= bomb.blastNorth; i++) {
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

