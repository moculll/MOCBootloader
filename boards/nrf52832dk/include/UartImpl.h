#pragma once

namespace MOCBootloader {

namespace Driver {

class Uart;

class UartImpl final : public Uart {
public:
 
    int init(uint8_t bus, UartConfig &config) override;

    int write(uint8_t bus, const char *data, uint32_t length) override;

    char read() override;
    
    bool txReady() override
    {
        return static_cast<bool>(!(*UART0_FR & (1 << 5)));
    }

    bool rxReady() override
    {
        return static_cast<bool>(!(*UART0_FR & (1 << 4)));
    }

    static UartImpl *_instance()
    {
        static UartImpl instance;
        return &instance;
    }
private:

    UartImpl() = default;
    UartImpl(UartImpl &) = delete;
    UartImpl(UartImpl &&) = delete;
    static void putChar(const char *c)
    {
        *UART0_DR = static_cast<unsigned int>(*c);
    }

    
    inline static volatile unsigned int *UART0_DR = (unsigned int *)0x09000000;
    inline static volatile unsigned int *UART0_FR = (unsigned int *)0x09000018;


    
};



} /* Driver */
} /* MOCBootloader */