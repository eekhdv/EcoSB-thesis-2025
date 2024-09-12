/*
 * <кодировка символов>
 *   Cyrillic (Windows) - Codepage 1251
 * </кодировка символов>
 *
 * <сводка>
 *   EcoUART1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoUART1.h"

#ifdef ECO_WIN32
#include "IEcoUART1WIN32Config.h"
#include "EcoUART1Dialog.h"

#elif ECO_AVR8
#include "IEcoUART1AVR8Config.h"

/* Определение базового адреса USART регистров для ATMega xx */
#define ECO_USART0   0x00C0UL
#define ECO_USART1   0x00C8UL
#define ECO_USART2   0x00D0UL
#define ECO_USART3   0x0130UL
/* Clock Speed */
#define ECO_FOSC 1843200

#elif ECO_BCM283X
#include "IEcoUART1BCM283xConfig.h"
/* Определение базового адреса UART для BCM2837 (Rasp Pi 3B) */
#define ECO_UART     0x3F201000UL
/* Clock Speed */
#define ECO_FUARTCLK 3000000

#include "IEcoGPIO1BCM283xConfig.h"

/* Определение базового адреса GPIO для BCM2837 (Rasp Pi 3B) */
#define ECO_GPIO     0x3F200000UL

#define ECO_GPIO_BANK_0      ((uint8_t)0x00)
#define ECO_GPIO_BANK_1      ((uint8_t)0x01)


#include "IEcoIPCCMailbox1.h"
#include "IEcoIPCCMailbox1BCM283x.h"
#include "IdEcoIPCCMailbox1.h"

extern uint32_t RPi_IO_Base_Addr; 
/* ARM bus address to GPU bus address */
extern uint32_t ARMaddrToGPUaddr (void* ARMaddress);

/* GPU bus address to ARM bus address */
extern uint32_t GPUaddrToARMaddr (uint32_t GPUaddress);

/*--------------------------------------------------------------------------}
{  RASPBERRY PI SYSTEM TIMER HARDWARE REGISTERS - BCM2835 Manual Section 12	}
{--------------------------------------------------------------------------*/
struct __attribute__((__packed__, aligned(4))) SystemTimerRegisters {
	uint32_t ControlStatus;											// 0x00
	uint32_t TimerLo;												// 0x04
	uint32_t TimerHi;												// 0x08
	uint32_t Compare0;												// 0x0C
	uint32_t Compare1;												// 0x10
	uint32_t Compare2;												// 0x14
	uint32_t Compare3;												// 0x18
};

#define SYSTEMTIMER ((volatile __attribute__((aligned(4))) struct SystemTimerRegisters*)(uintptr_t)(RPi_IO_Base_Addr + 0x3000))

uint64_t timer_getTickCount64 (void)
{
	uint64_t resVal;
	uint32_t lowCount;
	do {
		resVal = SYSTEMTIMER->TimerHi; 								// Read Arm system timer high count
		lowCount = SYSTEMTIMER->TimerLo;							// Read Arm system timer low count
	} while (resVal != (uint64_t)SYSTEMTIMER->TimerHi);				// Check hi counter hasn't rolled in that time
	resVal = (uint64_t)resVal << 32 | lowCount;						// Join the 32 bit values to a full 64 bit
	return(resVal);													// Return the uint64_t timer tick count
}


static const unsigned int BitFont[] = {0x00000000u, 0x3078ccccu, 0xccfcccccu, 0xcc000000u};

int8_t WriteCharacterAtCursorPosition(/* in */ uintptr_t FrameBufferAddress, /* in */ unsigned int Pitch, /* in */ uint8_t xPos, /* in */ uint8_t yPos) {
    uint16_t* video16 = 0;
    uint16_t Fc, Bc;
    uint32_t y = 0;
    uint32_t b = 0;
    uint16_t i = 0;
    uint16_t col = 0;
    uint16_t xoffs = i;
    Fc = 0x5FEB;
    Bc = 0x0000;

    video16 = (uint16_t*)(uintptr_t)(FrameBufferAddress + (yPos * Pitch) + (xPos));

    for (y = 0; y < 4; y++) {
        b = BitFont[y];
        for (i = 0; i < 32; i++) {					// For each bit
            col = Bc;										// Preset background colour
            xoffs = i % 8;										// X offset
            if ((b & 0x80000000) != 0) col = Fc;					// If bit set take text colour
            video16[xoffs] = col;								// Write pixel
    //__asm volatile ("DSB SY");
    //__asm volatile ("ISB SY");
            b <<= 1;												// Roll font bits left
            if (xoffs == 7) video16 += Pitch;				// If was bit 7 next line down
        }
    }
   // pCMe->m_CurPos.x += 8;

    return 0;
}

#elif ECO_STM32
#include "IEcoUART1STM32Config.h"
#endif

#ifdef ECO_WIN32
int16_t EcoMain(IEcoUnknown* pIUnk) {
#else
int main(void) {
#endif
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на интерфейс для работы с интерфейсом универсального асинхронного приемопередатчика */
    IEcoUART1* pIUART = 0;
    IEcoUART1Device* pIDevice1 = 0;
    IEcoUART1Device* pIDevice2 = 0;
#ifdef ECO_WIN32
    IEcoUART1WIN32Config* pIUARTConfig = 0;
#elif ECO_AVR8
    IEcoUART1AVR8Config* pIUARTConfig = 0;
#elif ECO_BCM283X
    IEcoUART1BCM283xConfig* pIUARTConfig = 0;
    IEcoGPIO1BCM283xConfig* pIGPIOConfig = 0;
    GPIO_CONFIG_DESCRIPTOR xGPIO = {0};
#elif ECO_STM32
#endif
    /* Указатель на интерфейс для работы с интерфейсом ввода/вывода общего назначения */
    //IEcoGPIO1* pIGPIO = 0;
    /* Код результата */
    int16_t result = 0;
    /* Данные */
    byte_t data = 0;
    ECO_UART_CONFIG_DESCRIPTOR xUART = {0};
    ECO_UART_1_CONFIG xDevConfig = {0};

#ifdef ECO_WIN32
    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoUART1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_B40E129B56624BD7B5F8339C025F3EF0);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
#else


    /* Указатель на тестируемый интерфейс */
    IEcoIPCCMailbox1* pIMailbox = 0;
    uint32_t buffer[23] = {0};
    uint32_t ScreenWidth;
    uint32_t ScreenHeight;
    uint32_t ColourDepth;
    uint32_t Pitch;
    uint32_t ColourByte;
    uintptr_t FrameBufferAddress;
    uint64_t colourChangeTime = timer_getTickCount64() + 3000000ul; // 3 seconds from now
    /* Создание экземпляра интерфейсной шины */
    result = GetIEcoComponentFactoryPtr_F10BC39A4F2143CF8A1E104650A2C302->pVTbl->Alloc(GetIEcoComponentFactoryPtr_F10BC39A4F2143CF8A1E104650A2C302, 0, 0, &IID_IEcoIPCCMailbox1, (void **)&pIMailbox);
    /* Проверка */
    if (result != 0 && pIMailbox == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    if (pIMailbox->pVTbl->ProcessingByArgs(pIMailbox, MB_CHANNEL_ARM_PROPERTY_ARM, &buffer[0], 5, MB_CHANNEL_PROPERTY_ARM_GET_PHYSICAL_WIDTH_HEIGHT, 8, 0, 0, 0) != -1) {
        ScreenWidth = buffer[3];
        ScreenHeight = buffer[4];
    }

    if (pIMailbox->pVTbl->ProcessingByArgs(pIMailbox, MB_CHANNEL_ARM_PROPERTY_ARM, &buffer[0], 4, MB_CHANNEL_PROPERTY_ARM_GET_DEPTH, 4, 4, 0) != -1) {
        ColourDepth = buffer[3];
    }
    pIMailbox->pVTbl->ProcessingByArgs(pIMailbox, MB_CHANNEL_ARM_PROPERTY_ARM, &buffer[0], 23,
        MB_CHANNEL_PROPERTY_ARM_ALLOCATE_FRAMEBUFFER, 8, 4, 16, 0,
        MB_CHANNEL_PROPERTY_ARM_SET_PHYSICAL_WIDTH_HEIGHT, 8, 8, ScreenWidth, ScreenHeight,
        MB_CHANNEL_PROPERTY_ARM_SET_VIRTUAL_WIDTH_HEIGHT, 8, 8, ScreenWidth, ScreenHeight,
        MB_CHANNEL_PROPERTY_ARM_SET_DEPTH, 4, 4, ColourDepth,
        MB_CHANNEL_PROPERTY_ARM_GET_PITCH, 4, 0, 0);
    FrameBufferAddress = GPUaddrToARMaddr(buffer[3]);
    Pitch = buffer[22];
    Pitch /= 2;

   // WriteCharacterAtCursorPosition(FrameBufferAddress, Pitch, 0, 0);


    /* Создание экземпляра интерфейсной шины */
    result = GetIEcoComponentFactoryPtr_00000000000000000000000042757331->pVTbl->Alloc(GetIEcoComponentFactoryPtr_00000000000000000000000042757331, 0, 0, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    /* Проверка */
    if (result != 0 && pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
        WriteCharacterAtCursorPosition(FrameBufferAddress, Pitch, 0, 16);
    /* Регистрация компонента для работы с интерфейсом универсального асинхронного приемопередатчика (UART) */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoUART1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_B40E129B56624BD7B5F8339C025F3EF0);
    /* Проверка */
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
      //  WriteCharacterAtCursorPosition(FrameBufferAddress, Pitch, 0, 32);

#endif

    /* Получение интерфейса для работы с UART */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoUART1, 0, &IID_IEcoUART1, (void**) &pIUART);
    if (result != 0 || pIUART == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
       // WriteCharacterAtCursorPosition(FrameBufferAddress, Pitch, 0, 48);
    /* Создание UART устройства с аппаратной реализацией */
    result = pIUART->pVTbl->new_Device(pIUART, &pIDevice1);
#ifdef ECO_WIN32
    /* Запрос интерфейса UART конфигурации */
    result = pIDevice1->pVTbl->QueryInterface(pIDevice1, &IID_IEcoUART1WIN32Config, (void**) &pIUARTConfig);
    if (result != 0 || pIUARTConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Установка наименования устройства и сохранение ссылки на конфигурацию UART */
    xUART.lpszName = "COM1";
    result = pIUARTConfig->pVTbl->set_ConfigDescriptor(pIUARTConfig, &xUART);
    pIUARTConfig->pVTbl->Release(pIUARTConfig);
#elif ECO_AVR8
    /* Запрос интерфейса UART конфигурации */
    result = pIDevice1->pVTbl->QueryInterface(pIDevice1, &IID_IEcoUART1AVR8Config, (void**) &pIUARTConfig);
    if (result != 0 && pIUARTConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Установка базового адреса и сохранение ссылки на конфигурацию USART регистров */
    xUART.Register.BaseAddress = ECO_USART0; // 0x00С0UL;
    xUART.Fosc = ECO_FOSC;
    result = pIUARTConfig->pVTbl->set_ConfigDescriptor(pIUARTConfig, &xUART);
    pIUARTConfig->pVTbl->Release(pIUARTConfig);
#elif ECO_BCM283X
    /* Запрос интерфейса UART конфигурации */
    result = pIDevice1->pVTbl->QueryInterface(pIDevice1, &IID_IEcoUART1BCM283xConfig, (void**) &pIUARTConfig);
    if (result != 0 && pIUARTConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
     //   WriteCharacterAtCursorPosition(FrameBufferAddress, Pitch, 0, 64);
    /* Установка базового адреса и сохранение ссылки на конфигурацию UART регистров */
    xUART.Register.BaseAddress = ECO_UART;  // 0x3F201000UL
    xUART.Fclk = ECO_FUARTCLK;
    result = pIUARTConfig->pVTbl->set_ConfigDescriptor(pIUARTConfig, &xUART);

    /* Запрос интерфейса GPIO конфигурации */
    pIDevice1->pVTbl->QueryInterface(pIDevice1, &IID_IEcoGPIO1BCM283xConfig, (void**) &pIGPIOConfig);
    if (result != 0 && pIGPIOConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Установка базового адреса и сохранение ссылки на конфигурацию */
    xGPIO.Register.BaseAddress = ECO_GPIO; //0x3F200000UL;
    result = pIGPIOConfig->pVTbl->set_ConfigDescriptor(pIGPIOConfig, &xGPIO);

    pIGPIOConfig->pVTbl->Release(pIGPIOConfig);
    pIUARTConfig->pVTbl->Release(pIUARTConfig);
#elif ECO_STM32
#endif

#ifdef ECO_WIN32
    /* Клиент */
    DialogProcessing(pIDevice1);
Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIDevice1 != 0) {
        pIDevice1->pVTbl->Release(pIDevice1);
    }

    if (pIUART != 0) {
        pIUART->pVTbl->Release(pIUART);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;

#else /* Эхо-сервер */
    /* Подключение */
            //WriteCharacterAtCursorPosition(FrameBufferAddress, Pitch, 32, 48);
    pIDevice1->pVTbl->Connect(pIDevice1, 0);
            WriteCharacterAtCursorPosition(FrameBufferAddress, Pitch, 0, 0);
    /* Передача сообщения */
    pIDevice1->pVTbl->Transmit(pIDevice1, 'H' );
            //pIDevice1->pVTbl->Receive(pIDevice1, &data );
            WriteCharacterAtCursorPosition(FrameBufferAddress, Pitch, 64, 48);
    //pIDevice1->pVTbl->Transmit(pIDevice1, 'e' );
    //pIDevice1->pVTbl->Transmit(pIDevice1, 'l' );
    //pIDevice1->pVTbl->Transmit(pIDevice1, 'l' );
    //pIDevice1->pVTbl->Transmit(pIDevice1, 'o' );
    //pIDevice1->pVTbl->Transmit(pIDevice1, '!' );
    //pIDevice1->pVTbl->Transmit(pIDevice1, '\n' );
    /* Цикл приема-передачи (эхо) */
    for(;;)
    {
        pIDevice1->pVTbl->Receive(pIDevice1, &data );
        pIDevice1->pVTbl->Transmit(pIDevice1, data );
    }

    /* Завершение в случае ошибки */
Release:
    while (1) {
        asm volatile ("NOP\n\t" ::: "memory");
    }
#endif

}
