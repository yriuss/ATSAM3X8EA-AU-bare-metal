/* Memory Spaces Definitions */
MEMORY
{
	flash (rx)    : ORIGIN = 0x00080000, LENGTH = 0x00080000 /* Flash, 512K */
	sram0 (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00010000 /* sram0, 64K */
	sram1 (rwx) : ORIGIN = 0x20080000, LENGTH = 0x00008000 /* sram1, 32K */
	ram (rwx)   : ORIGIN = 0x20070000, LENGTH = 0x00018000 /* sram, 96K */
}

/* The stack size used by the application. NOTE: you need to adjust  */
STACK_SIZE = DEFINED(STACK_SIZE) ? STACK_SIZE : 0x200 ;

/* Section Definitions */
SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        _sfixed = .;
        KEEP(*(.vectors .vectors.*))
        *(.text .text.* .gnu.linkonce.t.*)
        *(.glue_7t) *(.glue_7)
        *(.rodata .rodata* .gnu.linkonce.r.*)
        *(.ARM.extab* .gnu.linkonce.armextab.*)

        /* Support C constructors, and C destructors in both user code
           and the C library. This also provides support for C++ code. */
        . = ALIGN(4);
        KEEP(*(.init))
        . = ALIGN(4);
        __preinit_array_start = .;
        KEEP (*(.preinit_array))
        __preinit_array_end = .;

        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;

        . = ALIGN(0x4);
        KEEP (*crtbegin.o(.ctors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
        KEEP (*(SORT(.ctors.*)))
        KEEP (*crtend.o(.ctors))

        . = ALIGN(4);
        KEEP(*(.fini))

        . = ALIGN(4);
        __fini_array_start = .;
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        __fini_array_end = .;

        KEEP (*crtbegin.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*crtend.o(.dtors))

        . = ALIGN(4);
        _efixed = .;            /* End of text section */
    } > flash

    . = ALIGN(4);
    _data_flash = .;
    . = ORIGIN(ram);

    .relocate : AT (_data_flash)
    {
        . = ALIGN(4);
        _data_begin = .;
        *(.ramfunc .ramfunc.*);
        *(.data .data.*);
        . = ALIGN(4);
        _data_end = .;
    } > ram

    /* .bss section which is used for uninitialized data */
    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        _bss_begin = . ;
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(4);
        _bss_end = . ;
    } > ram

    /* stack section */
    _stack_end = ALIGN(ORIGIN(ram) + LENGTH(ram) - 8, 8);
    _stack_begin = _stack_end - STACK_SIZE;
    . = _stack_begin;
    .stack (NOLOAD): {
        . = . + STACK_SIZE;
    } > ram
}
