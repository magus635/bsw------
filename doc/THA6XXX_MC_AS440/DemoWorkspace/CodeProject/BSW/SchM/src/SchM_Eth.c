/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Eth.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Geth
*
*   brief                 : SchM file for Eth Driver.
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
#include "SchM_Eth.h"

/****************************************************************************************************
**                          Global function Definitions                                            **
****************************************************************************************************/
/*==================================================================================================
                                       ETH
==================================================================================================*/

/*==================================================================================================
                                       ETH
==================================================================================================*/

void SchM_Enter_Eth_SetControllerMode(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Eth_SetControllerMode(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Eth_GetEgressTimeStamp(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Eth_GetEgressTimeStamp(void)
{
    ResumeAllInterrupts();
}
void SchM_Enter_Eth_GetIngressTimeStamp(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Eth_GetIngressTimeStamp(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Eth_ProvideTxBuffer(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Eth_ProvideTxBuffer(void)
{
    ResumeAllInterrupts();
}

#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

