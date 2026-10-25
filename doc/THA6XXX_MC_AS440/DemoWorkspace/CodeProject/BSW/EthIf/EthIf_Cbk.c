/****************************************************************************************************
 *   FileName              : EthIf_Cbk.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Geth
 *
 *   brief                 : This file contain EthIf callback function
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ****************************************************************************************************/
#include "EthIf.h"
#include "Eth_Demo.h"
#include "Demo_Common.h"

#define ETH_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Eth_MemMap.h"
volatile uint16 Test_EthTxConfirmCount[ETH_MAX_CTRLS];
volatile uint16 Test_EthTxTimeConfirmCount[ETH_MAX_CTRLS];
volatile uint16 Test_EthRxConfirmCount[ETH_MAX_CTRLS];
volatile uint16 Test_EthRxTimeConfirmCount[ETH_MAX_CTRLS];

#define ETH_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Eth_MemMap.h"
static int timestampTestTime = 20;

#define ETH_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Eth_MemMap.h"

void EthIf_RxIndication
(
    uint8               CtrlIdx,
    Eth_FrameType       FrameType,
    boolean             IsBroadcast,
    const uint8        *PhysAddrPtr,
    const Eth_DataType *DataPtr,
    uint16              LenByte
)
{
    uint16 i;
    uint32 lSrcipadd = 0U;
    uint8  Eth_DestSrcAddrMismatch = 0U;

    MCAL_UNUSED_VAR(LenByte);

    if (FrameType == 0x0806U)
    {
        for (i = 0U; i < 4U; i++)
        {
            lSrcipadd <<= 8U;
            lSrcipadd |= (*(DataPtr + 14 + i));
        }
        if (lSrcipadd == Src_IPaddress)
        {
            ArpReply = 1;
            DEBUG_PRINTF(
                "\n Given IP address is at Mac Address - %x :%x :%x :%x :%x :%x ",
                (*(PhysAddrPtr + 0)),
                (*(PhysAddrPtr + 1)),
                (*(PhysAddrPtr + 2)),
                (*(PhysAddrPtr + 3)),
                (*(PhysAddrPtr + 4)),
                (*(PhysAddrPtr + 5)));
        }
    }
    else
    {
        for (i = 0; i < ETH_MAC_ADD_LEN; i++)
        {
            if (Ret_MacAddr[i] != *(DataPtr - ETH_FRAMEHEADER_LEN + i))
            {
                Eth_DestSrcAddrMismatch++;
            }
        }

        if ((0U != Eth_DestSrcAddrMismatch) && (FALSE == IsBroadcast))
        {
            PromiscuousCheck = 1;
        }
        if (1U == StabilityTest)
        {
            if ((uint8)(*(DataPtr + 28)) == 0xefU)
            {
                ArpReply++;
                TransmitArpFrame();
            }
        }

        /* DEBUG_PRINTF("\n\n Received Protocol is: 0x%x ", (FrameType));*/ 
        /* DEBUG_PRINTF("\n Received Payload Size is: %d \n ", (LenByte - ETH_CRC_FIELD_LENGTH)); */
    }
    Test_EthRxConfirmCount[CtrlIdx]++;
#if (ETH_GLOBAL_TIME_SUPPORT_API == STD_ON)
    if (timestampTestTime > 0)
    {
        timestampTestTime--;
        Eth_TimeStampQualType timeQual;
        Eth_TimeStampType     timeStamp;

        Eth_GetIngressTimeStamp(CtrlIdx, DataPtr, &timeQual, &timeStamp);
        if (ETH_VALID == timeQual)
        {
            Test_EthRxTimeConfirmCount[CtrlIdx]++;

        }
    }
#endif    /*#if (ETH_GLOBAL_TIME_SUPPORT_API \== STD_ON)*/ 
}

void EthIf_TxConfirmation
(
    uint8 CtrlIdx,
    Eth_BufIdxType BufIdx,
    Std_ReturnType Result
)
{

    MCAL_UNUSED_VAR(Result);
    Test_EthTxConfirmCount[CtrlIdx]++;

#if (ETH_GLOBAL_TIME_SUPPORT_API == STD_ON)
    if (timestampTestTime > 0)
    {
        timestampTestTime--;
        Eth_TimeStampQualType timeQual;
        Eth_TimeStampType     timeStamp;
        Eth_GetEgressTimeStamp(CtrlIdx, BufIdx, &timeQual, &timeStamp);
        if (ETH_VALID == timeQual)
        {
            Test_EthTxTimeConfirmCount[CtrlIdx]++;
            DEBUG_PRINTF(
                "Eth_GetEgressTimeStamp :secondsHi =%d, %d:%d \n;",
                timeStamp.secondsHi,
                timeStamp.seconds,
                timeStamp.nanoseconds);

        }
    }

#endif    /* #if (ETH_GLOBAL_TIME_SUPPORT_API \== STD_ON)*/ 
}

void EthIf_CtrlModeIndication(uint8 CtrlIdx, Eth_ModeType CtrlMode)
{
    (void)CtrlIdx;
    (void)CtrlMode;
}
