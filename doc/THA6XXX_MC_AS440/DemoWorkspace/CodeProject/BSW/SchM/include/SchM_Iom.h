/******************************************************************************
*
******************************************************************************
* 
*   FileName              : SchM_Iom.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Iom
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

#ifndef SCHM_IOM_H
#define SCHM_IOM_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

#include "Std_Types.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

extern void SchM_Enter_Iom_Init(void);
extern void SchM_Exit_Iom_Init(void);
extern void SchM_Enter_Iom_GetGlitch(void);
extern void SchM_Exit_Iom_GetGlitch(void);
extern void SchM_Enter_Iom_SetPPUPrecaler(void);
extern void SchM_Exit_Iom_SetPPUPrecaler(void);
extern void SchM_Enter_Iom_SetFilterTime(void);
extern void SchM_Exit_Iom_SetFilterTime(void);
extern void SchM_Enter_Iom_SetEventWindow(void);
extern void SchM_Exit_Iom_SetEventWindow(void);
extern void SchM_Enter_Iom_EnableEMUCounter(void);
extern void SchM_Exit_Iom_EnableEMUCounter(void);

#endif /* SCHM_IOM_H*/

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
