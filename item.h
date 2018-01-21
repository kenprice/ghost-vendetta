#ifndef _ITEM
#define _ITEM

#include <Arduino.h>

// constants /////////////////////////////////////////////////////////////////
#define ITEM_APPLE   1
#define ITEM_SHIELD  2
#define ITEM_SWORD   3
#define ITEM_FLAME   4

#define MAX_CHESTS   2

// structures ////////////////////////////////////////////////////////////////
typedef struct {
  byte id : 4;
  byte x : 4;
  byte y : 4;
  byte frame : 4;
  bool active : 1;
  bool opening : 1;
} TreasureChest;

// globals ///////////////////////////////////////////////////////////////////
extern TreasureChest treasureChests[MAX_CHESTS];

// functions /////////////////////////////////////////////////////////////////
void spawnChests();
void updateChests();
void drawChests(int posX, int posY);

#endif
