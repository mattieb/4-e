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

#include <stdbool.h>

#include "volumes.h"

const GBFS_FILE *find_volume(const void *start)
{
    return find_first_gbfs_file(start != 0 ? start : (void *)find_first_gbfs_file);
}

const GBFS_FILE *next_volume(const GBFS_FILE *current_volume)
{
    return find_first_gbfs_file(skip_gbfs_file(current_volume));
}

const GBFS_FILE *next_volume_or_loop(const GBFS_FILE *current_volume, const GBFS_FILE *first_volume)
{
    const GBFS_FILE *next;
    
    next = next_volume(current_volume);
    if (next == NULL)
        return first_volume;
    return next;
}

const GBFS_FILE *previous_volume_or_loop(const GBFS_FILE *current_volume, const GBFS_FILE *first_volume)
{
    const GBFS_FILE *candidate;
    
    candidate = first_volume;
    do
    {
        const GBFS_FILE *next = next_volume(candidate);
        if (next == current_volume || next == NULL)
            return candidate;
        candidate = next;
    } while (true);
}

bool more_volumes_exist(const GBFS_FILE *current_volume)
{
    return next_volume(current_volume) != 0;
}

unsigned short object_count(const GBFS_FILE *volume)
{
    return volume->dir_nmemb;
}

const void *get_object(const GBFS_FILE *volume, unsigned short index, char *name)
{
    return gbfs_get_nth_obj(volume, index, name, NULL);
}
