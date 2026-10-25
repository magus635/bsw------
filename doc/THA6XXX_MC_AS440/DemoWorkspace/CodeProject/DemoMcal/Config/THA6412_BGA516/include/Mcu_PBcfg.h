/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Mcu_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Rcc,PWRC
*
*   brief                 : This file contains all configuration declarations of Mcu Driver
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
*#Mcu_PBcfg_h_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Mcu_PBcfg_h_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*
*/

#ifndef MCU_PBCFG_H_
#define MCU_PBCFG_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Mcu_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_h_REF_2 */
#define MCU_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Mcu_PBcfg_h_REF_1*/
#include "Mcu_MemMap.h"
/* Extern declaration of Mcu Config Root */
extern const Mcu_ConfigType Mcu_ConfigSet[1U];
/* #Violation: Mcu_PBcfg_h_REF_2 */
#define MCU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Mcu_PBcfg_h_REF_1*/
#include "Mcu_MemMap.h"
#endif /* MCU_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
