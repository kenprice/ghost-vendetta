#include "player.h"
#include "level.h"
#include "globals.h"

Player player;

void handle_player_move() {
  if (player.state == DYING)
    return;

  bool dpad_pressed = arduboy.pressed(LEFT_BUTTON) || arduboy.pressed(RIGHT_BUTTON) || arduboy.pressed(UP_BUTTON) || arduboy.pressed(DOWN_BUTTON);
  if (dpad_pressed) player.frame = player.frame + 1 % 60;

  if(arduboy.pressed(B_BUTTON)) {
    int fx = (player.x+8)/16;
    int fy = (player.y+8)/16;
    gameObjects[fx][fy].id = FIRE;
    gameObjects[fx][fy].lifetime = 0;
  }
  if(arduboy.pressed(LEFT_BUTTON)) {
    player.dx = -1;
  }
  if(arduboy.pressed(RIGHT_BUTTON)) {
    player.dx = 1;
  }
  if(arduboy.pressed(UP_BUTTON)) {
    player.dy = -1;
  }
  if(arduboy.pressed(DOWN_BUTTON)) {
    player.dy = 1;
  }
  if (player.dx)
    movePlayer(player.dx, 0);
  if (player.dy)
    movePlayer(0, player.dy);
}

void updatePlayer(Player& player) {
  player.dx = 0;
  player.dy = 0;
  
  handle_player_move();
  playerCheckCollision(0, 0); // See if collided with EXPLOSION, trigger handling

  if (player.state == DYING) {
    player.frame++;
    if (player.frame > 20) {
      // reset_game_state();
    }
  }
}

/**
 * Returns true if player overlaps with board coordinates at (x, y)
 */
bool playerCollidedWith(int bx, int by) {
  return player.x < bx * 16 + 16 && player.x + 16 > bx * 16 && player.y < by * 16 + 16 && player.y + 16 > by * 16;
}

void playerCheckCollision(int dx, int dy) {
  int x = player.x;
  int y = player.y;
  int start_x = player.x / 16 - 1 < 0 ? 0 : player.x / 16 - 1;
  int start_y = player.y / 16 - 1 < 0 ? 0 : player.y / 16 - 1;
  int end_x = player.x / 16 + 1 > BOARD_DIM - 1 ? BOARD_DIM - 1 : player.x / 16 + 1;
  int end_y = player.y / 16 + 1 > BOARD_DIM - 1 ? BOARD_DIM - 1 : player.y / 16 + 1;

  for (int i = start_x; i <= end_x; i++) {
    for (int j = start_y; j <= end_y; j++) {
      bool is_collided = playerCollidedWith(i, j);

      if (is_collided) {
        if (dx != 0 && j > 1             && dy != -1 && gameObjects[i][j-1].id < WALL && (j - 1) * 16 + 5 > y && y > (j - 1) * 16)     player.y -= 1;
        if (dx != 0 && j < BOARD_DIM - 1 && dy != 1  && gameObjects[i][j+1].id < WALL && (j + 1) * 16 > y     && y > (j + 1) * 16 - 5) player.y += 1;
        if (dy != 0 && i > 1             && dx != -1 && gameObjects[i-1][j].id < WALL && (i - 1) * 16 + 5 > x && x > (i - 1) * 16)     player.x -= 1;
        if (dy != 0 && i < BOARD_DIM - 1 && dx != 1  && gameObjects[i+1][j].id < WALL && (i + 1) * 16 > x     && x > (i + 1) * 16 - 5) player.x += 1;

        if (gameObjects[i][j].id == EXPLOSION) {
          player.frame = 0;
          player.state = DYING;
        }

        if (gameObjects[i][j].id >= WALL) {
          player.x -= dx;
          player.y -= dy;
          return;
        }
      }
    }
  }
}

void movePlayer(int dx, int dy) {
  player.x += dx;
  player.y += dy;
  playerCheckCollision(dx, dy);
}

