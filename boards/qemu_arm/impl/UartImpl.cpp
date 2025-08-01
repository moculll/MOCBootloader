#include <driver/Uart.h>
#include <UartImpl.h>
#include <cstring>
#include <cstdio>
namespace MOCBootloader {

namespace Driver {
#define UART0_BASE 0x40004000
#define UARTDR (*((volatile uint32_t *)(UART0_BASE)))
#define UARTFR (*((volatile uint32_t *)(UART0_BASE + 0x18)))
#define UARTCR (*((volatile uint32_t *)(UART0_BASE + 0x30)))
#define UARTIBRD (*((volatile uint32_t *)(UART0_BASE + 0x24)))
#define UARTFBRD (*((volatile uint32_t *)(UART0_BASE + 0x28)))
#define UARTLCR_H (*((volatile uint32_t *)(UART0_BASE + 0x2C)))
#define UARTFR_TXFF (1 << 5)
void uart0_send_char(char c)
{
    while (UARTFR & UARTFR_TXFF)
    {
        __asm__ volatile("nop");
    }
    UARTDR = c;
}
int UartImpl::init(uint8_t bus, Uart::UartConfig &config)
{

    return 0;
}

int UartImpl::write(uint8_t bus, const char *data, uint32_t length)
{
    asm volatile (
        "mov r0, #4\n\t"
        "mov r1, %0\n\t"
        "bkpt 0xAB\n\t"
        : 
        : "r" (data)
        : "r0", "r1", "memory"
    );
    return 0;
    
}

char UartImpl::read()
{
    return 0;
}


} /* Driver */
} /* MOCBootloader */