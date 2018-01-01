#include "player.h"
#include "globals.h"
#include "level.h"
#include "bomb.h"
#include "brick.h"
#include "bitmap.h"

const uint16_t SOUND_PLAYER_HURT[] PROGMEM = {
  NOTE_A7, 25, NOTE_REST, 25, NOTE_A7, 25, NOTE_REST, 25,
  NOTE_A7, 25, TONES_END
};

Player player;

void initializePlayer() {
  player.x = 16;
  player.y = 16;
  player.frame = 0;
  player.state = ALIVE;
  player.cooldown = 0;
  player.health = 10;
  player.flashFrame = PLAYER_FLASHING_FRAMES;
  player.direction = PLAYER_DIRECTION_RIGHT;
  player.spriteFrame = 0;
}

bool isSolid(int x, int y) {
  // Tile coordinates
  return getTile(x, y) == WALL || isBrick(x, y);
}

void horizontalCollide(byte& x, byte& y, char& vx, char& vy, int i) {
  if (vx < 0) {
    x = (i + 1) * 16;
    if (!isSolid(x/16 - 1, y / 16) && !isSolid(x/16, y / 16) && vy == 0 && (y % 16) <= COLLISION_PADDING) {
      y--;
      mapCollide(x, y, false, vx, vy, true);
    }
    if (!isSolid(x/16 - 1, y / 16 + 1) && !isSolid(x/16, y / 16 + 1) && vy == 0 && (y % 16) >= 16 - COLLISION_PADDING) {
      y++;
      mapCollide(x, y, false, vx, vy, true);
    }
  } else if (vx > 0) {
    x = i * 16 - 16;
    if (!isSolid(x/16 + 1, y / 16) && !isSolid(x/16, y / 16) && vy == 0 && (y % 16) <= COLLISION_PADDING) {
      y--;
      mapCollide(x, y, false, vx, vy, true);
    }
    if (!isSolid(x/16 + 1, y / 16 + 1) && !isSolid(x/16, y / 16 + 1) && vy == 0 && (y % 16) >= 16 - COLLISION_PADDING) {
      y++;
      mapCollide(x, y, false, vx, vy, true);
    }
  }
}

void verticalCollide(byte& x, byte& y, char& vx, char& vy, int j) {
  if (vy < 0) {
    y = (j + 1) * 16;
    if (!isSolid(x / 16, y / 16 - 1) && !isSolid(x / 16, y / 16) && vx == 0 && (x % 16) <= COLLISION_PADDING) {
      x--;
      mapCollide(x, y, true, vx, vy, true);
    }
    if (!isSolid(x / 16 + 1, y / 16 - 1) && !isSolid(x / 16 + 1, y / 16 - 1) && vx == 0 && (x % 16) >= 16 - COLLISION_PADDING) {
      x++;
      mapCollide(x, y, true, vx, vy, true);
    }
  } else if (vy > 0) {
    y = j * 16 - 16;
    if (!isSolid(x / 16, y / 16 + 1) && !isSolid(x / 16, y / 16) && vx == 0 && (x % 16) <= COLLISION_PADDING) {
      x--;
      mapCollide(x, y, true, vx, vy, true);
    }
    if (!isSolid(x / 16 + 1, y / 16 + 1) && !isSolid(x / 16 + 1, y / 16 + 1) && vx == 0 && (x % 16) >= 16 - COLLISION_PADDING) {
      x++;
      mapCollide(x, y, true, vx, vy, true);
    }
  }
}

void mapCollide(byte& x, byte& y, bool horizontal, char& vx, char& vy, bool recursed) {
  byte tileXMax = x % 16 != 0;
  byte tileYMax = y % 16 != 0;
  for (int i = x / 16; i <= x / 16 + tileXMax; i++) {
    for (int j = y / 16; j <= y / 16 + tileYMax; j++) {
      if (getTile(i, j) != WALL && !isBrick(i, j)) continue;
      if (horizontal && !recursed) {
        horizontalCollide(x, y, vx, vy, i);
      } else if (!recursed) {
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

  mapCollide(player.x, player.y, true, vx, vy, false);

  // Move vertically
  if (up) { 
    vy = -1;
  } else if (down) {
    vy = 1;
  }

  player.y += vy;

  mapCollide(player.x, player.y, false, vx, vy, false);

  // Other stuff
  if(arduboy.pressed(B_BUTTON)) {
    byte fx = (player.x+8)/16;
    byte fy = (player.y+8)/16;
    if (player.cooldown == 0) {
      placeBomb(fx, fy);
      player.cooldown = 1;
    }
  }
}

void updatePlayer() {
  if (player.cooldown == 1 && arduboy.everyXFrames(100)) {
    player.cooldown = 0;
  }

  if (player.flashFrame > 0 && arduboy.everyXFrames(5)) {
    player.flashFrame--;
  }
  
  handlePlayerMove();

  if (player.state == DYING) {
    player.frame++;
    if (player.frame > 10) {
      gameState = STATE_GAME_OVER;
    }
  }
}

void drawPlayer() {
  player.spriteFrame = player.state == ALIVE ? player.frame / 20 % 4 : gameFrame % 4;

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
      spriteAddress += player.spriteFrame % 2 * SPRITE_COL_OFFSET + 32;
      break;
    case PLAYER_DIRECTION_RIGHT:
      spriteAddress += ((player.spriteFrame % 2) + 2) * SPRITE_COL_OFFSET + 32;
      break;
  }

  bool movingHorizontal = player.direction == PLAYER_DIRECTION_LEFT || player.direction == PLAYER_DIRECTION_RIGHT;
  bool mirrorHorizontal = (player.spriteFrame == 3 && !movingHorizontal) || player.direction == PLAYER_DIRECTION_RIGHT;

  if (player.flashFrame % 2 == 0) {
    arduboy.drawBitmap(cam_x_offset, cam_y_offset, spriteAddress, 16, 16, WHITE); 
  }
}

/**
 * Returns true if player overlaps with board coordinates at (x, y)
 */
bool playerCollidedWith(int bx, int by) {
  return player.x < bx * 16 + 16 && player.x + 16 > bx * 16 && player.y < by * 16 + 16 && player.y + 16 > by * 16;
}

void damagePlayer() {
  if (player.state == DYING || player.flashFrame) return;

  if (player.health > 0) {
    player.health--;
  }

  if (player.health == 0) {
      player.frame = 0;
      player.state = DYING;
  }

  player.flashFrame = PLAYER_FLASHING_FRAMES;
  sound.tones(SOUND_PLAYER_HURT);
}

