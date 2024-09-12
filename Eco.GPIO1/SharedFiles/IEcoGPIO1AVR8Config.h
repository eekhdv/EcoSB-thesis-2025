/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoGPIO1AVR8Config
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoGPIO1AVR8Config
 *
 * 
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2019 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_GPIO_1_AVR8_CONFIG_H__
#define __I_ECO_GPIO_1_AVR8_CONFIG_H__

#include "IEcoBase1.h"

typedef struct ECO_AVR8_GPIO_REGISTER_MAP {
    uint8_t PIN;   /* GPIO port Input Pins Address,         Address offset: 0x00      */
    uint8_t DDR;   /* GPIO port Data Direction Register,    Address offset: 0x01      */
    uint8_t PORT;  /* GPIO port Data Register,              Address offset: 0x02      */
} ECO_AVR8_GPIO_REGISTER_MAP;

#define ECO_GPIO_REGISTER_MAP ECO_AVR8_GPIO_REGISTER_MAP

typedef struct ECO_GPIO_CONFIG_DESCRIPTOR {
    union {
        uint16_t BaseAddress;
        struct ECO_GPIO_REGISTER_MAP* Map;
    } Register;
    uint8_t LogicalPinMask[8];
} ECO_GPIO_CONFIG_DESCRIPTOR;

/* IEcoGPIO1AVR8Config IID = {4FAE0B1A-4A55-4023-9620-F4699347A07F} */
#ifndef __IID_IEcoGPIO1AVR8Config
static const UGUID IID_IEcoGPIO1AVR8Config = { 0x01, 0x10, 0x4F, 0xAE, 0x0B, 0x1A, 0x4A, 0x55, 0x40, 0x23, 0x96, 0x20, 0xF4, 0x69, 0x93, 0x47, 0xA0, 0x7F };
#endif /* __IID_IEcoGPIO1AVR8Config */

typedef struct IEcoGPIO1AVR8ConfigVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ struct IEcoGPIO1AVR8Config* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ struct IEcoGPIO1AVR8Config* me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ struct IEcoGPIO1AVR8Config* me);

    /* IEcoGPIO1AVR8Config */
    int16_t (ECOCALLMETHOD *set_ConfigDescriptor)(/* in */ struct IEcoGPIO1AVR8Config* me, /* in */ uint8_t PortNumber, /* in */ ECO_GPIO_CONFIG_DESCRIPTOR* config);
    ECO_GPIO_CONFIG_DESCRIPTOR* (ECOCALLMETHOD *get_ConfigDescriptor)(/* in */ struct IEcoGPIO1AVR8Config* me, /* in */ uint8_t PortNumber);
    int16_t (ECOCALLMETHOD *set_LogicalPinNumber)(/* in */ struct IEcoGPIO1AVR8Config* me, /* in */ uint8_t LogicalPinNumber, /* in */ uint8_t PortNumber, /* in */ uint8_t PinNumber);

} IEcoGPIO1AVR8ConfigVTbl, *IEcoGPIO1AVR8ConfigVTblPtr;

interface IEcoGPIO1AVR8Config {
    struct IEcoGPIO1AVR8ConfigVTbl *pVTbl;
} IEcoGPIO1AVR8Config;

#endif /* __I_ECO_GPIO_1_AVR8_CONFIG_H__ */
