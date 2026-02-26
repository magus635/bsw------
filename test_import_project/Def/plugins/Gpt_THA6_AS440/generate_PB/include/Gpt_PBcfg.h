/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Gpt_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, BASETIMER
*
*   brief                 : This file contains all configurations of GPT module
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
*#Gpt_PBcfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef GPT_PBCFG_H_
#define GPT_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Gpt_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
/* #Violation: Gpt_PBcfg_h_REF_1 */
#define GPT_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Gpt_MemMap.h"

[!NOCODE!]
  [!/* Variation Point */!]
  [!IF "node:exists(as:modconf('EcuC')[1]/EcucPostBuildVariants//EcucSelectedPostBuildVariantRef)"!]
    [!LOOP "as:modconf('EcuC')[1]/EcucPostBuildVariants//EcucPostBuildVariantRef/*"!]
      [!VAR "index" = "num:i(count(text:split((.), '/')))"!]
      [!VAR "Variantname" = "text:split((.), '/')[num:i($index)]"!]
      [!CODE!][!//
        [!AUTOSPACING!]
        [!INDENT "0"!]
          /* Extern declaration of Gpt Gpt_ConfigSet for [!"$Variantname"!] */
          extern const Gpt_ConfigType Gpt_ConfigSet_[!"$Variantname"!][1U];
        [!CR!]
        [!ENDINDENT!]
      [!ENDCODE!][!//
    [!ENDLOOP!]
  [!ELSE!]
    [!CODE!][!//
      [!AUTOSPACING!]
      [!INDENT "0"!]
        /* Extern declaration of Gpt Gpt_ConfigSet */
        extern const Gpt_ConfigType Gpt_ConfigSet[1U];
      [!CR!]
      [!ENDINDENT!]
    [!ENDCODE!][!//
  [!ENDIF!]
[!ENDNOCODE!][!//

/* #Violation: Gpt_PBcfg_h_REF_1 */
#define GPT_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Gpt_MemMap.h"

#endif  /* GPT_PBCFG_H */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
