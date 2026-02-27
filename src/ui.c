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

#include <string.h>
#include <tonc.h>

#include "link.h"
#include "ui.h"

void setup_screen()
{
    irq_init(NULL);
    irq_enable(II_VBLANK);

    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
    tte_init_se(0, BG_CBB(0) | BG_SBB(31), 0, CLR_MEDGRAY, 14, NULL, NULL);
    tte_init_con();

    pal_bg_bank[1][15] = 0x51aa;
    pal_bg_bank[2][15] = 0x6ed1;
    pal_bg_bank[3][15] = 0x039e;
    pal_bg_bank[4][15] = 0x0234;
    pal_bg_bank[5][15] = 0x0cbb;
}

void clear_screen()
{
    tte_erase_screen();
    tte_set_pos(0, 152);
    tte_set_special(CX_BLUE);
    tte_write("mattiebee.dev/4-e         v3.0");
    tte_set_pos(0, 0);
    tte_set_special(CX_BROWN);
}

int centered_x(const char *message) {
    return 120 - (strlen(message) * 4);
}

void status(const char *message, const char *name, const char *meta)
{
    clear_screen();

    if (name != NULL)
    {
        tte_set_special(CX_SKYBLUE);
        tte_write(name);
        tte_write("\n");
    }

    if (meta != NULL)
    {
        tte_set_special(CX_BLUE);
        tte_write(meta);
        tte_write("\n");
    }

    tte_set_special(CX_SKYBLUE);
    tte_set_pos(centered_x(message), 76);
    tte_write(message);
}

void done(const char *message, const char *name)
{
    clear_screen();

    if (name != NULL)
    {
        tte_set_special(CX_SKYBLUE);
        tte_write(name);
    }

    tte_set_pos(centered_x(message), 68);
    tte_set_special(CX_RED);
    tte_write(message);

    tte_set_pos(16, 84);
    tte_set_special(CX_SKYBLUE);
    tte_write("Press any button to reset.");

    while (REG_KEYINPUT != KEY_MASK)
        VBlankIntrWait();
    while (REG_KEYINPUT == KEY_MASK)
        VBlankIntrWait();
    while (REG_KEYINPUT != KEY_MASK)
        VBlankIntrWait();

    SoftReset();
}
