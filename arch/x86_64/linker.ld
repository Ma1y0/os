ENTRY(start)

OUTPUT_FORMAT("elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)

SECTIONS
{
  .multiboot_header :
  {
    KEEP(*(.multiboot_header))
  }

  /* Load kernel at 1 MiB (traditional OS start) */
  . = 1M;

  /* Boot/early startup code (before .text proper) */
  .boot ALIGN(16) :
  {
    KEEP(*(.boot))
  }

  /* Executable kernel code */
  .text ALIGN(16) :
  {
    __text_start = .;               /* Mark start of .text for runtime use */
    *(.text)                        /* All functions without a subsection (a section of code containing one or more functions that is 
				       treated as a distinct, smaller unit by a linker) */
    *(.text.*)                      /* All functions with named subsections */
  }
  __text_end = .;                   /* Mark end of .text */

  /* Read-only data (constants, jump tables, etc.) */
  .rodata ALIGN(8) :
  {
    *(.rodata)
    *(.rodata.*)
  }

   /* Initialized data (global/static vars with values) */
  .data ALIGN(8) :
  {
    __data_start = .;
    *(.data)
    *(.data.*)
  }
  __data_end = .;

  /* Uninitialized data (zeroed at runtime, no space in binary) */
  .bss ALIGN(4096) :
  {
    __bss_start = .;
    *(.bss)
    *(.bss.*)
    *(COMMON)  /* Old-style uninitialized globals (???) */
  }
  __bss_end = .;

  }
