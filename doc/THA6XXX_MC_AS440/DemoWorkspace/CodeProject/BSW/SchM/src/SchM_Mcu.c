/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Mcu.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : None
*
*   brief                 : SchM file for Mcu Driver.
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
#include "SchM_Mcu.h"

/****************************************************************************************************
**                          Global function Definitions                                            **
****************************************************************************************************/

/*==================================================================================================
                                       MCU
==================================================================================================*/
/*==================================================================================================
                                       MCU
==================================================================================================*/
void SchM_Enter_Mcu_Init(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Mcu_Init(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Mcu_InitRamSection(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Mcu_InitRamSection(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Mcu_InitClock(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Mcu_InitClock(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Mcu_DistributePllClock(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Mcu_DistributePllClock(void)
{
    ResumeAllInterrupts();
}
void SchM_Enter_Mcu_PerformReset(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Mcu_PerformReset(void)
{
    ResumeAllInterrupts();
}
void SchM_Enter_Mcu_SetMode(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Mcu_SetMode(void)
{
    ResumeAllInterrupts();
}
void SchM_Enter_Mcu_ClearColdResetStatus(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Mcu_ClearColdResetStatus(void)
{
    ResumeAllInterrupts();
}
#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

