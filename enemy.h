#include <Arduino.h>

// constants /////////////////////////////////////////////////////////////////
#define ENEMY_FACING_NORTH    0
#define ENEMY_FACING_SOUTH    1
#define ENEMY_FACING_EAST     2
#define ENEMY_FACING_WEST     3

#define ENEMY_STATE_STOPPED   0
#define ENEMY_STATE_MOVING    1
#define ENEMY_STATE_KILLED    2
#define ENEMY_FLASHING        3

#define MAX_ENEMIES           7

#define ENEMY_SNAKE           0x01
#define ENEMY_HARD_SNAKE      0x02
#define ENEMY_SLIME           0x03
#define ENEMY_SLIME_CHILD     0x04

// structures ////////////////////////////////////////////////////////////////
typedef struct {
  byte id : 2;
  byte direction : 2;
  byte state : 2;
  bool active : 2;
  byte x;
  byte y;
} Enemy;

// globals ///////////////////////////////////////////////////////////////////
extern Enemy enemies[MAX_ENEMIES];

// functions /////////////////////////////////////////////////////////////////
void clearEnemies();
bool addEnemy(byte x, byte y);
void killEnemiesAt(byte x, byte y);
void spawnEnemies();
void drawEnemies();
void updateEnemies();
void updateGenericEnemy(Enemy& enemy);
void updateHardSnake(Enemy& enemy);
void updateSlime(Enemy& enemy);

