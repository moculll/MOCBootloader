#!/bin/env bash

BUILD_DIR=build
BOARD=qemu_aarch64

if [ ! -z "$1" ]; then
  BOARD=$1
fi

mkdir -p $BUILD_DIR
cd $BUILD_DIR

cmake .. -DBOARD=$BOARD
make -j$(nproc)
