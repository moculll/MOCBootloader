#pragma once
#include <driver/Uart.h>
namespace MOCBootloader {

class Board {
public:
    
    static Board &getInstance()
    {
        
        return *instance;
    }

    void init();

private:
    
    inline static Board *instance = nullptr;
    Board();
    Board(Board &) = delete;
    Board(Board &&) = delete;
};

} /* MOCBootloader */