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

#include "window.h"
#include "graphics.h"

void init_window()
{
    TILE *tile;
    int i;

    pal_bg_mem[4] = CLR_WINDOW_WHITE;
    pal_bg_mem[5] = CLR_WINDOW_EDGE_BLUE;

    tile = &tile_mem[CBB][TILE_WINDOW];
    for (i = 0; i <= 7; i++)
        tile->data[i] = 0x44444444;

    tile = &tile_mem[CBB][TILE_WINDOW_HORIZONTAL_EDGE];
    tile->data[0] = 0x55555555;
    tile->data[1] = 0x44444444;
    tile->data[2] = 0x44444444;
    tile->data[3] = 0x44444444;
    tile->data[4] = 0x44444444;
    tile->data[5] = 0x44444444;
    tile->data[6] = 0x44444444;
    tile->data[7] = 0x44444444;

    tile = &tile_mem[CBB][TILE_WINDOW_VERTICAL_EDGE];
    for (i = 0; i <= 7; i++)
        tile->data[i] = 0x44444445;

    tile = &tile_mem[CBB][TILE_WINDOW_CORNER];
    tile->data[0] = 0x55555000;
    tile->data[1] = 0x44444500;
    tile->data[2] = 0x44444450;
    tile->data[3] = 0x44444445;
    tile->data[4] = 0x44444445;
    tile->data[5] = 0x44444445;
    tile->data[6] = 0x44444445;
    tile->data[7] = 0x44444445;
}

void draw_window(int left_x, int upper_y, int right_x, int lower_y)
{
    int y;
    int x;
    SCR_ENTRY entry;

    erase_window();

    for (y = upper_y; y <= lower_y; y++)
    {
        for (x = left_x; x <= right_x; x++)
        {
            if (y == upper_y && x == left_x)
                entry = TILE_WINDOW_CORNER;
            else if (y == upper_y && x == right_x)
                entry = TILE_WINDOW_CORNER | SE_HFLIP;
            else if (y == lower_y && x == left_x)
                entry = TILE_WINDOW_CORNER | SE_VFLIP;
            else if (y == lower_y && x == right_x)
                entry = TILE_WINDOW_CORNER | SE_HFLIP | SE_VFLIP;
            else if (y == upper_y)
                entry = TILE_WINDOW_HORIZONTAL_EDGE;
            else if (y == lower_y)
                entry = TILE_WINDOW_HORIZONTAL_EDGE | SE_VFLIP;
            else if (x == left_x)
                entry = TILE_WINDOW_VERTICAL_EDGE;
            else if (x == right_x)
                entry = TILE_WINDOW_VERTICAL_EDGE | SE_HFLIP;
            else
                entry = TILE_WINDOW;

            se_mem[SBB_WINDOW][(32 * y) + x] = entry;
        }
    }
}

void erase_window()
{
    int y;
    int x;

    for (y = 2; y <= 17; y++) 
        for (x = 2; x <= 27; x++)
            se_mem[SBB_WINDOW][(32 * y) + x] = TILE_EMPTY;

    tte_erase_rect(0, 0, 239, 151);
}
