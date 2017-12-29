#define SPRITE_COL_OFFSET       320
#define SPRITE_ROW_OFFSET       256

#define BANSHEE_SPRITE_OFFSET   0
#define SNAKE_SPRITE_OFFSET     160

#define WALL_1_SPRITE_OFFSET    SPRITE_COL_OFFSET * 7 + 96
#define TREE_SPRITE_OFFSET      SPRITE_COL_OFFSET * 4
#define TREE_DEAD_SPRITE_OFFSET TREE_SPRITE_OFFSET + SPRITE_COL_OFFSET
#define CHEST_SPRITE_OFFSET     SPRITE_COL_OFFSET * 6 + 64

#define BOMB_SPRITE_OFFSET      SPRITE_COL_OFFSET + 96
#define FIRE_SPRITE_OFFSET      64

const unsigned char sprites[] PROGMEM = {
0x00, 0xc0, 0x30, 0x88, 0x44, 0x44, 0xa2, 0x12, 0x12, 0xa2, 0x44, 0x44, 0x88, 0x30, 0xc0, 0x00,
0x00, 0x7, 0xc, 0x6b, 0x94, 0xdb, 0xeb, 0x58, 0x58, 0xeb, 0xdb, 0x94, 0x6b, 0xc, 0x7, 0x00,
0x00, 0x00, 0x38, 0xd4, 0xa, 0xd1, 0xe1, 0x41, 0x41, 0x81, 0x2, 0x2, 0x4, 0x18, 0xe0, 0x00,
0x00, 0x00, 0x00, 0x1, 0x2, 0x65, 0xdd, 0xfc, 0xe4, 0xe5, 0x7e, 0x3c, 0x4, 0x2, 0x1, 0x00,
0x00, 0x00, 0xe, 0x00, 0x00, 0xe0, 0x10, 0x38, 0x44, 0x80, 0x00, 0x00, 0x00, 0x86, 0x00, 0x00,
0x00, 0x30, 0x4c, 0x9a, 0xa0, 0xd0, 0xef, 0xe0, 0xd8, 0xa7, 0xa0, 0xdc, 0xe3, 0x44, 0x38, 0x00,
0x38, 0x7c, 0xfc, 0xfd, 0x7b, 0xbc, 0x7c, 0x38, 0x00, 0x00, 0x1e, 0x36, 0x42, 0x36, 0x1e, 0x00,
0x3, 0x5, 0xa, 0x54, 0x68, 0x30, 0x58, 0x80, 0x00, 0x78, 0xe4, 0xfe, 0xe1, 0x78, 0x4, 0x00,
0x70, 0x88, 0xa4, 0x84, 0xa4, 0x88, 0x70, 0x00, 0x78, 0x84, 0xb2, 0x82, 0xb2, 0xb2, 0x84, 0x78,
0x70, 0x88, 0x84, 0x82, 0x8a, 0x9a, 0x84, 0x78, 0x00, 0x00, 0x30, 0x58, 0x48, 0x58, 0x30, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xc, 0x12, 0x12, 0x11, 0x14, 0x14, 0x8, 0x00, 0x00, 0x00, 0x00,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x00, 0xc0, 0x30, 0x88, 0x44, 0x44, 0xa2, 0x12, 0x12, 0xa2, 0x44, 0x44, 0x88, 0x30, 0xc0, 0x00,
0x00, 0x7, 0xc, 0xb, 0x74, 0xab, 0xeb, 0xd8, 0x58, 0x3b, 0x4b, 0x4c, 0x3b, 0xc, 0x3, 0x00,
0x00, 0x00, 0x70, 0xa8, 0x14, 0xa2, 0xc2, 0x82, 0x82, 0x2, 0x4, 0x4, 0x8, 0x30, 0xc0, 0x00,
0x00, 0x00, 0x20, 0x53, 0x94, 0xbb, 0xdb, 0x58, 0x78, 0x4b, 0x4c, 0xb8, 0x98, 0x64, 0x3, 0x00,
0x00, 0x00, 0x18, 0x70, 0x00, 0x00, 0x00, 0xe0, 0x40, 0x80, 0x00, 0x80, 0xa0, 0x18, 0x00, 0x00,
0x18, 0x27, 0x42, 0x9c, 0xa0, 0xd0, 0x2e, 0xa1, 0xd8, 0x27, 0xa0, 0xd7, 0xa8, 0x43, 0x3c, 0x00,
0x3c, 0x42, 0x95, 0xaf, 0x9f, 0xbf, 0x5e, 0x3c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xc, 0x12, 0x12, 0x11, 0x14, 0x14, 0x8, 0x00, 0x00, 0x00, 0x00,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x00, 0xe0, 0x18, 0x4, 0x2, 0x2, 0x1, 0x1, 0x1, 0x1, 0x2, 0x2, 0x4, 0x18, 0xe0, 0x00,
0x00, 0xd, 0x16, 0x7c, 0xbb, 0xec, 0xe8, 0x48, 0x48, 0xe8, 0xec, 0xbb, 0x7c, 0x16, 0xd, 0x00,
0x00, 0xc0, 0x30, 0x88, 0x44, 0xc4, 0x22, 0x12, 0x12, 0x22, 0xc4, 0x44, 0x88, 0x30, 0xc0, 0x00,
0x00, 0x7, 0xc, 0x3b, 0xcc, 0xcb, 0xfb, 0x58, 0x58, 0xfb, 0xcb, 0xcc, 0x3b, 0xc, 0x7, 0x00,
0x00, 0x00, 0x98, 0x70, 0xc0, 0x00, 0x00, 0x2, 0x00, 0x80, 0x40, 0xe0, 0x20, 0x18, 0x00, 0x00,
0x1e, 0x21, 0x40, 0x9c, 0xa3, 0xd0, 0xee, 0xe4, 0xd8, 0xa1, 0xa2, 0xdc, 0xe1, 0x42, 0x3c, 0x00,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xc, 0x12, 0x12, 0x11, 0x14, 0x14, 0x8, 0x00, 0x00, 0x00, 0x00,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x00, 0xc0, 0x30, 0x8, 0x4, 0x4, 0x2, 0x2, 0x2, 0x2, 0x4, 0x4, 0x8, 0x30, 0xc0, 0x00,
0x00, 0x19, 0x26, 0x24, 0x30, 0x2c, 0x70, 0x70, 0xf0, 0xf0, 0xac, 0x70, 0x1c, 0xa, 0x7, 0x00,
0x00, 0x00, 0x38, 0xd4, 0xa, 0xd1, 0xe1, 0x41, 0x41, 0x81, 0x2, 0x2, 0x4, 0x18, 0xe0, 0x00,
0x00, 0x00, 0x00, 0x1, 0x2, 0x65, 0xdd, 0xfc, 0xe4, 0xe5, 0x7e, 0x3c, 0x4, 0x2, 0x1, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe8, 0x44, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00,
0x18, 0x27, 0x42, 0x9c, 0xa0, 0xd0, 0x2e, 0xa1, 0xd8, 0x27, 0xa0, 0xd7, 0xa8, 0x43, 0x3c, 0x00,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xc, 0x12, 0x12, 0x11, 0x14, 0x14, 0x8, 0x00, 0x00, 0x00, 0x00,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x00, 0x50, 0xa8, 0x54, 0xa8, 0x54, 0xaa, 0x54, 0xaa, 0x54, 0xa8, 0x54, 0xa8, 0x50, 0x00, 0x00,
0x00, 0x00, 0x00, 0x1, 0x2, 0x81, 0xc2, 0xff, 0xff, 0xc1, 0x82, 0x1, 0x00, 0x00, 0x00, 0x00,
0xf8, 0xfe, 0x5f, 0x2f, 0x57, 0x2f, 0x17, 0xb, 0x7, 0xb, 0x7, 0xb, 0x7, 0xf, 0x5e, 0xf8,
0xf, 0x3a, 0x55, 0x82, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x20, 0x1f,
0x40, 0x22, 0xa6, 0x6c, 0xec, 0x00, 0x7e, 0xd8, 0xb0, 0xec, 0x8e, 0xb1, 0x38, 0x88, 0xa4, 0x10,
0x00, 0x6, 0x23, 0x39, 0x16, 0x1b, 0xed, 0x6f, 0x6, 0x19, 0x3a, 0x5, 0x37, 0x6c, 0x1, 0x3,
0xb3, 0x87, 0x36, 0xb8, 0x98, 0x63, 0x77, 0x76, 0x21, 0xd, 0xdc, 0xeb, 0x63, 0xd, 0x6e, 0x76,
0x63, 0x9, 0x5c, 0xcd, 0xc3, 0x33, 0x38, 0xdb, 0xc3, 0xb7, 0x36, 0x70, 0xae, 0x8f, 0x34, 0x73,
0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f, 0x5f, 0x3f, 0x5f, 0x2f, 0x55, 0x2a, 0x55, 0x2a, 0x00,
0x2b, 0x55, 0x2a, 0x55, 0x2a, 0x55, 0x2a, 0x00, 0x7f, 0x75, 0x7b, 0x7d, 0x3f, 0x5f, 0x3f, 0x5f,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xb6, 0x5d, 0x2e, 0x7, 0x2, 0x7, 0x3, 0x1, 0x1, 0x2, 0x7, 0x3, 0x2, 0x5, 0x3, 0x1,
0xa5, 0xdb, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8, 0x76, 0xeb,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0xc0, 0xa0, 0x78, 0xa7,
0xa2, 0xd5, 0x8b, 0x46, 0xee, 0xdf, 0x8e, 0xa7, 0x6f, 0xd4, 0xc6, 0x15, 0xba, 0x75, 0x73, 0x27,
0x16, 0xbd, 0x6a, 0x71, 0xb6, 0x15, 0x20, 0x44, 0xe, 0x55, 0xa8, 0x74, 0x2a, 0x34, 0x82, 0x11,
0xa, 0xd, 0xb, 0x7, 0xa, 0x6, 0xd, 0x7, 0x5, 0xa, 0x5, 0xc, 0xb, 0x7, 0xb, 0x5,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x40, 0x88, 0x50, 0x20, 0x7a, 0xc4, 0x82, 0xe8, 0x10, 0xcc, 0x8, 0xa8, 0x40, 0x40, 0x00,
0x00, 0x00, 0x1, 0x00, 0x6, 0x81, 0x40, 0xff, 0x7f, 0xc1, 0x21, 0x41, 0x82, 0x4, 0x00, 0x00,
0xf8, 0xfe, 0x5f, 0x2f, 0x57, 0x2f, 0x17, 0x8b, 0x7, 0x2b, 0x7, 0xb, 0x7, 0xf, 0x5e, 0xf8,
0xf, 0x3a, 0x55, 0x82, 0x80, 0x84, 0x84, 0xc8, 0xb6, 0x90, 0x88, 0x88, 0x84, 0x40, 0x20, 0x1f,
0x2, 0x3e, 0x74, 0x48, 0xb0, 0xc8, 0x7c, 0x4, 0x16, 0x2b, 0x3d, 0x37, 0x33, 0x61, 0xc2, 0x00,
0x00, 0xe2, 0x71, 0x59, 0x6b, 0x6d, 0x36, 0x18, 0x78, 0x36, 0x1b, 0xd, 0x6, 0x3, 0x4d, 0x3e,
0xf0, 0xf6, 0x7, 0xf7, 0xf7, 0xf0, 0xf7, 0xf7, 0x00, 0x7b, 0x7b, 0x1b, 0xdb, 0xc0, 0x6, 0xf6,
0xee, 0x00, 0xdc, 0xdd, 0xdd, 0x00, 0x76, 0x76, 0x6, 0xf7, 0xf7, 0xe0, 0xee, 0xe, 0xee, 0xee,
0xa7, 0x64, 0x7c, 0x97, 0xc, 0x8, 0x98, 0xfc, 0xa7, 0x24, 0x28, 0xf8, 0xcc, 0x87, 0x81, 0xc9,
0xcf, 0x7a, 0xa2, 0xc3, 0xc3, 0x65, 0x78, 0xcc, 0x4f, 0xe9, 0x50, 0x70, 0xb9, 0x4f, 0x84, 0x84,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x1, 0x2, 0x7, 0x3, 0x2, 0x5, 0x3, 0x1, 0x1, 0x2, 0x3, 0x5, 0x3, 0x5, 0x2, 0x1,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xeb, 0x9c, 0xd, 0x47, 0xef, 0xdf, 0x8f, 0xe7, 0xef, 0xd3, 0xc2, 0x15, 0xbe, 0x76, 0x77, 0x25,
0x8c, 0x59, 0x3a, 0x71, 0xd3, 0x25, 0x30, 0x44, 0xe, 0x5d, 0xac, 0x7e, 0x34, 0xe, 0x86, 0x11,
0x84, 0x6b, 0x97, 0xfe, 0xd5, 0x6e, 0x5b, 0xee, 0xca, 0x9d, 0x1a, 0xad, 0x5e, 0xac, 0x92, 0x7b,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1, 0x1, 0x2, 0x3, 0x6, 0x7, 0xb, 0x1e, 0x2f,
0xa, 0x5, 0xe, 0x4, 0xe, 0x5, 0xa, 0x5, 0xf, 0x3, 0x5, 0x3, 0x1, 0x1, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x40, 0xe0, 0xe0, 0xd0, 0x50, 0x48, 0x48, 0x44, 0xc4, 0x72, 0x4e, 0x43,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3, 0xc, 0x30, 0xc1, 0xb1, 0xce, 0xc3, 0xa4, 0xa4, 0x98, 0x98,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00,
0x60, 0x40, 0x00, 0x8, 0x3, 0x63, 0x73, 0x73, 0x60, 0x00, 0x81, 0x1, 0x31, 0x38, 0x38, 0x00,
0x00, 0x00, 0xe0, 0x30, 0xe0, 0x70, 0xa0, 0xb0, 0xa0, 0x70, 0xe0, 0x30, 0xe0, 0x50, 0x00, 0x00,
0x00, 0x00, 0x3e, 0x20, 0x3e, 0x3c, 0x3b, 0x38, 0x3b, 0x3c, 0x3e, 0x20, 0x3e, 0x15, 0x00, 0x00,
0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0x34, 0xfe, 0xff, 0xfe, 0xfe, 0xff, 0xff, 0xfe, 0x4c,
0xfe, 0xfe, 0xff, 0xf4, 0xfe, 0xff, 0xfe, 0xfe, 0xff, 0xfe, 0xfe, 0x4c, 0xfe, 0xff, 0xfe, 0xff,
0x53, 0x8a, 0x6, 0xc9, 0x30, 0x00, 0x19, 0x26, 0x42, 0xc2, 0x65, 0x99, 0x9, 0xa, 0x94, 0x65,
0x8, 0x94, 0x63, 0x94, 0x89, 0x8d, 0x52, 0x22, 0x61, 0x92, 0xc, 0x8, 0x91, 0x67, 0x94, 0x8,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x1, 0x2, 0x3, 0x5, 0x3, 0x5, 0x2, 0x1, 0x1, 0x2, 0x3, 0x5, 0x3, 0x17, 0x6d, 0xda,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x6e, 0xb9,
0x5, 0x6b, 0x97, 0x7e, 0xd5, 0x6d, 0x3a, 0x5e, 0x8a, 0x54, 0x1a, 0xa9, 0xb7, 0x6f, 0xb6, 0x6b,
0x3a, 0x17, 0xe, 0x7, 0x5, 0x3, 0x3, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xaf, 0xde, 0x8b, 0x46, 0xee, 0xdd, 0x8e, 0x67, 0xef, 0x54, 0xc6, 0x15, 0xba, 0x75, 0x70, 0xca,
0xa8, 0x51, 0x2a, 0x71, 0xb6, 0x15, 0x20, 0x44, 0xe, 0x55, 0xa8, 0x74, 0x2a, 0x35, 0xb2, 0x6d,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x43, 0x4e, 0x72, 0xc4, 0x44, 0x48, 0x48, 0x50, 0xd0, 0xe0, 0xe0, 0x40, 0x00, 0x00, 0x00, 0x00,
0x98, 0x98, 0xa4, 0xa4, 0xc3, 0xce, 0xb1, 0xc1, 0x30, 0xe, 0x1, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x38, 0x1c, 0x38, 0x1c, 0xc, 0xe, 0xc, 0x1c, 0x38, 0x1c, 0x38, 0x10, 0x00, 0x00,
0x00, 0x00, 0x3e, 0x20, 0x3e, 0x3c, 0x38, 0x38, 0x38, 0x3c, 0x3e, 0x20, 0x3e, 0x14, 0x00, 0x00,
0xac, 0x75, 0xf9, 0x36, 0xcf, 0xff, 0xe6, 0xd9, 0xbd, 0x3d, 0x9a, 0x66, 0xf6, 0xf5, 0x6b, 0x9a,
0xf7, 0x6b, 0x9c, 0x6b, 0x76, 0x72, 0xad, 0xdd, 0x9e, 0x6d, 0xf3, 0xf7, 0x6e, 0x98, 0x6b, 0xf7,
0x40, 0xc0, 0xc0, 0xc0, 0x10, 0xf0, 0xf0, 0xf0, 0x4, 0xfc, 0xfc, 0xfc, 0x81, 0xff, 0xff, 0xff,
0xa0, 0xbf, 0xbf, 0xbf, 0x88, 0xef, 0xef, 0xef, 0xe2, 0xfb, 0xfb, 0xfb, 0xf8, 0xfe, 0xfe, 0xfe,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xcd, 0x76, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xaf, 0x53, 0x80, 0xc0, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xae, 0xdd, 0x8f, 0x46, 0xee, 0xdd, 0x8e, 0xe7, 0xef, 0xd3, 0xc3, 0x17, 0xbf, 0x37, 0xd2, 0x68,
0xa8, 0x51, 0x3a, 0x71, 0xe3, 0x35, 0x30, 0x44, 0xe, 0x5d, 0xac, 0x7e, 0x3c, 0x16, 0x88, 0x53,
0x00, 0x1, 0x2, 0x1, 0x6, 0x5, 0xb, 0xf, 0xa, 0x6, 0x6, 0xd, 0xa, 0x7, 0x2, 0x5,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,

};


