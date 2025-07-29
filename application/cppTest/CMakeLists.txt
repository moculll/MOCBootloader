
add_executable(cppTest
    main.cpp
)
include_directories(${CMAKE_SOURCE_DIR}/vendor/nordic/cmsis/Include)
include_directories(${CMAKE_SOURCE_DIR}/boards/nrf52840dongle/include)
include_directories(${CMAKE_SOURCE_DIR}/coroutine)