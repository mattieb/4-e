#ifndef INCLUDE_PICK_H
#define INCLUDE_PICK_H

#include <stddef.h>

#include "gbfs.h"

#define PICKER_PAGE_SIZE 16

size_t pickBin(const GBFS_FILE *gbfs);

#endif /* INCLUDE_PICK_H */
