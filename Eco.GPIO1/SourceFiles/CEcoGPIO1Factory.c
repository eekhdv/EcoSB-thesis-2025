/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoGPIO1Factory
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

#include "IEcoGPIO1.h"
#include "CEcoGPIO1Factory.h"
#include "CEcoGPIO1.h"

bool_t ECOCALLMETHOD IsEqualUGUID_A70A4C2E9C9645BD91367754D01F101F(/* in */ const UGUID* rguid1, /* in */ const UGUID* rguid2) {
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

#define IsEqualUGUID(rguid1, rguid2) IsEqualUGUID_A70A4C2E9C9645BD91367754D01F101F(rguid1, rguid2)

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
int16_t ECOCALLMETHOD CEcoGPIO1Factory_QueryInterface(IEcoComponentFactory* me, const UGUID* riid, void** ppv) {
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
uint32_t ECOCALLMETHOD CEcoGPIO1Factory_AddRef(/* in */ IEcoComponentFactory* me) {
     CEcoGPIO1Factory* pCMe = (CEcoGPIO1Factory*)me;

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
uint32_t ECOCALLMETHOD CEcoGPIO1Factory_Release(/* in */ IEcoComponentFactory* me) {
    CEcoGPIO1Factory* pCMe = (CEcoGPIO1Factory*)me;

    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        //deleteCEcoGPIO1Factory(&pCMe->m_VtblICF);
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
int16_t ECOCALLMETHOD CEcoGPIO1Factory_Init(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pIUnkSystem, /* in */ void* pv) {
    CEcoGPIO1Factory* pCMe = (CEcoGPIO1Factory*)me;
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
int16_t ECOCALLMETHOD CEcoGPIO1Factory_Alloc(/* in */ struct IEcoComponentFactory* me, /* in */ struct IEcoUnknown *pISystem, /* in */ struct IEcoUnknown *pIUnknownOuter, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoGPIO1Factory* pCMe = (CEcoGPIO1Factory*)me;
    int16_t result = -1;
    IEcoUnknown* pIUnk = 0;

    if (me == 0 ) {
        return -1;
    }

    /* Агрегирование при условии если IID это IID_IEcoUnknown */
    if ( ( pIUnknownOuter != 0 ) && !IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        /* E_NOAGGREGATION */
        return -1;
    }

    /* Создание компонента */
    result = pCMe->m_pInstance(pISystem, pIUnknownOuter, (void**)&pIUnk);
    if ( result != 0 || pIUnk == 0) {
        return -1;
    }

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
char_t* ECOCALLMETHOD CEcoGPIO1Factory_get_Name(/* in */ struct IEcoComponentFactory* me) {
    CEcoGPIO1Factory* pCMe = (CEcoGPIO1Factory*)me;

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
char_t* ECOCALLMETHOD CEcoGPIO1Factory_get_Version(/* in */ struct IEcoComponentFactory* me) {
    CEcoGPIO1Factory* pCMe = (CEcoGPIO1Factory*)me;

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
char_t* ECOCALLMETHOD CEcoGPIO1Factory_get_Manufacturer(/* in */ struct IEcoComponentFactory* me) {
    CEcoGPIO1Factory* pCMe = (CEcoGPIO1Factory*)me;

    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_Manufacturer;
}

/* Create Virtual Table */
IEcoComponentFactoryVTbl g_xA70A4C2E9C9645BD91367754D01F101FFactoryVTbl = {
    CEcoGPIO1Factory_QueryInterface,
    CEcoGPIO1Factory_AddRef,
    CEcoGPIO1Factory_Release,
    CEcoGPIO1Factory_Alloc,
    CEcoGPIO1Factory_Init,
    CEcoGPIO1Factory_get_Name,
    CEcoGPIO1Factory_get_Version,
    CEcoGPIO1Factory_get_Manufacturer
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
CEcoGPIO1Factory g_xA70A4C2E9C9645BD91367754D01F101FFactory = {
    &g_xA70A4C2E9C9645BD91367754D01F101FFactoryVTbl,
    0,
    (CreateInstance)createCEcoGPIO1,
    (InitInstance)initCEcoGPIO1,
    "Eco.GPIO\0",
    "1.0.0.0\0",
    "PeerF\0"
};

#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr() {
    return (IEcoComponentFactory*)&g_xA70A4C2E9C9645BD91367754D01F101FFactory;
};
#elif ECO_LIB
IEcoComponentFactory* GetIEcoComponentFactoryPtr_A70A4C2E9C9645BD91367754D01F101F = (IEcoComponentFactory*)&g_xA70A4C2E9C9645BD91367754D01F101FFactory;
#endif
