enum alive_state { ALIVE, DYING };

struct {
  int x = 16;
  int y = 16;
  int last_x = 16;
  int last_y = 16;
  int dx = 0;
  int dy = 0;
  unsigned char frame = 0;
  enum alive_state state;
} player;
