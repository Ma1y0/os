# .gdbinit - GDB configuration for kernel debugging

# Connect to QEMU by default
target remote localhost:1234

# Load kernel symbols
symbol-file build/myos.bin

# Set up some useful settings for kernel debugging
set architecture i386
set disassembly-flavor intel

# Useful breakpoints
define kernel-break
    break kernel_main
    break *0x100000
end

# Display useful information
define kernel-info
    info registers
    x/10i $pc
    info stack
end

# Custom commands for kernel debugging
define reset-qemu
    monitor system_reset
end

# Print current instruction and registers
define step-debug
    stepi
    kernel-info
end

# Set initial breakpoint
break kernel_main

echo GDB configured for kernel debugging\n
echo Useful commands:\n
echo   kernel-break  - Set common breakpoints\n
echo   kernel-info   - Show registers and current instruction\n
echo   step-debug    - Step and show info\n
echo   reset-qemu    - Reset QEMU\n
