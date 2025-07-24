add_library(Uart STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/uart/Uart.cpp
)

target_include_directories(Uart PRIVATE ${BOARD_DIR}/include)

