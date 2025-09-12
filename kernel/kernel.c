#include <drivers/vga.h>
#include <kernel/console.h>
#include <kernel/multiboot2.h>


void kernel_main(uint32_t multiboot_addr) {
    vga_clear();
    puts("Hello, World!\n");

    multiboot2_parse_info(multiboot_addr);

    // int x = 5 / 0;
    // puts("We survived division by 0.\n");
}
