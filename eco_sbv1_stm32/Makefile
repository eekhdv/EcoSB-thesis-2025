LD_SCRIPT = ./STM32F427VITX_RAM.ld


OUT_DIR = ./out
OUT = $(OUT_DIR)/blink.elf
CCC = arm-none-eabi-gcc

SRC = \
./Core/Src/main.c \
./Core/Src/system_stm32f4xx.c \
./Core/Startup/startup_stm32f427vitx.s \
./User/Test.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_can.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_i2c.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
./Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c

INCLUDES = \
-I./Core/Inc \
-I./User \
-I./Drivers/CMSIS/Include \
-I./Drivers/STM32F4xx_HAL_Driver/Inc \
-I./Drivers/CMSIS/Device/ST/STM32F4xx/Include 


FLAGS = -Wl,-Map,kernel.map,-T $(LD_SCRIPT) -o $(OUT) -mcpu=cortex-m4 -mthumb -specs=nosys.specs -ggdb

all: $(OUT)

$(OUT): 
	mkdir -p $(OUT_DIR)
	$(CCC) $(SRC) $(FLAGS) $(INCLUDES)


clean:
	rm -rf $(OUT_DIR)
