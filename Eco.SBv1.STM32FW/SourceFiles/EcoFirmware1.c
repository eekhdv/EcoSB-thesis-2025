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
#include "IEcoSystem1.h"
#include "IdEcoGPIO1.h"
#include "IdEcoUART1.h"
#include "IdEcoModBus1.h"
#include "IdEcoModBus1SL.h"
//#include "IdEcoTaskScheduler1.h"
#include "IdEcoMemoryManager1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "IdEcoInterfaceBus1.h"
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
#define ECO_GPIO_LPN_13     ((uint8_t)0x8D)

#define ECO_GPIO_HIGHT     1
#define ECO_GPIO_LOW       0

/* Global Read-only variable */
const uint32_t DELAY_MAX = 0x0010BEEF;

/* Global Uninitialized varible */
uint32_t delay_counter;

void delay() {
    for(delay_counter=DELAY_MAX; delay_counter--;);
}


/* Clock */
#define RCC_AHB1ENR     *((volatile uint32_t*) (0x40023830))

/* GPIO A */
#define GPIOA_MODER     *((volatile uint32_t*) (0x40020000))
#define GPIOA_BSRR      *((volatile uint32_t*) (0x40020018))

/* GPIO B */
#define GPIOB_MODER     *((volatile uint32_t*) (0x40020400))
#define GPIOB_BSRR      *((volatile uint32_t*) (0x40020418))

/* Global initialized variable */
uint32_t isLoop = 1;

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
    IEcoRCC1STM32Config* pIRCCConfig = 0;
    IEcoGPIO1STM32Config* pIGPIOConfig = 0;
    ECO_RCC_CONFIG_DESCRIPTOR xRCC = {0};
    ECO_GPIO_CONFIG_DESCRIPTOR xGPIOB = {0};
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

    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoGPIO1, 0, &IID_IEcoGPIO1, (void**) &pIGPIO);

    /* Проверка */
    if (result != 0 || pIGPIO == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }


    /* Запрос интерфейса RCC конфигурации */
    result = pIGPIO->pVTbl->QueryInterface(pIGPIO, &IID_IEcoRCC1STM32Config, (void**) &pIRCCConfig);
    if (result != 0 || pIRCCConfig == 0) {
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
    if (result != 0 || pIGPIOConfig == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Установка базового адреса и сохранение ссылки на конфигурацию порта */
    xGPIOB.Register.BaseAddress = ECO_GPIOB; //0x40020400UL;
    result = pIGPIOConfig->pVTbl->set_ConfigDescriptor(pIGPIOConfig, 'B' /* or 2 */, &xGPIOB);
    /* Устанавка логического номера контакта для соответствующей конфигурации порта и контакта */
    result = pIGPIOConfig->pVTbl->set_LogicalPinNumber(pIGPIOConfig, ECO_GPIO_LPN_12, 'B' /* or 2 */, ECO_GPIO_PIN_12);
    result = pIGPIOConfig->pVTbl->set_LogicalPinNumber(pIGPIOConfig, ECO_GPIO_LPN_13, 'B' /* or 2 */, ECO_GPIO_PIN_13);

    /* Устанавливаем режим вывода по логический номеру контакта */
    result = pIGPIO->pVTbl->set_Mode(pIGPIO, ECO_GPIO_LPN_12, GPIO_MODE_OUTPUT);
      result = pIGPIO->pVTbl->set_Mode(pIGPIO, ECO_GPIO_LPN_13, GPIO_MODE_OUTPUT);  
    /* Пример 1: Цикл установки и сброса уровня на логическом контакте */
    while (1) {
        result = pIGPIO->pVTbl->set_Data(pIGPIO, ECO_GPIO_LPN_13, ECO_GPIO_LOW);
        result = pIGPIO->pVTbl->set_Data(pIGPIO, ECO_GPIO_LPN_12, ECO_GPIO_HIGHT);
        delay();
       result = pIGPIO->pVTbl->set_Data(pIGPIO, ECO_GPIO_LPN_13, ECO_GPIO_HIGHT);
         result = pIGPIO->pVTbl->set_Data(pIGPIO, ECO_GPIO_LPN_12, ECO_GPIO_LOW);
        delay();

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
