#include "game.h"
#include "bitmap.h"
#include "level.h"
#include "player.h"
#include "bomb.h"
#include "brick.h"
#include "enemy.h"
#include "item.h"
#include "obstacle.h"

void resetGameState() {
  initializePlayer();
  initializeBombs();
  generateBricks();
  spawnChests();
  spawnObstacles();
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
  updateChests();

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
  drawChests(player.x, player.y);
  drawObstacles(player.x, player.y);
}

void stateGameOver() {
  resetGameState();
  gameState = STATE_GAME_PREPARE_LEVEL;
}

