/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoGPIO1K210Config
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoGPIO1K210Config
 *
 * 
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2019 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_GPIO_1_K210_CONFIG_H__
#define __I_ECO_GPIO_1_K210_CONFIG_H__

#include "IEcoBase1.h"

typedef struct ECO_GPIO_REGISTER_MAP {
    uint32_t data_output;           /* GPIO Data (output) registers,                Address offset: 0x00      */
    uint32_t direction;             /* GPIO Data direction registers,               Address offset: 0x04      */
    uint32_t source;                /* GPIO Data source registers,                  Address offset: 0x08      */
    uint32_t unused_0[9];           /* GPIO Unused registers, 9x4 bytes,            Address offset: 0x0C-0x2F */
    uint32_t interrupt_enable;      /* GPIO Interrupt enable/disable registers,     Address offset: 0x30      */
    uint32_t interrupt_mask;        /* GPIO Interrupt mask registers,               Address offset: 0x34      */
    uint32_t interrupt_level;       /* GPIO Interrupt level registers,              Address offset: 0x38      */
    uint32_t interrupt_polarity;    /* GPIO Interrupt polarity registers,           Address offset: 0x3C      */
    uint32_t interrupt_status;      /* GPIO Interrupt status registers,             Address offset: 0x40      */
    uint32_t interrupt_status_raw;  /* GPIO Raw interrupt status registers,         Address offset: 0x44      */
    uint32_t interrupt_debounce;    /* GPIO Interrupt debounce registers,           Address offset: 0x48      */
    uint32_t interrupt_clear;       /* GPIO Registers for clearing interrupts,      Address offset: 0x4C      */
    uint32_t data_input;            /* GPIO External port (data input) registers,   Address offset: 0x50      */
    uint32_t unused_1[3];           /* GPIO Unused registers, 3x4 bytes,            Address offset: 0x54-0x5F */
    uint32_t sync_level;            /* GPIO Sync level registers,                   Address offset: 0x60      */
    uint32_t id_code;               /* GPIO ID code,                                Address offset: 0x64      */
    uint32_t interrupt_bothedge;    /* GPIO Interrupt both edge type,               Address offset: 0x68      */
} ECO_GPIO_REGISTER_MAP;

typedef struct ECO_GPIO_CONFIG_DESCRIPTOR {
    union {
        uint32_t BaseAddress;
        struct ECO_GPIO_REGISTER_MAP* Map;
    } Register;
    uint8_t LogicalPinMask[64];
} ECO_GPIO_CONFIG_DESCRIPTOR;

/* IEcoGPIO1K210Config IID = {3E002B7B-B389-408D-9EDE-B288C5DC2F30} */
#ifndef __IID_IEcoGPIO1K210Config
static const UGUID IID_IEcoGPIO1K210Config = { 0x01, 0x10, 0x3E, 0x00, 0x2B, 0x7B, 0xB3, 0x89, 0x40, 0x8D, 0x9E, 0xDE, 0xB2, 0x88, 0xC5, 0xDC, 0x2F, 0x30 };
#endif /* __IID_IEcoGPIO1K210Config */

typedef struct IEcoGPIO1K210ConfigVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ struct IEcoGPIO1K210Config* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ struct IEcoGPIO1K210Config* me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ struct IEcoGPIO1K210Config* me);

    /* IEcoGPIO1K210Config */
    int16_t (ECOCALLMETHOD *set_ConfigDescriptor)(/* in */ struct IEcoGPIO1K210Config* me, /* in */ ECO_GPIO_CONFIG_DESCRIPTOR* config);
    ECO_GPIO_CONFIG_DESCRIPTOR* (ECOCALLMETHOD *get_ConfigDescriptor)(/* in */ struct IEcoGPIO1K210Config* me);
    int16_t (ECOCALLMETHOD *set_LogicalPinNumber)(/* in */ struct IEcoGPIO1K210Config* me, /* in */ uint8_t LogicalPinNumber, /* in */ uint8_t BankNumber, /* in */ uint32_t PinNumber);

} IEcoGPIO1K210ConfigVTbl, *IEcoGPIO1K210ConfigVTblPtr;

interface IEcoGPIO1K210Config {
    struct IEcoGPIO1K210ConfigVTbl *pVTbl;
} IEcoGPIO1K210Config;

#endif /* __I_ECO_GPIO_1_K210_CONFIG_H__ */
