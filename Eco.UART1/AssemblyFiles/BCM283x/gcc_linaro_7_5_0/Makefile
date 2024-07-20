ifeq ($(OS), Windows_NT)
	#WINDOWS USE THESE DEFINITIONS
	RM = -del /q /f
	MKDIR = mkdir
	SLASH = \\
	SWALLOW_OUTPUT = >nul 2>nul
else
	#LINUX USE THESE DEFINITIONS
	RM = -rm -f
	MKDIR = mkdir
	SLASH = /
	SWALLOW_OUTPUT =
endif 

# source files.
SRC = \
..\..\..\SourceFiles\CEcoUART1.c \
..\..\..\SourceFiles\CEcoUART1Device.c \
..\..\..\SourceFiles\CEcoUART1Factory.c

OBJ = $(SRC:.c=.o)

OUT = libB40E129B56624BD7B5F8339C025F3EF0.a
OUT_DIR = ..\..\..\BuildFiles\BCM283x

# include directories
INCLUDES = \
-I ..\..\..\HeaderFiles \
-I ..\..\..\SharedFiles \
-I ..\..\..\..\Eco.GPIO1\SharedFiles \
-I ..\..\..\..\Eco.Core1\SharedFiles \
-I ..\..\..\..\Eco.InterfaceBus1\SharedFiles \
-I ..\..\..\..\Eco.MemoryManager1\SharedFiles
 
# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = -Wall -Wno-missing-braces -march=armv8-a+simd -mtune=cortex-a53 -mstrict-align -fno-tree-loop-vectorize -fno-tree-slp-vectorize -DECO_LIB -DECO_BCM283X -DUGUID_UTILITY
 
# compiler
ARMGNU  = $(ECO_TOOLCHAIN)/gcc-linaro-7.5.0/bin/
CCC = $(ARMGNU)aarch64-elf-gcc
 
# library paths
LIBS = -lc -lm -lgcc
 
# compile flags
LDFLAGS = -g
 
.SUFFIXES: .c

all: $(OUT)

.c.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@
 
$(OUT): $(OBJ)
	if not exist $(OUT_DIR) $(MKDIR) $(OUT_DIR)
	$(ARMGNU)aarch64-elf-ar rcs $(OUT_DIR)\$(OUT) $(OBJ)
	$(RM) $(OBJ)

clean:
	$(RM) $(OBJ) $(OUT_DIR)\$(OUT)