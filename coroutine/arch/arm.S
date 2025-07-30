    .syntax unified
    .thumb

    .global MOCoroutineSwitchImpl
    .global MOCoroutineSaveContextImpl
    .global MOCoroutineRestoreContextImpl
MOCoroutineSwitchImpl:

    bx lr

MOCoroutineSaveContextImpl:
   
    bx lr

MOCoroutineRestoreContextImpl:
    
    bx lr
