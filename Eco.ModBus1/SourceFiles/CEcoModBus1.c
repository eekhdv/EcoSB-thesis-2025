/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoModBus1_A10E8757
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoModBus1_A10E8757
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "ErrEcoCodes.h"
#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoModBus1.h"


/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoModBus1
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1_A10E8757_QueryInterface(/* in */ IEcoModBus1Ptr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoModBus1_A10E8757* pCMe = (CEcoModBus1_A10E8757*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoModBus1) ) {
        *ppv = &pCMe->m_pVTblIEcoModBus1;
        pCMe->m_pVTblIEcoModBus1->AddRef((IEcoModBus1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoModBus1;
        pCMe->m_pVTblIEcoModBus1->AddRef((IEcoModBus1*)pCMe);
    }
    else {
        *ppv = 0;
        return ERR_ECO_NOINTERFACE;
    }
    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoModBus1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoModBus1_A10E8757_AddRef(/* in */ IEcoModBus1Ptr_t me) {
    CEcoModBus1_A10E8757* pCMe = (CEcoModBus1_A10E8757*)me;

    /* Проверка указателя */
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
 *   Функция Release для интерфейса IEcoModBus1
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoModBus1_A10E8757_Release(/* in */ IEcoModBus1Ptr_t me) {
    CEcoModBus1_A10E8757* pCMe = (CEcoModBus1_A10E8757*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoModBus1_A10E8757((IEcoModBus1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция EncodePDU
 * </сводка>
 *
 * <описание>
 *   Функция упаковки (кодирования) PDU
 * </описание>
 *
 */
static int16_t CEcoModBus1_A10E8757_EncodePDU(/* in */  IEcoModBus1Ptr_t me,
                                              /* in */  uint8_t functionCode,
                                              /* in */  uint16_t subCode,
                                              /* in */  byte_t* Data,
                                              /* in */  uint32_t dataLength,
                                              /* out */ byte_t** PDU,
                                              /* out */ uint32_t* pduLength)
{
    CEcoModBus1_A10E8757* pCMe = (CEcoModBus1_A10E8757*)me;

    /* Проверка указателей */
    if (me == 0 || Data == 0 || PDU == 0 || pduLength == 0) {
        return ERR_ECO_POINTER;
    }
    uint32_t length = sizeof(functionCode) + dataLength;

    switch (functionCode) {
        case ECO_MB_FC_DIAGNOSTIC:
        case ECO_MB_FC_READ_DEVICE_IDENTIFICATION:
        //case ECO_MB_FC_ENCAPSULATED_INTERFACE_TRANSPORT:
        //case ECO_MB_FC_CANOPEN_GENERAL_REFERENCE:
            length += sizeof(subCode);
            break;
        default:
          if (subCode > 0)
            return ERR_ECO_UNEXPECTED;
          break;
    }
    
    /* Result PDU length */
    *pduLength = length;

    /* Fill PDU */
    byte_t* LocalPDU = (byte_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, length);

    LocalPDU[0] = functionCode;

    if (subCode > 0)
        *(uint16_t*)(LocalPDU + ECO_MB_FUNCTION_CODE_LENGTH) = subCode;

    pCMe->m_pIMem->pVTbl->Copy(pCMe->m_pIMem, LocalPDU + ECO_MB_FUNCTION_CODE_LENGTH + (subCode > 0 ? ECO_MB_SUBCODE_LENGTH : 0), Data, dataLength);

    *PDU = LocalPDU;

    return ERR_ECO_SUCCESES;
}


/*
 *
 * <сводка>
 *   Функция DecodePDU
 * </сводка>
 *
 * <описание>
 *   Функция декодирования PDU
 * </описание>
 *
 */
static int16_t CEcoModBus1_A10E8757_DecodePDU(/* in */  IEcoModBus1Ptr_t me,
                                              /* in */  byte_t* PDU,
                                              /* in */  uint32_t pduLength,
                                              /* out */ uint8_t* functionCode,
                                              /* out */ uint16_t* subCode,
                                              /* out */ byte_t** Data,
                                              /* out */ uint32_t* dataLength)
{
    union ResultCode res;
    CEcoModBus1_A10E8757* pCMe = (CEcoModBus1_A10E8757*)me;

    uint8_t N, bytes;

    /* Проверка указателей */
    if (PDU == 0 || functionCode == 0 || Data == 0 || dataLength == 0) {
        return ERR_ECO_POINTER;
    }
    
    *functionCode = PDU[0];

    switch (*functionCode) {
        case ECO_MB_FC_READ_COILS:
            *dataLength = sizeof(uint16_t) * 2;
            break;
        case ECO_MB_FC_READ_DISCRETE_INPUTS:
            *dataLength = sizeof(uint16_t) * 2;
            break;
        case ECO_MB_FC_WRITE_SINGLE_COIL:
            *dataLength = sizeof(uint16_t) * 2;
            break;
        case ECO_MB_FC_WRITE_MULTIPLE_COILS:
            /* 2 Bytes - Starting Address    
             * 2 Bytes - Quantity of Outputs 
             * 1 Byte  - Byte Count */
            N = PDU[2 + 2 + 1];
            N = (N / 8) + (N % 8 != 0); /* N = PDU[4] / 8, если остаток не равен 0 => N = N+1 */
            *dataLength = sizeof(uint16_t) * 2 + sizeof(uint8_t) + N;
            break;
        case ECO_MB_FC_READ_INPUT_REGISTER:
            *dataLength = sizeof(uint16_t) * 2;
            break;
        case ECO_MB_FC_READ_HOLDING_REGISTERS:
            *dataLength = sizeof(uint16_t) * 2;
            break;
        case ECO_MB_FC_WRITE_SINGLE_REGISTER:
            *dataLength = sizeof(uint16_t) * 2;
            break;
        case ECO_MB_FC_WRITE_MULTIPLE_REGISTERS:
            /* 2 Bytes - Starting Address     
             * 2 Bytes - Quantity of Registers
             * 1 Bytes - Byte Count */
            N = PDU[2 * 2 + 1]; /* N = PDU[4] (количество регистров) */
            *dataLength = sizeof(uint16_t) * 2 + sizeof(uint8_t) + sizeof(uint16_t) * N; /* тип регистров - uint16_t */
            break;
        case ECO_MB_FC_READ_WRITE_MULTIPLE_REGISTERS:
            /* 2 Bytes - Read Starting Address  
             * 2 Bytes - Quantity to Read       
             * 2 Bytes - Write Starting Address 
             * 2 Bytes - Quantity to Write      
             * 1 Bytes - Write Byte Count       */
            bytes = PDU[2 * 4 + 1]; /* the number of bytes to follow in the write data field. */
            *dataLength = sizeof(uint16_t) * 4 + sizeof(uint8_t) + bytes; 
            break;
        case ECO_MB_FC_MASK_WRITE_REGISTER:
            *dataLength = sizeof(uint16_t) * 3;
            break;
        case ECO_MB_FC_READ_FIFO_QUEUE:
            *dataLength = sizeof(uint16_t);
            break;
        case ECO_MB_FC_READ_FILE_RECORD:
            /* 1 Byte  - Byte Count */
            bytes = PDU[1]; /* is the total combined count of bytes in all ‘sub-responses’ */
            *dataLength = sizeof(uint8_t) + bytes; 
            break;
        case ECO_MB_FC_WRITE_FILE_RECORD:
            /* 1 Byte  - Request data length */
            bytes = PDU[1]; /*  in terms of number of bytes */
            *dataLength = sizeof(uint8_t) + bytes; 
            break;
        case ECO_MB_FC_READ_DEVICE_IDENTIFICATION:
            *dataLength = sizeof(uint8_t) * 3;
            break;
        case ECO_MB_FC_READ_EXCEPTION_STATUS: /* Serial Only */
            *dataLength = 0;
            return ERR_ECO_SUCCESES;
        case ECO_MB_FC_GET_COM_EVENT_COUNTER: /* Serial Only */
            *dataLength = 0;
            return ERR_ECO_SUCCESES;
        case ECO_MB_FC_GET_COM_EVENT_LOG:     /* Serial Only */
            *dataLength = 0;
            return ERR_ECO_SUCCESES;
        case ECO_MB_FC_REPORT_SERVER_ID:      /* Serial Only */
            *dataLength = 0;
            return ERR_ECO_SUCCESES;
        case ECO_MB_FC_DIAGNOSTIC:
            *subCode    = *(uint16_t*)(PDU + 1);
            *dataLength = 0;    /* TODO for serial */
            return ERR_ECO_SUCCESES;
        //case ECO_MB_FC_CANOPEN_GENERAL_REFERENCE:
        //    if (subCode == 0) return ECO_MB_EC_ILLEGAL_DATA_VALUE;
        //    *subCode    = *(uint16_t*)(PDU + 1);
        //    *dataLength = 0;
        //    return ERR_ECO_SUCCESES;
        //case ECO_MB_FC_ENCAPSULATED_INTERFACE_TRANSPORT:
        //    /* TODO: For special modbus interface */
        //    *dataLength = 1;
        //    break;
        default:
            res.except_rsp_pdu_t.ErrorCode     = *functionCode + 0x80;
            res.except_rsp_pdu_t.ExceptionCode = ECO_MB_EC_ILLEGAL_FUNCTION;
            return res.result;
    }
    *Data = (byte_t*)pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, *dataLength);

    pCMe->m_pIMem->pVTbl->Copy(pCMe->m_pIMem, *Data, (PDU + ECO_MB_FUNCTION_CODE_LENGTH), *dataLength);

    return ERR_ECO_SUCCESES;
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
int16_t ECOCALLMETHOD initCEcoModBus1_A10E8757(/*in*/ IEcoModBus1Ptr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoModBus1_A10E8757* pCMe = (CEcoModBus1_A10E8757*)me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = ERR_ECO_POINTER;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;



    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);
	
    return result;
}

/* Create Virtual Table IEcoModBus1 */
IEcoModBus1VTbl g_x74AB8CD0056F4D048F855D2FC8A9F3D0VTbl_A10E8757 = {
    CEcoModBus1_A10E8757_QueryInterface,
    CEcoModBus1_A10E8757_AddRef,
    CEcoModBus1_A10E8757_Release,
    CEcoModBus1_A10E8757_EncodePDU,
    CEcoModBus1_A10E8757_DecodePDU
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
int16_t ECOCALLMETHOD createCEcoModBus1_A10E8757(/* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter, /* out */ IEcoModBus1Ptr_t* ppIEcoModBus1) {
    int16_t result = ERR_ECO_POINTER;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoModBus1_A10E8757* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
	
    /* Проверка указателей */
    if (ppIEcoModBus1 == 0 || pIUnkSystem == 0) {
        return result; /* ERR_ECO_POINTER */
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **)&pISys);
    /* Проверка */
    if (result != 0 || pISys == 0) {
        return ERR_ECO_NOSYSTEM;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    /* Проверка */
    if (result != 0 || pIBus == 0) {
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_NOBUS;
    }
	
	/* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение в случае ошибки */
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_GET_MEMORY_ALLOCATOR;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoModBus1_A10E8757*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoModBus1_A10E8757));
    if (pCMe == 0) {
        /* Освобождение в случае ошибки */
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        return ERR_ECO_OUTOFMEMORY;
    }
	
    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoModBus1 */
    pCMe->m_pVTblIEcoModBus1 = &g_x74AB8CD0056F4D048F855D2FC8A9F3D0VTbl_A10E8757;

    /* Возврат указателя на интерфейс */
    *ppIEcoModBus1 = (IEcoModBus1*)pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return ERR_ECO_SUCCESES;
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
void ECOCALLMETHOD deleteCEcoModBus1_A10E8757(/* in */ IEcoModBus1Ptr_t pIEcoModBus1) {
    CEcoModBus1_A10E8757* pCMe = (CEcoModBus1_A10E8757*)pIEcoModBus1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoModBus1 != 0 ) {
        pIMem = pCMe->m_pIMem;
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
