/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Intc_Cfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Intc
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
*
*#Intc_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Intc_Cfg_h_REF_2:CertC-PRE00-C;
* Justification:Function like macros are used to reduce code complexity.
*
*/

[!NOCODE!][!//
[!INCLUDE "Intc_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
/**************************************************************************************************/
#ifndef INTC_CFG_H_
#define INTC_CFG_H_

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
#define INTC_CFG_AR_RELEASE_MAJOR_VERSION                      ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define INTC_CFG_AR_RELEASE_MINOR_VERSION                      ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define INTC_CFG_AR_RELEASE_REVISION_VERSION                   ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

#define INTC_CFG_SW_MAJOR_VERSION                              ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define INTC_CFG_SW_MINOR_VERSION                              ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define INTC_CFG_SW_PATCH_VERSION                              ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define INTC_CFG_VENDOR_ID                                     ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define INTC_CFG_MODULE_ID                                      ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)

/*
Configuration: IntcDevErrorDetect
- if Selected, DET is Enabled 
- if Deselected, DET is Disabled 
*/
#define INTC_DEV_ERROR_DETECT                                  [!IF "IntcGeneral/IntcDevErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

[!IF "node:exists(IntcGeneral/IntcOsekEnable) = 'true'"!][!//
/*
Configuration: IntcOsekEnable
- if Selected, OSEK OS Enabled 
- if Deselected, OSEK OS is Disabled 
*/
#define INTC_CFG_INT_OSEK_EN                                   [!IF "IntcGeneral/IntcOsekEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
[!ENDIF!][!//

/*
Configuration: IntcVersionInfoApi
- if Selected, Function Intc_GetVersionInfo is Enabled 
- if Deselected, Function Intc_GetVersionInfo is Disabled 
*/
#define INTC_CFG_VERSION_INFO_API                              [!IF "IntcGeneral/IntcVersionInfoApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/* Software generate interrupt enabled or disabled */
[!CALL "CG_GetSgiIntConfigFlag"!][!//
#define INTC_CFG_SGI_INT_EN                                    [!IF "num:i($Var_SoftIntConfigFlag) = num:i(1)"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/* Configuration parameter count */
#define INTC_CONFIGSET_CNT                                     (1U)

[!INDENT "0"!][!//
[!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!IF "num:i($Var_CoreIdx) = num:i(0)"!][!//
        [!VAR "Var_Temp_IntSrcNum" = "$Var_IntSrcNumCore0"!][!//
    [!ELSEIF "num:i($Var_CoreIdx) = num:i(1)"!][!//
        [!VAR "Var_Temp_IntSrcNum" = "$Var_IntSrcNumCore1"!][!//
    [!ELSEIF "num:i($Var_CoreIdx) = num:i(2)"!][!//
        [!VAR "Var_Temp_IntSrcNum" = "$Var_IntSrcNumCore2"!][!//
    [!ELSEIF "num:i($Var_CoreIdx) = num:i(3)"!][!//
        [!VAR "Var_Temp_IntSrcNum" = "$Var_IntSrcNumCore3"!][!//
    [!ENDIF!][!//
/* Total number of configured internal interrupt sources(SGI and PPI) in Core[!"num:i($Var_CoreIdx)"!] */
#define INTC_CFG_INTSRC_NUM_CORE[!"num:i($Var_CoreIdx)"!]                              ([!"$Var_Temp_IntSrcNum"!]U)
[!ENDFOR!][!//
/* Total number of configured internal interrupt sources(SGI and PPI) */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_INTSRC_NUM                                    ([!"$Var_IntSrcNum"!]U)
[!ENDINDENT!][!//

/* The interrupt priority configuration */
#define INTC_FIQ_MIN_PRIORITY                                  [!//
[!IF "node:value(IntcGeneral/IntcFIQPriorityBinaryPoint) = '2'"!][!//
(31U)
[!ELSEIF "node:value(IntcGeneral/IntcFIQPriorityBinaryPoint) = '3'"!][!//
(15U)
[!ELSEIF "node:value(IntcGeneral/IntcFIQPriorityBinaryPoint) = '4'"!][!//
(7U)
[!ELSEIF "node:value(IntcGeneral/IntcFIQPriorityBinaryPoint) = '5'"!][!//
(3U)
[!ELSEIF "node:value(IntcGeneral/IntcFIQPriorityBinaryPoint) = '6'"!][!//
(1U)
[!ELSEIF "node:value(IntcGeneral/IntcFIQPriorityBinaryPoint) = '7'"!][!//
(0U)
[!ENDIF!][!//
[!//
#define INTC_IRQ_MIN_PRIORITY                                  [!//
[!IF "node:value(IntcGeneral/IntcIRQPriorityBinaryPoint) = '3'"!][!//
(31U)
[!ELSEIF "node:value(IntcGeneral/IntcIRQPriorityBinaryPoint) = '4'"!][!//
(15U)
[!ELSEIF "node:value(IntcGeneral/IntcIRQPriorityBinaryPoint) = '5'"!][!//
(7U)
[!ELSEIF "node:value(IntcGeneral/IntcIRQPriorityBinaryPoint) = '6'"!][!//
(3U)
[!ELSEIF "node:value(IntcGeneral/IntcIRQPriorityBinaryPoint) = '7'"!][!//
(1U)
[!ENDIF!][!//

/* The interrupt enable status of each module */
[!CALL "CG_GeneIntCategoryEnStatusMacro"!][!//

/* Core mask for generate software interrupt */
[!CALL "CG_GeneSgiInterruptCoreMacro"!][!//

/* Configuration: Interrupt source enable status */
[!CALL "CG_GeneEnabledIntMacro"!][!//

/****************************************************************************************************
**                          Interrupt ID Macro Definition                                          **
****************************************************************************************************/
[!CALL "CG_GeneIntIdMacro"!][!//

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

#endif /* INTC_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
