# EcoSB: Eco Single Board Computer

## Flashing the STM32 Board

This section guides you through the process of flashing the firmware onto the STM32 board.

### Prerequisites:

* ST-LINK debugger/programmer.
* openOCD, gdb

### Steps:

1.  **Navigate to the Assembly Files Directory and Start OpenOCD:**

    Open a terminal window and execute the following commands:

    ```sh
    cd Eco.SBv1.STM32FW/AssemblyFiles/EcoOS/arm_gcc_13_2_1/
    openocd -f board.cfg
    ```

    *This command starts the OpenOCD server, which facilitates communication with the STM32 board.*

2.  **Load Firmware using GDB:**

    Open a **new** terminal window and execute the following commands:

    ```sh
    cd Eco.SBv1.STM32FW/BuildFiles/EcoOS/arm-v7m/StaticDebug
    gdb EcoSBv1STM32FW.elf
    ```

    Once GDB has started, enter the following commands into the GDB prompt:

    ```gdb
    target extended-remote localhost:<PORT from OpenOCD>
    load
    continue
    ```

    * `target extended-remote 0.0.0.0:61234`: Connects GDB to the OpenOCD server.
    * `load`: Loads the firmware file (`EcoSBv1STM32FW.elf`) onto the STM32 board's flash memory.
    * `continue`: Starts the execution of the loaded firmware on the board.

## Flashing the LicheeRV Board

For instructions on how to flash the LicheeRV board, please refer to the dedicated repository:

**[Build Arch Linux Image for D1 RISC-V](https://github.com/eekhdv/d1-riscv-arch-image-builder)**
