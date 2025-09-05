#include <drivers/vga.h>
#include <kernel/console.h>
#include <lib/itoa.h>
#include <lib/stdarg.h>
#include <lib/string.h>

static size_t cursor[] = {0, 0};

void putchar(char ch) {
    if (ch == '\n') {
        cursor[0] = 0;
        cursor[1]++;
        return;
    }

    if (cursor[1] == VGA_ROWS) {
        vga_scroll();
        cursor[1] -= 1;
    }

    vga_putchar(ch, VGA_COLOR_WHITE, cursor[0], cursor[1]);
    cursor[0]++;
}

void puts(const char *s) {
    for (size_t i = 0; s[i] != 0; i++) {
        putchar(s[i]);
    }
}
