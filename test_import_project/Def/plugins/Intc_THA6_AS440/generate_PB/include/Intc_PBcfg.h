/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Intc_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral           : Intc
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef INTC_PBCFG_H_
#define INTC_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Intc_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
[!AUTOSPACING!] 
[!VAR "EcucModuleExist" = "num:i(0)"!][!//
[!SELECT "as:modconf('EcuC')[1]"!][!//
  [!IF "node:exists(EcucPostBuildVariants/EcucPostBuildVariantRef/*[1])"!][!//
    [!VAR "EcucModuleExist" = "num:i(1)"!][!//
    [!LOOP "EcucPostBuildVariants/EcucPostBuildVariantRef/*"!][!//
      [!VAR "Variantname"="''"!][!//
      [!VAR "Variantname" = "text:split(.,'/')[4]"!]
      [!WS"0"!]/* Extern declaration of Intc Config Root for [!"$Variantname"!] */
      [!WS"0"!]extern const Intc_ConfigType Intc_ConfigSet_[!"$Variantname"!][];
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//
[!IF "$EcucModuleExist = num:i(0)"!][!//
  [!WS"0"!]/* Extern declaration of Intc Config Root */
  [!WS"0"!]extern const Intc_ConfigType Intc_ConfigSet[INTC_CONFIGSET_CNT];
[!ENDIF!][!//

#endif /* INTC_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
