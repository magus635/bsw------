/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Adc_PBcfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : SARADC
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
*#Adc_PBcfg_h_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*/

#ifndef ADC_PBCFG_H_
#define ADC_PBCFG_H_

#include "Adc_Cfg.h"
#include "Adc_GeneralTypes.h"

[!NOCODE!][!//
[!INCLUDE "Adc_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//

[!SELECT "as:modconf('Adc')[1]"!][!//
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/
#define ADC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Adc_MemMap.h"

[!INDENT "0"!][!//
[!VAR "Var_AllVariantNumber" = "variant:size()"!][!//
[!IF "num:i($Var_AllVariantNumber) != num:i(0)"!][!//
    [!FOR "Var_VariantIdx" = "num:i(1)" TO "num:i($Var_AllVariantNumber)"!][!//
        [!VAR "Var_VariantName" = "variant:all()[num:i($Var_VariantIdx)]"!][!//
        /* Extern declaration of Adc configuration parameters entry for [!"$Var_VariantName"!] */
        extern const Adc_ConfigType Adc_ConfigSet_[!"$Var_VariantName"!][ADC_CONFIG_COUNT];
    [!ENDFOR!][!//
[!ELSE!][!//
    /* Extern declaration of Adc configuration parameters entry */
    extern const Adc_ConfigType Adc_ConfigSet[ADC_CONFIG_COUNT];
[!ENDIF!][!//
[!ENDINDENT!][!//

#define ADC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Adc_PBcfg_h_REF_1 */
#include "Adc_MemMap.h"

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
[!ENDSELECT!][!//
#endif  /* ADC_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
