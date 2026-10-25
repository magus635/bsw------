/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Lin.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : ASI
*
*   brief                 : SchM file for Lin Driver.
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
void SchM_Enter_Lin_Status(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Lin_Status(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Lin_SendFrame(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Lin_SendFrame(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Lin_GoToSleep(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Lin_GoToSleep(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Lin_GoToSleepInternal(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Lin_GoToSleepInternal(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Lin_WakeUp(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Lin_WakeUp(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Lin_WakeUpInternal(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Lin_WakeUpInternal(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Lin_ErrorHandle(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Lin_ErrorHandle(void)
{
    ResumeAllInterrupts();
}

#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

