MEMORY {
    RAM (rwx) : ORIGIN = 0x40000000, LENGTH = 4096K
}

SECTIONS {
    .text : {
		*(.text.startup)
		*(.text .text.*)
		/* important for __libc_init_array */
		KEEP(*(.init))
	} > RAM

    .rodata : { *(.rodata) } > RAM
    .data : { *(.data) } > RAM

    .bss : {
        __bss_start = .;
        *(.bss)
        *(COMMON)
        __bss_end = .;
    } > RAM

	
    .heap (NOLOAD) : {
        . = ALIGN(8);
        _heap_start = .;
        . += 0x160000;
        _heap_end = .;
    } > RAM

	.init_array : {
		__init_array_start = .;
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		__init_array_end = .;
	} > RAM

    .stack (NOLOAD) : {
        . = ALIGN(16);
        _stack_bottom = .; 
        . += 0x16000;
        _stack_top = .;
    } > RAM

	
    _end = ALIGN(8);
}