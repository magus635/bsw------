/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Iom.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : IOM
*
*   brief                 : SchM file for Iom Driver.
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
void SchM_Enter_Iom_Init(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Iom_Init(void)
{
    ResumeAllInterrupts();
}
void SchM_Enter_Iom_GetGlitch(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Iom_GetGlitch(void)
{
    ResumeAllInterrupts();
}
void SchM_Enter_Iom_SetPPUPrecaler(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Iom_SetPPUPrecaler(void)
{
    ResumeAllInterrupts();
}
void SchM_Enter_Iom_SetFilterTime(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Iom_SetFilterTime(void)
{
    ResumeAllInterrupts();
}
void SchM_Enter_Iom_SetEventWindow(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Iom_SetEventWindow(void)
{
    ResumeAllInterrupts();
}
void SchM_Enter_Iom_EnableEMUCounter(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Iom_EnableEMUCounter(void)
{
    ResumeAllInterrupts();
}

#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
