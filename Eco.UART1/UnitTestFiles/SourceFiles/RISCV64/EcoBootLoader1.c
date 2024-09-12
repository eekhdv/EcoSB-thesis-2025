/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoBootLoader1
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
#include "EcoBootLoader1BROM.h"
#include "IdEcoUART1.h"
#include "IEcoUART1RISCV64D1Config.h"
#include "IEcoGPIO1RISCV64D1Config.h"
#include "IEcoCCU1RISCV64D1Config.h"

IEcoUART1Device* pIDevice1 = 0;


uint32_t timer_get_us(void) {

    unsigned long long cnt = 0;

    asm volatile("csrr %0, time\n"
        : "=r"(cnt)
        :
        : "memory"
    );

    return (uint32_t)(cnt / 24);
}

void udelay(unsigned long us)
{
	uint64_t t1, t2;

	t1 = timer_get_us();
	t2 = t1 + us * 24;
	do {
		t1 = timer_get_us();
	} while (t2 >= t1);
}

void mdelay(unsigned long ms)
{
	udelay(ms * 1000);
}

static void myprintf(char* str)
{
    int i = 0;
    while(str[i] != 0) {
            pIDevice1->pVTbl->Transmit(pIDevice1, str[i] );
        i++;
    }
}

void main(void) {

    IEcoUART1* pIUART = 0;
    IEcoUART1RISCV64D1Config* pIUARTConfig = 0;
    IEcoGPIO1RISCV64D1Config* pIGPIOConfig = 0;
    IEcoCCU1RISCV64D1Config* pICCUConfig = 0;
    ECO_UART_CONFIG_DESCRIPTOR xUART;
    ECO_GPIO_CONFIG_DESCRIPTOR xGPIO;
    ECO_CCU_CONFIG_DESCRIPTOR xCCU;
    //ECO_UART_1_CONFIG xDevConfig;

    /* Создаем экземпляр компонента UART */
    GetIEcoComponentFactoryPtr_B40E129B56624BD7B5F8339C025F3EF0->pVTbl->Alloc(GetIEcoComponentFactoryPtr_B40E129B56624BD7B5F8339C025F3EF0, 0, 0, &IID_IEcoUART1, (void **)&pIUART);

    /* Создаем устройство UART */
    pIUART->pVTbl->new_Device(pIUART, &pIDevice1);

    /* Запрашиваем интерфейс конфигурации UART */
    pIDevice1->pVTbl->QueryInterface(pIDevice1, &IID_IEcoUART1RISCV64D1Config, (void**) &pIUARTConfig);

    /* Установка базового адреса и сохранение ссылки на конфигурацию UART регистров */
    xUART.Register.BaseAddress = ECO_D1_H_UART0;    /* 0x02500000UL */
    pIUARTConfig->pVTbl->set_ConfigDescriptor(pIUARTConfig, &xUART);

    /* Запрашиваем интерфейс конфигурации GPIO */
    pIDevice1->pVTbl->QueryInterface(pIDevice1, &IID_IEcoGPIO1RISCV64D1Config, (void**) &pIGPIOConfig);

    /* Установка базового адреса и сохранение ссылки на конфигурацию GPIO регистров */
    xGPIO.Register.BaseAddress = ECO_D1_H_GPIO;     /* 0x02000000UL */
    pIGPIOConfig->pVTbl->set_ConfigDescriptor(pIGPIOConfig, &xGPIO);

    pIDevice1->pVTbl->QueryInterface(pIDevice1, &IID_IEcoCCU1RISCV64D1Config, (void**) &pICCUConfig);

    /* Установка базового адреса и сохранение ссылки на конфигурацию CCU регистров */
    xCCU.Register.BaseAddress = ECO_D1_H_CCU;   /* 0x02001000UL */
    pICCUConfig->pVTbl->set_ConfigDescriptor(pICCUConfig, &xCCU);

    /* Инициализация устройства */
    pIDevice1->pVTbl->Connect(pIDevice1, 0);

   // pIUARTConfig->pVTbl->Release(pIUARTConfig);
    /* Передача */
    char xC = '0' + BT0_head.prvt_head.uart_port;
    myprintf("Загрузчик Эко ОС\r\n");
    pIDevice1->pVTbl->Transmit(pIDevice1, xC );
    // PB1
    //*((volatile uint32_t*)&xGPIO.Register.Map->PB_CFG0) = 0xFFFFFF1F;
    //*((volatile uint32_t*)&xGPIO.Register.Map->PB_PULL0) = (1<<2);
    //while (1) {
    //*((volatile uint32_t*)&xGPIO.Register.Map->PB_DAT) = (1<<1);
    //   mdelay(100);
    //*((volatile uint32_t*)&xGPIO.Register.Map->PB_DAT) = (0<<1);
    //   mdelay(100);
    //}
    //PC4
    *((volatile uint32_t*)&xGPIO.Register.Map->PC_CFG0) = 0xFFF1FFFF;
    *((volatile uint32_t*)&xGPIO.Register.Map->PC_PULL0) = (1<<8);
    while (1) {
    *((volatile uint32_t*)&xGPIO.Register.Map->PC_DAT) = (1<<4);
       mdelay(100);
    *((volatile uint32_t*)&xGPIO.Register.Map->PC_DAT) = (0<<4);
       mdelay(100);
    }
    pIDevice1->pVTbl->Transmit(pIDevice1, xC );
    while(1);
} 
