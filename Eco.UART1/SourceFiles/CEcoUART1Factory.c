/*
 * <кодировка символов>
 *   Cyrillic (Windows) - Codepage 1251
 * </кодировка символов>
 *
 * <сводка>
 *   CEco.UART1Factory
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

#include "CEcoUART1.h"
#include "CEcoUART1Factory.h"

bool_t ECOCALLMETHOD IsEqualUGUIDB40E129B56624BD7B5F8339C025F3EF0(/* in */ const UGUID* rguid1, /* in */ const UGUID* rguid2) {
    bool_t bResult = 0;
    uint8_t index = 0;
    for (index = 0; index < 18; index++) {
        if ( ((uchar_t*) rguid1)[index] == ((uchar_t*) rguid2)[index] ) {
            bResult = 1;
        }
        else {
            bResult = 0;
            break;
        }
    }
    return bResult;
};

#define IsEqualUGUID(rguid1, rguid2) IsEqualUGUIDB40E129B56624BD7B5F8339C025F3EF0(rguid1, rguid2)

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
int16_t ECOCALLMETHOD CEcoUART1Factory_025F3EF0_QueryInterface(IEcoComponentFactory* me, const UGUID* riid, void** ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoUnknown) || IsEqualUGUID(riid, &IID_IEcoComponentFactory) ) {
        *ppv = me;
    }
    else {
        *ppv = 0;
        return -1;
    }
    ((IEcoUnknown*)(*ppv))->pVTbl->AddRef((IEcoUnknown*)*ppv);

    return 0;
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
uint32_t ECOCALLMETHOD CEcoUART1Factory_025F3EF0_AddRef(/* in */ IEcoComponentFactory* me) {
    CEcoUART1Factory_025F3EF0* pCMe = (CEcoUART1Factory_025F3EF0*)me;

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
 *   Функция уменьшает количество ссылок на интерфейс
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoUART1Factory_025F3EF0_Release(/* in */ IEcoComponentFactory* me) {
    CEcoUART1Factory_025F3EF0* pCMe = (CEcoUART1Factory_025F3EF0*)me;

    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        //deleteCEcoUART1Factory(&pCMe->m_VtblICF);
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
int16_t ECOCALLMETHOD CEcoUART1Factory_025F3EF0_Init(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pIUnkSystem, /* in */ void* pv) {
    CEcoUART1Factory_025F3EF0* pCMe = (CEcoUART1Factory_025F3EF0*)me;
    int16_t result = -1;

    if (me == 0 ) {
        return -1;
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
int16_t ECOCALLMETHOD CEcoUART1Factory_025F3EF0_Alloc(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pISystem, /* in */ struct IEcoUnknown *pIUnknownOuter, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoUART1Factory_025F3EF0* pCMe = (CEcoUART1Factory_025F3EF0*)me;
    IEcoUnknown* pIUnk = 0;
    int16_t result = -1;

    if (me == 0 ) {
        return -1;
    }

    /* Агрегирование при условии если IID это IID_IEcoUnknown */
    if ( ( pIUnknownOuter != 0 ) && !IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        /* не поддерживает агрегирование */
        return -1;
    }

    /* Создание компонента */
    result = pCMe->m_pInstance(pISystem, pIUnknownOuter, (void**)&pIUnk);
    if ( result != 0 || pIUnk == 0) {
        return -1;
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
char_t* ECOCALLMETHOD CEcoUART1Factory_025F3EF0_get_Name(/* in */ struct IEcoComponentFactory* me) {
    CEcoUART1Factory_025F3EF0* pCMe = (CEcoUART1Factory_025F3EF0*)me;

    if (me == 0 ) {
        return 0;
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
char_t* ECOCALLMETHOD CEcoUART1Factory_025F3EF0_get_Version(/* in */ struct IEcoComponentFactory* me) {
    CEcoUART1Factory_025F3EF0* pCMe = (CEcoUART1Factory_025F3EF0*)me;

    if (me == 0 ) {
        return 0;
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
char_t* ECOCALLMETHOD CEcoUART1Factory_025F3EF0_get_Manufacturer(/* in */ struct IEcoComponentFactory* me) {
    CEcoUART1Factory_025F3EF0* pCMe = (CEcoUART1Factory_025F3EF0*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Manufacturer;
}


/* Create Virtual Table */
IEcoComponentFactoryVTbl g_xB40E129B56624BD7B5F8339C025F3EF0FactoryVTbl = {
    CEcoUART1Factory_025F3EF0_QueryInterface,
    CEcoUART1Factory_025F3EF0_AddRef,
    CEcoUART1Factory_025F3EF0_Release,
    CEcoUART1Factory_025F3EF0_Alloc,
    CEcoUART1Factory_025F3EF0_Init,
    CEcoUART1Factory_025F3EF0_get_Name,
    CEcoUART1Factory_025F3EF0_get_Version,
    CEcoUART1Factory_025F3EF0_get_Manufacturer
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
CEcoUART1Factory_025F3EF0 g_xB40E129B56624BD7B5F8339C025F3EF0Factory = {
    &g_xB40E129B56624BD7B5F8339C025F3EF0FactoryVTbl,
    0,
    (CreateInstance)createCEcoUART1_025F3EF0,
    (InitInstance)initCEcoUART1_025F3EF0,
    "EcoUART1\0",
    "1.0.0.0\0",
    "CompanyName\0"
};

#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr(void) {
    return (IEcoComponentFactory*)&g_xB40E129B56624BD7B5F8339C025F3EF0Factory;
};
#elif ECO_LIB
IEcoComponentFactory* GetIEcoComponentFactoryPtr_B40E129B56624BD7B5F8339C025F3EF0 = (IEcoComponentFactory*)&g_xB40E129B56624BD7B5F8339C025F3EF0Factory;
#endif