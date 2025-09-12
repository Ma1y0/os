#include <kernel/console.h>
#include <kernel/multiboot2.h>
#include <lib/types.h>
#include <stddef.h>

struct multiboot2_info {
    uint32_t total_size;
    uint32_t _reserved; // Always 0, should be ignored
} __attribute__((packed));

struct multiboot2_tag {
    uint32_t type;
    uint32_t size;
} __attribute__((packed));

struct framebuffer_tag {
    uint32_t type;
    uint32_t size;
    uint64_t addr;
    uint32_t pitch; // Pitch in bytes
    uint32_t width;
    uint32_t height;
    uint8_t bpp; // Bits per pixel
    uint8_t fb_type;
    uint8_t _reserved; // Always 0, should be ignore
    // Color info follows
} __attribute__((packed));

struct framebuffer_pallet_entry {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} __attribute__((packed));

struct framebuffer_index_pallet {
    uint32_t num_collors;
    struct framebuffer_pallet_entry colors[];
} __attribute__((packed));

struct framebuffer_direct_RGB {
    uint8_t red_field_position;
    uint8_t red_mask_size;
    uint8_t green_field_position;
    uint8_t green_mask_size;
    uint8_t blue_field_position;
    uint8_t blue_mask_size;
} __attribute__((packed));

struct memory_map_record {
    uint64_t base_addr; // The starting physical address
    uint64_t length;    // The size of the memory region in bytes

    // Value of 1 indicates available RAM
    // Value of 2 isn't defined in the spec, so it will be treated as reserved.
    // Value of 3 indicates usable memory holding ACPI information
    // Value of 4 indicates reserved memory which needs to be preserved on hibernation
    // Value of 5 indicates a memory which is occupied by defective RAM modules and all other values currently indicated a reserved area
    uint32_t type;
    uint32_t _reserved; // Is 0 and should be ignored by the os image
} __attribute__((packed));

struct memory_map {
    uint32_t type; // 6
    uint32_t size;
    uint32_t entry_size;    // Guarantied to be a multiple of 8
    uint32_t entry_version; // Currently only 0
    struct memory_map_record entries[];
} __attribute__((packed));

void handle_framebuffer(struct framebuffer_tag *fb);
void handle_mamory_map(struct memory_map *m_map);

void multiboot2_parse_info(uint32_t addr) {
    printf("Loading the multiboot2 info from 0x%x\n", addr);

    struct multiboot2_info *info = (struct multiboot2_info *)(uint64_t)addr;

    printf("multiboot2 info total_size: %d\n", info->total_size);

    struct multiboot2_tag *tag = (struct multiboot2_tag *)(info + sizeof(struct multiboot2_info));

    while (tag->type != 0) {
        switch (tag->type) {
        // Memory map
        case 6:
            handle_mamory_map((struct memory_map *)tag);
            break;
            // Framebuffer
        case 8:
            handle_framebuffer((struct framebuffer_tag *)tag);
            break;
        default:
            printf("Unknown tag: Type: %d, size: %d\n", tag->type, tag->size);
            break;
        }


        // The address must be 8 aligned
        tag = (struct multiboot2_tag *)((char *)tag + ((tag->size + 7) & ~7));
    }
}

void handle_mamory_map(struct memory_map *m_map) {
    printf("Memmory map: Version: %d, Size %d\n", m_map->entry_version, m_map->size);
    struct memory_map_record *entry = m_map->entries;
    size_t mmap_end = (size_t)m_map + m_map->size;

    while ((size_t)entry < mmap_end) {
        printf("Entry. Addr: 0x%x, Len: %d, Type: %d\n", entry->base_addr, entry->length, entry->type);

        // Go to next entry
        entry = (struct memory_map_record *)((size_t)entry + m_map->entry_size);
    }
}


void handle_framebuffer(struct framebuffer_tag *fb) {
    printf("Framebuffer:\n");
    printf("Addr: %x\nwidth: %d, height: %d\nfb_type: %d\npitch: %d\nbpp: %d\n", fb->addr, fb->width, fb->height,
           fb->fb_type, fb->pitch, fb->bpp);

    void *color_info = (void *)(fb + 1);

    switch (fb->fb_type) {
    case 0: { // Indexed pallet
        struct framebuffer_index_pallet *pallet = color_info;
        printf("Indexed color with %d colors.\n", pallet->num_collors);
        printf("Color 1 red: %d, green: %d, blue: %d\n", pallet->colors[0].red, pallet->colors[0].green,
               pallet->colors[0].blue);

        break;
    }
    case 1: // Direct RGB
        // BROKEN!!!!!
        printf("Direct RGB color\n");
        struct framebuffer_direct_RGB *rgb_fb = color_info;
        printf("Red: pos=%d, mask=%d\nGreen: pos=%d, mask=%d\nBlue: pos=%d, mask=%d\n", rgb_fb->red_field_position,
               rgb_fb->red_mask_size, rgb_fb->green_field_position, rgb_fb->green_mask_size,
               rgb_fb->blue_field_position, rgb_fb->blue_mask_size);


        break;
    case 2: // VGA text
        printf("VGA text mode\n");
        break;
    default: // Unknown
        printf("Unknown framebuffer type\n");
        break;
    }
}
