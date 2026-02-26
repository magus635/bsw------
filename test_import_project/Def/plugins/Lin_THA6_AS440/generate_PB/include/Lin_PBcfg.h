/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Lin_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : ASI
*
*   brief                 : This file contains all configurations of Lin module
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef LIN_PBCFG_H_
#define LIN_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Lin_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
[!INDENT "0"!][!//
  [!VAR "AllVariantNumber" = "variant:size()"!][!//
  [!IF "num:i($AllVariantNumber) != num:i(0)"!][!//
      [!FOR "VariantIdx" = "num:i(1)" TO "num:i($AllVariantNumber)"!][!//
          [!VAR "VariantName" = "variant:all()[num:i($VariantIdx)]"!][!//
          /* Extern declaration of Lin configuration parameters entry for [!"$VariantName"!] */
          extern const Lin_ConfigType Lin_ConfigSet_[!"$VariantName"!][LIN_CONFIG_COUNT];
      [!ENDFOR!][!//
  [!ELSE!][!//
      /* Extern declaration of Lin configuration parameters entry */
      extern const Lin_ConfigType Lin_ConfigSet[LIN_CONFIG_COUNT];
  [!ENDIF!][!//
[!ENDINDENT!][!//

#endif /* LIN_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
