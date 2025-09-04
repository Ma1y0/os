#include <lib/string.h>
#include <stdint.h>

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

// Fills the first n bytes of the memory area pointed to by dest with the constant byte c
void *memset(void *dest, int c, size_t n) {
    char *s = dest;

    for (; n; n--, s++) {
        *s = c;
    }

    return dest;
}


// Copies `n` bytes from memory pointed to by `src` to memory pointed to by `dest`
void *memmove(void *dest, const void *src, size_t n) {
    uint8_t *d = dest;
    const uint8_t *s = src;


    if (d < s) {
        // Copy forward
        for (; n; d++, s++, n--) {
            *d = *s;
        }
    } else {
        // Copy backward
        d += n;
        s += n;
        for (; n; n--, d++, s++) {
            *d = *s;
        }
    }

    return dest;
}
