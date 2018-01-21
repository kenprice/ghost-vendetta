#include "globals.h"

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);
ArdBitmap<WIDTH, HEIGHT> ardbitmap;
byte gameState = STATE_MENU_MAIN;

byte gameFrame;

Camera camera;

/**
 * burp
 * returns the value a given percent distance between start and goal
 * percent is given in 4.4 fixed point
 * 
 * Credit: Team a.r.g. https://github.com/TEAMarg
 */
short burp(short start, short goal, unsigned char step)
{
  short a = goal;
  short b = start;
  char sign = 0;
  
  if(start > goal)
  {
    a = start;
    b = goal;
    sign = -1;
  }
  else if(start < goal)
  {
    sign = 1;
  }
  
  start += sign*(1+((a-b) * step)/16);
  if(a < b) return goal;
  
  return start;
}
