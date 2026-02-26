/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fls_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains all configurations of FLS module
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef FLS_PBCFG_H_
#define FLS_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Fls_GeneralTypes.h"

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
      [!WS"0"!]/* Extern declaration of Fls Config Root for [!"$Variantname"!] */
      [!WS"0"!]extern const Fls_ConfigType Fls_ConfigSet_[!"$Variantname"!][];
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDSELECT!][!//
[!IF "$EcucModuleExist = num:i(0)"!][!//
  [!WS"0"!]/* Extern declaration of Fls Config Root */
  [!WS"0"!]extern const Fls_ConfigType Fls_ConfigSet[FLS_CONFIG_COUNT];
[!ENDIF!][!//

#endif /* FLS_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
