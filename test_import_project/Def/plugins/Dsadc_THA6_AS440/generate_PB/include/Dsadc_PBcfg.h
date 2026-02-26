/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Dsadc_PBcfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : DMA
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*#Dsadc_PBcfg_h_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*/

#ifndef DSADC_PBCFG_H_
#define DSADC_PBCFG_H_

#include "Dsadc_Cfg.h"
#include "Dsadc_GeneralTypes.h"

[!NOCODE!][!//
[!INCLUDE "Dsadc_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//

[!SELECT "as:modconf('Dsadc')[1]"!][!//
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/
#define DSADC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Dsadc_MemMap.h"

[!INDENT "0"!][!//
[!VAR "Var_AllVariantNumber" = "variant:size()"!][!//
[!IF "num:i($Var_AllVariantNumber) != num:i(0)"!][!//
    [!FOR "Var_VariantIdx" = "num:i(1)" TO "num:i($Var_AllVariantNumber)"!][!//
        [!VAR "Var_VariantName" = "variant:all()[num:i($Var_VariantIdx)]"!][!//
        /* Extern declaration of Dsadc configuration parameters entry for [!"$Var_VariantName"!] */
        extern const Dsadc_ConfigType Dsadc_ConfigSet_[!"$Var_VariantName"!][DSADC_CONFIGSET_CNT];
    [!ENDFOR!][!//
[!ELSE!][!//
    /* Extern declaration of Dsadc configuration parameters entry */
    extern const Dsadc_ConfigType Dsadc_ConfigSet[DSADC_CONFIGSET_CNT];
[!ENDIF!][!//
[!ENDINDENT!][!//

#define DSADC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dsadc_PBcfg_h_REF_1 */
#include "Dsadc_MemMap.h"

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
[!ENDSELECT!][!//
#endif  /* DSADC_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
