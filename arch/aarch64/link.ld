MEMORY {
    FLASH (rx)  : ORIGIN = 0x40040000, LENGTH = 0x100000
    RAM (wx) : ORIGIN = 0x40000000, LENGTH = 0x40000
}

ENTRY(_Reset)

SECTIONS {
    .text : {
        . = ALIGN(8);
		*(.text.startup)
		*(.text .text*)
        *(.rodata)
        *(.rodata*)
        *(.srodata)        /* .srodata sections (constants, strings, etc.) */
		*(.srodata*)
		/* important for __libc_init_array */
		KEEP(*(.init))
        . = ALIGN(8);
        _text_end = .;
	} > FLASH

    .init_array : {
        . = ALIGN(8);
		__init_array_start = .;
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
        . = ALIGN(8);
		__init_array_end = .;
	} > RAM

    .stack (NOLOAD) : {
        . = ALIGN(8);
        _stack_bottom = .; 
        . += 0x8000;
        . = ALIGN(8);
        _stack_top = .;
    } > RAM

    .data : {
        . = ALIGN(16);
		_data_start = .;
		*(.data*)
        *(.sdata)          /* .sdata sections */
		*(.sdata*)         /* .sdata* sections */
		. = ALIGN(16);
		_data_end = .;
	} >RAM AT >FLASH
	_data_loadaddr = LOADADDR(.data);

    .bss(NOLOAD) : {
        . = ALIGN(8);
        __bss_start = .;
        *(.bss)
        *(.bss*)
        *(.sbss)
		*(.sbss*)
        *(COMMON)
        . = ALIGN(8);
        __bss_end = .;
    } > RAM

    .heap (NOLOAD) : {
        . = ALIGN(8);
        _heap_start = .;
        . += 0x16000;
        . = ALIGN(8);
        _heap_end = .;
    } > RAM


}