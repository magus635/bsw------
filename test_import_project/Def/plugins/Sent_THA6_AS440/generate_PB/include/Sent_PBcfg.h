/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Sent_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Sent
*
*   brief                 : This file contains all configurations of Sent module
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef SENT_PBCFG_H_
#define SENT_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Sent_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
[!INDENT "0"!][!//
  [!VAR "AllVariantNumber" = "variant:size()"!][!//
  [!IF "num:i($AllVariantNumber) != num:i(0)"!][!//
      [!FOR "VariantIdx" = "num:i(1)" TO "num:i($AllVariantNumber)"!][!//
          [!VAR "VariantName" = "variant:all()[num:i($VariantIdx)]"!][!//
          /* Extern declaration of Sent configuration parameters entry for [!"$VariantName"!] */
          extern const Sent_ConfigType Sent_ConfigSet_[!"$VariantName"!];
      [!ENDFOR!][!//
  [!ELSE!][!//
      /* Extern declaration of Sent configuration parameters entry */
      extern const Sent_ConfigType Sent_ConfigSet;
  [!ENDIF!][!//
[!ENDINDENT!][!//

#endif /* SENT_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
