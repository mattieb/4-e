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

#define TILE_CHARBLOCK 0

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

#define BACKGROUND_SCREENBLOCK 31
#define FRAME_SCREENBLOCK 30
#define WINDOW_SCREENBLOCK 29

#define BACKGROUND_PATTERN_DARK_BLUE RGB15(18, 21, 26)
#define BACKGROUND_PATTERN_LIGHT_BLUE RGB15(23, 25, 28)

#define FRAME_YELLOW RGB15(28, 28, 10)
#define FRAME_INNER_EDGE_BLUE RGB15(9, 12, 14)

#define WINDOW_WHITE RGB15(30, 30, 30)
#define WINDOW_EDGE_BLUE RGB15(68, 96, 192)

#endif /* INCLUDE_GRAPHICS_H */
