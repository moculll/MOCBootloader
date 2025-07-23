#!/bin/env bash

TARGET=minimalTest

if [ ! -z "$1" ]; then
  TARGET=$1
fi
qemu-system-aarch64 -M virt -cpu cortex-a53 -nographic -kernel $PWD/build/application/${TARGET}/${TARGET}.elf