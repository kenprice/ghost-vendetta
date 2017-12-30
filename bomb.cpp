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
   Attempt to destroy brick at tile coordinates, returns true if brick destroyed.
*/
bool destroyBrick(byte x, byte y) {
  if (isBrick(x, y)) {
    setBrick(x, y, false);
    addDestroyedBrick(x, y);
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
    if (destroyBrick(bomb.x + i, bomb.y) || getTile(bomb.x + i, bomb.y) == WALL) {
      bomb.blastEast = i - 1;
      break;
    }
  }
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (destroyBrick(bomb.x - i, bomb.y) || getTile(bomb.x - i, bomb.y) == WALL) {
      bomb.blastWest = i - 1;
      break;
    }
  }
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (destroyBrick(bomb.x, bomb.y + i) || getTile(bomb.x, bomb.y + i) == WALL) {
      bomb.blastSouth = i - 1;
      break;
    }
  }
  for (int i = 1; i <= bomb.blastRadius; i++) {
    if (destroyBrick(bomb.x, bomb.y - i) || getTile(bomb.x, bomb.y - i) == WALL) {
      bomb.blastNorth = i - 1;
      break;
    }
    if (destroyBrick(bomb.x, bomb.y - i)) {
      bomb.blastNorth = i;
      break;
    }
  }
}

void explosion(Bomb bomb) {
  destroyPlayer(bomb.x, bomb.y);
  killEnemiesAt(bomb.x, bomb.y);
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
   Place bomb on grid at grid coordinates.
*/
void placeBomb(int x, int y) {
  int i = 0;
  while (bombs[i].active && i < MAX_BOMBS) {
    i++;
  }
  bombs[i].x = x;
  bombs[i].y = y;
  bombs[i].active = true;
  bombs[i].lifetime = 200;
  bombs[i].blastNorth = bombs[i].blastRadius;
  bombs[i].blastSouth = bombs[i].blastRadius;
  bombs[i].blastEast = bombs[i].blastRadius;
  bombs[i].blastWest = bombs[i].blastRadius;
}

void updateBomb(Bomb& bomb) {
  bomb.lifetime--;
  if (!bomb.exploding && bomb.lifetime <= 0) {
    bomb.lifetime = 20;
    bomb.exploding = true;
    destroyBricks(bomb);
  }
  if (bomb.exploding) {
    explosion(bomb);
  }
  if (bomb.exploding && bomb.lifetime <= 0) {
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

/**
 * Draw bomb blast unless an obstruction is in the way
 * wx, wy = Where to draw sprite, in pixel coordinates
 * x, y = Where to check for obstruction, in tile coordinates
 */
void drawBombBlast(int wx, int wy, byte x, byte y) {
  if (isDestroyedBrick(x, y)) return;
  arduboy.drawBitmap(wx, wy, SPRITES + FIRE_SPRITE_OFFSET + (game_frame / 5 % 2 * SPRITE_COL_OFFSET), 16, 16, WHITE);
}

void drawBomb(Bomb bomb) {
  int cam_x_offset = 128 / 2 - 8;
  int cam_y_offset = 64 / 2 - 8;
  int wx = bomb.x * 16 + cam_x_offset - player.x;
  int wy = bomb.y * 16 + cam_y_offset - player.y;

  if (bomb.exploding) {
    arduboy.drawBitmap(wx, wy, SPRITES + FIRE_SPRITE_OFFSET + (game_frame / 5 % 2 * SPRITE_COL_OFFSET), 16, 16, WHITE);
    for (int i = 1; i <= bomb.blastEast; i++)  drawBombBlast(wx + (i * 16), wy, bomb.x + i, bomb.y);
    for (int i = 1; i <= bomb.blastWest; i++)  drawBombBlast(wx - (i * 16), wy, bomb.x - i, bomb.y);
    for (int i = 1; i <= bomb.blastNorth; i++) drawBombBlast(wx, wy - (i * 16), bomb.x, bomb.y - i);
    for (int i = 1; i <= bomb.blastSouth; i++) drawBombBlast(wx, wy + (i * 16), bomb.x, bomb.y + i);
  } else {
    arduboy.drawBitmap(wx + 4, wy + 6, SPRITES_8 + 128 + 64, 8, 8, WHITE);

    for (int i = 0; i < 3; i++) {
      arduboy.drawPixel(wx + 3 + random(7), wy - 1 + random(7));
    }
    if (bomb.lifetime > 160) arduboy.drawPixel(wx + 7, wy + 1);
    if (bomb.lifetime > 120) arduboy.drawPixel(wx + 8, wy + 2);
    if (bomb.lifetime > 80)  arduboy.drawPixel(wx + 7, wy + 3);
    if (bomb.lifetime > 40)  arduboy.drawPixel(wx + 8, wy + 4);
    if (bomb.lifetime > 0)   arduboy.drawPixel(wx + 7, wy + 5);
  }
}

void drawBombs() {
  for (int i = 0; i < MAX_BOMBS; i++) {
    if (!bombs[i].active) continue;
    drawBomb(bombs[i]);
  }
}

