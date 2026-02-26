/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Dma_PBcfg.h
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
*#Dma_PBcfg_h_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*/

#ifndef DMA_PBCFG_H_
#define DMA_PBCFG_H_

#include "Dma_Cfg.h"
#include "Dma_GeneralTypes.h"

[!NOCODE!][!//
[!INCLUDE "Dma_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//

[!SELECT "as:modconf('Dma')[1]"!][!//
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/
#define DMA_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Dma_MemMap.h"

[!INDENT "0"!][!//
[!VAR "Var_AllVariantNumber" = "variant:size()"!][!//
[!IF "num:i($Var_AllVariantNumber) != num:i(0)"!][!//
    [!FOR "Var_VariantIdx" = "num:i(1)" TO "num:i($Var_AllVariantNumber)"!][!//
        [!VAR "Var_VariantName" = "variant:all()[num:i($Var_VariantIdx)]"!][!//
        /* Extern declaration of Dma configuration parameters entry for [!"$Var_VariantName"!] */
        extern const Dma_ConfigType Dma_ConfigSet_[!"$Var_VariantName"!][DMA_CONFIGSET_CNT];
    [!ENDFOR!][!//
[!ELSE!][!//
    /* Extern declaration of Dma configuration parameters entry */
    extern const Dma_ConfigType Dma_ConfigSet[DMA_CONFIGSET_CNT];
[!ENDIF!][!//
[!ENDINDENT!][!//

#define DMA_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dma_PBcfg_h_REF_1 */
#include "Dma_MemMap.h"

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
[!ENDSELECT!][!//
#endif  /* DMA_PBCFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
