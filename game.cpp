#include "game.h"
#include "bitmap.h"
#include "level.h"
#include "player.h"
#include "bomb.h"
#include "brick.h"
#include "enemy.h"

void resetGameState() {
  initializePlayer();
  initializeBombs();
}

void draw() {
  unsigned char player_sprite = player.state == ALIVE ? player.frame / 20 % 4 : game_frame % 4;

  int cam_x_offset = 128/2-8;
  int cam_y_offset = 64/2-8;
  
  arduboy.drawBitmap(cam_x_offset, cam_y_offset, sprites + GHOST_SPRITES_OFFSET + (player_sprite * SPRITE_COL_OFFSET), 16, 16, WHITE);

  drawLevel(player.x, player.y);
  drawBricks(player.x, player.y);
}

void stateGamePrepareLevel() {
  resetGameState();
  generateBricks();

  clearEnemies();
  for (int i = 0; i < level + 3; i++) {
    spawnEnemy();
  }
  gameState = STATE_GAME_PLAYING;
}

void stateGameNextLevel() {
  level++;
  gameState = STATE_GAME_PREPARE_LEVEL;
}

void stateGamePlaying() {
  updatePlayer(player);
  updateBombs();
  updateEnemies();

  // Check win condition
  bool enemyAlive = false;
  for (int i = 0; i < MAX_ENEMIES && !enemyAlive; i++) {
    enemyAlive = enemies[i].active;
  }
  if (!enemyAlive) {
    gameState = STATE_GAME_NEXT_LEVEL;
  }

  draw();
  drawBombs();
  drawEnemies();
}

void stateGameOver() {
  resetGameState();
  gameState = STATE_GAME_PREPARE_LEVEL;
}

