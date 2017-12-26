enum alive_state { ALIVE, DYING };

typedef struct {
  int x;
  int y;
  int last_x;
  int last_y;
  int dx;
  int dy;
  int cooldown;
  int cooldownCounter;
  unsigned char frame;
  enum alive_state state;
} Player;

extern Player player;

void initializePlayer();

void updatePlayer(Player& player);

void movePlayer(int dx, int dy);

bool playerCollidedWith(int bx, int by);

void playerCheckCollision(int dx, int dy);

void killPlayer();
