#pragma once

// TODO: types should depend on the architecture

#define NULL ((void *)0)

#ifdef ARCH_x86_64
#include "../arch/x86_64/types.h"
#endif // ARCH_x86_64

/*** BOOLEANS ***/
typedef _Bool bool;
#define true 1
#define false 0
