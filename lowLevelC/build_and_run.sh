#!/bin/bash

# Set variables
CC=arm-none-eabi-gcc
CFLAGS="-mcpu=cortex-m3 -mthumb -nostdlib -nostartfiles -ffreestanding"
LDSCRIPT="cortexM3.ld"
OUTPUT="cortexM3.elf"
SOURCES="startup.c cortexM3.c"

# Compile
echo "Compiling..."
$CC $CFLAGS -T $LDSCRIPT -o $OUTPUT $SOURCES

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running in QEMU..."
    qemu-system-arm -M lm3s6965evb -nographic -kernel $OUTPUT
else
    echo "Compilation failed."
fi