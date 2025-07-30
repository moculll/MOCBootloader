#include <driver/Uart.h>
#include <UartImpl.h>
#include <memory>
#include <string_view>

namespace MOCBootloader {

namespace Driver {


Uart &Uart::instance()
{
    return static_cast<Uart &>(UartImpl::_instance());
}



} /* Driver */
} /* MOCBootloader */