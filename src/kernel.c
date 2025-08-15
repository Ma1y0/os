#include <stddef.h>

#include "vga.h"

void kernel_main(void) {
    vga_putchar('x', VGA_COLOR_MAGENTA, 2, 1);

    vga_clear();

    vga_putchar('x', VGA_COLOR_LIGHT_CYAN, 2, 1);

    vga_puts("Hello, World!", VGA_COLOR_LIGHT_RED, 5, 5);
}
