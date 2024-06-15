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
#include <tonc.h>

#include "gbfs.h"
#include "pick.h"
#include "ui.h"

void waitUp(u16 key)
{
    while (~REG_KEYINPUT & key)
        VBlankIntrWait();
}

size_t pickBin(const GBFS_FILE *gbfs)
{
    u16 count = gbfs->dir_nmemb;
    u16 page = 0;
    u16 selection = 0;

    while (true)
    {
        clearScreen();
        
        tte_printf("+=move, A=pick     %5d/%5d\n\n", selection + 1, count);

        for (int n = page; n < count && n < page + PICKER_PAGE_SIZE; n++)
        {
            char name[25] = {0};
            gbfs_get_nth_obj(gbfs, n, name, NULL);
            if (n == selection)
            {
                tte_write("  > ");
            }
            else
            {
                tte_write("    ");
            }
            tte_write(name);
            tte_write("\n");
        }

        while (true)
        {
            VBlankIntrWait();

            if (~REG_KEYINPUT & KEY_DOWN)
            {
                if (selection < (count - 1)) selection++;
                waitUp(KEY_DOWN);
                break;
            }

            if (~REG_KEYINPUT & KEY_UP)
            {
                if (!selection == 0) selection--;
                waitUp(KEY_UP);
                break;
            }

            if (~REG_KEYINPUT & KEY_RIGHT)
            {
                if (selection <= (count - 1 - PICKER_PAGE_SIZE))
                    selection += PICKER_PAGE_SIZE;
                else
                    selection = (count - 1);
                waitUp(KEY_RIGHT);
                break;
            }

            if (~REG_KEYINPUT & KEY_LEFT)
            {
                if (selection >= PICKER_PAGE_SIZE)
                    selection -= PICKER_PAGE_SIZE;
                else
                    selection = 0;
                waitUp(KEY_LEFT);
                break;
            }

            if (~REG_KEYINPUT & KEY_A)
            {
                return selection;
            }
        }

        page = (selection / PICKER_PAGE_SIZE) * PICKER_PAGE_SIZE;
    }

    return 0;
}
