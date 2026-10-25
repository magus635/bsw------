/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : CanIf_Can.h
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
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
***************************************************************************************************/
/**************************************************************************************************/
#ifndef CANIF_CBK_H_
#define CANIF_CBK_H_
/***************************************************************************************************
*                               Include
***************************************************************************************************/
#include "Can.h"
#include "CanIf_Typedefs.h"


extern uint8 BusOffErrorFlag;
extern uint8 TestStopFlag;
extern uint8 NoACKErrorFlag;
extern uint8 Can_Receive_MB_Flag;
extern Can_HwType Can_MessageBuf;
extern PduInfoType Can_Message_PduInfo;
extern uint8 Can_Tx_SentCounter;

extern FUNC(void, CANIF_CODE) CanIf_TxConfirmation
( 
    PduIdType CanTxPduId
);

extern FUNC(void, CANIF_CODE) CanIf_RxIndication
(
    P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_DATA) Mailbox,
    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
);

extern FUNC(void, CANIF_CODE) CanIf_ControllerBusOff
( 
    uint8 Controller
);

extern FUNC( void, CANIF_CODE ) CanIf_ControllerModeIndication
(
    uint8 Controller,
    Can_ControllerStateType ControllerMode
);

extern FUNC( void, CANIF_CODE ) CanIf_ControllerNoAck
(
    uint8 Controller
);

#endif
