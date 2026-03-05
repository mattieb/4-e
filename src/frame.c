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

void init_frame()
{
    TILE *tile;
    int i;
    int y;
    int x;

    pal_bg_mem[2] = FRAME_YELLOW;
    pal_bg_mem[3] = FRAME_INNER_EDGE_BLUE;

    tile = &tile_mem[TILE_CHARBLOCK][TILE_EMPTY];
    for (i = 0; i <= 7; i++)
        tile->data[i] = 0x00000000;

    tile = &tile_mem[TILE_CHARBLOCK][TILE_FRAME];
    for (i = 0; i <= 7; i++)
        tile->data[i] = 0x22222222;

    tile = &tile_mem[TILE_CHARBLOCK][TILE_FRAME_HORIZONTAL_EDGE];
    tile->data[0] = 0x22222222;
    tile->data[1] = 0x22222222;
    tile->data[2] = 0x22222222;
    tile->data[3] = 0x33333333;
    tile->data[4] = 0x00000000;
    tile->data[5] = 0x00000000;
    tile->data[6] = 0x00000000;
    tile->data[7] = 0x00000000;

    tile = &tile_mem[TILE_CHARBLOCK][TILE_FRAME_VERTICAL_EDGE];
    for (i = 0; i <= 7; i++)
        tile->data[i] = 0x00003222;

    tile = &tile_mem[TILE_CHARBLOCK][TILE_FRAME_CORNER];
    tile->data[0] = 0x22222222;
    tile->data[1] = 0x22222222;
    tile->data[2] = 0x22222222;
    tile->data[3] = 0x22222222;
    tile->data[4] = 0x33222222;
    tile->data[5] = 0x00322222;
    tile->data[6] = 0x00032222;
    tile->data[7] = 0x00032222;

    for (x = 0; x <= 29; x++)
    {
        se_mem[FRAME_SCREENBLOCK][x] = TILE_FRAME;
        se_mem[FRAME_SCREENBLOCK][(32 * 19) + x] = TILE_FRAME;

        if (x >= 2 && x <= 27)
        {
            se_mem[FRAME_SCREENBLOCK][32 + x] = TILE_FRAME_HORIZONTAL_EDGE;
            se_mem[FRAME_SCREENBLOCK][(32 * 18) + x] = TILE_FRAME_HORIZONTAL_EDGE | SE_VFLIP;
        }
        else
            switch (x)
            {
            case 1:
                for (y = 2; y <= 17; y++)
                {
                    se_mem[FRAME_SCREENBLOCK][(32 * y) + 1] = TILE_FRAME_VERTICAL_EDGE;
                }
                break;
            case 28:
                for (y = 2; y <= 17; y++)
                {
                    se_mem[FRAME_SCREENBLOCK][(32 * y) + 28] = TILE_FRAME_VERTICAL_EDGE | SE_HFLIP;
                }
                break;
            }

        for (y = 1; y <= 18; y++)
        {
            se_mem[FRAME_SCREENBLOCK][(32 * y)] = TILE_FRAME;
            se_mem[FRAME_SCREENBLOCK][(32 * y) + 29] = TILE_FRAME;
        }

        se_mem[FRAME_SCREENBLOCK][32 + 1] = TILE_FRAME_CORNER;
        se_mem[FRAME_SCREENBLOCK][32 + 28] = TILE_FRAME_CORNER | SE_HFLIP;
        se_mem[FRAME_SCREENBLOCK][(32 * 18) + 1] = TILE_FRAME_CORNER | SE_VFLIP;
        se_mem[FRAME_SCREENBLOCK][(32 * 18) + 28] = TILE_FRAME_CORNER | SE_HFLIP | SE_VFLIP;
    }
}
