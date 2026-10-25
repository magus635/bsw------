/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Wdg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : CPUWDT
*
*   brief                 : SchM file for Wdg Driver.
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

#ifndef SCHM_WDG_H_
#define SCHM_WDG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

#include "Std_Types.h"

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
extern void SchM_Enter_Wdg_Init(void);
extern void SchM_Exit_Wdg_Init(void);
extern void SchM_Enter_Wdg_SetMode(void);
extern void SchM_Exit_Wdg_SetMode(void);
extern void SchM_Enter_Wdg_SetTriggerCondition(void);
extern void SchM_Exit_Wdg_SetTriggerCondition(void);
extern void SchM_Enter_Wdg_ISRHandler(void);
extern void SchM_Exit_Wdg_ISRHandler(void);

#endif /* SCHM_WDG_H_ */
