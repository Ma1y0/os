#include <drivers/vga.h>
#include <kernel/console.h>

size_t cursor[] = {0, 0};

void putchar(char ch) {
    vga_putchar(ch, VGA_COLOR_WHITE, cursor[0], cursor[1]);
    cursor[0]++;
}

void puts(const char *s) {
    vga_puts(s, VGA_COLOR_WHITE, cursor[0], cursor[1]);
}
