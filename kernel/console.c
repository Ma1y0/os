#include <drivers/vga.h>
#include <kernel/console.h>
#include <lib/fmt.h>
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
        cursor[1]--;
    }

    vga_putchar(ch, VGA_COLOR_WHITE, cursor[0], cursor[1]);
    cursor[0]++;
}

void puts(const char *s) {
    for (size_t i = 0; s[i] != 0; i++) {
        putchar(s[i]);
    }
}

#define PRINTF_BUFFER_SIZE 1024

size_t printf(const char *format, ...) {
    char buffer[PRINTF_BUFFER_SIZE];

    va_list args;
    va_start(args, format);
    size_t written = vsnprintf(buffer, PRINTF_BUFFER_SIZE, format, args);
    va_end(args);

    puts(buffer);
    return written;
}
