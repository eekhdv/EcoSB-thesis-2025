/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoModBus1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IdEcoMemoryManager1.h"
#include "IdEcoString1.h"
#include "IdEcoList1.h"
#include "IdEcoLog1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoModBus1.h"
#include "IEcoModBus1.h"
#include "IEcoSystem1.h"
#include "IEcoLog1ConsoleAffiliate.h"


/* Указатель на интерфейс работы с логами */
static IEcoLog1* g_pILog = 0;

enum eEcoLog1Level LogLevel = ECO_LOG_1_LEVEL_DEBUG | ECO_LOG_1_LEVEL_ERROR;


int TestCaseReadCoils(IEcoModBus1* pIEcoModBus1, IEcoMemoryAllocator1* pIMem)
{
    int16_t ResultEncode = -1, ResultDecode = -1;
    uint8_t EncodeFunctionCode, DecodeFunctionCode;
    uint32_t EncodePduLength, EncodeDataLength, DecodeDataLength;

    byte_t *EncodedPDU = 0, *DecodeData = 0;

    EncodeDataLength = 4;
    EncodeFunctionCode = 0x01;
    byte_t EncodeData[] = { 0x00 , 0x13 , 0x00 , 0x13 };

    ResultEncode = pIEcoModBus1->pVTbl->EncodePDU(pIEcoModBus1, EncodeFunctionCode, 0, EncodeData, EncodeDataLength, &EncodedPDU, &EncodePduLength);
    ResultDecode = pIEcoModBus1->pVTbl->DecodePDU(pIEcoModBus1, EncodedPDU, EncodeDataLength, &DecodeFunctionCode, NULL, &DecodeData, &DecodeDataLength);

    if (ResultEncode != ERR_ECO_SUCCESES || ResultDecode != 0 || EncodeFunctionCode != DecodeFunctionCode || EncodeDataLength != DecodeDataLength)
    {
        if (ResultEncode != ERR_ECO_SUCCESES)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Enoding!", EncodeFunctionCode);
        else if (ResultDecode != 0)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Decoding!", ResultDecode);
        else if (EncodeFunctionCode != DecodeFunctionCode)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect function code! [%d]", EncodeFunctionCode, DecodeFunctionCode);
        else if (EncodeDataLength != DecodeDataLength)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect DataLength [%d/%d]!", EncodeFunctionCode, EncodeDataLength, DecodeDataLength);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
    }
    for (uint32_t i = 0; i < DecodeDataLength; i++)
    {
      if (EncodeData[i] != DecodeData[i])
      {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] Encode != Decode %d!", EncodeFunctionCode, i);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
      }
    }
    return 0;
}

int TestCaseReadDiscreteInputs(IEcoModBus1* pIEcoModBus1, IEcoMemoryAllocator1* pIMem)
{
    int16_t ResultEncode = -1, ResultDecode = -1;
    uint8_t EncodeFunctionCode, DecodeFunctionCode;
    uint32_t EncodePduLength, EncodeDataLength, DecodeDataLength;

    byte_t *EncodedPDU = 0, *DecodeData = 0;

    EncodeDataLength = 4;
    EncodeFunctionCode = 0x02;
    byte_t EncodeData[] = { 0x00, 0xC4, 0x00, 0x16 };

    ResultEncode = pIEcoModBus1->pVTbl->EncodePDU(pIEcoModBus1, EncodeFunctionCode, 0, EncodeData, EncodeDataLength, &EncodedPDU, &EncodePduLength);
    ResultDecode = pIEcoModBus1->pVTbl->DecodePDU(pIEcoModBus1, EncodedPDU, EncodeDataLength, &DecodeFunctionCode, NULL, &DecodeData, &DecodeDataLength);

    if (ResultEncode != 0 || ResultDecode != 0 || EncodeFunctionCode != DecodeFunctionCode || EncodeDataLength != DecodeDataLength)
    {
        if (ResultEncode != ERR_ECO_SUCCESES)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Enoding!", EncodeFunctionCode);
        else if (ResultDecode != 0)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Decoding!", ResultDecode);
        else if (EncodeFunctionCode != DecodeFunctionCode)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect function code! [%d]", EncodeFunctionCode, DecodeFunctionCode);
        else if (EncodeDataLength != DecodeDataLength)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect DataLength [%d/%d]!", EncodeFunctionCode, EncodeDataLength, DecodeDataLength);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
    }
    for (uint32_t i = 0; i < DecodeDataLength; i++)
    {
      if (EncodeData[i] != DecodeData[i])
      {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] Encode != Decode %d!", EncodeFunctionCode, i);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
      }
    }
    return 0;
}

int TestCaseReadHoldingRegisters(IEcoModBus1* pIEcoModBus1, IEcoMemoryAllocator1* pIMem)
{
    int16_t ResultEncode = -1, ResultDecode = -1;
    uint8_t EncodeFunctionCode, DecodeFunctionCode;
    uint32_t EncodePduLength, EncodeDataLength, DecodeDataLength;

    byte_t *EncodedPDU = 0, *DecodeData = 0;

    EncodeDataLength = 4;
    EncodeFunctionCode = 0x03;
    byte_t EncodeData[] = { 0x00, 0x6B, 0x00, 0x03 };

    ResultEncode = pIEcoModBus1->pVTbl->EncodePDU(pIEcoModBus1, EncodeFunctionCode, 0, EncodeData, EncodeDataLength, &EncodedPDU, &EncodePduLength);
    ResultDecode = pIEcoModBus1->pVTbl->DecodePDU(pIEcoModBus1, EncodedPDU, EncodeDataLength, &DecodeFunctionCode, NULL, &DecodeData, &DecodeDataLength);

    if (ResultEncode != 0 || ResultDecode != 0 || EncodeFunctionCode != DecodeFunctionCode || EncodeDataLength != DecodeDataLength)
    {
        if (ResultEncode != ERR_ECO_SUCCESES)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Enoding!", EncodeFunctionCode);
        else if (ResultDecode != 0)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Decoding!", ResultDecode);
        else if (EncodeFunctionCode != DecodeFunctionCode)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect function code! [%d]", EncodeFunctionCode, DecodeFunctionCode);
        else if (EncodeDataLength != DecodeDataLength)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect DataLength [%d/%d]!", EncodeFunctionCode, EncodeDataLength, DecodeDataLength);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
    }
    for (uint32_t i = 0; i < DecodeDataLength; i++)
    {
      if (EncodeData[i] != DecodeData[i])
      {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] Encode != Decode %d!", EncodeFunctionCode, i);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
      }
    }
    return 0;
}

int TestCaseReadInputRegisters(IEcoModBus1* pIEcoModBus1, IEcoMemoryAllocator1* pIMem)
{
    int16_t ResultEncode = -1, ResultDecode = -1;
    uint8_t EncodeFunctionCode, DecodeFunctionCode;
    uint32_t EncodePduLength, EncodeDataLength, DecodeDataLength;

    byte_t *EncodedPDU = 0, *DecodeData = 0;

    EncodeDataLength = 4;
    EncodeFunctionCode = 0x04;
    byte_t EncodeData[] = { 0x00, 0x08, 0x00, 0x01 };

    ResultEncode = pIEcoModBus1->pVTbl->EncodePDU(pIEcoModBus1, EncodeFunctionCode, 0, EncodeData, EncodeDataLength, &EncodedPDU, &EncodePduLength);
    ResultDecode = pIEcoModBus1->pVTbl->DecodePDU(pIEcoModBus1, EncodedPDU, EncodeDataLength, &DecodeFunctionCode, NULL, &DecodeData, &DecodeDataLength);

    if (ResultEncode != 0 || ResultDecode != 0 || EncodeFunctionCode != DecodeFunctionCode || EncodeDataLength != DecodeDataLength)
    {
        if (ResultEncode != ERR_ECO_SUCCESES)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Enoding!", EncodeFunctionCode);
        else if (ResultDecode != 0)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Decoding!", ResultDecode);
        else if (EncodeFunctionCode != DecodeFunctionCode)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect function code! [%d]", EncodeFunctionCode, DecodeFunctionCode);
        else if (EncodeDataLength != DecodeDataLength)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect DataLength [%d/%d]!", EncodeFunctionCode, EncodeDataLength, DecodeDataLength);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
    }
    for (uint32_t i = 0; i < DecodeDataLength; i++)
    {
      if (EncodeData[i] != DecodeData[i])
      {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] Encode != Decode %d!", EncodeFunctionCode, i);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
      }
    }
    return 0;
}

int TestCaseWriteSingleCoil(IEcoModBus1* pIEcoModBus1, IEcoMemoryAllocator1* pIMem)
{
    int16_t ResultEncode = -1, ResultDecode = -1;
    uint8_t EncodeFunctionCode, DecodeFunctionCode;
    uint32_t EncodePduLength, EncodeDataLength, DecodeDataLength;

    byte_t *EncodedPDU = 0, *DecodeData = 0;

    EncodeDataLength = 4;
    EncodeFunctionCode = 0x05;
    byte_t EncodeData[] = { 0x00, 0xAC, 0xFF, 0x00 };

    ResultEncode = pIEcoModBus1->pVTbl->EncodePDU(pIEcoModBus1, EncodeFunctionCode, 0, EncodeData, EncodeDataLength, &EncodedPDU, &EncodePduLength);
    ResultDecode = pIEcoModBus1->pVTbl->DecodePDU(pIEcoModBus1, EncodedPDU, EncodeDataLength, &DecodeFunctionCode, NULL, &DecodeData, &DecodeDataLength);

    if (ResultEncode != 0 || ResultDecode != 0 || EncodeFunctionCode != DecodeFunctionCode || EncodeDataLength != DecodeDataLength)
    {
        if (ResultEncode != ERR_ECO_SUCCESES)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Enoding!", EncodeFunctionCode);
        else if (ResultDecode != 0)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Decoding!", ResultDecode);
        else if (EncodeFunctionCode != DecodeFunctionCode)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect function code! [%d]", EncodeFunctionCode, DecodeFunctionCode);
        else if (EncodeDataLength != DecodeDataLength)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect DataLength [%d/%d]!", EncodeFunctionCode, EncodeDataLength, DecodeDataLength);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
    }
    for (uint32_t i = 0; i < DecodeDataLength; i++)
    {
      if (EncodeData[i] != DecodeData[i])
      {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] Encode != Decode %d!", EncodeFunctionCode, i);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
      }
    }
    return 0;
}

int TestCaseWriteSingleRegister(IEcoModBus1* pIEcoModBus1, IEcoMemoryAllocator1* pIMem)
{
    int16_t ResultEncode = -1, ResultDecode = -1;
    uint8_t EncodeFunctionCode, DecodeFunctionCode;
    uint32_t EncodePduLength, EncodeDataLength, DecodeDataLength;

    byte_t *EncodedPDU = 0, *DecodeData = 0;

    EncodeDataLength = 4;
    EncodeFunctionCode = 0x06;
    byte_t EncodeData[] = { 0x00, 0x01, 0x00, 0x03 };

    ResultEncode = pIEcoModBus1->pVTbl->EncodePDU(pIEcoModBus1, EncodeFunctionCode, 0, EncodeData, EncodeDataLength, &EncodedPDU, &EncodePduLength);
    ResultDecode = pIEcoModBus1->pVTbl->DecodePDU(pIEcoModBus1, EncodedPDU, EncodeDataLength, &DecodeFunctionCode, NULL, &DecodeData, &DecodeDataLength);

    if (ResultEncode != 0 || ResultDecode != 0 || EncodeFunctionCode != DecodeFunctionCode || EncodeDataLength != DecodeDataLength)
    {
        if (ResultEncode != ERR_ECO_SUCCESES)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Enoding!", EncodeFunctionCode);
        else if (ResultDecode != 0)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Decoding!", ResultDecode);
        else if (EncodeFunctionCode != DecodeFunctionCode)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect function code! [%d]", EncodeFunctionCode, DecodeFunctionCode);
        else if (EncodeDataLength != DecodeDataLength)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect DataLength [%d/%d]!", EncodeFunctionCode, EncodeDataLength, DecodeDataLength);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
    }
    for (uint32_t i = 0; i < DecodeDataLength; i++)
    {
      if (EncodeData[i] != DecodeData[i])
      {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] Encode != Decode %d!", EncodeFunctionCode, i);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
      }
    }
    return 0;
}

int TestCaseWriteMultipleCoils(IEcoModBus1* pIEcoModBus1, IEcoMemoryAllocator1* pIMem)
{
    int16_t ResultEncode = -1, ResultDecode = -1;
    uint8_t EncodeFunctionCode, DecodeFunctionCode;
    uint32_t EncodePduLength, EncodeDataLength, DecodeDataLength;

    byte_t *EncodedPDU = 0, *DecodeData = 0;

    EncodeDataLength = 7;
    EncodeFunctionCode = 0x0F;
    byte_t EncodeData[] = { 0x00, 0x13, 0x00, 0x0A, 0x02, 0xCD, 0x01 };

    ResultEncode = pIEcoModBus1->pVTbl->EncodePDU(pIEcoModBus1, EncodeFunctionCode, 0, EncodeData, EncodeDataLength, &EncodedPDU, &EncodePduLength);
    ResultDecode = pIEcoModBus1->pVTbl->DecodePDU(pIEcoModBus1, EncodedPDU, EncodeDataLength, &DecodeFunctionCode, NULL, &DecodeData, &DecodeDataLength);

    if (ResultEncode != 0 || ResultDecode != 0 || EncodeFunctionCode != DecodeFunctionCode || EncodeDataLength < DecodeDataLength)
    {
        if (ResultEncode != ERR_ECO_SUCCESES)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Enoding!", EncodeFunctionCode);
        else if (ResultDecode != 0)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Decoding!", ResultDecode);
        else if (EncodeFunctionCode != DecodeFunctionCode)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect function code! [%d]", EncodeFunctionCode, DecodeFunctionCode);
        else if (EncodeDataLength != DecodeDataLength)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect DataLength [%d < %d]!", EncodeFunctionCode, EncodeDataLength, DecodeDataLength);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
    }
    // TODO:
    // for (uint32_t i = 0; i < DecodeDataLength; i++)
    // {
    //   if (EncodeData[i] != DecodeData[i])
    //   {
    //     g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] Encode != Decode %d!", EncodeFunctionCode, i);
    //     pIMem->pVTbl->Free(pIMem, EncodedPDU);
    //     pIMem->pVTbl->Free(pIMem, DecodeData);
    //     return -1;
    //   }
    // }
    return 0;
}

int TestCaseWriteMultipleRegisters(IEcoModBus1* pIEcoModBus1, IEcoMemoryAllocator1* pIMem)
{
    int16_t ResultEncode = -1, ResultDecode = -1;
    uint8_t EncodeFunctionCode, DecodeFunctionCode;
    uint32_t EncodePduLength, EncodeDataLength, DecodeDataLength;

    byte_t *EncodedPDU = 0, *DecodeData = 0;

    EncodeDataLength = 9;
    EncodeFunctionCode = 0x10;
    byte_t EncodeData[] = { 0x00, 0x01, 0x00, 0x02, 0x04, 0x00, 0x0A, 0x01, 0x02 };

    ResultEncode = pIEcoModBus1->pVTbl->EncodePDU(pIEcoModBus1, EncodeFunctionCode, 0, EncodeData, EncodeDataLength, &EncodedPDU, &EncodePduLength);
    ResultDecode = pIEcoModBus1->pVTbl->DecodePDU(pIEcoModBus1, EncodedPDU, EncodeDataLength, &DecodeFunctionCode, NULL, &DecodeData, &DecodeDataLength);

    if (ResultEncode != 0 || ResultDecode != 0 || EncodeFunctionCode != DecodeFunctionCode || EncodeDataLength > DecodeDataLength)
    {
        if (ResultEncode != ERR_ECO_SUCCESES)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Enoding!", EncodeFunctionCode);
        else if (ResultDecode != 0)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Decoding!", ResultDecode);
        else if (EncodeFunctionCode != DecodeFunctionCode)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect function code! [%d]", EncodeFunctionCode, DecodeFunctionCode);
        else if (EncodeDataLength != DecodeDataLength)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect DataLength [%d > %d]!", EncodeFunctionCode, EncodeDataLength, DecodeDataLength);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
    }
    // TODO:
    // for (uint32_t i = 0; i < DecodeDataLength; i++)
    // {
    //   if (EncodeData[i] != DecodeData[i])
    //   {
    //     g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] Encode != Decode %d!", EncodeFunctionCode, i);
    //     pIMem->pVTbl->Free(pIMem, EncodedPDU);
    //     pIMem->pVTbl->Free(pIMem, DecodeData);
    //     return -1;
    //   }
    // }
    return 0;
}

int TestCaseReadFileRecord(IEcoModBus1* pIEcoModBus1, IEcoMemoryAllocator1* pIMem)
{
    int16_t ResultEncode = -1, ResultDecode = -1;
    uint8_t EncodeFunctionCode, DecodeFunctionCode;
    uint32_t EncodePduLength, EncodeDataLength, DecodeDataLength;

    byte_t *EncodedPDU = 0, *DecodeData = 0;

    EncodeDataLength = 15;
    EncodeFunctionCode = 0x14;
    byte_t EncodeData[] = { 0x0E , 0x06 , 0x00 , 0x04 , 0x00 , 0x01 , 0x00 , 0x02 , 0x06 , 0x00 , 0x03 , 0x00 , 0x09 , 0x00 , 0x02 };

    ResultEncode = pIEcoModBus1->pVTbl->EncodePDU(pIEcoModBus1, EncodeFunctionCode, 0, EncodeData, EncodeDataLength, &EncodedPDU, &EncodePduLength);
    ResultDecode = pIEcoModBus1->pVTbl->DecodePDU(pIEcoModBus1, EncodedPDU, EncodeDataLength, &DecodeFunctionCode, NULL, &DecodeData, &DecodeDataLength);

    if (ResultEncode != 0 || ResultDecode != 0 || EncodeFunctionCode != DecodeFunctionCode || EncodeDataLength != DecodeDataLength)
    {
        if (ResultEncode != ERR_ECO_SUCCESES)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Enoding!", EncodeFunctionCode);
        else if (ResultDecode != 0)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Decoding!", ResultDecode);
        else if (EncodeFunctionCode != DecodeFunctionCode)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect function code! [%d]", EncodeFunctionCode, DecodeFunctionCode);
        else if (EncodeDataLength != DecodeDataLength)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect DataLength [%d/%d]!", EncodeFunctionCode, EncodeDataLength, DecodeDataLength);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
    }
    for (uint32_t i = 0; i < DecodeDataLength; i++)
    {
      if (EncodeData[i] != DecodeData[i])
      {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] Encode != Decode %d!", EncodeFunctionCode, i);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
      }
    }
    return 0;
}

int TestCaseWriteFileRecord(IEcoModBus1* pIEcoModBus1, IEcoMemoryAllocator1* pIMem)
{
    int16_t ResultEncode = -1, ResultDecode = -1;
    uint8_t EncodeFunctionCode, DecodeFunctionCode;
    uint32_t EncodePduLength, EncodeDataLength, DecodeDataLength;

    byte_t *EncodedPDU = 0, *DecodeData = 0;

    EncodeDataLength = 14;
    EncodeFunctionCode = 0x15;
    byte_t EncodeData[] = { 0x0D , 0x06 , 0x00 , 0x04 , 0x00 , 0x07 , 0x00 , 0x03 , 0x06 , 0xAF , 0x04 , 0xBE , 0x10 , 0x0D };

    ResultEncode = pIEcoModBus1->pVTbl->EncodePDU(pIEcoModBus1, EncodeFunctionCode, 0, EncodeData, EncodeDataLength, &EncodedPDU, &EncodePduLength);
    ResultDecode = pIEcoModBus1->pVTbl->DecodePDU(pIEcoModBus1, EncodedPDU, EncodeDataLength, &DecodeFunctionCode, NULL, &DecodeData, &DecodeDataLength);

    if (ResultEncode != 0 || ResultDecode != 0 || EncodeFunctionCode != DecodeFunctionCode || EncodeDataLength != DecodeDataLength)
    {
        if (ResultEncode != ERR_ECO_SUCCESES)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Enoding!", EncodeFunctionCode);
        else if (ResultDecode != 0)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Decoding!", ResultDecode);
        else if (EncodeFunctionCode != DecodeFunctionCode)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect function code! [%d]", EncodeFunctionCode, DecodeFunctionCode);
        else if (EncodeDataLength != DecodeDataLength)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect DataLength [%d/%d]!", EncodeFunctionCode, EncodeDataLength, DecodeDataLength);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
    }
    for (uint32_t i = 0; i < DecodeDataLength; i++)
    {
      if (EncodeData[i] != DecodeData[i])
      {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] Encode != Decode %d!", EncodeFunctionCode, i);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
      }
    }
    return 0;
}

int TestCaseMaskWriteRegister(IEcoModBus1* pIEcoModBus1, IEcoMemoryAllocator1* pIMem)
{
    int16_t ResultEncode = -1, ResultDecode = -1;
    uint8_t EncodeFunctionCode, DecodeFunctionCode;
    uint32_t EncodePduLength, EncodeDataLength, DecodeDataLength;

    byte_t *DecodeData = 0, *EncodedPDU = 0;

    EncodeDataLength = 6;
    byte_t EncodeData[] = { 0x00 , 0x04, 0x00, 0xF2, 0x00, 0x25 };

    EncodeFunctionCode = 0x16;
    ResultEncode = pIEcoModBus1->pVTbl->EncodePDU(pIEcoModBus1, EncodeFunctionCode, 0, EncodeData, EncodeDataLength, &EncodedPDU, &EncodePduLength);
    ResultDecode = pIEcoModBus1->pVTbl->DecodePDU(pIEcoModBus1, EncodedPDU, EncodeDataLength, &DecodeFunctionCode, NULL, &DecodeData, &DecodeDataLength);

    if (ResultEncode != 0 || ResultDecode != 0 || EncodeFunctionCode != DecodeFunctionCode || EncodeDataLength != DecodeDataLength)
    {
        if (ResultEncode != ERR_ECO_SUCCESES)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Enoding!", EncodeFunctionCode);
        else if (ResultDecode != 0)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Decoding!", ResultDecode);
        else if (EncodeFunctionCode != DecodeFunctionCode)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect function code! [%d]", EncodeFunctionCode, DecodeFunctionCode);
        else if (EncodeDataLength != DecodeDataLength)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect DataLength [%d/%d]!", EncodeFunctionCode, EncodeDataLength, DecodeDataLength);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
    }
    for (uint32_t i = 0; i < DecodeDataLength; i++)
    {
      if (EncodeData[i] != DecodeData[i])
      {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] Encode != Decode %d!", EncodeFunctionCode, i);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
      }
    }
    return 0;
}

int TestCaseReadWriteMultipleRegister(IEcoModBus1* pIEcoModBus1, IEcoMemoryAllocator1* pIMem)
{
    int16_t ResultEncode = -1, ResultDecode = -1;
    uint8_t EncodeFunctionCode, DecodeFunctionCode;
    uint32_t EncodePduLength, EncodeDataLength, DecodeDataLength;

    byte_t *DecodeData = 0;
    byte_t *EncodedPDU = 0;

    EncodeDataLength = 15;
    byte_t EncodeData[] = { 0x00, 0x03, 0x00, 0x06, 0x00, 0x0E, 0x00, 0x03, 0x06, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF };
    EncodeFunctionCode = 0x17;

    ResultEncode = pIEcoModBus1->pVTbl->EncodePDU(pIEcoModBus1, EncodeFunctionCode, 0, EncodeData, EncodeDataLength, &EncodedPDU, &EncodePduLength);
    ResultDecode = pIEcoModBus1->pVTbl->DecodePDU(pIEcoModBus1, EncodedPDU, EncodeDataLength, &DecodeFunctionCode, NULL, &DecodeData, &DecodeDataLength);

    if (ResultEncode != 0 || ResultDecode != 0 || EncodeFunctionCode != DecodeFunctionCode || EncodeDataLength != DecodeDataLength)
    {
        if (ResultEncode != ERR_ECO_SUCCESES)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Enoding!", EncodeFunctionCode);
        else if (ResultDecode != 0)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Decoding!", ResultDecode);
        else if (EncodeFunctionCode != DecodeFunctionCode)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect function code! [%d]", EncodeFunctionCode, DecodeFunctionCode);
        else if (EncodeDataLength != DecodeDataLength)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect DataLength [%d/%d]!", EncodeFunctionCode, EncodeDataLength, DecodeDataLength);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
    }
    for (uint32_t i = 0; i < DecodeDataLength; i++)
    {
      if (EncodeData[i] != DecodeData[i])
      {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] Encode != Decode %d!", EncodeFunctionCode, i);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
      }
    }
    return 0;
}

int TestCaseReadFIFOQueue(IEcoModBus1* pIEcoModBus1, IEcoMemoryAllocator1* pIMem)
{
    int16_t ResultEncode = -1, ResultDecode = -1;
    uint8_t EncodeFunctionCode, DecodeFunctionCode;
    uint32_t EncodePduLength, EncodeDataLength, DecodeDataLength;

    byte_t *EncodedPDU = 0, *DecodeData = 0;

    EncodeDataLength = 2;
    EncodeFunctionCode = 0x18;
    byte_t EncodeData[] = { 0x04, 0xDE };

    ResultEncode = pIEcoModBus1->pVTbl->EncodePDU(pIEcoModBus1, EncodeFunctionCode, 0, EncodeData, EncodeDataLength, &EncodedPDU, &EncodePduLength);
    ResultDecode = pIEcoModBus1->pVTbl->DecodePDU(pIEcoModBus1, EncodedPDU, EncodeDataLength, &DecodeFunctionCode, NULL, &DecodeData, &DecodeDataLength);

    if (ResultEncode != 0 || ResultDecode != 0 || EncodeFunctionCode != DecodeFunctionCode || EncodeDataLength != DecodeDataLength)
    {
        if (ResultEncode != ERR_ECO_SUCCESES)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Enoding!", EncodeFunctionCode);
        else if (ResultDecode != 0)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Decoding!", ResultDecode);
        else if (EncodeFunctionCode != DecodeFunctionCode)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect function code! [%d]", EncodeFunctionCode, DecodeFunctionCode);
        else if (EncodeDataLength != DecodeDataLength)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect DataLength [%d/%d]!", EncodeFunctionCode, EncodeDataLength, DecodeDataLength);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
    }
    for (uint32_t i = 0; i < DecodeDataLength; i++)
    {
      if (EncodeData[i] != DecodeData[i])
      {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] Encode != Decode %d!", EncodeFunctionCode, i);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
      }
    }
    return 0;
}

int TestCaseEncapsulatedInterfaceTransport(IEcoModBus1* pIEcoModBus1, IEcoMemoryAllocator1* pIMem)
{
    int16_t ResultEncode = -1, ResultDecode = -1;

    uint8_t EncodeFunctionCode, DecodeFunctionCode;
    uint32_t EncodePduLength, EncodeDataLength, DecodeDataLength;

    byte_t *EncodedPDU = 0, *DecodeData = 0;

    EncodeDataLength = 2;
    EncodeFunctionCode = 0x2B;
    byte_t EncodeData[] = { 0x04, 0xDE };

    ResultEncode = pIEcoModBus1->pVTbl->EncodePDU(pIEcoModBus1, EncodeFunctionCode, 0, EncodeData, EncodeDataLength, &EncodedPDU, &EncodePduLength);
    ResultDecode = pIEcoModBus1->pVTbl->DecodePDU(pIEcoModBus1, EncodedPDU, EncodeDataLength, &DecodeFunctionCode, NULL, &DecodeData, &DecodeDataLength);

    if (ResultEncode != 0 || ResultDecode != 0 || EncodeFunctionCode != DecodeFunctionCode || EncodeDataLength != DecodeDataLength)
    {
        if (ResultEncode != ERR_ECO_SUCCESES)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Enoding!", EncodeFunctionCode);
        else if (ResultDecode != 0)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] error while Decoding!", ResultDecode);
        else if (EncodeFunctionCode != DecodeFunctionCode)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect function code! [%d]", EncodeFunctionCode, DecodeFunctionCode);
        else if (EncodeDataLength != DecodeDataLength)
          g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] incorrect DataLength [%d/%d]!", EncodeFunctionCode, EncodeDataLength, DecodeDataLength);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
    }
    for (uint32_t i = 0; i < DecodeDataLength; i++)
    {
      if (EncodeData[i] != DecodeData[i])
      {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "[%d] Encode != Decode %d!", EncodeFunctionCode, i);
        pIMem->pVTbl->Free(pIMem, EncodedPDU);
        pIMem->pVTbl->Free(pIMem, DecodeData);
        return -1;
      }
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoModBus1* pIEcoModBus1 = 0;
    /* Указатель на интерфейс управления выводом логов */
    IEcoLog1Affiliate* pIConsoleAffiliate = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
-       result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

#ifdef ECO_LIB
    /* Регистрация статического компонента для работы с MODBUS */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoModBus1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_D3D7232DDB6940469D2B535BA10E8757);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы со строками */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoString1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_84CC0A7DBABD44EEBE749C9A8312D37E);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoList1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_53884AFC93C448ECAA929C8D3A562281);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с Логгером */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLog1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_97322B6765B74342BBCE38798A0B40B5);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif

    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoModBus1, 0, &IID_IEcoModBus1, (void**) &pIEcoModBus1);
    if (result != 0 || pIEcoModBus1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Получение интерфейса логгирования */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLog1, 0, &IID_IEcoLog1, (void**) &g_pILog);
    if (result != 0 || g_pILog == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение компонента вывода в консоль */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLog1, 0, &IID_IEcoLog1ConsoleAffiliate, (void**)&pIConsoleAffiliate);
    if (result != 0 || pIConsoleAffiliate == 0) {
        goto Release;
    }

    g_pILog->pVTbl->AddAffiliate(g_pILog, (IEcoLog1Affiliate*)pIConsoleAffiliate);
    g_pILog->pVTbl->set_LevelMask(g_pILog, LogLevel);
    g_pILog->pVTbl->DebugFormat(g_pILog, "LogLevel: %d", LogLevel);

    result = TestCaseReadCoils(pIEcoModBus1, pIMem);
    if (result != 0) {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "%d", __LINE__);
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    result = TestCaseReadDiscreteInputs(pIEcoModBus1, pIMem);
    if (result != 0) {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "%d", __LINE__);
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    result = TestCaseReadHoldingRegisters(pIEcoModBus1, pIMem);
    if (result != 0) {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "%d", __LINE__);
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    result = TestCaseReadInputRegisters(pIEcoModBus1, pIMem);
    if (result != 0) {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "%d", __LINE__);
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    result = TestCaseWriteSingleCoil(pIEcoModBus1, pIMem);
    if (result != 0) {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "%d", __LINE__);
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    result = TestCaseWriteSingleRegister(pIEcoModBus1, pIMem);
    if (result != 0) {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "%d", __LINE__);
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    result = TestCaseWriteMultipleCoils(pIEcoModBus1, pIMem);
    if (result != 0) {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "%d", __LINE__);
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    result = TestCaseWriteMultipleRegisters(pIEcoModBus1, pIMem);
    if (result != 0) {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "%d", __LINE__);
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    result = TestCaseReadFileRecord(pIEcoModBus1, pIMem);
    if (result != 0) {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "%d", __LINE__);
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    result = TestCaseMaskWriteRegister(pIEcoModBus1, pIMem);
    if (result != 0) {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "%d", __LINE__);
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    result = TestCaseReadWriteMultipleRegister(pIEcoModBus1, pIMem);
    if (result != 0) {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "%d", __LINE__);
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    result = TestCaseReadFIFOQueue(pIEcoModBus1, pIMem);
    if (result != 0) {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "%d", __LINE__);
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    /* result = TestCaseEncapsulatedInterfaceTransport(pIEcoModBus1, pIMem);*/
    if (result != 0) {
        g_pILog->pVTbl->ErrorFormat(g_pILog, "%d", __LINE__);
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    
Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoModBus1 != 0) {
        pIEcoModBus1->pVTbl->Release(pIEcoModBus1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

