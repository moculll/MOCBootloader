MEMORY {
    FLASH (rx)  : ORIGIN = 0x40040000, LENGTH = 0x100000
    RAM (wx) : ORIGIN = 0x40000000, LENGTH = 0x40000
}

ENTRY(_Reset)

SECTIONS {

    .text : {
		*(.text .text*)
		/* important for __libc_init_array */
		KEEP(*(.init))
        KEEP(*(.fini))
        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        /* .dtors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)

        *(.rodata*)

        KEEP(*(.eh_frame*))
        _text_end = .;
	} > FLASH

    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > FLASH
    __exidx_end = .;

     . = ALIGN(16);
    __etext = .;

    .data : AT (__etext) {

		_data_start = .;
        *(vtable)
		*(.data*)
        . = ALIGN(16);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(16);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);


        . = ALIGN(16);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);

        KEEP(*(.jcr*))
        . = ALIGN(16);


		_data_end = .;
	} >RAM


    .bss : {
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

    .heap : {
        . = ALIGN(8);
        _heap_start = .;
        . += 0x8000;
        . = ALIGN(8);
        _heap_end = .;
    } > RAM

    .stack : {
        . = ALIGN(8);
        _stack_bottom = .; 
        . += 0x4000;
        . = ALIGN(8);
        _stack_top = .;
    } > RAM
  
}