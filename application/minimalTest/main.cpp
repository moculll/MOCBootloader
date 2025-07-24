#include <stdio.h>
#include <driver/Uart.h>
#include <string.h>
int main(int argc, char *argv[])
{
    char buffer[64];
    memcpy(buffer, "Welcome to MOCBootloader!\r\n", 29);
    MOCBootloader::Driver::Uart::UartConfig config;
    
    MOCBootloader::Driver::Uart::instance()->init(0, config);

    MOCBootloader::Driver::Uart::instance()->write(0, buffer, 29);
    return 0;
}