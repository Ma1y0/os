#include <lib/string.h>

// Returns the length of a null terminated string `s`
size_t strlen(const char *s) {
    size_t i = 0;
    while (s[i] != 0) {
        i++;
    }

    return i;
}
