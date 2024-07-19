/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoGPIO1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию фабрики для компонента
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_GPIO_1_H__
#define __C_ECO_GPIO_1_H__

#include "IEcoGPIO1.h"
#ifdef ECO_AVR8
#include "IEcoGPIO1AVR8Config.h"
#elif ECO_PIC32
#include "IEcoGPIO1PIC32Config.h"
#elif ECO_STM32
#include "IEcoGPIO1STM32Config.h"
#include "IEcoRCC1STM32Config.h"
#elif ECO_BCM283X
#include "IEcoGPIO1BCM283xConfig.h"
#elif ECO_K210
#include "IEcoFPIOA1K210Config.h"
#include "IEcoGPIO1K210Config.h"
#include "IEcoSYSCTL1K210Config.h"
#endif
#include "IEcoSystem1.h"
#include "IEcoMemoryAllocator1.h"

typedef struct CEcoGPIO1 {

    /* Таблица функций интерфейса IEcoGPIO1 */
    IEcoGPIO1VTbl* m_pVTblIGPIO;

#ifdef ECO_AVR8
    /* Таблица функций интерфейса IEcoGPIO1AVR8Config */
    IEcoGPIO1AVR8ConfigVTbl* m_pVTblIGPIOConfig;
#elif ECO_STM32
    /* Таблица функций интерфейса IEcoGPIO1STM32Config */
    IEcoGPIO1STM32ConfigVTbl* m_pVTblIGPIOConfig;
    /* Таблица функций интерфейса IEcoRCC1STM32Config */
    IEcoRCC1STM32ConfigVTbl* m_pVTblIRCCConfig;
#elif ECO_BCM283X
    /* Таблица функций интерфейса IEcoGPIO1BCM283xConfig */
    IEcoGPIO1BCM283xConfigVTbl* m_pVTblIGPIOConfig;
#elif ECO_K210
    /* Таблица функций интерфейса IEcoGPIO1K210Config */
    IEcoGPIO1K210ConfigVTbl* m_pVTblIGPIOConfig;
    /* Таблица функций интерфейса IEcoFPIOA1K210Config */
    IEcoFPIOA1K210ConfigVTbl* m_pVTblIFPIOAConfig;
    /* Таблица функций интерфейса IEcoSYSCTL1K210Config */
    IEcoSYSCTL1K210ConfigVTbl* m_pVTblISYSCTLConfig;
#endif
    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

#ifdef ECO_AVR8
    uint8_t m_PortName[14];
    void* m_PortConfig[14];
#elif ECO_STM32
    void* m_RCCConfig;
    uint8_t m_PortName[14];
    void* m_PortConfig[14];
#elif ECO_BCM283X
    void* m_GPIOConfig;
#elif ECO_K210
    void* m_GPIOConfig;
    void* m_FPIOAConfig;
    void* m_SYSCTLConfig;
#endif

} CEcoGPIO1, *CEcoGPIO1Ptr;

/* Инициализация экземпляра */
int16_t initCEcoGPIO1(/*in*/ struct IEcoGPIO1* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t createCEcoGPIO1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoGPIO1** ppIGPIO);
/* Удаление */
void deleteCEcoGPIO1(/* in */ IEcoGPIO1* pIGPIO);

#endif /* __C_ECO_GPIO_1_H__ */
