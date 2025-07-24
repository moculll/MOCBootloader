set(BOARD_DIR ${CMAKE_SOURCE_DIR}/boards/${BOARD})
if(EXISTS ${BOARD_DIR}/CMakeLists.txt)
  message(STATUS "Using board: ${BOARD}")
  add_subdirectory(${BOARD_DIR})
else()
  message(FATAL_ERROR "Board directory '${BOARD_DIR}' does not exist or has no CMakeLists.txt")
endif()


macro(add_executable TARGET_NAME)
    _add_executable(${TARGET_NAME}.elf ${ARGN} ${SYSCALL_FILE} ${STARTUP_FILE})
    target_link_libraries(Uart PRIVATE boardImpl)
    target_link_libraries(${TARGET_NAME}.elf PUBLIC Uart)
endmacro()
