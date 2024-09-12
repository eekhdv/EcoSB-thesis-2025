/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoGPIO1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoGPIO1
 *
 * 
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2019 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_GPIO_1_H__
#define __I_ECO_GPIO_1_H__

#include "IEcoBase1.h"

#define GPIO_MODE_INPUT     0x0UL
#define GPIO_MODE_OUTPUT    0x1UL
#define GPIO_MODE_AF        0x2UL
#define GPIO_MODE_ANALOG    0x3UL

/* IEcoGPIO1 IID = {96EBAA04-7B4E-4BDE-914D-8C3C57F48F2F} */
#ifndef __IID_IEcoGPIO1
static const UGUID IID_IEcoGPIO1 = { 0x01, 0x10, 0x96, 0xeb, 0xaa, 0x04, 0x7b, 0x4e, 0x4b, 0xde, 0x91, 0x4d, 0x8c, 0x3c, 0x57, 0xf4, 0x8f, 0x2f };
#endif /* __IID_IEcoGPIO1 */

typedef struct IEcoGPIO1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ struct IEcoGPIO1* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ struct IEcoGPIO1* me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ struct IEcoGPIO1* me);

    /* IEcoGPIO1 */
    int16_t (ECOCALLMETHOD *set_Mode)(/* in */ struct IEcoGPIO1* me, /* in */ uint16_t LogicalPinNumber, /* in */ uint8_t mode);
    int16_t (ECOCALLMETHOD *set_Data)(/* in */ struct IEcoGPIO1* me, /* in */ uint16_t LogicalPinNumber, /* in */ uint8_t Value);
    int16_t (ECOCALLMETHOD *get_Data)(/* in */ struct IEcoGPIO1* me, /* in */ uint16_t LogicalPinNumber, /* in | out */ uint8_t *pValue);

} IEcoGPIO1VTbl, *IEcoGPIO1VTblPtr;

interface IEcoGPIO1 {
    struct IEcoGPIO1VTbl *pVTbl;
} IEcoGPIO1;

#endif /* __I_ECO_GPIO_1_H__ */
