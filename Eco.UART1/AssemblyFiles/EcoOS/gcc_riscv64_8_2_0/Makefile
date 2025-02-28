
ifeq ($(OS), Windows_NT)
	#WINDOWS USE THESE DEFINITIONS
	RM = -rm -f
	MKDIR = mkdir -p
	SLASH = \\
	SWALLOW_OUTPUT = >nul 2>nul
else
	#LINUX USE THESE DEFINITIONS
	RM = -rm -f
	MKDIR = mkdir -p
	SLASH = /
	SWALLOW_OUTPUT =
endif 

# source files
SRC = \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)CEcoUART1.c \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)CEcoUART1Device.c \
..$(SLASH)..$(SLASH)..$(SLASH)SourceFiles$(SLASH)CEcoUART1Factory.c

OBJ = $(SRC:.c=.o)

OUT = libB40E129B56624BD7B5F8339C025F3EF0.a
OUT_DIR = ..$(SLASH)..$(SLASH)..$(SLASH)BuildFiles$(SLASH)RISCV64$(SLASH)D1$(SLASH)StaticRelease

# include directories
INCLUDES = \
-I ..$(SLASH)..$(SLASH)..$(SLASH)HeaderFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.GPIO1$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.Core1$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.InterfaceBus1$(SLASH)SharedFiles \
-I ..$(SLASH)..$(SLASH)..$(SLASH)..$(SLASH)Eco.MemoryManager1$(SLASH)SharedFiles
 
# C compiler flags
CCFLAGS = -Wall -Werror -Wstrict-prototypes -Wno-format-security -Wno-format-nonliteral -fno-delete-null-pointer-checks -march=rv64gc -mabi=lp64 -fno-common -ffunction-sections -fno-builtin -ffreestanding -pipe -DECO_LIB -DECO_OS -DECO_RISCV64
 
# compiler
GNU  = $(ECO_TOOLCHAIN)$(SLASH)xpack-riscv-none-elf-gcc-13.2.0-2$(SLASH)bin$(SLASH)
CC = $(GNU)riscv-none-elf-gcc
AR = $(GNU)riscv-none-elf-ar
 
# library paths
LIBS = 
 
# compile flags
LDFLAGS = -g
 
.SUFFIXES: .c

all: $(OUT)

.c.o:
	$(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@
 
$(OUT): $(OBJ)
	if [ ! -d $(OUT_DIR) ] ; \
	then $(MKDIR) $(OUT_DIR) ; \
	fi
	$(AR) rcs $(OUT_DIR)$(SLASH)$(OUT) $(OBJ)
	$(RM) $(OBJ)

clean:
	$(RM) $(OBJ) $(OUT_DIR)$(SLASH)$(OUT)
