/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoModBus1TCP
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoModBus1TCP
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

#ifndef __I_ECOMODBUS1TCP_HPP__
#define __I_ECOMODBUS1TCP_HPP__

#include "IEcoBase1.hpp"

/* IEcoModBus1TCP IID = {93101775-F72E-4052-91C5-A51057CF0CA4} */
#ifndef __IID_IEcoModBus1TCP
static const UGUID IID_IEcoModBus1TCP = {0x01, 0x10, {0x93, 0x10, 0x17, 0x75, 0xF7, 0x2E, 0x40, 0x52, 0x91, 0xC5, 0xA5, 0x10, 0x57, 0xCF, 0x0C, 0xA4}};
#endif /* __IID_IEcoModBus1TCP */

interface IEcoModBus1TCP : public IEcoUnknown {
public:
    /* IEcoModBus1TCP */
    virtual int16_t ECOCALLMETHOD MyFunction(/* in */ char_t* Name, /* out */ char_t** CopyName) = 0;

};



#endif /* __I_ECOMODBUS1TCP_HPP__ */
