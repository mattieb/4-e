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

#ifndef _4E_LINK_H_
#define _4E_LINK_H_

#include <tonc.h>

#define PROTO_HANDSHAKE_1           0xfbfb
#define PROTO_HANDSHAKE_2           0x5841
#define PROTO_HANDSHAKE_3           0x4534

#define PROTO_GAME_REQUEST_DEMO     0xecec
#define PROTO_GAME_REQUEST_POWERUP  0xeded
#define PROTO_GAME_REQUEST_LEVEL    0xeeee

#define PROTO_GAME_ANIMATING        0xf3f3
#define PROTO_EREADER_ANIMATING     0xf2f2
#define PROTO_EREADER_READY         0xf1f1

#define PROTO_GAME_READY_DEMO       0xefef
#define PROTO_GAME_READY_POWERUP    0xf0f0
#define PROTO_GAME_READY_LEVEL      0xfafa

#define PROTO_EREADER_CANCEL        0xf7f7

#define PROTO_EREADER_SEND_READY    0xf9f9
#define PROTO_GAME_RECEIVE_READY    0xfefe

#define PROTO_EREADER_SEND_START    0xfdfd
#define PROTO_EREADER_SEND_END      0xfcfc

#define PROTO_GAME_RECEIVE_OK       0xf5f5
#define PROTO_GAME_RECEIVE_ERROR    0xf4f4

void setup_link();
int wait_for_player_assignment();
int connect();
int send_card(const void *card);

#endif /* _4E_LINK_H_ */
