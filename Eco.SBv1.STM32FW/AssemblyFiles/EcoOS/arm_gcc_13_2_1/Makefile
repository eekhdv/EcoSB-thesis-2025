
ifeq ($(OS), Windows_NT)
	#WINDOWS USE THESE DEFINITIONS
	RM = -rm -f
	SLASH = \\
	SWALLOW_OUTPUT = >nul 2>nul
	TOOLCHAIN = $(ECO_TOOLCHAIN)
	TOOL = arm-none-eabi-
	GNU = $(TOOLCHAIN)/xpack-arm-none-eabi-gcc-13.2.1-1.1/bin/
	ECO = $(TOOLCHAIN)/eco_tools_1_0_0/
else
	#LINUX USE THESE DEFINITIONS
	RM = -rm -f
	SLASH = /
	SWALLOW_OUTPUT =
	TOOLCHAIN = $(ECO_TOOLCHAIN)
	TOOL = arm-none-eabi-
	GNU = $(TOOLCHAIN)/xpack-arm-none-eabi-gcc-13.2.1-1.1/bin/
	ECO = $(TOOLCHAIN)/eco_tools_1_0_0/
endif 

# configuration
PLATFORM_TARGET=EcoOS
ARCH_TARGET=arm-v7m
DEVICE_TARGET=

ifeq ($(TARGET), 1)
OUT_TARGET = EcoOS
ifeq ($(DEBUG), 1)
CONFIG_TARGET = StaticDebug
CCFLAGS_TARGET = -Wall -g -DECO_LIB
LDFLAGS_TARGET =
else
CONFIG_TARGET = StaticRelease
CCFLAGS_TARGET = -O3 -DECO_LIB
LDFLAGS_TARGET =
endif
else
# Configuration not supported...
endif

# source files.
SRC = \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)EcoFirmware1.c \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)arm$(SLASH)startup.c
# ASM source files.
#SRCS = \
#..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)arm$(SLASH)startup.S

# linker file
LINKERFILE = ..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)arm$(SLASH)linker.ld

# include directories
INC = \
-I ..$(SLASH)..$(SLASH)..$(SLASH)HeaderFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.Core1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.InterfaceBus1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.MemoryManager1$(SLASH)SharedFiles \
-I $(ECO_FRAMEWORK)$(SLASH)Eco.FileSystemManagement1$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.GPIO1$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.UART1$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.ModBus1$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.ModBus1.SL$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.TaskScheduler1$(SLASH)SharedFiles


# libraries directories
LIB_DIR = \
-L ..$(SLASH)..$(SLASH)..$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)$(ARCH_TARGET)$(SLASH)$(CONFIG_TARGET) \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.InterfaceBus1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)$(ARCH_TARGET)$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.FileSystemManagement1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)$(ARCH_TARGET)$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.MemoryManager1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)$(ARCH_TARGET)$(SLASH)StaticRelease \
-L $(ECO_FRAMEWORK)$(SLASH)Eco.System1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)$(ARCH_TARGET)$(SLASH)StaticRelease \
-L ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.GPIO1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)$(ARCH_TARGET)$(SLASH)$(CONFIG_TARGET) \
-L ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.UART1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)$(ARCH_TARGET)$(SLASH)$(CONFIG_TARGET) \
-L ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.ModBus1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)$(ARCH_TARGET)$(SLASH)$(CONFIG_TARGET) \
-L ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.ModBus1.SL$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)$(ARCH_TARGET)$(SLASH)$(CONFIG_TARGET) \
-L ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.TaskScheduler1$(SLASH)BuildFiles$(SLASH)EcoOS$(SLASH)$(ARCH_TARGET)$(SLASH)$(CONFIG_TARGET)


OBJ = $(SRC:.c=.o)
OBJS = $(SRCS:.S=.o)

OUT_ELF = EcoSBv1STM32FW.elf
OUT_BIN = EcoSBv1STM32FW.bin
OUT_HEX = EcoSBv1STM32FW.hex
OUT_MAP = EcoSBv1STM32FW.map
OUT_DIR = ..$(SLASH)..$(SLASH)..$(SLASH)BuildFiles$(SLASH)$(PLATFORM_TARGET)$(SLASH)$(ARCH_TARGET)$(SLASH)$(DEVICE_TARGET)$(SLASH)$(CONFIG_TARGET)

# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = -g -Wall -Wno-missing-braces -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -nostdlib -nostartfiles -fno-builtin -DECO_LIB -DECO_OS -DECO_AARCH32 -DUGUID_UTILITY -nostdlib -nostartfiles

# compiler
CC = $(TOOL)gcc
AR = $(TOOL)gcc-ar
OC = $(TOOL)objcopy
LD = $(TOOL)ld
EL = $(ECO)ecol1

# library paths
LIBS = $(LIB_DIR) -l00000000000000000000000042757331 -l0000000000000000000000004D656D31 -lA70A4C2E9C9645BD91367754D01F101F -lB40E129B56624BD7B5F8339C025F3EF0 -lD3D7232DDB6940469D2B535BA10E8757 -lDA26D759A46F405F9977CB5AA9153876


# compile flags
LDFLAGS = -nostdlib $(LIBS) 
.SUFFIXES: .c

.c.o:
	$(GNU)$(CC) $(INC) $(CCFLAGS) -c $< -o $@ 

.S.o:
	$(GNU)$(CC) $(INC) -D__ASSEMBLY__  $(CCFLAGS)  -o $@ $< -c 


$(OUT_ELF): $(OBJ) $(OBJS)
	mkdir -p $(OUT_DIR)
	$(GNU)$(LD) ${LDFLAGS} -T$(LINKERFILE) -o $(OUT_DIR)\$(OUT_ELF) $(OBJ) $(OBJS) -Map $(OUT_MAP) ${LDFLAGS}
	$(GNU)$(OC) --output-format=binary $(OUT_DIR)\$(OUT_ELF) $(OUT_DIR)\$(OUT_BIN)
	rm $(OBJ) $(OBJS)

clean:
	rm $(OBJ) $(OBJS) $(OUT_DIR)/$(OUT)