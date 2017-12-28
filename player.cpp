#include "player.h"
#include "globals.h"
#include "level.h"
#include "bomb.h"
#include "brick.h"

Player player;

void initializePlayer() {
  player.x = 16;
  player.y = 16;
  player.last_x = 16;
  player.last_y = 16;
  player.dx = 0;
  player.dy = 0;
  player.frame = 0;
  player.state = ALIVE;
  player.cooldown = 100;
  player.cooldownCounter = 0;
  player.speed = 1;
}

void handlePlayerMove() {
  if (player.state == DYING)
    return;

  bool dpad_pressed = arduboy.pressed(LEFT_BUTTON) || arduboy.pressed(RIGHT_BUTTON) || arduboy.pressed(UP_BUTTON) || arduboy.pressed(DOWN_BUTTON);
  if (dpad_pressed) player.frame = player.frame + 1 % 60;

  player.speed = arduboy.pressed(A_BUTTON) ? 2 : 1;

  if(arduboy.pressed(B_BUTTON)) {
    int fx = (player.x+8)/16;
    int fy = (player.y+8)/16;
    if (player.cooldownCounter == 0) {
      placeBomb(fx, fy);
      player.cooldownCounter = player.cooldown;
    }
  }
  if(arduboy.pressed(LEFT_BUTTON)) {
    player.dx = -player.speed;
  }
  if(arduboy.pressed(RIGHT_BUTTON)) {
    player.dx = player.speed;
  }
  if(arduboy.pressed(UP_BUTTON)) {
    player.dy = -player.speed;
  }
  if(arduboy.pressed(DOWN_BUTTON)) {
    player.dy = player.speed;
  }
  if (player.dx)
    movePlayer(player.dx, 0);
  if (player.dy)
    movePlayer(0, player.dy);
}

void updatePlayer(Player& player) {
  if (player.cooldownCounter > 0) {
    player.cooldownCounter--;
  }
  
  player.dx = 0;
  player.dy = 0;
  
  handlePlayerMove();

  if (player.state == DYING) {
    player.frame++;
    if (player.frame > 10) {
      gameState = STATE_GAME_OVER;
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
        if (dx != 0 && j > 1             && dy > -1 && getTile(i, j-1) < WALL && (j - 1) * 16 + 5 > y && y > (j - 1) * 16)     player.y += dy;
        if (dx != 0 && j < BOARD_DIM - 1 && dy < 1  && getTile(i, j+1) < WALL && (j + 1) * 16 > y     && y > (j + 1) * 16 - 5) player.y += dy;
        if (dy != 0 && i > 1             && dx > -1 && getTile(i-1, j) < WALL && (i - 1) * 16 + 5 > x && x > (i - 1) * 16)     player.x += dx;
        if (dy != 0 && i < BOARD_DIM - 1 && dx < 1  && getTile(i+1, j) < WALL && (i + 1) * 16 > x     && x > (i + 1) * 16 - 5) player.x += dx;

        while (playerCollidedWith(i, j) && (getTile(i, j) >= WALL || isBrick(i, j))) {
          player.x -= (dx < 0) ? -1 : (dx > 0);
          player.y -= (dy < 0) ? -1 : (dy > 0);
        }
        if (getTile(i, j) >= WALL || isBrick(i, j)) {
          return;
        }
      }
    }
  }
}

void movePlayer(int dx, int dy) {
  if (!arduboy.everyXFrames(2)) return;
  player.x += dx;
  player.y += dy;
  playerCheckCollision(dx, dy);
}

void killPlayer() {
  player.frame = 0;
  player.state = DYING;
}

