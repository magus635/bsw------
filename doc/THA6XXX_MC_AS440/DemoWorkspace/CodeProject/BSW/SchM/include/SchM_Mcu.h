/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : SchM_Mcu.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Mcu
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

#ifndef SCHM_MCU_H
#define SCHM_MCU_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

extern void SchM_Enter_Mcu_Init(void);
extern void SchM_Exit_Mcu_Init(void);
extern void SchM_Enter_Mcu_InitRamSection(void);
extern void SchM_Exit_Mcu_InitRamSection(void);
extern void SchM_Enter_Mcu_InitClock(void);
extern void SchM_Exit_Mcu_InitClock(void);
extern void SchM_Enter_Mcu_DistributePllClock(void);
extern void SchM_Exit_Mcu_DistributePllClock(void);
extern void SchM_Enter_Mcu_PerformReset(void);
extern void SchM_Exit_Mcu_PerformReset(void);
extern void SchM_Enter_Mcu_SetMode(void);
extern void SchM_Exit_Mcu_SetMode(void);
extern void SchM_Enter_Mcu_ClearColdResetStatus(void);
extern void SchM_Exit_Mcu_ClearColdResetStatus(void);



#endif /* SCHM_MCU_H*/
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
