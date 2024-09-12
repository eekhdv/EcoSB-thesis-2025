/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoModBus1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoModBus1
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

#ifndef __I_ECOMODBUS1_H__
#define __I_ECOMODBUS1_H__

#include "IEcoBase1.h"

/* IEcoModBus1 IID = {74AB8CD0-056F-4D04-8F85-5D2FC8A9F3D0} */
#ifndef __IID_IEcoModBus1
static const UGUID IID_IEcoModBus1 = {0x01, 0x10, {0x74, 0xAB, 0x8C, 0xD0, 0x05, 0x6F, 0x4D, 0x04, 0x8F, 0x85, 0x5D, 0x2F, 0xC8, 0xA9, 0xF3, 0xD0}};
#endif /* __IID_IEcoModBus1 */

typedef struct IEcoModBus1* IEcoModBus1Ptr_t;

typedef struct IEcoModBus1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoModBus1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoModBus1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoModBus1Ptr_t me);

    /* IEcoModBus1 */
    int16_t (ECOCALLMETHOD *MyFunction)(/* in */ IEcoModBus1Ptr_t me, /* in */ char_t* Name, /* out */ char_t** CopyName);

} IEcoModBus1VTbl, *IEcoModBus1VTblPtr_t;

interface IEcoModBus1 {
    struct IEcoModBus1VTbl *pVTbl;
} IEcoModBus1;


#endif /* __I_ECOMODBUS1_H__ */
