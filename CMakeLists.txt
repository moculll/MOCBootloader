
cmake_minimum_required (VERSION 3.22)
project(MOCBootloader LANGUAGES C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if(NOT DEFINED BOARD)
  message(FATAL_ERROR "Please specify BOARD via -DBOARD=<board_name>")
endif()

set(BOARD_DIR ${CMAKE_SOURCE_DIR}/boards/${BOARD})
if(EXISTS ${BOARD_DIR}/CMakeLists.txt)
  message(STATUS "Using board: ${BOARD}")
  add_subdirectory(${BOARD_DIR})
else()
  message(FATAL_ERROR "Board directory '${BOARD_DIR}' does not exist or has no CMakeLists.txt")
endif()


include(${BOARD_DIR}/board.cmake)
set(additional_cmake_files)
list(APPEND additional_cmake_files
    cmake/config.cmake
)

foreach(cmake_file ${additional_cmake_files})
    include(${cmake_file})
endforeach()

add_subdirectory(driver)
add_subdirectory(vendor)
add_subdirectory(boards)
add_subdirectory(application)

