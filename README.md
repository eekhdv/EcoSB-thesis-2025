# EcoSB
Eco Single Board computer


# How to flash STM32 board?

### First step

#### Connect board to the laptop (using ST-LINK), then:

```sh
cd Eco.SBv1.STM32FW/AssemblyFiles/EcoOS/arm_gcc_13_2_1/
openocd -f board.cfg
```

### Second step

#### Open another terminal:
```sh
$ cd Eco.SBv1.STM32FW/BuildFiles/EcoOS/arm-v7m/StaticDebug
$ gdb EcoSBv1STM32FW.elf
(gdb) target extended-remote 0.0.0.0:61234
(gdb) load
(gdb) continue
```

# How to flash LicheeRV board?

You can find instruction here:
[Build img Arch Linux D1 RISC-V](https://github.com/eekhdv/d1-riscv-arch-image-builder)
