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


// typedef struct ECO_STM32_UART_REGISTER_MAP {
//     uint32_t BaudRate;                  /*!< This member configures the UART communication baud rate.
//         The baud rate is computed using the following formula:
//         - IntegerDivider = ((PCLKx) / (8 * (OVR8+1) * (huart->Init.BaudRate)))
//         - FractionalDivider = ((IntegerDivider - ((uint32_t) IntegerDivider)) * 8 * (OVR8+1)) + 0.5
//         Where OVR8 is the "oversampling by 8 mode" configuration bit in the CR1 register. */
//     uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
//         This parameter can be a value of @ref UART_Word_Length */
//     uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
//         This parameter can be a value of @ref UART_Stop_Bits */
//     uint32_t Parity;                    /*!< Specifies the parity mode.
//         This parameter can be a value of @ref UART_Parity
//         @note When parity is enabled, the computed parity is inserted
//         at the MSB position of the transmitted data (9th bit when
//         the word length is set to 9 data bits; 8th bit when the
//         word length is set to 8 data bits). */
//     uint32_t Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
//         This parameter can be a value of @ref UART_Mode */
//     uint32_t HwFlowCtl;                 /*!< Specifies whether the hardware flow control mode is enabled or disabled.
//         This parameter can be a value of @ref UART_Hardware_Flow_Control */
//     uint32_t OverSampling;              /*!< Specifies whether the Over sampling 8 is enabled or disabled, to achieve higher speed (up to fPCLK/8).
//         This parameter can be a value of @ref UART_Over_Sampling */
// } ECO_STM32_UART_REGISTER_MAP;

typedef struct ECO_STM32_UART_REGISTER_MAP
{
  uint32_t SR;         /*!< USART Status register,                   Address offset: 0x00 */
  uint32_t DR;         /*!< USART Data register,                     Address offset: 0x04 */
  uint32_t BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
  uint32_t CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
  uint32_t CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
  uint32_t CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
  uint32_t GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
} ECO_STM32_UART_REGISTER_MAP;

#define ECO_UART_REGISTER_MAP ECO_STM32_UART_REGISTER_MAP

typedef struct ECO_UART_CONFIG_DESCRIPTOR {
    union {
        uint32_t BaseAddress;
        struct ECO_STM32_UART_REGISTER_MAP* Map;
    } Register;
    uint32_t Fclk;
} ECO_UART_CONFIG_DESCRIPTOR;

typedef struct IEcoUART1STM32F4Config* IEcoUART1STM32F4ConfigPtr_t;

/* IEcoUART1STM32F4Config IID = { 45B766B1-B836-4345-BFF2-69BF659FD3DC } */
#ifndef __IID_IEcoUART1STM32F4Config
static const UGUID IID_IEcoUART1STM32F4Config = { 0x01, 0x10, {0x45, 0xB7, 0x66, 0xB1, 0xB8, 0x36, 0x43, 0x45, 0xBF, 0xF2, 0x69, 0xBF, 0x65, 0x9F, 0xD3, 0xDC} };
#endif /* __IID_IEcoUART1STM32F4Config */

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
