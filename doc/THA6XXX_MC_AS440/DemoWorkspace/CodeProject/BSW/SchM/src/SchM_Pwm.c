/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Pwm.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, GTM-ATOM
*
*   brief                 : SchM file for Pwm Driver.
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

void SchM_Enter_Pwm_Init(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Pwm_Init(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Pwm_DeInit(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Pwm_DeInit(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Pwm_SetDutyCycle(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Pwm_SetDutyCycle(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Pwm_SetPeriodAndDuty(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Pwm_SetPeriodAndDuty(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Pwm_SetOutputToIdle(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Pwm_SetOutputToIdle(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Pwm_DisableNotification(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Pwm_DisableNotification(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Pwm_EnableNotification(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Pwm_EnableNotification(void)
{
    ResumeAllInterrupts();
}

#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
