#include "item.h"
#include "level.h"
#include "bitmap.h"
#include "globals.h"
#include "player.h"
#include "collision.h"
#include "brick.h"

const uint16_t SOUND_CHEST_OPEN[] PROGMEM = {NOTE_C7, 25, NOTE_A7, 25, NOTE_C7, 25, TONES_END};

TreasureChest treasureChests[MAX_CHESTS];

void initializeChests() {
  for (int i = 0; i < MAX_CHESTS; i++) {
    treasureChests[i].id = 0;
    treasureChests[i].x = 0;
    treasureChests[i].y = 0;
    treasureChests[i].active = false;
    treasureChests[i].frame = 0;
    treasureChests[i].opening = false;
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

    if (isBrick(x, y)) setBrick(x, y, false);
  }
}

void updateChests() {
  for (int i = 0; i < MAX_CHESTS; i++) {
    if (!treasureChests[i].active) continue;
    if (collidedWith(treasureChests[i].x * 16, treasureChests[i].y * 16, player.x, player.y, 3)) {
      // Open chest
      treasureChests[i].opening = true;
      sound.tones(SOUND_CHEST_OPEN);
    }
    if (treasureChests[i].opening && arduboy.everyXFrames(3)) {
      treasureChests[i].frame++;
    }
    if (treasureChests[i].frame == 10) {
      switch (treasureChests[i].id) {
        case ITEM_APPLE:
          player.health++;
          break;
        case ITEM_FLAME:
          player.blastRadius++;
          break;
      }
      treasureChests[i].active = false;
      treasureChests[i].opening = false;
    }
  }
}

void drawItem(TreasureChest chest, int wx, int wy) {
  int itemSpriteOffset;
  switch (chest.id) {
    case ITEM_APPLE:
      itemSpriteOffset = SPRITES_8 + ITEM_APPLE_SPRITE_OFFSET;
      break;
    case ITEM_FLAME:
      itemSpriteOffset = SPRITES_8 + ITEM_FLAME_SPRITE_OFFSET;
      break;
  }
  arduboy.drawBitmap(wx + 4, wy + 3 - chest.frame, itemSpriteOffset, 8, 8, WHITE);
}

void drawChest(TreasureChest chest, int posX, int posY) {
  int wx = chest.x * 16 + camera.xOffset - posX;
  int wy = chest.y * 16 + camera.yOffset - posY;
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

