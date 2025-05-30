/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoModBus1SL_A9153876
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoModBus1SL_A9153876
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
#include "CEcoModBus1SL.h"
#include "IEcoModBus1SL.h"

#if ECO_LINUX
    #include "IEcoUART1LinuxConfig.h"
    #include <unistd.h>
#elif ECO_STM32
    #include "IEcoUART1STM32F4Config.h"
#endif

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoModBus1SL
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SL_A9153876_QueryInterface(/* in */ IEcoModBus1SLPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoModBus1SL) ) {
        *ppv = &pCMe->m_pVTblIEcoModBus1SL;
        pCMe->m_pVTblIEcoModBus1SL->AddRef((IEcoModBus1SL*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoModBus1SLRTU) ) {
        *ppv = &pCMe->m_pVTblIEcoModBus1SLRTU;
        pCMe->m_pVTblIEcoModBus1SL->AddRef((IEcoModBus1SL*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoModBus1SLASCII) ) {
        *ppv = &pCMe->m_pVTblIEcoModBus1SLASCII;
        pCMe->m_pVTblIEcoModBus1SL->AddRef((IEcoModBus1SL*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoModBus1SL;
        pCMe->m_pVTblIEcoModBus1SL->AddRef((IEcoModBus1SL*)pCMe);
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
 *   Функция AddRef для интерфейса IEcoModBus1SL
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoModBus1SL_A9153876_AddRef(/* in */ IEcoModBus1SLPtr_t me) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)me;

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
 *   Функция Release для интерфейса IEcoModBus1SL
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoModBus1SL_A9153876_Release(/* in */ IEcoModBus1SLPtr_t me) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoModBus1SL_A9153876((IEcoModBus1SL*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция EmitMessage
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SL_A9153876_EmitMessage(/* in */ IEcoModBus1SLPtr_t me, /* in */ byte_t* PDU, /* in */ uint32_t pduLength) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)me;
    IEcoUART1Device* pIDevice1 = pCMe->m_pIUARTDevice;

    /* Проверка указателей */
    if (me == 0 || PDU == 0 || pIDevice1 == 0) {
        return ERR_ECO_POINTER;
    }
    
    pCMe->m_pVTblIEcoModBus1SL->SwitchCommunicationLED((IEcoModBus1SL*)pCMe, 1);

    for (uint32_t i = 0; i < pduLength; i++) {
      pIDevice1->pVTbl->Transmit(pIDevice1, PDU[i]);
    }

    pCMe->m_pVTblIEcoModBus1SL->SwitchCommunicationLED((IEcoModBus1SL*)pCMe, 0);

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция RecvMessage
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SL_A9153876_RecvMessage(/* in */ IEcoModBus1SLPtr_t me, /* out */ byte_t** data, /* out */ uint32_t* dataLength) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)me;
    IEcoUART1Device* pIDevice1 = pCMe->m_pIUARTDevice;

    /* Проверка указателей */
    if (me == 0 || pIDevice1 == 0) {
        return ERR_ECO_POINTER;
    }
    *data = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, 256);
    
    pCMe->m_pVTblIEcoModBus1SL->SwitchCommunicationLED((IEcoModBus1SL*)pCMe, 1);

    uint32_t i;
    double timeout = 3.5 * 10.0 / 115200;  /* 115200 - бодрейт */
#ifdef ECO_LINUX
    struct timespec current_time;
    struct timespec last_byte_time;
    // 3.5 символа * время передачи одного символа (10 бит на символ / скорость)

    clock_gettime(CLOCK_MONOTONIC, &last_byte_time);
#endif
    /* TODO:
     * Заменить 253 на define,
     * Где 253 - это максимальное количество байт данных (максимальный размер сообщения)
    **/
    for (i = 0; i < 253;)
    {
        int16_t bytesRead = pIDevice1->pVTbl->Receive(pIDevice1, &(*data)[i]);
    }
      
#ifdef ECO_LINUX
    int16_t bytesRead = 0;
    do {
	    bytesRead = pIDevice1->pVTbl->Receive(pIDevice1, *data);
	    if (bytesRead > 1)
    		printf("wow: %d\n", bytesRead);
    } while (bytesRead < 7);
    *dataLength = bytesRead;
#else 
    *dataLength = i;
#endif

    pCMe->m_pVTblIEcoModBus1SL->SwitchCommunicationLED((IEcoModBus1SL*)pCMe, 0);
    
    /* pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, data); */

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция ConnectBus
 * </сводка>
 *
 * <описание>
 *   Функция подключает объект к UART девайсу
 * </описание>
 *
 */
#ifdef ECO_LINUX
static int16_t ECOCALLMETHOD CEcoModBus1SL_A9153876_ConnectBus(/* in */ IEcoModBus1SLPtr_t me, uint8_t isSlave, byte_t* devName, uint16_t nameLength) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)me;
    IEcoUART1Device* pIDevice1 = 0;

    IEcoUART1LinuxConfig* pIUARTConfig = 0;

    /* Проверка указателей */
    if (me == 0 || pCMe->m_pIUART == 0) {
        return ERR_ECO_POINTER;
    }

    /* Если девайс уже подключен, то вернуть ошибку */
    if (pCMe->m_pIUARTDevice != 0) {
        return ERR_ECO_FAIL;
    }
    
    uint16_t result = pCMe->m_pIUART->pVTbl->new_Device(pCMe->m_pIUART, &pCMe->m_pIUARTDevice);
    if (result != ERR_ECO_SUCCESES) {
        return ERR_ECO_UNEXPECTED;
    }
    pIDevice1 = pCMe->m_pIUARTDevice;

    /* Запрос интерфейса UART конфигурации */
    result = pIDevice1->pVTbl->QueryInterface(pIDevice1, &IID_IEcoUART1LinuxConfig, (void**) &pIUARTConfig);
    if (result != 0 || pIUARTConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        return ERR_ECO_NOINTERFACE;
    }

    /* Конфигурация UART девайса */
    /* Конфигурация устройства */
    /* long conv = strtol(argv[1], &p, 10); */
    /* TODO:
     * Из-за того, что это псевдотерминал, номер девайса назначается динамически.
     * При нормальном подключении по UART, номер будет статический
    **/
    ECO_UART_CONFIG_DESCRIPTOR xUART = {.slaveFlag = isSlave, .devName = { 0 }};
    for (uint16_t i = 0; i < nameLength; i++) {
      xUART.devName[i] = devName[i];
    }
    pIUARTConfig->pVTbl->set_ConfigDescriptor(pIUARTConfig, &xUART);

    ECO_UART_1_CONFIG UARTconfig = {115200, 0, 0, 0};

    /* Подключение устройства */
    return pIDevice1->pVTbl->Connect(pIDevice1, &UARTconfig);
}
#elif defined(ECO_STM32)
static int16_t ECOCALLMETHOD CEcoModBus1SL_A9153876_ConnectBus(/* in */ IEcoModBus1SLPtr_t me, IEcoUART1Device* device) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)me;

    pCMe->m_pIUARTDevice = device;
    return 0;
}
#endif

/*
 *
 * <сводка>
 *   Функция DisconnectBus
 * </сводка>
 *
 * <описание>
 *   Функция отключает объект от UART девайса
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SL_A9153876_DisconnectBus(/* in */ IEcoModBus1SLPtr_t me) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)me;

#ifdef ECO_LINUX
     uint16_t result = pCMe->m_pIUARTDevice->pVTbl->Disconnect(pCMe->m_pIUARTDevice);
#else
    uint16_t result = 0;
#endif

    /* Если успешно отключили девайс - очистить указатель на девайс */
    if (result == ERR_ECO_OK) {
        pCMe->m_pIUARTDevice = 0;
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция SwitchCommunicationLED
 * </сводка>
 *
 * <описание>
 *   Функция для включения или отключения светодиода во время отправки/получения данных
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SL_A9153876_SwitchCommunicationLED(/* in */ IEcoModBus1SLPtr_t me, /* in */ uint8_t State) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)me;

    /* Проверка указателей */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }
    
    if (!pCMe->LEDEnabled) return ERR_ECO_SUCCESES;

    #ifdef ECO_LINUX
    return ERR_ECO_SUCCESES;
    #elif ECO_STM32
    return pCMe->m_pCommunicationLED->pVTbl->set_Mode((IEcoGPIO1*)pCMe->m_pCommunicationLED, 0 /* TODO: COMMUNICATION_LED_PORT */, GPIO_MODE_OUTPUT);
    #endif /* ifdef ECO_LINUX */
}

/*
 *
 * <сводка>
 *   Функция set_LEDEnabled
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SL_A9153876_set_LEDEnabled(/* in */ IEcoModBus1SLPtr_t me, /* in */ uint8_t State) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)me;

    /* Проверка указателей */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }
    pCMe->LEDEnabled = State;

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция set_Slave
 * </сводка>
 *
 * <описание>
 *   Функция, устанавливающая флаг Slave
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SL_A9153876_set_Slave(/* in */ IEcoModBus1SLPtr_t me, /* in */ uint8_t isSlave) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)me;

    /* Проверка указателей */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }
    pCMe->m_slaveflag = isSlave;

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция calcLRC
 * </сводка>
 *
 * <описание>
 *   Функция которая считает LRC для сообщения msg длины len
 * </описание>
 *
 */
static uint8_t _calcLRC(/* in */ char_t* msg, /* in */ uint32_t len)
{
  uint8_t resultLRC = 0;
  while (len--) resultLRC += *msg++;

  return (uint8_t)(-((int8_t)resultLRC));
}

/*
 *
 * <сводка>
 *   Функция calcCRC16
 * </сводка>
 *
 * <описание>
 *   Функция которая считает CRC16 для сообщения msg длины len
 * </описание>
 *
 */
static uint16_t _calcCRC16(/* in*/ char_t* msg, /* in */ uint32_t len)
{
  uint8_t CRCHi = 0xFF; 
  uint8_t CRCLo = 0xFF;
  uint32_t index; /* индекс для таблиц CRC */

  while (len--)
  {
      index = CRCLo ^ *msg++;
      CRCLo = CRCHi ^ s_cTableCRCHi[index];
      CRCHi = s_cTableCRCLo[index];
  }

  return (CRCHi << 8 | CRCLo);
}

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoModBus1SLRTU
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SLRTU_A9153876_QueryInterface(/* in */ IEcoModBus1SLRTUPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoModBus1SLRTU) ) {
        *ppv = &pCMe->m_pVTblIEcoModBus1SLRTU;
        pCMe->m_pVTblIEcoModBus1SLRTU->AddRef((IEcoModBus1SLRTU*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoModBus1SLRTU;
        pCMe->m_pVTblIEcoModBus1SLRTU->AddRef((IEcoModBus1SLRTU*)pCMe);
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
 *   Функция AddRef для интерфейса IEcoModBus1SLRTU
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoModBus1SLRTU_A9153876_AddRef(/* in */ IEcoModBus1SLRTUPtr_t me) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*));

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
 *   Функция Release для интерфейса IEcoModBus1SLRTU
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoModBus1SLRTU_A9153876_Release(/* in */ IEcoModBus1SLRTUPtr_t me) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    return --pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция EmitMessage
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SLRTU_A9153876_EmitMessage(/* in */ IEcoModBus1SLRTUPtr_t me, /* in */ uint8_t functionCode, /* in */ uint16_t subCode, /* in */ byte_t* data, /* in */ uint32_t dataLength) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    /* Проверка указателей */
    if (me == 0 || data == 0) {
        return ERR_ECO_POINTER;
    }

    uint32_t dataToSendLength = 0;
    byte_t* dataToSend = 0;

    uint32_t pduLength = 0;
    byte_t* PDU = 0;
    pCMe->m_pIModBus->pVTbl->EncodePDU(pCMe->m_pIModBus, functionCode, subCode, data, dataLength, &PDU, &pduLength);

    dataToSendLength = pduLength + 3; /* 1 байт на адрес, 2 байта CRC */
    dataToSend = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, 1 + dataToSendLength);
    
    /* TODO:
     * Заменить 1 на реальный адрес устройства.
    **/
    dataToSend[0] = (byte_t)1;
    for (uint32_t i = 0; i < pduLength; i++)
        dataToSend[1 + i] = PDU[i];
    
    /* Последние 2 байта - это CRC */
    *(uint16_t*)(&dataToSend[dataToSendLength - 2]) = _calcCRC16((char_t*)data, dataLength);

    uint16_t result = pCMe->m_pVTblIEcoModBus1SL->EmitMessage((IEcoModBus1SL*)pCMe, dataToSend, dataToSendLength);
    if (result != ERR_ECO_SUCCESES) {
        /* printf("Emit error: %d", result); */
    }

    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, PDU);
    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, dataToSend);

    return result;
}

/*
 *
 * <сводка>
 *   Функция RecvMessage
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SLRTU_A9153876_RecvMessage(/* in */ IEcoModBus1SLRTUPtr_t me, /* out */ uint8_t* functionCode, /* out */ uint16_t* subCode,  /* out */ byte_t** data, /* out */ uint32_t* dataLength) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    /* Проверка указателей */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    uint16_t result;
    byte_t* rawData;
    uint32_t rawDataLength;

    result = pCMe->m_pVTblIEcoModBus1SL->RecvMessage((IEcoModBus1SL*)pCMe, &rawData, &rawDataLength);
    if (result != ERR_ECO_SUCCESES) {
        /* printf("Error while receiving: %d", result); */
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, rawData);
        return result;
    }
    byte_t addr = rawData[0];

    uint16_t rawCRC16 = ((((uint16_t)rawData[rawDataLength - 1]) << 8) | rawData[rawDataLength - 2]);
    
    byte_t* decodedData;
    result = pCMe->m_pIModBus->pVTbl->DecodePDU(pCMe->m_pIModBus, rawData + 1, rawDataLength - 3, functionCode, subCode, &decodedData, dataLength);
    if (result != ERR_ECO_SUCCESES) {
        /* printf("Error while decoding: %d", result); */
        return result;
    }

    pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, rawData);
    *data = &*decodedData;

    uint16_t decodedCRC16 = _calcCRC16((char_t*)decodedData, *dataLength);
    if (rawCRC16 != decodedCRC16) {
#ifdef ECO_LINUX
      printf("ERROR: raw(%d) != decoded(%d)", rawCRC16, decodedCRC16);
#endif
      //return ERR_ECO_FAIL;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция ConnectBus
 * </сводка>
 *
 * <описание>
 *   Функция подключения объекта к шины
 * </описание>
 *
 */
#if ECO_LINUX
static int16_t ECOCALLMETHOD CEcoModBus1SLRTU_A9153876_ConnectBus(/* in */ IEcoModBus1SLRTUPtr_t me, uint8_t isSlave, /* in */ byte_t* devName, /* in */ uint16_t nameLength) {
#elif ECO_STM32
static int16_t ECOCALLMETHOD CEcoModBus1SLRTU_A9153876_ConnectBus(/* in */ IEcoModBus1SLRTUPtr_t me, /* in */ IEcoUART1Device* device) {
#endif
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    /* Проверка указателей */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

#if ECO_LINUX
    return pCMe->m_pVTblIEcoModBus1SL->ConnectBus((IEcoModBus1SL*)pCMe, isSlave, devName, nameLength);
#elif ECO_STM32
    return pCMe->m_pVTblIEcoModBus1SL->ConnectBus((IEcoModBus1SL*)pCMe, device);
#endif
}

/*
 *
 * <сводка>
 *   Функция DisconnectBus
 * </сводка>
 *
 * <описание>
 *   Функция отключения объекта от шины
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SLRTU_A9153876_DisconnectBus(/* in */ IEcoModBus1SLRTUPtr_t me) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    /* Проверка указателей */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return pCMe->m_pVTblIEcoModBus1SL->DisconnectBus((IEcoModBus1SL*)pCMe);
}

/*
 *
 * <сводка>
 *   Функция set_LEDEnabled
 * </сводка>
 *
 * <описание>
 *   Функция для включения и отключения использования LED
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SLRTU_A9153876_set_LEDEnabled(/* in */ IEcoModBus1SLRTUPtr_t me, /* in */ uint8_t State) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    /* Проверка указателей */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return pCMe->m_pVTblIEcoModBus1SL->set_LEDEnabled((IEcoModBus1SL*)pCMe, State);
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
int16_t ECOCALLMETHOD initCEcoModBus1SL_A9153876(/*in*/ IEcoModBus1SLPtr_t me, /* in */ IEcoUnknownPtr_t pIUnkSystem) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)me;
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
    if (pIBus == 0 ) {
        return result;
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoModBus1, 0, &IID_IEcoModBus1, (void**) &pCMe->m_pIModBus);
    if (result != 0) {
        return result;
    }

#ifdef ECO_LINUX
    /* Получение интерфейса для работы с UART */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoUART1, 0, &IID_IEcoUART1, (void**) &pCMe->m_pIUART);
    if (result != 0) {
        return result;
    }
#endif

#ifdef ECO_STM32
    /* Получение интерфейса для работы с GPIO */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoGPIO1, 0, &IID_IEcoGPIO1, (void**) &pCMe->m_pIGPIO);
    if (result != 0) {
        return result;
    }
#endif

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Назначение Slave'ом по умолчанию */
    pCMe->m_pVTblIEcoModBus1SL->set_Slave((IEcoModBus1SL*)pCMe, 1);

    /* Выключение LED по умолчанию */
    pCMe->m_pVTblIEcoModBus1SL->set_LEDEnabled((IEcoModBus1SL*)pCMe, 0);

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoModBus1SLASCII
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SLASCII_A9153876_QueryInterface(/* in */ IEcoModBus1SLASCIIPtr_t me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*) * 2);

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return ERR_ECO_POINTER;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoModBus1SLASCII) ) {
        *ppv = &pCMe->m_pVTblIEcoModBus1SLASCII;
        pCMe->m_pVTblIEcoModBus1SLASCII->AddRef((IEcoModBus1SLASCII*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoModBus1SLASCII;
        pCMe->m_pVTblIEcoModBus1SLASCII->AddRef((IEcoModBus1SLASCII*)pCMe);
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
 *   Функция AddRef для интерфейса IEcoModBus1SLASCII
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoModBus1SLASCII_A9153876_AddRef(/* in */ IEcoModBus1SLASCIIPtr_t me) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*) * 2);

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
 *   Функция Release для интерфейса IEcoModBus1SLASCII
 * </описание>
 *
 */
static uint32_t ECOCALLMETHOD CEcoModBus1SLASCII_A9153876_Release(/* in */ IEcoModBus1SLASCIIPtr_t me) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*) * 2);

    /* Проверка указателя */
    if (me == 0 ) {
        return -1; /* ERR_ECO_POINTER */
    }

    /* Уменьшение счетчика ссылок на компонент */
    return --pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция EmitMessage
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SLASCII_A9153876_EmitMessage(/* in */ IEcoModBus1SLASCIIPtr_t me, /* in */ uint8_t functionCode, /* in */ uint16_t subCode, /* in */ byte_t* data, /* in */ uint32_t dataLength) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*) * 2);

    /* Проверка указателей */
    if (me == 0 || data == 0) {
        return ERR_ECO_POINTER;
    }

    uint32_t pduLength = 0;
    byte_t* PDU = 0;
    pCMe->m_pIModBus->pVTbl->EncodePDU(pCMe->m_pIModBus, functionCode, subCode, data, dataLength, &PDU, &pduLength);
    // /* in */ uint8_t functionCode, /* in */ uint16_t subCode, /* in */ byte_t* Data, /* in */ uint32_t dataLength, /* out */ byte_t** PDU, /* out */ uint32_t* pduLength);
  
    /* TODO: add encoding for ASCII */
  

    return pCMe->m_pVTblIEcoModBus1SL->EmitMessage((IEcoModBus1SL*)pCMe->m_pVTblIEcoModBus1SL, PDU, pduLength);
}

/*
 *
 * <сводка>
 *   Функция RecvMessage
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SLASCII_A9153876_RecvMessage(/* in */ IEcoModBus1SLASCIIPtr_t me, /* in */ char_t* Name, /* out */ char_t** copyName) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*) * 2);

    /* Проверка указателей */
    if (me == 0 || Name == 0 || copyName == 0) {
        return ERR_ECO_POINTER;
    }

    return ERR_ECO_SUCCESES;
}

/*
 *
 * <сводка>
 *   Функция ConnectBus
 * </сводка>
 *
 * <описание>
 *   Функция подключения объекта к шины
 * </описание>
 *
 */
#if ECO_LINUX
static int16_t ECOCALLMETHOD CEcoModBus1SLASCII_A9153876_ConnectBus(/* in */ IEcoModBus1SLASCIIPtr_t me, /* in */ uint8_t isSlave, /* in */ byte_t* devName, /* in */ uint16_t nameLength) {
#elif ECO_STM32
static int16_t ECOCALLMETHOD CEcoModBus1SLASCII_A9153876_ConnectBus(/* in */ IEcoModBus1SLASCIIPtr_t me, /* in */ IEcoUART1Device* device) {
#endif
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    /* Проверка указателей */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

#if ECO_LINUX
    return pCMe->m_pVTblIEcoModBus1SL->ConnectBus((IEcoModBus1SL*)pCMe, isSlave, devName, nameLength);
#elif ECO_STM32
    return pCMe->m_pVTblIEcoModBus1SL->ConnectBus((IEcoModBus1SL*)pCMe, device);
#endif
}

/*
 *
 * <сводка>
 *   Функция DisconnectBus
 * </сводка>
 *
 * <описание>
 *   Функция отключения объекта от шины
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SLASCII_A9153876_DisconnectBus(/* in */ IEcoModBus1SLASCIIPtr_t me) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    /* Проверка указателей */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return pCMe->m_pVTblIEcoModBus1SL->DisconnectBus((IEcoModBus1SL*)pCMe);
}

/*
 *
 * <сводка>
 *   Функция set_LEDEnabled
 * </сводка>
 *
 * <описание>
 *   Функция для включения и отключения использования LED
 * </описание>
 *
 */
static int16_t ECOCALLMETHOD CEcoModBus1SLASCII_A9153876_set_LEDEnabled(/* in */ IEcoModBus1SLASCIIPtr_t me, /* in */ uint8_t State) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)((uint64_t)me - sizeof(struct IEcoUnknown*) * 2);

    /* Проверка указателей */
    if (me == 0) {
        return ERR_ECO_POINTER;
    }

    return pCMe->m_pVTblIEcoModBus1SL->set_LEDEnabled((IEcoModBus1SL*)pCMe, State);
}

/* Create Virtual Table IEcoModBus1SL */
IEcoModBus1SLVTbl g_x941CA1AA58374485AE010CBEAA9924D8VTbl_A9153876 = {
    CEcoModBus1SL_A9153876_QueryInterface,
    CEcoModBus1SL_A9153876_AddRef,
    CEcoModBus1SL_A9153876_Release,
    CEcoModBus1SL_A9153876_EmitMessage,
    CEcoModBus1SL_A9153876_RecvMessage,
    CEcoModBus1SL_A9153876_ConnectBus,
    CEcoModBus1SL_A9153876_DisconnectBus,
    CEcoModBus1SL_A9153876_SwitchCommunicationLED,
    CEcoModBus1SL_A9153876_set_LEDEnabled,
    CEcoModBus1SL_A9153876_set_Slave
};

/* Create Virtual Table IEcoModBus1SLRTU */
IEcoModBus1SLRTUVTbl g_xF461F8FE4FA74E4D88C6DCCA8A2B795CVTbl_A9153876 = {
    CEcoModBus1SLRTU_A9153876_QueryInterface,
    CEcoModBus1SLRTU_A9153876_AddRef,
    CEcoModBus1SLRTU_A9153876_Release,
    CEcoModBus1SLRTU_A9153876_EmitMessage,
    CEcoModBus1SLRTU_A9153876_RecvMessage,
    CEcoModBus1SLRTU_A9153876_ConnectBus,
    CEcoModBus1SLRTU_A9153876_DisconnectBus,
    CEcoModBus1SLRTU_A9153876_set_LEDEnabled
};

/* Create Virtual Table IEcoModBus1SLASCII */
IEcoModBus1SLASCIIVTbl g_xA060458B14A84C9DAE26A15C22D8E8ECVTbl_A9153876 = {
    CEcoModBus1SLASCII_A9153876_QueryInterface,
    CEcoModBus1SLASCII_A9153876_AddRef,
    CEcoModBus1SLASCII_A9153876_Release,
    CEcoModBus1SLASCII_A9153876_EmitMessage,
    CEcoModBus1SLASCII_A9153876_RecvMessage,
    CEcoModBus1SLASCII_A9153876_ConnectBus,
    CEcoModBus1SLASCII_A9153876_DisconnectBus,
    CEcoModBus1SLASCII_A9153876_set_LEDEnabled
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
int16_t ECOCALLMETHOD createCEcoModBus1SL_A9153876(/* in */ IEcoUnknownPtr_t pIUnkSystem, /* in */ IEcoUnknownPtr_t pIUnkOuter, /* out */ IEcoModBus1SLPtr_t* ppIEcoModBus1SL) {
    int16_t result = ERR_ECO_POINTER;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoModBus1SL_A9153876* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
	
    /* Проверка указателей */
    if (ppIEcoModBus1SL == 0 || pIUnkSystem == 0) {
        return result; /* ERR_ECO_POINTER */
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem, (void **)&pISys);
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
    pCMe = (CEcoModBus1SL_A9153876*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoModBus1SL_A9153876));
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

    /* Создание таблицы функций интерфейса IEcoModBus1SL */
    pCMe->m_pVTblIEcoModBus1SL      = &g_x941CA1AA58374485AE010CBEAA9924D8VTbl_A9153876;
    /* Создание таблицы функций интерфейса IEcoModBus1SLRTU */
    pCMe->m_pVTblIEcoModBus1SLRTU   = &g_xF461F8FE4FA74E4D88C6DCCA8A2B795CVTbl_A9153876;
    /* Создание таблицы функций интерфейса IEcoModBus1SLASCII */
    pCMe->m_pVTblIEcoModBus1SLASCII = &g_xA060458B14A84C9DAE26A15C22D8E8ECVTbl_A9153876;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoModBus1SL = (IEcoModBus1SL*)pCMe;

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
void ECOCALLMETHOD deleteCEcoModBus1SL_A9153876(/* in */ IEcoModBus1SLPtr_t pIEcoModBus1SL) {
    CEcoModBus1SL_A9153876* pCMe = (CEcoModBus1SL_A9153876*)pIEcoModBus1SL;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoModBus1SL != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
