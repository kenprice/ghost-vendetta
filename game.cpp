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

#define GAMETEXT_TITLE     0
#define GAMETEXT_LEVEL     1
#define GAMETEXT_COMPLETED 2
#define GAMETEXT_THANKS    3
#define GAMETEXT_LETSTRY   4
#define GAMETEXT_HARDMODE  5

bool levelCleared = false;

const uint16_t SOUND_LEVEL_CLEAR[] PROGMEM = {
  NOTE_A6, 50, NOTE_D6, 50, NOTE_E6, 50, NOTE_A6, 50, TONES_END
};

const char* const levelText[] PROGMEM = {
  "Kill It With Fire",
  "Snakes & Treasure",
  "Sneaky Snakes",
  "Boulder Dash",
  "Slimy Situation",
  "Duplicating Dunce",
  "Catacomb Concerns",
  "Hide & Seek",
  "Centralized",
  "Finally Finished",
};

const char* const gameText[] PROGMEM = {
  "GHOST VENDETTA",
  "LEVEL",
  "GAME COMPLETED!",
  "Thanks for playing!",
  "Let's try again...",
  "...in HARD MODE!"
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
    randomSeed(millis());
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
  if (level == 11) {
    gameState = STATE_GAME_EASY_COMPLETE;
  } else {
    gameState = STATE_GAME_DISPLAY_LEVEL;
  }
  gameFrame = 0;
}

void stateGameDisplayLevel() {
  arduboy.setCursor(14, 20);
  arduboy.print((char*)pgm_read_word(&gameText[GAMETEXT_LEVEL]));
  
  arduboy.setCursor(51, 20);
  arduboy.print((level % NUM_LEVELS) == 0 ? 10 : level % NUM_LEVELS);
  
  arduboy.setCursor(14, 28);
  arduboy.print((char*)pgm_read_word(&levelText[(level-1)%NUM_LEVELS]));

  // Start bomb animation
  arduboy.drawBitmap(2, 28, SPRITES_8 + BOMB_SPRITE_OFFSET, 8, 8, WHITE);
  for (byte i = 0; i < 3; i++) {
    arduboy.drawPixel(5 + random(7), 21 + random(7));
  }
  if (gameFrame < 90) arduboy.drawPixel(2 + 3, 28 - 1);
  if (gameFrame < 60) arduboy.drawPixel(2 + 4, 28 - 2);
  if (gameFrame < 50) arduboy.drawPixel(2 + 3, 28 - 3);
  if (gameFrame < 40) arduboy.drawPixel(2 + 4, 28 - 4);
  if (gameFrame < 20) arduboy.drawPixel(2 + 3, 28 - 5);
  // End bomb animation

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
    enemyAlive |= enemies[i].active;
  }
  if (!enemyAlive && !levelCleared) {
    levelCleared = true;
    gameFrame = 0;
    sound.tones(SOUND_LEVEL_CLEAR);
  }
  if (levelCleared) {
    gameFrame++;
    if (gameFrame > 90) {
      gameFrame = 0;
      levelCleared = false;
      gameState = STATE_GAME_NEXT_LEVEL;
    }
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

void stateGameVictory() {
  updatePlayer();
  updateBombs();
  updateEnemies();
  updateBricks();

  drawLevel(player.x, player.y);
  drawBricks(player.x, player.y);
  drawBombs();
  drawEnemies();
  drawPlayer();

  gameFrame++;

  if (gameFrame > 30) gameState = STATE_GAME_NEXT_LEVEL;
}

void stateGameEasyComplete() {
  arduboy.setCursor(12, 3);
  arduboy.print((char*)pgm_read_word(&gameText[GAMETEXT_COMPLETED]));

  arduboy.setCursor(12, 21);
  arduboy.print((char*)pgm_read_word(&gameText[GAMETEXT_THANKS]));

  arduboy.setCursor(0, 39);
  arduboy.print((char*)pgm_read_word(&gameText[GAMETEXT_LETSTRY]));

  arduboy.setCursor(40, 48);
  arduboy.print((char*)pgm_read_word(&gameText[GAMETEXT_HARDMODE]));

  ardbitmap.drawBitmap(
    0,
    2,
    SPRITES_8 + SLIME_SPRITE_OFFSET,
    8,
    8,
    WHITE,
    ALIGN_NONE,
    (gameFrame / 20 % 2) ? MIRROR_HORIZONTAL : MIRROR_NONE
  );

  static bool start = false;

  if (arduboy.pressed(B_BUTTON)) {
    start = true;
  }

  if (arduboy.notPressed(B_BUTTON) && start) {
    gameState = STATE_GAME_NEXT_LEVEL;
  }
}

