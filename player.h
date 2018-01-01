#ifndef _PLAYER
#define _PLAYER

#include "globals.h"

// constants /////////////////////////////////////////////////////////////////
#define PLAYER_MAX_SPEED   10   // Number of frames it takes for player to move
#define COLLISION_PADDING  5

#define PLAYER_DIRECTION_UP     0
#define PLAYER_DIRECTION_DOWN   1
#define PLAYER_DIRECTION_LEFT   2
#define PLAYER_DIRECTION_RIGHT  3

#define PLAYER_FLASHING_FRAMES  20    // Number of frames it takes for player to lose flash

// structures ////////////////////////////////////////////////////////////////
enum alive_state { ALIVE, DYING };

typedef struct {
  byte x;
  byte y;
  byte cooldown;
  byte cooldownCounter;
  byte health;
  byte flashFrame;     // How many frames to lose flash (temp invincibility)
  byte direction;
  byte frame;          // General frame
  byte spriteFrame;    // Animation frame
  enum alive_state state;
} Player;

// globals ///////////////////////////////////////////////////////////////////
extern Player player;

// functions /////////////////////////////////////////////////////////////////
void initializePlayer();
void updatePlayer();
void drawPlayer();
void movePlayer(int dx, int dy);
bool playerCollidedWith(int bx, int by);
void damagePlayer();
void mapCollide(byte& x, byte& y, bool horizontal, char& vx, char& vy, bool recursed);

#endif
