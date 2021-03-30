#ifndef HEAP_H
#define HEAP_H

#include "common.h"

void heap_initialize();

void* heap_alloc(uint32 size);

void heap_free(void* ptr);

#endif // HEAP_H