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

#include <stddef.h>
#include <string.h>
#include <tonc.h>

#include "gbfs.h"
#include "card.h"
#include "pick.h"
#include "ui.h"
#include "volumes.h"

void waitUp(u16 key)
{
    while (~REG_KEYINPUT & key)
        VBlankIntrWait();
}

const void *pick(const GBFS_FILE *initialVolume, char *selectedName)
{
    const GBFS_FILE *currentVolume = initialVolume;

    while (1)
    {
        u16 count = objectCount(currentVolume);
        u16 page = 0;
        u16 selection = 0;
        const void *selectedObject;

        while (true)
        {
            clearScreen();

            tte_set_special(CX_SKYBLUE);
            tte_printf("+/L/R=move, A=pick %5d/%5d\n\n", selection + 1, count);

            for (int index = page; index < count && index < page + PICKER_PAGE_SIZE; index++)
            {
                char name[MAX_OBJECT_NAME_LENGTH];
                const void *object = getObject(currentVolume, index, name);

                if (index == selection)
                {
                    tte_set_special(CX_SKYBLUE);
                    selectedObject = object;
                    strncpy(selectedName, name, MAX_OBJECT_NAME_LENGTH);
                }
                else
                    tte_set_special(CX_BLUE);

                char contentType[MAX_CONTENT_TYPE_LENGTH];
                char shortType[6];

                getCardContentType(object, contentType);
                snprintf(shortType, 6, "%.5s", contentType);
                tte_printf("%5s ", shortType);
               
                if (index == selection)
                    tte_set_special(CX_YELLOW);
                else
                    tte_set_special(CX_BROWN);

                tte_write(name);
                tte_write("\n");
            }

            while (true)
            {
                VBlankIntrWait();

                if (~REG_KEYINPUT & KEY_DOWN)
                {
                    if (selection < (count - 1))
                        selection++;
                    else
                    {
                        currentVolume = nextVolumeOrLoop(currentVolume, initialVolume);
                        count = objectCount(currentVolume);
                        selection = 0;
                    }

                    waitUp(KEY_DOWN);
                    break;
                }

                if (~REG_KEYINPUT & KEY_UP)
                {
                    if (selection != 0)
                        selection--;
                    else
                    {
                        currentVolume = previousVolumeOrLoop(currentVolume, initialVolume);
                        count = objectCount(currentVolume);
                        selection = count - 1;
                    }

                    waitUp(KEY_UP);
                    break;
                }

                if (~REG_KEYINPUT & KEY_RIGHT)
                {
                    selection += PICKER_PAGE_SIZE;

                    // would we move off the last page?
                    if (selection / PICKER_PAGE_SIZE > (count - 1) / PICKER_PAGE_SIZE)
                    {
                        currentVolume = nextVolumeOrLoop(currentVolume, initialVolume);
                        count = objectCount(currentVolume);
                        selection = selection % PICKER_PAGE_SIZE;
                    }

                    waitUp(KEY_RIGHT);
                    break;
                }

                if (~REG_KEYINPUT & KEY_LEFT)
                {
                    if (selection >= PICKER_PAGE_SIZE)
                        selection -= PICKER_PAGE_SIZE;
                    else
                    {
                        currentVolume = previousVolumeOrLoop(currentVolume, initialVolume);
                        count = objectCount(currentVolume);
                        selection = (selection % PICKER_PAGE_SIZE) + count - (count % PICKER_PAGE_SIZE);
                    }

                    waitUp(KEY_LEFT);
                    break;
                }

                if (~REG_KEYINPUT & KEY_L)
                {
                    currentVolume = previousVolumeOrLoop(currentVolume, initialVolume);
                    count = objectCount(currentVolume);
                    selection = (selection % PICKER_PAGE_SIZE) + count - (count % PICKER_PAGE_SIZE);

                    waitUp(KEY_L);
                    break;
                }

                if (~REG_KEYINPUT & KEY_R)
                {
                    currentVolume = nextVolumeOrLoop(currentVolume, initialVolume);
                    count = objectCount(currentVolume);
                    selection = selection % PICKER_PAGE_SIZE;

                    waitUp(KEY_R);
                    break;
                }

                if (~REG_KEYINPUT & KEY_A)
                {
                    return selectedObject;
                }
            }

            if (selection >= count)
                selection = count - 1;

            page = (selection / PICKER_PAGE_SIZE) * PICKER_PAGE_SIZE;
        }

        return 0;
    }
}
