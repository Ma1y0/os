#include <kernel/console.h>
#include <lib/snprintf.h>

#include "types.h"

// Only supports two char long formatting specifiers
size_t snprintf(char *restrict s, size_t maxlen, const char *restrict format, ...) {
    size_t w = 0;
    for (size_t i = 0; w < maxlen && format[i] != 0; i++) {
        if (format[i] == '%') {
            switch (format[i + 1]) {
            case 'd':
            case 'i':
                s[w] = '+';
                // Skip over the formatting specifier type
                i++;
                break;
            default:
                s[w] = '_';
            }
        } else {
            s[w] = format[i];
        }
        w++;
    }

    return w;
}
