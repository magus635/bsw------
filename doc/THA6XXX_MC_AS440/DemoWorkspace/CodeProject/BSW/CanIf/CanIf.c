/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : CanIf.c
*
*   Platform             : AUTOSAR
*
*   brief                : This file contains sample code only. It is not part of the production
*                          code deliverables.
*
*   Autosar Version      : 4.4.0
*
*   SW Version           : 1.0.0
*
*    Copyright (c) 2021, Beijing TongXin Microelectroics Co., Ltd.
*
***************************************************************************************************/
/**************************************************************************************************/
#include "CanIf_Can.h"
#include "CanIf.h"
#include "Mcall.h"

#define CAN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Can_MemMap.h"
uint8 BusOffErrorFlag = 0x00;
uint8 NoACKErrorFlag = 0x00;
uint8 Can_Tx_SentCounter = 0x00;
uint8 Can_MessageDataBuffer[64] = {0};

uint8 TestStopFlag = 0x00;
uint8 Can_Receive_MB_Flag = 0u;
Can_HwType Can_MessageBuf = {0,0,0};
PduInfoType Can_Message_PduInfo = {NULL_PTR, NULL_PTR, 0};

#define CAN_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Can_MemMap.h"

FUNC(void, CANIF_CODE) CanIf_TxConfirmation
(
    PduIdType CanTxPduId
)
{
    (void)CanTxPduId;
    Can_Tx_SentCounter++;
}

FUNC( void, CANIF_CODE ) CanIf_ControllerNoAck
(
    uint8 Controller
)
{
    if(Controller == 0u)
    {
        NoACKErrorFlag |= 0x01;
    }
    else if(Controller == 1u)
    {
        NoACKErrorFlag |= 0x02;
    }
    else if(Controller == 2u)
    {
        NoACKErrorFlag |= 0x04;
    }
    else if(Controller == 3u)
    {
        NoACKErrorFlag |= 0x08;
    }
    else if(Controller == 4u)
    {
        NoACKErrorFlag |= 0x10;
    }
    else if(Controller == 5u)
    {
        NoACKErrorFlag |= 0x20;
    }
    else
    {
        /*Do Nothing*/
    }
}

FUNC(void, CANIF_CODE) CanIf_RxIndication
(
    P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_DATA) Mailbox,
    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
)
{
    uint8 i = 0u;

    if((Mailbox->CanId == 0xb4)&&(Mailbox->ControllerId == 0u))
    {
        TestStopFlag = 0x01;
    }

    if((Mailbox->Hoh == 2)||(Mailbox->Hoh == 4)||
       (Mailbox->Hoh == 5)||(Mailbox->Hoh == 6)||
       (Mailbox->Hoh == 7)||(Mailbox->Hoh == 8))
    {
        Can_MessageBuf.CanId = Mailbox->CanId & 0x1fffffff;
    }
    else
    {
        Can_MessageBuf.CanId = Mailbox->CanId;
    }

    Can_MessageBuf.Hoh = Mailbox->Hoh;
    Can_MessageBuf.ControllerId = Mailbox->ControllerId;
    Can_Message_PduInfo.SduLength = PduInfoPtr->SduLength;
    Can_Message_PduInfo.SduDataPtr = &Can_MessageDataBuffer[0];


    for(i = 0u; i < PduInfoPtr->SduLength; i++)
    {
        Can_Message_PduInfo.SduDataPtr[i] = PduInfoPtr->SduDataPtr[i];
    }

    Can_Receive_MB_Flag = 1u;
}
FUNC(void, CANIF_CODE) CanIf_ControllerBusOff
(
    uint8 Controller
)
{
    if(Controller == 0u)
    {
        BusOffErrorFlag |= 0x01;
    }
    else if(Controller == 1u)
    {
        BusOffErrorFlag |= 0x02;
    }
    else if(Controller == 2u)
    {
        BusOffErrorFlag |= 0x04;
    }
    else if(Controller == 3u)
    {
        BusOffErrorFlag |= 0x08;
    }
    else if(Controller == 4u)
    {
        BusOffErrorFlag |= 0x10;
    }
    else if(Controller == 5u)
    {
        BusOffErrorFlag |= 0x20;
    }
    else
    {
        /*Do Nothing*/
    }
}
FUNC( void, CANIF_CODE ) CanIf_ControllerModeIndication
(
    uint8 Controller,
    Can_ControllerStateType ControllerMode
)
{
    (void)Controller;
    (void)ControllerMode;
}
FUNC(Std_ReturnType, CANIF_CODE ) CanIf_TriggerTransmit
(
    PduIdType TxPduId,
    P2VAR(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
)
{
    (void)TxPduId;
    (void)PduInfoPtr;
    return E_OK;
}
