# MOCBootloader

## Description
```
most of the embedded systems' bootloader uses bare metal
but with the development of technology, the ram and flash is no longer precious in chips
so now we're developing a Bootloader with coroutine and c++17
```
## Usage

```
prepare aarch64 toolchain and put it
${CMAKE_SOURCE_DIR}/../toolchain/aarch64/gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf/

apt-get install -y qemu-system-aarch64

chmod +x scripts/build.sh

./scripts/build.sh

./scripts/run_application.sh

and you should see the output of console
```

