/*
 * This file is part of 4-e <https://mattiebee.dev/4-e>.
 *
 * Copyright 2024 Mattie Behrens.
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

void initScreen()
{
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
    tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));
    tte_init_con();
}

void clearScreen()
{
    tte_erase_screen();
    tte_set_pos(0, 152);
    //         ----+----1----+----2----+----3
    tte_write("mattiebee.dev/4-e         v2.1");
    tte_set_pos(0, 0);
}

void status(const char *message, const char *name)
{
    clearScreen();

    if (name != NULL) tte_write(name);

    int len = strlen(message);
    int x = 120 - (len * 4);

    tte_set_pos(x, 76);
    tte_write(message);
}

void done(const char *message, const char *name)
{
    clearScreen();

    if (name != NULL) tte_write(name);

    int len = strlen(message);
    int x = 120 - (len * 4);

    tte_set_pos(x, 68);
    tte_write(message);

    tte_set_pos(16, 84);
    tte_write("Press any button to reset.");

    while (REG_KEYINPUT != KEY_MASK)
        VBlankIntrWait();
    while (REG_KEYINPUT == KEY_MASK)
        VBlankIntrWait();
    while (REG_KEYINPUT != KEY_MASK)
        VBlankIntrWait();

    SoftReset();
}
