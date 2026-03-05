/*
 * This file is part of 4-e <https://mattiebee.dev/4-e>.
 *
 * Copyright 2024-2026 Mattie Behrens.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * “Software”), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef INCLUDE_GRAPHICS_H
#define INCLUDE_GRAPHICS_H

#include <tonc.h>

// character (tile) base block, for tile artwork
#define CBB 0

#define TILE_EMPTY 0

#define TILE_DIAMOND_QUADRANT 1

#define TILE_FRAME 2
#define TILE_FRAME_HORIZONTAL_EDGE 3
#define TILE_FRAME_VERTICAL_EDGE 4
#define TILE_FRAME_CORNER 5

#define TILE_WINDOW 6
#define TILE_WINDOW_HORIZONTAL_EDGE 7
#define TILE_WINDOW_VERTICAL_EDGE 8
#define TILE_WINDOW_CORNER 9

// screen base block, for tilemaps
#define SBB_BACKGROUND 31
#define SBB_FRAME 30
#define SBB_WINDOW 29
#define SBB_TEXT 28

#define CLR_PATTERN_DARK_BLUE RGB15(18, 21, 26)
#define CLR_PATTERN_LIGHT_BLUE RGB15(23, 25, 28)

#define CLR_FRAME_YELLOW RGB15(28, 28, 10)
#define CLR_FRAME_EDGE_BLUE RGB15(9, 12, 14)

#define CLR_WINDOW_WHITE RGB15(30, 30, 30)
#define CLR_WINDOW_EDGE_BLUE RGB15(68, 96, 192)

#define CLR_TEXT_LIGHT_BLUE RGB15(8, 12, 20)
#define CLR_TEXT_DARK_BLUE RGB15(4, 6, 10)
#define CLR_TEXT_YELLOW RGB15(26, 23, 8)
#define CLR_TEXT_RED RGB15(17, 6, 5)

void start_display();
void animate_frame();

#endif /* INCLUDE_GRAPHICS_H */
