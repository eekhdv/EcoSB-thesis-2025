/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoModBus1OPC
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoModBus1OPC
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

#ifndef __ID_ECOMODBUS1OPC_HPP__
#define __ID_ECOMODBUS1OPC_HPP__

#include "IEcoBase1.hpp"
#include "IEcoModBus1OPC.hpp"

/* EcoModBus1OPC CID = {F37B74AD-4582-4C10-9898-1A99C35C9FC5} */
#ifndef __CID_EcoModBus1OPC
static const UGUID CID_EcoModBus1OPC = {0x01, 0x10, {0xF3, 0x7B, 0x74, 0xAD, 0x45, 0x82, 0x4C, 0x10, 0x98, 0x98, 0x1A, 0x99, 0xC3, 0x5C, 0x9F, 0xC5}};
#endif /* __CID_EcoModBus1OPC */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern "C" IEcoComponentFactory* GetIEcoComponentFactoryPtr_F37B74AD45824C1098981A99C35C9FC5;
#endif

#endif /* __ID_ECOMODBUS1OPC_HPP__ */
