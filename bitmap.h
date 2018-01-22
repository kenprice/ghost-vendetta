#define SPRITE_COL_OFFSET         96
#define SPRITE_8_COL_OFFSET       32

#define BANSHEE_SPRITE_OFFSET     0
#define BANSHEE_SPRITE_MASK       (SPRITE_8_COL_OFFSET * 7) + 32
#define SNAKE_SPRITE_OFFSET       SPRITE_8_COL_OFFSET * 4
#define SLIME_SPRITE_OFFSET       SPRITE_8_COL_OFFSET
#define SLIME_CHILD_SPRITE_OFFSET SPRITE_8_COL_OFFSET * 3
#define ZOMBIE_SPRITE_OFFSET      16

#define SHRUB_SPRITE_OFFSET       SPRITE_COL_OFFSET * 4 + 64
#define BOULDER_SPRITE_OFFSET     SPRITE_COL_OFFSET * 4 + 32
#define WALL_SPRITE_OFFSET        64
#define TREE_SPRITE_OFFSET        SPRITE_COL_OFFSET * 4
#define TREE_DEAD_SPRITE_OFFSET   TREE_SPRITE_OFFSET + SPRITE_COL_OFFSET
#define CHEST_SPRITE_OFFSET       SPRITE_COL_OFFSET * 6 + 64
#define CHEST_OPEN_SPRITE_OFFSET  CHEST_SPRITE_OFFSET + SPRITE_COL_OFFSET

#define BOMB_SPRITE_OFFSET        (SPRITE_8_COL_OFFSET * 6)
#define FIRE_SPRITE_OFFSET        (SPRITE_COL_OFFSET * 6)

#define ITEM_APPLE_SPRITE_OFFSET  8
#define ITEM_FLAME_SPRITE_OFFSET  SPRITE_8_COL_OFFSET * 3 + 8

const unsigned char SPRITES_8[] PROGMEM = {
  0x70, 0x88, 0xa4, 0x84, 0xa4, 0x88, 0x70, 0x00, 0x38, 0x7c, 0xfc, 0xfd, 0x7b, 0xbc, 0x7c, 0x38,
  0x40, 0x1a, 0xcf, 0x5b, 0x6b, 0xf6, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x78, 0x84, 0xb2, 0x82, 0xb2, 0xb2, 0x84, 0x78, 0x00, 0x00, 0x1e, 0x36, 0x42, 0x36, 0x1e, 0x00,
  0x10, 0x10, 0x15, 0xe7, 0x55, 0x55, 0xf2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x70, 0x88, 0x84, 0x82, 0x8a, 0x9a, 0x84, 0x78, 0x03, 0x05, 0x0a, 0x54, 0x68, 0x30, 0x58, 0x80,
  0x40, 0x0a, 0xd7, 0x55, 0x6d, 0x76, 0x90, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x30, 0x58, 0x48, 0x58, 0x30, 0x00, 0x00, 0x78, 0xe4, 0xfe, 0xe1, 0x78, 0x04, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x60, 0x91, 0x8f, 0x80, 0xa0, 0xa0, 0x40, 0x00, 0x00, 0x00, 0x08, 0x14, 0x08, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x60, 0x92, 0x96, 0x98, 0x80, 0xa0, 0xa0, 0x40, 0x00, 0x00, 0x08, 0x00, 0x2a, 0x00, 0x08, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3c, 0x42, 0x95, 0xaf, 0x9f, 0xbf, 0x5e, 0x3c, 0x00, 0x08, 0x00, 0x08, 0x5d, 0x08, 0x00, 0x08,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x22, 0x08, 0x5d, 0x08, 0x22, 0x08,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const unsigned char SPRITES[] PROGMEM = {
  0x00, 0xc0, 0x30, 0x88, 0x44, 0x44, 0xa2, 0x12, 0x12, 0xa2, 0x44, 0x44, 0x88, 0x30, 0xc0, 0x00,
  0x00, 0x07, 0x0c, 0x6b, 0x94, 0xdb, 0xeb, 0x58, 0x58, 0xeb, 0xdb, 0x94, 0x6b, 0x0c, 0x07, 0x00,
  0x00, 0x00, 0x38, 0xd4, 0x0a, 0xd1, 0xe1, 0x41, 0x41, 0x81, 0x02, 0x02, 0x04, 0x18, 0xe0, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x02, 0x65, 0xdd, 0xfc, 0xe4, 0xe5, 0x7e, 0x3c, 0x04, 0x02, 0x01, 0x00,
  0xb3, 0x87, 0x36, 0xb8, 0x98, 0x63, 0x77, 0x76, 0x21, 0x0d, 0xdc, 0xeb, 0x63, 0x0d, 0x6e, 0x76,
  0x63, 0x09, 0x5c, 0xcd, 0xc3, 0x33, 0x38, 0xdb, 0xc3, 0xb7, 0x36, 0x70, 0xae, 0x8f, 0x34, 0x73,
  0x00, 0xc0, 0x30, 0x88, 0x44, 0x44, 0xa2, 0x12, 0x12, 0xa2, 0x44, 0x44, 0x88, 0x30, 0xc0, 0x00,
  0x00, 0x07, 0x0c, 0x0b, 0x74, 0xab, 0xeb, 0xd8, 0x58, 0x3b, 0x4b, 0x4c, 0x3b, 0x0c, 0x03, 0x00,
  0x00, 0x00, 0x70, 0xa8, 0x14, 0xa2, 0xc2, 0x82, 0x82, 0x02, 0x04, 0x04, 0x08, 0x30, 0xc0, 0x00,
  0x00, 0x00, 0x20, 0x53, 0x94, 0xbb, 0xdb, 0x58, 0x78, 0x4b, 0x4c, 0xb8, 0x98, 0x64, 0x03, 0x00,
  0xf0, 0xf6, 0x07, 0xf7, 0xf7, 0xf0, 0xf7, 0xf7, 0x00, 0x7b, 0x7b, 0x1b, 0xdb, 0xc0, 0x06, 0xf6,
  0xee, 0x00, 0xdc, 0xdd, 0xdd, 0x00, 0x76, 0x76, 0x06, 0xf7, 0xf7, 0xe0, 0xee, 0x0e, 0xee, 0xee,
  0x00, 0xe0, 0x18, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x04, 0x18, 0xe0, 0x00,
  0x00, 0x0d, 0x16, 0x7c, 0xbb, 0xec, 0xe8, 0x48, 0x48, 0xe8, 0xec, 0xbb, 0x7c, 0x16, 0x0d, 0x00,
  0x00, 0xe0, 0x18, 0x04, 0x02, 0x02, 0x81, 0x41, 0x41, 0xe1, 0xd1, 0x0a, 0xd4, 0x38, 0x00, 0x00,
  0x00, 0x01, 0x02, 0x04, 0x3c, 0x7e, 0xe5, 0xe4, 0xfc, 0xdd, 0x65, 0x02, 0x01, 0x00, 0x00, 0x00,
  0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x5f, 0x3f, 0x5f, 0x2f, 0x55, 0x2a, 0x55, 0x2a, 0x00,
  0x2b, 0x55, 0x2a, 0x55, 0x2a, 0x55, 0x2a, 0x00, 0x7f, 0x75, 0x7b, 0x7d, 0x3f, 0x5f, 0x3f, 0x5f,
  0x00, 0xc0, 0x30, 0x08, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x08, 0x30, 0xc0, 0x00,
  0x00, 0x19, 0x26, 0x24, 0x30, 0x2c, 0x70, 0x70, 0xf0, 0xf0, 0xac, 0x70, 0x1c, 0x0a, 0x07, 0x00,
  0x00, 0xc0, 0x30, 0x08, 0x04, 0x04, 0x02, 0x82, 0x82, 0xc2, 0xa2, 0x14, 0xa8, 0x70, 0x00, 0x00,
  0x00, 0x03, 0x64, 0x98, 0xb8, 0x4c, 0x4b, 0x78, 0x58, 0xdb, 0xbb, 0x94, 0x53, 0x20, 0x00, 0x00,
  0xac, 0x75, 0xf9, 0x36, 0xcf, 0xff, 0xe6, 0xd9, 0xbd, 0x3d, 0x9a, 0x66, 0xf6, 0xf5, 0x6b, 0x9a,
  0xf7, 0x6b, 0x9c, 0x6b, 0x76, 0x72, 0xad, 0xdd, 0x9e, 0x6d, 0xf3, 0xf7, 0x6e, 0x98, 0x6b, 0xf7,
  0x00, 0x50, 0xa8, 0x54, 0xa8, 0x54, 0xaa, 0x54, 0xaa, 0x54, 0xa8, 0x54, 0xa8, 0x50, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x02, 0x81, 0xc2, 0xff, 0xff, 0xc1, 0x82, 0x01, 0x00, 0x00, 0x00, 0x00,
  0xf8, 0xfe, 0x5f, 0x2f, 0x57, 0x2f, 0x17, 0x0b, 0x07, 0x0b, 0x07, 0x0b, 0x07, 0x0f, 0x5e, 0xf8,
  0x0f, 0x3a, 0x55, 0x82, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x20, 0x1f,
  0x00, 0x00, 0xa6, 0x6c, 0xec, 0x00, 0x7e, 0xd8, 0xb0, 0xec, 0x8e, 0xb1, 0x38, 0x88, 0xa4, 0x10,
  0x00, 0x00, 0x23, 0x39, 0x16, 0x1b, 0xed, 0x6f, 0x06, 0x19, 0x3a, 0x05, 0x37, 0x6c, 0x01, 0x03,
  0x00, 0x40, 0x88, 0x50, 0x20, 0x7a, 0xc4, 0x82, 0xe8, 0x10, 0xcc, 0x08, 0xa8, 0x40, 0x40, 0x00,
  0x00, 0x00, 0x01, 0x00, 0x06, 0x81, 0x40, 0xff, 0x7f, 0xc1, 0x21, 0x41, 0x82, 0x04, 0x00, 0x00,
  0xf8, 0xfe, 0x5f, 0x2f, 0x57, 0x2f, 0x17, 0x8b, 0x07, 0x2b, 0x07, 0x0b, 0x07, 0x0f, 0x5e, 0xf8,
  0x0f, 0x3a, 0x55, 0x82, 0x80, 0x84, 0x84, 0xc8, 0xb6, 0x90, 0x88, 0x88, 0x84, 0x40, 0x20, 0x1f,
  0x02, 0x3e, 0x74, 0x48, 0xb0, 0xc8, 0x7c, 0x04, 0x16, 0x2b, 0x3d, 0x37, 0x33, 0x61, 0xc2, 0x00,
  0x00, 0xe2, 0x71, 0x59, 0x6b, 0x6d, 0x36, 0x18, 0x78, 0x36, 0x1b, 0x0d, 0x06, 0x03, 0x4d, 0x3e,
  0x00, 0x00, 0x60, 0x00, 0x00, 0xe0, 0x10, 0x38, 0x44, 0x80, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00,
  0x00, 0x30, 0x4c, 0x9a, 0xa0, 0xd0, 0xef, 0xe0, 0xd8, 0xa7, 0xa0, 0xdc, 0xe3, 0x44, 0x38, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x60, 0x40, 0x00, 0x08, 0x03, 0x63, 0x73, 0x73, 0x60, 0x00, 0x81, 0x01, 0x31, 0x38, 0x38, 0x00,
  0x00, 0x00, 0xe0, 0x30, 0xe0, 0x70, 0xa0, 0xb0, 0xa0, 0x70, 0xe0, 0x30, 0xe0, 0x50, 0x00, 0x00,
  0x00, 0x00, 0x3e, 0x20, 0x3e, 0x3c, 0x3b, 0x38, 0x3b, 0x3c, 0x3e, 0x20, 0x3e, 0x15, 0x00, 0x00,
  0x00, 0x00, 0x18, 0x70, 0x00, 0x00, 0x00, 0xe0, 0x40, 0x80, 0x00, 0x80, 0xa0, 0x18, 0x00, 0x00,
  0x18, 0x27, 0x42, 0x9c, 0xa0, 0xd0, 0x2e, 0xa1, 0xd8, 0x27, 0xa0, 0xd7, 0xa8, 0x43, 0x3c, 0x00,
  0x00, 0xe0, 0xf8, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfc, 0xf8, 0xe0, 0x00,
  0x00, 0x0d, 0x1f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x1f, 0x0d, 0x00,
  0x00, 0x00, 0x38, 0x1c, 0x38, 0x1c, 0x0c, 0x0e, 0x0c, 0x1c, 0x38, 0x1c, 0x38, 0x10, 0x00, 0x00,
  0x00, 0x00, 0x3e, 0x20, 0x3e, 0x3c, 0x38, 0x38, 0x38, 0x3c, 0x3e, 0x20, 0x3e, 0x14, 0x00, 0x00,
};

const unsigned char TITLE[] PROGMEM = {
  0x02, 0x03, 0x83, 0x87, 0x8f, 0x9e, 0x3c, 0x01, 0xff, 0xff, 0x21, 0x21, 0x33, 0x7f, 0xee, 0xc0,
  0x10, 0x68, 0x28, 0x84, 0xe0, 0x9c, 0x83, 0x8f, 0xfc, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x01, 0xff,
  0x03, 0x1e, 0xf8, 0xc0, 0x00, 0x80, 0x60, 0x1c, 0x03, 0xff, 0xff, 0x01, 0x00, 0x00, 0x01, 0xff,
  0xff, 0x21, 0x21, 0x21, 0xf1, 0x07, 0x00, 0x00, 0x1c, 0x3e, 0x3f, 0x73, 0x61, 0xe1, 0xc7, 0x87,
  0x00, 0x00, 0x01, 0xff, 0xff, 0x21, 0x20, 0x20, 0x20, 0x20, 0x21, 0xff, 0xff, 0x01, 0x00, 0x01,
  0xff, 0xff, 0x21, 0x21, 0x21, 0xf1, 0x03, 0x07, 0x00, 0x01, 0x00, 0x00, 0x01, 0x03, 0x03, 0x08,
  0x0f, 0x0f, 0x08, 0x0b, 0x09, 0x0c, 0x07, 0x03, 0x00, 0x08, 0x0c, 0x0b, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x09, 0x0f, 0x0c, 0x08, 0x00, 0x08, 0x0f, 0x08, 0x00, 0x00, 0x07, 0x0e, 0x03, 0x00, 0x00,
  0x08, 0x0f, 0x0f, 0x08, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0x0f, 0x08, 0x08, 0x08, 0x0c, 0x07, 0x03, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0e,
};

const unsigned char TITLE_URL[] PROGMEM = {
  0x1f, 0x11, 0x15, 0x1d, 0x00, 0x1f, 0x00, 0x01, 0x1f, 0x01, 0x00, 0x1f, 0x04, 0x1f, 0x00, 0x1f,
  0x10, 0x1f, 0x00, 0x1f, 0x15, 0x1b, 0x00, 0x10, 0x00, 0x1f, 0x11, 0x11, 0x00, 0x1f, 0x11, 0x1f,
  0x00, 0x1f, 0x06, 0x06, 0x1f, 0x00, 0x18, 0x0e, 0x03, 0x00, 0x1f, 0x04, 0x1b, 0x00, 0x1f, 0x15,
  0x15, 0x00, 0x1f, 0x06, 0x0c, 0x1f, 0x00, 0x1f, 0x05, 0x07, 0x00, 0x1f, 0x05, 0x1b, 0x00, 0x1f,
  0x00, 0x1f, 0x11, 0x11, 0x00, 0x1f, 0x15, 0x15,
};

