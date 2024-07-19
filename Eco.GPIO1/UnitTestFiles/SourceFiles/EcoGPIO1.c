/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoGPIO1
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
#include "IEcoSystem1.h"
#include "IdEcoGPIO1.h"

#ifdef ECO_AVR8
#include "IEcoGPIO1AVR8Config.h"


/* Определение базового адреса портов для ATMega xx */
#define ECO_GPIOA   0x0020UL
#define ECO_GPIOB   0x0023UL
#define ECO_GPIOC   0x0026UL
#define ECO_GPIOD   0x0029UL
#define ECO_GPIOE   0x002CUL
#define ECO_GPIOF   0x002FUL
#define ECO_GPIOG   0x0032UL
#define ECO_GPIOH   0x0100UL
#define ECO_GPIOJ   0x0103UL
#define ECO_GPIOK   0x0106UL

#elif ECO_STM32

#include "IEcoRCC1STM32Config.h"
#include "IEcoGPIO1STM32Config.h"

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

#elif ECO_BCM283X

#include "IEcoGPIO1BCM283xConfig.h"

/* Определение базового адреса GPIO для BCM2837 (Rasp Pi 3B) */
#define ECO_GPIO     0x3F200000UL

#define ECO_GPIO_BANK_0      ((uint8_t)0x00)
#define ECO_GPIO_BANK_1      ((uint8_t)0x01)

#elif ECO_K210

#include "IEcoGPIO1K210Config.h"
#include "IEcoFPIOA1K210Config.h"
#include "IEcoSYSCTL1K210Config.h"

/* Определение базового адреса GPIO для K210 (Maixduino) */
#define ECO_GPIO     0x50200000U
#define ECO_FPIOA    0x502B0000U
#define ECO_SYSCTL   0x50440000U

#define ECO_IO_FUNC_NUM  3
#define ECO_FUNC_GPIO3   59

#endif

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
#define ECO_GPIO_LPN_12     ((uint8_t)0x0C)
#define ECO_GPIO_LPN_13     ((uint8_t)0x0D)

#define ECO_GPIO_HIGHT     1
#define ECO_GPIO_LOW       0

int16_t Delay(/*in*/ uint32_t milliseconds) {
#ifdef ECO_AVR8
    uint32_t count = 3400;
#elif ECO_STM32
    uint32_t count = 1200;
#elif ECO_BCM283X
    uint32_t count = 69000;
#elif ECO_K210
    uint32_t count = 120000;
#endif
    for (uint32_t i = 0; i < milliseconds; i++) {
        for (uint32_t j = 0; j < count; j++) {
            asm volatile ("NOP\n\t" ::: "memory");
        }
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
#ifdef ECOOS
int EcoMain(IEcoUnknown* pIUnk) {
#else
int main() {
#endif
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoGPIO1* pIGPIO = 0;
#ifdef ECO_AVR8
    IEcoGPIO1AVR8Config* pIGPIOConfig = 0;
#elif ECO_STM32
    IEcoRCC1STM32Config* pIRCCConfig = 0;
    IEcoGPIO1STM32Config* pIGPIOConfig = 0;
    RCC_CONFIG_DESCRIPTOR xRCC = {0};
#elif ECO_BCM283X
    IEcoGPIO1BCM283xConfig* pIGPIOConfig = 0;
#elif ECO_K210
    IEcoGPIO1K210Config* pIGPIOConfig = 0;
    IEcoFPIOA1K210Config* pIFPIOAConfig = 0;
    IEcoSYSCTL1K210Config* pISYSCTLConfig = 0;
    ECO_FPIOA_CONFIG_DESCRIPTOR xFPIOA = {0};
    ECO_FPIOA_IO_REGISTER xIO = {0};
    ECO_SYSCTL_CONFIG_DESCRIPTOR xSYSCTL = {0};

#endif
    GPIO_CONFIG_DESCRIPTOR xGPIOB = {0};
    uint8_t iValue = 0;

    /* Создание экземпляра для работы с GPIO */
    result = GetIEcoComponentFactoryPtr_A70A4C2E9C9645BD91367754D01F101F->pVTbl->Alloc(GetIEcoComponentFactoryPtr_A70A4C2E9C9645BD91367754D01F101F, 0, 0, &IID_IEcoGPIO1, (void**) &pIGPIO);
    if (result != 0 && pIGPIO == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

#ifdef ECO_AVR8
    /* Запрос интерфейса GPIO конфигурации */
    pIGPIO->pVTbl->QueryInterface(pIGPIO, &IID_IEcoGPIO1AVR8Config, (void**) &pIGPIOConfig);
    if (result != 0 && pIGPIOConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Установка базового адреса и сохранение ссылки на конфигурацию порта */
    xGPIOB.Register.BaseAddress = ECO_GPIOB; //0x0023UL;
    result = pIGPIOConfig->pVTbl->set_ConfigDescriptor(pIGPIOConfig, 'B' /* or 2 */, &xGPIOB);
    /* Устанавка логического номера контакта для соответствующей конфигурации порта и контакта */
    result = pIGPIOConfig->pVTbl->set_LogicalPinNumber(pIGPIOConfig, ECO_GPIO_LPN_12, 'B' /* or 2 */, ECO_GPIO_PIN_4);
    result = pIGPIOConfig->pVTbl->set_LogicalPinNumber(pIGPIOConfig, ECO_GPIO_LPN_13, 'B' /* or 2 */, ECO_GPIO_PIN_5);
    /* Настройка порта */
    pIGPIOConfig->pVTbl->get_ConfigDescriptor(pIGPIOConfig, 'B')->Register.Map->DDR &= ~ECO_GPIO_PIN_4;
    pIGPIOConfig->pVTbl->get_ConfigDescriptor(pIGPIOConfig, 'B')->Register.Map->DDR != ECO_GPIO_PIN_5;
    pIGPIOConfig->pVTbl->Release(pIGPIOConfig);

#elif ECO_STM32
    /* Запрос интерфейса RCC конфигурации */
    pIGPIO->pVTbl->QueryInterface(pIGPIO, &IID_IEcoRCC1STM32Config, (void**) &pIRCCConfig);
    if (result != 0 && pIRCCConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Установка базового адреса и сохранение ссылки на конфигурацию */
    xRCC.Register.BaseAddress = ECO_RCC; //0x40023830UL;
    result = pIRCCConfig->pVTbl->set_ConfigDescriptor(pIRCCConfig, &xRCC);

    /* Разрешаем подачу тактового сигнала для порта B */
    pIRCCConfig->pVTbl->get_ConfigDescriptor(pIRCCConfig)->Register.Map->AHB1ENR |= 0x00000002;
    pIRCCConfig->pVTbl->Release(pIRCCConfig);

    /* Запрос интерфейса GPIO конфигурации */
    pIGPIO->pVTbl->QueryInterface(pIGPIO, &IID_IEcoGPIO1STM32Config, (void**) &pIGPIOConfig);
    if (result != 0 && pIGPIOConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Установка базового адреса и сохранение ссылки на конфигурацию порта */
    xGPIOB.Register.BaseAddress = ECO_GPIOB; //0x40020400UL;
    result = pIGPIOConfig->pVTbl->set_ConfigDescriptor(pIGPIOConfig, 'B' /* or 2 */, &xGPIOB);
    /* Устанавка логического номера контакта для соответствующей конфигурации порта и контакта */
    result = pIGPIOConfig->pVTbl->set_LogicalPinNumber(pIGPIOConfig, ECO_GPIO_LPN_12, 'B' /* or 2 */, ECO_GPIO_PIN_12);
    result = pIGPIOConfig->pVTbl->set_LogicalPinNumber(pIGPIOConfig, ECO_GPIO_LPN_13, 'B' /* or 2 */, ECO_GPIO_PIN_13);
    /* Настройка порта */

    pIGPIOConfig->pVTbl->get_ConfigDescriptor(pIGPIOConfig, 'B')->Register.Map->MODER &= ~(0x3 << (ECO_GPIO_LPN_12*2));
    pIGPIOConfig->pVTbl->get_ConfigDescriptor(pIGPIOConfig, 'B')->Register.Map->PUPDR &= ~(0x3 << (ECO_GPIO_LPN_12*2));
    pIGPIOConfig->pVTbl->get_ConfigDescriptor(pIGPIOConfig, 'B')->Register.Map->PUPDR |=  (0x1 << (ECO_GPIO_LPN_12*2));

    pIGPIOConfig->pVTbl->get_ConfigDescriptor(pIGPIOConfig, 'B')->Register.Map->MODER  &= ~(0x3 << (ECO_GPIO_LPN_13*2));
    pIGPIOConfig->pVTbl->get_ConfigDescriptor(pIGPIOConfig, 'B')->Register.Map->MODER  |=  (0x1 << (ECO_GPIO_LPN_13*2));
    pIGPIOConfig->pVTbl->get_ConfigDescriptor(pIGPIOConfig, 'B')->Register.Map->OTYPER &= ~(1 << ECO_GPIO_LPN_13);
    pIGPIOConfig->pVTbl->get_ConfigDescriptor(pIGPIOConfig, 'B')->Register.Map->OSPEEDR = 0300;
    pIGPIOConfig->pVTbl->Release(pIGPIOConfig);

#elif ECO_BCM283X
    /* Запрос интерфейса GPIO конфигурации */
    pIGPIO->pVTbl->QueryInterface(pIGPIO, &IID_IEcoGPIO1BCM283xConfig, (void**) &pIGPIOConfig);
    if (result != 0 && pIGPIOConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Установка базового адреса и сохранение ссылки на конфигурацию */
    xGPIOB.Register.BaseAddress = ECO_GPIO; //0x3F200000UL;
    result = pIGPIOConfig->pVTbl->set_ConfigDescriptor(pIGPIOConfig, &xGPIOB);
    /* Устанавка логического номера контакта для соответствующей конфигурации банка и контакта */
    result = pIGPIOConfig->pVTbl->set_LogicalPinNumber(pIGPIOConfig, ECO_GPIO_LPN_13, ECO_GPIO_BANK_0, ECO_GPIO_PIN_21);
    /* Настройка */
    pIGPIOConfig->pVTbl->get_ConfigDescriptor(pIGPIOConfig)->Register.Map->GPFSEL2 |= (1 << 3);
    pIGPIOConfig->pVTbl->Release(pIGPIOConfig);

#elif ECO_K210
    /* Запрос интерфейса SYSCTL конфигурации */
    pIGPIO->pVTbl->QueryInterface(pIGPIO, &IID_IEcoSYSCTL1K210Config, (void**) &pISYSCTLConfig);
    if (result != 0 && pISYSCTLConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Установка базового адреса и сохранение ссылки на конфигурацию */
    xSYSCTL.Register.BaseAddress = ECO_SYSCTL; //0x50440000U;
    result = pISYSCTLConfig->pVTbl->set_ConfigDescriptor(pISYSCTLConfig, &xSYSCTL);

    /* Разрешаем подачу тактового сигнала  */
    pISYSCTLConfig->pVTbl->get_ConfigDescriptor(pISYSCTLConfig)->Register.Map->clk_en_cent |= 0x00000008;
    pISYSCTLConfig->pVTbl->get_ConfigDescriptor(pISYSCTLConfig)->Register.Map->clk_en_peri |= 0x00000020;
    pISYSCTLConfig->pVTbl->Release(pISYSCTLConfig);

    /* Запрос интерфейса FPIOA конфигурации */
    pIGPIO->pVTbl->QueryInterface(pIGPIO, &IID_IEcoFPIOA1K210Config, (void**) &pIFPIOAConfig);
    if (result != 0 && pIFPIOAConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Установка базового адреса и сохранение ссылки на конфигурацию */
    xFPIOA.Register.BaseAddress = ECO_FPIOA; //0x502B0000U;
    result = pIFPIOAConfig->pVTbl->set_ConfigDescriptor(pIFPIOAConfig, &xFPIOA);

    /* Настраиваем функцию работы с GPIO  */
    pIFPIOAConfig->pVTbl->get_ConfigDescriptor(pIFPIOAConfig)->Register.Map->io[ECO_IO_FUNC_NUM] =  *(uint32_t*)&(const ECO_FPIOA_IO_REGISTER)
    {
        .bits.ch_sel = 3,
        .bits.ds     = 2,
        .bits.oe_en  = 0,
        .bits.oe_inv = 0,
        .bits.do_sel = 0,
        .bits.do_inv = 0,
        .bits.pu     = 0,
        .bits.pd     = 0,
        .bits.sl     = 0,
        .bits.ie_en  = 0,
        .bits.ie_inv = 0,
        .bits.di_inv = 0,
        .bits.st     = 0
    }; //0x00921F3B;
    pIFPIOAConfig->pVTbl->Release(pIFPIOAConfig);

    /* Запрос интерфейса GPIO конфигурации */
    pIGPIO->pVTbl->QueryInterface(pIGPIO, &IID_IEcoGPIO1K210Config, (void**) &pIGPIOConfig);
    if (result != 0 && pIGPIOConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Установка базового адреса и сохранение ссылки на конфигурацию порта */
    xGPIOB.Register.BaseAddress = ECO_GPIO; //0x50200000U;
    result = pIGPIOConfig->pVTbl->set_ConfigDescriptor(pIGPIOConfig, &xGPIOB);
    /* Устанавка логического номера контакта для соответствующей конфигурации порта и контакта */
    //result = pIGPIOConfig->pVTbl->set_LogicalPinNumber(pIGPIOConfig, ECO_GPIO_LPN_12, ECO_IO_FUNC_NUM, ECO_GPIO_PIN_12);
    result = pIGPIOConfig->pVTbl->set_LogicalPinNumber(pIGPIOConfig, ECO_GPIO_LPN_13, 0, ECO_GPIO_PIN_3);
    /* Настройка порта */
    pIGPIOConfig->pVTbl->get_ConfigDescriptor(pIGPIOConfig)->Register.Map->direction |= ECO_GPIO_PIN_3;
    pIGPIOConfig->pVTbl->get_ConfigDescriptor(pIGPIOConfig)->Register.Map->data_output |= ECO_GPIO_PIN_3;
    pIGPIOConfig->pVTbl->Release(pIGPIOConfig);
#endif

    /* Устанавливаем режим вывода по логический номеру контакта */
    result = pIGPIO->pVTbl->set_Mode(pIGPIO, 13, GPIO_MODE_OUTPUT);

    /* Пример 1: Цикл установки и сброса уровня на логическом контакте */
    while (1) {
        result = pIGPIO->pVTbl->set_Data(pIGPIO, ECO_GPIO_LPN_13, ECO_GPIO_LOW);
        Delay(2000);
        result = pIGPIO->pVTbl->set_Data(pIGPIO, ECO_GPIO_LPN_13, ECO_GPIO_HIGHT);
        Delay(2000);
    }


    /* Пример 2: Установка или сброса уровня на логическом контакте при чтении  */
    //while (1) {
        ////result = pIGPIO->pVTbl->set_Data(pIGPIO, ECO_GPIO_LPN_12, ECO_GPIO_HIGHT);
        //pIGPIO->pVTbl->get_Data(pIGPIO, ECO_GPIO_LPN_12, &iValue);
        //if (iValue == 0) {
            //pIGPIO->pVTbl->get_Data(pIGPIO, ECO_GPIO_LPN_13, &iValue);
            //if (iValue == 1) {
                //result = pIGPIO->pVTbl->set_Data(pIGPIO, ECO_GPIO_LPN_13, ECO_GPIO_LOW);
            //}
            //else {
                //result = pIGPIO->pVTbl->set_Data(pIGPIO, ECO_GPIO_LPN_13, ECO_GPIO_HIGHT);
            //}
        //}
        //Delay(300);
    //}

Release:

    /* Освобождение тестируемого интерфейса */
    if (pIGPIO != 0) {
    	pIGPIO->pVTbl->Release(pIGPIO);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}
