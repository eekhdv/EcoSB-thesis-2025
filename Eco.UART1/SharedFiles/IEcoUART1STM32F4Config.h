/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoUART1STM32F4Config
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoUART1STM32F4Config
 *
 * 
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2019 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_UART_1_STM32F4_CONFIG_H__
#define __I_ECO_UART_1_STM32F4_CONFIG_H__

#include "IEcoBase1.h"


/* IEcoUART1STM32F4Config IID = { 45B766B1-B836-4345-BFF2-69BF659FD3DC } */
#ifndef __IID_IEcoUART1STM32F4Config
static const UGUID IID_IEcoUART1STM32F4Config = { 0x01, 0x10, 0x45, 0xB7, 0x66, 0xB1, 0xB8, 0x36, 0x43, 0x45, 0xBF, 0xF2, 0x69, 0xBF, 0x65, 0x9F, 0xD3, 0xDC };
#endif /* __IID_IEcoUART1STM32F4Config */

typedef struct ECO_STM32_UART_REGISTER_MAP {
    uint32_t SR;            /*!< USART Status register,                   Address offset: 0x00 */
    uint32_t DR;            /*!< USART Data register,                     Address offset: 0x04 */
    uint32_t BRR;           /*!< USART Baud rate register,                Address offset: 0x08 */
    uint32_t CR1;           /*!< USART Control register 1,                Address offset: 0x0C */
    uint32_t CR2;           /*!< USART Control register 2,                Address offset: 0x10 */
    uint32_t CR3;           /*!< USART Control register 3,                Address offset: 0x14 */
    uint32_t GTPR;          /*!< USART Guard time and prescaler register, Address offset: 0x18 */
    uint32_t CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
    uint32_t PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
    uint32_t CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
    uint32_t CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
    uint32_t AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
    uint32_t AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
    uint32_t AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
    uint32_t      RESERVED0;     /*!< Reserved, 0x1C                                                                    */
    uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
    uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
    uint32_t      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
    uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
    uint32_t AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
    uint32_t AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
    uint32_t      RESERVED2;     /*!< Reserved, 0x3C                                                                    */
    uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
    uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
    uint32_t      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
    uint32_t AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
    uint32_t AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
    uint32_t AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
    uint32_t      RESERVED4;     /*!< Reserved, 0x5C                                                                    */
    uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
    uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
    uint32_t      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
    uint32_t BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
    uint32_t CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
    uint32_t      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
    uint32_t SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
    uint32_t PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
} ECO_STM32_UART_REGISTER_MAP;

#define ECO_UART_REGISTER_MAP ECO_STM32_UART_REGISTER_MAP

typedef struct ECO_UART_CONFIG_DESCRIPTOR {
    union {
        uint32_t BaseAddress;
        struct ECO_UART_REGISTER_MAP* Map;
    } Register;
    uint32_t Fclk;
} ECO_UART_CONFIG_DESCRIPTOR;

typedef struct IEcoUART1STM32F4Config* IEcoUART1STM32F4ConfigPtr_t;

typedef struct IEcoUART1STM32F4ConfigVTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ IEcoUART1STM32F4ConfigPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (*AddRef)(/* in */ IEcoUART1STM32F4ConfigPtr_t me);
    uint32_t (*Release)(/* in */ IEcoUART1STM32F4ConfigPtr_t me);

    /* IEcoUART1STM32F4Config */
    int16_t (*set_ConfigDescriptor)(/* in */ IEcoUART1STM32F4ConfigPtr_t me, /* in */ ECO_UART_CONFIG_DESCRIPTOR* config);
    ECO_UART_CONFIG_DESCRIPTOR* (*get_ConfigDescriptor)(/* in */ IEcoUART1STM32F4ConfigPtr_t me);

} IEcoUART1STM32F4ConfigVTbl, *IEcoUART1STM32F4ConfigVTblPtr;

interface IEcoUART1STM32F4Config {
    struct IEcoUART1STM32F4ConfigVTbl *pVTbl;
} IEcoUART1STM32F4Config;

#endif /* __I_ECO_UART_1_STM32F4_CONFIG_H__ */
