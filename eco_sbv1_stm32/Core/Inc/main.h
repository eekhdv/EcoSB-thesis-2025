/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CAN_FD_INT_Pin GPIO_PIN_2
#define CAN_FD_INT_GPIO_Port GPIOE
#define RS485_EN_Pin GPIO_PIN_3
#define RS485_EN_GPIO_Port GPIOE
#define RS232_EN_Pin GPIO_PIN_4
#define RS232_EN_GPIO_Port GPIOE
#define CAN_FD_CS_Pin GPIO_PIN_5
#define CAN_FD_CS_GPIO_Port GPIOE
#define NC_Pin GPIO_PIN_6
#define NC_GPIO_Port GPIOE
#define NCC13_Pin GPIO_PIN_13
#define NCC13_GPIO_Port GPIOC
#define OSC_32_IN_Pin GPIO_PIN_14
#define OSC_32_IN_GPIO_Port GPIOC
#define OSC_32_OUT_Pin GPIO_PIN_15
#define OSC_32_OUT_GPIO_Port GPIOC
#define OSC_IN_Pin GPIO_PIN_0
#define OSC_IN_GPIO_Port GPIOH
#define OSC_OUT_Pin GPIO_PIN_1
#define OSC_OUT_GPIO_Port GPIOH
#define STM_ADC1_Pin GPIO_PIN_0
#define STM_ADC1_GPIO_Port GPIOC
#define STM_GPIO2_Pin GPIO_PIN_1
#define STM_GPIO2_GPIO_Port GPIOC
#define STM_GPIO1_Pin GPIO_PIN_2
#define STM_GPIO1_GPIO_Port GPIOC
#define _5V_Sens_Pin GPIO_PIN_3
#define _5V_Sens_GPIO_Port GPIOC
#define UART4_RX_Pin GPIO_PIN_0
#define UART4_RX_GPIO_Port GPIOA
#define UART4_TX_Pin GPIO_PIN_1
#define UART4_TX_GPIO_Port GPIOA
#define STM_ADC2_Pin GPIO_PIN_2
#define STM_ADC2_GPIO_Port GPIOA
#define STM_DIN2_Pin GPIO_PIN_3
#define STM_DIN2_GPIO_Port GPIOA
#define STM_DIN1_Pin GPIO_PIN_4
#define STM_DIN1_GPIO_Port GPIOA
#define CAN_FD_SCK_Pin GPIO_PIN_5
#define CAN_FD_SCK_GPIO_Port GPIOA
#define CAN_FD_SDI_Pin GPIO_PIN_6
#define CAN_FD_SDI_GPIO_Port GPIOA
#define CAN_FD_SDO_Pin GPIO_PIN_7
#define CAN_FD_SDO_GPIO_Port GPIOA
#define STM_DIN5_Pin GPIO_PIN_4
#define STM_DIN5_GPIO_Port GPIOC
#define STM_DIN3_Pin GPIO_PIN_5
#define STM_DIN3_GPIO_Port GPIOC
#define NCB0_Pin GPIO_PIN_0
#define NCB0_GPIO_Port GPIOB
#define NCB1_Pin GPIO_PIN_1
#define NCB1_GPIO_Port GPIOB
#define NCB2_Pin GPIO_PIN_2
#define NCB2_GPIO_Port GPIOB
#define STM_DIN4_Pin GPIO_PIN_7
#define STM_DIN4_GPIO_Port GPIOE
#define STM_DIN6_Pin GPIO_PIN_8
#define STM_DIN6_GPIO_Port GPIOE
#define LTE_EN_Pin GPIO_PIN_9
#define LTE_EN_GPIO_Port GPIOE
#define AI_EN_Pin GPIO_PIN_10
#define AI_EN_GPIO_Port GPIOE
#define ESP32_EN_Pin GPIO_PIN_11
#define ESP32_EN_GPIO_Port GPIOE
#define NCE12_Pin GPIO_PIN_12
#define NCE12_GPIO_Port GPIOE
#define NCE13_Pin GPIO_PIN_13
#define NCE13_GPIO_Port GPIOE
#define NCE14_Pin GPIO_PIN_14
#define NCE14_GPIO_Port GPIOE
#define NCE15_Pin GPIO_PIN_15
#define NCE15_GPIO_Port GPIOE
#define CPU_EN_Pin GPIO_PIN_12
#define CPU_EN_GPIO_Port GPIOB
#define RS485_DE_Pin GPIO_PIN_13
#define RS485_DE_GPIO_Port GPIOB
#define RS485_RE_Pin GPIO_PIN_14
#define RS485_RE_GPIO_Port GPIOB
#define NCB15_Pin GPIO_PIN_15
#define NCB15_GPIO_Port GPIOB
#define RS485_D_Pin GPIO_PIN_8
#define RS485_D_GPIO_Port GPIOD
#define RS485_R_Pin GPIO_PIN_9
#define RS485_R_GPIO_Port GPIOD
#define STM_OUT1_Pin GPIO_PIN_10
#define STM_OUT1_GPIO_Port GPIOD
#define STM_OUT2_Pin GPIO_PIN_11
#define STM_OUT2_GPIO_Port GPIOD
#define CPU_GPIO_Pin GPIO_PIN_12
#define CPU_GPIO_GPIO_Port GPIOD
#define CPU_RES_Pin GPIO_PIN_13
#define CPU_RES_GPIO_Port GPIOD
#define GNSS_ANT_PWR_Pin GPIO_PIN_14
#define GNSS_ANT_PWR_GPIO_Port GPIOD
#define SPI3_CS_Pin GPIO_PIN_15
#define SPI3_CS_GPIO_Port GPIOD
#define RS232_TIN_Pin GPIO_PIN_6
#define RS232_TIN_GPIO_Port GPIOC
#define RS232_ROUT_Pin GPIO_PIN_7
#define RS232_ROUT_GPIO_Port GPIOC
#define ACCEL_INT_Pin GPIO_PIN_8
#define ACCEL_INT_GPIO_Port GPIOC
#define ESP32_UART1_RX_Pin GPIO_PIN_9
#define ESP32_UART1_RX_GPIO_Port GPIOA
#define ESP32_UART1_TX_Pin GPIO_PIN_10
#define ESP32_UART1_TX_GPIO_Port GPIOA
#define ESP32_UART1_CTS_Pin GPIO_PIN_11
#define ESP32_UART1_CTS_GPIO_Port GPIOA
#define ESP32_UART1_RTS_Pin GPIO_PIN_12
#define ESP32_UART1_RTS_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define SPI3_CLK_Pin GPIO_PIN_10
#define SPI3_CLK_GPIO_Port GPIOC
#define SPI3_MOSI_Pin GPIO_PIN_11
#define SPI3_MOSI_GPIO_Port GPIOC
#define UART5_RX_Pin GPIO_PIN_12
#define UART5_RX_GPIO_Port GPIOC
#define CAN_RX_Pin GPIO_PIN_0
#define CAN_RX_GPIO_Port GPIOD
#define CAN_TX_Pin GPIO_PIN_1
#define CAN_TX_GPIO_Port GPIOD
#define UART5_TX_Pin GPIO_PIN_2
#define UART5_TX_GPIO_Port GPIOD
#define A_S0_Pin GPIO_PIN_3
#define A_S0_GPIO_Port GPIOD
#define A_S1_Pin GPIO_PIN_4
#define A_S1_GPIO_Port GPIOD
#define LTE_UART2_RX_Pin GPIO_PIN_5
#define LTE_UART2_RX_GPIO_Port GPIOD
#define LTE_UART2_TX_Pin GPIO_PIN_6
#define LTE_UART2_TX_GPIO_Port GPIOD
#define CAN_FD_STBY_Pin GPIO_PIN_7
#define CAN_FD_STBY_GPIO_Port GPIOD
#define CAN_FD_INT1_Pin GPIO_PIN_3
#define CAN_FD_INT1_GPIO_Port GPIOB
#define CAN_FD_CLK0_Pin GPIO_PIN_4
#define CAN_FD_CLK0_GPIO_Port GPIOB
#define SPI3_MISO_Pin GPIO_PIN_5
#define SPI3_MISO_GPIO_Port GPIOB
#define CAN_STBY_Pin GPIO_PIN_6
#define CAN_STBY_GPIO_Port GPIOB
#define BMS_D_Pin GPIO_PIN_7
#define BMS_D_GPIO_Port GPIOB
#define BMS_C_Pin GPIO_PIN_8
#define BMS_C_GPIO_Port GPIOB
#define CHRING_Pin GPIO_PIN_9
#define CHRING_GPIO_Port GPIOB
#define USR_BUT_Pin GPIO_PIN_0
#define USR_BUT_GPIO_Port GPIOE
#define CHR_DN_Pin GPIO_PIN_1
#define CHR_DN_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
