#pragma once
/* #include <driver/Uart.h> */
namespace MOCBootloader {

namespace Driver {

class Uart;

class UartImpl final : public Uart {
    friend class Uart;
public:
 
    int init(uint8_t bus, UartConfig &config) override;

    int write(uint8_t bus, char *data, uint32_t length) override;

    

private:
    static void putChar(char c)
    {
        *UART0_DR = (unsigned int)c;
    }

    inline static volatile unsigned int *UART0_DR = (unsigned int *)0x09000000;
    

    static UartImpl *_instance()
    {
        static UartImpl instance;
        return &instance;
    }
};



} /* Driver */
} /* MOCBootloader */