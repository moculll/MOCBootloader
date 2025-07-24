#pragma once
#include <driver/Uart.h>
namespace MOCBootloader {

class Board {
public:
    
    static Board &getInstance()
    {
        
        return *instance;
    }


private:
    
    inline static Board *instance = nullptr;
    Board();
    Board(Board &) = delete;
    Board(Board &&) = delete;
};

} /* MOCBootloader */