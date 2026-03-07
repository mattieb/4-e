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

#include <tonc.h>

#include "tiles.h"
#include "window.h"
#include "graphics.h"

void init_window()
{
    TILE *tile;

    pal_bg_mem[4] = CLR_WINDOW_WHITE;
    pal_bg_mem[5] = CLR_WINDOW_EDGE_BLUE;

    tile = &tile_mem[CBB][TILE_WINDOW];
    tonccpy(tile, tile_window, 32);

    tile = &tile_mem[CBB][TILE_WINDOW_HORIZONTAL_EDGE];
    tonccpy(tile, tile_window_horizontal_edge, 32);

    tile = &tile_mem[CBB][TILE_WINDOW_VERTICAL_EDGE];
    tonccpy(tile, tile_window_vertical_edge, 32);

    tile = &tile_mem[CBB][TILE_WINDOW_CORNER];
    tonccpy(tile, tile_window_corner, 32);
}

void draw_window(u8 left, u8 top, u8 right, u8 bottom)
{
    u8 y;
    u8 x;
    SCR_ENTRY entry;

    erase_window();

    for (y = top; y <= bottom; y++)
    {
        for (x = left; x <= right; x++)
        {
            if (y == top)
            {
                if (x == left)
                    entry = TILE_WINDOW_CORNER;
                else if (x == right)
                    entry = TILE_WINDOW_CORNER | SE_HFLIP;
                else
                    entry = TILE_WINDOW_HORIZONTAL_EDGE;
            }
            else if (y == bottom)
            {
                if (x == left)
                    entry = TILE_WINDOW_CORNER | SE_VFLIP;
                else if (x == right)
                    entry = TILE_WINDOW_CORNER | SE_HFLIP | SE_VFLIP;
                else
                    entry = TILE_WINDOW_HORIZONTAL_EDGE | SE_VFLIP;
            }
            else
            {
                if (x == left)
                    entry = TILE_WINDOW_VERTICAL_EDGE;
                else if (x == right)
                    entry = TILE_WINDOW_VERTICAL_EDGE | SE_HFLIP;
                else
                    entry = TILE_WINDOW;
            }

            TILEMAP(SBB_WINDOW, x, y) = entry;
        }
    }
}

void erase_window()
{
    u8 y;
    u8 x;

    for (y = 2; y <= 17; y++)
        for (x = 2; x <= 27; x++)
            TILEMAP(SBB_WINDOW, x, y) = TILE_EMPTY;

    tte_erase_rect(WINDOW_AREA_LEFT, WINDOW_AREA_TOP,
                   WINDOW_AREA_RIGHT, WINDOW_AREA_BOTTOM);
}
