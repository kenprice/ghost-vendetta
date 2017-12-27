#include <Arduino.h>

// constants /////////////////////////////////////////////////////////////////
#define ENEMY_FACING_NORTH    0
#define ENEMY_FACING_SOUTH    1
#define ENEMY_FACING_EAST     2
#define ENEMY_FACING_WEST     3

#define ENEMIES_MAX           20

#define ENEMY_SNAKE           0x00

// structures ////////////////////////////////////////////////////////////////
typedef struct {
  byte id;
  int x;
  int y;
  byte frame;
  byte direction;
  bool active;
} Enemy;

// globals ///////////////////////////////////////////////////////////////////
extern Enemy enemies[ENEMIES_MAX];

// functions /////////////////////////////////////////////////////////////////
bool addEnemy(byte x, byte y);

bool spawnEnemy();

void drawEnemies();
