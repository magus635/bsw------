/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Can_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MCAN
*
*   brief                 : This file contains all configurations of CAN module
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef CAN_PBCFG_H_
#define CAN_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Can_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
[!INDENT "0"!][!//
[!VAR "AllVariantNumber" = "variant:size()"!][!//
[!IF "num:i($AllVariantNumber) != num:i(0)"!][!//
    [!FOR "VariantIdx" = "num:i(1)" TO "num:i($AllVariantNumber)"!][!//
        [!VAR "VariantName" = "variant:all()[num:i($VariantIdx)]"!][!//
        /* Extern declaration of Can configuration parameters entry for [!"$VariantName"!] */
        extern const Can_ConfigType Can_ConfigSet_[!"$VariantName"!][CAN_CONFIG_COUNT];
    [!ENDFOR!][!//
[!ELSE!][!//
    /* Extern declaration of Can configuration parameters entry */
    extern const Can_ConfigType Can_ConfigSet[CAN_CONFIG_COUNT];
[!ENDIF!][!//
[!ENDINDENT!][!//

#endif /* CAN_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
