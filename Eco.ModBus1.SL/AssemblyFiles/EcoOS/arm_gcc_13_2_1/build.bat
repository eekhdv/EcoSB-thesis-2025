call make clean -f Makefile TARGET=0 DEBUG=0
call make -f Makefile TARGET=0 DEBUG=0
call make clean -f Makefile TARGET=0 DEBUG=1
call make -f Makefile TARGET=0 DEBUG=1
call make clean -f Makefile TARGET=1 DEBUG=0
call make -f Makefile TARGET=1 DEBUG=0
call make clean -f Makefile TARGET=1 DEBUG=1
call make -f Makefile TARGET=1 DEBUG=1

xcopy /y ..\..\..\BuildFiles\EcoOS\arm-v7m\StaticRelease\libDA26D759A46F405F9977CB5AA9153876.a %ECO_FRAMEWORK%\Eco.ModBus1.SL\BuildFiles\EcoOS\arm-v7m\StaticRelease\
xcopy /y ..\..\..\BuildFiles\EcoOS\arm-v7m\DynamicRelease\DA26D759A46F405F9977CB5AA9153876.so %ECO_FRAMEWORK%\Eco.ModBus1.SL\BuildFiles\EcoOS\arm-v7m\DynamicRelease\

pause