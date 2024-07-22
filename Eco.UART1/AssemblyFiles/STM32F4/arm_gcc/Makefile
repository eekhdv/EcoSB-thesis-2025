ifeq ($(OS), Windows_NT)
	#WINDOWS USE THESE DEFINITIONS
	RM = -del /q /f
	MKDIR = mkdir
	SLASH = \\
	SWALLOW_OUTPUT = >nul 2>nul
else
	#LINUX USE THESE DEFINITIONS
	RM = -rm -f
	MKDIR = mkdir -p
	SLASH = /
	SWALLOW_OUTPUT =
endif 

#OUT = $(OUT_DIR)/blink.elf
CCC = arm-none-eabi-gcc
AR  = arm-none-eabi-ar

# source files.
SRC = \
../../../SourceFiles/CEcoUART1.c \
../../../SourceFiles/CEcoUART1Device.c \
../../../SourceFiles/CEcoUART1Factory.c

OBJ = $(SRC:.c=.o)

OUT = libB40E129B56624BD7B5F8339C025F3EF0.a
OUT_DIR = ../../../BuildFiles/STM32F4

# include directories
INCLUDES = \
-I ../../../HeaderFiles/\
-I ../../../SharedFiles/\
-I $(ECO_FRAMEWORK)/Eco.GPIO1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles
 
# C++ compiler flags (-g -O3 -Wall)
CCFLAGS = -O3 -Wall -Wno-missing-braces -mtune=cortex-m4 -DECO_LIB -DECO_STM32 -DUGUID_UTILITY

# library paths
LIBS = -lc -lm -lgcc
 
# compile flags
LDFLAGS = -g
 
.SUFFIXES: .c

all: $(OUT)

.c.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@
 
$(OUT): $(OBJ)
	$(MKDIR) $(OUT_DIR)
	$(AR) rcs $(OUT_DIR)/$(OUT) $(OBJ)
	$(RM) $(OBJ)

clean:
	$(RM) $(OBJ) $(OUT_DIR)/$(OUT)
