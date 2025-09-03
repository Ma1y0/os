ARCH ?= x86_64
KERNEL_NAME = MyOS


ifeq ($(ARCH),x86_64)
	CC      = x86_64-elf-gcc
	AS      = nasm
	LD      = x86_64-elf-gcc
	# CFLAGS = -m64 -ffreestanding -fno-stack-protector -fno-pic -mno-red-zone
	#  -g -ggdb
	CFLAGS  = -std=gnu17 -ffreestanding -O0 -Wall -Wextra 
	LDFLAGS = -T ./arch/x86_64/linker.ld -ffreestanding -O2 -nostdlib
	ASFLAGS = -felf64
endif

# Directories
SRCDIR = .
BUILDDIR = build
ARCHDIR = arch/$(ARCH)
KERNELDIR = kernel
DRIVERSDIR = drivers
LIBDIR = lib
INCLUDEDIR = include

# Source files
C_SOURCES = $(shell find $(KERNELDIR) $(DRIVERSDIR) $(LIBDIR) -name "*.c")
ASM_SOURCES = $(shell find $(ARCHDIR) -name "*.asm")

# Object files
C_OBJECTS = $(C_SOURCES:%.c=$(BUILDDIR)/%.o)
ASM_OBJECTS = $(ASM_SOURCES:%.asm=$(BUILDDIR)/%.o)
OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)


# Compiler flags
CFLAGS += -std=c17 -Wall -Wextra -I$(INCLUDEDIR)

# Default target
all: $(BUILDDIR)/$(KERNEL_NAME).bin

# Create kernel binary
$(BUILDDIR)/$(KERNEL_NAME).bin: $(OBJECTS)
	@echo "Linking kernel for $(ARCH)..."
	@mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) -o $@ $^
	@echo "Kernel built successfully: $@"

# Compile C source files
$(BUILDDIR)/%.o: %.c
	@echo "Compiling C: $<"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Assemble ASM source files
$(BUILDDIR)/%.o: %.asm
	@echo "Assembling: $<"
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

# Create ISO image (useful for testing)
iso: $(BUILDDIR)/$(KERNEL_NAME).bin
	@echo "Creating ISO image..."
	@mkdir -p $(BUILDDIR)/iso/boot/grub
	@cp $(BUILDDIR)/$(KERNEL_NAME).bin $(BUILDDIR)/iso/boot/
	@echo 'menuentry "$(KERNEL_NAME)" {' > $(BUILDDIR)/iso/boot/grub/grub.cfg
	@echo '    multiboot2 /boot/$(KERNEL_NAME).bin' >> $(BUILDDIR)/iso/boot/grub/grub.cfg
	@echo '}' >> $(BUILDDIR)/iso/boot/grub/grub.cfg
	@grub-mkrescue -o $(BUILDDIR)/$(KERNEL_NAME).iso $(BUILDDIR)/iso 2>/dev/null || echo "grub-mkrescue not found, skipping ISO creation"

# Run kernel with ISO in QEMU
run-iso: iso
ifeq ($(ARCH),x86_64)
	qemu-system-x86_64 -cdrom $(BUILDDIR)/$(KERNEL_NAME).iso
else
	@echo "Run-iso target not implemented for $(ARCH)"
endif

# Debug with GDB
debug: $(BUILDDIR)/$(KERNEL_NAME).bin
ifeq ($(ARCH),x86_64)
	qemu-system-x86_64 -kernel $(BUILDDIR)/$(KERNEL_NAME).bin -serial stdio -s -S &
	gdb $(BUILDDIR)/$(KERNEL_NAME).bin -ex "target remote :1234"
else
	@echo "Debug target not implemented for $(ARCH)"
endif

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILDDIR)

# Generate compile_commands.json using bear
bear: clean
	bear -- $(MAKE) all


# Clean and rebuild
rebuild: clean all

# Create build directories
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

# Show build information
info:
	@echo "Kernel Build Information:"
	@echo "  Architecture: $(ARCH)"
	@echo "  Kernel Name:  $(KERNEL_NAME)"
	@echo "  C Compiler:   $(CC)"
	@echo "  Assembler:    $(AS)"
	@echo "  Linker:       $(LD)"
	@echo "  C Sources:    $(C_SOURCES)"
	@echo "  ASM Sources:  $(ASM_SOURCES)"
	@echo "  Objects:      $(OBJECTS)"

# Show available targets
help:
	@echo "Available targets:"
	@echo "  all       - Build the kernel binary (default)"
	@echo "  iso       - Create bootable ISO image"
	@echo "  run       - Run kernel in QEMU"
	@echo "  run-iso   - Run kernel ISO in QEMU"
	@echo "  debug     - Run kernel in QEMU with GDB debugging"
	@echo "  clean     - Remove build artifacts"
	@echo "  rebuild   - Clean and rebuild"
	@echo "  info      - Show build configuration"
	@echo "  bear      - Generate compile_commands.json"
	@echo "  help      - Show this help message"
	@echo ""
	@echo "Variables:"
	@echo "  ARCH      - Target architecture (default: x86_64)"
	@echo ""
	@echo "Examples:"
	@echo "  make ARCH=x86_64    # Build for x86_64"
	@echo "  make clean all      # Clean and rebuild"
	@echo "  make run            # Build and run in QEMU"

# Prevent make from deleting intermediate files
.PRECIOUS: $(BUILDDIR)/%.o

# Declare phony targets
.PHONY: all clean rebuild run run-iso debug iso info help
