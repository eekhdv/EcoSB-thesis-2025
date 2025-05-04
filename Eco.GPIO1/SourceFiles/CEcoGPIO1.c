/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoGPIO1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoGPIO1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <util/delay.h>
#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "CEcoGPIO1.h"

extern bool_t ECOCALLMETHOD IsEqualUGUID_A70A4C2E9C9645BD91367754D01F101F(/* in */ const UGUID* rguid1, /* in */ const UGUID* rguid2);
#define IsEqualUGUID(rguid1, rguid2) IsEqualUGUID_A70A4C2E9C9645BD91367754D01F101F(rguid1, rguid2)

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoGPIO1
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_QueryInterface(/* in */ struct IEcoGPIO1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoGPIO1) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
#ifdef ECO_AVR8
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1AVR8Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
#elif ECO_STM32
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1STM32Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoRCC1STM32Config) ) {
        *ppv = &pCMe->m_pVTblIRCCConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
#elif ECO_BCM283X
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1BCM283xConfig) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
#elif ECO_K210
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1K210Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoFPIOA1K210Config) ) {
        *ppv = &pCMe->m_pVTblIFPIOAConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoSYSCTL1K210Config) ) {
        *ppv = &pCMe->m_pVTblISYSCTLConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
#endif
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoGPIO1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoGPIO1_AddRef(/* in */ struct IEcoGPIO1* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;

}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoGPIO1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoGPIO1_Release(/* in */ struct IEcoGPIO1* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoGPIO1((IEcoGPIO1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция set_Mode
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_set_Mode(/* in */ struct IEcoGPIO1* me, /* in */ uint16_t LogicalPinNumber, /* in */ uint8_t mode) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)me;
#ifdef ECO_STM32
    ECO_GPIO_CONFIG_DESCRIPTOR* pDescriptor = 0;
    uint8_t indexPort = 0;
    uint8_t indexPin = 0;
#elif ECO_RISCV64
#endif
    int16_t result = -1;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }
    
#ifdef ECO_STM32
#define  GPIO_SPEED_FREQ_HIGH         0x00000002U  /*!< range 25 MHz to 100 MHz, please refer to the product datasheet  */

#define OUTPUT_TYPE_Pos               4U
#define OUTPUT_TYPE                   (0x1UL << OUTPUT_TYPE_Pos)

#define GPIO_OTYPER_OT_0              0x00000001U
#define GPIO_OSPEEDER_OSPEEDR0        0x00000003U
#define GPIO_PUPDR_PUPDR0             0x00000003U
#define GPIO_MODE                     0x3UL

    for(indexPort = 0; indexPort < 14; indexPort++) {
        if (pCMe->m_PortConfig[indexPort] != 0) {
            pDescriptor = pCMe->m_PortConfig[indexPort];
            for(indexPin = 0; indexPin < 16; indexPin++) {
                if (pDescriptor->LogicalPinMask[indexPin] == LogicalPinNumber) {
					if (GPIO_MODE_INPUT == mode) {
						pDescriptor->Register.Map->MODER &= ~(1 << indexPin*2+1);
						pDescriptor->Register.Map->MODER &= ~(1 << indexPin*2);
					}
					else if (GPIO_MODE_OUTPUT == mode) {
            pDescriptor->Register.Map->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (indexPin * 2U));
            pDescriptor->Register.Map->OSPEEDR |= (GPIO_SPEED_FREQ_HIGH    << (indexPin * 2U));

            pDescriptor->Register.Map->OTYPER  &= ~(GPIO_OTYPER_OT_0        << indexPin);
            pDescriptor->Register.Map->OTYPER  |= (((GPIO_MODE_OUTPUT & OUTPUT_TYPE) >> OUTPUT_TYPE_Pos) << indexPin);

            pDescriptor->Register.Map->PUPDR   &= ~(GPIO_PUPDR_PUPDR0        << (indexPin * 2U));
            pDescriptor->Register.Map->PUPDR   |= (0                         << (indexPin * 2U));

						pDescriptor->Register.Map->MODER   &= ~(1 << indexPin*2+1);
						pDescriptor->Register.Map->MODER   |=  (1 << indexPin*2);
					}
					else if (GPIO_MODE_AF == mode) {
						pDescriptor->Register.Map->MODER |=  (1 << indexPin*2+1);
						pDescriptor->Register.Map->MODER &= ~(1 << indexPin*2);
					}
					else if (GPIO_MODE_ANALOG == mode) {
						pDescriptor->Register.Map->MODER |=  (1 << indexPin*2+1);
						pDescriptor->Register.Map->MODER |=  (1 << indexPin*2);
					}
					else {
						result = -1;
					}

                    break;
                }
            }
        }
    }
#elif ECO_RISCV64
    pCMe->m_GPIOConfig = 0;
#else
#endif

    return result;
}


/*
 *
 * <сводка>
 *   Функция set_Data
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_set_Data(/* in */ struct IEcoGPIO1* me, /* in */ uint16_t LogicalPinNumber, /* in */ uint8_t Value) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)me;
    ECO_GPIO_CONFIG_DESCRIPTOR* pDescriptor = 0;
    uint8_t indexPort = 0;
    uint8_t indexPin = 0;
    int16_t result = -1;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

#ifdef ECO_AVR8
    for(indexPort = 0; indexPort < 14; indexPort++) {
        if (pCMe->m_PortConfig[indexPort] != 0) {
            pDescriptor = pCMe->m_PortConfig[indexPort];
            for(indexPin = 0; indexPin < 8; indexPin++) {
                if (pDescriptor->LogicalPinMask[indexPin] == LogicalPinNumber) {
                    if(Value != 0)
                    {
                        pDescriptor->Register.Map->PORT |= (uint8_t) (1 << indexPin);
                    }
                    else
                    {
                        pDescriptor->Register.Map->PORT &= ~(uint8_t) (1 << indexPin);
                    }
                    result = 0;
                    break;
                }
            }
            if (result == 0) {
                break;
            }
        }
    }
#elif ECO_STM32
    for(indexPort = 0; indexPort < 14; indexPort++) {
        if (pCMe->m_PortConfig[indexPort] != 0) {
            pDescriptor = pCMe->m_PortConfig[indexPort];
            for(indexPin = 0; indexPin < 16; indexPin++) {
                if (pDescriptor->LogicalPinMask[indexPin] == LogicalPinNumber) {
                    if(Value != 0)
                    {
                        pDescriptor->Register.Map->BSRR = (uint32_t) (1 << indexPin);
                    }
                    else
                    {
                        pDescriptor->Register.Map->BSRR = (uint32_t) (1 << (indexPin + 16U));
                    }
                    result = 0;
                    break;
                }
            }
            if (result == 0) {
                break;
            }
        }
    }
#elif ECO_BCM283X

    pDescriptor = (GPIO_CONFIG_DESCRIPTOR*)pCMe->m_GPIOConfig;
    if (pDescriptor != 0) {
        for(indexPin = 0; indexPin < 64; indexPin++) {
            if (pDescriptor->LogicalPinMask[indexPin] == LogicalPinNumber) {
                if (indexPin < 32) {
                    if(Value != 0)
                    {
                        pDescriptor->Register.Map->GPSET0 |= (uint32_t) (1 << indexPin);
                    }
                    else {
                        pDescriptor->Register.Map->GPCLR0 |= (uint32_t) (1 << indexPin);
                    }
                }
                else {
                    if(Value != 0)
                    {
                        pDescriptor->Register.Map->GPSET1 |= (uint32_t) (1 << (indexPin - 32));
                    }
                    else {
                        pDescriptor->Register.Map->GPCLR1 |= (uint32_t) (1 << (indexPin - 32));
                    }
                }
                break;
            }
        }
    }
#elif ECO_K210

    pDescriptor = (ECO_GPIO_CONFIG_DESCRIPTOR*)pCMe->m_GPIOConfig;
    if (pDescriptor != 0) {
        for(indexPin = 0; indexPin < 64; indexPin++) {
            if (pDescriptor->LogicalPinMask[indexPin] == LogicalPinNumber) {
                if (indexPin < 32) {
                    if(Value != 0)
                    {
                        pDescriptor->Register.Map->data_output |= (uint32_t) (1 << indexPin);
                    }
                    else {
                        pDescriptor->Register.Map->data_output &= ~(uint32_t) (1 << indexPin);
                    }
                }
                else {
                    if(Value != 0)
                    {
                        pDescriptor->Register.Map->data_output |= (uint32_t) (1 << (indexPin - 32));
                    }
                    else {
                        pDescriptor->Register.Map->data_output &= ~(uint32_t) (1 << (indexPin - 32));
                    }
                }
                break;
            }
        }
    }
#elif ECO_RISCV64
    pDescriptor = (ECO_GPIO_CONFIG_DESCRIPTOR*)pCMe->m_GPIOConfig;
    pDescriptor->LogicalPinMask[indexPin] = indexPort;
    pDescriptor->LogicalPinMask[indexPort] = indexPin;
#endif
    result = 0;

    return result;
}

/*
 *
 * <сводка>
 *   Функция get_Data
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_get_Data(/* in */ struct IEcoGPIO1* me, /* in */ uint16_t LogicalPinNumber, /* in | out */ uint8_t *pValue) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)me;
    ECO_GPIO_CONFIG_DESCRIPTOR* pDescriptor = 0;
    uint8_t indexPort = 0;
    uint8_t indexPin = 0;
    int16_t result = -1;
    uint16_t value = 0;
    uint16_t value2 = 0;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

#ifdef ECO_AVR8
    for(indexPort = 0; indexPort < 14; indexPort++) {
        if (pCMe->m_PortConfig[indexPort] != 0) {
            pDescriptor = pCMe->m_PortConfig[indexPort];
            for(indexPin = 0; indexPin < 8; indexPin++) {
                if (pDescriptor->LogicalPinMask[indexPin] == LogicalPinNumber) {
                    if (pDescriptor->Register.Map->DDR & (1 << indexPin)) {
                        *pValue = (uint8_t) (pDescriptor->Register.Map->PORT & (1 << indexPin)) ? 1 : 0;
                    }
                    else {
                        *pValue = (uint8_t) (pDescriptor->Register.Map->PIN & (1 << indexPin)) ? 1 : 0;
                    }
                    result = 0;
                    break;
                }
            }
            if (result == 0) {
                break;
            }
        }
    }
#elif ECO_STM32
    for(indexPort = 0; indexPort < 14; indexPort++) {
        if (pCMe->m_PortConfig[indexPort] != 0) {
            pDescriptor = pCMe->m_PortConfig[indexPort];
            for(indexPin = 0; indexPin < 16; indexPin++) {
                if (pDescriptor->LogicalPinMask[indexPin] == LogicalPinNumber) {
                	if (pDescriptor->Register.Map->MODER & (1 << (indexPin*2))) {
                        *pValue = (pDescriptor->Register.Map->ODR & (1 << indexPin)) ? 1 : 0;
                	}
                    else {
                    	value = ~pDescriptor->Register.Map->IDR;
                    	*pValue = (value & (1 << indexPin)) ? 0 : 1;
                	}
                    result = 0;
                    break;
                }
            }
        }
    }
#elif ECO_BCM283X
#elif ECO_RISCV64
    pDescriptor = (ECO_GPIO_CONFIG_DESCRIPTOR*)pCMe->m_GPIOConfig;
    pDescriptor->LogicalPinMask[indexPin] = indexPort;
    pDescriptor->LogicalPinMask[indexPort] = indexPin;
    pDescriptor->LogicalPinMask[indexPort] = value = value2;
#endif
    return result;
}

#ifdef ECO_AVR8
/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoGPIO1AVR8Config
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_AVR8Config_QueryInterface(/* in */ struct IEcoGPIO1AVR8Config* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoGPIO1) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1AVR8Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoGPIO1AVR8Config
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoGPIO1_AVR8Config_AddRef(/* in */ struct IEcoGPIO1AVR8Config* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;

}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoGPIO1AVR8Config
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoGPIO1_AVR8Config_Release(/* in */ struct IEcoGPIO1AVR8Config* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoGPIO1((IEcoGPIO1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция set_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_AVR8Config_set_ConfigDescriptor(/* in */ struct IEcoGPIO1AVR8Config* me, /* in */ uint8_t PortNumber, /* in */ ECO_GPIO_CONFIG_DESCRIPTOR* config) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));
    int16_t result = -1;
    uint8_t index = 0;

    /* Проверка указателя */
    if (me == 0 || config == 0 ) {
        return -1;
    }

    for(index = 0; index < 14; index++) {
        if (pCMe->m_PortName[index] == PortNumber || index == PortNumber) {
            pCMe->m_PortConfig[index] = config;
            result = 0;
            break;
        }
    }
    return result;
}


/*
 *
 * <сводка>
 *   Функция get_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
ECO_GPIO_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoGPIO1_AVR8Config_get_ConfigDescriptor(/* in */ struct IEcoGPIO1AVR8Config* me, /* in */ uint8_t PortNumber) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));
    ECO_GPIO_CONFIG_DESCRIPTOR* pDescriptor = 0;
    uint8_t index = 0;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    for(index = 0; index < 14; index++) {
        if (pCMe->m_PortName[index] == PortNumber || index == PortNumber) {
            pDescriptor = pCMe->m_PortConfig[index];
            break;
        }
    }
    return pDescriptor;
}

/*
 *
 * <сводка>
 *   Функция set_LogicalPinNumber
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_AVR8Config_set_LogicalPinNumber(/* in */ struct IEcoGPIO1AVR8Config* me, /* in */ uint8_t LogicalPinNumber, /* in */ uint8_t PortNumber, /* in */ uint16_t PinNumber) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));
    ECO_GPIO_CONFIG_DESCRIPTOR* pDescriptor = 0;
    uint8_t index = 0;
    int16_t result = -1;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    for(index = 0; index < 14; index++) {
        if (pCMe->m_PortName[index] == PortNumber || index == PortNumber) {
            pDescriptor = pCMe->m_PortConfig[index];
            break;
        }
    }
    if (pDescriptor != 0) {
        for(index = 0; index < 16; index++) {
            if (PinNumber & (1 << index)) {
                pDescriptor->LogicalPinMask[index] = LogicalPinNumber;
                result = 0;
                break;
            }
        }
    }
    return result;
}
#elif ECO_STM32
/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoGPIO1
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_STM32Config_QueryInterface(/* in */ struct IEcoGPIO1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoGPIO1) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1STM32Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoRCC1STM32Config) ) {
        *ppv = &pCMe->m_pVTblIRCCConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoGPIO1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoGPIO1_STM32Config_AddRef(/* in */ struct IEcoGPIO1* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;

}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoGPIO1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoGPIO1_STM32Config_Release(/* in */ struct IEcoGPIO1* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoGPIO1((IEcoGPIO1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция set_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_STM32Config_set_ConfigDescriptor(/* in */ struct IEcoGPIO1STM32Config* me, /* in */ uint8_t PortNumber, /* in */ ECO_GPIO_CONFIG_DESCRIPTOR* config) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));
    int16_t result = -1;
    uint8_t index = 0;

    /* Проверка указателя */
    if (me == 0 || config == 0 ) {
        return -1;
    }

    for(index = 0; index < 14; index++) {
        if (pCMe->m_PortName[index] == PortNumber || index == PortNumber) {
            pCMe->m_PortConfig[index] = config;
            result = 0;
            break;
        }
    }
    return result;
}


/*
 *
 * <сводка>
 *   Функция get_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
ECO_GPIO_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoGPIO1_STM32Config_get_ConfigDescriptor(/* in */ struct IEcoGPIO1STM32Config* me, /* in */ uint8_t PortNumber) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));
    ECO_GPIO_CONFIG_DESCRIPTOR* pDescriptor = 0;
    uint8_t index = 0;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    for(index = 0; index < 14; index++) {
        if (pCMe->m_PortName[index] == PortNumber || index == PortNumber) {
            pDescriptor = pCMe->m_PortConfig[index];
            break;
        }
    }
    return pDescriptor;
}

/*
 *
 * <сводка>
 *   Функция set_LogicalPinNumber
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_STM32Config_set_LogicalPinNumber(/* in */ struct IEcoGPIO1STM32Config* me, /* in */ uint8_t LogicalPinNumber, /* in */ uint8_t PortNumber, /* in */ uint16_t PinNumber) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));
    ECO_GPIO_CONFIG_DESCRIPTOR* pDescriptor = 0;
    uint8_t index = 0;
    int16_t result = -1;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    for(index = 0; index < 14; index++) {
        if (pCMe->m_PortName[index] == PortNumber || index == PortNumber) {
            pDescriptor = pCMe->m_PortConfig[index];
            break;
        }
    }
    if (pDescriptor != 0) {
        for(index = 0; index < 16; index++) {
            if (PinNumber & (1 << index)) {
                pDescriptor->LogicalPinMask[index] = LogicalPinNumber;
                result = 0;
                break;
            }
        }
    }
    return result;
}

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoGPIO1
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoRCC1_STM32Config_QueryInterface(/* in */ struct IEcoGPIO1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1STM32Config*)));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoGPIO1) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1STM32Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoRCC1STM32Config) ) {
        *ppv = &pCMe->m_pVTblIRCCConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoGPIO1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoRCC1_STM32Config_AddRef(/* in */ struct IEcoGPIO1* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1STM32Config*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;

}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoGPIO1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoRCC1_STM32Config_Release(/* in */ struct IEcoGPIO1* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1STM32Config*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoGPIO1((IEcoGPIO1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция set_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoRCC1_STM32Config_set_ConfigDescriptor(/* in */ struct IEcoGPIO1STM32Config* me, /* in */ ECO_RCC_CONFIG_DESCRIPTOR* config) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1STM32Config*)));

    /* Проверка указателя */
    if (me == 0 || config == 0 ) {
        return -1;
    }

    pCMe->m_RCCConfig = config;

    return 0;
}


/*
 *
 * <сводка>
 *   Функция get_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
ECO_RCC_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoRCC1_STM32Config_get_ConfigDescriptor(/* in */ struct IEcoGPIO1STM32Config* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1STM32Config*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return 0;
    }

    return (ECO_RCC_CONFIG_DESCRIPTOR*)pCMe->m_RCCConfig;
}

#elif ECO_BCM283X
/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoGPIO1BCM283xConfig
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_BCM283xConfig_QueryInterface(/* in */ struct IEcoGPIO1BCM283xConfig* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1BCM283xConfig*)));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoGPIO1) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1BCM283xConfig) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoGPIO1BCM283xConfig
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoGPIO1_BCM283xConfig_AddRef(/* in */ struct IEcoGPIO1BCM283xConfig* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;

}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoGPIO1BCM283xConfig
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoGPIO1_BCM283xConfig_Release(/* in */ struct IEcoGPIO1BCM283xConfig* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoGPIO1((IEcoGPIO1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция set_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_BCM283xConfig_set_ConfigDescriptor(/* in */ struct IEcoGPIO1BCM283xConfig* me, /* in */ GPIO_CONFIG_DESCRIPTOR* config) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателя */
    if (me == 0 || config == 0 ) {
        return -1;
    }

    pCMe->m_GPIOConfig = config;

    return 0;
}


/*
 *
 * <сводка>
 *   Функция get_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
GPIO_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoGPIO1_BCM283xConfig_get_ConfigDescriptor(/* in */ struct IEcoGPIO1BCM283xConfig* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return 0;
    }

    return (GPIO_CONFIG_DESCRIPTOR*)pCMe->m_GPIOConfig;
}

/*
 *
 * <сводка>
 *   Функция set_LogicalPinNumber
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_BCM283xConfig_set_LogicalPinNumber(/* in */ struct IEcoGPIO1BCM283xConfig* me, /* in */ uint8_t LogicalPinNumber, /* in */ uint8_t BankNumber, /* in */ uint32_t PinNumber) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));
    GPIO_CONFIG_DESCRIPTOR* pDescriptor = 0;
    uint8_t index = 0;
    int16_t result = -1;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    pDescriptor = (GPIO_CONFIG_DESCRIPTOR*)pCMe->m_GPIOConfig;

    if (pDescriptor != 0) {
        for(index = 0; index < 32; index++) {
            if (PinNumber & (1 << index)) {
                if (BankNumber == 0) {
                    pDescriptor->LogicalPinMask[index] = LogicalPinNumber;
                    result = 0;
                }
                else if (BankNumber == 1) {
                    pDescriptor->LogicalPinMask[32 + index] = LogicalPinNumber;
                    result = 0;
                }
                break;
            }
        }
    }
    return result;
}

#elif ECO_K210
/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoGPIO1K210Config
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_K210Config_QueryInterface(/* in */ struct IEcoGPIO1K210Config* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoGPIO1) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1K210Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoGPIO1K210Config
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoGPIO1_K210Config_AddRef(/* in */ struct IEcoGPIO1K210Config* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;

}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoGPIO1K210Config
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoGPIO1_K210Config_Release(/* in */ struct IEcoGPIO1K210Config* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoGPIO1((IEcoGPIO1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция set_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_K210Config_set_ConfigDescriptor(/* in */ struct IEcoGPIO1K210Config* me, /* in */ ECO_GPIO_CONFIG_DESCRIPTOR* config) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателя */
    if (me == 0 || config == 0 ) {
        return -1;
    }

    pCMe->m_GPIOConfig = config;

    return 0;
}


/*
 *
 * <сводка>
 *   Функция get_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
ECO_GPIO_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoGPIO1_K210Config_get_ConfigDescriptor(/* in */ struct IEcoGPIO1K210Config* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return 0;
    }

    return (ECO_GPIO_CONFIG_DESCRIPTOR*)pCMe->m_GPIOConfig;
}

/*
 *
 * <сводка>
 *   Функция set_LogicalPinNumber
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoGPIO1_K210Config_set_LogicalPinNumber(/* in */ struct IEcoGPIO1K210Config* me, /* in */ uint8_t LogicalPinNumber, /* in */ uint8_t BankNumber, /* in */ uint32_t PinNumber) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*)));
    ECO_GPIO_CONFIG_DESCRIPTOR* pDescriptor = 0;
    uint8_t index = 0;
    int16_t result = -1;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    pDescriptor = (ECO_GPIO_CONFIG_DESCRIPTOR*)pCMe->m_GPIOConfig;

    if (pDescriptor != 0) {
        for(index = 0; index < 32; index++) {
            if (PinNumber & (1 << index)) {
                if (BankNumber == 0) {
                    pDescriptor->LogicalPinMask[index] = LogicalPinNumber;
                    result = 0;
                }
                else if (BankNumber == 1) {
                    pDescriptor->LogicalPinMask[32 + index] = LogicalPinNumber;
                    result = 0;
                }
                break;
            }
        }
    }
    return result;
}

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoFPIOA1K210Config
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoFPIOA1_K210Config_QueryInterface(/* in */ struct IEcoFPIOA1K210Config* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1K210Config*)));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoGPIO1) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1K210Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoFPIOA1K210Config) ) {
        *ppv = &pCMe->m_pVTblIFPIOAConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoSYSCTL1K210Config) ) {
        *ppv = &pCMe->m_pVTblISYSCTLConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoFPIOA1K210Config
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoFPIOA1_K210Config_AddRef(/* in */ struct IEcoFPIOA1K210Config* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1K210Config*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;

}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoFPIOA1K210Config
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoFPIOA1_K210Config_Release(/* in */ struct IEcoFPIOA1K210Config* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1K210Config*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoGPIO1((IEcoGPIO1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция set_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoFPIOA1_K210Config_set_ConfigDescriptor(/* in */ struct IEcoFPIOA1K210Config* me, /* in */ ECO_FPIOA_CONFIG_DESCRIPTOR* config) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1K210Config*)));

    /* Проверка указателя */
    if (me == 0 || config == 0 ) {
        return -1;
    }

    pCMe->m_FPIOAConfig = config;

    return 0;
}


/*
 *
 * <сводка>
 *   Функция get_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
ECO_FPIOA_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoFPIOA1_K210Config_get_ConfigDescriptor(/* in */ struct IEcoFPIOA1K210Config* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1K210Config*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return 0;
    }

    return (ECO_FPIOA_CONFIG_DESCRIPTOR*)pCMe->m_FPIOAConfig;
}

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoSYSCTL1K210Config
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoSYSCTL1_K210Config_QueryInterface(/* in */ struct IEcoSYSCTL1K210Config* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1K210Config*) + sizeof(struct IEcoFPIOA1K210Config*)));

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoGPIO1) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoGPIO1K210Config) ) {
        *ppv = &pCMe->m_pVTblIGPIOConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoFPIOA1K210Config) ) {
        *ppv = &pCMe->m_pVTblIFPIOAConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoSYSCTL1K210Config) ) {
        *ppv = &pCMe->m_pVTblISYSCTLConfig;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIGPIO;
        pCMe->m_pVTblIGPIO->AddRef((IEcoGPIO1*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoSYSCTL1K210Config
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoSYSCTL1_K210Config_AddRef(/* in */ struct IEcoSYSCTL1K210Config* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1K210Config*) + sizeof(struct IEcoFPIOA1K210Config*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;

}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoSYSCTL1K210Config
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoSYSCTL1_K210Config_Release(/* in */ struct IEcoSYSCTL1K210Config* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1K210Config*) + sizeof(struct IEcoFPIOA1K210Config*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoGPIO1((IEcoGPIO1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция set_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoSYSCTL1_K210Config_set_ConfigDescriptor(/* in */ struct IEcoSYSCTL1K210Config* me, /* in */ ECO_SYSCTL_CONFIG_DESCRIPTOR* config) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1K210Config*) + sizeof(struct IEcoFPIOA1K210Config*)));

    /* Проверка указателя */
    if (me == 0 || config == 0 ) {
        return -1;
    }

    pCMe->m_SYSCTLConfig = config;

    return 0;
}

/*
 *
 * <сводка>
 *   Функция get_ConfigDescriptor
 * </сводка>
 *
 * <описание>
 *   Функция 
 * </описание>
 *
 */
ECO_SYSCTL_CONFIG_DESCRIPTOR* ECOCALLMETHOD CEcoSYSCTL1_K210Config_get_ConfigDescriptor(/* in */ struct IEcoSYSCTL1K210Config* me) {
    CEcoGPIO1* pCMe = (CEcoGPIO1*)((uint64_t)me - (sizeof(struct IEcoGPIO1*) + sizeof(struct IEcoGPIO1K210Config*) + sizeof(struct IEcoFPIOA1K210Config*)));

    /* Проверка указателя */
    if (me == 0 ) {
        return 0;
    }

    return (ECO_SYSCTL_CONFIG_DESCRIPTOR*)pCMe->m_SYSCTLConfig;
}

#endif

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoGPIO1(/*in*/ struct IEcoGPIO1* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    /*CEcoGPIO1* pCMe = (CEcoGPIO1*)me;*/
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Инициализация данных */

    return 0;
}

/* Create Virtual Table */
IEcoGPIO1VTbl g_x96EBAA047B4E4BDE914D8C3C57F48F2FVTbl_D01F101F = {
    CEcoGPIO1_QueryInterface,
    CEcoGPIO1_AddRef,
    CEcoGPIO1_Release,
    CEcoGPIO1_set_Mode,
    CEcoGPIO1_set_Data,
    CEcoGPIO1_get_Data
};

#ifdef ECO_AVR8
IEcoGPIO1AVR8ConfigVTbl g_4FAE0B1A4A5540239620F4699347A07FVTbl = {
    CEcoGPIO1_AVR8Config_QueryInterface,
    CEcoGPIO1_AVR8Config_AddRef,
    CEcoGPIO1_AVR8Config_Release,
    CEcoGPIO1_AVR8Config_set_ConfigDescriptor,
    CEcoGPIO1_AVR8Config_get_ConfigDescriptor,
    CEcoGPIO1_AVR8Config_set_LogicalPinNumber
};

/* Выделяем память под один экземпляр */
CEcoGPIO1 g_x96EBAA047B4E4BDE914D8C3C57F48F2FVTblGPIO = {
    &g_x96EBAA047B4E4BDE914D8C3C57F48F2FVTbl,
    &g_4FAE0B1A4A5540239620F4699347A07FVTbl,
    0, /* Ref */
    0, /* Mem */
    'A','B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#elif ECO_STM32
IEcoGPIO1STM32ConfigVTbl g_D9671208DCAD444890AA5F4825055DFAVTbl = {
    CEcoGPIO1_STM32Config_QueryInterface,
    CEcoGPIO1_STM32Config_AddRef,
    CEcoGPIO1_STM32Config_Release,
    CEcoGPIO1_STM32Config_set_ConfigDescriptor,
    CEcoGPIO1_STM32Config_get_ConfigDescriptor,
    CEcoGPIO1_STM32Config_set_LogicalPinNumber
};

IEcoRCC1STM32ConfigVTbl g_21F17A2862264966A6CEB207CDB6CB1CVTbl = {
    CEcoRCC1_STM32Config_QueryInterface,
    CEcoRCC1_STM32Config_AddRef,
    CEcoRCC1_STM32Config_Release,
    CEcoRCC1_STM32Config_set_ConfigDescriptor,
    CEcoRCC1_STM32Config_get_ConfigDescriptor,
};

/* Выделяем память под один экземпляр */
CEcoGPIO1 g_x96EBAA047B4E4BDE914D8C3C57F48F2FGPIO1_D01F101F = {
    &g_x96EBAA047B4E4BDE914D8C3C57F48F2FVTbl_D01F101F,
    &g_D9671208DCAD444890AA5F4825055DFAVTbl,
    &g_21F17A2862264966A6CEB207CDB6CB1CVTbl,
    0, /* Ref */
    0, /* Mem */
    0, /* RCC */
    'A','B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P',
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#elif ECO_BCM283X
IEcoGPIO1BCM283xConfigVTbl g_7B844D9CEA994E8695DDCA78668D0B2AVTbl = {
    CEcoGPIO1_BCM283xConfig_QueryInterface,
    CEcoGPIO1_BCM283xConfig_AddRef,
    CEcoGPIO1_BCM283xConfig_Release,
    CEcoGPIO1_BCM283xConfig_set_ConfigDescriptor,
    CEcoGPIO1_BCM283xConfig_get_ConfigDescriptor,
    CEcoGPIO1_BCM283xConfig_set_LogicalPinNumber
};

/* Выделяем память под один экземпляр */
CEcoGPIO1 g_x96EBAA047B4E4BDE914D8C3C57F48F2FVTblGPIO = {
    &g_x96EBAA047B4E4BDE914D8C3C57F48F2FVTbl,
    &g_7B844D9CEA994E8695DDCA78668D0B2AVTbl,
    0, /* Ref */
    0, /* Mem */
    0  /* Conf */
};

#elif ECO_K210
IEcoGPIO1K210ConfigVTbl g_3E002B7BB389408D9EDEB288C5DC2F30VTbl = {
    CEcoGPIO1_K210Config_QueryInterface,
    CEcoGPIO1_K210Config_AddRef,
    CEcoGPIO1_K210Config_Release,
    CEcoGPIO1_K210Config_set_ConfigDescriptor,
    CEcoGPIO1_K210Config_get_ConfigDescriptor,
    CEcoGPIO1_K210Config_set_LogicalPinNumber
};

IEcoFPIOA1K210ConfigVTbl g_D74C3896D5184D92B47AAD510B216A6BVTbl = {
    CEcoFPIOA1_K210Config_QueryInterface,
    CEcoFPIOA1_K210Config_AddRef,
    CEcoFPIOA1_K210Config_Release,
    CEcoFPIOA1_K210Config_set_ConfigDescriptor,
    CEcoFPIOA1_K210Config_get_ConfigDescriptor,
};

IEcoSYSCTL1K210ConfigVTbl g_BEADA64ACF0443ED836D39A5CDEEF7C0VTbl = {
    CEcoSYSCTL1_K210Config_QueryInterface,
    CEcoSYSCTL1_K210Config_AddRef,
    CEcoSYSCTL1_K210Config_Release,
    CEcoSYSCTL1_K210Config_set_ConfigDescriptor,
    CEcoSYSCTL1_K210Config_get_ConfigDescriptor,
};

/* Выделяем память под один экземпляр */
CEcoGPIO1 g_x96EBAA047B4E4BDE914D8C3C57F48F2FVTblGPIO = {
    &g_x96EBAA047B4E4BDE914D8C3C57F48F2FVTbl,
    &g_3E002B7BB389408D9EDEB288C5DC2F30VTbl,
    &g_D74C3896D5184D92B47AAD510B216A6BVTbl,
    &g_BEADA64ACF0443ED836D39A5CDEEF7C0VTbl,
    0, /* Ref */
    0, /* Mem */
    0, /* Conf */
    0, /* Conf */
    0  /* Conf */
};
#elif ECO_RISCV64
IEcoGPIO1RISCV64D1ConfigVTbl g_2C25EC2943B44E4583B43375FC35C4D6VTbl_D01F101F = {
    //CEcoGPIO1_K210Config_QueryInterface,
    //CEcoGPIO1_K210Config_AddRef,
    //CEcoGPIO1_K210Config_Release,
    //CEcoGPIO1_K210Config_set_ConfigDescriptor,
    //CEcoGPIO1_K210Config_get_ConfigDescriptor,
    //CEcoGPIO1_K210Config_set_LogicalPinNumber
};

/* Выделяем память под один экземпляр */
CEcoGPIO1 g_x96EBAA047B4E4BDE914D8C3C57F48F2FGPIO1_D01F101F = {
    &g_x96EBAA047B4E4BDE914D8C3C57F48F2FVTbl_D01F101F,
    &g_2C25EC2943B44E4583B43375FC35C4D6VTbl_D01F101F,
    0, /* Ref */
    0, /* Mem */
    0  /* Conf */
};
#endif

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoGPIO1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoGPIO1** ppIGPIO) {
    int16_t result = -1;
    CEcoGPIO1* pCMe = 0;

    /* Проверка указателей */
    if (ppIGPIO == 0 ) {
        return result;
    }

    /* Получение указателя на структуру компонента расположенной в области инициализированных данных */
    pCMe = &g_x96EBAA047B4E4BDE914D8C3C57F48F2FGPIO1_D01F101F;

    if (pCMe->m_cRef > 1) {
        pCMe->m_cRef++;
    } else {
        /* Установка счетчика ссылок на компонент */
        pCMe->m_cRef = 1;

    }

    /* Возврат указателя на интерфейс */
    *ppIGPIO = (IEcoGPIO1*)pCMe;

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoGPIO1(/* in */ IEcoGPIO1* pIGPIO) {
    /*CEcoGPIO1* pCMe = (CEcoGPIO1*)pIGPIO;*/
}
