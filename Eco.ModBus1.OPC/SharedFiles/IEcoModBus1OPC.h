/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoModBus1OPC
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoModBus1OPC
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

#ifndef __I_ECOMODBUS1OPC_H__
#define __I_ECOMODBUS1OPC_H__

#include "IEcoBase1.h"

/* IEcoModBus1OPC IID = {875723E0-4678-4CA2-A8AC-10A31DD07A88} */
#ifndef __IID_IEcoModBus1OPC
static const UGUID IID_IEcoModBus1OPC = {0x01, 0x10, {0x87, 0x57, 0x23, 0xE0, 0x46, 0x78, 0x4C, 0xA2, 0xA8, 0xAC, 0x10, 0xA3, 0x1D, 0xD0, 0x7A, 0x88}};
#endif /* __IID_IEcoModBus1OPC */

typedef struct IEcoModBus1OPC* IEcoModBus1OPCPtr_t;

typedef struct IEcoModBus1OPCVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoModBus1OPCPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoModBus1OPCPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoModBus1OPCPtr_t me);

    /* IEcoModBus1OPC */
    int16_t (ECOCALLMETHOD *MyFunction)(/* in */ IEcoModBus1OPCPtr_t me, /* in */ char_t* Name, /* out */ char_t** CopyName);

} IEcoModBus1OPCVTbl, *IEcoModBus1OPCVTblPtr_t;

interface IEcoModBus1OPC {
    struct IEcoModBus1OPCVTbl *pVTbl;
} IEcoModBus1OPC;


#endif /* __I_ECOMODBUS1OPC_H__ */
