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

#define GAMETEXT_TITLE 0
#define GAMETEXT_LEVEL 1

const char* const levelText[] PROGMEM = {
  "Kill It With Fire",
  "Snakes & Treasure",
  "  Sneaky Snakes  ",
  "  Boulder  Dash  ",
  " Slimy Situation ",
  "Duplicating Dunce",
  "Catacomb Concerns",
  "   Hide & Seek   ",
};

const char* const gameText[] PROGMEM = {
  "GHOST VENDETTA",
  "LEVEL",
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

  arduboy.drawBitmap(17, 4, TITLE, 88, 12, WHITE);
  arduboy.setCursor(21, 20);
  arduboy.print((char*)pgm_read_word(&gameText[GAMETEXT_TITLE]));
  arduboy.drawBitmap(27, 59, TITLE_URL, 72, 5, WHITE);

  if (arduboy.pressed(B_BUTTON)) {
    start = true;
  }

  if (arduboy.notPressed(B_BUTTON) && start) {
    initializePlayer();
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
}

void stateGameDisplayLevel() {
  arduboy.setCursor(11, 20);
  arduboy.print((char*)pgm_read_word(&gameText[GAMETEXT_LEVEL]));
  
  arduboy.setCursor(51, 20);
  arduboy.print(level);
  
  arduboy.setCursor(11, 28);
  arduboy.print((char*)pgm_read_word(&levelText[level-1]));

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

