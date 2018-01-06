#include "game.h"
#include "globals.h"
#include "bitmap.h"
#include "level.h"
#include "player.h"
#include "bomb.h"
#include "brick.h"
#include "enemy.h"
#include "item.h"
#include "obstacle.h"

const unsigned char* LEVEL_NUMS[10] = {
  LEVEL_NUM_0,
  LEVEL_NUM_1,
  LEVEL_NUM_2,
  LEVEL_NUM_3,
  LEVEL_NUM_4,
  LEVEL_NUM_5,
  LEVEL_NUM_6,
  LEVEL_NUM_7,
  LEVEL_NUM_8,
  LEVEL_NUM_9,
};

void resetGameState() {
  initializeBombs();
  generateBricks();
  spawnChests();
  spawnObstacles();
  startPlayerAtLevel();
}

void stateMainMenu() {
  static bool start = false;

  if (arduboy.pressed(B_BUTTON)) {
    start = true;
  }

  if (arduboy.notPressed(B_BUTTON) && start) {
    gameState = STATE_GAME_NEXT_LEVEL;
  }
}

void stateGamePrepareLevel() {
  resetGameState();
  spawnEnemies();

  gameState = STATE_GAME_PLAYING;
}

void stateGameNextLevel() {
  level++;
  gameState = STATE_GAME_DISPLAY_LEVEL;
  gameFrame = 0;

  if (level == 1) {
    initializePlayer();
  }
}

void stateGameDisplayLevel() {
  ardbitmap.drawCompressed(6, 20, LEVEL_TEXT, WHITE, ALIGN_NONE, MIRROR_NONE);
  ardbitmap.drawCompressed(96, 20, LEVEL_NUMS[level], WHITE, ALIGN_NONE, MIRROR_NONE);
  if (arduboy.everyXFrames(5)) gameFrame++;

  if (gameFrame > 90) {
    gameFrame = 0;
    gameState = STATE_GAME_PREPARE_LEVEL;
  }
}

void stateGamePlaying() {
  updatePlayer();
  updateBombs();
  updateEnemies();
  updateBricks();
  updateChests();
  updateObstacles();

  // Check win condition
  bool enemyAlive = false;
  for (int i = 0; i < MAX_ENEMIES && !enemyAlive; i++) {
    enemyAlive = enemies[i].active;
  }
  if (!enemyAlive) {
    gameState = STATE_GAME_NEXT_LEVEL;
  }

  drawLevel(player.x, player.y);
  drawBricks(player.x, player.y);
  drawBombs();
  drawEnemies();
  drawChests(player.x, player.y);
  drawObstacles(player.x, player.y);
  drawPlayer();
}

void stateGameOver() {
  resetGameState();
  gameState = STATE_GAME_PREPARE_LEVEL;
}

