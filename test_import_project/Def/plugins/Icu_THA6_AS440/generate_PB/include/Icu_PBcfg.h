/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Icu_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TIM
*
*   brief                 : This file contains all configurations of ICU module
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
*#Icu_PBcfg_h_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Icu_PBcfg_h_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*
*/
#ifndef ICU_PBCFG_H_
#define ICU_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Icu_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
/* #Violation: Icu_PBcfg_h_REF_2 */
#define ICU_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Icu_PBcfg_h_REF_1*/
#include "Icu_MemMap.h"

[!NOCODE!]
  [!/* Variation Point */!]
  [!IF "node:exists(as:modconf('EcuC')[1]/EcucPostBuildVariants/EcucSelectedPostBuildVariantRef)"!]
    [!LOOP "as:modconf('EcuC')[1]/EcucPostBuildVariants/EcucPostBuildVariantRef/*"!]
      [!VAR "index" = "num:i(count(text:split((.), '/')))"!]
      [!VAR "Variantname" = "text:split((.), '/')[num:i($index)]"!]
      [!CODE!][!//
        [!AUTOSPACING!]
        [!INDENT "0"!]
          /* Extern declaration of Icu Icu_ConfigSet for [!"$Variantname"!] */
          extern const Icu_ConfigType Icu_ConfigSet_[!"$Variantname"!][1U];
        [!CR!]
        [!ENDINDENT!]
      [!ENDCODE!][!//
    [!ENDLOOP!]
  [!ELSE!]
    [!CODE!][!//
      [!AUTOSPACING!]
      [!INDENT "0"!]
        /* Extern declaration of Icu Icu_ConfigSet */
        extern const Icu_ConfigType Icu_ConfigSet[1U];
      [!CR!]
      [!ENDINDENT!]
    [!ENDCODE!][!//
  [!ENDIF!]
[!ENDNOCODE!][!//

/* #Violation: Icu_PBcfg_h_REF_2 */
#define ICU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Icu_PBcfg_h_REF_1*/
#include "Icu_MemMap.h"

#endif  /* ICU_PBCFG_H */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
