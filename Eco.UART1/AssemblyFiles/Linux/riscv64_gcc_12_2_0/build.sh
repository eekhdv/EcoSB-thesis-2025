#!/usr/bin/env bash
echo "Build Eco.UART1"
DIR=$(cd "$(dirname "$0")"; pwd)
echo $DIR
export TARGET=0
export DEBUG=0
make clean -f Makefile
make -f Makefile
export TARGET=0
export DEBUG=1
make clean -f Makefile
make -f Makefile
export TARGET=1
export DEBUG=0
make clean -f Makefile
make -f Makefile
export TARGET=1
export DEBUG=1
make clean -f Makefile
make -f Makefile

mkdir -p $ECO_FRAMEWORK/Eco.UART1/BuildFiles/Linux/rv64gcv/StaticRelease && cp ../../../BuildFiles/Linux/rv64gcv/StaticRelease/libB40E129B56624BD7B5F8339C025F3EF0.a $ECO_FRAMEWORK/Eco.UART1/BuildFiles/Linux/rv64gcv/StaticRelease
mkdir -p $ECO_FRAMEWORK/Eco.UART1/BuildFiles/Linux/rv64gcv/DynamicRelease && cp ../../../BuildFiles/Linux/rv64gcv/DynamicRelease/B40E129B56624BD7B5F8339C025F3EF0.so $ECO_FRAMEWORK/Eco.UART1/BuildFiles/Linux/rv64gcv/DynamicRelease
