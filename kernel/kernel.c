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

    snprintf(b, 200, "Message: %d.abcdefgh\n", 5);
    puts(b);

    char c[255];

    puts(itoa(-20, c, 10));
    puts("     <-- number");
}
