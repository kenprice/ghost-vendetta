#include "game.h"
#include "bitmap.h"
#include "level.h"
#include "player.h"
#include "bomb.h"
#include "brick.h"
#include "enemy.h"
#include <Arduboy2.h>

Arduboy2 arduboy2;

void resetGameState() {
  initializePlayer();
  initializeBombs();
}

void draw() {
  unsigned char player_sprite = player.state == ALIVE ? player.frame / 20 % 4 : game_frame % 4;

  int cam_x_offset = 128/2-8;
  int cam_y_offset = 64/2-8;

  arduboy2.setCursor(0, 0);
  arduboy2.print(player.x / 16);
  arduboy2.setCursor(64, 0);
  arduboy2.print(player.y / 16);
  
  arduboy.drawBitmap(cam_x_offset, cam_y_offset, sprites + GHOST_SPRITES_OFFSET + (player_sprite * SPRITE_COL_OFFSET), 16, 16, WHITE);

  drawLevel(player.x, player.y);
  drawBricks(player.x, player.y);
}

void stateGamePrepareLevel() {
  resetGameState();
  generateBricks();
  gameState = STATE_GAME_PLAYING;

  addEnemy(3, 2); // TODO: This is just a test. Delete this later.
}

void stateGameNextLevel() {
  
}

void stateGamePlaying() {
  updatePlayer(player);
  updateBombs();

  draw();
  drawBombs();
  drawEnemies();
}

void stateGameOver() {
  resetGameState();
  gameState = STATE_GAME_PREPARE_LEVEL;
}

