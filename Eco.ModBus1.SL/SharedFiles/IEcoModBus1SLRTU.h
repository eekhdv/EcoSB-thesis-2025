/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoModBus1SL
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoModBus1SLRTU
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECOMODBUS1SLRTU_H__
#define __I_ECOMODBUS1SLRTU_H__

#include "IEcoBase1.h"
#include "IEcoModBus1SL.h"


/* IEcoModBus1SLRTU IID = {F461F8FE-4FA7-4E4D-88C6-DCCA8A2B795C} */
#ifndef __IID_IEcoModBus1SLRTU
static const UGUID IID_IEcoModBus1SLRTU = {0x01, 0x10, {0xF4, 0x61, 0xF8, 0xFE, 0x4F, 0xA7, 0x4E, 0x4D, 0x88, 0xC6, 0xDC, 0xCA, 0x8A, 0x2B, 0x79, 0x5C}};
#endif /* __IID_IEcoModBus1SLRTU */

typedef struct IEcoModBus1SLRTU* IEcoModBus1SLRTUPtr_t;

typedef struct IEcoModBus1SLRTUVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoModBus1SLRTUPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoModBus1SLRTUPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoModBus1SLRTUPtr_t me);

    /* IEcoModBus1SLRTU */
    int16_t (ECOCALLMETHOD *EmitMessage)(/* in */ IEcoModBus1SLRTUPtr_t me, /* in */ uint8_t functionCode, /* in */ uint16_t subCode, /* in */ byte_t* data, /* in */ uint32_t dataLength);
    int16_t (ECOCALLMETHOD *RecvMessage)(/* in */ IEcoModBus1SLRTUPtr_t me, /* out */ uint8_t* functionCode, /* out */ uint16_t* subCode,  /* out */ byte_t** data, /* out */ uint32_t* dataLength);

#if ECO_LINUX
    int16_t (ECOCALLMETHOD *ConnectBus)(/* in */ IEcoModBus1SLRTUPtr_t me, uint8_t isSlave, /* in */ byte_t* devName, /* in */ uint16_t nameLength);
#elif defined(ECO_STM32)
    int16_t (ECOCALLMETHOD *ConnectBus)(/* in */ IEcoModBus1SLRTUPtr_t me, /* in */ IEcoUART1Device* device);
#endif
    int16_t (ECOCALLMETHOD *DisconnectBus)(/* in */ IEcoModBus1SLRTUPtr_t me);

    int16_t (ECOCALLMETHOD *EnableLED)(/* in */ IEcoModBus1SLRTUPtr_t me, /* in */ uint8_t State);

} IEcoModBus1SLRTUVTbl, *IEcoModBus1SLRTUVTblPtr_t;

interface IEcoModBus1SLRTU {
    struct IEcoModBus1SLRTUVTbl *pVTbl;
} IEcoModBus1SLRTU;


#endif /* __I_ECOMODBUS1SLRTU_H__ */
