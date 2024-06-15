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
#include "link.h"
#include "pick.h"
#include "ui.h"

#define CARD_HEADER_OFFSET 0x72

bool connect()
{
    sendAndExpect(HANDSHAKE_1, HANDSHAKE_1);
    sendAndExpect(HANDSHAKE_2, HANDSHAKE_2);
    sendAndExpect(HANDSHAKE_3, HANDSHAKE_3);

    u16 cardRequest = sendAndReceiveExcept(HANDSHAKE_3, HANDSHAKE_3);

    sendAndExpect(GAME_ANIMATING, EREADER_ANIMATING);
    send(EREADER_ANIMATING);

    switch (cardRequest)
    {
    case GAME_REQUEST_DEMO:
        sendAndExpect(EREADER_READY, GAME_READY_DEMO);
        break;

    case GAME_REQUEST_POWERUP:
        sendAndExpect(EREADER_READY, GAME_READY_POWERUP);
        break;

    case GAME_REQUEST_LEVEL:
        sendAndExpect(EREADER_READY, GAME_READY_LEVEL);
        break;

    default:
        return true;
    }

    sendAndExpect(EREADER_SEND_READY, GAME_RECEIVE_READY);
    return false;
}

void sendBin(const void *file, u32 len)
{
    send(EREADER_SEND_START);
    u32 checksum = 0;
    for (off_t o = CARD_HEADER_OFFSET; o < len; o += 2)
    {
        u16 block = *(u16 *)(file + o);
        send(block);
        checksum += block;
    }
    send(checksum & 0xffff);
    send(checksum >> 16);
    send(EREADER_SEND_END);
}

int main(void)
{
    irq_init(NULL);
    irq_enable(II_VBLANK);

    initScreen();

    const GBFS_FILE *gbfs = find_first_gbfs_file((void *)find_first_gbfs_file);
    if (!gbfs)
    {
        done("No attached GBFS file found.", NULL);
    }

    size_t n = gbfs->dir_nmemb == 1 ? 0 : pickBin(gbfs);

    char name[25];
    u32 len;
    const void *file = gbfs_get_nth_obj(gbfs, n, name, &len);

    status("Waiting... (B=cancel)", name);
    activateLink();
    waitForPlayerAssignment();

    status("Connecting... (B=cancel)", name);
    if (connect())
    {
        done("Connection failed.", name);
    }

    status("Sending... (B=cancel)", name);
    sendBin(file, len);

    done("Card data sent!", name);
}
