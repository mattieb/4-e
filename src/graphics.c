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

u8 delay;
u8 scroll;

void init_graphics()
{
    TILE *tile;
    int i;

    tile = &tile_mem[CBB][TILE_EMPTY];
    for (i = 0; i <= 7; i++)
        tile->data[i] = 0x00000000;
}

void handle_vblank_interrupt()
{
    if ((delay++ & 0x3) == 0)
    {
        scroll++;
        REG_BG0HOFS = scroll;
        REG_BG0VOFS = scroll;
    }
}

void start_display()
{
    delay = 0;
    scroll = 0;

    REG_BG0CNT = BG_CBB(0) | BG_SBB(SBB_BACKGROUND) | BG_4BPP | BG_REG_32x32 | BG_PRIO(3);
    REG_BG1CNT = BG_CBB(0) | BG_SBB(SBB_FRAME) | BG_4BPP | BG_REG_32x32 | BG_PRIO(2);
    REG_BG2CNT = BG_CBB(0) | BG_SBB(SBB_WINDOW) | BG_4BPP | BG_REG_32x32 | BG_PRIO(1);
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3;

    irq_init(NULL);
    irq_add(II_VBLANK, handle_vblank_interrupt);
}
