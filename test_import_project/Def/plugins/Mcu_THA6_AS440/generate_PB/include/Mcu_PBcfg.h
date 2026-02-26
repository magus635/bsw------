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
[!AUTOSPACING!] 
/* #Violation: Mcu_PBcfg_h_REF_2 */
#define MCU_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Mcu_PBcfg_h_REF_1*/
#include "Mcu_MemMap.h"
[!VAR "EcucModuleExist" = "num:i(0)"!][!//
[!SELECT "as:modconf('EcuC')[1]"!][!//
  [!IF "node:exists(EcucPostBuildVariants/EcucPostBuildVariantRef/*[1])"!][!//
    [!VAR "EcucModuleExist" = "num:i(1)"!][!//
    [!LOOP "EcucPostBuildVariants/EcucPostBuildVariantRef/*"!][!//
      [!VAR "Variantname"="''"!][!//
      [!VAR "Variantname" = "text:split(.,'/')[4]"!]
      [!WS"0"!]/* Extern declaration of Mcu Config Root for [!"$Variantname"!] */
      [!WS"0"!]extern const Mcu_ConfigType Mcu_ConfigSet_[!"$Variantname"!][1U];
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//
[!IF "$EcucModuleExist = num:i(0)"!][!//
  [!WS"0"!]/* Extern declaration of Mcu Config Root */
  [!WS"0"!]extern const Mcu_ConfigType Mcu_ConfigSet[1U];
[!ENDIF!][!//
/* #Violation: Mcu_PBcfg_h_REF_2 */
#define MCU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Mcu_PBcfg_h_REF_1*/
#include "Mcu_MemMap.h"
#endif /* MCU_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
