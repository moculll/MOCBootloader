#include <stdio.h>
#include <driver/Uart.h>
#include <string.h>
#include <forward_list>
#include <Board.h>
#include <MOCoroutine.h>
static void semihosting_write0(const char* str) {
    register const char* r1 asm("r2") = str;
    register int op asm("r3") = 4;  // SYS_WRITE0: write null-terminated string
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


static void putChar(const char *c)
{
    static volatile unsigned int *UART0_DR = (unsigned int *)0x40009000;
    *UART0_DR = static_cast<unsigned int>(*c);
}

int main(void)
{
    
    /* open fpu */
    *(volatile unsigned int*)0xE000ED88 |= ((3UL << 10*2) | (3UL << 11*2));
    __DSB();
    __ISB();

    MOCBootloader::Driver::Uart::UartConfig config;
    MOCBootloader::Driver::Uart::instance().init(0, config);

    auto stack = std::make_unique<MOCoroutine::Stack>(1024);
    auto stack1 = std::make_unique<MOCoroutine::Stack>(1024);
    MOCoroutine::Scheduler &scheduler = MOCoroutine::Scheduler::instance();
    MOCoroutine::Coroutine coro("coro", std::move(stack), [&scheduler] () {
        int coroId = 0;
        for(int i = 0; i < 5; i++) {
            /* printf("id: %d.\r\n", i); */
            coroId++;
            scheduler.yield();
        }
        printf("id: %d.\r\n", coroId);
    });

    MOCoroutine::Coroutine coroShared("coroShared", std::move(stack1), [&scheduler] () {
        int coroSharedId = 10;
        for(int i = 0; i < 5; i++) {

            scheduler.yield();
        }
        printf("id: %d.\r\n", coroSharedId);
        
    });

    scheduler.add(&coro);
    scheduler.add(&coroShared);
    scheduler.run();
    printf("exit program\r\n.");
    return 0;
}