[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Resource_Cfg_Common.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : None
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
***************************************************************************************************/
[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!/* avoid multiple inclusion */!]
[!IF "not(var:defined('RESOURCE_CFG_COMMON_M'))"!]
[!VAR "RESOURCE_CFG_COMMON_M"="'true'"!]

[!INDENT "0"!][!//
[!/* Judge the core enable status */!][!//
[!MACRO "CG_GetCoreEnableStatus", "CoreId" = ""!][!//
    [!VAR "CorexEnableStatus" = "'false'"!][!//
    [!LOOP "as:modconf('Resource')[1]/ResourceCoreConfigSet/ResourceCoreConfig/*"!][!//
        [!IF "./ResourceCoreId = $CoreId"!][!//
            [!IF "./ResourceCoreEnable"!][!//
                [!VAR "CorexEnableStatus" = "'true'"!][!//
            [!ELSE!][!//
                [!VAR "CorexEnableStatus" = "'false'"!][!//
            [!ENDIF!][!//
            [!BREAK!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!/* Calculate the total cores used */!][!//
[!MACRO "CG_GetTotalNumOfCoreEnable"!][!//
    [!VAR "UsedCoreNum" = "0"!][!//
    [!LOOP "ResourceCoreConfigSet/ResourceCoreConfig/*"!][!//
        [!IF "./ResourceCoreEnable"!][!//
            [!VAR "UsedCoreNum" = "$UsedCoreNum + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!VAR "UsedCoreNum" = "num:i($UsedCoreNum)"!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!/* Generate the Macro if the module is added in project whatever the mudule is enable or disable */!][!//
[!MACRO "CG_McalGeneUsedModuleMacro"!][!//
[!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/*/ELEMENTS/*)"!][!//
    [!IF "node:name(.) = 'MODULE-DEF'"!][!//
        [!VAR "index" = "num:i(count(text:split(node:path(.), '/')))"!][!//
        [!VAR "ModuleName" = "text:split(node:path(.), '/')[num:i($index)]"!][!//
/* MCAL module '[!"$ModuleName"!]' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_[!"text:toupper($ModuleName)"!]_USED                             (STD_ON)
/* MCAL module '[!"$ModuleName"!]' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_[!"text:toupper($ModuleName)"!]_EN                               [!IF "node:exists(as:modconf($ModuleName))"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
[!/* Line Feed */!]
    [!ENDIF!][!//
[!ENDLOOP!]

[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!ENDIF!][!// avoid multiple inclusion ENDIF
[!ENDNOCODE!][!//

