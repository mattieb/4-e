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

#ifndef INCLUDE_LINK_H
#define INCLUDE_LINK_H

#include <tonc.h>

#define HANDSHAKE_1             0xfbfb
#define HANDSHAKE_2             0x5841
#define HANDSHAKE_3             0x4534

#define GAME_REQUEST_DEMO       0xecec
#define GAME_REQUEST_POWERUP    0xeded
#define GAME_REQUEST_LEVEL      0xeeee

#define GAME_ANIMATING          0xf3f3
#define EREADER_ANIMATING       0xf2f2
#define EREADER_READY           0xf1f1

#define GAME_READY_DEMO         0xefef
#define GAME_READY_POWERUP      0xf0f0
#define GAME_READY_LEVEL        0xfafa

#define EREADER_CANCEL          0xf7f7

#define EREADER_SEND_READY      0xf9f9
#define GAME_RECEIVE_READY      0xfefe

#define EREADER_SEND_START      0xfdfd
#define EREADER_SEND_END        0xfcfc

#define GAME_RECEIVE_OK         0xf5f5
#define GAME_RECEIVE_ERROR      0xf4f4

#define EREADER_SIO_END         0xf3f3
#define GAME_SIO_END            0xf1f1

void activateLink();
void waitForPlayerAssignment();
void send(u16 data);
void sendAndExpect(u16 data, u16 expect);
u16 sendAndReceiveExcept(u16 data, u16 except);

#endif /* INCLUDE_LINK_H */
