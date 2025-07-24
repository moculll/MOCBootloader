#!/bin/env bash

TARGET=minimalTest
GDB_SYM=
if [ ! -z "$1" ]; then
  TARGET=$1
fi

if [ "$1" == "gdb" ]; then
  GDB_SYM="-s -S"
  TARGET=minimalTest
fi

qemu-system-aarch64 -M virt -cpu cortex-a53 -nographic -kernel ${PWD}/build/application/${TARGET}/${TARGET}.elf ${GDB_SYM}