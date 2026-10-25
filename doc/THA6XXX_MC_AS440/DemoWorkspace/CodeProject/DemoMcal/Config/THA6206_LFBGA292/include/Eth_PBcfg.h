/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Eth_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Ethernet
*
*   brief                 : This file contains all configuration declarations of Ethernet Driver
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
*#Eth_PBcfg_h_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Eth_PBcfg_h_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*
*/

#ifndef ETH_PBCFG_H_
#define ETH_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Eth_Types.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
/* #Violation: Eth_PBcfg_h_REF_2 */
#define ETH_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Eth_PBcfg_h_REF_1*/
#include "Eth_MemMap.h" 
/* Extern declaration of Eth Config Root */
extern const Eth_ConfigType Eth_ConfigSet[1U];
/* #Violation: Eth_PBcfg_h_REF_2 */
#define ETH_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Eth_PBcfg_h_REF_1*/
#include "Eth_MemMap.h"
#endif /* ETH_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
