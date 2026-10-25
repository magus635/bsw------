/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Msc.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Msc
*
*   brief                 : SchM file for Msc Driver.
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

void SchM_Enter_Msc_TxCmdFrame(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Msc_TxCmdFrame(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Msc_TxDataFrame(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Msc_TxDataFrame(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Msc_GetRxData(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Msc_GetRxData(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Msc_DeInit(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Msc_DeInit(void)
{
    ResumeAllInterrupts();
}

#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
