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

#include "four_font.h"
#include "graphics.h"
#include "link.h"
#include "ui.h"
#include "window.h"

void init_ui()
{
    tte_init_chr4c(
        3,
        BG_CBB(2) | BG_SBB(SBB_TEXT) | BG_PRIO(0),
        0xF000,
        0x0201,
        CLR_TEXT_LIGHT_BLUE,
        &fourFont,
        NULL);

    pal_bg_bank[15][2] = CLR_TEXT_DARK_BLUE;
    pal_bg_bank[15][3] = CLR_TEXT_YELLOW;
    pal_bg_bank[15][4] = CLR_TEXT_RED;

    tte_set_ink(3);
    tte_set_pos(16, 151);
    tte_write("mattiebee.dev/4-e");
    char version[] = "v4.0";
    tte_set_pos(225 - tte_get_text_size(version).x, 151);
    tte_write(version);
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

int centered_x(const char *message)
{
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

void fatal(const char *message)
{
    char instruction[] = "Press any button to reset.";
    POINT16 message_size;
    POINT16 instruction_size;
    POINT16 minimum_size;
    int blocks_x;
    int blocks_y;

    message_size = tte_get_text_size(message);
    instruction_size = tte_get_text_size(instruction);
    if (message_size.x > instruction_size.x)
        minimum_size = message_size;
    else
        minimum_size = instruction_size;

    blocks_x = (minimum_size.x / 8) + 2;
    blocks_y = (minimum_size.y / 8) + 2;

    draw_window(
        13 - (blocks_x / 2),
        7 - (blocks_y / 2),
        16 + (blocks_x / 2),
        12 + (blocks_y / 2));

    tte_set_pos(120 - (message_size.x / 2), 70 - (message_size.y / 2));
    tte_set_ink(4);
    tte_write(message);

    tte_set_pos(120 - (instruction_size.x / 2), 90 - (instruction_size.y / 2));
    tte_set_ink(2);
    tte_write(instruction);

    while (REG_KEYINPUT != KEY_MASK)
        VBlankIntrWait();
    while (REG_KEYINPUT == KEY_MASK)
        VBlankIntrWait();
    while (REG_KEYINPUT != KEY_MASK)
        VBlankIntrWait();

    erase_window();

    SoftReset();
}
