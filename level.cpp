#include "globals.h"
#include "level.h"
#include "bitmap.h"
#include "player.h"

byte level = 1;

PROGMEM const byte blocks[10][16] = {
  {
    0x01, 0x01, 0x01, 0x01,   // 0x00
    0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01,
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x01
    0x0A, 0x01, 0x01, 0x09,
    0x0A, 0x01, 0x0A, 0x09,
    0x0A, 0x09, 0x09, 0x09
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x02
    0x09, 0x09, 0x09, 0x09,
    0x0A, 0x09, 0x0A, 0x09,
    0x09, 0x09, 0x09, 0x09
  },
  {
    0x0A, 0x0A, 0x0A, 0x00,   // 0x03
    0x09, 0x09, 0x0A, 0x00,
    0x0A, 0x09, 0x0A, 0x00,
    0x09, 0x09, 0x0A, 0x00
  },
  {
    0x0A, 0x09, 0x0A, 0x00,   // 0x04
    0x09, 0x09, 0x0A, 0x00,
    0x0A, 0x09, 0x0A, 0x00,
    0x09, 0x09, 0x0A, 0x00
  },
  {
    0x0A, 0x09, 0x0A, 0x00,   // 0x05
    0x09, 0x09, 0x0A, 0x00,
    0x0A, 0x0A, 0x0A, 0x00,
    0x00, 0x00, 0x00, 0x00
  },
  {
    0x0A, 0x09, 0x0A, 0x09,   // 0x06
    0x09, 0x09, 0x09, 0x09,
    0x0A, 0x0A, 0x0A, 0x0A,
    0x00, 0x00, 0x00, 0x00
  },
  {
    0x0A, 0x09, 0x0A, 0x09,   // 0x07
    0x0A, 0x09, 0x09, 0x09,
    0x0A, 0x0A, 0x0A, 0x0A,
    0x00, 0x00, 0x00, 0x00
  },
  {
    0x0A, 0x09, 0x0A, 0x09,   // 0x08
    0x0A, 0x09, 0x09, 0x09,
    0x0A, 0x09, 0x0A, 0x09,
    0x0A, 0x09, 0x09, 0x09
  },
  {
    0x0A, 0x09, 0x0A, 0x09,   // 0x09
    0x09, 0x09, 0x09, 0x09,
    0x0A, 0x09, 0x0A, 0x09,
    0x09, 0x09, 0x09, 0x09
  }
};

PROGMEM const byte maps[][MAP_DIM*MAP_DIM] = {
  {
    0x01, 0x02, 0x02, 0x03,
    0x08, 0x09, 0x09, 0x04,
    0x08, 0x09, 0x09, 0x04,
    0x07, 0x06, 0x06, 0x05,
  }
};

byte getTile(unsigned int posX, unsigned int posY) {
  return pgm_read_byte(
    &blocks[
      pgm_read_byte(&maps[level-1][posX / BLOCK_DIM + posY / BLOCK_DIM * MAP_DIM])
    ][
      (posX % BLOCK_DIM) + ((posY % BLOCK_DIM) * BLOCK_DIM)
    ]
  );
}

void drawLevel(int posX, int posY) {
  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j = 0; j < BOARD_DIM; j++) {
      int wx = i * 16 + CAM_X_OFFSET + 16 - posX;
      int wy = j * 16 + CAM_Y_OFFSET + 16 - posY;
      if (wx < 0 || wx > WIDTH + 16 || wy < 0 || wy > HEIGHT + 16) continue;

      if (getTile(i, j) == WALL) {
          arduboy.drawBitmap(wx - 16, wy - 16, sprites + WALL_SPRITES_OFFSET, 16, 16, WHITE);
      }
    }
  }
}

