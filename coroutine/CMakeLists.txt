
set(COROUTINE_COMPILE_DEFS "")

if(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "aarch64")

    file(GLOB_RECURSE ARCH_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/aarch64.S
    )
    list(APPEND COROUTINE_COMPILE_DEFS "__AARCH64=1")
elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "arm")

    file(GLOB_RECURSE ARCH_FILE
        ${CMAKE_CURRENT_SOURCE_DIR}/arch/arm.S
    )
    list(APPEND COROUTINE_COMPILE_DEFS "__ARM=1")
    
endif()

add_library(MOCoroutine STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/MOCoroutine.cpp
    ${ARCH_FILE}
)
# other places needs to use this
target_compile_definitions(MOCoroutine INTERFACE ${COROUTINE_COMPILE_DEFS})
target_compile_definitions(MOCoroutine PRIVATE ${COROUTINE_COMPILE_DEFS})
target_include_directories(MOCoroutine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})