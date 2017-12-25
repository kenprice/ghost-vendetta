#include "globals.h"
#include "level.h"
#include "bitmap.h"

#define CAM_X_OFFSET 56 // 128 / 2 - 8
#define CAM_Y_OFFSET 24 // 64 / 2 - 8

byte level;
byte displayLevel;

GameObject gameObjects[BOARD_DIM][BOARD_DIM];

void drawLevel(int posX, int posY) {
  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j = 0; j < BOARD_DIM; j++) {
      int wx = i * 16 + CAM_X_OFFSET + 16 - posX;
      int wy = j * 16 + CAM_Y_OFFSET + 16 - posY;
      if (wx < 0 || wx > WIDTH + 16 || wy < 0 || wy > HEIGHT + 16) continue;

      if (gameObjects[i][j].id == FIRE) {
          arduboy.drawBitmap(wx - 16, wy - 16, sprites + FIRE_SPRITES_OFFSET + (game_frame / 20 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
      }
      if (gameObjects[i][j].id == WALL) {
          arduboy.drawBitmap(wx - 16, wy - 16, sprites + WALL_SPRITES_OFFSET, 16, 16, WHITE);
      }
      if (gameObjects[i][j].id == BRICK) {
          arduboy.drawBitmap(wx - 16, wy - 16, sprites + BRICK_SPRITES_OFFSET, 16, 16, WHITE);
      }
      if (gameObjects[i][j].id == EXPLOSION) {
          arduboy.drawBitmap(wx - 16, wy - 16, sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
      }
    }
  }
}

