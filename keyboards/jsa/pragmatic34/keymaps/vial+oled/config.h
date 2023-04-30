#pragma once

#define VIAL_KEYBOARD_UID {0xA4, 0x6E, 0xAE, 0xC4, 0x38, 0x71, 0x57, 0x22}

#define DYNAMIC_KEYMAP_LAYER_COUNT 8

#define OLED_BRIGHTNESS 128

// 354 bytes, 6x8 font, 59 characters, 6 bytes per character,
// From Space to Z
#define OLED_FONT_START     32   // SPACE
#define OLED_FONT_END       90   // Z
#define OLED_FONT_WIDTH     6
#define OLED_FONT_HEIGHT    8
#define OLED_FONT_SIZE      2    // 1 or 2
#define OLED_FONT_H         "glcdfont.c"
#define OLED_FONT_INTERLACING true

#define OLED_UPDATE_INTERVAL 100 //ms 一定要設，不然不會清除畫面。
