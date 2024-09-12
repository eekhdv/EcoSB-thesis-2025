/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoModBus1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoModBus1
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

#ifndef __ID_ECOMODBUS1_H__
#define __ID_ECOMODBUS1_H__

#include "IEcoBase1.h"
#include "IEcoModBus1.h"

/* EcoModBus1 CID = {D3D7232D-DB69-4046-9D2B-535BA10E8757} */
#ifndef __CID_EcoModBus1
static const UGUID CID_EcoModBus1 = {0x01, 0x10, {0xD3, 0xD7, 0x23, 0x2D, 0xDB, 0x69, 0x40, 0x46, 0x9D, 0x2B, 0x53, 0x5B, 0xA1, 0x0E, 0x87, 0x57}};
#endif /* __CID_EcoModBus1 */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_D3D7232DDB6940469D2B535BA10E8757;
#endif

#endif /* __ID_ECOMODBUS1_H__ */
