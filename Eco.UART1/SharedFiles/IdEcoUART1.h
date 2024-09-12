/*
 * <кодировка символов>
 *   Cyrillic (Windows) - Codepage 1251
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoUART1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoUART1
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

#ifndef __ID_ECO_UART_1_H__
#define __ID_ECO_UART_1_H__

#include "IEcoBase1.h"
#include "IEcoUART1.h"

/* EcoUART1 CID = {B40E129B-5662-4BD7-B5F8-339C025F3EF0} */
#ifndef __CID_EcoUART1
static const UGUID CID_EcoUART1 = {0x01, 0x10, {0xB4, 0x0E, 0x12, 0x9B, 0x56, 0x62, 0x4B, 0xD7, 0xB5, 0xF8, 0x33, 0x9C, 0x02, 0x5F, 0x3E, 0xF0}};
#endif /* __CID_EcoUART1 */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr(void);
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_B40E129B56624BD7B5F8339C025F3EF0;
#endif

#endif /* __ID_ECO_UART_1_H__ */
