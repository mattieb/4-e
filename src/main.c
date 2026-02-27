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

#include <stdio.h>
#include <tonc.h>

#include "gbfs.h"
#include "card.h"
#include "link.h"
#include "pick.h"
#include "ui.h"
#include "volumes.h"

int main(void)
{
    const GBFS_FILE *initialVolume;
    char name[MAX_OBJECT_NAME_LENGTH];
    const void *object;

    setup_screen();

    initialVolume = findVolume(0);
    if (!initialVolume)
    {
        done("Please attach a GBFS volume.", NULL);
    }

    if (!moreVolumes(initialVolume) && objectCount(initialVolume) == 1)
    {
        // object should not be NULL, but we will end if it is
        object = getObject(initialVolume, 1, name);
    }
    else
    {
        object = pick(initialVolume, name);
    }

    if (object == NULL)
    {
        done("Thank you for playing!", NULL);
    }

    char meta[31];
    char contentType[MAX_CONTENT_TYPE_LENGTH];
    char setType;
    u8 setNumber;

    get_card_content_type(object, contentType);
    setType = get_set_type(object);
    setNumber = get_set_number(object);

    snprintf(meta, 31, "07-%c%03u %s Card", setType, setNumber, contentType);

    status("Waiting... (B=cancel)", name, meta);
    setup_link();
    wait_for_player_assignment();

    status("Connecting... (B=cancel)", name, meta);
    if (connect())
    {
        done("Connection failed.", name);
    }

    status("Sending... (B=cancel)", name, meta);
    send_card(object);

    done("Card data sent!", name);
}
