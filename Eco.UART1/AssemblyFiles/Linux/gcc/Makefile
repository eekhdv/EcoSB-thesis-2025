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

CC = gcc
AR = gcc-ar

CMD_TARGET=$(AR) rcs

# source files.
SRC = \
../../../SourceFiles/CEcoUART1.c \
../../../SourceFiles/CEcoUART1Device.c \
../../../SourceFiles/CEcoUART1Factory.c

OBJ = $(SRC:.c=.o)

OUT = libB40E129B56624BD7B5F8339C025F3EF0.a
OUT_DIR = ../../../BuildFiles/Linux/x64

# include directories
INCLUDES = \
-I ../../../HeaderFiles/\
-I ../../../SharedFiles/\
-I $(ECO_FRAMEWORK)/Eco.GPIO1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.Core1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.InterfaceBus1/SharedFiles \
-I $(ECO_FRAMEWORK)/Eco.MemoryManager1/SharedFiles
 
# C++ compiler flags (-g -O3 -Wall)
CCFLAGS = -O3 -Wall -DECO_LIB -DECO_LIB -DECO_LINUX -DUGUID_UTILITY

# library paths
LIBS = -lc -lm 
 
# compile flags
LDFLAGS =
 
.SUFFIXES: .c

all: $(OUT)

.c.o:
	$(CC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

$(OUT): $(OBJ) $(OBJ_COMPLEX)
	mkdir -p $(OUT_DIR)
	$(CMD_TARGET) $(OUT_DIR)/$(OUT) $(OBJ) $(LDFLAGS)

clean:
	rm $(OBJ) $(OUT_DIR)/$(OUT)
