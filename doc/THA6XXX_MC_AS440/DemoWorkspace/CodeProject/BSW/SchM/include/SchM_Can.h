/****************************************************************************************************
*   FileName              : SchM_Can.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MCAN
*
*   brief                 : SchM file for Can Driver.
*                           This file contains sample code only. It is not part of the
*                           production code deliverables.
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
#ifndef SCHM_CAN_H
#define SCHM_CAN_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
extern void SchM_Enter_Can_EnableControllerInterrupts(void);

extern void SchM_Exit_Can_EnableControllerInterrupts(void);

extern void SchM_Enter_Can_DisableControllerInterrupts(void);

extern void SchM_Exit_Can_DisableControllerInterrupts(void);

extern void SchM_Enter_Can_TxProcessing(void);

extern void SchM_Exit_Can_TxProcessing(void);

extern void SchM_Enter_Can_WriteMsgObj(void);

extern void SchM_Exit_Can_WriteMsgObj(void);

extern void SchM_Enter_Can_ModeTransition(void);

extern void SchM_Exit_Can_ModeTransition(void);

extern void SchM_Enter_Can_Init(void);

extern void SchM_Exit_Can_Init(void);

#endif /* SCHM_CAN_H*/

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


