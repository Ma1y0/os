CC      := i686-elf-gcc
AS      := nasm
LD      := i686-elf-gcc
CFLAGS  := -std=gnu17 -ffreestanding -O0 -Wall -Wextra -Iinclude -Iinclude/drivers -Iinclude/kernel -Iinclude/lib -g -ggdb
LDFLAGS := -T linker.ld -ffreestanding -O2 -nostdlib
ASFLAGS := -felf32

# Directories
BUILD_DIR := build
ISO_DIR := $(BUILD_DIR)/isodir

# Source files
KERNEL_SRC := $(wildcard kernel/*.c)
DRIVERS_SRC := $(wildcard drivers/*.c)
LIB_SRC := $(wildcard lib/*.c)
C_SOURCES := $(KERNEL_SRC) $(DRIVERS_SRC) $(LIB_SRC)
ASM_SOURCES := arch/x86/boot.asm

# Object files
C_OBJS := $(C_SOURCES:%.c=$(BUILD_DIR)/%.o)
C_OBJS := $(subst kernel/,kernel/,$(C_OBJS))
C_OBJS := $(subst drivers/,drivers/,$(C_OBJS))
C_OBJS := $(subst lib/,lib/,$(C_OBJS))
ASM_OBJS := $(BUILD_DIR)/boot.o
OBJS := $(ASM_OBJS) $(C_OBJS)
ISO_FILE := $(BUILD_DIR)/myos.iso

# Output binary
KERNEL_BIN := $(BUILD_DIR)/myos.bin

# GRUB config
GRUB_CFG := $(ISO_DIR)/boot/grub/grub.cfg

.PHONY: all clean run iso debug bear

all: $(KERNEL_BIN)

# Link all object files
$(KERNEL_BIN): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS) -lgcc

# Compile C files (pattern rule)
$(BUILD_DIR)/kernel/%.o: kernel/%.c | $(BUILD_DIR)/kernel
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/drivers/%.o: drivers/%.c | $(BUILD_DIR)/drivers
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/lib/%.o: lib/%.c | $(BUILD_DIR)/lib
	$(CC) -c $< -o $@ $(CFLAGS)

# Assemble boot.asm
$(BUILD_DIR)/boot.o: $(ASM_SOURCES) | $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

# Ensure build subdirs exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
$(BUILD_DIR)/kernel:
	mkdir -p $(BUILD_DIR)/kernel
$(BUILD_DIR)/drivers:
	mkdir -p $(BUILD_DIR)/drivers
$(BUILD_DIR)/lib:
	mkdir -p $(BUILD_DIR)/lib

# Build GRUB ISO
iso: $(ISO_FILE)

$(ISO_FILE): $(KERNEL_BIN) $(GRUB_CFG)
	grub-mkrescue -o $@ $(ISO_DIR)

$(GRUB_CFG): $(KERNEL_BIN)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL_BIN) $(ISO_DIR)/boot/myos.bin
	echo 'menuentry "myos" { multiboot /boot/myos.bin }' > $(GRUB_CFG)

# Run in QEMU
run: $(KERNEL_BIN)
	qemu-system-i386 -kernel $(KERNEL_BIN) -device virtio-gpu-pci

# Clean
clean:
	rm -rf $(BUILD_DIR)

# Generate compile_commands.json using bear
bear: clean
	bear -- $(MAKE) all


LDFLAGS_DEBUG := -T linker.ld -ffreestanding -O0 -nostdlib -g

debug-build: CFLAGS += -DDEBUG
debug-build: LDFLAGS := $(LDFLAGS_DEBUG)
debug-build: $(KERNEL_BIN)

# Run QEMU with GDB server enabled
run-debug: $(KERNEL_BIN)
	qemu-system-i386 -kernel $(KERNEL_BIN) -device virtio-gpu-pci -s -S

# Run GDB and connect to QEMU
gdb: $(KERNEL_BIN)
	gdb -ex "target remote localhost:1234" -ex "symbol-file $(KERNEL_BIN)" $(KERNEL_BIN)

# Run both QEMU and GDB in separate terminals (requires tmux or screen)
debug: $(KERNEL_BIN)
	@echo "Starting QEMU with GDB server on port 1234..."
	@echo "Run 'make gdb-connect' in another terminal to connect GDB"
	qemu-system-i386 -kernel $(KERNEL_BIN) -device virtio-gpu-pci -s -S

gdb-connect: $(KERNEL_BIN)
	gdb -ex "target remote localhost:1234" -ex "symbol-file $(KERNEL_BIN)" -ex "b kernel_main" -ex "continue" $(KERNEL_BIN)
