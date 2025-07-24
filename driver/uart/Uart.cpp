#include <driver/Uart.h>
#include <UartImpl.h>
#include <memory>
#include <string_view>

namespace MOCBootloader {

namespace Driver {


Uart *Uart::instance()
{
    return static_cast<Uart *>(UartImpl::_instance());
}

int Uart::init(uint8_t bus, UartConfig &config)
{
    return instance()->init(bus, config);
}

int Uart::write(uint8_t bus, char *data, uint32_t length)
{
    return instance()->write(bus, data, length);
}

} /* Driver */
} /* MOCBootloader */