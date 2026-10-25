/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Wdg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : CPUWDT
*
*   brief                 : SchM file for Wdg Driver.
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

/****************************************************************************************************
 
****************************************************************************************************/
/*
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
void SchM_Enter_Wdg_Init(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Wdg_Init(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Wdg_SetMode(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Wdg_SetMode(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Wdg_SetTriggerCondition(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Wdg_SetTriggerCondition(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Wdg_ISRHandler(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Wdg_ISRHandler(void)
{
    ResumeAllInterrupts();
}

#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
