#include <kernel/console.h>
#include <kernel/multiboot2.h>
#include <lib/types.h>


struct multiboot2_info {
    uint32_t total_size;

    // "Is always set to zero and must be ignored by OS image."
    uint32_t reserved;
} __attribute__((packed));

struct multiboot2_tag {
    uint32_t type;
    uint32_t size;
} __attribute__((packed));


void multiboot2_parse_info(uint32_t addr) {
    printf("Loading the multiboot2 info from 0x%x\n", addr);

    struct multiboot2_info *info = (struct multiboot2_info *)(uint64_t)addr;

    printf("multiboot2 info total_size: %d\n", info->total_size);

    struct multiboot2_tag *tag = (struct multiboot2_tag *)(info + sizeof(struct multiboot2_info));

    while (tag->type != 0) {
        switch (tag->type) {
        default:
            printf("Unknown tag: Type: %d, size: %d\n", tag->type, tag->size);
            break;
        }


        // The address must be 8 aligned
        tag = (struct multiboot2_tag *)((char *)tag + (tag->size + 7 & ~7));
    }
}
