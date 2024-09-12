/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoRCC1STM32Config
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoRCC1STM32Config
 *
 * 
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2019 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_RCC_1_STM32_CONFIG_H__
#define __I_ECO_RCC_1_STM32_CONFIG_H__

#include "IEcoBase1.h"


typedef struct RCC_REGISTER_MAP {
    uint32_t CR;            /* RCC clock control register,                                  Address offset: 0x00 */
    uint32_t PLLCFGR;       /* RCC PLL configuration register,                              Address offset: 0x04 */
    uint32_t CFGR;          /* RCC clock configuration register,                            Address offset: 0x08 */
    uint32_t CIR;           /* RCC clock interrupt register,                                Address offset: 0x0C */
    uint32_t AHB1RSTR;      /* RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
    uint32_t AHB2RSTR;      /* RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
    uint32_t AHB3RSTR;      /* RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
    uint32_t RESERVED0;     /* Reserved, 0x1C                                                                    */
    uint32_t APB1RSTR;      /* RCC APB1 peripheral reset register,                          Address offset: 0x20 */
    uint32_t APB2RSTR;      /* RCC APB2 peripheral reset register,                          Address offset: 0x24 */
    uint32_t RESERVED1[2];  /* Reserved, 0x28-0x2C                                                               */
    uint32_t AHB1ENR;       /* RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
    uint32_t AHB2ENR;       /* RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
    uint32_t AHB3ENR;       /* RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
    uint32_t RESERVED2;     /* Reserved, 0x3C                                                                    */
    uint32_t APB1ENR;       /* RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
    uint32_t APB2ENR;       /* RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
    uint32_t RESERVED3[2];  /* Reserved, 0x48-0x4C                                                               */
    uint32_t AHB1LPENR;     /* RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
    uint32_t AHB2LPENR;     /* RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
    uint32_t AHB3LPENR;     /* RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
    uint32_t RESERVED4;     /* Reserved, 0x5C                                                                    */
    uint32_t APB1LPENR;     /* RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
    uint32_t APB2LPENR;     /* RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
    uint32_t RESERVED5[2];  /* Reserved, 0x68-0x6C                                                               */
    uint32_t BDCR;          /* RCC Backup domain control register,                          Address offset: 0x70 */
    uint32_t CSR;           /* RCC clock control & status register,                         Address offset: 0x74 */
    uint32_t RESERVED6[2];  /* Reserved, 0x78-0x7C                                                               */
    uint32_t SSCGR;         /* RCC spread spectrum clock generation register,               Address offset: 0x80 */
    uint32_t PLLI2SCFGR;    /* RCC PLLI2S configuration register,                           Address offset: 0x84 */
    uint32_t PLLSAICFGR;    /* RCC PLLSAI configuration register,                           Address offset: 0x88 */
    uint32_t DCKCFGR;       /* RCC Dedicated Clocks configuration register,                 Address offset: 0x8C */
} RCC_REGISTER_MAP;

typedef struct RCC_CONFIG_DESCRIPTOR {
    union {
        uint32_t BaseAddress;
        struct RCC_REGISTER_MAP* Map;
    } Register;
} RCC_CONFIG_DESCRIPTOR;


/* IEcoRCC1STM32Config IID = {21F17A28-6226-4966-A6CE-B207CDB6CB1C} */
#ifndef __IID_IEcoRCC1STM32Config
static const UGUID IID_IEcoRCC1STM32Config = { 0x01, 0x10, 0x21, 0xF1, 0x7A, 0x28, 0x62, 0x26, 0x49, 0x66, 0xA6, 0xCE, 0xB2, 0x07, 0xCD, 0xB6, 0xCB, 0x1C };
#endif /* __IID_IEcoRCC1STM32Config */

typedef struct IEcoRCC1STM32ConfigVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ struct IEcoRCC1STM32Config* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ struct IEcoRCC1STM32Config* me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ struct IEcoRCC1STM32Config* me);

    /* IEcoRCC1STM32Config */
    int16_t (ECOCALLMETHOD *set_ConfigDescriptor)(/* in */ struct IEcoRCC1STM32Config* me, /* in */ RCC_CONFIG_DESCRIPTOR* config);
    RCC_CONFIG_DESCRIPTOR* (ECOCALLMETHOD *get_ConfigDescriptor)(/* in */ struct IEcoRCC1STM32Config* me);

} IEcoRCC1STM32ConfigVTbl, *IEcoRCC1STM32ConfigVTblPtr;

interface IEcoRCC1STM32Config {
    struct IEcoRCC1STM32ConfigVTbl *pVTbl;
} IEcoRCC1STM32Config;

#endif /* __I_ECO_RCC_1_STM32_CONFIG_H__ */
