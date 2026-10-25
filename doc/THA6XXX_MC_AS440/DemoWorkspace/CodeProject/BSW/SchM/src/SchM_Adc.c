/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Adc.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Saradc
*
*   brief                 : SchM file for Adc Driver.
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
void SchM_Enter_Adc_StartGroup(void)
{
  SuspendAllInterrupts();
}

void SchM_Enter_Adc_StopGroup(void)
{
  SuspendAllInterrupts();
}

void SchM_Enter_Adc_ReadGroup(void)
{
  SuspendAllInterrupts();
}

void SchM_Enter_Adc_EnableHwTrig(void)
{
  SuspendAllInterrupts();
}

void SchM_Enter_Adc_DisableHwTrig(void)
{
  SuspendAllInterrupts();
}

void SchM_Enter_Adc_GetGrpStatus(void)
{
  SuspendAllInterrupts();
}

void SchM_Enter_Adc_GetStreamLastPtr(void)
{
  SuspendAllInterrupts();
}

void SchM_Enter_Adc_ScheduleStart(void)
{
  SuspendAllInterrupts();
}

void SchM_Enter_Adc_ScheduleStop(void)
{
  SuspendAllInterrupts();
}

void SchM_Enter_Adc_ScheduleNext(void)
{
  SuspendAllInterrupts();
}

void SchM_Enter_Adc_PushQueue(void)
{
  SuspendAllInterrupts();
}

void SchM_Enter_Adc_PopQueue(void)
{
  SuspendAllInterrupts();
}

void SchM_Exit_Adc_StartGroup(void)
{
  ResumeAllInterrupts();
}

void SchM_Exit_Adc_StopGroup(void)
{
  ResumeAllInterrupts();
}

void SchM_Exit_Adc_ReadGroup(void)
{
  ResumeAllInterrupts();
}

void SchM_Exit_Adc_EnableHwTrig(void)
{
  ResumeAllInterrupts();
}

void SchM_Exit_Adc_DisableHwTrig(void)
{
  ResumeAllInterrupts();
}

void SchM_Exit_Adc_GetGrpStatus(void)
{
  ResumeAllInterrupts();
}

void SchM_Exit_Adc_GetStreamLastPtr(void)
{
  ResumeAllInterrupts();
}

void SchM_Exit_Adc_ScheduleStart(void)
{
  ResumeAllInterrupts();
}

void SchM_Exit_Adc_ScheduleStop(void)
{
  ResumeAllInterrupts();
}

void SchM_Exit_Adc_ScheduleNext(void)
{
  ResumeAllInterrupts();
}

void SchM_Exit_Adc_PushQueue(void)
{
  ResumeAllInterrupts();
}

void SchM_Exit_Adc_PopQueue(void)
{
  ResumeAllInterrupts();
}

void SchM_Enter_Adc_DisableGroupNotification(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Adc_DisableGroupNotification(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Adc_EnableGroupNotification(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Adc_EnableGroupNotification(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Adc_Endinit(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Adc_Endinit(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Adc_ResultHandling(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Adc_ResultHandling(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Adc_DeInit(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Adc_DeInit(void)
{
    ResumeAllInterrupts();
}

#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

