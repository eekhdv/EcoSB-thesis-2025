﻿#!/usr/bin/env bash
echo "Build Eco.ModBus1.OPC"
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