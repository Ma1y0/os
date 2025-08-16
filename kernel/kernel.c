#include <drivers/vga.h>
#include <kernel/console.h>

void kernel_main(void) {
    vga_clear();
    putchar('x');
    putchar('a');
    putchar('b');

    puts("Hello, Wordl!");

    putchar('c');
    putchar('d');
}
