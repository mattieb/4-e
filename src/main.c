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
    char name[MAX_OBJECT_NAME_LENGTH];
    const void *object;
    // char meta[31];
    // char content_type[MAX_CONTENT_TYPE_LENGTH];
    // char set_type;
    // u8 set_number;

    init_background();
    init_frame();
    init_window();
    init_ui();
    
    start_display();

    initial_volume = find_volume(0);
    if (!initial_volume)
    {
        fatal("No cards attached. See instructions.", NULL);
    }

    if (!more_volumes_exist(initial_volume) && object_count(initial_volume) == 1)
    {
        // object should not be NULL, but we will end if it is
        object = get_object(initial_volume, 1, name);
    }
    else
    {
        object = pick(initial_volume, name);
    }

    while (1)
    {
        animate_frame();
    }

    // if (object == NULL)
    // {
    //     done("Thank you for playing!", NULL);
    // }

    // get_card_content_type(object, content_type);
    // set_type = get_set_type(object);
    // set_number = get_set_number(object);

    // snprintf(meta, 31, "07-%c%03u %s Card", set_type, set_number, content_type);

    // status("Waiting... (B=cancel)", name, meta);
    // setup_link();
    // if (wait_for_player_assignment())
    // {
    //     done("Cancelled.", NULL);
    // }

    // status("Connecting... (B=cancel)", name, meta);
    // switch (connect())
    // {
    // case 0:
    //     break;
    // case 1:
    //     done("Cancelled.", name);
    //     break;
    // case 2:
    //     done("Connection failed.", name);
    //     break;
    // default:
    //     done("Internal error.", name);
    //     break;
    // }

    // status("Sending... (B=cancel)", name, meta);
    // if (send_card(object))
    // {
    //     done("Cancelled.", NULL);
    // }

    // done("Card data sent!", name);
}
