/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoModBus1SLASCII
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoModBus1SLASCII
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

#ifndef __I_ECOMODBUS1SLASCII_H__
#define __I_ECOMODBUS1SLASCII_H__

#include "IEcoBase1.h"
#include "IEcoModBus1SL.h"


/* IEcoModBus1SLASCII IID = {A060458B-14A8-4C9D-AE26-A15C22D8E8EC} */
#ifndef __IID_IEcoModBus1SLASCII
static const UGUID IID_IEcoModBus1SLASCII = {0x01, 0x10, {0xA0, 0x60, 0x45, 0x8B, 0x14, 0xA8, 0x4C, 0x9D, 0xAE, 0x26, 0xA1, 0x5C, 0x22, 0xD8, 0xE8, 0xEC}};
#endif /* __IID_IEcoModBus1SLASCII */

typedef struct IEcoModBus1SLASCII* IEcoModBus1SLASCIIPtr_t;

typedef struct IEcoModBus1SLASCIIVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoModBus1SLASCIIPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoModBus1SLASCIIPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoModBus1SLASCIIPtr_t me);

    /* IEcoModBus1SLASCII */
    int16_t (ECOCALLMETHOD *EmitMessage)(/* in */ IEcoModBus1SLASCIIPtr_t me, /* in */ uint8_t functionCode, /* in */ uint16_t subCode, /* in */ byte_t* data, /* in */ uint32_t dataLength);
    int16_t (ECOCALLMETHOD *RecvMessage)(/* in */ IEcoModBus1SLASCIIPtr_t me, /* in */ char_t* Name, /* out */ char_t** CopyName);

#if defined(ECO_LINUX)
    int16_t (ECOCALLMETHOD *ConnectBus)(/* in */ IEcoModBus1SLASCIIPtr_t me, uint8_t isSlave, /* in */ byte_t* devName, /* in */ uint16_t nameLength);
#elif defined(ECO_STM32)
    int16_t (ECOCALLMETHOD *ConnectBus)(/* in */ IEcoModBus1SLASCIIPtr_t me, /* in */ IEcoUART1Device* device);
#endif
    int16_t (ECOCALLMETHOD *DisconnectBus)(/* in */ IEcoModBus1SLASCIIPtr_t me);

    int16_t (ECOCALLMETHOD *EnableLED)(/* in */ IEcoModBus1SLASCIIPtr_t me, /* in */ uint8_t State);

} IEcoModBus1SLASCIIVTbl, *IEcoModBus1SLASCIIVTblPtr_t;

interface IEcoModBus1SLASCII {
    struct IEcoModBus1SLASCIIVTbl *pVTbl;
} IEcoModBus1SLASCII;


#endif /* __I_ECOMODBUS1SLASCII_H__ */
