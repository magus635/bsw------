/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_I2c.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : I2C
*
*   brief                 : SchM file for I2c Driver.
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
void SchM_Enter_I2c_SyncTransmit(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_I2c_SyncTransmit(void)
{
    ResumeAllInterrupts();
}

void SchM_Enter_I2c_DeInit(void)
{
    SuspendAllInterrupts();
}

void SchM_Exit_I2c_DeInit(void)
{
    ResumeAllInterrupts();
}

#ifdef __cplusplus
}
#endif

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

