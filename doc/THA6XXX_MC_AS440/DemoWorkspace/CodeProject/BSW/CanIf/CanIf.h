/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : CanIf_Cbk.h
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
#ifndef CANIF_H_
#define CANIF_H_
/***************************************************************************************************
*                               Include
***************************************************************************************************/
#include "Can.h"
#include "CanIf_Typedefs.h"

extern FUNC(Std_ReturnType, CANIF_CODE ) CanIf_TriggerTransmit
(
    PduIdType TxPduId,
    P2VAR(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr
);

#endif
