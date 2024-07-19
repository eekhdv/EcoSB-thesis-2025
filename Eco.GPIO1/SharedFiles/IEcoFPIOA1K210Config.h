/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoFPIOA1K210Config
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoFPIOA1K210Config
 *
 * 
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2019 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_FPIOA_1_K210_CONFIG_H__
#define __I_ECO_FPIOA_1_K210_CONFIG_H__

#include "IEcoBase1.h"

typedef union ECO_FPIOA_IO_REGISTER {
    struct {
        uint32_t ch_sel  : 8;   /* Channel select from 256 input. */
        uint32_t ds      : 4;   /* Driving selector. */
        uint32_t oe_en   : 1;   /* Static output enable, will AND with OE_INV. */
        uint32_t oe_inv  : 1;   /* Invert output enable. */
        uint32_t do_sel  : 1;   /* Data output select: 0 for DO, 1 for OE. */
        uint32_t do_inv  : 1;   /* Invert the result of data output select (DO_SEL). */
        uint32_t pu      : 1;   /* Pull up enable. 0 for nothing, 1 for pull up. */
        uint32_t pd      : 1;   /* Pull down enable. 0 for nothing, 1 for pull down. */
        uint32_t resv0   : 1;   /* Reserved bits. */
        uint32_t sl      : 1;   /* Slew rate control enable. */
        uint32_t ie_en   : 1;   /* Static input enable, will AND with IE_INV. */
        uint32_t ie_inv  : 1;   /* Invert input enable. */
        uint32_t di_inv  : 1;   /* Invert Data input. */
        uint32_t st      : 1;   /* Schmitt trigger. */
        uint32_t tie_en  : 1;   /* Input tie enable, 1 for enable, 0 for disable. */
        uint32_t tie_val : 1;   /* Input tie value, 1 for high, 0 for low. */
        uint32_t resv1   : 5;   /* Reserved bits. */
        uint32_t pad_di  : 1;   /* Read current PAD's data input. */
    } bits;
    uint32_t dword;
} ECO_FPIOA_IO_REGISTER;

typedef struct ECO_FPIOA_REGISTER_MAP {
    uint32_t io[48];        /* FPIOA GPIO multiplexer io array,         Address offset: 0x00      */
    uint32_t tie_en[8];     /* FPIOA GPIO multiplexer tie enable,       Address offset: 0xC0      */
    uint32_t tie_val[8];    /* FPIOA GPIO multiplexer tie value,        Address offset: 0xE0      */
} ECO_FPIOA_REGISTER_MAP;

typedef struct ECO_FPIOA_CONFIG_DESCRIPTOR {
    union {
        uint32_t BaseAddress;
        struct ECO_FPIOA_REGISTER_MAP* Map;
    } Register;
} ECO_FPIOA_CONFIG_DESCRIPTOR;

/* IEcoFPIOA1K210Config IID = {D74C3896-D518-4D92-B47A-AD510B216A6B} */
#ifndef __IID_IEcoFPIOA1K210Config
static const UGUID IID_IEcoFPIOA1K210Config = { 0x01, 0x10, 0xD7, 0x4C, 0x38, 0x96, 0xD5, 0x18, 0x4D, 0x92, 0xB4, 0x7A, 0xAD, 0x51, 0x0B, 0x21, 0x6A, 0x6B };
#endif /* __IID_IEcoFPIOA1K210Config */

typedef struct IEcoFPIOA1K210ConfigVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ struct IEcoFPIOA1K210Config* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ struct IEcoFPIOA1K210Config* me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ struct IEcoFPIOA1K210Config* me);

    /* IEcoFPIOA1K210Config */
    int16_t (ECOCALLMETHOD *set_ConfigDescriptor)(/* in */ struct IEcoFPIOA1K210Config* me, /* in */ ECO_FPIOA_CONFIG_DESCRIPTOR* config);
    ECO_FPIOA_CONFIG_DESCRIPTOR* (ECOCALLMETHOD *get_ConfigDescriptor)(/* in */ struct IEcoFPIOA1K210Config* me);

} IEcoFPIOA1K210ConfigVTbl, *IEcoFPIOA1K210ConfigVTblPtr;

interface IEcoFPIOA1K210Config {
    struct IEcoFPIOA1K210ConfigVTbl *pVTbl;
} IEcoFPIOA1K210Config;

#endif /* __I_ECO_FPIOA_1_K210_CONFIG_H__ */
