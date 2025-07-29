#pragma once
#include <driver/Uart.h>
namespace MOCBootloader {

namespace Driver {


class UartImpl final : public Uart {
public:
 
    int init(uint8_t bus, UartConfig &config) override;

    int write(uint8_t bus, const char *data, uint32_t length) override;

    char read() override;
    
    bool txReady() override
    {
        return false;
    }

    bool rxReady() override
    {
        return false;
    }

    static UartImpl &_instance()
    {
        static UartImpl instance;
        return instance;
    }
private:

    UartImpl() = default;
    UartImpl(UartImpl &) = delete;
    UartImpl(UartImpl &&) = delete;
    static void putChar(const char *c)
    {
        
    }



    
};



} /* Driver */
} /* MOCBootloader */