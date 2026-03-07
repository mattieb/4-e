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

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <tonc.h>

#include "card.h"
#include "gbfs.h"
#include "graphics.h"
#include "pick.h"
#include "ui.h"
#include "volumes.h"
#include "window.h"

void wait_for_keyup(u16 key)
{
    while (~REG_KEYINPUT & key)
        VBlankIntrWait();
}

void draw_pick_window(bool multi_volume_mode)
{
    char instruction_move[] = "\204 move";
    char instruction_switch[] = "\202\203 switch stacks";
    char instruction_send[] = "\200 send";

    draw_window(2, 2, 27, 17);

    tte_set_ink(CATTR_DARK_BLUE);

    tte_set_pos(24, 129);
    tte_write(instruction_move);

    if (multi_volume_mode)
    {
        tte_set_pos(CENTER_X - (tte_get_text_size(instruction_switch).x / 2), 129);
        tte_write(instruction_switch);
    }

    tte_set_pos(217 - tte_get_text_size(instruction_send).x, 129);
    tte_write(instruction_send);
}

const void *pick(const GBFS_FILE *initial_volume,
                 bool multi_volume_mode,
                 char *selected_name)
{
    const GBFS_FILE *current_volume;
    unsigned short count;
    int page;
    int last_page;
    unsigned short index;
    unsigned short offset;
    int selection;
    int last_selection;
    const void *selected_object;
    char name[MAX_OBJECT_NAME];
    const void *object;
    char content_type[MAX_CONTENT_TYPE];

    current_volume = initial_volume;

    draw_pick_window(multi_volume_mode);

    while (true)
    {
        count = object_count(current_volume);
        page = 0;
        last_page = 0;
        selection = 0;
        last_selection = -1;
        selected_object = NULL;

        tte_erase_rect(PICKER_LEFT, PICKER_TOP,
                       PICKER_RIGHT, PICKER_BOTTOM);

        while (true)
        {
            if (selection != last_selection || page != last_page)
            {
                for (offset = 0; offset < PICKER_PAGE_SIZE; offset++)
                {
                    index = page + offset;
                    if (index < count)
                        object = get_object(current_volume, index, name);
                    else
                        object = NULL;

                    if (index == selection)
                    {
                        schr4c_rect(&tte_get_context()->dst,
                                    PICKER_LEFT,
                                    PICKER_ITEM_TOP(offset),
                                    PICKER_RIGHT,
                                    PICKER_ITEM_BOTTOM(offset),
                                    CATTR_YELLOW);

                        tte_set_ink(CATTR_LIGHT_BLUE);
                        tte_set_pos(PICKER_LEFT + 1,
                                    PICKER_ITEM_TOP(offset) + 1);
                        tte_write(">");

                        selected_object = object;
                        strncpy(selected_name, name, MAX_OBJECT_NAME);
                    }
                    else if (index == last_selection || page != last_page)
                    {
                        tte_erase_rect(PICKER_LEFT,
                                       PICKER_ITEM_TOP(offset),
                                       PICKER_RIGHT,
                                       PICKER_ITEM_BOTTOM(offset));
                    }

                    if (object != NULL)
                    {
                        get_card_content_type(object, content_type);

                        tte_set_ink(CATTR_DARK_BLUE);
                        tte_set_pos(PICKER_CONTENT_TYPE_RIGHT -
                                        tte_get_text_size(content_type).x,
                                    PICKER_ITEM_TOP(offset) + 1);
                        tte_write(content_type);

                        tte_set_ink(CATTR_LIGHT_BLUE);
                        tte_set_pos(PICKER_NAME_LEFT,
                                    PICKER_ITEM_TOP(offset) + 1);
                        tte_write(name);
                    }
                }
            }

            last_page = page;
            last_selection = selection;

            while (true)
            {
                VBlankIntrWait();

                if (~REG_KEYINPUT & KEY_DOWN)
                {
                    if (selection < (count - 1))
                        selection++;
                    else
                    {
                        current_volume = next_volume_or_loop(current_volume,
                                                             initial_volume);
                        count = object_count(current_volume);
                        last_page = -1; // redraw
                        selection = 0;
                    }

                    wait_for_keyup(KEY_DOWN);
                    break;
                }

                if (~REG_KEYINPUT & KEY_UP)
                {
                    if (selection != 0)
                        selection--;
                    else
                    {
                        current_volume =
                            previous_volume_or_loop(current_volume,
                                                    initial_volume);
                        count = object_count(current_volume);
                        last_page = -1; // redraw
                        selection = count - 1;
                    }

                    wait_for_keyup(KEY_UP);
                    break;
                }

                if (~REG_KEYINPUT & KEY_RIGHT)
                {
                    selection += PICKER_PAGE_SIZE;

                    // would we move off the last page?
                    if (selection / PICKER_PAGE_SIZE >
                        (count - 1) / PICKER_PAGE_SIZE)
                    {
                        current_volume = next_volume_or_loop(current_volume,
                                                             initial_volume);
                        count = object_count(current_volume);
                        last_page = -1; // redraw
                        selection = selection % PICKER_PAGE_SIZE;
                    }

                    wait_for_keyup(KEY_RIGHT);
                    break;
                }

                if (~REG_KEYINPUT & KEY_LEFT)
                {
                    if (selection >= PICKER_PAGE_SIZE)
                        selection -= PICKER_PAGE_SIZE;
                    else
                    {
                        current_volume =
                            previous_volume_or_loop(current_volume,
                                                    initial_volume);
                        count = object_count(current_volume);
                        last_page = -1; // redraw
                        selection = (selection % PICKER_PAGE_SIZE) + count -
                                    (count % PICKER_PAGE_SIZE);
                    }

                    wait_for_keyup(KEY_LEFT);
                    break;
                }

                if (multi_volume_mode)
                {
                    if (~REG_KEYINPUT & KEY_L)
                    {
                        current_volume =
                            previous_volume_or_loop(current_volume,
                                                    initial_volume);
                        count = object_count(current_volume);
                        page = 0;
                        last_page = -1; // redraw
                        selection = (selection % PICKER_PAGE_SIZE) + count -
                                    (count % PICKER_PAGE_SIZE);

                        wait_for_keyup(KEY_L);
                        break;
                    }

                    if (~REG_KEYINPUT & KEY_R)
                    {
                        current_volume = next_volume_or_loop(current_volume,
                                                             initial_volume);
                        count = object_count(current_volume);
                        page = 0;
                        last_page = -1; // redraw
                        selection = selection % PICKER_PAGE_SIZE;

                        wait_for_keyup(KEY_R);
                        break;
                    }
                }

                if (~REG_KEYINPUT & KEY_A)
                {
                    return selected_object;
                }
            }

            if (selection >= count)
                selection = count - 1;

            page = (selection / PICKER_PAGE_SIZE) * PICKER_PAGE_SIZE;
        }
    }
}
