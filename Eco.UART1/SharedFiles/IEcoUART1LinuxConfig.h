/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoUART1LINUXConfig
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoUART1LINUXConfig
 *
 * 
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2019 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_UART_1_LINUX_CONFIG_H__
#define __I_ECO_UART_1_LINUX_CONFIG_H__

#include "IEcoBase1.h"

#define I_ECO_UART_MAX_LINUX_DEVICE_NAME_LENGTH 15

typedef struct ECO_UART_CONFIG_DESCRIPTOR {
    uint8_t  slaveFlag; /* 1 if slave, 0 if master */
    byte_t   devName[I_ECO_UART_MAX_LINUX_DEVICE_NAME_LENGTH]; /* Имя девайса в /dev */
} ECO_UART_CONFIG_DESCRIPTOR;

/* IEcoUART1LinuxConfig IID = {057C9F95-D2D5-4489-A36C-CFC7561254C5} */

#ifndef __IID_IEcoUART1LinuxConfig
static const UGUID IID_IEcoUART1LinuxConfig = { 0x01, 0x10, 0x05, 0x7C, 0x9F, 0x95, 0xD2, 0xD5, 0x44, 0x89, 0xA3, 0x6C, 0xCF, 0xC7, 0x56, 0x12, 0x54, 0xC5 };
#endif /* __IID_IEcoUART1LinuxConfig */

typedef struct IEcoUART1LinuxConfig* IEcoUART1LinuxConfigPtr_t;

typedef struct IEcoUART1LinuxConfigVTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ IEcoUART1LinuxConfigPtr_t me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ IEcoUART1LinuxConfigPtr_t me);
    uint32_t (*Release)(/* in */ IEcoUART1LinuxConfigPtr_t me);

    /* IEcoUART1LinuxConfig */
    int16_t (*set_ConfigDescriptor)(/* in */ struct IEcoUART1LinuxConfig* me, /* in */ ECO_UART_CONFIG_DESCRIPTOR* config);
    ECO_UART_CONFIG_DESCRIPTOR* (*get_ConfigDescriptor)(/* in */ struct IEcoUART1LinuxConfig* me);

} IEcoUART1LinuxConfigVTbl, *IEcoUART1LinuxConfigVTblPtr;

interface IEcoUART1LinuxConfig {
    struct IEcoUART1LinuxConfigVTbl *pVTbl;
} IEcoUART1LinuxConfig;

#endif /* __I_ECO_UART_1_Linux_CONFIG_H__ */
