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

#ifndef INCLUDE_CARD_H
#define INCLUDE_CARD_H

#define CARD_HEADER_OFFSET 0x72
#define CARD_DATA_LENGTH 2112

#define MAX_CONTENT_TYPE_LENGTH 9

#define SET_NUMBER_BYTE_OFFSET 0x72
#define SET_TYPE_BYTE_OFFSET 0x73

#define SET_TYPE_A 0x00
#define SET_TYPE_C 0x04
#define SET_TYPE_D 0x06
#define SET_TYPE_E 0x08

int get_card_content_type(const void *card, char *content_type);
char get_set_type(const void *card);
u8 get_set_number(const void *card);

#endif /* INCLUDE_CARD_H */