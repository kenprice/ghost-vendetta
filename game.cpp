#include "game.h"
#include "bitmap.h"
#include "level.h"
#include "player.h"

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
  player.x = 16;
  player.y = 16;
  player.last_x = 16;
  player.last_y = 16;
  player.dx = 0;
  player.dy = 0;
  player.frame = 0;
  player.state = ALIVE;
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

      if (gameObjects[i][j].id == FIRE) {
          arduboy.drawBitmap(wx - 16, wy - 16, sprites + FIRE_SPRITES_OFFSET + (game_frame / 20 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
      }
      if (gameObjects[i][j].id == WALL) {
          arduboy.drawBitmap(wx - 16, wy - 16, sprites + WALL_SPRITES_OFFSET, 16, 16, WHITE);
      }
      if (gameObjects[i][j].id == BRICK) {
          arduboy.drawBitmap(wx - 16, wy - 16, sprites + BRICK_SPRITES_OFFSET, 16, 16, WHITE);
      }
      if (gameObjects[i][j].id == EXPLOSION) {
        arduboy.drawBitmap(wx - 16, wy - 16, sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
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

void explosion(int x, int y);

void destroy(int x, int y) {
  if (gameObjects[x][y].id == BRICK) {
    gameObjects[x][y].id = 0;
  }
  if (gameObjects[x][y].id == FIRE) {
    explosion(x, y);
  }
  if (playerCollidedWith(x, y)) {
    player.frame = 0;
    player.state = DYING;
  }
}

void explosion(int x, int y) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (abs(i) == abs(j) && i != 0) continue;
      if (gameObjects[x+i][y+j].id == 0 || gameObjects[x+i][y+j].id == FIRE) {
        gameObjects[x+i][y+j].id = EXPLOSION;
        gameObjects[x+i][y+j].lifetime = 0;
      }
      destroy(x + i, y + j);
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
  draw();

  updatePlayer(player);

  // handle explosions
  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j = 0; j < BOARD_DIM; j++) {
      if (gameObjects[i][j].id == FIRE) {
        gameObjects[i][j].lifetime++;
        if (gameObjects[i][j].lifetime > 200) {
          gameObjects[i][j].lifetime = 0;
          gameObjects[i][j].id = EXPLOSION;
          explosion(i, j);
         }
      }
      if (gameObjects[i][j].id == EXPLOSION) {
        gameObjects[i][j].lifetime++;
        if (gameObjects[i][j].lifetime > 25) {
          gameObjects[i][j].lifetime = 0;
          gameObjects[i][j].id = 0;
        }
      }
    }
  }
}

void stateGameOver() {
  resetGameState();
  gameState = STATE_GAME_PREPARE_LEVEL;
}

