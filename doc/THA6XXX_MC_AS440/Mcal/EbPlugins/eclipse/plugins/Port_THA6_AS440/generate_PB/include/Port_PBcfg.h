/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Port_PBcfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
*
*   brief                 : This file contains all configurations of PORT module
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef PORT_PBCFG_H_
#define PORT_PBCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Port_GeneralTypes.h"

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
[!INDENT "0"!][!//
[!VAR "AllVariantNumber" = "variant:size()"!][!//
[!IF "num:i($AllVariantNumber) != num:i(0)"!][!//
    [!FOR "VariantIdx" = "num:i(1)" TO "num:i($AllVariantNumber)"!][!//
        [!VAR "VariantName" = "variant:all()[num:i($VariantIdx)]"!][!//
        /* Extern declaration of Port configuration parameters entry for [!"$VariantName"!] */
        extern const Port_ConfigType Port_ConfigSet_[!"$VariantName"!][PORT_CONFIG_COUNT];
    [!ENDFOR!][!//
[!ELSE!][!//
    /* Extern declaration of Port configuration parameters entry */
    extern const Port_ConfigType Port_ConfigSet[PORT_CONFIG_COUNT];
[!ENDIF!][!//
[!ENDINDENT!][!//

#endif /* PORT_PBCFG_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
