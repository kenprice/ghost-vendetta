#include "brick.h"
#include "globals.h"
#include "bitmap.h"

byte bricks[NUM_LEVEL_TILES/8];
DestroyedBrick destroyedBricks[MAX_DESTROYED_BRICKS];

void clearBricks() {
  for (int i = 0; i < NUM_LEVEL_TILES / 8; i++) {
    bricks[i] = 0x00;
    destroyedBricks[i].active = false;
  }
}

void setBrick(unsigned int posX, unsigned int posY, bool placeBrick) {
  int i = posX + (posY * BOARD_DIM);
  if (placeBrick) bricks[i/8] |= (B10000000 >> (posX % 8));
  else bricks[i/8] &= ~(B10000000 >> (posX % 8));
}

bool isBrick(unsigned int posX, unsigned int posY) {
  int i = posX + (posY * BOARD_DIM);
  return (bricks[i/8] & (B10000000 >> (posX % 8))) > 0;
}

void generateBricks() {
  clearBricks();
  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j= 0; j < BOARD_DIM; j++) {
      if (getTile(i, j) != BRICK_SPAWN) continue;
      if (random(10) <= brickDensity[level-1]) {
        setBrick(i, j, true);
      }
    }    
  }
}

/**
 * This function updates destroyed bricks
 */
void updateBricks() {
  for (int i = 0; i < MAX_DESTROYED_BRICKS; i++) {
    if (!destroyedBricks[i].active) continue;
    destroyedBricks[i].lifetime--;
    if (destroyedBricks[i].lifetime <= 0) destroyedBricks[i].active = false;
  }
}

void drawBricks(int posX, int posY) {
  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j = 0; j < BOARD_DIM; j++) {
      int wx = i * 16 + CAM_X_OFFSET + 16 - posX;
      int wy = j * 16 + CAM_Y_OFFSET + 16 - posY;
      if (wx < 0 || wx > WIDTH + 16 || wy < 0 || wy > HEIGHT + 16) continue;
      if (isBrick(i, j)) {
          arduboy.drawBitmap(wx - 16, wy - 16, SPRITES + TREE_SPRITE_OFFSET, 16, 16, WHITE);
      }
      if (isDestroyedBrick(i, j)) {
          arduboy.drawBitmap(wx - 16, wy - 16, SPRITES + TREE_DEAD_SPRITE_OFFSET, 16, 16, WHITE);
      }
    }
  }
}

void addDestroyedBrick(byte x, byte y) {
  for (int i = 0; i < MAX_DESTROYED_BRICKS; i++) {
    if (destroyedBricks[i].active) continue;
    destroyedBricks[i].active = true;
    destroyedBricks[i].lifetime = 20;
    destroyedBricks[i].x = x;
    destroyedBricks[i].y = y;
    return;
  }
}

bool isDestroyedBrick(byte x, byte y) {
  for (int i = 0; i < MAX_DESTROYED_BRICKS; i++) {
    if (!destroyedBricks[i].active) continue;
    if (destroyedBricks[i].x == x && destroyedBricks[i].y == y) return true; 
  }
  return false;
}

