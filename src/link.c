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

#include <tonc.h>

#include "link.h"
#include "ui.h"

void activateLink()
{
    irq_enable(II_SERIAL);
    irq_enable(II_KEYPAD);
    REG_KEYCNT = KEY_B | KCNT_IRQ;

    REG_RCNT = REG_RCNT & ~R_MODE_GPIO;
    REG_SIOCNT = SIO_MODE_MULTI;
    REG_SIOCNT = REG_SIOCNT | SIO_IRQ | SIOM_CONNECTED | SIOM_SLAVE | SIOM_115200;
}

void waitForPlayerAssignment()
{
    do
    {
        IntrWait(1, IRQ_SERIAL | IRQ_KEYPAD);
        if (~REG_KEYINPUT & KEY_B)
            done("Cancelled.", NULL);
    } while ((REG_SIOCNT & SIOM_ID_MASK) == 0);
}

void send(u16 data)
{
    IntrWait(1, IRQ_SERIAL | IRQ_KEYPAD);
    if (~REG_KEYINPUT & KEY_B)
        done("Cancelled.", NULL);
    REG_SIOMLT_SEND = data;
}

void sendAndExpect(u16 data, u16 expect)
{
    u16 received;
    do
    {
        send(data);
        received = REG_SIOMULTI0;
    } while (received != expect);
}

u16 sendAndReceiveExcept(u16 data, u16 except)
{
    u16 received;
    do
    {
        send(data);
        received = REG_SIOMULTI0;
    } while (received == except);
    return received;
}
