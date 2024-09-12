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
 *   Данный заголовок описывает реализацию компонента CEcoUART1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECO_UART_1_H__
#define __C_ECO_UART_1_H__

#include "IEcoUART1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoUART1_025F3EF0 {

    /* Таблица функций интерфейса IEcoUART1 */
    IEcoUART1VTbl* m_pVTblIUART;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    char_t* m_Name;

} CEcoUART1_025F3EF0, *CEcoUART1_025F3EF0Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoUART1_025F3EF0(/*in*/ struct IEcoUART1* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoUART1_025F3EF0(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoUART1** ppIUART);
/* Удаление */
void ECOCALLMETHOD deleteCEcoUART1_025F3EF0(/* in */ IEcoUART1* pIUART);

#endif /* __C_ECO_UART_1_H__ */
