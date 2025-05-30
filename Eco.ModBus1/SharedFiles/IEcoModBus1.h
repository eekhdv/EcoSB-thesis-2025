/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoModBus1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoModBus1
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

#ifndef __I_ECO_MODBUS_1_H__
#define __I_ECO_MODBUS_1_H__

#include "IEcoBase1.h"


#define ECO_MB_FUNCTION_CODE_LENGTH    0x1    /* 1 byte for function code */
#define ECO_MB_SUBCODE_LENGTH          0x2    /* 2 bytes for subcode */

/* Function codes descriptions */
#define ECO_MB_FC_READ_COILS                        0x01    /* Read Coils. */
#define ECO_MB_FC_READ_DISCRETE_INPUTS              0x02    /* Read Discrete Inputs. */
#define ECO_MB_FC_WRITE_SINGLE_COIL                 0x05    /* Write Single Coil */
#define ECO_MB_FC_WRITE_MULTIPLE_COILS              0x0F    /* Write Multiple Coils */

#define ECO_MB_FC_READ_INPUT_REGISTER               0x04    /* Read Input Register */
#define ECO_MB_FC_READ_HOLDING_REGISTERS            0x03    /* Read Holding Registers */
#define ECO_MB_FC_WRITE_SINGLE_REGISTER             0x06    /* Write Single Register */
#define ECO_MB_FC_WRITE_MULTIPLE_REGISTERS          0x10    /* Write Multiple Registers */
#define ECO_MB_FC_READ_WRITE_MULTIPLE_REGISTERS     0x17    /* Read/Write Multiple Registers */
#define ECO_MB_FC_MASK_WRITE_REGISTER               0x16    /* Mask Write Register */
#define ECO_MB_FC_READ_FIFO_QUEUE                   0x18    /* Read FIFO queue */

#define ECO_MB_FC_READ_FILE_RECORD                  0x14    /* Read File record */
#define ECO_MB_FC_WRITE_FILE_RECORD                 0x15    /* Write File record */

#define ECO_MB_FC_READ_EXCEPTION_STATUS             0x07    /* Read Exception status */
#define ECO_MB_FC_DIAGNOSTIC                        0x08    /* Diagnostic */ /* Sub-code: 0 - 18, 20 */
#define ECO_MB_FC_GET_COM_EVENT_COUNTER             0x0B    /* Get Com event counter */
#define ECO_MB_FC_GET_COM_EVENT_LOG                 0x0C    /* Get Com Event Log */
#define ECO_MB_FC_REPORT_SERVER_ID                  0x11    /* Report Server ID */
#define ECO_MB_FC_READ_DEVICE_IDENTIFICATION        0x2B    /* Read device Identification */ /* Sub-code: 14 */

#define ECO_MB_FC_ENCAPSULATED_INTERFACE_TRANSPORT  0x2B    /* Encapsulated Interface Transport */ /* Sub-code: 13, 14 */
#define ECO_MB_FC_CANOPEN_GENERAL_REFERENCE         0x2B    /* CANopen General Reference */ /* Sub-code: 13 */

/* MODBUS Exception Codes */
#define ECO_MB_EC_ILLEGAL_FUNCTION                        0x01    /* The function code received in the query is not an allowable action for the server. */
#define ECO_MB_EC_ILLEGAL_DATA_ADDRESS                    0x02    /* The data address received in the query is not an allowable address for the server. */
#define ECO_MB_EC_ILLEGAL_DATA_VALUE                      0x03    /* A value contained in the query data field is not an
allowable value for server. */
#define ECO_MB_EC_SERVER_DEVICE_FAILURE                   0x04    /* An unrecoverable error occurred while the server
was attempting to perform the requested action. */
#define ECO_MB_EC_ACKNOWLEDGE                             0x05    /* Specialized use in conjunction with programming
commands. */
#define ECO_MB_EC_SERVER_DEVICE_BUSY                      0x06    /* Specialized use in conjunction with programming
commands. */
#define ECO_MB_EC_MEMORY_PARITY_ERROR                     0x08    /* See in docs. */
#define ECO_MB_EC_GATEWAY_PATH_UNAVAILABLE                0x0A    /* See in docs. */
#define ECO_MB_EC_GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND 0x0B    /* See in docs. */


union ResultCode {
  struct {
    uint8_t ErrorCode;
    uint8_t ExceptionCode;
  } except_rsp_pdu_t;

  int16_t result;
};


/* IEcoModBus1 IID = {74AB8CD0-056F-4D04-8F85-5D2FC8A9F3D0} */
#ifndef __IID_IEcoModBus1
static const UGUID IID_IEcoModBus1 = {0x01, 0x10, {0x74, 0xAB, 0x8C, 0xD0, 0x05, 0x6F, 0x4D, 0x04, 0x8F, 0x85, 0x5D, 0x2F, 0xC8, 0xA9, 0xF3, 0xD0}};
#endif /* __IID_IEcoModBus1 */

typedef struct IEcoModBus1* IEcoModBus1Ptr_t;

typedef struct IEcoModBus1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ IEcoModBus1Ptr_t me, /* in */ const UGUID* riid, /* out */ voidptr_t* ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ IEcoModBus1Ptr_t me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ IEcoModBus1Ptr_t me);

    /* IEcoModBus1 */
    int16_t (ECOCALLMETHOD *EncodePDU)(/* in */ IEcoModBus1Ptr_t me, /* in */ uint8_t functionCode, /* in */ uint16_t subCode, /* in */ byte_t* Data, /* in */ uint32_t dataLength, /* out */ byte_t** PDU, /* out */ uint32_t* pduLength);
    int16_t (ECOCALLMETHOD *DecodePDU)(/* in */ IEcoModBus1Ptr_t me, /* in */ byte_t* PDU, /* in */ uint32_t pduLength, /* out */ uint8_t* functionCode, /* in */ uint16_t* subCode, /* in */ byte_t** Data, /* in */ uint32_t* dataLength);

} IEcoModBus1VTbl, *IEcoModBus1VTblPtr_t;

interface IEcoModBus1 {
    struct IEcoModBus1VTbl *pVTbl;
} IEcoModBus1;


#endif /* __I_ECO_MODBUS_1_H__ */
