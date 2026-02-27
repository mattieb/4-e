/*
 * This file is part of 4-e <https://mattiebee.dev/4-e>.
 *
 * Copyright 2024, 2026 Mattie Behrens.
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

#ifndef INCLUDE_VOLUMES_H
#define INCLUDE_VOLUMES_H

#include "gbfs.h"

#define MAX_OBJECT_NAME_LENGTH 25

const GBFS_FILE *findVolume(const void *start);
const GBFS_FILE *nextVolume(const GBFS_FILE *currentVolume);
const GBFS_FILE *nextVolumeOrLoop(const GBFS_FILE *currentVolume, const GBFS_FILE *firstVolume);
const GBFS_FILE *previousVolumeOrLoop(const GBFS_FILE *currentVolume, const GBFS_FILE *firstVolume);
int moreVolumes(const GBFS_FILE *currentVolume);
size_t objectCount(const GBFS_FILE *volume);
const void *getObject(const GBFS_FILE *volume, size_t index, char *name);

#endif /* INCLUDE_VOLUMES_H */