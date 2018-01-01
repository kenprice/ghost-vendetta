#ifndef _BOMB_H
#define _BOMB_H

#include <Arduino.h>

// constants /////////////////////////////////////////////////////////////////
#define MAX_BOMBS       5
#define BOMB_SPRITE_DIM 8

// structures ////////////////////////////////////////////////////////////////
typedef struct {
  byte lifetime : 4;
  byte x : 4;
  byte y : 4;
  byte blastRadius : 2;
  bool active : 1;
  bool exploding : 1;
  byte blastNorth : 2;
  byte blastSouth : 2;
  byte blastEast : 2;
  byte blastWest : 2;
} Bomb;

// globals ///////////////////////////////////////////////////////////////////
extern Bomb bombs[MAX_BOMBS];

// functions /////////////////////////////////////////////////////////////////
void initializeBombs();
void placeBomb(byte x, byte y);
void updateBombs();
void drawBombs();

#endif
