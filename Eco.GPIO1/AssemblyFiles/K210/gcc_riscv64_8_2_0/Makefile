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
../../../SourceFiles/CEcoGPIO1.c \
../../../SourceFiles/CEcoGPIO1Factory.c

OBJ = $(SRC:.c=.o)

OUT = libA70A4C2E9C9645BD91367754D01F101F.a
OUT_DIR = ../../../BuildFiles\K210

# include directories
INCLUDES = \
-I ../../../HeaderFiles \
-I ../../../SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.System1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles
 
# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = -Wall -O3 -Wno-missing-braces -mcmodel=medany -mabi=lp64f -march=rv64imafc -mstrict-align -fno-tree-loop-vectorize -fno-tree-slp-vectorize -DECO_LIB -DECO_K210 -DUGUID_UTILITY
 
# compiler
ARMGNU  = $(ECO_TOOLCHAIN)/gcc-riscv64-8.2.0/bin/
CCC = $(ARMGNU)riscv64-unknown-elf-gcc
 
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
	$(ARMGNU)riscv64-unknown-elf-ar rcs $(OUT_DIR)\$(OUT) $(OBJ)
	$(RM) $(OBJ)

clean:
	$(RM) $(OBJ) $(OUT_DIR)\$(OUT)