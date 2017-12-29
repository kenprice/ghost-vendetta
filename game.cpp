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
  updatePlayer();
  updateBombs();
  updateEnemies();
  updateBricks();

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
  drawPlayer();
}

void stateGameOver() {
  resetGameState();
  gameState = STATE_GAME_PREPARE_LEVEL;
}

