ifeq ($(OS), Windows_NT)
	# WINDOWS USE THESE DEFINITIONS
	PLATFORM_SOURCE = Windows
	ARCH_SOURCE = x86_64
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		ARCH_SOURCE = x86_64
	endif
	CUR_DIR = $(shell pwd)
	RM = -rm -f
	MKDIR = mkdir -p
	SLASH = \\
	SWALLOW_OUTPUT = >nul 2>nul
else
	# LINUX & MACOS USE THESE DEFINITIONS
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		PLATFORM_SOURCE = Linux
	endif
	ifeq ($(UNAME_S),Darwin)
		PLATFORM_SOURCE = MacOSX
	endif
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		ARCH_SOURCE = x86_64
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		ARCH_SOURCE = x86_64
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		ARCH_SOURCE = ARM64
	endif
	RM = -rm -f
	MKDIR = mkdir -p
	SLASH = /
	SWALLOW_OUTPUT =
	TOOLCHAIN = 
	TOOL = 
endif 

# configuration


PLATFORM_TARGET=ECO_OS
OUT_PLATFORM= EcoOS

ifeq ($(TARGET), 1)
OUT_TARGET = libB40E129B56624BD7B5F8339C025F3EF0.a
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
OUT_TARGET = B40E129B56624BD7B5F8339C025F3EF0.so
ifeq ($(DEBUG), 1)
CONFIG_TARGET = DynamicDebug
CCFLAGS_TARGET = -Wall -fPIC -g -DECO_DLL
LDFLAGS_TARGET = -nostartfiles
else
CONFIG_TARGET = DynamicRelease
CCFLAGS_TARGET = -O3 -fPIC -DECO_DLL
LDFLAGS_TARGET = -nostartfiles
endif
endif

ifeq ($(ARCHITECTURE), ECO_AARCH32)
GNU_TOOLCHAIN =  $(ECO_TOOLCHAIN)/$(PLATFORM_SOURCE)_$(ARCH_SOURCE)_aarch32/bin/arm-none-eabi-
endif
ifeq ($(ARCHITECTURE), ECO_AARCH64)
GNU_TOOLCHAIN =  $(ECO_TOOLCHAIN)/$(PLATFORM_SOURCE)_$(ARCH_SOURCE)_aarch64/bin/aarch64-none-elf-
endif
ifeq ($(ARCHITECTURE), ECO_RISCV32)
GNU_TOOLCHAIN =  $(ECO_TOOLCHAIN)/$(PLATFORM_SOURCE)_$(ARCH_SOURCE)_riscv/bin/riscv-none-elf-
endif
ifeq ($(ARCHITECTURE), ECO_RISCV64)
GNU_TOOLCHAIN =  $(ECO_TOOLCHAIN)/$(PLATFORM_SOURCE)_$(ARCH_SOURCE)_riscv/bin/riscv-none-elf-
ARCH_TARGET=rv64gc
ABI_TARGET=lp64
DEVICE_TARGET=ECO_DEVICE_$(DEVICE)
CCFLAGS_ARCH = -march=$(ARCH_TARGET) -mabi=$(ABI_TARGET)
endif
ifeq ($(ARCHITECTURE), ECO_AVR8)
GNU_TOOLCHAIN =  $(ECO_TOOLCHAIN)/$(PLATFORM_SOURCE)_$(ARCH_SOURCE)_avr/bin/avr-
DEVICE_TARGET=ECO_DEVICE_$(DEVICE)
CCFLAGS_ARCH = -mmcu=atmega328p
endif

# include directories
INC = \
-I ..$(SLASH)..$(SLASH)..$(SLASH)HeaderFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.DateTime1$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.GPIO1$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.Core1$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.InterfaceBus1$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.MemoryManager1$(SLASH)SharedFiles

# source files
SRC = \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)CEcoUART1.c \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)CEcoUART1Device.c \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)CEcoUART1Factory.c

OBJ = $(SRC:.c=.o)

OUT = $(OUT_TARGET)
OUT_DIR = ..$(SLASH)..$(SLASH)..$(SLASH)BuildFiles$(SLASH)$(OUT_PLATFORM)$(SLASH)$(ARCH_TARGET)$(SLASH)$(DEVICE)$(SLASH)$(CONFIG_TARGET)


# C compiler flags
CCFLAGS = $(CCFLAGS_TARGET) $(CCFLAGS_ARCH) -Wall -Werror -Wstrict-prototypes -Wno-format-security -Wno-format-nonliteral -fno-delete-null-pointer-checks  -fno-common -ffunction-sections -fno-builtin -ffreestanding  -D$(PLATFORM_TARGET) -D$(ARCHITECTURE) -D$(DEVICE_TARGET)
 
# compiler
ECO = $(ECO_TOOLCHAIN)/eco_tools_1_0_0/

CC = $(GNU_TOOLCHAIN)gcc
AR = $(GNU_TOOLCHAIN)ar
EL = $(ECO_TOOLCHAIN)ecol1

ifeq ($(TARGET), 1)
CMD_TARGET=$(GNU)$(AR) rcs
#CMD_TARGET=$(EL)
else
CMD_TARGET=$(GNU)$(CC) -o
endif

# library paths
LIBS = 
 
# compile flags
LDFLAGS = $(LDFLAGS_TARGET)
 
.SUFFIXES: .c

all: $(OUT)

.c.o:
	$(CC) $(INC) $(CCFLAGS) -c $< -o $@
 
$(OUT): $(OBJ)
	if [ ! -d $(OUT_DIR) ] ; \
	then $(MKDIR) $(OUT_DIR) ; \
	fi
	$(CMD_TARGET) $(OUT_DIR)$(SLASH)$(OUT) $(OBJ) $(LDFLAGS)
#	$(RM) $(OBJ)

clean:
	$(RM) $(OBJ) $(OUT_DIR)$(SLASH)$(OUT)