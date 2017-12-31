#ifndef _BOMB_H
#define _BOMB_H

#include <Arduino.h>

// constants /////////////////////////////////////////////////////////////////
#define MAX_BOMBS       5
#define BOMB_SPRITE_DIM 8

// structures ////////////////////////////////////////////////////////////////
typedef struct {
  int lifetime;
  byte x;
  byte y;
  byte blastRadius = 1;
  bool active;
  bool exploding;
  byte blastNorth;
  byte blastSouth;
  byte blastEast;
  byte blastWest;
} Bomb;

// globals ///////////////////////////////////////////////////////////////////
extern Bomb bombs[MAX_BOMBS];
extern int numBombs;
extern int startBombs;

// functions /////////////////////////////////////////////////////////////////
void initializeBombs();
void placeBomb(int x, int y);
void updateBombs();
void drawBombs();

#endif
