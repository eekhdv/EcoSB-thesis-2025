/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoStartup1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoGPIO1.h"
#include "IEcoSystem1.h"
#include "IEcoUART1.h"
#include "IdEcoGPIO1.h"
#include "IdEcoUART1.h"
//#include "IdEcoTaskScheduler1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "IdEcoInterfaceBus1.h"
#include "IEcoRCC1STM32Config.h"
#include "IEcoGPIO1STM32Config.h"
#include "IEcoUART1STM32F4Config.h"

/* ModBus */
#include "IdEcoModBus1.h"
#include "IdEcoModBus1SL.h"
#include "IEcoModBus1SLRTU.h"

static ECO_UART_CONFIG_DESCRIPTOR xUART  = {0};


#define MODBUS_BUFFER_SIZE 256
uint8_t modbusBuffer[MODBUS_BUFFER_SIZE];

static inline uint32_t __STREXW(uint32_t value, volatile uint32_t *addr)
{
   uint32_t result;

   __asm volatile ("strex %0, %2, %1" : "=&r" (result), "=Q" (*addr) : "r" (value) );
   return(result);
}

static inline uint32_t __LDREXW(volatile uint32_t *addr)
{
    uint32_t result;

   __asm volatile ("ldrex %0, %1" : "=r" (result) : "Q" (*addr) );
   return(result);
}

typedef struct
{
  uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_Type;

typedef struct
{
  volatile uint32_t CR;   /*!< PWR power control register,        Address offset: 0x00 */
  volatile uint32_t CSR;  /*!< PWR power control/status register, Address offset: 0x04 */
} PWR_TypeDef;

#define PERIPH_BASE           0x40000000UL /*!< Peripheral base address in the alias region                                */
#define APB1PERIPH_BASE       PERIPH_BASE
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000UL)
#define PWR                 ((PWR_TypeDef *) PWR_BASE)

typedef struct
{
  volatile uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
  uint32_t RESERVED0[24U];
  volatile uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
  uint32_t RSERVED1[24U];
  volatile uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
  uint32_t RESERVED2[24U];
  volatile uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
  uint32_t RESERVED3[24U];
  volatile uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
  uint32_t RESERVED4[56U];
  volatile uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
  uint32_t RESERVED5[644U];
  volatile uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}  NVIC_Type;

typedef struct
{
  volatile uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  volatile uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  volatile uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  volatile uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  volatile uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  volatile uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  volatile uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  volatile uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  volatile uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  volatile uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  volatile uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  volatile uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  volatile uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  volatile uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  volatile uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  volatile uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  volatile uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  volatile uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  volatile uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
  uint32_t RESERVED0[5U];
  volatile uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;


/* IRQ */
static const int32_t SysTick_IRQn        = -1;     /*!< 15 Cortex-M4 System Tick Interrupt                                */
static const int32_t UART4_IRQn          = 52;     /*!< UART4 global Interrupt                                            */


/* System Core Clock */
static uint32_t SystemCoreClock = 16000000U;
const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APBPrescTable[8]  = {0, 0, 0, 0, 1, 2, 3, 4};


#define SYS_TICK_LOAD_RELOAD 0xFFFFFFUL

#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address */
#define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address */

#define SysTick             ((SysTick_Type   *)     SysTick_BASE  )
#define NVIC                ((NVIC_Type      *)     NVIC_BASE     )   /*!< NVIC configuration struct */
#define SCB                 ((SCB_Type       *)     SCB_BASE      )   /*!< SCB configuration struct */


#define __NVIC_PRIO_BITS          4U       /*!< STM32F4XX uses 4 Bits for the Priority Levels */

#define SysTick_CTRL_CLKSOURCE_Pos          2U                                            /*!< SysTick CTRL: CLKSOURCE Position */
#define SysTick_CTRL_CLKSOURCE_Msk         (1UL << SysTick_CTRL_CLKSOURCE_Pos)            /*!< SysTick CTRL: CLKSOURCE Mask */
#define SysTick_CTRL_TICKINT_Pos            1U                                            /*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL: TICKINT Mask */
#define SysTick_CTRL_ENABLE_Pos             0U                                            /*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_Msk            (1UL /*<< SysTick_CTRL_ENABLE_Pos*/)           /*!< SysTick CTRL: ENABLE Mask */

#define SCB_AIRCR_PRIGROUP_Pos              8U                                            /*!< SCB AIRCR: PRIGROUP Position */
#define SCB_AIRCR_PRIGROUP_Msk             (7UL << SCB_AIRCR_PRIGROUP_Pos)                /*!< SCB AIRCR: PRIGROUP Mask */

#define __NVIC_PRIO_BITS          4U       /*!< STM32F4XX uses 4 Bits for the Priority Levels */

static inline uint32_t __NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);   /* only values 0..7 are used          */
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(__NVIC_PRIO_BITS)) ? (uint32_t)(__NVIC_PRIO_BITS) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(__NVIC_PRIO_BITS)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(__NVIC_PRIO_BITS));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority     & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL)))
         );
}

static inline uint32_t __NVIC_GetPriorityGrouping(void)
{
  return ((uint32_t)((SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) >> SCB_AIRCR_PRIGROUP_Pos));
}

static inline void NVIC_SetPriority(int32_t IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->IP[((uint32_t)IRQn)]               = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
  else
  {
    SCB->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - __NVIC_PRIO_BITS)) & (uint32_t)0xFFUL);
  }
}



static inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > SYS_TICK_LOAD_RELOAD)
  {
    return (1UL);                                                   /* Reload value impossible */
  }

  SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         /* set reload register */
  NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
  SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_TICKINT_Msk   |
                   SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
  return (0UL);                                                     /* Function successful */
}


/* Определение базового адреса RCC для STM32F4xx */
#define ECO_RCC     0x40023800UL

/* Определение базового адреса портов для STM32F4xx */
#define ECO_GPIOA   0x40020000UL
#define ECO_GPIOB   0x40020400UL
#define ECO_GPIOC   0x40020800UL
#define ECO_GPIOD   0x40020C00UL
#define ECO_GPIOE   0x40021000UL
#define ECO_GPIOF   0x40021400UL
#define ECO_GPIOG   0x40021800UL
#define ECO_GPIOH   0x40021C00UL
#define ECO_GPIOI   0x40022000UL
#define ECO_GPIOJ   0x40022400UL
#define ECO_GPIOK   0x40022800UL

#define ECO_USART1  0x40011000UL
#define ECO_USART6  0x40011400UL
#define ECO_USART3  0x40004800UL
#define ECO_USART2  0x40004400UL
#define ECO_UART5   0x40005000UL
#define ECO_UART4   0x40004C00UL

/* Определение номеров контактов для портов */
#define ECO_GPIO_PIN_0      ((uint8_t)0x01)
#define ECO_GPIO_PIN_1      ((uint8_t)0x02)
#define ECO_GPIO_PIN_2      ((uint8_t)0x04)
#define ECO_GPIO_PIN_3      ((uint8_t)0x08)
#define ECO_GPIO_PIN_4      ((uint8_t)0x10)
#define ECO_GPIO_PIN_5      ((uint8_t)0x20)
#define ECO_GPIO_PIN_6      ((uint8_t)0x40)
#define ECO_GPIO_PIN_7      ((uint8_t)0x80)
#define ECO_GPIO_PIN_8      ((uint16_t)0x0100)
#define ECO_GPIO_PIN_9      ((uint16_t)0x0200)
#define ECO_GPIO_PIN_10     ((uint16_t)0x0400)
#define ECO_GPIO_PIN_11     ((uint16_t)0x0800)
#define ECO_GPIO_PIN_12     ((uint16_t)0x1000)
#define ECO_GPIO_PIN_13     ((uint16_t)0x2000)
#define ECO_GPIO_PIN_14     ((uint16_t)0x4000)
#define ECO_GPIO_PIN_15     ((uint16_t)0x8000)
#define ECO_GPIO_PIN_16     ((uint32_t)0x00010000)
#define ECO_GPIO_PIN_17     ((uint32_t)0x00020000)
#define ECO_GPIO_PIN_18     ((uint32_t)0x00040000)
#define ECO_GPIO_PIN_19     ((uint32_t)0x00080000)
#define ECO_GPIO_PIN_20     ((uint32_t)0x00100000)
#define ECO_GPIO_PIN_21     ((uint32_t)0x00200000)
#define ECO_GPIO_PIN_22     ((uint32_t)0x00400000)
#define ECO_GPIO_PIN_23     ((uint32_t)0x00800000)
#define ECO_GPIO_PIN_24     ((uint32_t)0x01000000)
#define ECO_GPIO_PIN_25     ((uint32_t)0x02000000)
#define ECO_GPIO_PIN_26     ((uint32_t)0x04000000)
#define ECO_GPIO_PIN_27     ((uint32_t)0x08000000)
#define ECO_GPIO_PIN_28     ((uint32_t)0x10000000)
#define ECO_GPIO_PIN_29     ((uint32_t)0x20000000)
#define ECO_GPIO_PIN_30     ((uint32_t)0x40000000)
#define ECO_GPIO_PIN_31     ((uint32_t)0x80000000)

/* Определение логического номера контакта (Logical Pin Number) */
#define ECO_GPIO_LPN_0      ((uint8_t)0x0A)
#define ECO_GPIO_LPN_1      ((uint8_t)0x0B)
#define ECO_GPIO_LPN_2      ((uint8_t)0x02)
#define ECO_GPIO_LPN_3      ((uint8_t)0x03)
#define ECO_GPIO_LPN_6      ((uint8_t)0x06)
#define ECO_GPIO_LPN_7      ((uint8_t)0x07)
#define ECO_GPIO_LPN_12     ((uint8_t)0x0C)
#define ECO_GPIO_LPN_13     ((uint8_t)0x8D)


/* Глобальные макросы */
#define ECO_GPIO_HIGHT                    1
#define ECO_GPIO_LOW                      0

#define RCC_AHB1ENR                       *((volatile uint32_t*) (0x40023830))

#define RCC_HCLK_DIV1                     0x00000000U
#define RCC_HCLK_DIV2                     0x00001000U
#define RCC_HCLK_DIV4                     0x00001400U
#define RCC_HCLK_DIV8                     0x00001800U
#define RCC_HCLK_DIV16                    0x00001C00U
#define RCC_SYSCLK_DIV1                   0x00000000U

#define RCC_CFGR_PPRE1                    0x00001C00                  /*!< PRE1[2:0] bits (APB1 prescaler) */
#define RCC_CFGR_PPRE2                    0x0000E000                  /*!< PRE2[2:0] bits (APB2 prescaler) */
#define RCC_CFGR_HPRE                     0x000000F0                   /*!< HPRE[3:0] bits (AHB prescaler) */

#define RCC_AHB1ENR_GPIOAEN               0x00000001             

#define RCC_CFGR_SWS_Pos                  (2U)                                
#define RCC_CFGR_SWS_Msk                  (0x3UL << RCC_CFGR_SWS_Pos)          /*!< 0x0000000C */
#define RCC_CFGR_SWS                      RCC_CFGR_SWS_Msk                    /*!< SWS[1:0] bits (System Clock Switch Status) */
#define RCC_SYSCLKSOURCE_HSI              0x00000000U
#define RCC_CFGR_SW                       0x00000003UL                    /*!< SW[1:0] bits (System clock Switch) */

#define RCC_FLAG_MASK                    ((uint8_t)0x1FU)
#define RCC_FLAG_HSIRDY                  ((uint8_t)0x21)

#define USART_CR1_RE                  0x00000004U                        /*!<Receiver Enable                        */
#define USART_CR1_TE                  0x00000008U                        /*!<Transmitter Enable                     */
#define UART_WORDLENGTH_8B            0x00000000U
#define UART_STOPBITS_1               0x00000000U
#define UART_PARITY_NONE              0x00000000U
#define UART_OVERSAMPLING_16          0x00000000U
#define UART_HWCONTROL_NONE           0x00000000U
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

#define UART_FLAG_TXE                       ((uint32_t)USART_SR_TXE)
#define UART_FLAG_RXNE                      ((uint32_t)USART_SR_RXNE)
#define UART_FLAG_TC                        ((uint32_t)USART_SR_TC)

#define USART_CR1_IDLEIE              0x00000010                     /*!<IDLE Interrupt Enable                  */


#define ATOMIC_CLEAR_BIT(REG, BIT)                           \
  do {                                                       \
    uint32_t val;                                            \
    do {                                                     \
      val = __LDREXW((volatile uint32_t *)&(REG)) & ~(BIT);      \
    } while ((__STREXW(val,(volatile uint32_t *)&(REG))) != 0U); \
  } while(0)

#define UART_DIV_SAMPLING16(_PCLK_, _BAUD_)            ((uint32_t)((((uint32_t)(_PCLK_))*25U)/(4U*((uint32_t)(_BAUD_)))))
#define UART_DIVMANT_SAMPLING16(_PCLK_, _BAUD_)        (UART_DIV_SAMPLING16((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING16(_PCLK_, _BAUD_)        ((((UART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) * 100U)) * 16U)\
                                                         + 50U) / 100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + (UART DIVFRAQ & 0xF0) + (UART DIVFRAQ & 0x0FU) */
#define UART_BRR_SAMPLING16(_PCLK_, _BAUD_)            ((UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) << 4U) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0xF0U) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0x0FU))


/* Global Read-only variable */
const uint32_t DELAY_MAX = 0x0010BEEF;

static uint32_t uwTick;
static const uint32_t uwTickFreq = 1;

void Eco_IncTick(void) { uwTick += uwTickFreq; }

void SysTick_Handler(void) { Eco_IncTick(); }

uint32_t Eco_GetTick(void) { return uwTick; }

void EcoDelay(uint32_t Delay)
{
   uint32_t tickstart = Eco_GetTick();
   uint32_t wait = Delay;

   if (wait < DELAY_MAX)
   {
	   wait += (uint32_t)(uwTickFreq);
   }

   while((Eco_GetTick() - tickstart) < wait) { }
}

uint32_t isLoop = 1;


void UART4_IRQHandler(void)
{
  /* Add UART4 IRQ handler logic */
  return;
}


void EcoClockConfigure(ECO_RCC_CONFIG_DESCRIPTOR* rccConfig)
{
	/* HCLK Configuration */
  rccConfig->Register.Map->CFGR = (rccConfig->Register.Map->CFGR & (~RCC_CFGR_PPRE1)) | RCC_HCLK_DIV16;
  rccConfig->Register.Map->CFGR = (rccConfig->Register.Map->CFGR & (~RCC_CFGR_PPRE2)) | (RCC_HCLK_DIV16 << 3);
  rccConfig->Register.Map->CFGR = (rccConfig->Register.Map->CFGR & (~RCC_CFGR_HPRE))  | RCC_SYSCLK_DIV1;


  uint32_t flagHsiRdy = RCC_FLAG_HSIRDY >> 5U;
  (void)flagHsiRdy;
  /* (((((flagHsiRdy == 1U)? rccConfig->Register.Map->CR : (flagHsiRdy == 2U ? rccConfig->Register.Map->BDCR : (flagHsiRdy == 3U ? rccConfig->Register.Map->CSR : rccConfig->Register.Map->CIR))) & (1U << (RCC_FLAG_HSIRDY & RCC_FLAG_MASK))) != 0U) ? 1U : 0U); */

	rccConfig->Register.Map->CFGR = (rccConfig->Register.Map->CFGR & (~RCC_CFGR_SW)) | RCC_SYSCLKSOURCE_HSI;

	while ((rccConfig->Register.Map->CFGR & RCC_CFGR_SWS) != (RCC_SYSCLKSOURCE_HSI << RCC_CFGR_SWS_Pos)) {}

	rccConfig->Register.Map->CFGR = (rccConfig->Register.Map->CFGR & (~RCC_CFGR_PPRE1)) | RCC_HCLK_DIV1;
	rccConfig->Register.Map->CFGR = (rccConfig->Register.Map->CFGR & (~RCC_CFGR_PPRE2)) | (RCC_HCLK_DIV1 << 3U);

	/* Update the SystemCoreClock global variable */
	SysTick_Config(SystemCoreClock / (1000U / uwTickFreq));
}

/* SCB Application Interrupt and Reset Control Register Definitions */
#define SCB_AIRCR_VECTKEY_Pos              16U                                            /*!< SCB AIRCR: VECTKEY Position */
#define SCB_AIRCR_VECTKEY_Msk              (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)            /*!< SCB AIRCR: VECTKEY Mask */

static inline void __NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);             /* only values 0..7 are used          */

  reg_value  =  SCB->AIRCR;                                                   /* read old register configuration    */
  reg_value &= ~((uint32_t)(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_PRIGROUP_Msk)); /* clear bits to change               */
  reg_value  =  (reg_value                                   |
                ((uint32_t)0x5FAUL << SCB_AIRCR_VECTKEY_Pos) |
                (PriorityGroupTmp << SCB_AIRCR_PRIGROUP_Pos)  );              /* Insert write key and priority group */
  SCB->AIRCR =  reg_value;
}

void EcoUartTransmit(/* ECO_UART_CONFIG_DESCRIPTOR* uartConfig */IEcoUART1Device* pIDevice, const uint8_t* buffer, uint32_t bufferSize)
{
	const uint8_t  *pdata8bits;

	uint32_t tickstart = Eco_GetTick();
	uint16_t TxXferCount = bufferSize;

  pdata8bits  = buffer;

	while (TxXferCount > 0U)
	{
    pIDevice->pVTbl->Transmit(pIDevice, *pdata8bits);
	  pdata8bits++;
	  TxXferCount--;
	}

  /* Нужно добавить небольшое ожидание, пока не будет достигнут флаг UART_FLAG_TC */
	/*while ((((uartConfig->Register.Map->SR & UART_FLAG_TC) == UART_FLAG_TC) ? ECO_SET : ECO_RESET) == ECO_RESET)
	 *{
	 *  if ((Eco_GetTick() - tickstart) > 1000)
	 *  {
	 *    ATOMIC_CLEAR_BIT(uartConfig->Register.Map->CR1, (USART_CR1_RXNEIE | USART_CR1_PEIE | USART_CR1_TXEIE));
	 *    ATOMIC_CLEAR_BIT(uartConfig->Register.Map->CR3, USART_CR3_EIE);
   * return;
	 *  }
	 *}
  **/
}



uint16_t EcoUartReceive(/* ECO_UART_CONFIG_DESCRIPTOR* uartConfig */ IEcoUART1Device* pIDevice, const uint8_t* buffer, uint32_t bufferSize, uint16_t timeout)
{
  uint8_t  *pdata8bits;
	uint32_t tickstart = Eco_GetTick();
	uint16_t RxXferCount = bufferSize;

	pdata8bits  = buffer;

	while (RxXferCount > 0U)
	{
    /* TODO: Receive - блокер, поэтому зависает на бесконечном цикле */
    pIDevice->pVTbl->Receive(pIDevice, pdata8bits);
	  pdata8bits++;
	  RxXferCount--;
	}
  return 0x00;
}

extern uint32_t _end;

/*
 *
 * <сводка>
 *   Функция EcoStartup
 * </сводка>
 *
 * <описание>
 *   Функция EcoStartup - точка запуска ОС
 * </описание>
 *
 */
int EcoStartup() {
    int16_t result = -1;
     /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoMemoryManager1* pIMemMgr = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    /* Указатель на интерфейс для работы с планировщиком */
    //IEcoTaskScheduler1* pIScheduler = 0;
    /* Указатель на интерфейс GPIO */
    IEcoGPIO1* pIGPIO = 0;
    IEcoUART1* pIUART = 0;
    IEcoRCC1STM32Config* pIRCCConfig     = 0;
    IEcoGPIO1STM32Config* pIGPIOConfig   = 0;
    IEcoGPIO1STM32Config* pIUARTGPIOConfig = 0;
    ECO_RCC_CONFIG_DESCRIPTOR xRCC    = {0};
    ECO_GPIO_CONFIG_DESCRIPTOR xGPIOB = {0};

    IEcoUART1STM32F4Config* pIUARTConfig = 0;
    //ECO_UART_CONFIG_DESCRIPTOR xUART  = {0};
    ECO_GPIO_CONFIG_DESCRIPTOR xGPIOA = {0};
    IEcoUART1Device* pIDevice1   = 0;
    ECO_UART_1_CONFIG xDevConfig = {0};

    /* Указатель на интерфейс работы с ModBus */
    IEcoModBus1* pIEcoModBus1 = 0;
    /* Указатель на интерфейс работы с ModBus RTU */
    IEcoModBus1SLRTU*   pIEcoModBus1SLRTU = 0;

    uint8_t iValue = 0;

/* Добавим макрос условной компиляции для дополнительной проверки статической сборки (можно опустить/закоментировать) */
#ifdef ECO_LIB

    /* Создание экземпляра интерфейсной шины */
    result = GetIEcoComponentFactoryPtr_00000000000000000000000042757331->pVTbl->Alloc(GetIEcoComponentFactoryPtr_00000000000000000000000042757331, 0, 0, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    /* Проверка */
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с памятью */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoMemoryManager1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_0000000000000000000000004D656D31);
    /* Проверка */
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Запрос расширения интерфейсной шины */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        /* Установка расширения менаджера памяти */
        pIMemExt->pVTbl->set_Manager(pIMemExt, &CID_EcoMemoryManager1);
       /* Установка разрешения расширения пула */
        pIMemExt->pVTbl->set_ExpandPool(pIMemExt, 1);
    }

    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryManager1, (void**) &pIMemMgr);
    if (result != 0 || pIMemMgr == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Выделение области памяти 4 КБ  (STM32F407VET6) */
    pIMemMgr->pVTbl->Init(pIMemMgr, &_end, 0x1000);
    /* ВАЖНО: Освобождение указателя pIMemMgr->pVTbl->Release(pIMemMgr); приведет к овобождению выделенной области */


    /* Регистрация статического компонента для работы с GPIO */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoGPIO1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_A70A4C2E9C9645BD91367754D01F101F);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с UART */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoUART1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_B40E129B56624BD7B5F8339C025F3EF0);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с ModBus1 */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoModBus1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_D3D7232DDB6940469D2B535BA10E8757);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с ModBus1 Serial Line */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoModBus1SL, (IEcoUnknown*)GetIEcoComponentFactoryPtr_DA26D759A46F405F9977CB5AA9153876);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoUART1, 0, &IID_IEcoUART1, (void**) &pIUART);
    if (result != 0 || pIUART == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Создание UART устройства с аппаратной реализацией */
    result = pIUART->pVTbl->new_Device(pIUART, &pIDevice1);
    if (result != 0 || pIDevice1 == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Запрос интерфейса RCC конфигурации */
    result = pIDevice1->pVTbl->QueryInterface(pIDevice1, &IID_IEcoGPIO1STM32Config, (void**) &pIUARTGPIOConfig);
    if (result != 0 || pIUARTGPIOConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Запрос интерфейса RCC конфигурации */
    result = pIDevice1->pVTbl->QueryInterface(pIDevice1, &IID_IEcoRCC1STM32Config, (void**) &pIRCCConfig);
    if (result != 0 || pIRCCConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    /* Запрос интерфейса UART конфигурации */
    result = pIDevice1->pVTbl->QueryInterface(pIDevice1, &IID_IEcoUART1STM32F4Config, (void**) &pIUARTConfig);
    if (result != 0 && pIUARTConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса работы с ModBus */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoModBus1, 0, &IID_IEcoModBus1, (void**) &pIEcoModBus1);
    if (result != 0 || pIEcoModBus1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса работы с ModBus.SL */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoModBus1SL, 0, &IID_IEcoModBus1SLRTU, (void**) &pIEcoModBus1SLRTU);
    if (result != 0 || pIEcoModBus1SLRTU == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    xRCC.Register.BaseAddress   = ECO_RCC; /* 0x40023800UL */
    xGPIOA.Register.BaseAddress = ECO_GPIOA; /* 0x40020400UL */
    xUART.Register.BaseAddress  = ECO_UART4; /* 0x40004C00UL */

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoGPIO1, 0, &IID_IEcoGPIO1, (void**) &pIGPIO);

    /* Проверка */
    if (result != 0 || pIGPIO == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Запрос интерфейса GPIO конфигурации */
    pIGPIO->pVTbl->QueryInterface(pIGPIO, &IID_IEcoGPIO1STM32Config, (void**) &pIGPIOConfig);
    if (result != 0 || pIGPIOConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    //xGPIOA.Register.BaseAddress = ECO_GPIOA; //0x40020400UL;



    result = pIRCCConfig->pVTbl->set_ConfigDescriptor(pIRCCConfig, &xRCC);
    if (result != 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }
    result = pIUARTGPIOConfig->pVTbl->set_ConfigDescriptor(pIUARTGPIOConfig, 0, &xGPIOA);
    if (result != 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    // result = pIGPIO->pVTbl->set_ConfigDescriptor(pIRCCConfig, &xRCC);
    // if (result != 0) {
    //     /* Освобождение системного интерфейса в случае ошибки */
    //     goto Release;
    // }

    result = pIUARTConfig->pVTbl->set_ConfigDescriptor(pIUARTConfig, &xUART);
    if (result != 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    #define NVIC_PRIORITYGROUP_4         0x00000003U /*!< 4 bits for pre-emption priority
                                                      0 bits for subpriority */
    __NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    EcoClockConfigure(pIRCCConfig->pVTbl->get_ConfigDescriptor(pIRCCConfig));

    xRCC.Register.Map->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	  xGPIOA.Register.Map->BSRR = (uint32_t)(ECO_GPIO_PIN_6|ECO_GPIO_PIN_7) << 16U;

/******************** init GPIO LEDs *****************************/

    result = pIGPIOConfig->pVTbl->set_ConfigDescriptor(pIGPIOConfig, 0 /* or A */, &xGPIOA);
    result = pIGPIOConfig->pVTbl->set_LogicalPinNumber(pIGPIOConfig, ECO_GPIO_LPN_6, 0 /* or A */, ECO_GPIO_PIN_6);
    result = pIGPIOConfig->pVTbl->set_LogicalPinNumber(pIGPIOConfig, ECO_GPIO_LPN_7, 0 /* or A */, ECO_GPIO_PIN_7);
    result = pIGPIO->pVTbl->set_Mode(pIGPIO, ECO_GPIO_LPN_6, GPIO_MODE_OUTPUT);
    result = pIGPIO->pVTbl->set_Mode(pIGPIO, ECO_GPIO_LPN_7, GPIO_MODE_OUTPUT);  

/******************** init UART 4 *****************************/

    ECO_UART_1_CONFIG config = 
    {
      .BaudRate     = 115200,
      .DataBits     = 0,
      .StopBits     = UART_STOPBITS_1,
      .Parity       = UART_PARITY_NONE,
      .WordLength   = UART_WORDLENGTH_8B,
      .Mode         = UART_MODE_TX_RX,
      .Oversampling = UART_OVERSAMPLING_16,
      .HwControl    = UART_HWCONTROL_NONE
    };

    result = pIDevice1->pVTbl->Connect(pIDevice1, &config);

    result = pIEcoModBus1SLRTU->pVTbl->ConnectBus(pIEcoModBus1SLRTU, pIDevice1);

    if (result != ERR_ECO_SUCCESES) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    uint8_t buffer[256];
    uint8_t functionCode = ECO_MB_FC_WRITE_FILE_RECORD;
    uint16_t subCode = 0;

    byte_t sendData[] = " HALT";
    uint32_t dataLength = sizeof(sendData);
    sendData[0] = (uint8_t)(dataLength - 1);

    while (1)
    {
      result = pIGPIO->pVTbl->set_Data(pIGPIO, ECO_GPIO_LPN_7, ECO_GPIO_LOW);
	    EcoDelay(1000);
      result = pIGPIO->pVTbl->set_Data(pIGPIO, ECO_GPIO_LPN_7, ECO_GPIO_HIGHT);
	    EcoDelay(1000);

      //if (EcoUartReceive(&xUART, buffer, 256, 1000) == 0x0)
      // if (EcoUartReceive(pIDevice1, buffer, 256, 1000) == 0x0)
      // {
        // EcoUartTransmit(&xUART, "Hello World\n\r", 13);
        //EcoUartTransmit(pIDevice1, "Hello World\n\r", 13);
      result = pIEcoModBus1SLRTU->pVTbl->EmitMessage(pIEcoModBus1SLRTU, functionCode, subCode, sendData, dataLength);
	    EcoDelay(5000);
      // }
      // else
      // {
      //   //EcoUartTransmit(&xUART, "NO RECV\n\r", 9);
      //   EcoUartTransmit(pIDevice1, "NO RECV\n\r", 9);
      // }
    }

Release:

    /* Освобождение тестируемого интерфейса */
    if (pIGPIO != 0) {
    	pIGPIO->pVTbl->Release(pIGPIO);
    }

    /* Освобождение системного интерфейса */
   // if (pISys != 0) {
   //     pISys->pVTbl->Release(pISys);
   // }

    return result;

}
