/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoUART1BCM283xConfig
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IEcoUART1BCM283xConfig
 *
 * 
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2019 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_UART_1_BCM283X_CONFIG_H__
#define __I_ECO_UART_1_BCM283X_CONFIG_H__

#include "IEcoBase1.h"

typedef union ECO_BCM283X_UART_DR_REGISTER {
    struct {
        uint32_t DATA   : 8;    /* Receive (read) data character.
                                   Transmit (write) data character */
        uint32_t FE     : 1;    /* Framing error. */
        uint32_t PE     : 1;    /* Parity error */
        uint32_t BE     : 1;    /* Break error. */
        uint32_t OE     : 1;    /* Overrun error. */
        uint32_t RES    : 20;   /* Reserved. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_DR_REGISTER;

typedef union ECO_BCM283X_UART_RSRECR_REGISTER {
    struct {
        uint32_t FE     : 1;    /* Framing error. */
        uint32_t PE     : 1;    /* Parity error */
        uint32_t BE     : 1;    /* Break error. */
        uint32_t OE     : 1;    /* Overrun error. */
        uint32_t RES    : 28;   /* Reserved. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_RSRECR_REGISTER;

typedef union ECO_BCM283X_UART_FR_REGISTER {
    struct {
        uint32_t CTS    : 1;    /* Clear to send.. */
        uint32_t DSR    : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t DCD    : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t BUSY   : 1;    /* UART busy. */
        uint32_t RXFE   : 1;    /* Receive FIFO empty. */
        uint32_t TXFF   : 1;    /* Transmit FIFO full. */
        uint32_t RXFF   : 1;    /* Receive FIFO full */
        uint32_t TXFE   : 1;    /* Transmit FIFO empty. */
        uint32_t RI     : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t RES    : 23;   /* Reserved. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_FR_REGISTER;

typedef union ECO_BCM283X_UART_ILPR_REGISTER {
    struct {
        uint32_t RES    : 32;   /* Reserved - write zero, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_ILPR_REGISTER;

typedef union ECO_BCM283X_UART_IBRD_REGISTER {
    struct {
        uint32_t IBRD   : 16;   /* The integer baud rate divisor. */
        uint32_t RES    : 16;   /* Reserved - Write as 0, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_IBRD_REGISTER;

typedef union ECO_BCM283X_UART_FBRD_REGISTER {
    struct {
        uint32_t FBRD   : 6;    /* The fractional baud rate divisor. */
        uint32_t RES    : 26;   /* Reserved - Write as 0, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_FBRD_REGISTER;

typedef union ECO_BCM283X_UART_LCRH_REGISTER {
    struct {
        uint32_t BRK    : 1;    /* Send break. */
        uint32_t PEN    : 1;    /* Parity enable. */
        uint32_t EPS    : 1;    /* Even parity select. */
        uint32_t STP2   : 1;    /* Two stop bits select. */
        uint32_t FEN    : 1;    /* Enable FIFOs. */
        uint32_t WLEN   : 2;    /* Word length. */
        uint32_t SPS    : 1;    /* Stick parity select. */
        uint32_t RES    : 24;   /* Reserved - Write as 0, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_LCRH_REGISTER;

typedef union ECO_BCM283X_UART_CR_REGISTER {
    struct {
        uint32_t UARTEN : 1;    /* UART enable. */
        uint32_t SIREN  : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t SIRLP  : 2;    /* Unsupported, write zero, read as don't care. */
        uint32_t RES1   : 4;    /* Reserved - Write as 0, read as don't care */
        uint32_t LBE    : 1;    /* Loopback enable. */
        uint32_t TXE    : 1;    /* Transmit enable. */
        uint32_t RXE    : 1;    /* Receive enable. */
        uint32_t DTR    : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t RTS    : 1;    /* Request to send. */
        uint32_t OUT1   : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t OUT2   : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t RTSEN  : 1;    /* RTS hardware flow control enable. */
        uint32_t CTSEN  : 1;    /* CTS hardware flow control enable. */
        uint32_t RES2   : 16;   /* Reserved - Write as 0, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_CR_REGISTER;

typedef union ECO_BCM283X_UART_IFLS_REGISTER {
    struct {
        uint32_t TXIFLSEL   : 3;    /* Transmit interrupt FIFO level select. */
        uint32_t RXIFLSEL   : 3;    /* Receive interrupt FIFO level select. */
        uint32_t TXIFPSEL   : 3;    /* Unsupported, write zero, read as don't care. */
        uint32_t RXIFPSEL   : 3;    /* Unsupported, write zero, read as don't care. */
        uint32_t RES        : 20;   /* Reserved - Write as 0, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_IFLS_REGISTER;

typedef union ECO_BCM283X_UART_IMSC_REGISTER {
    struct {
        uint32_t RIMIM  : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t CTSMIM : 1;    /* nUARTCTS modem interrupt mask. */
        uint32_t DCDMIM : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t DSRMIM : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t RXIM   : 1;    /* Receive interrupt mask. */
        uint32_t TXIM   : 1;    /* Transmit interrupt mask. */
        uint32_t RTIM   : 1;    /* Receive timeout interrupt mask. */
        uint32_t FEIM   : 1;    /* Framing error interrupt mask. */
        uint32_t PEIM   : 1;    /* Parity error interrupt mask. */
        uint32_t BEIM   : 2;    /* Break error interrupt mask. */
        uint32_t OEIM   : 1;    /* Overrun error interrupt mask. */
        uint32_t RES    : 21;   /* Reserved - Write as 0, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_IMSC_REGISTER;

typedef union ECO_BCM283X_UART_RIS_REGISTER {
    struct {
        uint32_t RIRMIS     : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t CTSRMIS    : 1;    /* nUARTCTS modem interrupt status. */
        uint32_t DCDRMIS    : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t DSRRMIS    : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t RXRIS      : 1;    /* Receive interrupt status. */
        uint32_t TXRIS      : 1;    /* Transmit interrupt status. */
        uint32_t RTRIS      : 1;    /* Receive timeout interrupt status. */
        uint32_t FERIS      : 1;    /* Framing error interrupt status. */
        uint32_t PERIS      : 1;    /* Parity error interrupt status. */
        uint32_t BERIS      : 1;    /* Break error interrupt status. */
        uint32_t OERIS      : 1;    /* Overrun error interrupt status. */
        uint32_t RES        : 21;   /* Reserved - Write as 0, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_RIS_REGISTER;

typedef union ECO_BCM283X_UART_MIS_REGISTER {
    struct {
        uint32_t RIMMIS     : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t CTSMMIS    : 1;    /* nUARTCTS modem masked interrupt status. */
        uint32_t DCDMMIS    : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t DSRMMIS    : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t RXMIS      : 1;    /* Receive masked interrupt status. */
        uint32_t TXMIS      : 1;    /* Transmit masked interrupt status. */
        uint32_t RTMIS      : 1;    /* Receive timeout masked interrupt status. */
        uint32_t FEMIS      : 1;    /* Framing error masked interrupt status. */
        uint32_t PEMIS      : 1;    /* Parity error masked interrupt status. */
        uint32_t BEMIS      : 1;    /* Break error masked interrupt status. */
        uint32_t OEMIS      : 1;    /* Overrun error masked interrupt status. */
        uint32_t RES        : 21;   /* Reserved - Write as 0, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_MIS_REGISTER;

typedef union ECO_BCM283X_UART_ICR_REGISTER {
    struct {
        uint32_t RIMIC      : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t CTSMIC     : 1;    /* nUARTCTS modem masked interruptstatus. */
        uint32_t DCDMIC     : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t DSRMIC     : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t RXIC       : 1;    /* Receive masked interrupt status. */
        uint32_t TXIC       : 1;    /* Transmit interrupt clear. */
        uint32_t RTIC       : 1;    /* Receive timeout interrupt clear. */
        uint32_t FEIC       : 1;    /* Framing error interrupt clear. */
        uint32_t PEIC       : 1;    /* Parity error interrupt clear. */
        uint32_t BEIC       : 1;    /* Break error interrupt clear. */
        uint32_t OEIC       : 1;    /* Overrun error interrupt clear. */
        uint32_t RES        : 21;   /* Reserved - Write as 0, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_ICR_REGISTER;

typedef union ECO_BCM283X_UART_DMACR_REGISTER {
    struct {
        uint32_t RXDMAE     : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t TXDMAE     : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t DMAONERR   : 1;    /* Unsupported, write zero, read as don't care. */
        uint32_t RES        : 29;   /* Reserved - Write as 0, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_DMACR_REGISTER;

typedef union ECO_BCM283X_UART_ITCR_REGISTER {
    struct {
        uint32_t ITCR0      : 1;    /* Integration test enable. */
        uint32_t ITCR1      : 1;    /* Test FIFO enable. */
        uint32_t RES        : 30;   /* Reserved - Write as 0, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_ITCR_REGISTER;

typedef union ECO_BCM283X_UART_ITIP_REGISTER {
    struct {
        uint32_t ITIP0      : 1;    /* Reads return the value of the UARTRXD primary input. */
        uint32_t RES1       : 2;    /* Reserved - Write as 0, read as don't care. */
        uint32_t ITIP3      : 1;    /* Reads return the value of the nUARTCTS primary input. */
        uint32_t RES2       : 28;   /* Reserved - Write as 0, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_ITIP_REGISTER;

typedef union ECO_BCM283X_UART_ITOP_REGISTER {
    struct {
        uint32_t ITOP0      : 1;    /* Primary output. */
        uint32_t RES1       : 2;    /* Reserved - Write as 0, read as don't care. */
        uint32_t ITOP3      : 1;    /* Primary output. */
        uint32_t RES2       : 2;    /* Reserved - Write as 0, read as don't care. */
        uint32_t ITOP6      : 1;    /* Intra-chip output. */
        uint32_t ITOP7      : 1;    /* Intra-chip output. */
        uint32_t ITOP8      : 1;    /* Intra-chip output. */
        uint32_t ITOP9      : 1;    /* Intra-chip output. */
        uint32_t ITOP10     : 1;    /* Intra-chip output. */
        uint32_t ITOP11     : 1;    /* Intra-chip output. */
        uint32_t RES3       : 28;   /* Reserved - Write as 0, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_ITOP_REGISTER;

typedef union ECO_BCM283X_UART_TDR_REGISTER {
    struct {
        uint32_t TDR10_0    : 11;   /* When the ITCR1 bit is set to 1, data is
                                       written into the receive FIFO and read out
                                       of the transmit FIFO. */
        uint32_t RES        : 21;   /* Reserved - Write as 0, read as don't care. */
    } bits;
    uint32_t dword;
} ECO_BCM283X_UART_TDR_REGISTER;

typedef struct ECO_BCM283X_UART_REGISTER_MAP {
    uint32_t DR;            /* Data Register,                       Address offset: 0x00      */
    uint32_t RSRECR;        /* Receive status register/error clear Register, Address offset: 0x04      */
    uint32_t RESERVED1[4];  /* Reserved,                            Address offset: 0x08-0x14 */
    uint32_t FR;            /* Flag register,                       Address offset: 0x18      */
    uint32_t RESERVED2;     /* Reserved,                            Address offset: 0x1С      */
    uint32_t ILPR;          /* not in use,                          Address offset: 0x20      */
    uint32_t IBRD;          /* Integer Baud rate divisor,           Address offset: 0x24      */
    uint32_t FBRD;          /* Fractional Baud rate divisor,        Address offset: 0x28      */
    uint32_t LCRH;          /* Line Control register,               Address offset: 0x2C      */
    uint32_t CR;            /* Control register,                    Address offset: 0x30      */
    uint32_t IFLS;          /* Interupt FIFO Level Select Register, Address offset: 0x34      */
    uint32_t IMSC;          /* Interupt Mask Set Clear Register,    Address offset: 0x38      */
    uint32_t RIS;           /* Raw Interupt Status Register,        Address offset: 0x3C      */
    uint32_t MIS;           /* Masked Interupt Status Register,     Address offset: 0x40      */
    uint32_t ICR;           /* Interupt Clear Register,             Address offset: 0x44      */
    uint32_t DMACR;         /* DMA Control Register,                Address offset: 0x48      */
    uint32_t RESERVED3[13]; /* Reserved,                            Address offset: 0x4C-0x7C */
    uint32_t ITCR;          /* Test Control register,               Address offset: 0x80      */
    uint32_t ITIP;          /* Integration test input reg,          Address offset: 0x84      */
    uint32_t ITOP;          /* Integration test output reg,         Address offset: 0x88      */
    uint32_t TDR;           /* Test Data reg,                       Address offset: 0x8C      */
} ECO_BCM283X_UART_REGISTER_MAP;

#define ECO_UART_REGISTER_MAP ECO_BCM283X_UART_REGISTER_MAP

typedef struct ECO_UART_CONFIG_DESCRIPTOR {
    union {
        uint32_t BaseAddress;
        struct ECO_UART_REGISTER_MAP* Map;
    } Register;
    uint32_t Fclk;
} ECO_UART_CONFIG_DESCRIPTOR;

/* IEcoUART1BCM283xConfig IID = {A1EC7F56-6538-454B-A186-6D34922E64DA} */
#ifndef __IID_IEcoUART1BCM283xConfig
static const UGUID IID_IEcoUART1BCM283xConfig = { 0x01, 0x10, {0xA1, 0xEC, 0x7F, 0x56, 0x65, 0x38, 0x45, 0x4B, 0xA1, 0x86, 0x6D, 0x34, 0x92, 0x2E, 0x64, 0xDA}};
#endif /* __IID_IEcoUART1BCM283xConfig */

typedef struct IEcoUART1BCM283xConfig* IEcoUART1BCM283xConfigPtr_t;

typedef struct IEcoUART1BCM283xConfigVTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ IEcoUART1BCM283xConfigPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (*AddRef)(/* in */ IEcoUART1BCM283xConfigPtr_t me);
    uint32_t (*Release)(/* in */ IEcoUART1BCM283xConfigPtr_t me);

    /* IEcoUART1BCM283xConfig */
    int16_t (*set_ConfigDescriptor)(/* in */ IEcoUART1BCM283xConfigPtr_t me, /* in */ ECO_UART_CONFIG_DESCRIPTOR* config);
    ECO_UART_CONFIG_DESCRIPTOR* (*get_ConfigDescriptor)(/* in */ IEcoUART1BCM283xConfigPtr_t me);

} IEcoUART1BCM283xConfigVTbl, *IEcoUART1BCM283xConfigVTblPtr;

interface IEcoUART1BCM283xConfig {
    struct IEcoUART1BCM283xConfigVTbl *pVTbl;
} IEcoUART1BCM283xConfig;

#endif /* __I_ECO_UART_1_BCM283X_CONFIG_H__ */
