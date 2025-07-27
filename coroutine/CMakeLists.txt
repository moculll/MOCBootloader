

add_library(MOCoroutine STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/MOCoroutine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/arch/aarch64.S
)

target_include_directories(MOCoroutine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})