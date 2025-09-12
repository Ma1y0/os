#include <lib/types.h>
#include <mm/memory.h>
#include <stddef.h>

static size_t heap_ptr;

void heap_init(void) {
    heap_ptr = (size_t)__heap_start;
}

// Very simple bump allocator
void *kmalloc(size_t size) {
    // Align to 8. (CPUs like it???)
    size_t ptr = (heap_ptr + 8 - 1) & ~(8 - 1);
    if (ptr + size > (size_t)__heap_end) {
        return NULL;
    }

    // Move the heap_ptr to the end
    heap_ptr = ptr + size;

    return (void *)ptr;
}
