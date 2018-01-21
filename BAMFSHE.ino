#include "bitmap.h"
#include "game.h"
#include "globals.h"

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM mainGameLoop[] =
{
  NULL,
  stateMainMenu,
  NULL,
  NULL,
  NULL,
  stateGameDisplayLevel,
  stateGamePrepareLevel,
  stateGameNextLevel,
  stateGamePlaying,
  stateGameOver,
  NULL,
  NULL,
  stateGameEasyComplete,
};

void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.setFrameRate(60);
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();

  gameFrame = (gameFrame + 1) % 100;
}

