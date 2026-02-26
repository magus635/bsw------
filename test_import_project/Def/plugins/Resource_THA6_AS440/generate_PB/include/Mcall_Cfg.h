/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Mcall_Cfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : None
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
*#Mcall_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*/

[!NOCODE!][!//
[!INCLUDE "Resource_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
/***************************************************************************************************/
#ifndef MCALL_CFG_H_
#define MCALL_CFG_H_

/****************************************************************************************************
*                            Global Macro Definitions
****************************************************************************************************/
/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
#define RESOURCE_CFG_AR_RELEASE_MAJOR_VERSION                  ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define RESOURCE_CFG_AR_RELEASE_MINOR_VERSION                  ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define RESOURCE_CFG_AR_RELEASE_REVISION_VERSION               ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

#define RESOURCE_CFG_SW_MAJOR_VERSION                          ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define RESOURCE_CFG_SW_MINOR_VERSION                          ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define RESOURCE_CFG_SW_PATCH_VERSION                          ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define RESOURCE_CFG_VENDOR_ID                                 ([!"num:i(CommonPublishedInformation/VendorId)"!]U)

[!//
[!/* Judge if the cores used */!][!//
[!VAR "core_mask_flag" = "num:i(0)"!][!//
[!INDENT "0"!][!//
[!VAR "CoreMask" = "num:i(0)"!][!//
[!FOR "Var_CoreId" = "num:i(1)" TO "num:i(count(ecu:list('Resource.AvailableCores')))"!][!//
    [!VAR "Var_CoreName" = "ecu:list('Resource.AvailableCores')[num:i($Var_CoreId)]"!][!//
    [!IF "$Var_CoreName != 'CORE0'"!][!//
        [!CALL "CG_GetCoreEnableStatus", "CoreId" = "$Var_CoreName"!][!//
        [!VAR "Var_CoreNumber" = "num:i(text:split($Var_CoreName, 'CORE')[1] - 1)"!][!//
        [!IF "$CorexEnableStatus = 'true'"!][!//
            [!VAR "core_mask_flag" = "bit:or(bit:shl(num:i(1), $Var_CoreNumber), $core_mask_flag)"!][!//
        [!ENDIF!][!//
        [!VAR "CoreMask" = "bit:shl(num:i(1), $Var_CoreNumber)"!][!//
    [!ELSE!][!//
        [!VAR "CoreMask" = "0"!][!//     
    [!ENDIF!][!//
/* Core Mask for [!"$Var_CoreName"!] */
/* #Violation: Mcall_Cfg_h_REF_1 */
#define MCAL_[!"$Var_CoreName"!]_MASK                                        ([!"num:inttohex($CoreMask, 8)"!]U)
[!ENDFOR!][!//
[!ENDINDENT!][!//

/* Core mask, flag which cores used */
/* #Violation: Mcall_Cfg_h_REF_1 */
#define MCAL_USED_CORE_MASK                                    ([!"num:inttohex($core_mask_flag, 8)"!]U)

/* THA6 Processor family */
[!INDENT "0"!][!//
[!VAR "ProcessCount" = "num:i(0)"!][!//
[!LOOP "ecu:list('Resource.SupportProcessor')"!][!//
/* #Violation: Mcall_Cfg_h_REF_1 */
#define MCAL_PROCESSOR_[!"."!]                                 ([!"num:i($ProcessCount)"!]U)
    [!VAR "ProcessCount" = "$ProcessCount + num:i(1)"!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
/* Used processor is  [!"."!] */
#define MCAL_PROCESSOR_CAT                                     (MCAL_PROCESSOR_[!"node:value(ResourceGeneral/ResourceSubderivative)"!])

/* Macro for the master Core */
#define MCAL_MASTER_CORE                                       (MCAL_CORE[!"text:split(ResourceCoreConfigSet/ResourceMasterCore, 'CORE')[1]"!])

/* Total number of cores */
#define MCAL_NUMBER_OF_CORES                                   ([!"ecu:get('Resource.NumOfCores')"!]U)

/* Number of cores used */
[!CALL "CG_GetTotalNumOfCoreEnable"!][!//
/* #Violation: Mcall_Cfg_h_REF_1 */
#define MCAL_CFG_NUMBER_OF_USED_CORES                          ([!"$UsedCoreNum"!]U)

[!INDENT "0"!][!//
[!FOR "Var_CoreId" = "num:i(1)" TO "num:i(count(ecu:list('Resource.AvailableCores')))"!][!//
    [!VAR "Var_CoreName" = "ecu:list('Resource.AvailableCores')[num:i($Var_CoreId)]"!][!//
    /* [!"$Var_CoreName"!] used */
    [!CALL "CG_GetCoreEnableStatus", "CoreId" = "$Var_CoreName"!][!//
    #ifndef MCAL_CFG_ENABLE_[!"$Var_CoreName"!]
    #define MCAL_CFG_ENABLE_[!"$Var_CoreName"!]                                  ([!IF "$CorexEnableStatus = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
    #endif /* \ifndef MCAL_CFG_ENABLE_[!"$Var_CoreName"!] */
[!ENDFOR!][!//
[!ENDINDENT!][!//

[!CALL "CG_McalGeneUsedModuleMacro"!][!//

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

#endif /* MCALL_CFG_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
