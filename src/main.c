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
#include <stdio.h>
#include <tonc.h>

#include "background.h"
#include "frame.h"
#include "gbfs.h"
#include "graphics.h"
#include "card.h"
#include "link.h"
#include "pick.h"
#include "ui.h"
#include "volumes.h"
#include "window.h"

int main(void)
{
    const GBFS_FILE *initial_volume;
    bool multi_volume_mode;
    char name[MAX_OBJECT_NAME];
    const void *object;
    char meta[20];
    char content_type[MAX_CONTENT_TYPE];
    char set_type;
    u8 set_number;

    init_graphics();
    init_background();
    init_frame();
    init_window();
    init_ui();

    start_display();

    initial_volume = first_volume();
    if (!initial_volume)
    {
        fatal("No card data attached. See instructions.");
    }

    multi_volume_mode = more_volumes_exist(initial_volume);

    if (!multi_volume_mode && object_count(initial_volume) == 1)
    {
        object = get_object(initial_volume, 0, name);
    }
    else
    {
        object = pick(initial_volume, multi_volume_mode, name);
    }

    if (object == NULL)
    {
        fatal("Error reading card data. See instructions.");
    }

    get_card_content_type(object, content_type);
    set_type = get_set_type(object);
    set_number = get_set_number(object);

    snprintf(meta, 20,
             "%s (07-%c%03u)", content_type, set_type, set_number);

    status(CATTR_LIGHT_BLUE, "Waiting...",
           "Start communication, or cancel with \201.",
           name, meta);

    setup_link();
    if (wait_for_player_assignment())
    {
        fatal("Cancelled.");
    }

    status(CATTR_LIGHT_BLUE, "Connecting...",
           "Please wait, or cancel with \201.",
           name, meta);

    switch (connect())
    {
    case 0:
        break;
    case 1:
        fatal("Cancelled.");
        break;
    case 2:
        fatal("Connection failed.");
        break;
    default:
        fatal("Internal error.");
        break;
    }

    status(CATTR_LIGHT_BLUE, "Sending...",
           "Please wait, or cancel with \201.",
           name, meta);

    if (send_card(object))
    {
        fatal("Cancelled.");
    }

    status(CATTR_LIGHT_BLUE, "Done!",
           "Press any button to reset.",
           name, meta);

    pause_and_reset();
}
