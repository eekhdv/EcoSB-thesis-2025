# EcoSB
Eco Single Board computer





# How to flash STM32 board?

### First step

#### Connect board to the laptop, then:

```sh
chmod +x STM_DBG.sh
./STM_DBG.sh
```

### Second step

#### Open another terminal:
```sh
cd ./out
arm-none-eabi-gdb blink.elf
(gdb) target remote 0.0.0.0:61234
(gdb) load blink.elf
(gdb) continue
```

