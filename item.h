#ifndef _ITEM
#define _ITEM

#include <Arduino.h>

// constants /////////////////////////////////////////////////////////////////
#define ITEM_APPLE   1
#define ITEM_SHIELD  2
#define ITEM_SWORD   3
#define ITEM_FLAME   4

#define MAX_CHESTS   5

// structures ////////////////////////////////////////////////////////////////
typedef struct {
  byte id;
  byte x;
  byte y;
  byte frame;
  bool active;
} TreasureChest;

// globals ///////////////////////////////////////////////////////////////////
extern TreasureChest treasureChests[MAX_CHESTS];

// functions /////////////////////////////////////////////////////////////////
void spawnChests();
void drawChests(int posX, int posY);

#endif
