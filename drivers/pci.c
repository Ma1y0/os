#include <drivers/pci.h>

#define CONFIG_ADDR 0xCF8
#define CONFIG_DATA 0xCFC

static inline void outl(uint16_t port, uint32_t val) {
    __asm__ volatile("outl %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint32_t inl(uint16_t port) {
    uint32_t ret;
    __asm__ volatile("inl %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

size_t pci_config_read(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset) {
    uint32_t address = (1U << 31) // enable bit
                       | ((uint32_t)bus << 16) | ((uint32_t)device << 11) | ((uint32_t)function << 8) |
                       (offset & 0xFC); // must be 4-byte aligned
    outl(0xCF8, address);
    return inl(0xCFC);
}
