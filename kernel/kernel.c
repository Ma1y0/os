#include <drivers/vga.h>
#include <kernel/console.h>

void kernel_main(void) {
    vga_clear();
    puts("Hello World\n");
}
