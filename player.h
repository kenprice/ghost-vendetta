enum alive_state { ALIVE, DYING };

// constants /////////////////////////////////////////////////////////////////
#define PLAYER_MAX_SPEED   10   // Number of frames it takes for player to move

// structures ////////////////////////////////////////////////////////////////
typedef struct {
  int x;
  int y;
  int last_x;
  int last_y;
  int dx;
  int dy;
  int cooldown;
  int cooldownCounter;
  int speed;
  unsigned char frame;
  enum alive_state state;
} Player;

// globals ///////////////////////////////////////////////////////////////////
extern Player player;

// functions /////////////////////////////////////////////////////////////////
void initializePlayer();
void updatePlayer(Player& player);
void movePlayer(int dx, int dy);
bool playerCollidedWith(int bx, int by);
void playerCheckCollision(int dx, int dy);
void killPlayer();

