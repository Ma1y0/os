#include <lib/string.h>

// Returns the length of a null terminated string `s`
size_t strlen(const char *s) {
    size_t i = 0;
    while (s[i] != 0) {
        i++;
    }

    return i;
}

// Revers string `a` and returns pointer to it
char *strrev(char *s) {
    size_t len = strlen(s);
    for (size_t i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = temp;
    }

    return s;
}
