/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoModBus1SL
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoModBus1SL
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOMODBUS1SL_H__
#define __C_ECOMODBUS1SL_H__

#include "IEcoModBus1SL.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoModBus1SL_A9153876 {

    /* Таблица функций интерфейса IEcoModBus1SL */
    IEcoModBus1SLVTbl* m_pVTblIEcoModBus1SL;


    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    char_t* m_Name;

} CEcoModBus1SL_A9153876, *CEcoModBus1SL_A9153876Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoModBus1SL_A9153876(/*in*/ IEcoModBus1SLPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoModBus1SL_A9153876(/* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter, /* out */ IEcoModBus1SLPtr_t* ppIEcoModBus1SL);
/* Удаление */
void ECOCALLMETHOD deleteCEcoModBus1SL_A9153876(/* in */ IEcoModBus1SLPtr_t pIEcoModBus1SL);

#endif /* __C_ECOMODBUS1SL_H__ */
