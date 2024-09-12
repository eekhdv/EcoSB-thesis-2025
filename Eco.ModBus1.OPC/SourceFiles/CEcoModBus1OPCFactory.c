/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoModBus1OPCFactory
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию фабрики для компонента
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CEcoModBus1OPC.h"
#include "CEcoModBus1OPCFactory.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция возвращает указатель на интерфейс
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1OPC_C35C9FC5Factory_QueryInterface(IEcoComponentFactory* me, const UGUID* riid, void** ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoUnknown) || IsEqualUGUID(riid, &IID_IEcoComponentFactory) ) {
        *ppv = me;
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    ((IEcoUnknown*)(*ppv))->pVTbl->AddRef((IEcoUnknown*)*ppv);

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция увеличивает количество ссылок на интерфейс
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoModBus1OPC_C35C9FC5Factory_AddRef(/* in */ IEcoComponentFactory* me) {
    CEcoModBus1OPC_C35C9FC5Factory* pCMe = (CEcoModBus1OPC_C35C9FC5Factory*)me;

    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
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
 *   Функция уменьшает количество ссылок на интерфейс
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoModBus1OPC_C35C9FC5Factory_Release(/* in */ IEcoComponentFactory* me) {
    CEcoModBus1OPC_C35C9FC5Factory* pCMe = (CEcoModBus1OPC_C35C9FC5Factory*)me;

    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        //deleteCEcoModBus1OPC_C35C9FC5Factory(&pCMe->m_VtblICF);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализирует компонент с параметрами
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1OPC_C35C9FC5Factory_Init(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pIUnkSystem, /* in */ void* pv) {
    CEcoModBus1OPC_C35C9FC5Factory* pCMe = (CEcoModBus1OPC_C35C9FC5Factory*)me;
    int16_t result = ERR_ECO_POINTER;

    if (me == 0 ) {
        return result;
    }

    /* Инициализация компонента */
    result = pCMe->m_pInitInstance(pv, pIUnkSystem);

    return result;
}

/*
 *
 * <сводка>
 *   Функция Alloc
 * </сводка>
 *
 * <описание>
 *   Функция создает компонент
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1OPC_C35C9FC5Factory_Alloc(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pISystem, /* in */ struct IEcoUnknown *pIUnknownOuter, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoModBus1OPC_C35C9FC5Factory* pCMe = (CEcoModBus1OPC_C35C9FC5Factory*)me;
    IEcoUnknown* pIUnk = 0;
    int16_t result = ERR_ECO_POINTER;

    if (me == 0 ) {
        return result;
    }

    /* Агрегирование при условии если IID это IID_IEcoUnknown */
    if ( ( pIUnknownOuter != 0 ) && !IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        /* не поддерживает агрегирование */
        return ERR_ECO_NOAGGREGATION;
    }

    /* Создание компонента */
    result = pCMe->m_pInstance(pISystem, pIUnknownOuter, (void**)&pIUnk);
    if ( result != 0 || pIUnk == 0) {
        return result;
    }

    /* Инициализация компонента */
    result = me->pVTbl->Init(me, pISystem, pIUnk);
	
    /* Получение указателя на интерфейс */
    result = pIUnk->pVTbl->QueryInterface(pIUnk, riid, ppv);

    /* Уменьшение ссылки запрошенной Фабрикой компонентов */
    pIUnk->pVTbl->Release(pIUnk);

    return result;
}

/*
 *
 * <сводка>
 *   Функция get_Name
 * </сводка>
 *
 * <описание>
 *   Функция возвращает наименование компонента
 * </описание>
 *
 */
static char_t* ECOCALLMETHOD CEcoModBus1OPC_C35C9FC5Factory_get_Name(/* in */ struct IEcoComponentFactory* me) {
    CEcoModBus1OPC_C35C9FC5Factory* pCMe = (CEcoModBus1OPC_C35C9FC5Factory*)me;

    if (me == 0 ) {
        return 0; /* ERR_ECO_POINTER */
    }

    return pCMe->m_Name;
}

/*
 *
 * <сводка>
 *   Функция get_Version
 * </сводка>
 *
 * <описание>
 *   Функция возвращает версию компонента
 * </описание>
 *
 */
static char_t* ECOCALLMETHOD CEcoModBus1OPC_C35C9FC5Factory_get_Version(/* in */ struct IEcoComponentFactory* me) {
    CEcoModBus1OPC_C35C9FC5Factory* pCMe = (CEcoModBus1OPC_C35C9FC5Factory*)me;

    if (me == 0 ) {
        return 0; /* ERR_ECO_POINTER */
    }

    return pCMe->m_Version;
}

/*
 *
 * <сводка>
 *   Функция get_Manufacturer
 * </сводка>
 *
 * <описание>
 *   Функция возвращает наименование производителя компонента
 * </описание>
 *
 */
static char_t* ECOCALLMETHOD CEcoModBus1OPC_C35C9FC5Factory_get_Manufacturer(/* in */ struct IEcoComponentFactory* me) {
    CEcoModBus1OPC_C35C9FC5Factory* pCMe = (CEcoModBus1OPC_C35C9FC5Factory*)me;

    if (me == 0 ) {
        return 0; /* ERR_ECO_POINTER */
    }

    return pCMe->m_Manufacturer;
}

/* Create Virtual Table */
IEcoComponentFactoryVTbl g_xF37B74AD45824C1098981A99C35C9FC5FactoryVTbl = {
    CEcoModBus1OPC_C35C9FC5Factory_QueryInterface,
    CEcoModBus1OPC_C35C9FC5Factory_AddRef,
    CEcoModBus1OPC_C35C9FC5Factory_Release,
    CEcoModBus1OPC_C35C9FC5Factory_Alloc,
    CEcoModBus1OPC_C35C9FC5Factory_Init,
    CEcoModBus1OPC_C35C9FC5Factory_get_Name,
    CEcoModBus1OPC_C35C9FC5Factory_get_Version,
    CEcoModBus1OPC_C35C9FC5Factory_get_Manufacturer
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
CEcoModBus1OPC_C35C9FC5Factory g_xF37B74AD45824C1098981A99C35C9FC5Factory = {
    &g_xF37B74AD45824C1098981A99C35C9FC5FactoryVTbl,
    0,
    (CreateInstance)createCEcoModBus1OPC_C35C9FC5,
    (InitInstance)initCEcoModBus1OPC_C35C9FC5,
    "EcoModBus1OPC\0",
    "1.0.0.0\0",
    "CompanyName\0"
};

#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr() {
    return (IEcoComponentFactory*)&g_xF37B74AD45824C1098981A99C35C9FC5Factory;
};
#elif ECO_LIB
IEcoComponentFactory* GetIEcoComponentFactoryPtr_F37B74AD45824C1098981A99C35C9FC5 = (IEcoComponentFactory*)&g_xF37B74AD45824C1098981A99C35C9FC5Factory;
#endif