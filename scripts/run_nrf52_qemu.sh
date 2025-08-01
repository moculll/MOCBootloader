#!/bin/env bash

TARGET=cppTest
QEMU_NRF52=/home/mocul/work/bootloader/qemu_nrf52/qemu-nrf52/build/qemu-system-arm
GDB_SYM=
if [ ! -z "$1" ]; then
  TARGET=$1
fi

if [ "$1" == "gdb" ]; then
  GDB_SYM="-s -S"
  TARGET=cppTest
fi
qemu-system-arm -M mps2-an386 -cpu cortex-m4 -nographic -semihosting -kernel ${PWD}/build/application/${TARGET}/${TARGET}.elf ${GDB_SYM}
#/home/mocul/work/bootloader/qemu_nrf52/qemu-nrf52/build/qemu-system-arm -M nrf52832DK -nographic -kernel build/application/cppTest/cppTest.elf

# /home/mocul/work/bootloader/qemu_nrf52/qemu-nrf52/build/qemu-system-arm -M nrf52832DK -nographic -kernel /home/mocul/nordic/nrf_sdk/mt_projects/minimal/build/merged.hex