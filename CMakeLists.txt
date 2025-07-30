
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

include_directories(${CMAKE_SOURCE_DIR}/include)


set(additional_cmake_files)
list(APPEND additional_cmake_files
  cmake/config.cmake
)
foreach(cmake_file ${additional_cmake_files})
  include(${cmake_file})
endforeach()

include(${BOARD_DIR}/board.cmake)

add_subdirectory(coroutine)

#add_subdirectory(boards)
add_subdirectory(driver)


add_subdirectory(application)

