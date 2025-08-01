    .thumb_func
    .syntax unified

    .global MOCoroutineSwitchImpl
    .global MOCoroutineSaveContextImpl
    .global MOCoroutineRestoreContextImpl
MOCoroutineSwitchImpl:

    str sp, [r0, #96]
    str lr, [r0, #100]
    ldr r3, [r0, #104]
    mrs r3, psp

    stmdb r0!,{r4-r11}
    tst   lr,0x10
    it    eq
    vstmdbeq r0!,{s16-s31}

    ldr sp, [r1, #96]
    ldr lr, [r1, #100]
    ldr r3, [r1, #104]
    msr psp, r3
    ldr r2, [r1, #108]
    ldr r0, [r1, #112]
    
    ldmia r1!,{r4-r11}
    tst   lr,0x10
    it    eq
    vldmiaeq r1!,{s16-s31}
    bx r2
MOCoroutineSaveContextImpl:
    str sp, [r0, #96]
    str lr, [r0, #100]
    ldr r3, [r0, #104]
    mrs r3, psp
    stmdb r0!,{r4-r11}
    tst   lr,0x10
    it    eq
    vstmdbeq r0!,{s16-s31}


MOCoroutineRestoreContextImpl:
    ldr sp, [r1, #96]
    ldr lr, [r1, #100]
    ldr r3, [r1, #104]
    msr psp, r3
    ldr r2, [r1, #108]
    ldr r0, [r1, #112]
    
    ldmia r1!,{r4-r11}
    tst   lr,0x10
    it    eq
    vldmiaeq r1!,{s16-s31}
    bx r2
