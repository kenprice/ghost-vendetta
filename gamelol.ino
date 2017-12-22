#include <Arduboy.h>
#include "bitmap.h"
#include "levels.h"
Arduboy arduboy;

const unsigned char SPRITE_COL_OFFSET = 224;
const unsigned char PROGMEM GHOST_SPRITES_OFFSET = 32;
const unsigned char PROGMEM FIRE_SPRITES_OFFSET = 96;
const unsigned char PROGMEM WALL_SPRITES_OFFSET = 192;
const unsigned char PROGMEM BRICK_SPRITES_OFFSET = 128;

const unsigned char FIRE = 1;
const unsigned char EXPLOSION = 2;
const unsigned char WALL = 10;
const unsigned char BRICK = 11;

unsigned int playerx = 16;
unsigned int playery = 16;
unsigned int player_lastx = 16;
unsigned int player_lasty = 16;
unsigned int player_dx = 0;
unsigned int player_dy = 0;
unsigned char game_frame = 0;
unsigned char player_frame = 0;

typedef struct {
  unsigned char id;
  unsigned char lifetime;
} game_object;

game_object objects[BOARD_DIM][BOARD_DIM];

void setup_board1() {
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

void draw_explosion(int x, int y, int wx, int wy) {
  arduboy.drawBitmap(wx - 16, wy - 16, sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);

  if (objects[x-1][y].id < WALL)
    arduboy.drawBitmap(wx - 32, wy - 16, sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);  // LEFT
  if (objects[x][y-1].id < WALL)
    arduboy.drawBitmap(wx - 16, wy - 32, sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);  // DOWN
  if (objects[x+1][y].id < WALL)
    arduboy.drawBitmap(wx, wy - 16, sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);       // RIGHT
  if (objects[x][y+1].id < WALL)
    arduboy.drawBitmap(wx - 16, wy, sprites + FIRE_SPRITES_OFFSET + (game_frame / 5 % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);       // UP
}

void draw() {
  unsigned char player_sprite = player_frame / 20 % 4;
  if (player_frame > 60) player_frame = 0;

  int cam_x_offset = 128/2-8;
  int cam_y_offset = 64/2-8;
  
  arduboy.drawBitmap(cam_x_offset, cam_y_offset, sprites + GHOST_SPRITES_OFFSET + (player_sprite * SPRITE_COL_OFFSET), 16, 16, WHITE);

  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j = 0; j < BOARD_DIM; j++) {
      int wx = i * 16 + cam_x_offset + 16 - playerx;
      int wy = j * 16 + cam_y_offset + 16 - playery;
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
        draw_explosion(i, j, wx, wy);
      }
    }
  }

  arduboy.setCursor(0, 0);
  arduboy.print(playerx);
  
  arduboy.setCursor(32, 0);
  arduboy.print(playery);
}

void player_move(int dx, int dy) {
  playerx += dx;
  playery += dy;
  player_collision(dx, dy);
}

void player_collision(int dx, int dy) {
  int x = playerx;
  int y = playery;
  int start_x = playerx / 16 - 1 < 0 ? 0 : playerx / 16 - 1;
  int start_y = playery / 16 - 1 < 0 ? 0 : playery / 16 - 1;
  int end_x = playerx / 16 + 1 > BOARD_DIM - 1 ? BOARD_DIM - 1 : playerx / 16 + 1;
  int end_y = playery / 16 + 1 > BOARD_DIM - 1 ? BOARD_DIM - 1 : playery / 16 + 1;
  
  for (int i = start_x; i <= end_x; i++) {
    for (int j = start_y; j <= end_y; j++) {
      if (objects[i][j].id < WALL) continue;

      bool is_collided = x < i * 16 + 16 && x + 16 > i * 16 && y < j * 16 + 16 && y + 16 > j * 16;

      if (is_collided) {
        if (dx != 0 && j > 1             && dy != -1 && objects[i][j-1].id < WALL && (j - 1) * 16 + 5 > y && y > (j - 1) * 16)     playery -= 1;
        if (dx != 0 && j < BOARD_DIM - 1 && dy != 1  && objects[i][j+1].id < WALL && (j + 1) * 16 > y     && y > (j + 1) * 16 - 5) playery += 1;
        if (dy != 0 && i > 1             && dx != -1 && objects[i-1][j].id < WALL && (i - 1) * 16 + 5 > x && x > (i - 1) * 16)     playerx -= 1;
        if (dy != 0 && i < BOARD_DIM - 1 && dx != 1  && objects[i+1][j].id < WALL && (i + 1) * 16 > x     && x > (i + 1) * 16 - 5) playerx += 1;

        playerx -= dx;
        playery -= dy;
        return;
      }
    }
  }
}

void destroy(int x, int y) {
  if (objects[x][y].id == BRICK)
    objects[x][y].id = 0;
  if (objects[x][y].id == FIRE) {
    explosion(x, y);
    objects[x][y].id = EXPLOSION;
    objects[x][y].lifetime = 25;
  }
}

void explosion(int x, int y) {
  objects[x][y].lifetime = 0;
  objects[x][y].id = 0;
  
  destroy(x-1, y);
  destroy(x+1, y);
  destroy(x, y-1);
  destroy(x, y+1);
}

void setup() {
  arduboy.beginNoLogo();
  arduboy.clear();
  arduboy.setFrameRate(40);
  setup_board1();
}

void loop() {
  if (!arduboy.nextFrame())
    return;

  game_frame++;
  if (game_frame > 100) game_frame = 0;

  arduboy.clear();

  draw();
  player_dx = 0;
  player_dy = 0;

  bool dpad_pressed = arduboy.pressed(LEFT_BUTTON) || arduboy.pressed(RIGHT_BUTTON) || arduboy.pressed(UP_BUTTON) || arduboy.pressed(DOWN_BUTTON);
  if (dpad_pressed) player_frame++;

  if(arduboy.pressed(B_BUTTON)) {
    int fx = (playerx+8)/16;
    int fy = (playery+8)/16;
    objects[fx][fy].id = FIRE;
    objects[fx][fy].lifetime = 0;
  }
  if(arduboy.pressed(LEFT_BUTTON)) {
    player_dx = -1;
  }
  if(arduboy.pressed(RIGHT_BUTTON)) {
    player_dx = 1;
  }
  if(arduboy.pressed(UP_BUTTON)) {
    player_dy = -1;
  }
  if(arduboy.pressed(DOWN_BUTTON)) {
    player_dy = 1;
  }
  if (player_dx)
    player_move(player_dx, 0);
  if (player_dy)
    player_move(0, player_dy);

  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j = 0; j < BOARD_DIM; j++) {
      if (objects[i][j].id == FIRE) {
        objects[i][j].lifetime++;
        if (objects[i][j].lifetime > 200) {
          objects[i][j].lifetime = 0;
          objects[i][j].id = EXPLOSION;
         }
      }
      if (objects[i][j].id == EXPLOSION) {
        objects[i][j].lifetime++;
        if (objects[i][j].lifetime > 25) {
          explosion(i, j);
        }
      }
    }
  }
  
  arduboy.display();
}

