#pragma once

#include "stdarg.h"
#include "types.h"

size_t snprintf(char *restrict s, size_t maxlen, const char *restrict format, ...);
size_t vsnprintf(char *restrict s, size_t maxlen, const char *restrict format, va_list args);
