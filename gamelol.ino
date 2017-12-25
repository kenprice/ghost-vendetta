#include "bitmap.h"
#include "game.h"
#include "globals.h"

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM mainGameLoop[] =
{
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  stateGamePrepareLevel,
  stateGameNextLevel,
  stateGamePlaying,
  stateGameOver,
  NULL,
  NULL
};

void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.setFrameRate(40);
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();

  game_frame++;
  if (game_frame > 100) game_frame = 0;
}

