#include <drivers/pci.h>
#include <drivers/vga.h>
#include <kernel/console.h>
#include <lib/snprintf.h>
#include <lib/string.h>

void kernel_main(void) {
    vga_clear();
    puts("Hello, World!\nWelcome to the OS!\n====================================================\n\n");

    char b[255];

    snprintf(b, 200, "Message: %d.abcdefgh", 5);
    puts(b);
}
