/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Intc.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Intc/Gic
*
*   brief                 : SchM file for Intc/Gic Driver.
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

void SchM_Enter_Intc_EnableInterrupt(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Intc_EnableInterrupt(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Intc_GenSwInterrupt(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Intc_GenSwInterrupt(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Intc_DisableInterrupt(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Intc_DisableInterrupt(void)
{
    ResumeAllInterrupts();
}


#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

