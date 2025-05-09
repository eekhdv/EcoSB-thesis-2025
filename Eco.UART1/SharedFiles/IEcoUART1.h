/*
 * <кодировка символов>
 *   Cyrillic (Windows) - Codepage 1251
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoUART1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoUART1
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

#ifndef __I_ECO_UART_1_H__
#define __I_ECO_UART_1_H__

#include "IEcoBase1.h"

/* Baud Rate */
#define ECO_UART_BR_110     110     /* 110 bps */
#define ECO_UART_BR_300     300     /* 300 bps */
#define ECO_UART_BR_600     600     /* 600 bps */
#define ECO_UART_BR_1200    1200    /* 1200 bps */
#define ECO_UART_BR_2400    2400    /* 2400 bps */
#define ECO_UART_BR_4800    4800    /* 4800 bps */
#define ECO_UART_BR_9600    9600    /* 9600 bps */
#define ECO_UART_BR_14400   14400   /* 14400 bps */
#define ECO_UART_BR_19200   19200   /* 19200 bps */
#define ECO_UART_BR_38400   38400   /* 38400 bps */
#define ECO_UART_BR_57600   57600   /* 57600 bps */
#define ECO_UART_BR_115200  115200  /* 115200 bps */
#define ECO_UART_BR_128000  128000  /* 128000 bps */
#define ECO_UART_BR_256000  256000  /* 256000 bps */

/* Parity */
#define ECO_UART_ONE_STOP_BIT       0   /* 1 stop bit. */
#define ECO_UART_ONE_5_STOP_BITS    1   /* 1.5 stop bits. */
#define ECO_UART_TWO_STOP_BITS      2   /* 2 stop bits. */

/* Parity */
#define ECO_UART_NO_PARITY      0   /* No parity. */
#define ECO_UART_ODD_PARITY     1   /* Odd parity. */
#define ECO_UART_EVEN_PARITY    2   /* Even parity. */
#define ECO_UART_MARK_PARITY    3   /* Mark parity. */
#define ECO_UART_SPACE_PARITY   4   /* Space parity. */

#define OUTPUT_PP                     0x0UL << 4U
#define USART_CR1_UE                  0x00002000                         /*!<USART Enable                           */
#define USART_CR2_STOP                0x00003000                         /*!<STOP[1:0] bits (STOP bits) */
#define UART_WORDLENGTH_8B            0x00000000U
#define UART_STOPBITS_1               0x00000000U
#define UART_PARITY_NONE              0x00000000U
#define UART_OVERSAMPLING_16          0x00000000U
#define USART_CR1_PCE                 0x00000400UL                       /*!<Parity Control Enable                  */
#define USART_CR1_M                   0x00001000UL                       /*!<Word length                            */
#define USART_CR1_PS                  0x00000200UL                       /*!<Parity Selection                       */
#define USART_CR1_OVER8               0x00008000UL                       /*!<USART Oversampling by 8 enable         */
#define UART_HWCONTROL_NONE           0x00000000U
#define USART_CR3_RTSE                0x00000100UL                       /*!<RTS Enable                  */

#define USART_CR1_RE                  0x00000004U                        /*!<Receiver Enable                        */
#define UART_MODE_RX                  ((uint32_t)USART_CR1_RE)
#define UART_MODE_TX                  ((uint32_t)USART_CR1_TE)
#define UART_MODE_TX_RX               ((uint32_t)(USART_CR1_TE | USART_CR1_RE))

#define USART_CR3_CTSE                0x00000200UL                       /*!<CTS Enable                  */
#define USART_CR1_RXNEIE              0x00000020UL                       /*!<RXNE Interrupt Enable                  */
#define USART_CR1_PEIE                0x00000100UL                       /*!<PE Interrupt Enable                    */
#define USART_SR_RXNE                 0x00000020UL                       /*!<Read Data Register Not Empty */
#define USART_SR_TXE                  0x00000080UL                       /*!<Transmit Data Register Empty */
#define USART_CR1_TXEIE               0x00000080UL                       /*!<TXE Interrupt Enable                   */
#define USART_CR3_EIE                 0x00000001UL                       /*!<Error Interrupt Enable      */
#define USART_SR_TC                   0x00000040UL                       /*!<Transmission Complete        */


typedef struct ECO_UART_1_CONFIG {
    uint32_t    BaudRate;
    uint8_t     DataBits;
    uint8_t     StopBits;
    uint8_t     Parity;
#if defined (ECO_STM32) || defined(STM32F407xx)
    uint8_t    WordLength  ;
    uint32_t    Mode        ;
    uint8_t    Oversampling; 
    uint8_t    HwControl   ;
#endif /* ECO_STM32 */
} ECO_UART_1_CONFIG;

/* IEcoUART1Device IID = {6B754B24-7D03-435B-B5E2-2165A2041862} */
#ifndef __IID_IEcoUART1Device
static const UGUID IID_IEcoUART1Device = {0x01, 0x10, {0x6B, 0x75, 0x4B, 0x24, 0x7D, 0x03, 0x43, 0x5B, 0xB5, 0xE2, 0x21, 0x65, 0xA2, 0x04, 0x18, 0x62}};
#endif /* __IID_IEcoUART1Device */

typedef struct IEcoUART1Device* IEcoUART1DevicePtr_t;

typedef struct IEcoUART1DeviceVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoUART1DevicePtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoUART1DevicePtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoUART1DevicePtr_t me);

    /* IEcoUART1Device */
    int16_t (ECOCALLMETHOD *Connect)(/* in */ IEcoUART1DevicePtr_t me, /* in */ ECO_UART_1_CONFIG* config);
    int16_t (ECOCALLMETHOD *Disconnect)(/* in */ IEcoUART1DevicePtr_t me);
    int16_t (ECOCALLMETHOD *Transmit)(/* in */ IEcoUART1DevicePtr_t me, /* in */ byte_t data);
    int16_t (ECOCALLMETHOD *Receive)(/* in */ IEcoUART1DevicePtr_t me, /* out */ byte_t* data);

} IEcoUART1DeviceVTbl, *IEcoUART1DeviceVTblPtr;

interface IEcoUART1Device {
    struct IEcoUART1DeviceVTbl *pVTbl;
} IEcoUART1Device;

/* IEcoUART1 IID = {A82B703D-A9BD-453C-9A2B-8A16F71F1BEC} */
#ifndef __IID_IEcoUART1
static const UGUID IID_IEcoUART1 = {0x01, 0x10, {0xA8, 0x2B, 0x70, 0x3D, 0xA9, 0xBD, 0x45, 0x3C, 0x9A, 0x2B, 0x8A, 0x16, 0xF7, 0x1F, 0x1B, 0xEC}};
#endif /* __IID_IEcoUART1 */

typedef struct IEcoUART1* IEcoUART1Ptr_t;

typedef struct IEcoUART1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoUART1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoUART1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoUART1Ptr_t me);

    /* IEcoUART1 */
    int16_t (ECOCALLMETHOD *new_Device)(/* in */ IEcoUART1Ptr_t me, /* out */ IEcoUART1DevicePtr_t* ppIDevice);

} IEcoUART1VTbl, *IEcoUART1VTblPtr;

interface IEcoUART1 {
    struct IEcoUART1VTbl *pVTbl;
} IEcoUART1;

#endif /* __I_ECO_UART_1_H__ */
