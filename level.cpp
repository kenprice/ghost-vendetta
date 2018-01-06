#include "globals.h"
#include "level.h"
#include "bitmap.h"
#include "player.h"
#include "item.h"

byte level = 0;

PROGMEM const byte blocks[][16] = {
  {
    0x01, 0x01, 0x01, 0x01,   // 0x00
    0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01,
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x01   # # # #
    0x0A, 0x01, 0x01, 0x09,   //        # - - *
    0x0A, 0x01, 0x0A, 0x09,   //        # - # *
    0x0A, 0x09, 0x09, 0x09    //        # * * *
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x02   # # # #
    0x09, 0x09, 0x09, 0x09,   //        * * * *
    0x0A, 0x09, 0x0A, 0x09,   //        # * # *
    0x09, 0x09, 0x09, 0x09    //        * * * *
  },
  {
    0x0A, 0x0A, 0x0A, 0x00,   // 0x03   # # #
    0x09, 0x09, 0x0A, 0x00,   //        * * #
    0x0A, 0x09, 0x0A, 0x00,   //        # * #
    0x09, 0x09, 0x0A, 0x00    //        * * #
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
  },
  {
    0x0A, 0x0A, 0x0A, 0x00,   // 0x0A   # # #
    0x09, 0x09, 0x0A, 0x00,   //        * * #
    0x0A, 0x09, 0x0A, 0x00,   //        # * #
    0x09, 0x09, 0x0A, 0x0A    //        * * #
  },
  {
    0x0A, 0x09, 0x0A, 0x0A,   // 0x0B
    0x09, 0x09, 0x0A, 0x00,
    0x0A, 0x0A, 0x0A, 0x00,
    0x00, 0x00, 0x00, 0x00
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x0C   # # # #
    0x0A, 0x01, 0x01, 0x0A,   //        #     #
    0x0A, 0x01, 0x09, 0x09,   //        #   * *
    0x0A, 0x0A, 0x09, 0x09    //        # # * *
  },
  {
    0x09, 0x09, 0x0A, 0x0A,   // 0x0D   * * # #
    0x09, 0x09, 0x09, 0x0A,   //        * * * #
    0x0A, 0x09, 0x09, 0x0A,   //        # * * #
    0x0A, 0x0A, 0x0A, 0x0A    //        # # # #
  },
  {
    0x0A, 0x08, 0x0A, 0x08,   // 0x0E   # s # s   Like 0x02, but with shrub and boulder spawns
    0x08, 0x07, 0x08, 0x07,   //        s b * b
    0x0A, 0x08, 0x0A, 0x08,   //        # s # s
    0x08, 0x07, 0x08, 0x07    //        s b s b
  },
  {
    0x00, 0x00, 0x00, 0x00,   // 0x0F
    0x00, 0x00, 0x00, 0x0A,   //
    0x0A, 0x0A, 0x0A, 0x0A,   //        # # # #
    0x09, 0x09, 0x09, 0x09    //        * * * *
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x10   # # # #
    0x0A, 0x09, 0x09, 0x09,   //        # * * *
    0x0A, 0x09, 0x0A, 0x09,   //        # * # *
    0x0A, 0x09, 0x09, 0x09    //        # * * *
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x011  # # # #
    0x09, 0x09, 0x09, 0x09,   //        * * * *
    0x09, 0x0A, 0x09, 0x0A,   //        * # * #
    0x09, 0x09, 0x09, 0x09    //        * * * *
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x12   # # # #
    0x09, 0x09, 0x09, 0x0A,   //        * * * #
    0x09, 0x0A, 0x09, 0x0A,   //        * # * #
    0x09, 0x09, 0x09, 0x0A    //        * * * #
  },
  {
    0x08, 0x0A, 0x08, 0x0A,   // 0x13   s # s #
    0x07, 0x08, 0x07, 0x08,   //        b s b s
    0x08, 0x0A, 0x08, 0x0A,   //        s # s #
    0x07, 0x08, 0x07, 0x08    //        b s b s
  },
  {
    0x07, 0x08, 0x07, 0x08,   // 0x14   b s b s
    0x08, 0x0A, 0x08, 0x0A,   //        s # s #
    0x07, 0x08, 0x07, 0x08,   //        b s b s
    0x08, 0x0A, 0x08, 0x0A    //        s # s #
  },
  {
    0x08, 0x07, 0x08, 0x07,   // 0x15  b s b s
    0x0A, 0x08, 0x0A, 0x08,   //       # b # b
    0x08, 0x07, 0x08, 0x07,   //       b s b s
    0x0A, 0x08, 0x0A, 0x08    //       # b # b
  },
  {
    0x0A, 0x09, 0x09, 0x09,   // 0x16  # * * *
    0x0A, 0x09, 0x0A, 0x09,   //       # * # *
    0x0A, 0x09, 0x09, 0x09,   //       # * * *
    0x0A, 0x0A, 0x0A, 0x0A    //       # # # #
  },
  {
    0x09, 0x09, 0x09, 0x09,   // 0x17  * * * *
    0x0A, 0x09, 0x0A, 0x09,   //       # * # *
    0x09, 0x09, 0x09, 0x09,   //       * * * *
    0x0A, 0x0A, 0x0A, 0x0A    //       # # # #
  },
  {
    0x09, 0x09, 0x09, 0x09,   // 0x18  # # # #
    0x09, 0x0A, 0x09, 0x0A,   //       * # * #
    0x09, 0x09, 0x09, 0x09,   //       * * * *
    0x0A, 0x0A, 0x0A, 0x0A    //       # # # #
  },
  {
    0x09, 0x09, 0x09, 0x0A,   // 0x19  * * * #
    0x09, 0x0A, 0x09, 0x0A,   //       * # * #
    0x09, 0x09, 0x09, 0x0A,   //       * * * #
    0x0A, 0x0A, 0x0A, 0x0A    //       # # # #
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x1A  # # # #
    0x0A, 0x00, 0x00, 0x00,   //       #
    0x0A, 0x00, 0x00, 0x00,   //       #
    0x0A, 0x00, 0x00, 0x00    //       #
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x1B  # # # #
    0x00, 0x00, 0x00, 0x0A,   //             #
    0x00, 0x00, 0x00, 0x0A,   //             #
    0x00, 0x00, 0x00, 0x0A    //             #
  },
  {
    0x0A, 0x00, 0x00, 0x00,   // 0x1C  #
    0x0A, 0x00, 0x00, 0x00,   //       #
    0x0A, 0x00, 0x00, 0x00,   //       #
    0x0A, 0x0A, 0x0A, 0x0A,   //       # # # #
  },
  {
    0x00, 0x00, 0x00, 0x0A,   // 0x1D        #
    0x00, 0x00, 0x00, 0x0A,   //             #
    0x00, 0x00, 0x00, 0x0A,   //             #
    0x0A, 0x0A, 0x0A, 0x0A,   //       # # # #
  }
};

PROGMEM const byte maps[][MAP_DIM*MAP_DIM] = {
  {
    0x01, 0x02, 0x02, 0x03,
    0x08, 0x09, 0x09, 0x04,
    0x08, 0x09, 0x09, 0x04,
    0x07, 0x06, 0x06, 0x05,
  },
  {
    0x01, 0x0A, 0x01, 0x03,
    0x08, 0x09, 0x09, 0x04,
    0x08, 0x09, 0x09, 0x04,
    0x07, 0x0B, 0x07, 0x05,
  },
  {
    0x0C, 0x0F, 0x02, 0x03,
    0x08, 0x0E, 0x0E, 0x04,
    0x0C, 0x0E, 0x0E, 0x04,
    0x07, 0x06, 0x06, 0x0D
  },
  {
    0x10, 0x02, 0x11, 0x12,
    0x1B, 0x13, 0x0E, 0x1A,
    0x1D, 0x14, 0x15, 0x1C,
    0x16, 0x17, 0x18, 0x19
  }
};

PROGMEM const byte itemSpawns[][15] = {
  // Format: <item1 id>, <item1 x>, <item1 y>, <item2 id>, <item2 x>, <item2 y>...
  // 0, 0 for no item
  {
    ITEM_APPLE, 1, 2,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  },
  {
    ITEM_APPLE, 5, 5,
    ITEM_FLAME, 11, 11,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  },
  {
    ITEM_APPLE, 5, 5,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  },
  {
    ITEM_APPLE, 5, 5,
    ITEM_FLAME, 11, 11,
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  },
};

PROGMEM const byte playerStartPosition[][3] = {
  // Format: <player.x>, <player.y>, <player.direction>
  {16,  16,  PLAYER_DIRECTION_RIGHT},
  {16,  16,  PLAYER_DIRECTION_RIGHT},
  {16,  16,  PLAYER_DIRECTION_DOWN},
  {16,  224, PLAYER_DIRECTION_UP}
};

PROGMEM const byte brickDensity[] = {4, 4, 3, 5};

// Enemies that spawn at random locations in each level
PROGMEM const byte enemySpawns[][7] = {
  {0x01, 0x01, 0x01, 0x01, NULL, NULL, NULL},
  {0x01, 0x01, 0x01, 0x01, 0x02, NULL, NULL},
  {0x01, 0x01, 0x02, 0x02, 0x02, NULL, NULL},
  {0x02, 0x02, 0x02, 0x02, 0x02, NULL, NULL},
  {0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02}
};

byte getTile(byte posX, byte posY) {
  return pgm_read_byte(
    &blocks[
      pgm_read_byte(&maps[level-1][posX / BLOCK_DIM + posY / BLOCK_DIM * MAP_DIM])
    ][
      (posX % BLOCK_DIM) + ((posY % BLOCK_DIM) * BLOCK_DIM)
    ]
  );
}

void drawLevel(byte posX, byte posY) {
  for (byte i = 0; i < BOARD_DIM; i++) {
    for (byte j = 0; j < BOARD_DIM; j++) {
      int wx = i * 16 + camera.xOffset + 16 - posX;
      int wy = j * 16 + camera.yOffset + 16 - posY;
      if (wx < 0 || wx > WIDTH + 16 || wy < 0 || wy > HEIGHT + 16) continue;

      if (getTile(i, j) == WALL) {
          arduboy.drawBitmap(wx - 16, wy - 16, SPRITES + WALL_SPRITE_OFFSET + ((level - 1) % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
      }
    }
  }
}

