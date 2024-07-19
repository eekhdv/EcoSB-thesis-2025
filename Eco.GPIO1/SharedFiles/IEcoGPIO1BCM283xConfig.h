/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoGPIO1BCM283xConfig
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoGPIO1BCM283xConfig
 *
 * 
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2019 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_GPIO_1_BCM283X_CONFIG_H__
#define __I_ECO_GPIO_1_BCM283X_CONFIG_H__

#include "IEcoBase1.h"

typedef struct GPIO_REGISTER_MAP {
    uint32_t GPFSEL0;       /* GPIO Function Select 0,               Address offset: 0x00      */
    uint32_t GPFSEL1;       /* GPIO Function Select 1,               Address offset: 0x04      */
    uint32_t GPFSEL2;       /* GPIO Function Select 2,               Address offset: 0x08      */
    uint32_t GPFSEL3;       /* GPIO Function Select 3,               Address offset: 0x0C      */
    uint32_t GPFSEL4;       /* GPIO Function Select 4,               Address offset: 0x10      */
    uint32_t GPFSEL5;       /* GPIO Function Select 5,               Address offset: 0x14      */
    uint32_t RESERVED1;     /* Reserved,                             Address offset: 0x18      */
    uint32_t GPSET0;        /* GPIO Pin Output Set 0,                Address offset: 0x1C      */
    uint32_t GPSET1;        /* GPIO Pin Output Set 1,                Address offset: 0x20      */
    uint32_t RESERVED2;     /* Reserved,                             Address offset: 0x24      */
    uint32_t GPCLR0;        /* GPIO Pin Output Clear 0,              Address offset: 0x28      */
    uint32_t GPCLR1;        /* GPIO Pin Output Clear 1,              Address offset: 0x2C      */
    uint32_t RESERVED3;     /* Reserved,                             Address offset: 0x30      */
    uint32_t GPLEV0;        /* GPIO Pin Level 0,                     Address offset: 0x34      */
    uint32_t GPLEV1;        /* GPIO Pin Level 1,                     Address offset: 0x38      */
    uint32_t RESERVED4;     /* Reserved,                             Address offset: 0x3C      */
    uint32_t GPEDS0;        /* GPIO Pin Event Detect Status 0,       Address offset: 0x40      */
    uint32_t GPEDS1;        /* GPIO Pin Event Detect Status 1,       Address offset: 0x44      */
    uint32_t RESERVED5;     /* Reserved,                             Address offset: 0x48      */
    uint32_t GPREN0;        /* GPIO Pin Rising Edge Detect Enable 0, Address offset: 0x4C      */
    uint32_t GPREN1;        /* GPIO Pin Rising Edge Detect Enable 1, Address offset: 0x50      */
    uint32_t RESERVED6;     /* Reserved,                             Address offset: 0x54      */
    uint32_t GPFEN0;        /* GPIO Pin Falling Edge Detect Enable 0,Address offset: 0x58      */
    uint32_t GPFEN1;        /* GPIO Pin Falling Edge Detect Enable 1,Address offset: 0x5C      */
    uint32_t RESERVED7;     /* Reserved,                             Address offset: 0x60      */
    uint32_t GPHEN0;        /* GPIO Pin High Detect Enable 0,        Address offset: 0x64      */
    uint32_t GPHEN1;        /* GPIO Pin High Detect Enable 1,        Address offset: 0x68      */
    uint32_t RESERVED8;     /* Reserved,                             Address offset: 0x6C      */
    uint32_t GPLEN0;        /* GPIO Pin Low Detect Enable 0,         Address offset: 0x70      */
    uint32_t GPLEN1;        /* GPIO Pin Low Detect Enable 1,         Address offset: 0x74      */
    uint32_t RESERVED9;     /* Reserved,                             Address offset: 0x78      */
    uint32_t GPAREN0;       /* GPIO Pin Async.Rising Edge Detect 0,  Address offset: 0x7C      */
    uint32_t GPAREN1;       /* GPIO Pin Async.Rising Edge Detect 1,  Address offset: 0x80      */
    uint32_t RESERVED10;    /* Reserved,                             Address offset: 0x84      */
    uint32_t GPAFEN0;       /* GPIO Pin Async.Falling Edge Detect 0, Address offset: 0x88      */
    uint32_t GPAFEN1;       /* GPIO Pin Async.Falling Edge Detect 1, Address offset: 0x8C      */
    uint32_t RESERVED11;    /* Reserved,                             Address offset: 0x90      */
    uint32_t GPPUD;         /* GPIO Pin Pull-up/down Enable,         Address offset: 0x94      */
    uint32_t GPPUDCLK0;     /* GPIO Pin Pull-up/down Enable Clock 0, Address offset: 0x98      */
    uint32_t GPPUDCLK1;     /* GPIO Pin Pull-up/down Enable Clock 1, Address offset: 0x9C      */
    uint32_t RESERVED12;    /* Reserved,                             Address offset: 0xA0      */
} GPIO_REGISTER_MAP;

typedef struct GPIO_CONFIG_DESCRIPTOR {
    union {
        uint32_t BaseAddress;
        struct GPIO_REGISTER_MAP* Map;
    } Register;
    uint8_t LogicalPinMask[64];
} GPIO_CONFIG_DESCRIPTOR;

/* IEcoGPIO1BCM283xConfig IID = {7B844D9C-EA99-4E86-95DD-CA78668D0B2A} */
#ifndef __IID_IEcoGPIO1BCM283xConfig
static const UGUID IID_IEcoGPIO1BCM283xConfig = { 0x01, 0x10, 0x7B, 0x84, 0x4D, 0x9C, 0xEA, 0x99, 0x4E, 0x86, 0x95, 0xDD, 0xCA, 0x78, 0x66, 0x8D, 0x0B, 0x2A };
#endif /* __IID_IEcoGPIO1BCM283xConfig */

typedef struct IEcoGPIO1BCM283xConfigVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ struct IEcoGPIO1BCM283xConfig* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ struct IEcoGPIO1BCM283xConfig* me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ struct IEcoGPIO1BCM283xConfig* me);

    /* IEcoGPIO1BCM283xConfig */
    int16_t (ECOCALLMETHOD *set_ConfigDescriptor)(/* in */ struct IEcoGPIO1BCM283xConfig* me, /* in */ GPIO_CONFIG_DESCRIPTOR* config);
    GPIO_CONFIG_DESCRIPTOR* (ECOCALLMETHOD *get_ConfigDescriptor)(/* in */ struct IEcoGPIO1BCM283xConfig* me);
    int16_t (ECOCALLMETHOD *set_LogicalPinNumber)(/* in */ struct IEcoGPIO1BCM283xConfig* me, /* in */ uint8_t LogicalPinNumber, /* in */ uint8_t BankNumber, /* in */ uint32_t PinNumber);

} IEcoGPIO1BCM283xConfigVTbl, *IEcoGPIO1BCM283xConfigVTblPtr;

interface IEcoGPIO1BCM283xConfig {
    struct IEcoGPIO1BCM283xConfigVTbl *pVTbl;
} IEcoGPIO1BCM283xConfig;

#endif /* __I_ECO_GPIO_1_BCM283X_CONFIG_H__ */
