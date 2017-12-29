#include "collision.h"

bool collidedWith(int x1, int y1, int x2, int y2, byte padding) {
  return
    x1 < x2 + 16 - padding && 
    x1 + 16 - padding > x2 && 
    y1 < y2 + 16 - padding &&
    y1 + 16 - padding > y2;
}
