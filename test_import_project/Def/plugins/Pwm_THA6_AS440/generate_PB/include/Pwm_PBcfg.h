/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Pwm_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, GTM ATOM
*
*   brief                 : This file contains all configurations of PWM module
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
*#Pwm_PBcfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef PWM_PBCFG_H_
#define PWM_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Pwm_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
/* #Violation: Pwm_PBcfg_h_REF_1 */
#define PWM_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Pwm_MemMap.h"

[!NOCODE!]
  [!/* Variation Point */!]
  [!IF "node:exists(as:modconf('EcuC')[1]/EcucPostBuildVariants/EcucSelectedPostBuildVariantRef)"!]
    [!LOOP "as:modconf('EcuC')[1]/EcucPostBuildVariants/EcucPostBuildVariantRef/*"!]
      [!VAR "index" = "num:i(count(text:split((.), '/')))"!]
      [!VAR "Variantname" = "text:split((.), '/')[num:i($index)]"!]
      [!CODE!][!//
        [!AUTOSPACING!]
        [!INDENT "0"!]
          /* Extern declaration of Pwm Pwm_ConfigSet for [!"$Variantname"!] */
          extern const Pwm_ConfigType Pwm_ConfigSet_[!"$Variantname"!][1U];
        [!CR!]
        [!ENDINDENT!]
      [!ENDCODE!][!//
    [!ENDLOOP!]
  [!ELSE!]
    [!CODE!][!//
      [!AUTOSPACING!]
      [!INDENT "0"!]
        /* Extern declaration of Pwm Pwm_ConfigSet */
        extern const Pwm_ConfigType Pwm_ConfigSet[1U];
      [!CR!]
      [!ENDINDENT!]
    [!ENDCODE!][!//
  [!ENDIF!]
[!ENDNOCODE!][!//

/* #Violation: Pwm_PBcfg_h_REF_1 */
#define PWM_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Pwm_MemMap.h"

#endif  /* PWM_PBCFG_H */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
