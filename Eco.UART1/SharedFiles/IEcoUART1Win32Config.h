/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoUART1WIN32Config
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoUART1WIN32Config
 *
 * 
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2019 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_UART_1_WIN32_CONFIG_H__
#define __I_ECO_UART_1_WIN32_CONFIG_H__

#include "IEcoBase1.h"

typedef struct ECO_UART_CONFIG_DESCRIPTOR {
    char_t*         lpszName;   /* The name of the device. For example, COM1 through COM9 */
    void*           lpCC;       /* A pointer to a COMMCONFIG structure. */
    uint32_t        dwSize;     /* The size of the structure pointed to by lpCC, in bytes. */
} ECO_UART_CONFIG_DESCRIPTOR;

/* IEcoUART1WIN32Config IID = {5A72857A-AEEA-4BF5-AAB4-B692A4BE3FAA} */
#ifndef __IID_IEcoUART1WIN32Config
static const UGUID IID_IEcoUART1WIN32Config = { 0x01, 0x10, 0x5A, 0x72, 0x85, 0x7A, 0xAE, 0xEA, 0x4B, 0xF5, 0xAA, 0xB4, 0xB6, 0x92, 0xA4, 0xBE, 0x3F, 0xAA };
#endif /* __IID_IEcoUART1WIN32Config */

typedef struct IEcoUART1WIN32ConfigVTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ struct IEcoUART1WIN32Config* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ struct IEcoUART1WIN32Config* me);
    uint32_t (*Release)(/* in */ struct IEcoUART1WIN32Config* me);

    /* IEcoUART1WIN32Config */
    int16_t (*set_ConfigDescriptor)(/* in */ struct IEcoUART1WIN32Config* me, /* in */ ECO_UART_CONFIG_DESCRIPTOR* config);
    ECO_UART_CONFIG_DESCRIPTOR* (*get_ConfigDescriptor)(/* in */ struct IEcoUART1WIN32Config* me);

} IEcoUART1WIN32ConfigVTbl, *IEcoUART1WIN32ConfigVTblPtr;

interface IEcoUART1WIN32Config {
    struct IEcoUART1WIN32ConfigVTbl *pVTbl;
} IEcoUART1WIN32Config;

#endif /* __I_ECO_UART_1_WIN32_CONFIG_H__ */
