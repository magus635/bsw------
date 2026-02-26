/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Can.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : MCAN
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
/**************************************************************************************************/
#ifndef CAN_CALLOUT_H
#define CAN_CALLOUT_H
/***************************************************************************************************
*                               Include
***************************************************************************************************/
#include "Can.h"
/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/

/***************************************************************************************************
*                               Type Definitions
***************************************************************************************************/

/***************************************************************************************************
*                               Extern Data Declaration
***************************************************************************************************/

/***************************************************************************************************
*                               Extern Function Declaration
***************************************************************************************************/
#if (CAN_LPDU_CALLOUT_FUNCTION_SUPPORT == STD_ON)
extern FUNC(void, CAN_APPL_CODE) Can_Callout_Data_Init
(
    void
);
[!IF "node:exists(CanGeneral/CanLPduReceiveCalloutFunction) and (normalize-space(CanGeneral/CanLPduReceiveCalloutFunction) != 'NULL_PTR')"!][!//
/*SWS_Can_00443*/
extern FUNC(boolean, CAN_APPL_CODE) [!"normalize-space(CanGeneral/CanLPduReceiveCalloutFunction)"!]       /*<LPDU_CalloutName>*/
(
    uint8 Hrh,
    Can_IdType CanId,
    uint8 CanDlc,
    P2CONST(uint8, AUTOMATIC, CAN_APPL_CONST) CanSduPtr
);
[!ENDIF!][!//
#endif /* (CAN_LPDU_CALLOUT_FUNCTION_SUPPORT  \== STD_ON) */

[!IF "node:exists(CanGeneral/CanLPduTransmitCalloutFunction) and (normalize-space(CanGeneral/CanLPduTransmitCalloutFunction) != 'NULL_PTR')"!][!//
/****************************************************************************************************
*   Function Name           : [!"normalize-space(CanGeneral/CanLPduTransmitCalloutFunction)"!]
*
*   Service ID              : None.
*
*   Description             : Can transmit callback function.
*                     
*   Parameters in           : ControllerId: Logical ID of the Controller.
*
*                             PduInfoPtr: pointer to SDU user memory, DLC and Identifier.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, CAN_APPL_CODE) [!"normalize-space(CanGeneral/CanLPduTransmitCalloutFunction)"!]
(
    Can_IdType ControllerId,
    P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_CONST) PduInfoPtr
);
[!ENDIF!][!//

#endif
