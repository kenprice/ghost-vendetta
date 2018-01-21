#include "globals.h"
#include "level.h"
#include "bitmap.h"
#include "player.h"
#include "item.h"

byte level = 0;

PROGMEM const byte blocks[][16] = {
  {
    0x00, 0x00, 0x00, 0x00,   // 0x00
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x01   # # # #
    0x0A, 0x09, 0x09, 0x09,   //        # * * *
    0x0A, 0x09, 0x0A, 0x09,   //        # * # *
    0x0A, 0x09, 0x09, 0x09    //        # * * *
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x02   # # # #
    0x09, 0x09, 0x09, 0x09,   //        * * * *
    0x0A, 0x09, 0x0A, 0x09,   //        # * # *
    0x09, 0x09, 0x09, 0x09    //        * * * *
  },
  {
    0x0A, 0x0A, 0x0A, 0x00,   // 0x03   # # #
    0x09, 0x09, 0x0A, 0x00,   //        * * #
    0x0A, 0x09, 0x0A, 0x00,   //        # * #
    0x09, 0x09, 0x0A, 0x00    //        * * #
  },
  {
    0x0A, 0x09, 0x0A, 0x00,   // 0x04
    0x09, 0x09, 0x0A, 0x00,
    0x0A, 0x09, 0x0A, 0x00,
    0x09, 0x09, 0x0A, 0x00
  },
  {
    0x0A, 0x09, 0x0A, 0x00,   // 0x05
    0x09, 0x09, 0x0A, 0x00,
    0x0A, 0x0A, 0x0A, 0x00,
    0x00, 0x00, 0x00, 0x00
  },
  {
    0x0A, 0x09, 0x0A, 0x09,   // 0x06
    0x09, 0x09, 0x09, 0x09,
    0x0A, 0x0A, 0x0A, 0x0A,
    0x00, 0x00, 0x00, 0x00
  },
  {
    0x0A, 0x09, 0x0A, 0x09,   // 0x07
    0x0A, 0x09, 0x09, 0x09,
    0x0A, 0x0A, 0x0A, 0x0A,
    0x00, 0x00, 0x00, 0x00
  },
  {
    0x0A, 0x09, 0x0A, 0x09,   // 0x08
    0x0A, 0x09, 0x09, 0x09,
    0x0A, 0x09, 0x0A, 0x09,
    0x0A, 0x09, 0x09, 0x09
  },
  {
    0x0A, 0x09, 0x0A, 0x09,   // 0x09
    0x09, 0x09, 0x09, 0x09,
    0x0A, 0x09, 0x0A, 0x09,
    0x09, 0x09, 0x09, 0x09
  },
  {
    0x0A, 0x0A, 0x0A, 0x00,   // 0x0A   # # #
    0x09, 0x09, 0x0A, 0x00,   //        * * #
    0x0A, 0x09, 0x0A, 0x00,   //        # * #
    0x09, 0x09, 0x0A, 0x0A    //        * * #
  },
  {
    0x0A, 0x09, 0x0A, 0x0A,   // 0x0B   # * # #
    0x09, 0x09, 0x0A, 0x00,   //        * * #
    0x0A, 0x0A, 0x0A, 0x00,   //        # # #
    0x00, 0x00, 0x00, 0x00    //
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x0C   # # # #
    0x0A, 0x09, 0x09, 0x0A,   //        #     #
    0x0A, 0x09, 0x09, 0x09,   //        #   * *
    0x0A, 0x0A, 0x09, 0x09    //        # # * *
  },
  {
    0x09, 0x09, 0x0A, 0x0A,   // 0x0D   * * # #
    0x09, 0x09, 0x09, 0x0A,   //        * * * #
    0x0A, 0x09, 0x09, 0x0A,   //        # * * #
    0x0A, 0x0A, 0x0A, 0x0A    //        # # # #
  },
  {
    0x0A, 0x08, 0x0A, 0x08,   // 0x0E   # s # s   Like 0x02, but with shrub and boulder spawns
    0x08, 0x07, 0x08, 0x07,   //        s b s b
    0x0A, 0x08, 0x0A, 0x08,   //        # s # s
    0x08, 0x07, 0x08, 0x07    //        s b s b
  },
  {
    0x00, 0x00, 0x00, 0x00,   // 0x0F
    0x00, 0x00, 0x00, 0x0A,   //
    0x0A, 0x0A, 0x0A, 0x0A,   //        # # # #
    0x09, 0x09, 0x09, 0x09    //        * * * *
  },
  {
    0x00, 0x0A, 0x0A, 0x0A,   // 0x10     # # #
    0x0A, 0x0A, 0x08, 0x08,   //        # # s s
    0x0A, 0x08, 0x08, 0x0A,   //        # s s #
    0x0A, 0x08, 0x0A, 0x09    //        # s # *
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x11   # # # #
    0x09, 0x09, 0x09, 0x09,   //        * * * *
    0x09, 0x0A, 0x09, 0x0A,   //        * # * #
    0x09, 0x09, 0x09, 0x09    //        * * * *
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x12   # # # #
    0x09, 0x09, 0x09, 0x0A,   //        * * * #
    0x09, 0x0A, 0x09, 0x0A,   //        * # * #
    0x09, 0x09, 0x09, 0x0A    //        * * * #
  },
  {
    0x08, 0x0A, 0x08, 0x0A,   // 0x13   s # s #
    0x07, 0x08, 0x07, 0x08,   //        b s b s
    0x08, 0x0A, 0x08, 0x0A,   //        s # s #
    0x07, 0x08, 0x07, 0x08    //        b s b s
  },
  {
    0x07, 0x08, 0x07, 0x08,   // 0x14   b s b s
    0x08, 0x0A, 0x08, 0x0A,   //        s # s #
    0x07, 0x08, 0x07, 0x08,   //        b s b s
    0x08, 0x0A, 0x08, 0x0A    //        s # s #
  },
  {
    0x08, 0x07, 0x08, 0x07,   // 0x15  b s b s
    0x0A, 0x08, 0x0A, 0x08,   //       # b # b
    0x08, 0x07, 0x08, 0x07,   //       b s b s
    0x0A, 0x08, 0x0A, 0x08    //       # b # b
  },
  {
    0x0A, 0x09, 0x09, 0x09,   // 0x16  # * * *
    0x0A, 0x09, 0x0A, 0x09,   //       # * # *
    0x0A, 0x09, 0x09, 0x09,   //       # * * *
    0x0A, 0x0A, 0x0A, 0x0A    //       # # # #
  },
  {
    0x09, 0x09, 0x09, 0x09,   // 0x17  * * * *
    0x0A, 0x09, 0x0A, 0x09,   //       # * # *
    0x09, 0x09, 0x09, 0x09,   //       * * * *
    0x0A, 0x0A, 0x0A, 0x0A    //       # # # #
  },
  {
    0x09, 0x09, 0x09, 0x09,   // 0x18  # # # #
    0x09, 0x0A, 0x09, 0x0A,   //       * # * #
    0x09, 0x09, 0x09, 0x09,   //       * * * *
    0x0A, 0x0A, 0x0A, 0x0A    //       # # # #
  },
  {
    0x09, 0x09, 0x09, 0x0A,   // 0x19  * * * #
    0x09, 0x0A, 0x09, 0x0A,   //       * # * #
    0x09, 0x09, 0x09, 0x0A,   //       * * * #
    0x0A, 0x0A, 0x0A, 0x0A    //       # # # #
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x1A  # # # #
    0x0A, 0x00, 0x00, 0x00,   //       #
    0x0A, 0x00, 0x00, 0x00,   //       #
    0x0A, 0x00, 0x00, 0x00    //       #
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x1B  # # # #
    0x00, 0x00, 0x00, 0x0A,   //             #
    0x00, 0x00, 0x00, 0x0A,   //             #
    0x00, 0x00, 0x00, 0x0A    //             #
  },
  {
    0x0A, 0x00, 0x00, 0x00,   // 0x1C  #
    0x0A, 0x00, 0x00, 0x00,   //       #
    0x0A, 0x00, 0x00, 0x00,   //       #
    0x0A, 0x0A, 0x0A, 0x0A,   //       # # # #
  },
  {
    0x00, 0x00, 0x00, 0x0A,   // 0x1D        #
    0x00, 0x00, 0x00, 0x0A,   //             #
    0x00, 0x00, 0x00, 0x0A,   //             #
    0x0A, 0x0A, 0x0A, 0x0A,   //       # # # #
  },
  {
    0x0A, 0x09, 0x09, 0x09,   // 0x1E  # * * *
    0x0A, 0x0A, 0x09, 0x09,   //       # # * *
    0x00, 0x0A, 0x09, 0x09,   //         # * *
    0x00, 0x0A, 0x09, 0x0A,   //         # * #
  },
  {
    0x00, 0x0A, 0x09, 0x0A,   // 0x1F    # * #
    0x00, 0x0A, 0x09, 0x09,   //         # * *
    0x0A, 0x0A, 0x09, 0x09,   //       # # * *
    0x0A, 0x09, 0x09, 0x09,   //       # * * *
  },
  {
    0x0A, 0x08, 0x0A, 0x09,   // 0x20  # s # *
    0x0A, 0x08, 0x08, 0x0A,   //       # s s #
    0x0A, 0x0A, 0x08, 0x08,   //       # # s s
    0x00, 0x0A, 0x0A, 0x0A,   //         # # #
  },
  {
    0x0A, 0x0A, 0x00, 0x00,   // 0x21  # #
    0x09, 0x0A, 0x0A, 0x0A,   //       * # # #
    0x09, 0x09, 0x09, 0x09,   //       * * * *
    0x09, 0x09, 0x09, 0x0A,   //       * * * #
  },
  {
    0x00, 0x00, 0x0A, 0x0A,   // 0x22      # #
    0x0A, 0x0A, 0x0A, 0x09,   //       # # # *
    0x09, 0x09, 0x09, 0x09,   //       * * * *
    0x0A, 0x09, 0x09, 0x09,   //       # * * *
  },
  {
    0x0A, 0x0A, 0x0A, 0x00,   // 0x23  # # #
    0x08, 0x08, 0x0A, 0x0A,   //       s s # #
    0x0A, 0x08, 0x08, 0x0A,   //       # s s #
    0x08, 0x0A, 0x08, 0x0A,   //       s # s #
  },
  {
    0x0A, 0x0A, 0x09, 0x0A,   // 0x24  # # * #
    0x0A, 0x09, 0x09, 0x09,   //       # * * *
    0x09, 0x09, 0x0A, 0x09,   //       * * # *
    0x0A, 0x09, 0x09, 0x09,   //       # * * *
  },
  {
    0x0A, 0x09, 0x0A, 0x0A,   // 0x25  # * # #
    0x09, 0x09, 0x09, 0x0A,   //       * * * #
    0x09, 0x0A, 0x09, 0x09,   //       * # * *
    0x09, 0x09, 0x09, 0x0A,   //       * * * #
  },
  {
    0x09, 0x09, 0x09, 0x0A,   // 0x26  * * * #
    0x09, 0x09, 0x0A, 0x0A,   //       * * # #
    0x09, 0x09, 0x0A, 0x00,   //       * * #
    0x0A, 0x09, 0x0A, 0x00,   //       # * #
  },
  {
    0x0A, 0x09, 0x0A, 0x00,   // 0x27  # * #
    0x09, 0x09, 0x0A, 0x00,   //       * * #
    0x09, 0x09, 0x0A, 0x0A,   //       * * # #
    0x09, 0x09, 0x09, 0x0A,   //       * * * #
  },
  {
    0x0A, 0x09, 0x09, 0x09,   // 0x28  # * * *
    0x09, 0x09, 0x0A, 0x09,   //       * * # *
    0x0A, 0x09, 0x09, 0x09,   //       # * * *
    0x0A, 0x0A, 0x09, 0x0A,   //       # # * #
  },
  {
    0x09, 0x09, 0x09, 0x0A,   // 0x29  * * * #
    0x09, 0x0A, 0x09, 0x09,   //       * # * *
    0x09, 0x09, 0x09, 0x0A,   //       * * * #
    0x0A, 0x09, 0x0A, 0x0A,   //       # * # #
  },
  {
    0x09, 0x09, 0x09, 0x0A,   // 0x2A  * * * #
    0x09, 0x09, 0x09, 0x09,   //       * * * *
    0x09, 0x0A, 0x0A, 0x0A,   //       * # # #
    0x0A, 0x0A, 0x00, 0x00,   //       # #
  },
  {
    0x0A, 0x09, 0x09, 0x09,   // 0x2B  # * * *
    0x09, 0x09, 0x09, 0x09,   //       * * * *
    0x0A, 0x0A, 0x0A, 0x09,   //       # # # *
    0x00, 0x00, 0x0A, 0x0A,   //           # #
  },
  {
    0x08, 0x0A, 0x08, 0x0A,   // 0x2C  s # s #
    0x0A, 0x08, 0x08, 0x0A,   //       # s s #
    0x08, 0x08, 0x0A, 0x0A,   //       s s # #
    0x0A, 0x0A, 0x0A, 0x00,   //       # # #
  },
  {
    0x09, 0x09, 0x09, 0x0A,   // 0x2D  * * * #
    0x09, 0x0A, 0x09, 0x0A,   //       * # * #
    0x09, 0x09, 0x09, 0x0A,   //       * * * #
    0x0A, 0x0A, 0x0A, 0x0A,   //       # # # #
  },
  {
    0x0A, 0x09, 0x09, 0x09,   // 0x2E  # * * *
    0x0A, 0x09, 0x0A, 0x09,   //       # * # *
    0x0A, 0x09, 0x09, 0x09,   //       # * * *
    0x0A, 0x0A, 0x0A, 0x0A,   //       # # # #
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x2F  # # # #
    0x09, 0x0A, 0x09, 0x0A,   //       * # * #
    0x09, 0x09, 0x09, 0x09,   //       * * * *
    0x0A, 0x09, 0x0A, 0x0A,   //       # * # *
  },
  {
    0x0A, 0x0A, 0x0A, 0x0A,   // 0x30  # # # #
    0x09, 0x09, 0x09, 0x09,   //       * * * *
    0x09, 0x0A, 0x09, 0x0A,   //       * # * #
    0x09, 0x09, 0x09, 0x0A,   //       * * * #
  },
  {
    0x0A, 0x09, 0x0A, 0x09,   // 0x31  # * # *
    0x0A, 0x0A, 0x0A, 0x09,   //       # # # *
    0x0A, 0x09, 0x09, 0x09,   //       # * * *
    0x0A, 0x09, 0x0A, 0x0A,   //       # * # #
  },
  {
    0x0A, 0x09, 0x09, 0x09,   // 0x32  # * * *
    0x0A, 0x09, 0x0A, 0x09,   //       # * # *
    0x09, 0x0A, 0x0A, 0x09,   //       * # # *
    0x09, 0x09, 0x0A, 0x09,   //       * * # *
  },
  {
    0x09, 0x0A, 0x0A, 0x0A,   // 0x33  * # # #
    0x09, 0x09, 0x09, 0x0A,   //       * * * #
    0x0A, 0x09, 0x0A, 0x0A,   //       # * # #
    0x0A, 0x09, 0x09, 0x0A,   //       # * * #
  },
  {
    0x0A, 0x09, 0x09, 0x09,   // 0x34  # * * *
    0x0A, 0x0A, 0x09, 0x0A,   //       # # * #
    0x0A, 0x09, 0x09, 0x09,   //       # * * *
    0x0A, 0x09, 0x0A, 0x09,   //       # * # *
  },
  {
    0x0A, 0x09, 0x09, 0x0A,   // 0x35  # * * #
    0x09, 0x0A, 0x09, 0x09,   //       * # * *
    0x09, 0x09, 0x0A, 0x0A,   //       * * # #
    0x0A, 0x09, 0x0A, 0x09,   //       # * # *
  },
  {
    0x0A, 0x0A, 0x0A, 0x09,   // 0x36  # # # *
    0x09, 0x09, 0x09, 0x09,   //       * * * *
    0x0A, 0x09, 0x0A, 0x0A,   //       # * # #
    0x0A, 0x09, 0x0A, 0x09,   //       # * # *
  },
  {
    0x0A, 0x09, 0x0A, 0x0A,   // 0x37  # * # #
    0x09, 0x09, 0x09, 0x0A,   //       * * * #
    0x0A, 0x0A, 0x09, 0x0A,   //       # # * #
    0x09, 0x09, 0x09, 0x0A,   //       * * * #
  },
  {
    0x0A, 0x09, 0x09, 0x09,   // 0x38  # * * *
    0x0A, 0x09, 0x0A, 0x0A,   //       # * # #
    0x0A, 0x09, 0x09, 0x09,   //       # * * *
    0x0A, 0x0A, 0x0A, 0x0A,   //       # # # #
  },
  {
    0x09, 0x09, 0x0A, 0x09,   // 0x39  * * # *
    0x0A, 0x09, 0x0A, 0x09,   //       # * # *
    0x0A, 0x09, 0x09, 0x09,   //       # * * *
    0x0A, 0x0A, 0x0A, 0x0A,   //       # # # #
  }, 
  {
    0x09, 0x0A, 0x09, 0x0A,   // 0x3A  * # * #
    0x0A, 0x0A, 0x09, 0x0A,   //       # # * #
    0x09, 0x09, 0x09, 0x0A,   //       * * * #
    0x0A, 0x0A, 0x0A, 0x0A,   //       # # # #
  },
  {
    0x09, 0x09, 0x09, 0x0A,
    0x09, 0x0A, 0x09, 0x0A,
    0x09, 0x09, 0x09, 0x0A,
    0x09, 0x0A, 0x09, 0x0A,
  }
};

PROGMEM const byte maps[][MAP_DIM * MAP_DIM] = {
  { // Level 1
    0x01, 0x02, 0x02, 0x03,
    0x08, 0x09, 0x09, 0x04,
    0x08, 0x09, 0x09, 0x04,
    0x07, 0x06, 0x06, 0x05,
  },
  { // Level 2
    0x01, 0x0A, 0x01, 0x03,
    0x08, 0x09, 0x09, 0x04,
    0x08, 0x09, 0x09, 0x04,
    0x07, 0x0B, 0x07, 0x05,
  },
  { // Level 3
    0x0C, 0x0F, 0x02, 0x03,
    0x08, 0x0E, 0x0E, 0x04,
    0x0C, 0x0E, 0x0E, 0x04,
    0x07, 0x06, 0x06, 0x0D,
  },
  { // Level 4
    0x01, 0x02, 0x11, 0x12,
    0x1B, 0x13, 0x0E, 0x1A,
    0x1D, 0x14, 0x15, 0x1C,
    0x16, 0x17, 0x18, 0x19,
  },
  { // Level 5
    0x10, 0x21, 0x22, 0x23,
    0x1E, 0x24, 0x25, 0x26,
    0x1F, 0x28, 0x29, 0x27,
    0x20, 0x2A, 0x2B, 0x2C,
  },
  { // Level 6
    0x00, 0x01, 0x12, 0x00,
    0x01, 0x0E, 0x13, 0x12,
    0x2E, 0x15, 0x14, 0x2D,
    0x00, 0x2E, 0x2D, 0x00
  },
  { // Level 7
    0x01, 0x2F, 0x30, 0x23,
    0x31, 0x32, 0x01, 0x33,
    0x34, 0x35, 0x36, 0x37,
    0x2E, 0x38, 0x39, 0x3A
  },
  { // Level 8
    0x00, 0x00, 0x0C, 0x23,
    0x01, 0x10, 0x0E, 0x26,
    0x1E, 0x0E, 0x2C, 0x0B,
    0x20, 0x0D, 0x00, 0x00
  },
  { // Level 9
    0x01, 0x02, 0x02, 0x0A,
    0x1F, 0x0C, 0x33, 0x37,
    0x34, 0x28, 0x0D, 0x27,
    0x38, 0x18, 0x18, 0x3A
  },
  { // Level 10
    0x00, 0x00, 0x10, 0x23,
    0x00, 0x00, 0x20, 0x3B,
    0x10, 0x23, 0x10, 0x3B,
    0x20, 0x18, 0x18, 0x3A
  }
};

PROGMEM const byte itemSpawns[][15] = {
  // Format: <item1 id>, <item1 x>, <item1 y>, <item2 id>, <item2 x>, <item2 y>
  // 0, 0 for no item
  { // Level 1
    0, 0, 0,
    0, 0, 0,
  },
  { // Level 2
    ITEM_APPLE, 5, 5,
    ITEM_FLAME, 11, 11,
  },
  { // Level 3
    ITEM_APPLE, 5, 5,
    0, 0, 0,
  },
  { // Level 4
    ITEM_APPLE, 5, 5,
    ITEM_FLAME, 11, 11,
  },
  { // Level 5
    ITEM_APPLE, 7, 7,
    0, 0, 0,
  },
  { // Level 6
    ITEM_APPLE, 7, 7,
    0, 0, 0,
  },
  { // Level 7
    ITEM_APPLE, 7, 7,
    0, 0, 0,
  },
  { // Level 8
    ITEM_APPLE, 7, 7,
    0, 0, 0,
  },
  { // Level 9
    ITEM_APPLE, 7, 7,
    0, 0, 0,
  },
  { // Level 10
    0, 0, 0,
    0, 0, 0,
  },
};

PROGMEM const byte playerStartPosition[][3] = {
  // Format: <player.x>, <player.y>, <player.direction>
  {16,  16,  PLAYER_DIRECTION_RIGHT},
  {16,  16,  PLAYER_DIRECTION_RIGHT},
  {16,  16,  PLAYER_DIRECTION_DOWN},
  {16,  224, PLAYER_DIRECTION_UP},
  {128, 128, PLAYER_DIRECTION_LEFT},
  {80,  224, PLAYER_DIRECTION_UP},
  {224, 224, PLAYER_DIRECTION_UP},
  {224, 32,  PLAYER_DIRECTION_RIGHT},
  {80,  80,  PLAYER_DIRECTION_RIGHT},
  {224, 224, PLAYER_DIRECTION_UP},
};

const byte brickDensity[] = {
  4, 4, 3, 5, 5, 3, 3, 4, 3, 3,
  // Hard Mode
  4, 4, 3, 5, 5, 3, 3, 4, 3, 3,
};

// Enemies that spawn at random locations in each level
PROGMEM const byte enemySpawns[][7] = {
  {0x01, 0x01, 0x01, 0x01, NULL, NULL, NULL},
  {0x01, 0x01, 0x01, 0x01, 0x02, NULL, NULL},
  {0x01, 0x01, 0x02, 0x02, 0x02, NULL, NULL},
  {0x02, 0x02, 0x02, 0x02, 0x02, NULL, NULL},
  {0x02, 0x02, 0x02, 0x03, 0x03, NULL, NULL},
  {0x03, 0x03, 0x03, 0x03, NULL, NULL, NULL},
  {0x03, 0x03, 0x03, 0x03, 0x03, NULL, NULL},
  {0x02, 0x03, 0x05, 0x05, 0x05, NULL, NULL},
  {0x01, 0x01, 0x01, 0x05, 0x05, 0x05, NULL},
  {0x03, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05},
  // Hard Mode
  {0x01, 0x01, 0x01, 0x01, NULL, NULL, NULL},
  {0x01, 0x01, 0x01, 0x01, 0x02, NULL, NULL},
  {0x01, 0x01, 0x02, 0x02, 0x02, NULL, NULL},
  {0x02, 0x02, 0x02, 0x02, 0x02, NULL, NULL},
  {0x02, 0x02, 0x02, 0x03, 0x03, NULL, NULL},
  {0x03, 0x03, 0x03, 0x03, NULL, NULL, NULL},
  {0x03, 0x03, 0x03, 0x03, 0x03, NULL, NULL},
  {0x02, 0x03, 0x05, 0x05, 0x05, NULL, NULL},
  {0x01, 0x01, 0x01, 0x05, 0x05, 0x05, NULL},
  {0x03, 0x03, 0x05, 0x05, 0x05, 0x05, 0x05},
};

byte getTile(byte posX, byte posY) {
  return pgm_read_byte(
    &blocks[
      pgm_read_byte(&maps[(level-1)%NUM_LEVELS][posX / BLOCK_DIM + posY / BLOCK_DIM * MAP_DIM])
    ][
      (posX % BLOCK_DIM) + ((posY % BLOCK_DIM) * BLOCK_DIM)
    ]
  );
}

void drawLevel(byte posX, byte posY) {
  for (byte i = 0; i < BOARD_DIM; i++) {
    for (byte j = 0; j < BOARD_DIM; j++) {
      int wx = i * 16 + camera.xOffset + 16 - posX;
      int wy = j * 16 + camera.yOffset + 16 - posY;
      if (wx < 0 || wx > WIDTH + 16 || wy < 0 || wy > HEIGHT + 16) continue;

      if (getTile(i, j) == WALL) {
        arduboy.drawBitmap(wx - 16, wy - 16, SPRITES + WALL_SPRITE_OFFSET + (((level-1) % NUM_LEVELS) % 4 * SPRITE_COL_OFFSET), 16, 16, WHITE);
      }
    }
  }
}

