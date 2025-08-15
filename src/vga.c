#include "vga.h"

static volatile uint16_t *vga_mem = (uint16_t *)VGA_MEM;

// Sets the whole VGA text buffer to 0
void vga_clear(void) {
    for (size_t i = 0; i < VGA_COLS * VGA_ROWS; i++) {
        vga_mem[i] = 0;
    }
}

// Puts the char `ch` into the VGA text buffer
void vga_putchar(uint8_t ch, enum vga_color color, size_t x, size_t y) {
    vga_mem[y * VGA_COLS + x] = (color << 8) | ch;
}

// Puts a null terminated string `s` into the VGA text buffer
// TODO: Should make sure the string `s` doesn't overflow the VGA buffer
void vga_puts(const char *s, enum vga_color color, size_t x, size_t y) {
    for (size_t i = 0; s[i] != 0; i++) {
        vga_putchar(s[i], color, x + i, y);
    }
}
