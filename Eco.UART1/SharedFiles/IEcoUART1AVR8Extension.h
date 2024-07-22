/*
 * <кодировка символов>
 *   Cyrillic (Windows) - Codepage 1251
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoUART1AVR8Extension
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoUART1AVR8Extension
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

#ifndef __ID_ECO_UART_1_AVR_8_EXTENSION_H__
#define __ID_ECO_UART_1_AVR_8_EXTENSION_H__

#include "IEcoBase1.h"
#include "IEcoUART1.h"

typedef struct tagAVR8UARTPORTINFO {
    uint8_t DataRegisterAddress; // UDR0
    uint8_t DataDirectionRegisterAddress;
    uint8_t InputPinsAddress;
    uint8_t BoundRateRegisterHighAddress;
    uint8_t BoundRateRegisterLowAddress;
    uint8_t ControlStatusRegisterAAddress;
    uint8_t ControlStatusRegisterBAddress;
    uint8_t ControlStatusRegisterCAddress;
    uint8_t TxPin;
    uint8_t RxPin;
    bool_t HardwareEnabled;
} AVR8UARTPORTINFO;


/* IEcoUART1AVR8Extension IID = {707F7730-0FA9-4B6D-8716-CF196316C928} */
#ifndef __IID_IEcoUART1AVR8Extension
static const UGUID IID_IEcoUART1AVR8Extension = {0x01, 0x10, 0x70, 0x7F, 0x77, 0x30, 0x0F, 0xA9, 0x4B, 0x6D, 0x87, 0x16, 0xCF, 0x19, 0x63, 0x16, 0xC9, 0x28};
#endif /* __IID_IEcoUART1AVR8Extension */

typedef struct IEcoUART1AVR8ExtensionVTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ struct IEcoUART1AVR8Extension* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ struct IEcoUART1AVR8Extension* me);
    uint32_t (*Release)(/* in */ struct IEcoUART1AVR8Extension* me);

    /* IEcoUART1AVR8Extension */
    AVR8UARTPORTINFO* (*get_PortInfo)(/* in */ struct IEcoUART1AVR8Extension* me);

} IEcoUART1AVR8ExtensionVTbl, *IEcoUART1AVR8ExtensionVTblPtr;

interface IEcoUART1AVR8Extension {
    struct IEcoUART1AVR8ExtensionVTbl *pVTbl;
} IEcoUART1AVR8Extension;

#endif /* __ID_ECO_UART_1_AVR_8_EXTENSION_H__ */
