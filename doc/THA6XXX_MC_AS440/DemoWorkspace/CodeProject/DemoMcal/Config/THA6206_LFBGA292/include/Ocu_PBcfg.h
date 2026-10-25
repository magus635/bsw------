/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Ocu_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-ATOM
*
*   brief                 : This file contains all configurations of OCU module
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
/*
*#Violation Summary
*#Ocu_PBcfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef OCU_PBCFG_H_
#define OCU_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Ocu_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
/* #Violation: Ocu_PBcfg_h_REF_1 */
#define OCU_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Ocu_MemMap.h"

/* Extern declaration of Ocu Config Root */
extern const Ocu_ConfigType Ocu_ConfigSet[1U];

/* #Violation: Ocu_PBcfg_h_REF_1 */
#define OCU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Ocu_MemMap.h"

#endif /* OCU_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
