#include <kernel/console.h>
#include <kernel/multiboot2.h>
#include <lib/types.h>

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

void handle_framebuffer(struct framebuffer_tag *fb);

void multiboot2_parse_info(uint32_t addr) {
    printf("Loading the multiboot2 info from 0x%x\n", addr);

    struct multiboot2_info *info = (struct multiboot2_info *)(uint64_t)addr;

    printf("multiboot2 info total_size: %d\n", info->total_size);

    struct multiboot2_tag *tag = (struct multiboot2_tag *)(info + sizeof(struct multiboot2_info));

    while (tag->type != 0) {
        switch (tag->type) {
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

void handle_framebuffer(struct framebuffer_tag *fb) {
    printf("Framebuffer:\n");
    printf("Addr: %x\nwidth: %d, height: %d\nfb_type: %d\npitch: %d\nbpp: %d\n", fb->addr, fb->width, fb->height,
           fb->fb_type, fb->pitch, fb->bpp);

    void *color_info = (void *)(fb + 1);

    switch (fb->fb_type) {
    case 0: {
        struct framebuffer_index_pallet *pallet = color_info;
        printf("Indexed color with %d colors.\n", pallet->num_collors);
        printf("Color 1 red: %d, green: %d, blue: %d\n", pallet->colors[0].red, pallet->colors[0].green,
               pallet->colors[0].blue);

        break;
    }
    case 1:
        printf("Direct RGB color\n");
        break;
    case 2:
        printf("VGA text mode\n");
        break;
    default:
        printf("Unknown framebuffer type\n");
        break;
    }
}
