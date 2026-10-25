/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Spi.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : ESPI
*
*   brief                 : SchM file for Spi Driver.
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
void SchM_Enter_Spi_WriteIB(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Spi_WriteIB(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Spi_ReadIB(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Spi_ReadIB(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Spi_SetupEB(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Spi_SetupEB(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Spi_SyncTransmit(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Spi_SyncTransmit(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Spi_AsyncTransmit(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Spi_AsyncTransmit(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Spi_SetAsyncMode(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Spi_SetAsyncMode(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Spi_IsrError(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Spi_IsrError(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Spi_DeInit(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Spi_DeInit(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_Spi_GetStatus(void)
{
    SuspendAllInterrupts();
}
void SchM_Exit_Spi_GetStatus(void)
{
    ResumeAllInterrupts();
}
#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

