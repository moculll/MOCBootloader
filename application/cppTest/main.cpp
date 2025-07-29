#include <stdio.h>
#include <driver/Uart.h>
#include <string.h>
#include <forward_list>
#include <Board.h>

static void semihosting_write0(const char* str) {
    register const char* r1 asm("r1") = str;
    register int op asm("r0") = 4;  // SYS_WRITE0: write null-terminated string
    asm volatile ("bkpt 0xAB"
                  :
                  : "r"(op), "r"(r1)
                  : "memory");
}

void semihosting_exit(int code) {
    //register int r0 asm("r0") = code;
    //register int r1 asm("r1") = 0x18;  // SYS_EXIT
    //asm volatile ("bkpt 0xAB" : : "r"(r0), "r"(r1));
    register int op asm("r0") = 0x18;      // SYS_EXIT
    register int arg asm("r1") = code;     // exit code
    asm volatile ("bkpt 0xAB" : : "r"(op), "r"(arg) : "memory");
}

 __attribute__((always_inline)) static inline void __ISB(void)
{
  __asm volatile ("isb 0xF":::"memory");
}


/**
  \brief   Data Synchronization Barrier
  \details Acts as a special kind of Data Memory Barrier.
           It completes when all explicit memory accesses before this instruction complete.
 */
 __attribute__((always_inline)) static inline void __DSB(void)
{
  __asm volatile ("dsb 0xF":::"memory");
}
int main(void)
{
    /* open fpu */
    *(volatile unsigned int*)0xE000ED88 |= ((3UL << 10*2) | (3UL << 11*2));
    __DSB();
    __ISB();
    MOCBootloader::Driver::Uart::UartConfig config;
    MOCBootloader::Driver::Uart::instance().init(0, config);

    semihosting_write0("minimalTest\r\n");
    semihosting_exit(0);
    while(1);
    return 0;
}