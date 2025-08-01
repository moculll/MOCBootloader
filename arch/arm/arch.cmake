set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(TOOLCHAIN_PREFIX ${CMAKE_SOURCE_DIR}/../toolchain/arm/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_STRIP ${TOOLCHAIN_PREFIX}-strip)
set(CMAKE_LINKER ${TOOLCHAIN_PREFIX}-ld)

set(CMAKE_C_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffreestanding -fno-strict-aliasing -Wall")
set(CMAKE_CXX_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffreestanding -fno-exceptions -fno-rtti -Wall")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffreestanding -fno-strict-aliasing -Wall")
set(CMAKE_EXE_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/arch/arm/link.ld -Wl,--gc-sections -Wl,-Map=${CMAKE_BINARY_DIR}/output.map")
file(GLOB_RECURSE STARTUP_FILE
    ${CMAKE_SOURCE_DIR}/arch/arm/startup.S
    ${CMAKE_SOURCE_DIR}/arch/arm/syscalls.cpp
)
