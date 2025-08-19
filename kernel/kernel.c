#include <drivers/pci.h>
#include <drivers/vga.h>
#include <kernel/console.h>
#include <lib/snprintf.h>
#include <lib/string.h>

void kernel_main(void) {
    vga_clear();
    puts("Hello, World!");

    char *a = "Hello, World!";
    char b[255];

    // snprintf(b, strlen(a), a);
    // puts(a);
    // putchar('\n');
    // puts(b);
}
