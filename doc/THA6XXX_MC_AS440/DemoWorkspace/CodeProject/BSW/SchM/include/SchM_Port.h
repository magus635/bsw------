/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Port.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
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
****************************************************************************************************/

#ifndef SCHM_PORT_H_
#define SCHM_PORT_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

#include "Std_Types.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

extern void SchM_Enter_Port_Init(void);

extern void SchM_Exit_Port_Init(void);

extern void SchM_Enter_Port_SetPinDirection(void);

extern void SchM_Exit_Port_SetPinDirection(void);

extern void SchM_Enter_Port_RefreshPortDirection(void);

extern void SchM_Exit_Port_RefreshPortDirection(void);

extern void SchM_Enter_Port_SetPinMode(void);

extern void SchM_Exit_Port_SetPinMode(void);

#endif /* SCHM_PORT_H_ */
