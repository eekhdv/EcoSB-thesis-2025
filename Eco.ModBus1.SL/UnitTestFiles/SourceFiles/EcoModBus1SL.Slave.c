/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoModBus1SL
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
#include "ErrEcoCodes.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoModBus1.h"
#include "IdEcoUART1.h"

#include "IdEcoModBus1SL.h"
#include "IEcoModBus1SLRTU.h"
#include "IEcoModBus1SLASCII.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на интерфейс работы с ModBus */
    IEcoModBus1* pIEcoModBus1 = 0;
    /* Указатели на тестируемые интерфейсы */
    IEcoModBus1SLRTU*   pIEcoModBus1SLRTU = 0;
    IEcoModBus1SLASCII* pIEcoModBus1SLASCII = 0;
    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы с ModBus */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoModBus1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_D3D7232DDB6940469D2B535BA10E8757);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы c ModBus Serial Line */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoModBus1SL, (IEcoUnknown*)GetIEcoComponentFactoryPtr_DA26D759A46F405F9977CB5AA9153876);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoUART1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_B40E129B56624BD7B5F8339C025F3EF0);
    /* Проверка */
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    printf("Quering modbus...\n");
    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoModBus1, 0, &IID_IEcoModBus1, (void**) &pIEcoModBus1);
    if (result != 0 || pIEcoModBus1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        printf("Error quering modbus component");
        goto Release;
    }

    printf("Quering RTU...\n");
    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoModBus1SL, 0, &IID_IEcoModBus1SLRTU, (void**) &pIEcoModBus1SLRTU);
    if (result != 0 || pIEcoModBus1SLRTU == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        printf("Error quering RTU interface");
        goto Release;
    }

#ifdef ASCII_NOT_IMPLEMENTED_YET
    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoModBus1SL, 0, &IID_IEcoModBus1SLASCII, (void**) &pIEcoModBus1SLASCII);
    if (result != 0 || pIEcoModBus1SLASCII == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
#endif

    /* Подключение к шине */
    printf("Connecting to the bus...\n");
    result = pIEcoModBus1SLRTU->pVTbl->ConnectBus(pIEcoModBus1SLRTU, 1);
    if (result != ERR_ECO_SUCCESES) {
        /* Освобождение интерфейсов в случае ошибки */
        printf("Error connection to the BUS");
        goto Release;
    }

    /* Проверка отправки/получения сообщений */
    uint8_t functionCode = ECO_MB_FC_WRITE_FILE_RECORD;
    uint16_t subCode = 0;

    byte_t sendData_[] = " Hello from slave!";
    byte_t sendData[sizeof(sendData_) - 1] = { 0 };
    uint32_t dataLength = sizeof(sendData);
    memcpy(sendData, sendData_, dataLength);
    sendData[0] = (uint8_t)(dataLength - 1);

    result = pIEcoModBus1SLRTU->pVTbl->EmitMessage(pIEcoModBus1SLRTU, functionCode, subCode, sendData, dataLength);
    if (result != ERR_ECO_SUCCESES) {
        /* Освобождение интерфейсов в случае ошибки */
        printf("Error while emmiting");
        goto Release;
    }

    sleep(1);
    printf("Receiving message...\n");
    byte_t* recvData = 0;
    result = pIEcoModBus1SLRTU->pVTbl->RecvMessage(pIEcoModBus1SLRTU, &functionCode, &subCode, &recvData, &dataLength);
    if (result != ERR_ECO_SUCCESES) {
        printf("Error while receiving");
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    printf("Received succ: (%d bytes)\n", dataLength);
    for (uint32_t i = 0; i < dataLength; i++)
        printf("%c", recvData[i]);
    putc('\n', stdout);

    /* Очистить выделенную память при получении сообщения */
    pIMem->pVTbl->Free(pIMem, recvData);

    /* Отключение от шины */
    result = pIEcoModBus1SLRTU->pVTbl->DisconnectBus(pIEcoModBus1SLRTU);
    if (result != ERR_ECO_SUCCESES) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

#ifdef ASCII_NOT_IMPLEMENTED_YET
    result = pIEcoModBus1SLASCII->pVTbl->EmitMessage();
#endif

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoModBus1 != 0) {
        pIEcoModBus1->pVTbl->Release(pIEcoModBus1);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoModBus1SLRTU != 0) {
        pIEcoModBus1SLRTU->pVTbl->Release(pIEcoModBus1SLRTU);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoModBus1SLASCII != 0) {
        pIEcoModBus1SLASCII->pVTbl->Release(pIEcoModBus1SLASCII);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

