.section .text.startup
.global _Reset
_Reset:
    mov x0, xzr
	mov x1, xzr
	mov x2, xzr
	mov x3, xzr
	mov x4, xzr
	mov x5, xzr
	mov x6, xzr
	mov x7, xzr
	mov x8, xzr
	mov x9, xzr
	mov x10, xzr
	mov x11, xzr
	mov x12, xzr
	mov x13, xzr
	mov x14, xzr
	mov x15, xzr
	mov x16, xzr
	mov x17, xzr
	mov x18, xzr
	mov x19, xzr
	mov x20, xzr
	mov x21, xzr
	mov x22, xzr
	mov x23, xzr
	mov x24, xzr
	mov x25, xzr
	mov x26, xzr
	mov x27, xzr
	mov x28, xzr
	mov x29, xzr
	mov x30, xzr

    /* open fpu, it's important for printf because ldp uses fpu, if we don't open it the program will crash when printf is called */
    mrs x1, cpacr_el1
    orr x1, x1, #(0b11 << 20)
    msr cpacr_el1, x1
    isb

    /* set stack top */
    ldr x0, =_stack_top
    /* set sp 16bytes aligned, aarch64 required */
    and x0, x0, ~0xF
    mov sp, x0

_data_init:
	ldr x0, =_data_loadaddr
	ldr x1, =_data_start
	ldr x2, =_data_end
_data_init_loop:
	cmp x1, x2
	beq _bss_init
	ldp x3, x4, [x0], 16
	stp x3, x4, [x1], 16
	b   _data_init_loop

    

_bss_init:
    /* clear bss */
    ldr x0, =__bss_start
    ldr x1, =__bss_end
    cbz x1, 2f
1:  str xzr, [x0], #8
    cmp x0, x1
    b.lt 1b
_cleanup:
	mov x0, xzr
	mov x1, xzr
	mov x2, xzr
	mov x3, xzr
	mov x4, xzr
2:
    bl __libc_init_array
    bl main
    b .