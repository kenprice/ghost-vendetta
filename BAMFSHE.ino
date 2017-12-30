#include "bitmap.h"
#include "game.h"
#include "globals.h"

// TODO: Delete after sprite shit done
void drawTiles() {
  for (unsigned char i = 0; i < 128; i++) {
    arduboy.drawBitmap((i / 8) * 8, (i * 8) % 64, SPRITES + (i * 8), 8, 8, WHITE);
  }
}

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM mainGameLoop[] =
{
  drawTiles,
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
  arduboy.setFrameRate(60);
}

void loop() {
  // gameState = 0; // TODO: Delete after sprite shit done
  
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();

  game_frame++;
  if (game_frame > 100) game_frame = 0;
}

