section .multiboot_header
    ; Align the entire section to a 8-byte boundary
    align 8

multiboot_header:
    dd 0xe85250d6      ; Multiboot magic number
    dd 0               ; Multiboot Arch i386
    dd multiboot_header_end - multiboot_header
    dd -(0xe85250d6 + (multiboot_header_end - multiboot_header)) ; Checksum

    ; Information Request Tag: modules (type=3). I have no idea what this does.
    align 8
    dw 1
    dw 0                            ; flags = 0
    dd 16                           ; size = 16 bytes total
    dd 3    ; we want modules
    dd 0                            ; end of the request array

    ; Module Align Tag
    align 8
    dw 6
    dw 0
    dd 8

    ; GOP (Graphics Output Protocol UEFI thing) Framebuffer Tag
    dw 5                            ; Tag type = 5 (Framebuffer)
    dw 0                            ; Flags
    dd 20                           ; Size of the tag in bytes
    dd 0                            ; Preferred width in pixels (0 = no preference)
    dd 0                            ; Preferred height in pixels (0 = no preference)
    dd 32                           ; Preferred depth in bits per pixel (0 = no preference)

    ; Padding to align to 8-byte boundary
    times 4 db 0

    ; End Tag
    dw 0
    dw 0
    dd 8

multiboot_header_end:
