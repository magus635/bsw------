/******************************************************************************
*
******************************************************************************
* 
*   FileName              : SchM_Lin.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : ASI
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

#ifndef SCHM_LIN_H
#define SCHM_LIN_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

#include "Std_Types.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
extern void SchM_Enter_Lin_Status(void);
extern void SchM_Exit_Lin_Status(void);
extern void SchM_Enter_Lin_SendFrame(void);
extern void SchM_Exit_Lin_SendFrame(void);
extern void SchM_Enter_Lin_GoToSleep(void);
extern void SchM_Exit_Lin_GoToSleep(void);
extern void SchM_Enter_Lin_GoToSleepInternal(void);
extern void SchM_Exit_Lin_GoToSleepInternal(void);
extern void SchM_Enter_Lin_WakeUp(void);
extern void SchM_Exit_Lin_WakeUp(void);
extern void SchM_Enter_Lin_WakeUpInternal(void);
extern void SchM_Exit_Lin_WakeUpInternal(void);
extern void SchM_Enter_Lin_ErrorHandle(void);
extern void SchM_Exit_Lin_ErrorHandle(void);

#endif /* SCHM_LIN_H */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

