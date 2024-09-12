/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoModBus1SL
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoModBus1SL
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

#ifndef __ID_ECOMODBUS1SL_H__
#define __ID_ECOMODBUS1SL_H__

#include "IEcoBase1.h"
#include "IEcoModBus1SL.h"

/* EcoModBus1SL CID = {DA26D759-A46F-405F-9977-CB5AA9153876} */
#ifndef __CID_EcoModBus1SL
static const UGUID CID_EcoModBus1SL = {0x01, 0x10, {0xDA, 0x26, 0xD7, 0x59, 0xA4, 0x6F, 0x40, 0x5F, 0x99, 0x77, 0xCB, 0x5A, 0xA9, 0x15, 0x38, 0x76}};
#endif /* __CID_EcoModBus1SL */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_DA26D759A46F405F9977CB5AA9153876;
#endif

#endif /* __ID_ECOMODBUS1SL_H__ */
