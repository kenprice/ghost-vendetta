#include <Arduboy.h>
#include "bitmap.h"
#include "game_state.h"
#include "globals.h"
Arduboy arduboy;

void reset_game_state() {
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

void clear_board() {
  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j = 0; j < BOARD_DIM; j++) {
      objects[i][j].id = 0;
      objects[i][j].lifetime = 0;
    }
  }
}

void setup_board1() {
  clear_board();
  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j = 0; j < BOARD_DIM; j++) {
      bool is_wall = i == 0 || i == BOARD_DIM - 1 || j == 0 || j == BOARD_DIM - 1 || ((i + 1) % 2 && (j + 1) % 2);
      if (is_wall)
        objects[i][j].id = WALL;

      bool is_brick = !is_wall && (i > 2 || j > 2);
      if (is_brick) {
        objects[i][j].id = random(0, 4) < 3 ? BRICK : 0;
      }
    }
  }
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

      if (objects[i][j].id == FIRE) {
          arduboy.drawBitmap(wx - 16, wy - 16, sprites + FIRE_SPRITES_OFFSET + (game_frame / 20 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
      }
      if (objects[i][j].id == WALL) {
          arduboy.drawBitmap(wx - 16, wy - 16, sprites + WALL_SPRITES_OFFSET, 16, 16, WHITE);
      }
      if (objects[i][j].id == BRICK) {
          arduboy.drawBitmap(wx - 16, wy - 16, sprites + BRICK_SPRITES_OFFSET, 16, 16, WHITE);
      }
      if (objects[i][j].id == EXPLOSION) {
        arduboy.drawBitmap(wx - 16, wy - 16, sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
      }
    }
  }

  arduboy.setCursor(0, 0);
  arduboy.print(player.x);
  
  arduboy.setCursor(32, 0);
  arduboy.print(player.y);
}

void player_move(int dx, int dy) {
  player.x += dx;
  player.y += dy;
  player_check_collision(dx, dy);
}

/**
 * Returns true if player overlaps with board coordinates at (x, y)
 */
bool player_collided_with(int bx, int by) {
  return player.x < bx * 16 + 16 && player.x + 16 > bx * 16 && player.y < by * 16 + 16 && player.y + 16 > by * 16;
}

void player_check_collision(int dx, int dy) {
  int x = player.x;
  int y = player.y;
  int start_x = player.x / 16 - 1 < 0 ? 0 : player.x / 16 - 1;
  int start_y = player.y / 16 - 1 < 0 ? 0 : player.y / 16 - 1;
  int end_x = player.x / 16 + 1 > BOARD_DIM - 1 ? BOARD_DIM - 1 : player.x / 16 + 1;
  int end_y = player.y / 16 + 1 > BOARD_DIM - 1 ? BOARD_DIM - 1 : player.y / 16 + 1;

  for (int i = start_x; i <= end_x; i++) {
    for (int j = start_y; j <= end_y; j++) {
      bool is_collided = player_collided_with(i, j);

      if (is_collided) {
        if (dx != 0 && j > 1             && dy != -1 && objects[i][j-1].id < WALL && (j - 1) * 16 + 5 > y && y > (j - 1) * 16)     player.y -= 1;
        if (dx != 0 && j < BOARD_DIM - 1 && dy != 1  && objects[i][j+1].id < WALL && (j + 1) * 16 > y     && y > (j + 1) * 16 - 5) player.y += 1;
        if (dy != 0 && i > 1             && dx != -1 && objects[i-1][j].id < WALL && (i - 1) * 16 + 5 > x && x > (i - 1) * 16)     player.x -= 1;
        if (dy != 0 && i < BOARD_DIM - 1 && dx != 1  && objects[i+1][j].id < WALL && (i + 1) * 16 > x     && x > (i + 1) * 16 - 5) player.x += 1;

        if (objects[i][j].id == EXPLOSION) {
          player.frame = 0;
          player.state = DYING;
        }

        if (objects[i][j].id >= WALL) {
          player.x -= dx;
          player.y -= dy;
          return;
        }
      }
    }
  }
}

void destroy(int x, int y) {
  if (objects[x][y].id == BRICK) {
    objects[x][y].id = 0;
  }
  if (objects[x][y].id == FIRE) {
    explosion(x, y);
  }
  if (player_collided_with(x, y)) {
    player.frame = 0;
    player.state = DYING;
  }
}

void explosion(int x, int y) {
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (abs(i) == abs(j) && i != 0) continue;
      if (objects[x+i][y+j].id == 0 || objects[x+i][y+j].id == FIRE) {
        objects[x+i][y+j].id = EXPLOSION;
        objects[x+i][y+j].lifetime = 0;
      }
      destroy(x + i, y + j);
    }
  }
}

void handle_player_move() {
  if (player.state == DYING)
    return;

  bool dpad_pressed = arduboy.pressed(LEFT_BUTTON) || arduboy.pressed(RIGHT_BUTTON) || arduboy.pressed(UP_BUTTON) || arduboy.pressed(DOWN_BUTTON);
  if (dpad_pressed) player.frame = player.frame + 1 % 60;

  if(arduboy.pressed(B_BUTTON)) {
    int fx = (player.x+8)/16;
    int fy = (player.y+8)/16;
    objects[fx][fy].id = FIRE;
    objects[fx][fy].lifetime = 0;
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
    player_move(player.dx, 0);
  if (player.dy)
    player_move(0, player.dy);
}

void setup() {
  arduboy.beginNoLogo();
  arduboy.clear();
  arduboy.setFrameRate(40);
  reset_game_state();
}

void loop() {
  if (!arduboy.nextFrame())
    return;

  game_frame++;
  if (game_frame > 100) game_frame = 0;

  arduboy.clear();

  draw();
  player.dx = 0;
  player.dy = 0;

  handle_player_move();
  player_check_collision(0, 0); // See if collided with EXPLOSION, trigger handling

  if (player.state == DYING) {
    player.frame++;
    if (player.frame > 20) {
      reset_game_state();
    }
  }

  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j = 0; j < BOARD_DIM; j++) {
      if (objects[i][j].id == FIRE) {
        objects[i][j].lifetime++;
        if (objects[i][j].lifetime > 200) {
          objects[i][j].lifetime = 0;
          objects[i][j].id = EXPLOSION;
          explosion(i, j);
         }
      }
      if (objects[i][j].id == EXPLOSION) {
        objects[i][j].lifetime++;
        if (objects[i][j].lifetime > 25) {
          objects[i][j].lifetime = 0;
          objects[i][j].id = 0;
        }
      }
    }
  }
  
  arduboy.display();
}

