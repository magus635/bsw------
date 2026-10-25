/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Ocu.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-ATOM
*
*   brief                 : SchM file for Ocu Driver.
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
**                          Global Variable Definitions                                            **
****************************************************************************************************/

void SchM_Enter_Ocu_StartChannel(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Ocu_StartChannel(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Ocu_SetAbsoluteThreshold(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Ocu_SetAbsoluteThreshold(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Ocu_SetRelativeThreshold(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Ocu_SetRelativeThreshold(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Ocu_StopChannel(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Ocu_StopChannel(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Ocu_SetPinAction(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Ocu_SetPinAction(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Ocu_EnableNotification(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Ocu_EnableNotification(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Ocu_DisableNotification(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Ocu_DisableNotification(void)
{
    ResumeAllInterrupts();
}

#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
