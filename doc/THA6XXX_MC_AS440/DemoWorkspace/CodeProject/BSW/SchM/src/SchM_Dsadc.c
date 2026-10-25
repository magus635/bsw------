/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Dsadc.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DSADC
*
*   brief                 : SchM file for Dsadc Driver.
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

void SchM_Enter_Dsadc_StartConversion(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Dsadc_StartConversion(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Dsadc_StopConversion(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Dsadc_StopConversion(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Dsadc_GetStreamLastPointer(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Dsadc_GetStreamLastPointer(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Dsadc_GetChannelStatus(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Dsadc_GetChannelStatus(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Dsadc_ResultHandling(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Dsadc_ResultHandling(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Dsadc_DeInit(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Dsadc_DeInit(void)
{
    ResumeAllInterrupts();
}


#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

