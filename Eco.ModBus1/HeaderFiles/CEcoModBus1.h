/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoModBus1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoModBus1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOMODBUS1_H__
#define __C_ECOMODBUS1_H__

#include "IEcoModBus1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoModBus1_A10E8757 {

    /* Таблица функций интерфейса IEcoModBus1 */
    IEcoModBus1VTbl* m_pVTblIEcoModBus1;


    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

} CEcoModBus1_A10E8757, *CEcoModBus1_A10E8757Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoModBus1_A10E8757(/*in*/ IEcoModBus1Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoModBus1_A10E8757(/* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter, /* out */ IEcoModBus1Ptr_t* ppIEcoModBus1);
/* Удаление */
void ECOCALLMETHOD deleteCEcoModBus1_A10E8757(/* in */ IEcoModBus1Ptr_t pIEcoModBus1);

#endif /* __C_ECOMODBUS1_H__ */
