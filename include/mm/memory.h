#pragma once

#include "lib/types.h"

extern char __heap_start[];
extern char __heap_end[];


void heap_init(void);
void *kmalloc(size_t size);
