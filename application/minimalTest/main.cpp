#include <stdio.h>
volatile unsigned int *UART0_DR = (unsigned int *)0x09000000;

void uart_putc(char c) {
    *UART0_DR = (unsigned int)c;
}

void uart_puts(const char *str) {
    while (*str) {
        uart_putc(*str++);
    }
}

int main(int argc, char *argv[])
{
    uart_puts("Welcome to MOCBootloader!\r\n");
    return 0;
}