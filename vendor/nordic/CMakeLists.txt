
file(GLOB_RECURSE NRFX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/drivers/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/soc/*.c
)

add_library(NRFX_LIB STATIC ${NRFX_SOURCES})
target_compile_options(NRFX_LIB PRIVATE 
    -Wno-int-to-pointer-cast
    -Wno-pointer-to-int-cast
    -Wno-unused-variable
)


target_include_directories(NRFX_LIB PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/drivers
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/drivers/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/drivers/src
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/drivers/src/prs
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/hal
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/soc
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/mdk
    ${CMAKE_SOURCE_DIR}/vendor/cmsis/Include
)


target_include_directories(NRFX_LIB INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/drivers
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/drivers/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/drivers/src
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/drivers/src/prs
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/hal
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/soc
    ${CMAKE_CURRENT_SOURCE_DIR}/nrfx/mdk
    ${CMAKE_SOURCE_DIR}/vendor/cmsis/Include

)