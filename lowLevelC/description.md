# Bare-Metal ARM Cortex-M3 Programming Project

This project demonstrates basic bare-metal programming for ARM Cortex-M3 microcontrollers, using QEMU for emulation.

## Key Components
- `cortexM3.c`: Main program file
- `startup.c`: Startup code and vector table
- `cortexM3.ld`: Linker script
- `build_and_run.sh`: Bash script to compile and run the program

## Features
- Implements a simple UART print function
- Sets up the vector table for interrupt handling
- Uses QEMU to emulate an LM3S6965 microcontroller
- Demonstrates bare-metal programming without an operating system

## Build and Run
Use the `build_and_run.sh` script to compile the code and run it in QEMU.