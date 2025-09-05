#include <drivers/vga.h>
#include <lib/string.h>

static volatile uint16_t *vga_mem = (uint16_t *)VGA_MEM;

// Sets the whole VGA text buffer to 0
void vga_clear(void) {
    for (size_t i = 0; i < VGA_COLS * VGA_ROWS; i++) {
        vga_mem[i] = 0;
    }
}

// Puts the char `ch` into the VGA text buffer
void vga_putchar(char ch, enum vga_color color, size_t x, size_t y) {
    vga_mem[y * VGA_COLS + x] = (color << 8) | ch;
}

// Scrolls the VGA buffer by one
void vga_scroll(void) {
    size_t n = VGA_COLS * (VGA_ROWS - 1);

    // Move all rows up by one
    memmove((void *)vga_mem, (const void *)(vga_mem + VGA_COLS), n * sizeof(uint16_t));

    for (size_t i = 0; i < VGA_COLS; i++) {
        vga_mem[n + i] = 0;
    }
}
