CC      := i686-elf-gcc
AS      := nasm
LD      := i686-elf-gcc
# What standard should I use
CFLAGS  := -std=gnu17 -ffreestanding -O2 -Wall -Wextra
LDFLAGS := -T linker.ld -ffreestanding -O2 -nostdlib
ASFLAGS := -felf32

# Directories
SRC_DIR := src
BUILD_DIR := build
ISO_DIR := $(BUILD_DIR)/isodir

# Files
C_SOURCES := $(wildcard $(SRC_DIR)/*.c)
ASM_SOURCES := boot.asm
C_OBJS := $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
ASM_OBJS := $(BUILD_DIR)/boot.o
OBJS := $(ASM_OBJS) $(C_OBJS)
ISO_FILE := $(BUILD_DIR)/myos.iso

# Output binary
KERNEL_BIN := $(BUILD_DIR)/myos.bin

# GRUB config
GRUB_CFG := $(ISO_DIR)/boot/grub/grub.cfg

.PHONY: all clean run iso

all: $(KERNEL_BIN)

# Link all object files
$(KERNEL_BIN): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS) -lgcc

# Compile C files (pattern rule)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Assemble boot.asm
$(BUILD_DIR)/boot.o: $(ASM_SOURCES) | $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

# Ensure build dir exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

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
	qemu-system-i386 -kernel $(KERNEL_BIN)

# Clean
clean:
	rm -rf $(BUILD_DIR)

# Debug: show what files will be compiled
debug:
	@echo "C sources: $(C_SOURCES)"
	@echo "C objects: $(C_OBJS)"
	@echo "All objects: $(OBJS)"
