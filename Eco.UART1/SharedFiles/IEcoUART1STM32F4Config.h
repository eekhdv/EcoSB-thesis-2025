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
//
#define ECO_RESET 0x0
#define ECO_SET   0x1

#define RCC_APB2ENR_USART1EN        (0x1UL << 4U)
#define RCC_AHB1ENR_GPIOAEN         (0x1UL << 0U)

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

/* Mode */
#define USART_CR1_RE                  0x00000004U                        /*!<Receiver Enable                        */
#define USART_CR1_TE                  0x00000008U                        /*!<Transmitter Enable                     */
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

#define RCC_CFGR_PPRE1_DIV1           0x00000000U                         /*!< HCLK not divided   */
#define RCC_CFGR_PPRE1_DIV2           0x00001000U                         /*!< HCLK divided by 2  */
#define RCC_CFGR_PPRE1_DIV4           0x00001400U                         /*!< HCLK divided by 4  */
#define RCC_CFGR_PPRE1_DIV8           0x00001800U                         /*!< HCLK divided by 8  */
#define RCC_CFGR_PPRE1_DIV16          0x00001C00U                         /*!< HCLK divided by 16 */
#define RCC_HCLK_DIV16                RCC_CFGR_PPRE1_DIV16

#define USART_CR2_LINEN               0x00004000                      /*!<LIN mode enable */
#define USART_CR2_CLKEN               0x00000800                      /*!<Clock Enable                         */
#define USART_CR3_SCEN                0x00000020                       /*!<Smartcard mode enable       */
#define USART_CR3_IREN                0x00000002                       /*!<IrDA mode Enable            */
#define USART_CR3_HDSEL               0x00000008                      /*!<Half-Duplex Selection       */

#define UART_DIV_SAMPLING16(_PCLK_, _BAUD_)            ((uint32_t)((((uint32_t)(_PCLK_))*25U)/(4U*((uint32_t)(_BAUD_)))))
#define UART_DIVMANT_SAMPLING16(_PCLK_, _BAUD_)        (UART_DIV_SAMPLING16((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING16(_PCLK_, _BAUD_)        ((((UART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) * 100U)) * 16U)\
                                                         + 50U) / 100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + (UART DIVFRAQ & 0xF0) + (UART DIVFRAQ & 0x0FU) */
#define UART_BRR_SAMPLING16(_PCLK_, _BAUD_)            ((UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) << 4U) + \
                                                    (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0xF0U) + \
                                                    (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0x0FU))

#define  GPIO_SPEED_FREQ_LOW          0x00000000U  /*!< IO works at 2 MHz, please refer to the product datasheet */
#define  GPIO_SPEED_FREQ_MEDIUM       0x00000001U  /*!< range 12,5 MHz to 50 MHz, please refer to the product datasheet */
#define  GPIO_SPEED_FREQ_HIGH         0x00000002U  /*!< range 25 MHz to 100 MHz, please refer to the product datasheet  */
#define  GPIO_SPEED_FREQ_VERY_HIGH    0x00000003U  /*!< range 50 MHz to 200 MHz, please refer to the product datasheet  */

#define OUTPUT_TYPE_Pos               4U
#define OUTPUT_TYPE                   (0x1UL << OUTPUT_TYPE_Pos)

#define GPIO_OTYPER_OT_0              0x00000001U
#define GPIO_OSPEEDER_OSPEEDR0        0x00000003U
#define GPIO_PUPDR_PUPDR0             0x00000003U
#define GPIO_MODE                     0x3UL
#define GPIO_MODER_MODER0             0x00000003U

#define GPIO_MODE_INPUT     0x0UL
#define GPIO_MODE_OUTPUT    0x1UL
#define GPIO_MODE_AF        0x2UL
#define GPIO_MODE_ANALOG    0x3UL

#define RCC_APB1ENR_UART4EN_Pos            (19U)
#define RCC_APB1ENR_UART4EN_Msk            (0x1UL << RCC_APB1ENR_UART4EN_Pos)   /*!< 0x00080000 */
#define RCC_APB1ENR_UART4EN                RCC_APB1ENR_UART4EN_Msk

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
