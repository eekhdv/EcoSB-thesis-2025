/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoPowerManagement1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

/* Eco OS */
#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoSystemInformation1.h"
#include "IEcoCommandArguments1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoFileSystemManagement1.h"
/* #include "IdEcoList1.h" */

/* ModBus */
#include "IdEcoModBus1.h"
#include "IdEcoModBus1SL.h"
#include "IEcoModBus1SLRTU.h"

/* Log */
#include "IdEcoLog1.h"
#include "IEcoLog1ConsoleAffiliate.h"


/* Глобальный указатель на системный интерфейс */
IEcoSystem1* g_pISys = 0;

/* Глобальный указатель на интерфейс работы с логами */
static IEcoLog1* g_pILog = 0;

enum eEcoLog1Level LogLevel = ECO_LOG_1_LEVEL_DEBUG || ECO_LOG_1_LEVEL_ERROR;


/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoSystemInformation1* pISysInfo = 0;
    IEcoCommandArguments1* pICmdArg = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoFileManager1* pIFileMgr = 0;
    IEcoFile1* pIFile = 0;
    IEcoLog1Affiliate* pIConsoleAffiliate = 0;
    /* Указатель на интерфейс работы с ModBus */
    IEcoModBus1* pIEcoModBus1 = 0;
    /* Указатели на тестируемые интерфейсы */
    IEcoModBus1SLRTU*   pIEcoModBus1SLRTU = 0;


    /* Проверка и создание системного интрефейса */
    if (g_pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&g_pISys);
        if (result != 0 || g_pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = g_pISys->pVTbl->QueryInterface(g_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }


#ifdef ECO_LIB
    /* Регистрация статического компонента для работы с UART */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoUART1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_B40E129B56624BD7B5F8339C025F3EF0);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с ModBus1 */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoModBus1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_D3D7232DDB6940469D2B535BA10E8757);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с ModBus1 Serial Line */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoModBus1SL, (IEcoUnknown*)GetIEcoComponentFactoryPtr_DA26D759A46F405F9977CB5AA9153876);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с Логгером */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLog1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_97322B6765B74342BBCE38798A0B40B5);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

#endif


    result = g_pISys->pVTbl->QueryInterface(g_pISys, &IID_IEcoSystemInformation1, (void **)&pISysInfo);
    if (result != 0 || pISysInfo == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    result = pISysInfo->pVTbl->QueryInterface(pISysInfo, &IID_IEcoCommandArguments1, (void **)&pICmdArg);
    if (result != 0 || pICmdArg == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    pISysInfo->pVTbl->Release(pISysInfo);
    pICmdArg->pVTbl->Release(pICmdArg);

    /* Получение интерфейса работы с ModBus */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoModBus1, 0, &IID_IEcoModBus1, (void**) &pIEcoModBus1);
    if (result != 0 || pIEcoModBus1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса работы с ModBus.SL */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoModBus1SL, 0, &IID_IEcoModBus1SLRTU, (void**) &pIEcoModBus1SLRTU);
    if (result != 0 || pIEcoModBus1SLRTU == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса логгирования */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLog1, 0, &IID_IEcoLog1, (void**) &g_pILog);
    if (result != 0 || g_pILog == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение компонента вывода в консоль */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLog1, 0, &IID_IEcoLog1ConsoleAffiliate, (void**)&pIConsoleAffiliate);
    if (result != 0 || pIConsoleAffiliate == 0) {
        goto Release;
    }

    /* Подключение к шине */
    byte_t devName[] = "/dev/ttyS2";
    result = pIEcoModBus1SLRTU->pVTbl->ConnectBus(pIEcoModBus1SLRTU, 1, devName, sizeof(devName));
    if (result != ERR_ECO_SUCCESES) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    
    g_pILog->pVTbl->AddAffiliate(g_pILog, (IEcoLog1Affiliate*)pIConsoleAffiliate);
    g_pILog->pVTbl->set_LevelMask(g_pILog, LogLevel);
    g_pILog->pVTbl->DebugFormat(g_pILog, "LogLevel: %d", LogLevel);


Release:

    /* Освобождение интерфейса управления файлами */
    if (pIFileMgr != 0) {
        pIFileMgr->pVTbl->Release(pIFileMgr);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение системного интерфейса */
    if (g_pISys != 0) {
        g_pISys->pVTbl->Release(g_pISys);
    }

    return result;
}
