/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Iom_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : IOM
*
*   brief                 : IOM configuration generated out of ECU configuration file
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Codeing Rule Violations                                                **
****************************************************************************************************/
/*
*#Violation Summary
*#Iom_PBcfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef IOM_PBCFG_H_
#define IOM_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Iom_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
/* #Violation: Iom_PBcfg_h_REF_1 */
#define IOM_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Iom_MemMap.h"

/* Extern declaration of Iom Config Root */
extern const Iom_ConfigType Iom_ConfigSet[1U];

/* #Violation: Iom_PBcfg_h_REF_1 */
#define IOM_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Iom_MemMap.h"

#endif /* IOM_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
