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

#define BG3 3

void init_ui()
{
    tte_init_chr4c(
        BG3,
        BG_CBB(2) | BG_SBB(SBB_TEXT) | BG_PRIO(0),
        SE_PALBANK(15),
        bytes2word(1, 0, 0, 0), // ink color 1, other colors 0
        CLR_TEXT_LIGHT_BLUE,    // color 1
        &fourFont,
        NULL);

    pal_bg_bank[15][CATTR_DARK_BLUE] = CLR_TEXT_DARK_BLUE;
    pal_bg_bank[15][CATTR_YELLOW] = CLR_TEXT_YELLOW;
    pal_bg_bank[15][CATTR_RED] = CLR_TEXT_RED;

    tte_set_ink(CATTR_YELLOW);
    tte_set_pos(16, 151);
    tte_write("mattiebee.dev/4-e");

    char version[] = "v4.0";
    tte_set_pos(225 - tte_get_text_size(version).x, 151);
    tte_write(version);
}

void status(u16 message_ink, const char *message,
            const char *instruction,
            const char *header_left, const char *header_right)
{
    POINT16 message_size;
    POINT16 instruction_size;
    POINT16 header_left_size;
    POINT16 header_right_size;
    s16 min_width;
    s16 header_width;
    s16 blocks_width;
    u8 left;
    u8 right;

    message_size = tte_get_text_size(message);
    instruction_size = tte_get_text_size(instruction);
    if (message_size.x > instruction_size.x)
        min_width = message_size.x;
    else
        min_width = instruction_size.x;

    if (header_left != NULL)
        header_left_size = tte_get_text_size(header_left);
    else
        header_left_size.x = header_left_size.y = 0;

    if (header_right != NULL)
        header_right_size = tte_get_text_size(header_right);
    else
        header_right_size.x = header_right_size.y = 0;

    header_width = header_left_size.x + header_right_size.x;
    if (min_width < header_width)
        min_width = header_width;

    blocks_width = (min_width / 8);
    left = 13 - (blocks_width / 2);
    right = 16 + (blocks_width / 2);
    draw_window(left, 4, right, 15);

    tte_set_ink(CATTR_YELLOW);
    tte_set_pos((left * 8) + 8, 39);
    tte_write(header_left);
    tte_set_pos((right * 8) + 1 - header_right_size.x, 39);
    tte_write(header_right);

    tte_set_ink(message_ink);
    tte_set_pos(CENTER_X - (message_size.x / 2),
                CENTER_Y - (message_size.y / 2));
    tte_write(message);

    tte_set_ink(CATTR_DARK_BLUE);
    tte_set_pos(CENTER_X - (instruction_size.x / 2), 114);
    tte_write(instruction);
}

void fatal(const char *message)
{
    status(CATTR_RED, message, "Press any button to restart.", NULL, NULL);
    pause();
    erase_window();
}

void pause()
{
    while (REG_KEYINPUT != KEY_MASK)
        VBlankIntrWait();
    while (REG_KEYINPUT == KEY_MASK)
        VBlankIntrWait();
    while (REG_KEYINPUT != KEY_MASK)
        VBlankIntrWait();
}
