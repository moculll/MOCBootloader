
include(${CMAKE_SOURCE_DIR}/arch/arm/arch.cmake)

add_library(boardImpl
    ${BOARD_DIR}/Board.cpp
    ${BOARD_DIR}/impl/UartImpl.cpp
)

target_include_directories(boardImpl PRIVATE
    ${BOARD_DIR}/include
)

