/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoGPIO1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает реализацию интерфейса IdEcoGPIO1
 *
 * 
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2019 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __ID_ECO_GPIO_1_H__
#define __ID_ECO_GPIO_1_H__

#include "IEcoBase1.h"
#include "IEcoGPIO1.h"

/* EcoGPIO1 CID = {A70A4C2E-9C96-45BD-9136-7754D01F101F} */
#ifndef __CID_EcoGPIO1
static const UGUID CID_EcoGPIO1 = { 0x01, 0x10, 0xa7, 0x0a, 0x4c, 0x2e, 0x9c, 0x96, 0x45, 0xbd, 0x91, 0x36, 0x77, 0x54, 0xd0, 0x1f, 0x10, 0x1f };
#endif /* __CID_EcoGPIO1 */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_A70A4C2E9C9645BD91367754D01F101F;
#endif

#endif /* __ID_ECO_GPIO_1_H__ */
