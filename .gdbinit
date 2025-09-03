# GDB initialization script for kernel debugging
set confirm off
set verbose off
set prompt \033[31mgdb$ \033[0m

# Enable pretty printing (if available)
set print pretty on
set print array on
set print array-indexes on

# Don't pause for output
set pagination off

# Intel syntax for assembly
set disassembly-flavor intel

# Allow debugging without source
set substitute-path /build/gdb /usr/src/gdb

# Architecture settings
set architecture i386:x86-64

# Define some useful commands for kernel debugging
define hook-stop
    # Show current instruction and next few instructions
    x/5i $pc
end

define regs
    printf "RAX: %016lx  RBX: %016lx  RCX: %016lx  RDX: %016lx\n", $rax, $rbx, $rcx, $rdx
    printf "RSI: %016lx  RDI: %016lx  RBP: %016lx  RSP: %016lx\n", $rsi, $rdi, $rbp, $rsp
    printf "RIP: %016lx  RFLAGS: %08x\n", $rip, $eflags
    printf "CS: %04x  DS: %04x  ES: %04x  FS: %04x  GS: %04x  SS: %04x\n", $cs, $ds, $es, $fs, $gs, $ss
end

define stack
    printf "Stack trace (top 10 entries):\n"
    x/10gx $rsp
end

define vgadump
    printf "VGA buffer contents (first 160 chars):\n"
    x/80hx 0xB8000
end

# Set up common breakpoints
define setup_kernel_debug
    break kernel_main
    break *0x100000
    # Add more breakpoints as needed
end

# Helper to connect to QEMU
define qemu
    target remote :1234
end

# Show this help
define help-kernel
    printf "Custom kernel debugging commands:\n"
    printf "  regs        - Show all general purpose registers\n"
    printf "  stack       - Show stack contents\n"
    printf "  vgadump     - Dump VGA text buffer\n"
    printf "  qemu        - Connect to QEMU GDB server\n"
    printf "  setup_kernel_debug - Set common kernel breakpoints\n"
    printf "\nUsage:\n"
    printf "  1. Start QEMU: make debug\n"
    printf "  2. In GDB: qemu\n"
    printf "  3. Set breakpoint: break kernel_main\n"
    printf "  4. Continue: continue\n"
end

printf "Kernel debugging GDB config loaded.\n"
printf "Type 'help-kernel' for kernel-specific commands.\n"
