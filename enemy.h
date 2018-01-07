#include <Arduino.h>

// constants /////////////////////////////////////////////////////////////////
#define ENEMY_FACING_NORTH    0
#define ENEMY_FACING_SOUTH    1
#define ENEMY_FACING_EAST     2
#define ENEMY_FACING_WEST     3

#define ENEMY_STATE_STOPPED   0
#define ENEMY_STATE_MOVING    1
#define ENEMY_STATE_KILLED    2
#define ENEMY_STATE_FLASHING  3

#define MAX_INIT_ENEMIES      7    // Max number of enemies initially spawned on level begin
#define MAX_ENEMIES           10

#define ENEMY_SNAKE           0x01
#define ENEMY_HARD_SNAKE      0x02
#define ENEMY_SLIME           0x03
#define ENEMY_SLIME_CHILD     0x04

#define ENEMY_FLASHING_FRAMES 5    // Number of frames it takes for enemy to lose flash

// structures ////////////////////////////////////////////////////////////////
typedef struct {
  byte id : 4;
  byte direction : 2;
  byte state : 2;
  bool active : 2;
  byte x;
  byte y;
  byte flashFrame;      // How many frames to lose flash (temp invincibility)
} Enemy;

// globals ///////////////////////////////////////////////////////////////////
extern Enemy enemies[MAX_ENEMIES];

// functions /////////////////////////////////////////////////////////////////
void clearEnemies();
int addEnemy(byte x, byte y);
void killEnemiesAt(byte x, byte y);
void spawnEnemies();
void drawEnemies();
void updateEnemies();
void updateGenericEnemy(Enemy& enemy);
void updateHardSnake(Enemy& enemy);
void updateSlime(Enemy& enemy);

