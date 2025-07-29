#pragma once
#include <memory>
#include <string_view>

namespace MOCBootloader {

namespace Driver {


class Uart {

public:
    struct UartConfig {
        uint32_t tx_pin;
        uint32_t rx_pin;
        uint32_t cts_pin;
        uint32_t rts_pin;

        uint32_t baud_rate;
        uint8_t data_bits;
        uint8_t stop_bits;
        uint8_t parity;
        uint8_t flow_ctrl;

        UartConfig() : tx_pin(0), rx_pin(0), cts_pin(0), rts_pin(0), baud_rate(115200), data_bits(8), stop_bits(1), parity(0), flow_ctrl(0)
        {

        }
    };
    
    virtual int init(uint8_t bus, UartConfig &config) = 0;

    virtual int write(uint8_t bus, const char *data, uint32_t length) = 0;
    virtual bool rxReady() = 0;
    virtual bool txReady() = 0;
    virtual char read() = 0;

    static Uart &instance();

    Uart() = default;
    Uart(Uart &) = delete;
    Uart(Uart &&) = delete;

private:
    
    
};




} /* Driver */
} /* MOCBootloader */
