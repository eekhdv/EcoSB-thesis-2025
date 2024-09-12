/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoModBus1TCP
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoModBus1TCP
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOMODBUS1TCP_H__
#define __C_ECOMODBUS1TCP_H__

#include "IEcoModBus1TCP.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoModBus1TCP_E7CA43E2 {

    /* Таблица функций интерфейса IEcoModBus1TCP */
    IEcoModBus1TCPVTbl* m_pVTblIEcoModBus1TCP;


    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    char_t* m_Name;

} CEcoModBus1TCP_E7CA43E2, *CEcoModBus1TCP_E7CA43E2Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoModBus1TCP_E7CA43E2(/*in*/ IEcoModBus1TCPPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoModBus1TCP_E7CA43E2(/* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter, /* out */ IEcoModBus1TCPPtr_t* ppIEcoModBus1TCP);
/* Удаление */
void ECOCALLMETHOD deleteCEcoModBus1TCP_E7CA43E2(/* in */ IEcoModBus1TCPPtr_t pIEcoModBus1TCP);

#endif /* __C_ECOMODBUS1TCP_H__ */
