#include <Arduino.h>

// constants /////////////////////////////////////////////////////////////////
#define ENEMY_FACING_NORTH    0
#define ENEMY_FACING_SOUTH    1
#define ENEMY_FACING_EAST     2
#define ENEMY_FACING_WEST     3

#define ENEMY_STATE_STOPPED   0
#define ENEMY_STATE_MOVING    1

#define MAX_ENEMIES           5

#define ENEMY_SNAKE           0x00

// structures ////////////////////////////////////////////////////////////////
typedef struct {
  byte id;
  int x;
  int y;
  byte direction;
  byte state;
  bool active;
} Enemy;

// globals ///////////////////////////////////////////////////////////////////
extern Enemy enemies[MAX_ENEMIES];

// functions /////////////////////////////////////////////////////////////////
void clearEnemies();
bool addEnemy(byte x, byte y);
void killEnemiesAt(byte x, byte y);
bool spawnEnemy();
void drawEnemies();
void updateEnemies();
void updateSnake(Enemy& enemy);

