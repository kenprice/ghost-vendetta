#include "globals.h"
#include "bitmap.h"
#include "bomb.h"
#include "player.h"
#include "level.h"
#include "brick.h"
#include "enemy.h"
#include "obstacle.h"

const uint16_t SOUND_BOMB_PLACE[] PROGMEM = { NOTE_A1, 100, TONES_END };
const uint16_t SOUND_BOMB_EXPLODE[] PROGMEM = { NOTE_C1, 500, TONES_END };

Bomb bombs[MAX_BOMBS];

void initializeBombs() {
  for (byte i = 0; i < MAX_BOMBS; i++) {
    bombs[i].active = false;
    bombs[i].exploding = false;
    bombs[i].blastRadius = player.blastRadius;
  }
}

bool handleCollidePlayer(byte x, byte y) {
  if (playerCollidedWith(x, y)) {
    damagePlayer();
  }
}

/**
 * Damage in-game objects, such as bricks, shrubs, and boulders
 */
bool damageObject(byte x, byte y) {
  if (isBrick(x, y)) return destroyBrick(x, y);
  byte obstacleType = getObstacleType(x, y);
  if (obstacleType) {
    damageObstacle(x, y);
  }
  switch (obstacleType) {
    case OBS_SHRUB:   return false;
    case OBS_BOULDER: return true;
  }
  
  return false;
}

void destroyBricks(Bomb& bomb) {
  for (byte i = 1; i <= bomb.blastRadius; i++) {
    if (damageObject(bomb.x + i, bomb.y) || getTile(bomb.x + i, bomb.y) == WALL) {
      bomb.blastEast = i - 1;
      break;
    }
  }
  for (byte i = 1; i <= bomb.blastRadius; i++) {
    if (damageObject(bomb.x - i, bomb.y) || getTile(bomb.x - i, bomb.y) == WALL) {
      bomb.blastWest = i - 1;
      break;
    }
  }
  for (byte i = 1; i <= bomb.blastRadius; i++) {
    if (damageObject(bomb.x, bomb.y + i) || getTile(bomb.x, bomb.y + i) == WALL) {
      bomb.blastSouth = i - 1;
      break;
    }
  }
  for (byte i = 1; i <= bomb.blastRadius; i++) {
    if (damageObject(bomb.x, bomb.y - i) || getTile(bomb.x, bomb.y - i) == WALL) {
      bomb.blastNorth = i - 1;
      break;
    }
  }
}

void explosion(Bomb bomb) {
  handleCollidePlayer(bomb.x, bomb.y);
  killEnemiesAt(bomb.x, bomb.y);
  for (byte i = 1; i <= bomb.blastEast; i++) {
    handleCollidePlayer(bomb.x + i, bomb.y);
    killEnemiesAt(bomb.x + i, bomb.y);
  }
  for (byte i = 1; i <= bomb.blastWest; i++) {
    handleCollidePlayer(bomb.x - i, bomb.y);
    killEnemiesAt(bomb.x - i, bomb.y);
  }
  for (byte i = 1; i <= bomb.blastSouth; i++) {
    handleCollidePlayer(bomb.x, bomb.y + i);
    killEnemiesAt(bomb.x, bomb.y + i);
  }
  for (byte i = 1; i <= bomb.blastNorth; i++) {
    handleCollidePlayer(bomb.x, bomb.y - i);
    killEnemiesAt(bomb.x, bomb.y - i);
  }
}

/**
   Place bomb on grid at grid coordinates.
*/
void placeBomb(byte x, byte y) {
  int i = 0;
  while (bombs[i].active && i < MAX_BOMBS) {
    i++;
  }
  bombs[i].x = x;
  bombs[i].y = y;
  bombs[i].active = true;
  bombs[i].lifetime = 10;
  bombs[i].blastRadius = player.blastRadius;
  bombs[i].blastNorth = bombs[i].blastRadius;
  bombs[i].blastSouth = bombs[i].blastRadius;
  bombs[i].blastEast = bombs[i].blastRadius;
  bombs[i].blastWest = bombs[i].blastRadius;
  sound.tones(SOUND_BOMB_PLACE);
}

void updateBomb(Bomb& bomb) {
  if (arduboy.everyXFrames(20)) bomb.lifetime--;
  if (!bomb.exploding && bomb.lifetime <= 0) {
    bomb.lifetime = 1;
    bomb.exploding = true;
    destroyBricks(bomb);
    sound.tones(SOUND_BOMB_EXPLODE);
  }
  if (bomb.exploding) {
    explosion(bomb);
  }
  if (bomb.exploding && bomb.lifetime <= 0) {
    bomb.active = false;
    bomb.exploding = false;
  }
}

void updateBombs() {
  for (byte i = 0; i < MAX_BOMBS; i++) {
    if (!bombs[i].active) continue;
    updateBomb(bombs[i]);
  }
}

/**
 * Draw bomb blast unless an obstruction is in the way
 * wx, wy = Where to draw sprite, in pixel coordinates
 * x, y = Where to check for obstruction, in tile coordinates
 */
void drawBombBlast(byte wx, byte wy, byte x, byte y) {
  if (isDestroyedBrick(x, y)) return;
  arduboy.drawBitmap(wx, wy, SPRITES + FIRE_SPRITE_OFFSET + (gameFrame / 5 % 2 * SPRITE_COL_OFFSET), 16, 16, WHITE);
}

void drawBomb(Bomb bomb) {
  char wx = bomb.x * 16 + CAM_X_OFFSET - player.x;
  char wy = bomb.y * 16 + CAM_Y_OFFSET - player.y;

  if (bomb.exploding) {
    arduboy.drawBitmap(wx, wy, SPRITES + FIRE_SPRITE_OFFSET + (gameFrame / 5 % 2 * SPRITE_COL_OFFSET), 16, 16, WHITE);
    for (byte i = 1; i <= bomb.blastEast; i++)  drawBombBlast(wx + (i * 16), wy, bomb.x + i, bomb.y);
    for (byte i = 1; i <= bomb.blastWest; i++)  drawBombBlast(wx - (i * 16), wy, bomb.x - i, bomb.y);
    for (byte i = 1; i <= bomb.blastNorth; i++) drawBombBlast(wx, wy - (i * 16), bomb.x, bomb.y - i);
    for (byte i = 1; i <= bomb.blastSouth; i++) drawBombBlast(wx, wy + (i * 16), bomb.x, bomb.y + i);
  } else {
    arduboy.drawBitmap(wx + 4, wy + 6, SPRITES_8 + 128 + 64, 8, 8, WHITE);

    for (byte i = 0; i < 3; i++) {
      arduboy.drawPixel(wx + 3 + random(7), wy - 1 + random(7));
    }
    if (bomb.lifetime > 8) arduboy.drawPixel(wx + 7, wy + 1);
    if (bomb.lifetime > 6) arduboy.drawPixel(wx + 8, wy + 2);
    if (bomb.lifetime > 4) arduboy.drawPixel(wx + 7, wy + 3);
    if (bomb.lifetime > 2) arduboy.drawPixel(wx + 8, wy + 4);
    if (bomb.lifetime > 0) arduboy.drawPixel(wx + 7, wy + 5);
  }
}

void drawBombs() {
  for (byte i = 0; i < MAX_BOMBS; i++) {
    if (!bombs[i].active) continue;
    drawBomb(bombs[i]);
  }
}

