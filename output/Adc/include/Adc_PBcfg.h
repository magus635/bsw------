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

/* Extern declaration of Adc configuration parameters entry */
extern const Adc_ConfigType Adc_ConfigSet[ADC_CONFIG_COUNT];

#define ADC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Adc_PBcfg_h_REF_1 */
#include "Adc_MemMap.h"

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
#endif  /* ADC_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
