/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Icu.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Tim
*
*   brief                 : SchM file for Icu Driver.
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
**                          Global function Definitions                                            **
****************************************************************************************************/
/*==================================================================================================
                                       ICU
==================================================================================================*/
void SchM_Enter_Icu_GetInputState(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_GetInputState(void)
{
    ResumeAllInterrupts();
}


void SchM_Enter_Icu_StartTimestamp(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_StartTimestamp(void)
{
    ResumeAllInterrupts();
}


void SchM_Enter_Icu_StopTimestamp(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_StopTimestamp(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Icu_GetTimestampIndex(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_GetTimestampIndex(void)
{
    ResumeAllInterrupts();
}
void SchM_Enter_Icu_ResetEdgeCount(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_ResetEdgeCount(void)
{
    ResumeAllInterrupts();
}


void SchM_Enter_Icu_EnableEdgeCount(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_EnableEdgeCount(void)
{
    ResumeAllInterrupts();
}


void SchM_Enter_Icu_DisableEdgeCount(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_DisableEdgeCount(void)
{
    ResumeAllInterrupts();
}


void SchM_Enter_Icu_EnableEdgeDetection(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_EnableEdgeDetection(void)
{
    ResumeAllInterrupts();
}


void SchM_Enter_Icu_EnableMultiEdgeDetection(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_EnableMultiEdgeDetection(void)
{
    ResumeAllInterrupts();
}


void SchM_Enter_Icu_DisableEdgeDetection(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_DisableEdgeDetection(void)
{
    ResumeAllInterrupts();
}


void SchM_Enter_Icu_StartSignalMeasurement(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_StartSignalMeasurement(void)
{
    ResumeAllInterrupts();
}


void SchM_Enter_Icu_StopSignalMeasurement(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_StopSignalMeasurement(void)
{
    ResumeAllInterrupts();
}


void SchM_Enter_Icu_GetTimeElapsed(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_GetTimeElapsed(void)
{
    ResumeAllInterrupts();
}


void SchM_Enter_Icu_GetDutyCycleValues(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_GetDutyCycleValues(void)
{
    ResumeAllInterrupts();
}


void SchM_Enter_Icu_Tim_ISRHandler(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Icu_Tim_ISRHandler(void)
{
    ResumeAllInterrupts();
}


#ifdef __cplusplus
}
#endif
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

