#include <stdio.h>
#include <driver/Uart.h>
#include <string.h>
#include <iostream>
int main(int argc, char *argv[])
{
    
    MOCBootloader::Driver::Uart::UartConfig config;
    MOCBootloader::Driver::Uart::instance()->init(0, config);

    printf("[C] Welcome to MOCBootloader!\r\n");
    std::cout << "[C++] Welcome to MOCBootloader!" << std::endl;

    return 0;
}