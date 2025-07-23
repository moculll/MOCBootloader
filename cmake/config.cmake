macro(add_executable TARGET_NAME)
    _add_executable(${TARGET_NAME}.elf ${ARGN} ${STARTUP_FILE})
endmacro()
