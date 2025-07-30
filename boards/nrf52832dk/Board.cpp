#include <Board.h>
#include <driver/Uart.h>
#include <UartImpl.h>
#include <system_nrf52.h>
namespace MOCBootloader {

void Board::init()
{
    SystemInit();
}

Board::Board()
{
    
}

} /* MOCBootloader */