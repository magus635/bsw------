/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Uart.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : ASI
*
*   brief                 : SchM file for Uart Driver.
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

/****************************************************************************************************
 
****************************************************************************************************/
/*
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
void SchM_Enter_Uart_Init(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Uart_Init(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Uart_GetStatus(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Uart_GetStatus(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Uart_Write(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Uart_Write(void)
{
    ResumeAllInterrupts();
}
void SchM_Enter_Uart_Read(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Uart_Read(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Uart_DeInit(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_Uart_DeInit(void)
{
    ResumeAllInterrupts();
}

#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

