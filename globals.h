#ifndef _GLOBALS
#define _GLOBALS

#include <Arduino.h>
#include <Arduboy2.h>
#include <ArduboyTones.h>

// constants /////////////////////////////////////////////////////////////////

//define menu states (on main menu)
#define STATE_MENU_INTRO         0
#define STATE_MENU_MAIN          1
#define STATE_MENU_HELP          2
#define STATE_MENU_PLAY          3
#define STATE_MENU_SOUNDFX       4

//define game states (on main menu)
#define STATE_GAME_DISPLAY_LEVEL 5
#define STATE_GAME_PREPARE_LEVEL 6
#define STATE_GAME_NEXT_LEVEL    7
#define STATE_GAME_PLAYING       8
#define STATE_GAME_OVER          9
#define STATE_GAME_PAUSE         10
#define STATE_GAME_END           11
#define STATE_GAME_EASY_COMPLETE 12
#define STATE_GAME_HARD_COMPLETE 13

//camera offsets
#define CAM_X_OFFSET 56 // 128 / 2 - 8
#define CAM_Y_OFFSET 24 // 64 / 2 - 8

// Debug mode
#define DEBUG false

// structures ////////////////////////////////////////////////////////////////
typedef struct {
  int xOffset = CAM_X_OFFSET;
  int yOffset = CAM_Y_OFFSET;
} Camera;

// main objects //////////////////////////////////////////////////////////////

extern Arduboy2 arduboy;
extern byte gameState;
extern byte gameFrame;
extern ArduboyTones sound;
extern Camera camera;

// functions /////////////////////////////////////////////////////////////////
short burp(short start, short goal, unsigned char step);

// Ardbitmap /////////////////////////////////////////////////////////////////
#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
extern ArdBitmap<WIDTH, HEIGHT> ardbitmap;

#endif
