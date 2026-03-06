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

#include "graphics.h"
#include "tiles.h"
#include "tilemaps.h"

void init_frame()
{
    TILE *tile;

    pal_bg_mem[2] = CLR_FRAME_YELLOW;
    pal_bg_mem[3] = CLR_FRAME_EDGE_BLUE;

    tile = &tile_mem[CBB][TILE_FRAME];
    tonccpy(tile, tile_frame, 32);

    tile = &tile_mem[CBB][TILE_FRAME_HORIZONTAL_EDGE];
    tonccpy(tile, tile_frame_horizontal_edge, 32);

    tile = &tile_mem[CBB][TILE_FRAME_VERTICAL_EDGE];
    tonccpy(tile, tile_frame_vertical_edge, 32);

    tile = &tile_mem[CBB][TILE_FRAME_CORNER];
    tonccpy(tile, tile_frame_corner, 32);

    tonccpy(se_mem[SBB_FRAME], tilemap_frame, 64 * 20);
}
