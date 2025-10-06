/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --font PixelOperatorMono.ttf --size 16 --format lvgl --bpp 1 --range 0x20-0x7F
 *--no-compress -o pixel_operator_mono.c
 *
 * Released by Jayvee Enaguas (HarvettFox96) <harvettfox96 [at] protonmail [dot] com>
 * licensed under a Creative Commons Zero (CC0) 1.0 <https://creativecommons.org/licenses/zero/1.0/>
 * (c) 2009-2018.
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include <lvgl.h>
#endif

#ifndef PIXEL_OPERATOR_MONO
#define PIXEL_OPERATOR_MONO 1
#endif

#if PIXEL_OPERATOR_MONO

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfe, 0x80,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x49, 0x2f, 0xd2, 0x49, 0x2f, 0xd2, 0x48,

    /* U+0024 "$" */
    0x21, 0x1d, 0x5a, 0x51, 0xc5, 0x2d, 0x5c, 0x42, 0x0,

    /* U+0025 "%" */
    0x41, 0x42, 0x92, 0x41, 0x4, 0x92, 0x85, 0x4,

    /* U+0026 "&" */
    0x74, 0x61, 0x7, 0x46, 0x31, 0x78,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x2a, 0x49, 0x22, 0x20,

    /* U+0029 ")" */
    0x88, 0x92, 0x4a, 0x80,

    /* U+002A "*" */
    0x25, 0x5d, 0x52, 0x0,

    /* U+002B "+" */
    0x21, 0x3e, 0x42, 0x0,

    /* U+002C "," */
    0x58,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x24, 0xa4, 0xa4, 0x80,

    /* U+0030 "0" */
    0x74, 0x63, 0x3a, 0xe6, 0x31, 0x70,

    /* U+0031 "1" */
    0x23, 0x28, 0x42, 0x10, 0x84, 0xf8,

    /* U+0032 "2" */
    0x74, 0x42, 0x22, 0x22, 0x10, 0xf8,

    /* U+0033 "3" */
    0x74, 0x42, 0x13, 0x4, 0x31, 0x70,

    /* U+0034 "4" */
    0x8, 0xca, 0x98, 0xfc, 0x21, 0x8,

    /* U+0035 "5" */
    0xfc, 0x21, 0xe0, 0x84, 0x31, 0x70,

    /* U+0036 "6" */
    0x74, 0x61, 0xf, 0x46, 0x31, 0x70,

    /* U+0037 "7" */
    0xf8, 0x42, 0x22, 0x22, 0x10, 0x80,

    /* U+0038 "8" */
    0x74, 0x63, 0x17, 0x46, 0x31, 0x70,

    /* U+0039 "9" */
    0x74, 0x63, 0x17, 0x84, 0x31, 0x70,

    /* U+003A ":" */
    0x82,

    /* U+003B ";" */
    0x40, 0x5, 0x80,

    /* U+003C "<" */
    0x2a, 0x22,

    /* U+003D "=" */
    0xf0, 0xf0,

    /* U+003E ">" */
    0x88, 0xa8,

    /* U+003F "?" */
    0x74, 0x42, 0x22, 0x10, 0x80, 0x20,

    /* U+0040 "@" */
    0x7d, 0x6, 0x6d, 0x5a, 0xb5, 0x67, 0x40, 0x7c,

    /* U+0041 "A" */
    0x74, 0x63, 0x18, 0xfe, 0x31, 0x88,

    /* U+0042 "B" */
    0xf4, 0x63, 0x1f, 0x46, 0x31, 0xf0,

    /* U+0043 "C" */
    0x74, 0x61, 0x8, 0x42, 0x11, 0x70,

    /* U+0044 "D" */
    0xf4, 0x63, 0x18, 0xc6, 0x31, 0xf0,

    /* U+0045 "E" */
    0xfc, 0x21, 0xe, 0x42, 0x10, 0xf8,

    /* U+0046 "F" */
    0xfc, 0x21, 0xe, 0x42, 0x10, 0x80,

    /* U+0047 "G" */
    0x74, 0x61, 0x9, 0xc6, 0x31, 0x78,

    /* U+0048 "H" */
    0x8c, 0x63, 0x1f, 0xc6, 0x31, 0x88,

    /* U+0049 "I" */
    0xf9, 0x8, 0x42, 0x10, 0x84, 0xf8,

    /* U+004A "J" */
    0x3c, 0x20, 0x82, 0x8, 0x20, 0xa2, 0x70,

    /* U+004B "K" */
    0x8c, 0x65, 0x4c, 0x52, 0x51, 0x88,

    /* U+004C "L" */
    0x84, 0x21, 0x8, 0x42, 0x10, 0xf8,

    /* U+004D "M" */
    0x83, 0x7, 0x1d, 0x59, 0x30, 0x60, 0xc1, 0x82,

    /* U+004E "N" */
    0x8c, 0x63, 0x9a, 0xce, 0x31, 0x88,

    /* U+004F "O" */
    0x74, 0x63, 0x18, 0xc6, 0x31, 0x70,

    /* U+0050 "P" */
    0xf4, 0x63, 0x1f, 0x42, 0x10, 0x80,

    /* U+0051 "Q" */
    0x74, 0x63, 0x18, 0xc6, 0xb2, 0x68,

    /* U+0052 "R" */
    0xf4, 0x63, 0x1f, 0x52, 0x51, 0x88,

    /* U+0053 "S" */
    0x74, 0x61, 0x7, 0x4, 0x31, 0x70,

    /* U+0054 "T" */
    0xf9, 0x8, 0x42, 0x10, 0x84, 0x20,

    /* U+0055 "U" */
    0x8c, 0x63, 0x18, 0xc6, 0x31, 0x70,

    /* U+0056 "V" */
    0x8c, 0x63, 0x18, 0xc6, 0x2a, 0x20,

    /* U+0057 "W" */
    0x83, 0x6, 0x4c, 0x99, 0x32, 0x64, 0xc9, 0x6c,

    /* U+0058 "X" */
    0x8c, 0x62, 0xa2, 0x2a, 0x31, 0x88,

    /* U+0059 "Y" */
    0x8c, 0x62, 0xa2, 0x10, 0x84, 0x20,

    /* U+005A "Z" */
    0xf8, 0x42, 0x22, 0x22, 0x10, 0xf8,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0xe0,

    /* U+005C "\\" */
    0x92, 0x24, 0x89, 0x20,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0xe0,

    /* U+005E "^" */
    0x22, 0xa2,

    /* U+005F "_" */
    0xff,

    /* U+0060 "`" */
    0x90,

    /* U+0061 "a" */
    0x74, 0x42, 0xf8, 0xc5, 0xe0,

    /* U+0062 "b" */
    0x84, 0x3d, 0x18, 0xc6, 0x31, 0xf0,

    /* U+0063 "c" */
    0x74, 0x61, 0x8, 0x45, 0xc0,

    /* U+0064 "d" */
    0x8, 0x5f, 0x18, 0xc6, 0x31, 0x78,

    /* U+0065 "e" */
    0x74, 0x63, 0xf8, 0x45, 0xc0,

    /* U+0066 "f" */
    0x34, 0x4f, 0x44, 0x44, 0x40,

    /* U+0067 "g" */
    0x7c, 0x63, 0x18, 0xbc, 0x31, 0x70,

    /* U+0068 "h" */
    0x84, 0x3d, 0x18, 0xc6, 0x31, 0x88,

    /* U+0069 "i" */
    0x20, 0x38, 0x42, 0x10, 0x84, 0xf8,

    /* U+006A "j" */
    0x8, 0xe, 0x10, 0x84, 0x21, 0xc, 0x5c,

    /* U+006B "k" */
    0x84, 0x23, 0x2a, 0x62, 0x92, 0x88,

    /* U+006C "l" */
    0xe1, 0x8, 0x42, 0x10, 0x84, 0xf8,

    /* U+006D "m" */
    0xed, 0x26, 0x4c, 0x99, 0x30, 0x60, 0x80,

    /* U+006E "n" */
    0xf4, 0x63, 0x18, 0xc6, 0x20,

    /* U+006F "o" */
    0x74, 0x63, 0x18, 0xc5, 0xc0,

    /* U+0070 "p" */
    0xf4, 0x63, 0x18, 0xc7, 0xd0, 0x80,

    /* U+0071 "q" */
    0x7c, 0x63, 0x18, 0xc5, 0xe1, 0x8,

    /* U+0072 "r" */
    0x9d, 0x31, 0x8, 0x42, 0x0,

    /* U+0073 "s" */
    0x74, 0x60, 0xe0, 0xc5, 0xc0,

    /* U+0074 "t" */
    0x4f, 0x44, 0x44, 0x43,

    /* U+0075 "u" */
    0x8c, 0x63, 0x18, 0xc5, 0xc0,

    /* U+0076 "v" */
    0x8c, 0x63, 0x18, 0xa8, 0x80,

    /* U+0077 "w" */
    0x83, 0x6, 0x4c, 0x99, 0x32, 0x5b, 0x0,

    /* U+0078 "x" */
    0x8c, 0x54, 0x45, 0x46, 0x20,

    /* U+0079 "y" */
    0x8c, 0x63, 0x18, 0xbc, 0x31, 0x70,

    /* U+007A "z" */
    0xf8, 0x44, 0x44, 0x43, 0xe0,

    /* U+007B "{" */
    0x34, 0x44, 0x84, 0x44, 0x30,

    /* U+007C "|" */
    0xff, 0x80,

    /* U+007D "}" */
    0xc2, 0x22, 0x12, 0x22, 0xc0,

    /* U+007E "~" */
    0x66, 0x60};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0,
     .adv_w = 0,
     .box_w = 0,
     .box_h = 0,
     .ofs_x = 0,
     .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 128, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 128, .box_w = 1, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 128, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 5, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 128, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 21, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 35, .adv_w = 128, .box_w = 1, .box_h = 3, .ofs_x = 3, .ofs_y = 6},
    {.bitmap_index = 36, .adv_w = 128, .box_w = 3, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 128, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 128, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 48, .adv_w = 128, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 52, .adv_w = 128, .box_w = 2, .box_h = 3, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 53, .adv_w = 128, .box_w = 4, .box_h = 1, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 54, .adv_w = 128, .box_w = 1, .box_h = 1, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 128, .box_w = 3, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 59, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 71, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 77, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 128, .box_w = 1, .box_h = 7, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 128, .box_w = 2, .box_h = 9, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 123, .adv_w = 128, .box_w = 3, .box_h = 5, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 125, .adv_w = 128, .box_w = 4, .box_h = 3, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 127, .adv_w = 128, .box_w = 3, .box_h = 5, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 129, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 128, .box_w = 3, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 128, .box_w = 3, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 128, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 128, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 318, .adv_w = 128, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 319, .adv_w = 128, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 320, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 325, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 128, .box_w = 4, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 358, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 370, .adv_w = 128, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 377, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 412, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 418, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 128, .box_w = 4, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 460, .adv_w = 128, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 128, .box_w = 4, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 128, .box_w = 1, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 128, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 128, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 7}};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] = {{.range_start = 32,
                                                .range_length = 95,
                                                .glyph_id_start = 1,
                                                .unicode_list = NULL,
                                                .glyph_id_ofs_list = NULL,
                                                .list_length = 0,
                                                .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY}};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};

/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t pixel_operator_mono = {
#else
lv_font_t pixel_operator_mono = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt, /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt, /*Function pointer to get glyph's bitmap*/
    .line_height = 13,                              /*The maximum line height required by the font*/
    .base_line = 2, /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -3,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc, /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};

#endif /*#if PIXEL_OPERATOR_MONO*/
