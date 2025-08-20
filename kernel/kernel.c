#include <drivers/pci.h>
#include <drivers/vga.h>
#include <kernel/console.h>
#include <lib/itoa.h>
#include <lib/snprintf.h>
#include <lib/string.h>

void kernel_main(void) {
    vga_clear();
    puts("Hello, World!\nWelcome to the OS!\n====================================================\n\n");

    char b[255];
    snprintf(b, 500, "Decimal: %d, HEX: %x, Char: %c, String: %s\nHello % World\n", 5, 64, 'O', "Hello, World!");
    puts(b);
}
