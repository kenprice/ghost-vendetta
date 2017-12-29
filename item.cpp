#include "item.h"
#include "level.h"
#include "bitmap.h"
#include "globals.h"

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
    int x = pgm_read_byte(&itemSpawnLocations[level-1][0]);
    int y = pgm_read_byte(&itemSpawnLocations[level-1][1]);
    if (x == 0 && y == 0) return;
    treasureChests[i].x = x;
    treasureChests[i].y = y;
    treasureChests[i].active = true;
  }
}

void drawChest(TreasureChest chest, int posX, int posY) {
  int wx = chest.x * 16 + CAM_X_OFFSET - posX;
  int wy = chest.y * 16 + CAM_Y_OFFSET - posY;
  arduboy.drawBitmap(wx, wy, sprites + CHEST_SPRITE_OFFSET, 16, 16, WHITE);
}

void drawChests(int posX, int posY) {
  for (int i = 0; i < MAX_CHESTS; i++) {
    if (!treasureChests[i].active) continue;
    drawChest(treasureChests[i], posX, posY);
  }
}

