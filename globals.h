#ifndef _GLOBALS
#define _GLOBALS

#include <Arduboy2.h>

// constants /////////////////////////////////////////////////////////////////

//define menu states (on main menu)
#define STATE_MENU_INTRO         0
#define STATE_MENU_MAIN          1
#define STATE_MENU_HELP          2
#define STATE_MENU_PLAY          3
#define STATE_MENU_INFO          4
#define STATE_MENU_SOUNDFX       5

//define game states (on main menu)

#define STATE_GAME_PREPARE_LEVEL 6
#define STATE_GAME_NEXT_LEVEL    7
#define STATE_GAME_PLAYING       8
#define STATE_GAME_OVER          9
#define STATE_GAME_PAUSE         10
#define STATE_GAME_END           11

//camera offsets

#define CAM_X_OFFSET 56 // 128 / 2 - 8
#define CAM_Y_OFFSET 24 // 64 / 2 - 8

// main objects //////////////////////////////////////////////////////////////

extern Arduboy2Base arduboy;
extern byte gameState;

extern unsigned char game_frame;

// Ardbitmap /////////////////////////////////////////////////////////////////
#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
extern ArdBitmap<WIDTH, HEIGHT> ardbitmap;

#endif
