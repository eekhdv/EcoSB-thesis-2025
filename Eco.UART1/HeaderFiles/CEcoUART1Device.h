/*
 * <кодировка символов>
 *   Cyrillic (Windows) - Codepage 1251
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoUART1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoUART1Device
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_UART_1_DEVICE_H__
#define __C_ECO_UART_1_DEVICE_H__

#include "IEcoUART1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#ifdef ECO_WIN32
#include "IEcoUART1WIN32Config.h"
#elif ECO_AVR8
#include "IEcoUART1AVR8Config.h"
#elif ECO_BCM283X
#include "IEcoUART1BCM283xConfig.h"
#include "IEcoGPIO1BCM283xConfig.h"
#elif ECO_RISCV64
#ifdef ECO_DEVICE_D1
#include "IEcoUART1RISCV64D1Config.h"
#include "IEcoGPIO1RISCV64D1Config.h"
//#include "IEcoCCU1RISCV64D1Config.h"
#include "IEcoCCU1RISCV64D1Config.h"
#endif
#elif ECO_LINUX
#include "IEcoUART1LinuxConfig.h"
#elif ECO_STM32
#include "IEcoUART1STM32F4Config.h"
#include "IEcoGPIO1STM32Config.h"
#define ECO_GPIO_CONFIG_DESCRIPTOR GPIO_CONFIG_DESCRIPTOR
#endif

typedef struct CEcoUART1Device_025F3EF0 {

    /* Таблица функций интерфейса IEcoUART1Device */
    IEcoUART1DeviceVTbl* m_pVTblIDevice;

    /* Таблица функций интерфейса IEcoUART1Config */
#ifdef ECO_WIN32
    IEcoUART1WIN32ConfigVTbl* m_pVTblIUARTConfig;
#elif ECO_AVR8
    IEcoUART1AVR8ConfigVTbl* m_pVTblIUARTConfig;
#elif ECO_BCM283X
    IEcoUART1BCM283xConfigVTbl* m_pVTblIUARTConfig;
    IEcoGPIO1BCM283xConfigVTbl* m_pVTblIGPIOConfig;
#elif ECO_RISCV64
    IEcoUART1RISCV64D1ConfigVTbl* m_pVTblIUARTConfig;
    IEcoGPIO1RISCV64D1ConfigVTbl* m_pVTblIGPIOConfig;
    IEcoCCU1RISCV64D1ConfigVTbl* m_pVTblICCUConfig;
#elif ECO_LINUX
    IEcoUART1LinuxConfigVTbl* m_pVTblIUARTConfig;
#elif ECO_STM32
    IEcoUART1STM32F4ConfigVTbl* m_pVTblIUARTConfig;
    IEcoGPIO1STM32ConfigVTbl* m_pVTblIGPIOConfig;
#endif

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    ECO_UART_CONFIG_DESCRIPTOR* m_UARTConfig;

#ifdef ECO_WIN32
    void* m_Device;
#elif ECO_BCM283X
    ECO_GPIO_CONFIG_DESCRIPTOR* m_GPIOConfig;
#elif ECO_RISCV64
    ECO_GPIO_CONFIG_DESCRIPTOR* m_GPIOConfig;
    ECO_CCU_CONFIG_DESCRIPTOR* m_CCUConfig;
#elif ECO_LINUX
    int16_t m_Fd;
=======
#elif ECO_STM32
    ECO_GPIO_CONFIG_DESCRIPTOR* m_GPIOConfig;
#endif

} CEcoUART1Device_025F3EF0, *CEcoUART1Device_025F3EF0Ptr;

/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoUART1Device_025F3EF0(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoUART1Device** ppIDevice);
/* Удаление */
void ECOCALLMETHOD deleteCEcoUART1Device_025F3EF0(/* in */ IEcoUART1Device* pIDevice);

#endif /* __C_ECO_UART_1_DEVICE_H__ */
