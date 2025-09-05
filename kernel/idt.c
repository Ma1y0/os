// // Interrupt Descriptor Table
// // X86_64
//
// #include <kernel/console.h>
// #include <lib/types.h>
//
// extern isr0;
//
// #define IDT_SIZE 256
//
// struct IDTEntry {
//     uint16_t offset_1; // offset bits 0..15
//     uint16_t selector; // a code segment selector in GDT
//     uint8_t ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
//     uint8_t type_attr; // gate type, dpl, and p fields
//     uint16_t offset_2; // offset bits 16..31
//     uint32_t offset_3; // offset bits 32..63
//     uint32_t zero;     // reserved
// } __attribute__((packed));
//
// struct IDTPointer {
//     uint16_t limit; // size of IDT - 1
//     uint64_t base;  // address of first IDTEntry
// } __attribute__((packed));
//
//
// struct IDTEntry idt[IDT_SIZE];
// struct IDTPointer idt_ptr;
//
// void set_idt_entry(int n, uint64_t handler, uint16_t selector, uint8_t type_attr) {
//     idt[n].offset_1 = handler & 0xFFFF;
//     idt[n].selector = selector;
//     idt[n].ist = 0;
//     idt[n].type_attr = type_attr;
//     idt[n].offset_2 = (handler >> 16) & 0xFFFF;
//     idt[n].offset_3 = (handler >> 32) & 0xFFFFFFFF;
//     idt[n].zero = 0;
// }
//
// void idt_load() {
//     idt_ptr.limit = (sizeof(struct IDTEntry) * IDT_SIZE) - 1;
//     idt_ptr.base = (uint64_t)&idt;
//
//     __asm__ volatile("lidt %0" : : "m"(idt_ptr));
// }
//
// void idt_init() {
//     // zero the table
//     for (int i = 0; i < IDT_SIZE; i++) {
//         set_idt_entry(i, (uint64_t)isr0, 0x08, 0x8E);
//     }
//     idt_load();
// }
//
// void isr_handler_c(int interrupt, int error_code) {
//     // printf("Interrupt %d, error code %d\n", interrupt, error_code);
//     puts("FUCK");
//     for (;;)
//         ; // halt
// }
