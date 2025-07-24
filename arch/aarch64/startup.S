.section .text.startup
.global _Reset
_Reset:
    /* set stack top */
    ldr x0, =_stack_top
    /* set sp 16bytes aligned, aarch64 required */
    and x0, x0, ~0xF
    mov sp, x0
    /* open fpu, it's important for printf because ldp uses fpu, if we don't open it the program will crash when printf is called */
    mrs x1, cpacr_el1
    orr x1, x1, #(0b11 << 20)
    msr cpacr_el1, x1
    isb

    
    /* clear bss */
    ldr x0, =__bss_start
    ldr x1, =__bss_end
    cbz x1, 2f
1:  str xzr, [x0], #8
    cmp x0, x1
    b.lt 1b
2:
    bl __libc_init_array
    bl main
    b .