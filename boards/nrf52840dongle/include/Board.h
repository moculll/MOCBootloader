#pragma once
#include <driver/Uart.h>
namespace MOCBootloader {

class Board {
public:
    
    static Board &getInstance()
    {
        static Board instance;
        return instance;
    }

    void init();

private:
    
   
    Board();
    Board(Board &) = delete;
    Board(Board &&) = delete;
};

} /* MOCBootloader */