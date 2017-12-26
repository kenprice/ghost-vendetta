#ifndef _BOMB_H
#define _BOMB_H

#include <Arduino.h>
#define MAX_BOMBS 20

typedef struct {
  int lifetime;
  int frame;
  byte x;
  byte y;
  byte blastRadius = 1;
  bool active;
  bool exploding;
} Bomb;

extern Bomb bombs[MAX_BOMBS];

extern int numBombs;
extern int startBombs;

void initializeBombs();

void placeBomb(int x, int y);

void updateBombs();

void drawBombs();
#endif
