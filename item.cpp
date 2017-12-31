#include "item.h"
#include "level.h"
#include "bitmap.h"
#include "globals.h"
#include "player.h"
#include "collision.h"

TreasureChest treasureChests[MAX_CHESTS];

void initializeChests() {
  for (int i = 0; i < MAX_CHESTS; i++) {
    treasureChests[i].id = 0;
    treasureChests[i].x = 0;
    treasureChests[i].y = 0;
    treasureChests[i].active = false;
    treasureChests[i].frame = 0;
  }
}

void spawnChests() {
  initializeChests();
  for (int i = 0; i < MAX_CHESTS; i++) {
    int x = pgm_read_byte(&itemSpawns[level-1][i*3+1]);
    int y = pgm_read_byte(&itemSpawns[level-1][i*3+2]);
    if (x == 0 && y == 0) return;
    treasureChests[i].id = pgm_read_byte(&itemSpawns[level-1][i*3]);
    treasureChests[i].x = x;
    treasureChests[i].y = y;
    treasureChests[i].active = true;
  }
}

void updateChests() {
  for (int i = 0; i < MAX_CHESTS; i++) {
    if (!treasureChests[i].active) continue;
    if (collidedWith(treasureChests[i].x * 16, treasureChests[i].y * 16, player.x, player.y, 3)) {
      // Open chest
      treasureChests[i].opening = true;
    }
    if (treasureChests[i].opening && arduboy.everyXFrames(3)) {
      treasureChests[i].frame++;
    }
    if (treasureChests[i].frame == 10) {
      switch (treasureChests[i].id) {
        case ITEM_APPLE:
          player.health++;
          break;
      }
      treasureChests[i].active = false;
    }
  }
}

void drawItem(TreasureChest chest, int wx, int wy) {
  arduboy.drawBitmap(wx + 4, wy + 6 - min(chest.frame, 7), SPRITES_8 + ITEM_APPLE_SPRITE_OFFSET, 8, 8, WHITE);
}

void drawChest(TreasureChest chest, int posX, int posY) {
  int wx = chest.x * 16 + CAM_X_OFFSET - posX;
  int wy = chest.y * 16 + CAM_Y_OFFSET - posY;
  if (chest.opening) {
    if (chest.frame < 5) arduboy.drawBitmap(wx, wy, SPRITES + CHEST_OPEN_SPRITE_OFFSET, 16, 16, WHITE);
    drawItem(chest, wx, wy);
  } else {
    arduboy.drawBitmap(wx, wy, SPRITES + CHEST_SPRITE_OFFSET, 16, 16, WHITE);
  }
}

void drawChests(int posX, int posY) {
  for (int i = 0; i < MAX_CHESTS; i++) {
    if (!treasureChests[i].active) continue;
    drawChest(treasureChests[i], posX, posY);
  }
}

