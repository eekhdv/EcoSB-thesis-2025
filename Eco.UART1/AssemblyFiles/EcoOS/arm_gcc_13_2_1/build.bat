call make clean -f Makefile TARGET=0 DEBUG=0
call make -f Makefile TARGET=0 DEBUG=0
call make clean -f Makefile TARGET=0 DEBUG=1
call make -f Makefile TARGET=0 DEBUG=1
call make clean -f Makefile TARGET=1 DEBUG=0
call make -f Makefile TARGET=1 DEBUG=0
call make clean -f Makefile TARGET=1 DEBUG=1
call make -f Makefile TARGET=1 DEBUG=1

xcopy /y ..\..\..\BuildFiles\EcoOS\arm-v7m\StaticRelease\libB40E129B56624BD7B5F8339C025F3EF0.a %ECO_FRAMEWORK%\Eco.UART1\BuildFiles\EcoOS\arm-v7m\StaticRelease\
xcopy /y ..\..\..\BuildFiles\EcoOS\arm-v7m\DynamicRelease\B40E129B56624BD7B5F8339C025F3EF0.so %ECO_FRAMEWORK%\Eco.UART1\BuildFiles\EcoOS\arm-v7m\DynamicRelease\

pause