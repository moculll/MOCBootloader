#include <driver/Uart.h>
#include <UartImpl.h>
#include <cstring>
#include <cstdio>
#include <stdint.h>
#include <nrfx_uarte.h>
namespace MOCBootloader {

namespace Driver {

#define NRFX_UARTE0_INST_IDX 0
static nrfx_uarte_t uarteInstance = NRFX_UARTE_INSTANCE(0);
int UartImpl::init(uint8_t bus, Uart::UartConfig &config)
{
    
    nrfx_uarte_config_t uart_cfg = NRFX_UARTE_DEFAULT_CONFIG(20, 24);
    nrfx_uarte_init(&uarteInstance, &uart_cfg, NULL);
    /* nrfx_uarte_config_t uart_cfg;
    nrfx_uarte_init(NULL, &uart_cfg, NULL); */

    return 0;
}

int UartImpl::write(uint8_t bus, const char *data, uint32_t length)
{

    
    return nrfx_uarte_tx(&uarteInstance, reinterpret_cast<const uint8_t *>(data), length, NRFX_UARTE_TX_EARLY_RETURN);
    
}

char UartImpl::read()
{
    return (char)(*UART0_DR & 0xFF);
}


} /* Driver */
} /* MOCBootloader */