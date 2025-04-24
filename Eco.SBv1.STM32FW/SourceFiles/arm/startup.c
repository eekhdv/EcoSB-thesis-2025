#include <stdint.h>

#define RAM_START       0x20000000
#define RAM_SIZE        128 * 1024
#define RAM_END         ((RAM_START) + (RAM_SIZE))


extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _lddata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern void EcoStartup(void);

extern void SysTick_Handler(void);


void Default_Handler(void) {
    while(1) {}
}

void Reset_Handler(void) {
    // copy .data section from flash to ram
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *pRAM = (uint8_t*)&_sdata;
    uint8_t *pFlash = (uint8_t*)&_lddata;
    
    for(int i=0; i<size; i++) {
        pRAM[i] = pFlash[i];
    }

    // initialize .bss section
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pRAM = (uint8_t*)&_sbss;

    for(int i=0; i<size; i++) {
        pRAM[i] = 0;
    }

    // call to EcoStartup
    EcoStartup();
}


__attribute__ ((section(".isr_vector")))
uint32_t vector_table[] = {
    (uint32_t) RAM_END,
    (uint32_t) Reset_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) 0,
    (uint32_t) Default_Handler,
    (uint32_t) SysTick_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) 0,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) Default_Handler,
    (uint32_t) 0,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) Default_Handler,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) Default_Handler,
    (uint32_t) Default_Handler,
};
