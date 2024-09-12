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
 *   Данный исходный код описывает реализацию интерфейсов CEcoUART1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "CEcoUART1.h"
#include "CEcoUART1Device.h"



extern bool_t ECOCALLMETHOD IsEqualUGUIDB40E129B56624BD7B5F8339C025F3EF0(/* in */ const UGUID* rguid1, /* in */ const UGUID* rguid2);
#define IsEqualUGUID(rguid1, rguid2) IsEqualUGUIDB40E129B56624BD7B5F8339C025F3EF0(rguid1, rguid2)


/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoUART1
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoUART1_025F3EF0_QueryInterface(/* in */ struct IEcoUART1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoUART1_025F3EF0* pCMe = (CEcoUART1_025F3EF0*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoUART1) ) {
        *ppv = &pCMe->m_pVTblIUART;
        pCMe->m_pVTblIUART->AddRef((IEcoUART1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIUART;
        pCMe->m_pVTblIUART->AddRef((IEcoUART1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoUART1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoUART1_025F3EF0_AddRef(/* in */ struct IEcoUART1* me) {
    CEcoUART1_025F3EF0* pCMe = (CEcoUART1_025F3EF0*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoUART1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoUART1_025F3EF0_Release(/* in */ struct IEcoUART1* me) {
    CEcoUART1_025F3EF0* pCMe = (CEcoUART1_025F3EF0*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoUART1_025F3EF0((IEcoUART1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция new_Device
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoUART1_025F3EF0_new_Device(/* in */ struct IEcoUART1* me, /* out */ IEcoUART1Device **ppIDevice) {
    CEcoUART1_025F3EF0* pCMe = (CEcoUART1_025F3EF0*)me;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    return createCEcoUART1Device_025F3EF0((IEcoUnknownPtr_t)pCMe->m_pISys, 0, ppIDevice);
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoUART1_025F3EF0(/*in*/ struct IEcoUART1* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoUART1_025F3EF0* pCMe = (CEcoUART1_025F3EF0*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Инициализация данных */

    return 0;
}

/* Create Virtual Table */
IEcoUART1VTbl g_xB40E129B56624BD7B5F8339C025F3EF0VTbl_025F3EF0 = {
    CEcoUART1_025F3EF0_QueryInterface,
    CEcoUART1_025F3EF0_AddRef,
    CEcoUART1_025F3EF0_Release,
    CEcoUART1_025F3EF0_new_Device
};

/* Выделяем память под один экземпляр */
CEcoUART1_025F3EF0 g_xB40E129B56624BD7B5F8339C025F3EF0UART1 = {
    &g_xB40E129B56624BD7B5F8339C025F3EF0VTbl_025F3EF0,
    0,
    0,
    0,
    0
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoUART1_025F3EF0(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoUART1** ppIEcoUART1) {
    CEcoUART1_025F3EF0* pCMe = 0;
    int16_t result = -1;

    /* Проверка указателей */
    if (ppIEcoUART1 == 0) {
        return result;
    }

    /* Получение указателя на структуру компонента расположенной в области инициализированных данных */
    pCMe = &g_xB40E129B56624BD7B5F8339C025F3EF0UART1;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Возврат указателя на интерфейс */
    *ppIEcoUART1 = (IEcoUART1*)pCMe;

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoUART1_025F3EF0(/* in */ IEcoUART1* pIEcoUART1) {
    /*CEcoUART1_025F3EF0* pCMe = (CEcoUART1_025F3EF0*)pIEcoUART1*/;
}
