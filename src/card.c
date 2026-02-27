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

#include <string.h>
#include <tonc.h>

#include "card.h"

u8 getSetTypeByte(const void *card)
{
    return *(u8 *)(card + SET_TYPE_BYTE_OFFSET);
}

int getCardContentType(const void *card, char *contentType)
{
    switch (getSetTypeByte(card))
    {
    case SET_TYPE_A:
        strncpy(contentType, "Level", MAX_CONTENT_TYPE_LENGTH);
        return 0;
    case SET_TYPE_C:
    case SET_TYPE_D:
        strncpy(contentType, "Power-Up", MAX_CONTENT_TYPE_LENGTH);
        return 0;
    case SET_TYPE_E:
        strncpy(contentType, "Demo", MAX_CONTENT_TYPE_LENGTH);
        return 0;
    default:
        strncpy(contentType, "???", MAX_CONTENT_TYPE_LENGTH);
        return 1;
    }
}

char getSetType(const void *card)
{
    switch (getSetTypeByte(card))
    {
    case SET_TYPE_A:
        return 'A';
    case SET_TYPE_C:
        return 'C';
    case SET_TYPE_D:
        return 'D';
    case SET_TYPE_E:
        return 'E';
    default:
        return '?';
    }
}

u8 getSetNumber(const void *card)
{
    return *(u8 *)(card + SET_NUMBER_BYTE_OFFSET);
}
