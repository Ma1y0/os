#include <drivers/vga.h>

void kernel_main(void) {
  vga_clear();
  vga_putchar('O', VGA_COLOR_LIGHT_GREEN, 10, 10);
  vga_putchar('K', VGA_COLOR_LIGHT_GREEN, 11, 10);
}
