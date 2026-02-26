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

[!AUTOSPACING!] 
[!VAR "EcucModuleExist" = "num:i(0)"!][!//
[!SELECT "as:modconf('EcuC')[1]"!][!//
  [!IF "node:exists(EcucPostBuildVariants/EcucPostBuildVariantRef/*[1])"!][!//
    [!VAR "EcucModuleExist" = "num:i(1)"!][!//
    [!LOOP "EcucPostBuildVariants/EcucPostBuildVariantRef/*"!][!//
      [!VAR "Variantname"="''"!][!//
      [!VAR "Variantname" = "text:split(.,'/')[4]"!]
      [!WS"0"!]/* Extern declaration of Ocu Config Root for [!"$Variantname"!] */
      [!WS"0"!]extern const Ocu_ConfigType Ocu_ConfigSet_[!"$Variantname"!][1U];
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//
[!IF "$EcucModuleExist = num:i(0)"!][!//
  [!WS"0"!]/* Extern declaration of Ocu Config Root */
  [!WS"0"!]extern const Ocu_ConfigType Ocu_ConfigSet[1U];
[!ENDIF!][!//

/* #Violation: Ocu_PBcfg_h_REF_1 */
#define OCU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Ocu_MemMap.h"

#endif /* OCU_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
