OUTPUT_ARCH(aarch64)
ENTRY(_start)
   /* Specify the memory areas */
   MEMORY
   {
         RAM (xrw)      : ORIGIN = 0x80000 , LENGTH = 0x8000000 /*128MB which is half memory on smallest memory PI, assumes GPU has other half */
    }

SECTIONS
{
	/*
	* First and formost we need the .init section, containing the code to 
        	* be run first. We allow room for the ATAGs and stack and conform to 
       	* the bootloader's expectation by putting this code at 0x8000.
	*/
	.init 0x80000 : {
		KEEP(*(.init))
	} > RAM

	/* 
	* Next we put the rest of the code.
	*/
	.text : {
		. = ALIGN(4);
		 __text_start__ = .;     	/* Label in case we want address of text section start */
		*(.text .text.*)
		 __text_end__ = .;      	/* Label in case we want address of text section end */
	} > RAM

	/* 
	* Next we put the data.
	*/
	.data : {
		. = ALIGN(4);
		 __data_start__ = .;     	/* Label in case we want address of data section start */
		*(.data .data.*)
		 __data_end__ = .;     	/* Label in case we want address of data section end */
	} > RAM

	/* 
	* Next we put the bss data .. C/C++ compilers produce this.
	*/
	.bss :
    	{
		. = ALIGN(4);
		 __bss_start__ = .;     	/* Label in case we want address of BSS section start */
		*(.bss .bss.*)
 		*(COMMON)
		 __bss_end__ = .;     	/* Label in case we want address of BSS section end */
   	} > RAM

	/* 
	* Next we put the rodata .. C/C++ compilers store preset constants here.
	*/
	.rodata :
    	{
       		. = ALIGN(4);
        		__rodata_start__ = .;	/* Label in case we want address of rodata section start */
        		*(.rodata .rodata.*)
        		__rodata_end__ = .;	/* Label in case we want address of rodata section start */
   	} > RAM


	
	.stack_core0 :
    	{
        		. = ALIGN(16);  /* Stack must always be aligned to 8 byte boundary AAPCS64 call standard */
        		__stack_start_core0__ = .;
        		. = . + 512;    /* EL0 stack size */
        		__EL0_stack_core0 = .;
        		. = . + 16384;    /* EL1 stack size */
        		__EL1_stack_core0 = .;
        		. = . + 4096;  /* EL2 stack size (start-up) */
        		__EL2_stack_core0 = .;
        		. = ALIGN(16);
        		__stack_end_core0__ = .;    
    	} > RAM

	.stack_core1 :
    	{
        		. = ALIGN(16);  /* Stack must always be aligned to 8 byte boundary AAPCS64 call standard */
        		__stack_start_core1__ = .;
        		. = . + 512;    /* EL0 stack size */
        		__EL0_stack_core1 = .;
        		. = . + 512;    /* EL1 stack size */
        		__EL1_stack_core1 = .;
        		. = . + 4096;  /* EL2 stack size (start-up) */
        		__EL2_stack_core1 = .;
        		. = ALIGN(16);
        		__stack_end_core1__ = .;    
    	} > RAM

	.stack_core2 :
    	{
        		. = ALIGN(16);  /* Stack must always be aligned to 8 byte boundary AAPCS call standard */
        		__stack_start_core2__ = .;
        		. = . + 512;    /* EL0 stack size */
        		__EL0_stack_core2 = .;
        		. = . + 512;    /* EL1 stack size */
        		__EL1_stack_core2 = .;
        		. = . + 4096;  /* EL2 stack size (start-up) */
        		__EL2_stack_core2 = .;
        		. = ALIGN(16);
        		__stack_end_core2__ = .;  
    	} > RAM

	.stack_core3 :
    	{
        		. = ALIGN(16);  /* Stack must always be aligned to 8 byte boundary AAPCS call standard */
        		__stack_start_core3__ = .;
        		. = . + 512;    /* EL0 stack size */
        		__EL0_stack_core3 = .;
        		. = . + 512;    /* EL1 stack size */
        		__EL1_stack_core3 = .;
        		. = . + 4096;  /* EL2 stack size (start-up) */
       		__EL2_stack_core3 = .;
        		. = ALIGN(16);
        		__stack_end_core3__ = .;  
    	} > RAM

	.heap :
    	{
     		. = ALIGN(4);
     		__heap_start__ = .;	/* Label in case we want address of heap section start */
                         . = . + 4096;
    		 _end = .; PROVIDE (end = .); /* Any memory from here is free to use so this is end of code and start of heap */
             . = . + 512;
   	 } > RAM

	/*
	* Finally comes everything else. A fun trick here is to put all other 
	* sections into this section, which will be discarded by default.
	*/
	/DISCARD/ : {
		*(*)
	}
}
