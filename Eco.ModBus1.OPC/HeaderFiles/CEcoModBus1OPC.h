/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoModBus1OPC
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию компонента CEcoModBus1OPC
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOMODBUS1OPC_H__
#define __C_ECOMODBUS1OPC_H__

#include "IEcoModBus1OPC.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoModBus1OPC_C35C9FC5 {

    /* Таблица функций интерфейса IEcoModBus1OPC */
    IEcoModBus1OPCVTbl* m_pVTblIEcoModBus1OPC;


    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    char_t* m_Name;

} CEcoModBus1OPC_C35C9FC5, *CEcoModBus1OPC_C35C9FC5Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoModBus1OPC_C35C9FC5(/*in*/ IEcoModBus1OPCPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoModBus1OPC_C35C9FC5(/* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter, /* out */ IEcoModBus1OPCPtr_t* ppIEcoModBus1OPC);
/* Удаление */
void ECOCALLMETHOD deleteCEcoModBus1OPC_C35C9FC5(/* in */ IEcoModBus1OPCPtr_t pIEcoModBus1OPC);

#endif /* __C_ECOMODBUS1OPC_H__ */
