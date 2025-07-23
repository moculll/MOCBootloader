set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(TOOLCHAIN_PREFIX /home/mocul/toolchain/gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf/bin/aarch64-none-elf)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_STRIP ${TOOLCHAIN_PREFIX}-strip)
set(CMAKE_LINKER ${TOOLCHAIN_PREFIX}-ld)

set(CMAKE_C_FLAGS "-O2 -ffreestanding -nostdlib -nostartfiles -Wall -lnosys")
set(CMAKE_CXX_FLAGS "-O2 -lnosys -ffreestanding -nostdlib -nostartfiles -fno-exceptions -fno-rtti -Wall ")
set(LINK_FLAGS "-Map=output.map --gc-sections -nostdlib -T${CMAKE_SOURCE_DIR}/arch/aarch64/link.ld")
set(CMAKE_C_LINK_EXECUTABLE
    "${CMAKE_LINKER} ${LINK_FLAGS} <OBJECTS> -o <TARGET>"
)

set(CMAKE_CXX_LINK_EXECUTABLE
    "${CMAKE_LINKER} ${LINK_FLAGS} <OBJECTS> -o <TARGET>"
)

file(GLOB_RECURSE STARTUP_FILE
    ${CMAKE_SOURCE_DIR}/arch/aarch64/startup.S
)

