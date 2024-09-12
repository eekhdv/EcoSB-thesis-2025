#!/bin/sh

STM_LINK_GDB="$HOME/st/stm32cubeide_1.11.0/plugins/com.st.stm32cube.ide.mcu.externaltools.stlink-gdb-server.linux64_2.0.400.202209281104/tools/bin/ST-LINK_gdbserver"
CUBE_DL="$HOME/st/stm32cubeide_1.11.0/plugins/com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.linux64_2.0.500.202209151145/tools/bin"

$STM_LINK_GDB -p 61234 -l 1 -d -s -cp $CUBE_DL -m 0 -k

# stm32cubeide_1.10.1/plugins/com.st.stm32cube.ide.mcu.externaltools.stlink-gdb-server.linux64_2.0.300.202203231527/tools/bin/ST-LINK_gdbserver -p 61234 -l 1 -d -s -cp stm32cubeide_1.10.1/plugins/com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.linux64_2.0.301.202207041506/tools/bin -m 0 -g
