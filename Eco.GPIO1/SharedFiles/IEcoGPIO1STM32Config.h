/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoGPIO1STM32Config
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoGPIO1STM32Config
 *
 * 
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2019 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_GPIO_1_STM32_CONFIG_H__
#define __I_ECO_GPIO_1_STM32_CONFIG_H__

#include "IEcoBase1.h"

typedef struct GPIO_REGISTER_MAP {
    uint32_t MODER;    /* GPIO port mode register,               Address offset: 0x00      */
    uint32_t OTYPER;   /* GPIO port output type register,        Address offset: 0x04      */
    uint32_t OSPEEDR;  /* GPIO port output speed register,       Address offset: 0x08      */
    uint32_t PUPDR;    /* GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
    uint32_t IDR;      /* GPIO port input data register,         Address offset: 0x10      */
    uint32_t ODR;      /* GPIO port output data register,        Address offset: 0x14      */
    uint32_t BSRR;     /* GPIO port bit set/reset register,      Address offset: 0x18      */
    uint32_t LCKR;     /* GPIO port configuration lock register, Address offset: 0x1C      */
    uint32_t AFR[2];   /* GPIO alternate function registers,     Address offset: 0x20-0x24 */
} GPIO_REGISTER_MAP;

typedef struct ECO_GPIO_CONFIG_DESCRIPTOR {
    union {
        uint32_t BaseAddress;
        struct GPIO_REGISTER_MAP* Map;
    } Register;
    uint8_t LogicalPinMask[16];
} ECO_GPIO_CONFIG_DESCRIPTOR;

/* IEcoGPIO1STM32Config IID = {D9671208-DCAD-4448-90AA-5F4825055DFA} */
#ifndef __IID_IEcoGPIO1STM32Config
static const UGUID IID_IEcoGPIO1STM32Config = { 0x01, 0x10, 0xD9, 0x67, 0x12, 0x08, 0xDC, 0xAD, 0x44, 0x48, 0x90, 0xAA, 0x5F, 0x48, 0x25, 0x05, 0x5D, 0xFA };
#endif /* __IID_IEcoGPIO1STM32Config */

typedef struct IEcoGPIO1STM32Config* IEcoGPIO1STM32ConfigPtr_t;

typedef struct IEcoGPIO1STM32ConfigVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoGPIO1STM32ConfigPtr_t me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoGPIO1STM32ConfigPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoGPIO1STM32ConfigPtr_t me);

    /* IEcoGPIO1STM32Config */
    int16_t (ECOCALLMETHOD *set_ConfigDescriptor)(/* in */ IEcoGPIO1STM32ConfigPtr_t me, /* in */ uint8_t PortNumber, /* in */ ECO_GPIO_CONFIG_DESCRIPTOR* config);
    ECO_GPIO_CONFIG_DESCRIPTOR* (ECOCALLMETHOD *get_ConfigDescriptor)(/* in */ IEcoGPIO1STM32ConfigPtr_t me, /* in */ uint8_t PortNumber);
    int16_t (ECOCALLMETHOD *set_LogicalPinNumber)(/* in */ IEcoGPIO1STM32ConfigPtr_t me, /* in */ uint8_t LogicalPinNumber, /* in */ uint8_t PortNumber, /* in */ uint16_t PinNumber);

} IEcoGPIO1STM32ConfigVTbl, *IEcoGPIO1STM32ConfigVTblPtr;

interface IEcoGPIO1STM32Config {
    struct IEcoGPIO1STM32ConfigVTbl *pVTbl;
} IEcoGPIO1STM32Config;

#endif /* __I_ECO_GPIO_1_STM32_CONFIG_H__ */
