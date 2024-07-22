/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoUART1AVR8Config
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoUART1AVR8Config
 *
 * 
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2019 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_UART_1_AVR8_CONFIG_H__
#define __I_ECO_UART_1_AVR8_CONFIG_H__

#include "IEcoBase1.h"

typedef union ECO_AVR8_UART_IO_DATA_REGISTER {
    union {
        uint8_t RXB;                /* Receive Data Buffer Registers. */
        uint8_t TXB;                /* Transmit Data Buffer Register. */
    } bits;
    uint8_t byte;
} ECO_AVR8_UART_IO_DATA_REGISTER;

typedef union ECO_AVR8_UART_CONTROL_STATUS_REGISTER_A {
    struct {
        uint8_t MPCMn       : 1;    /* Multi-processor Communication Mode */
        uint8_t U2Xn        : 1;    /* Double the USART Transmission Speed. */
        uint8_t UPEn        : 1;    /* USART Parity Error */
        uint8_t DORn        : 1;    /* Data OverRun. */
        uint8_t FEn         : 1;    /* Frame Error. */
        uint8_t UDREn       : 1;    /* USART Data Register Empty. */
        uint8_t TXCn        : 1;    /* USART Transmit Complete */
        uint8_t RXCn        : 1;    /* USART Receive Complete */
    } bits;
    uint8_t byte;
} ECO_AVR8_UART_CONTROL_STATUS_REGISTER_A;

typedef union ECO_AVR8_UART_CONTROL_STATUS_REGISTER_B {
    struct {
        uint8_t TXB8n       : 1;    /* Transmit Data Bit 8 n */
        uint8_t RXB8n       : 1;    /* Receive Data Bit 8 n */
        uint8_t UCSZn2      : 1;    /* Character Size n */
        uint8_t TXENn       : 1;    /* Transmitter Enable n. */
        uint8_t RXENn       : 1;    /* Receiver Enable n. */
        uint8_t UDRIEn      : 1;    /* USART Data Register Empty Interrupt Enable n. */
        uint8_t TXCIEn      : 1;    /* TX Complete Interrupt Enable n */
        uint8_t RXCIEn      : 1;    /* RX Complete Interrupt Enable n */
    } bits;
    uint8_t byte;
} ECO_AVR8_UART_CONTROL_STATUS_REGISTER_B;

typedef union ECO_AVR8_UART_CONTROL_STATUS_REGISTER_C {
    struct {
        uint8_t UCPOLn      : 1;    /* Clock Polarity */
        uint8_t UCSZn       : 2;    /* Receiver Enable n. */
        uint8_t USBSn       : 1;    /* Stop Bit Select */
        uint8_t UPMn        : 2;    /* Parity Mode */
        uint8_t UMSELn      : 2;    /* USART Mode Select */
    } bits;
    uint8_t byte;
} ECO_AVR8_UART_CONTROL_STATUS_REGISTER_C;


typedef union ECO_AVR8_UART_BAUD_RATE_REGISTER {
    struct {
        uint16_t UBRR       : 12;   /* USART Baud Rate Register. */
        uint16_t RES        : 4;    /* Reserved. */
    } bits;
    uint16_t word;
} ECO_AVR8_UART_BAUD_RATE_REGISTER;

typedef struct ECO_AVR8_UART_REGISTER_MAP {
    uint8_t UCSRnA;     /* USART Control and Status Register n A,       Address offset: 0x00      */
    uint8_t UCSRnB;     /* USART Control and Status Register n B,       Address offset: 0x01      */
    uint8_t UCSRnC;     /* USART Control and Status Register n C,       Address offset: 0x02      */
    uint8_t RES;        /* Reserved,                                    Address offset: 0x03      */
    uint8_t UBRRnL;     /* USART Low Baud Rate Register,                Address offset: 0x04      */
    uint8_t UBRRnH;     /* USART High Baud Rate Register,               Address offset: 0x05      */
    uint8_t UDRn;       /* USART I/O Data Register n,                   Address offset: 0x06      */
} ECO_AVR8_UART_REGISTER_MAP;

#define ECO_UART_REGISTER_MAP ECO_AVR8_UART_REGISTER_MAP

typedef struct ECO_UART_CONFIG_DESCRIPTOR {
    union {
        uint16_t BaseAddress;
        struct ECO_UART_REGISTER_MAP* Map;
    } Register;
    uint32_t Fosc;
} ECO_UART_CONFIG_DESCRIPTOR;

/* IEcoUART1AVR8Config IID = {C04E2997-A52A-4848-97FF-8A43EBB1CBCC} */
#ifndef __IID_IEcoUART1AVR8Config
static const UGUID IID_IEcoUART1AVR8Config = { 0x01, 0x10, {0xC0, 0x4E, 0x29, 0x97, 0xA5, 0x2A, 0x48, 0x48, 0x97, 0xFF, 0x8A, 0x43, 0xEB, 0xB1, 0xCB, 0xCC}};
#endif /* __IID_IEcoUART1AVR8Config */


typedef struct IEcoUART1AVR8Config* IEcoUART1AVR8ConfigPtr_t;

typedef struct IEcoUART1AVR8ConfigVTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ IEcoUART1AVR8ConfigPtr_t me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ IEcoUART1AVR8ConfigPtr_t me);
    uint32_t (*Release)(/* in */ IEcoUART1AVR8ConfigPtr_t me);

    /* IEcoUART1AVR8Config */
    int16_t (*set_ConfigDescriptor)(/* in */ IEcoUART1AVR8ConfigPtr_t me, /* in */ ECO_UART_CONFIG_DESCRIPTOR* config);
    ECO_UART_CONFIG_DESCRIPTOR* (*get_ConfigDescriptor)(/* in */ IEcoUART1AVR8ConfigPtr_t me);

} IEcoUART1AVR8ConfigVTbl, *IEcoUART1AVR8ConfigVTblPtr;

interface IEcoUART1AVR8Config {
    struct IEcoUART1AVR8ConfigVTbl *pVTbl;
} IEcoUART1AVR8Config;

#endif /* __I_ECO_UART_1_AVR8_CONFIG_H__ */
