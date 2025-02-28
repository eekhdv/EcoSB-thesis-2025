call make clean -f Makefile TARGET=0 DEBUG=0
call make -f Makefile TARGET=0 DEBUG=0
call make clean -f Makefile TARGET=0 DEBUG=1
call make -f Makefile TARGET=0 DEBUG=1
call make clean -f Makefile TARGET=1 DEBUG=0
call make -f Makefile TARGET=1 DEBUG=0
call make clean -f Makefile TARGET=1 DEBUG=1
call make -f Makefile TARGET=1 DEBUG=1

xcopy /y ..\..\..\BuildFiles\EcoOS\arm-v7m\StaticRelease\libA70A4C2E9C9645BD91367754D01F101F.a %ECO_FRAMEWORK%\Eco.GPIO1\BuildFiles\EcoOS\arm-v7m\StaticRelease\
xcopy /y ..\..\..\BuildFiles\EcoOS\arm-v7m\DynamicRelease\A70A4C2E9C9645BD91367754D01F101F.so %ECO_FRAMEWORK%\Eco.GPIO1\BuildFiles\EcoOS\arm-v7m\DynamicRelease\

pause