/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Port.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
*
*   brief                 : SchM file for Port Driver.
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
void SchM_Enter_Port_Init(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Port_Init(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Port_SetPinDirection(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Port_SetPinDirection(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Port_RefreshPortDirection(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Port_RefreshPortDirection(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Port_SetPinMode(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Port_SetPinMode(void)
{
    ResumeAllInterrupts();
}
#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


