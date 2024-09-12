/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoModBus1TCP
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoModBus1TCP
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

#ifndef __ID_ECOMODBUS1TCP_HPP__
#define __ID_ECOMODBUS1TCP_HPP__

#include "IEcoBase1.hpp"
#include "IEcoModBus1TCP.hpp"

/* EcoModBus1TCP CID = {7A956018-B6B3-4FAE-806E-5A5EE7CA43E2} */
#ifndef __CID_EcoModBus1TCP
static const UGUID CID_EcoModBus1TCP = {0x01, 0x10, {0x7A, 0x95, 0x60, 0x18, 0xB6, 0xB3, 0x4F, 0xAE, 0x80, 0x6E, 0x5A, 0x5E, 0xE7, 0xCA, 0x43, 0xE2}};
#endif /* __CID_EcoModBus1TCP */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern "C" IEcoComponentFactory* GetIEcoComponentFactoryPtr_7A956018B6B34FAE806E5A5EE7CA43E2;
#endif

#endif /* __ID_ECOMODBUS1TCP_HPP__ */
