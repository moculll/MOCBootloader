#!/bin/env bash

BUILD_DIR=build
BOARD=qemu_aarch64

if [ ! -z "$1" ]; then
  BOARD=$1
fi

cmake -S . -B build -G Ninja -DBOARD=$BOARD -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build

