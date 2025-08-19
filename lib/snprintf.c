#include <lib/snprintf.h>

#include "types.h"

size_t snprintf(char *restrict s, size_t maxlen, const char *restrict format, ...) {
    for (size_t i = 0; i < maxlen || format[i] == 0; i++) {
        s[i] = format[i];
    }

    // TODO
    return -1;
}
