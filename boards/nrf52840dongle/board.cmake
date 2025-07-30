
include(${CMAKE_SOURCE_DIR}/arch/arm/arch.cmake)

add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/nordic)

add_definitions(
    -DNRF52840_XXAA
)
target_compile_definitions(NRFX_LIB PRIVATE 
    NRF52840_XXAA
    NRFX_UARTE_ENABLED=1
    NRFX_UARTE0_ENABLED=1
    NRFX_CLOCK_ENABLED=1
    NRFX_POWER_ENABLED=1
)

add_library(boardImpl
    ${BOARD_DIR}/Board.cpp
    ${BOARD_DIR}/impl/UartImpl.cpp
    ${CMAKE_SOURCE_DIR}/vendor/nordic/nrfx/mdk/system_nrf52.c
)

target_include_directories(boardImpl PRIVATE
    ${BOARD_DIR}/include
)

target_link_libraries(boardImpl PRIVATE NRFX_LIB)


