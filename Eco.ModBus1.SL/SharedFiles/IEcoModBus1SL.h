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

#ifndef __I_ECOMODBUS1SL_H__
#define __I_ECOMODBUS1SL_H__

#include "IEcoBase1.h"

enum eEcoModBus1SLParity {
    ECO_MODBUS_1_MODE_NO   = 0,
    ECO_MODBUS_1_MODE_ODD  = 1,
    ECO_MODBUS_1_MODE_EVEN = 2
};

enum eEcoModBus1SLMode {
    ECO_MODBUS_1_MODE_RTU   = 0,
    ECO_MODBUS_1_MODE_ASCII = 1
};

enum eEcoModBus1SLStandard {
    ECO_MODBUS_1_STANDART_RS_485_2W = 0,
    ECO_MODBUS_1_STANDART_RS_232    = 1,
    ECO_MODBUS_1_STANDART_RS_485_4W = 2,
};

enum eEcoModBus1SLConnector {
    ECO_MODBUS_1_CONNECTOR_RJ_45 = 0
};

typedef struct ModBus1SLParams {
    uint8_t                     m_cAddr;
    uint8_t                     m_bBroadcast;
    uint32_t                    m_cBaudrate;
    enum eEcoModBus1SLParity    m_eParity;
    enum eEcoModBus1SLMode      m_eMode;
    enum eEcoModBus1SLStandard  m_eElectricalStandart;
    enum eEcoModBus1SLConnector m_eConnectorType;
} modbus_sl_param_t;

/* IEcoModBus1SL IID = {941CA1AA-5837-4485-AE01-0CBEAA9924D8} */
#ifndef __IID_IEcoModBus1SL
static const UGUID IID_IEcoModBus1SL = {0x01, 0x10, {0x94, 0x1C, 0xA1, 0xAA, 0x58, 0x37, 0x44, 0x85, 0xAE, 0x01, 0x0C, 0xBE, 0xAA, 0x99, 0x24, 0xD8}};
#endif /* __IID_IEcoModBus1SL */

typedef struct IEcoModBus1SL* IEcoModBus1SLPtr_t;

typedef struct IEcoModBus1SLVTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoModBus1SLPtr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoModBus1SLPtr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoModBus1SLPtr_t me);

    /* IEcoModBus1SL */
    int16_t (ECOCALLMETHOD *EmitMessage)(/* in */ IEcoModBus1SLPtr_t me, /* in */ byte_t* PDU, /* in */ uint32_t pduLength);
    int16_t (ECOCALLMETHOD *RecvMessage)(/* in */ IEcoModBus1SLPtr_t me, /* out */ byte_t** data, /* out */ uint32_t* dataLength);

    int16_t (ECOCALLMETHOD *ConnectBus)(/* in */ IEcoModBus1SLPtr_t me, /* in */ uint8_t isSlave, /* in */ byte_t* devName, /* in */ uint16_t nameLength);
    int16_t (ECOCALLMETHOD *DisconnectBus)(/* in */ IEcoModBus1SLPtr_t me);

    int16_t (ECOCALLMETHOD *SwitchCommunicationLED)(/* in */ IEcoModBus1SLPtr_t me, /* in */ uint8_t State);

    /* Сеттеры */
    int16_t (ECOCALLMETHOD *set_LEDEnabled)(/* in */ IEcoModBus1SLPtr_t me, /* in */ uint8_t State);
    int16_t (ECOCALLMETHOD *set_Slave)(/* in */ IEcoModBus1SLPtr_t me, /* in */ uint8_t isSlave);

} IEcoModBus1SLVTbl, *IEcoModBus1SLVTblPtr_t;

interface IEcoModBus1SL {
    struct IEcoModBus1SLVTbl *pVTbl;
} IEcoModBus1SL;

#endif /* __I_ECOMODBUS1SL_H__ */
