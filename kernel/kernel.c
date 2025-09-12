#include <drivers/vga.h>
#include <kernel/console.h>
#include <kernel/multiboot2.h>
#include <mm/memory.h>


void kernel_main(uint32_t multiboot_addr) {
    heap_init();
    vga_clear();
    puts("Hello, World!\n");


    multiboot2_parse_info(multiboot_addr);

    // int x = 5 / 0;
    // puts("We survived division by 0.\n");

    void *a = kmalloc(50);
    printf("1. 0x%x\n", a);
    void *b = kmalloc(120);
    printf("2. 0x%x\n", b);
}
