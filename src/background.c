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
#include "tiles.h"

void init_background()
{
    TILE *tile;
    int y;
    int x;

    pal_bg_mem[0] = CLR_PATTERN_DARK_BLUE;
    pal_bg_mem[1] = CLR_PATTERN_LIGHT_BLUE;

    tile = &tile_mem[CBB][TILE_DIAMOND_QUADRANT];
    tonccpy(tile, tile_diamond_quadrant, 32);

    for (y = 0; y <= 31; y += 2)
    {
        for (x = 0; x <= 31; x += 2)
        {
            se_mem[SBB_BACKGROUND][(y * 32) + x] = TILE_DIAMOND_QUADRANT;
            se_mem[SBB_BACKGROUND][(y * 32) + x + 1] = TILE_DIAMOND_QUADRANT | SE_HFLIP;
            se_mem[SBB_BACKGROUND][((y + 1) * 32) + x] = TILE_DIAMOND_QUADRANT | SE_VFLIP;
            se_mem[SBB_BACKGROUND][((y + 1) * 32) + x + 1] = TILE_DIAMOND_QUADRANT | SE_HFLIP | SE_VFLIP;
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
