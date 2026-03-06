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

void status(u16 message_ink, const char *message, const char *instruction, const char *header_left, const char *header_right)
{
    POINT16 message_size;
    POINT16 instruction_size;
    POINT16 header_left_size;
    POINT16 header_right_size;
    s16 minimum_x;
    s16 total_header_x;
    s16 blocks_x;
    u8 left_x;
    u8 right_x;

    message_size = tte_get_text_size(message);
    instruction_size = tte_get_text_size(instruction);
    if (message_size.x > instruction_size.x)
        minimum_x = message_size.x;
    else
        minimum_x = instruction_size.x;

    if (header_left != NULL)
        header_left_size = tte_get_text_size(header_left);
    else
        header_left_size.x = header_left_size.y = 0;

    if (header_right != NULL)
        header_right_size = tte_get_text_size(header_right);
    else
        header_right_size.x = header_right_size.y = 0;

    total_header_x = header_left_size.x + header_right_size.x;
    if (minimum_x < total_header_x)
        minimum_x = total_header_x;

    blocks_x = (minimum_x / 8);
    left_x = 13 - (blocks_x / 2);
    right_x = 16 + (blocks_x / 2);
    draw_window(left_x, 4, right_x, 15);

    tte_set_ink(3);
    tte_set_pos((left_x * 8) + 8, 39);
    tte_write(header_left);
    tte_set_pos((right_x * 8) + 1 - header_right_size.x, 39);
    tte_write(header_right);

    tte_set_ink(message_ink);
    tte_set_pos(120 - (message_size.x / 2), 80 - (message_size.y / 2));
    tte_write(message);

    tte_set_ink(2);
    tte_set_pos(120 - (instruction_size.x / 2), 114);
    tte_write(instruction);
}

void fatal(const char *message)
{
    status(4, message, "Press any button to reset.", NULL, NULL);
    wait_for_key_and_reset();
}

void wait_for_key_and_reset()
{
    while (REG_KEYINPUT != KEY_MASK)
        VBlankIntrWait();
    while (REG_KEYINPUT == KEY_MASK)
        VBlankIntrWait();
    while (REG_KEYINPUT != KEY_MASK)
        VBlankIntrWait();

    erase_window();

    SoftReset();
}
