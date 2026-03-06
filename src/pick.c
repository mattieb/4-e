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

void draw_pick_window()
{
    draw_window(2, 2, 27, 17);

    tte_set_ink(2);
    tte_set_pos(24, 129);
    tte_write("\204 move");

    tte_set_pos(120 - (tte_get_text_size("\202\203 switch stacks").x / 2), 129);
    tte_write("\202\203 switch stacks");

    tte_set_pos(217 - tte_get_text_size("\200 send").x, 129);
    tte_write("\200 send");
}

const void *pick(const GBFS_FILE *initial_volume, char *selected_name)
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
    char name[MAX_OBJECT_NAME_LENGTH];
    const void *object;
    char content_type[MAX_CONTENT_TYPE_LENGTH];

    current_volume = initial_volume;

    draw_pick_window();

    while (true)
    {
        count = object_count(current_volume);
        page = 0;
        last_page = 0;
        selection = 0;
        last_selection = -1;
        selected_object = NULL;

        tte_erase_rect(23, 23, 217, 122);

        while (true)
        {
            if (selection != last_selection || page != last_page)
            {
                for (offset = 0; offset < PICKER_PAGE_SIZE; offset++)
                {
                    index = page + offset;
                    object = index < count ? get_object(current_volume, index, name) : NULL;

                    if (index == selection)
                    {
                        schr4c_rect(&tte_get_context()->dst, 23, 23 + (offset * 10), 217, 32 + (offset * 10), 3);
                        tte_set_ink(1);
                        tte_set_pos(24, 24 + (offset * 10));
                        tte_write(">");
                        selected_object = object;
                        strncpy(selected_name, name, MAX_OBJECT_NAME_LENGTH);
                    }
                    else if (index == last_selection || page != last_page)
                    {
                        tte_erase_rect(23, 23 + (offset * 10), 217, 32 + (offset * 10));
                    }

                    if (object != NULL)
                    {
                        get_card_content_type(object, content_type);
                        tte_set_ink(2);
                        tte_set_pos(70 - tte_get_text_size(content_type).x, 24 + (offset * 10));
                        tte_write(content_type);
                        tte_set_ink(1);
                        tte_set_pos(73, 24 + (offset * 10));
                        tte_write(name);
                    }
                }
            }

            // char status[100];
            // tte_set_ink(1);
            // tte_set_pos(1, 1);
            // tte_erase_line();
            // snprintf(status, 100, "selection=%i(%i) page=%i(%i) count=%i volume=%x", selection, last_selection, page, last_page, count, current_volume);
            // tte_write(status);

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
                        current_volume = next_volume_or_loop(current_volume, initial_volume);
                        count = object_count(current_volume);
                        last_page = -1; // force redraw
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
                        current_volume = previous_volume_or_loop(current_volume, initial_volume);
                        count = object_count(current_volume);
                        last_page = -1;
                        selection = count - 1;
                    }

                    wait_for_keyup(KEY_UP);
                    break;
                }

                if (~REG_KEYINPUT & KEY_RIGHT)
                {
                    selection += PICKER_PAGE_SIZE;

                    // would we move off the last page?
                    if (selection / PICKER_PAGE_SIZE > (count - 1) / PICKER_PAGE_SIZE)
                    {
                        current_volume = next_volume_or_loop(current_volume, initial_volume);
                        count = object_count(current_volume);
                        last_page = -1;
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
                        current_volume = previous_volume_or_loop(current_volume, initial_volume);
                        count = object_count(current_volume);
                        last_page = -1;
                        selection = (selection % PICKER_PAGE_SIZE) + count - (count % PICKER_PAGE_SIZE);
                    }

                    wait_for_keyup(KEY_LEFT);
                    break;
                }

                if (~REG_KEYINPUT & KEY_L)
                {
                    current_volume = previous_volume_or_loop(current_volume, initial_volume);
                    count = object_count(current_volume);
                    page = 0;
                    selection = 0;
                    last_page = -1;
                    selection = (selection % PICKER_PAGE_SIZE) + count - (count % PICKER_PAGE_SIZE);

                    wait_for_keyup(KEY_L);
                    break;
                }

                if (~REG_KEYINPUT & KEY_R)
                {
                    current_volume = next_volume_or_loop(current_volume, initial_volume);
                    count = object_count(current_volume);
                    page = 0;
                    selection = 0;
                    last_page = -1;
                    selection = selection % PICKER_PAGE_SIZE;

                    wait_for_keyup(KEY_R);
                    break;
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

        return 0;
    }
}
