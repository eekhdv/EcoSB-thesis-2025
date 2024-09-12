/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoModBus1SL
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoModBus1SL
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

#ifndef __I_ECOMODBUS1SL_HPP__
#define __I_ECOMODBUS1SL_HPP__

#include "IEcoBase1.hpp"

/* IEcoModBus1SL IID = {941CA1AA-5837-4485-AE01-0CBEAA9924D8} */
#ifndef __IID_IEcoModBus1SL
static const UGUID IID_IEcoModBus1SL = {0x01, 0x10, {0x94, 0x1C, 0xA1, 0xAA, 0x58, 0x37, 0x44, 0x85, 0xAE, 0x01, 0x0C, 0xBE, 0xAA, 0x99, 0x24, 0xD8}};
#endif /* __IID_IEcoModBus1SL */

interface IEcoModBus1SL : public IEcoUnknown {
public:
    /* IEcoModBus1SL */
    virtual int16_t ECOCALLMETHOD MyFunction(/* in */ char_t* Name, /* out */ char_t** CopyName) = 0;

};



#endif /* __I_ECOMODBUS1SL_HPP__ */
