set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(TOOLCHAIN_PREFIX ${CMAKE_SOURCE_DIR}/../toolchain/aarch64/gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf/bin/aarch64-none-elf)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_STRIP ${TOOLCHAIN_PREFIX}-strip)
set(CMAKE_LINKER ${TOOLCHAIN_PREFIX}-ld)

set(CMAKE_C_FLAGS "-ffreestanding -fno-strict-aliasing -Wall")
set(CMAKE_CXX_FLAGS "-ffreestanding -fno-exceptions -fno-rtti -Wall")
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/arch/aarch64/link.ld -Wl,--gc-sections -Wl,-Map=${CMAKE_BINARY_DIR}/output.map")
file(GLOB_RECURSE STARTUP_FILE
    ${CMAKE_SOURCE_DIR}/arch/aarch64/startup.S
    ${CMAKE_SOURCE_DIR}/arch/aarch64/syscalls.cpp
)
