#include "game.h"
#include "bitmap.h"
#include "level.h"
#include "player.h"
#include "bomb.h"

void clear_board() {
  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j = 0; j < BOARD_DIM; j++) {
      gameObjects[i][j].id = 0;
      gameObjects[i][j].lifetime = 0;
    }
  }
}

void setup_board1() {
  clear_board();
  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j = 0; j < BOARD_DIM; j++) {
      bool is_wall = i == 0 || i == BOARD_DIM - 1 || j == 0 || j == BOARD_DIM - 1 || ((i + 1) % 2 && (j + 1) % 2);
      if (is_wall)
        gameObjects[i][j].id = WALL;

      bool is_brick = !is_wall && (i > 2 || j > 2);
      if (is_brick) {
        gameObjects[i][j].id = random(0, 4) < 3 ? BRICK : 0;
      }
    }
  }
}

void resetGameState() {
  setup_board1();
  initializePlayer();
  initializeBombs();
}

void draw() {
  unsigned char player_sprite = player.state == ALIVE ? player.frame / 20 % 4 : game_frame % 4;

  int cam_x_offset = 128/2-8;
  int cam_y_offset = 64/2-8;
  
  arduboy.drawBitmap(cam_x_offset, cam_y_offset, sprites + GHOST_SPRITES_OFFSET + (player_sprite * SPRITE_COL_OFFSET), 16, 16, WHITE);

  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j = 0; j < BOARD_DIM; j++) {
      int wx = i * 16 + cam_x_offset + 16 - player.x;
      int wy = j * 16 + cam_y_offset + 16 - player.y;
      if (wx < 0 || wx > WIDTH + 16 || wy < 0 || wy > HEIGHT + 16) continue;

      if (gameObjects[i][j].id == WALL) {
          arduboy.drawBitmap(wx - 16, wy - 16, sprites + WALL_SPRITES_OFFSET, 16, 16, WHITE);
      }
      if (gameObjects[i][j].id == BRICK) {
          arduboy.drawBitmap(wx - 16, wy - 16, sprites + BRICK_SPRITES_OFFSET, 16, 16, WHITE);
      }
    }
  }
  /*
  arduboy.setCursor(0, 0);
  arduboy.print(player.x);
  
  arduboy.setCursor(32, 0);
  arduboy.print(player.y);
  */
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

