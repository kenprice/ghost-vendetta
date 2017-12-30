#include "player.h"
#include "globals.h"
#include "level.h"
#include "bomb.h"
#include "brick.h"
#include "bitmap.h"

Player player;

void initializePlayer() {
  player.x = 16;
  player.y = 16;
  player.last_x = 16;
  player.last_y = 16;
  player.dx = 0;
  player.dy = 0;
  player.frame = 0;
  player.state = ALIVE;
  player.cooldown = 100;
  player.cooldownCounter = 0;
  player.direction = PLAYER_DIRECTION_RIGHT;
  player.spriteFrame = 0;
}

void mapCollide(int& x, int& y, bool horizontal, char& vx, char& vy);

bool isSolid(int x, int y) {
  // Tile coordinates
  return getTile(x, y) == WALL || isBrick(x, y);
}

void horizontalCollide(int& x, int& y, char& vx, char& vy, int i) {
  if (vx < 0) {
    x = (i + 1) * 16;
    if (!isSolid(x/16 - 1, y / 16) && !isSolid(x/16, y / 16) && vy == 0 && (y % 16) <= COLLISION_PADDING) {
      y--;
      mapCollide(x, y, false, vx, vy);
    }
    if (!isSolid(x/16 - 1, y / 16 + 1) && !isSolid(x/16, y / 16 + 1) && vy == 0 && (y % 16) >= 16 - COLLISION_PADDING) {
      y++;
      mapCollide(x, y, false, vx, vy);
    }
  } else if (vx > 0) {
    x = i * 16 - 16;
    if (!isSolid(x/16 + 1, y / 16) && !isSolid(x/16, y / 16) && vy == 0 && (y % 16) <= COLLISION_PADDING) {
      y--;
      mapCollide(x, y, false, vx, vy);
    }
    if (!isSolid(x/16 + 1, y / 16 + 1) && !isSolid(x/16, y / 16 + 1) && vy == 0 && (y % 16) >= 16 - COLLISION_PADDING) {
      y++;
      mapCollide(x, y, false, vx, vy);
    }
  }
}

void verticalCollide(int& x, int& y, char& vx, char& vy, int j) {
  if (vy < 0) {
    y = (j + 1) * 16;
    if (!isSolid(x / 16, y / 16 - 1) && !isSolid(x / 16, y / 16) && vx == 0 && (x % 16) <= COLLISION_PADDING) {
      x--;
      mapCollide(x, y, true, vx, vy);
    }
    if (!isSolid(x / 16 + 1, y / 16 - 1) && !isSolid(x / 16 + 1, y / 16 - 1) && vx == 0 && (x % 16) >= 16 - COLLISION_PADDING) {
      x++;
      mapCollide(x, y, true, vx, vy);
    }
  } else if (vy > 0) {
    y = j * 16 - 16;
    if (!isSolid(x / 16, y / 16 + 1) && !isSolid(x / 16, y / 16) && vx == 0 && (x % 16) <= COLLISION_PADDING) {
      x--;
      mapCollide(x, y, true, vx, vy);
    }
    if (!isSolid(x / 16 + 1, y / 16 + 1) && !isSolid(x / 16 + 1, y / 16 + 1) && vx == 0 && (x % 16) >= 16 - COLLISION_PADDING) {
      x++;
      mapCollide(x, y, true, vx, vy);
    }
  }
}

void mapCollide(int& x, int& y, bool horizontal, char& vx, char& vy) {
  byte tileXMax = x % 16 != 0;
  byte tileYMax = y % 16 != 0;
  for (int i = x / 16; i <= x / 16 + tileXMax; i++) {
    for (int j = y / 16; j <= y / 16 + tileYMax; j++) {
      if (getTile(i, j) != WALL && !isBrick(i, j)) continue;
      if (horizontal) {
        horizontalCollide(x, y, vx, vy, i);
      }
      else {
        verticalCollide(x, y, vx, vy, j);
      }
      vx = 0;
      vy = 0;
    }
  }
}

void handlePlayerMove() {
  if (player.state == DYING) {
    return;
  }

  // Input velocity
  char vx = 0;
  char vy = 0;

  bool left = arduboy.pressed(LEFT_BUTTON);
  bool right = arduboy.pressed(RIGHT_BUTTON);
  bool up = arduboy.pressed(UP_BUTTON);
  bool down = arduboy.pressed(DOWN_BUTTON);

  if (left) player.direction = PLAYER_DIRECTION_LEFT;
  if (right) player.direction = PLAYER_DIRECTION_RIGHT;
  if (up) player.direction = PLAYER_DIRECTION_UP;
  if (down) player.direction = PLAYER_DIRECTION_DOWN;

  bool dpad_pressed = left || right || up || down;
  if (dpad_pressed) player.frame = player.frame + 1 % 60;

  // Move horizontally
  if (left) {
    vx = -1;
  } else if (right) {
    vx = 1;
  }

  player.x += vx;

  mapCollide(player.x, player.y, true, vx, vy);

  // Move vertically
  if (up) { 
    vy = -1;
  } else if (down) {
    vy = 1;
  }

  player.y += vy;

  mapCollide(player.x, player.y, false, vx, vy);

  // Other stuff
  if(arduboy.pressed(B_BUTTON)) {
    int fx = (player.x+8)/16;
    int fy = (player.y+8)/16;
    if (player.cooldownCounter == 0) {
      placeBomb(fx, fy);
      player.cooldownCounter = player.cooldown;
    }
  }
}

void updatePlayer() {
  if (player.cooldownCounter > 0) {
    player.cooldownCounter--;
  }
  
  player.dx = 0;
  player.dy = 0;
  
  handlePlayerMove();

  if (player.state == DYING) {
    player.frame++;
    if (player.frame > 10) {
      gameState = STATE_GAME_OVER;
    }
  }
}

void drawPlayer() {
  player.spriteFrame = player.state == ALIVE ? player.frame / 20 % 4 : game_frame % 4;

  int cam_x_offset = 128/2-8;
  int cam_y_offset = 64/2-8;

  int spriteAddress = SPRITES + BANSHEE_SPRITE_OFFSET;

  switch (player.direction) {
    case PLAYER_DIRECTION_UP:
      spriteAddress += ((player.spriteFrame % 2) + 2) * SPRITE_COL_OFFSET;
      break;
    case PLAYER_DIRECTION_DOWN:
      spriteAddress += player.spriteFrame % 2 * SPRITE_COL_OFFSET;
      break;
    case PLAYER_DIRECTION_LEFT:
    case PLAYER_DIRECTION_RIGHT:
      spriteAddress += player.spriteFrame % 2 * SPRITE_COL_OFFSET + 32;
      break;
  }

  bool movingHorizontal = player.direction == PLAYER_DIRECTION_LEFT || player.direction == PLAYER_DIRECTION_RIGHT;
  bool mirrorHorizontal = (player.spriteFrame == 3 && !movingHorizontal) || player.direction == PLAYER_DIRECTION_RIGHT;
  
  ardbitmap.drawBitmap(cam_x_offset, cam_y_offset, spriteAddress, 16, 16, WHITE, ALIGN_NONE, mirrorHorizontal ? MIRROR_HORIZONTAL : MIRROR_NONE); 
}

/**
 * Returns true if player overlaps with board coordinates at (x, y)
 */
bool playerCollidedWith(int bx, int by) {
  return player.x < bx * 16 + 16 && player.x + 16 > bx * 16 && player.y < by * 16 + 16 && player.y + 16 > by * 16;
}

void killPlayer() {
  if (player.state == DYING) return;
  player.frame = 0;
  player.state = DYING;
}

