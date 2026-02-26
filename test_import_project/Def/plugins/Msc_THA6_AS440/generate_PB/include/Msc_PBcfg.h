/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Msc_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MSC
*
*   brief                 : This file contains all configurations of MSC module
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef MSC_PBCFG_H_
#define MSC_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Msc_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
#define ICU_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
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
          /* Extern declaration of Msc Msc_ConfigSet for [!"$Variantname"!] */
          extern const Msc_ConfigType Msc_ConfigSet_[!"$Variantname"!][1U];
        [!CR!]
        [!ENDINDENT!]
      [!ENDCODE!][!//
    [!ENDLOOP!]
  [!ELSE!]
    [!CODE!][!//
      [!AUTOSPACING!]
      [!INDENT "0"!]
        /* Extern declaration of Msc Msc_ConfigSet */
        extern const Msc_ConfigType Msc_ConfigSet[1U];
      [!CR!]
      [!ENDINDENT!]
    [!ENDCODE!][!//
  [!ENDIF!]
[!ENDNOCODE!][!//

#define ICU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Icu_MemMap.h"

#endif /* MSC_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
