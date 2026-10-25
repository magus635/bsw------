/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Can.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Can
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

#ifdef __cplusplus
extern "C"{
#endif

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Compiler.h"
#include "Std_Types.h"
#include "Mcall.h"

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

void SchM_Enter_Can_EnableControllerInterrupts(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Can_EnableControllerInterrupts(void)
{
    ResumeAllInterrupts();
}
void SchM_Enter_Can_DisableControllerInterrupts(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Can_DisableControllerInterrupts(void)
{
    ResumeAllInterrupts();
}
void SchM_Enter_Can_TxProcessing(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Can_TxProcessing(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Can_WriteMsgObj(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Can_WriteMsgObj(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Can_ModeTransition(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Can_ModeTransition(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Can_Init(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Can_Init(void)
{
    ResumeAllInterrupts();
}

#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

