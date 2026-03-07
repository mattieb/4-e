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

#include <tonc.h>

#include "card.h"
#include "link.h"
#include "ui.h"

void setup_link()
{
    irq_enable(II_KEYPAD);
    irq_enable(II_SERIAL);

    REG_KEYCNT = KEY_B | KCNT_IRQ;

    REG_RCNT = REG_RCNT & ~R_MODE_GPIO;
    REG_SIOCNT = SIO_MODE_MULTI;
    REG_SIOCNT = REG_SIOCNT |
                 SIO_IRQ |
                 SIOM_CONNECTED |
                 SIOM_SLAVE |
                 SIOM_115200;
}

int wait_for_player_assignment()
{
    do
    {
        IntrWait(1, IRQ_SERIAL | IRQ_KEYPAD);
        if (~REG_KEYINPUT & KEY_B)
            return 1;
    } while (!(REG_SIOCNT & SIOM_ID_MASK));
    return 0;
}

int send(u16 data)
{
    IntrWait(1, IRQ_SERIAL | IRQ_KEYPAD);
    if (~REG_KEYINPUT & KEY_B)
        return 1;
    REG_SIOMLT_SEND = data;
    return 0;
}

int send_until_receive(u16 data, u16 expect)
{
    u16 received;

    do
    {
        if (send(data))
            return 1;
        received = REG_SIOMULTI0;
    } while (received != expect);
    return 0;
}

u16 send_until_receive_not(u16 data, u16 except, int *error)
{
    u16 received;

    *error = 0;
    do
    {
        if (send(data))
        {
            *error = 1;
            return 0;
        }
        received = REG_SIOMULTI0;
    } while (received == except);
    return received;
}

int connect()
{
    u16 card_request;
    int error;

    if (send_until_receive(PROTO_HANDSHAKE_1, PROTO_HANDSHAKE_1))
        return 1;
    if (send_until_receive(PROTO_HANDSHAKE_2, PROTO_HANDSHAKE_2))
        return 1;
    if (send_until_receive(PROTO_HANDSHAKE_3, PROTO_HANDSHAKE_3))
        return 1;

    error = 0;
    card_request = send_until_receive_not(PROTO_HANDSHAKE_3,
                                          PROTO_HANDSHAKE_3,
                                          &error);
    if (error)
        return 1;

    if (send_until_receive(PROTO_GAME_ANIMATING, PROTO_EREADER_ANIMATING))
        return 1;
    if (send(PROTO_EREADER_ANIMATING))
        return 1;

    switch (card_request)
    {
    case PROTO_GAME_REQUEST_DEMO:
        if (send_until_receive(PROTO_EREADER_READY, PROTO_GAME_READY_DEMO))
            return 1;
        break;

    case PROTO_GAME_REQUEST_POWERUP:
        if (send_until_receive(PROTO_EREADER_READY, PROTO_GAME_READY_POWERUP))
            return 1;
        break;

    case PROTO_GAME_REQUEST_LEVEL:
        if (send_until_receive(PROTO_EREADER_READY, PROTO_GAME_READY_LEVEL))
            return 1;
        break;

    default:
        return 2;
    }

    if (send_until_receive(PROTO_EREADER_SEND_READY, PROTO_GAME_RECEIVE_READY))
        return 1;

    return 0;
}

int send_card(const void *card)
{
    u32 checksum;
    u16 offset;
    u16 block;

    if (send(PROTO_EREADER_SEND_START))
        return 1;

    checksum = 0;

    for (offset = OFFSET_CARD_HEADER; offset < SIZE_CARD_DATA; offset += 2)
    {
        block = *(const u16 *)((const u8 *)card + offset);
        if (send(block))
            return 1;
        checksum += block;
    }

    if (send(checksum & 0xffff))
        return 1;
    if (send(checksum >> 16))
        return 1;
    if (send(PROTO_EREADER_SEND_END))
        return 1;

    return 0;
}
