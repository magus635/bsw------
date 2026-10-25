/******************************************************************************
*
******************************************************************************
* 
*   FileName              : SchM_I2c.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : I2C
*
*   brief                 : This file contains sample code only. It is not part of the production
*                           code deliverables.
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*          
******************************************************************************/

#ifndef SCHM_I2C_H
#define SCHM_I2C_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

#include "Std_Types.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

extern void SchM_Enter_I2c_SyncTransmit(void);
extern void SchM_Exit_I2c_SyncTransmit(void);
extern void SchM_Enter_I2c_DeInit(void);
extern void SchM_Exit_I2c_DeInit(void);
#endif /* _SCHM_I2C_H */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

