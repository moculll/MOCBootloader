#include <driver/Uart.h>
#include <UartImpl.h>
#include <cstring>
#include <cstdio>
namespace MOCBootloader {

namespace Driver {

int UartImpl::init(uint8_t bus, Uart::UartConfig &config)
{
    return 0;
}

int UartImpl::write(uint8_t bus, char *data, uint32_t length)
{
    while(length--) {
        putChar(*data++);
    }
    return 0;
    
}

} /* Driver */
} /* MOCBootloader */