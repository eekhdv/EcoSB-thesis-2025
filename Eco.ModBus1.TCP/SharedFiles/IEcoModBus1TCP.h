/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoModBus1TCP
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoModBus1TCP
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

#ifndef __I_ECOMODBUS1TCP_H__
#define __I_ECOMODBUS1TCP_H__

#include "IEcoBase1.h"

/* IEcoModBus1TCP IID = {93101775-F72E-4052-91C5-A51057CF0CA4} */
#ifndef __IID_IEcoModBus1TCP
static const UGUID IID_IEcoModBus1TCP = {0x01, 0x10, {0x93, 0x10, 0x17, 0x75, 0xF7, 0x2E, 0x40, 0x52, 0x91, 0xC5, 0xA5, 0x10, 0x57, 0xCF, 0x0C, 0xA4}};
#endif /* __IID_IEcoModBus1TCP */

typedef struct IEcoModBus1TCP* IEcoModBus1TCPPtr_t;

typedef struct IEcoModBus1TCPVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoModBus1TCPPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoModBus1TCPPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoModBus1TCPPtr_t me);

    /* IEcoModBus1TCP */
    int16_t (ECOCALLMETHOD *MyFunction)(/* in */ IEcoModBus1TCPPtr_t me, /* in */ char_t* Name, /* out */ char_t** CopyName);

} IEcoModBus1TCPVTbl, *IEcoModBus1TCPVTblPtr_t;

interface IEcoModBus1TCP {
    struct IEcoModBus1TCPVTbl *pVTbl;
} IEcoModBus1TCP;


#endif /* __I_ECOMODBUS1TCP_H__ */
