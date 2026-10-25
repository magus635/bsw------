/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Dma.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Dma
*
*   brief                 : SchM file for Dma Driver.
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


/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

void SchM_Enter_Dma_GetChannelStatus(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Dma_GetChannelStatus(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Dma_ChannelStart(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Dma_ChannelStart(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Dma_ChannelCancel(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Dma_ChannelCancel(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Dma_ChannelSuspend(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Dma_ChannelSuspend(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Dma_ChannelResume(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Dma_ChannelResume(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Dma_ChannelUpdate(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Dma_ChannelUpdate(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Dma_ChannelShadowingUpdate(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Dma_ChannelShadowingUpdate(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Dma_DeInit(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Dma_DeInit(void)
{
    ResumeAllInterrupts();
}


#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

