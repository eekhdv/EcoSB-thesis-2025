﻿call make clean -f Makefile TARGET=0 DEBUG=0
call make -f Makefile TARGET=0 DEBUG=0
call make clean -f Makefile TARGET=0 DEBUG=1
call make -f Makefile TARGET=0 DEBUG=1
call make clean -f Makefile TARGET=1 DEBUG=0
call make -f Makefile TARGET=1 DEBUG=0
call make clean -f Makefile TARGET=1 DEBUG=1
call make -f Makefile TARGET=1 DEBUG=1

xcopy /y ..\..\..\BuildFiles\EcoOS\arm-v7m\StaticRelease\libD3D7232DDB6940469D2B535BA10E8757.a %ECO_FRAMEWORK%\Eco.ModBus1\BuildFiles\EcoOS\arm-v7m\StaticRelease\
xcopy /y ..\..\..\BuildFiles\EcoOS\arm-v7m\DynamicRelease\D3D7232DDB6940469D2B535BA10E8757.so %ECO_FRAMEWORK%\Eco.ModBus1\BuildFiles\EcoOS\arm-v7m\DynamicRelease\

pause