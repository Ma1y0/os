#include <drivers/vga.h>
#include <kernel/console.h>
#include <lib/snprintf.h>
#include <lib/string.h>

void kernel_main(void) {
    vga_clear();

    for (size_t i = 0; i < 100; i++) {
        char s[255] = {0};

        snprintf(s, 255, "%d\n", i);
        puts(s);
    }

    puts("Hello World");

    // int x = 5 / 0;
    // puts("We survived division by 0.\n");
}
