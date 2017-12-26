#include "game.h"
#include "bitmap.h"
#include "level.h"
#include "player.h"
#include "bomb.h"
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

  for (int i = 0; i < MAP_DIM * BLOCK_DIM; i++) {
    for (int j = 0; j < MAP_DIM * BLOCK_DIM; j++) {
      int wx = i * 16 + cam_x_offset + 16 - player.x;
      int wy = j * 16 + cam_y_offset + 16 - player.y;
      if (wx < 0 || wx > WIDTH + 16 || wy < 0 || wy > HEIGHT + 16) continue;

      if (getTile(i, j) == WALL) {
          arduboy.drawBitmap(wx - 16, wy - 16, sprites + WALL_SPRITES_OFFSET, 16, 16, WHITE);
      }
    }
  }
}

void stateGamePrepareLevel() {
  resetGameState();
  gameState = STATE_GAME_PLAYING;
}

void stateGameNextLevel() {
  
}

void stateGamePlaying() {
  updatePlayer(player);
  updateBombs();

  draw();
  drawBombs();
}

void stateGameOver() {
  resetGameState();
  gameState = STATE_GAME_PREPARE_LEVEL;
}

