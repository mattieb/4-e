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

#include "background.h"
#include "graphics.h"

void init_background()
{
    TILE *tile;
    int y;
    int x;
    SCR_ENTRY entry;

    pal_bg_mem[0] = BACKGROUND_PATTERN_DARK_BLUE;
    pal_bg_mem[1] = BACKGROUND_PATTERN_LIGHT_BLUE;

    tile = &tile_mem[TILE_CHARBLOCK][TILE_DIAMOND_QUADRANT];
    tile->data[0] = 0x00000000;
    tile->data[1] = 0x10000000;
    tile->data[2] = 0x11000000;
    tile->data[3] = 0x11100000;
    tile->data[4] = 0x11110000;
    tile->data[5] = 0x11111000;
    tile->data[6] = 0x11111100;
    tile->data[7] = 0x11111110;

    for (y = 0; y <= 31; y++)
    {
        for (x = 0; x <= 31; x++)
        {
            entry = TILE_DIAMOND_QUADRANT;
            if (y & 1)
                entry |= SE_VFLIP;
            if (x & 1)
                entry |= SE_HFLIP;
            se_mem[BACKGROUND_SCREENBLOCK][y * 32 + x] = entry;
        }
    }

}

int background_scroll = 0;

void animate_background()
{
    background_scroll++;
    REG_BG0HOFS = background_scroll;
    REG_BG0VOFS = background_scroll;
}
