set(BOARD_DIR ${CMAKE_SOURCE_DIR}/boards/${BOARD})
if(EXISTS ${BOARD_DIR}/CMakeLists.txt)
  message(STATUS "Using board: ${BOARD}")
  add_subdirectory(${BOARD_DIR})
else()
  message(FATAL_ERROR "Board directory '${BOARD_DIR}' does not exist or has no CMakeLists.txt")
endif()


macro(add_executable TARGET_NAME)
    _add_executable(${TARGET_NAME}.elf ${ARGN} ${SYSCALL_FILE} ${STARTUP_FILE})
    target_link_libraries(${TARGET_NAME}.elf PUBLIC Uart boardImpl)
    add_custom_command(TARGET ${TARGET_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET_NAME}.elf ${TARGET_NAME}.bin
        COMMENT "Generating ${TARGET_NAME}.bin"
    )

    # 生成 .hex 文件
    add_custom_command(TARGET ${TARGET_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${TARGET_NAME}.elf ${TARGET_NAME}.hex
        COMMENT "Generating ${TARGET_NAME}.hex"
    )
endmacro()
