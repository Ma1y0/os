#include <drivers/vga.h>
#include <kernel/console.h>
#include <lib/string.h>

void kernel_main(void) {
    vga_clear();
    putchar('x');
    putchar('a');
    putchar('b');

    puts("Hello, Wordl!");

    putchar('c');
    putchar('d');

    putchar(' ');
    putchar(' ');

    puts("Line 1\nLine 2");
    putchar('\n');

    putchar(strlen("Hello!") + 48);
}
