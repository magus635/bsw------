[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Iom.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Iom
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
*   History:
*   2023-10-11 by HL
*     1. Original version 0.1
*
***************************************************************************************************/
[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!/************************************************************
    Macro:Iom_FindIomModuleMappedCoreId
    Find which core the Iom module is assigned to
****************************************************************/!]
[!MACRO "Iom_FindIomModuleMappedCoreId"!][!//
[!VAR "IOMModuleName" = "'IOM'"!][!//
[!VAR "IOMModuleAllocationCoreId" = "num:i(0)"!][!//
[!VAR "IomModuleMappedFlag" = "'false'"!][!//
[!SELECT "as:modconf('Resource')[1]"!][!//
[!LOOP "ResourceCoreConfigSet/ResourceCoreConfig/*"!][!//
[!VAR "Resource_CoreId" = "./ResourceCoreId"!][!//
[!VAR "Resource_CoreEnable" = "./ResourceCoreEnable"!][!//
[!IF "$Resource_CoreEnable = 'true'"!][!//
[!LOOP "ResourceAllocation/*"!][!//
[!IF "./ResourceModule = $IOMModuleName"!][!//
[!VAR "IOMModuleAllocationCoreId" = "text:split($Resource_CoreId,'CORE')[1]"!][!//
[!VAR "IomModuleMappedFlag" = "'true'"!][!//
[!BREAK!]
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!IF "$IomModuleMappedFlag = 'false'"!][!//
[!/* If not allocated the Lin channel to any core will default allocate to core0 */!][!//
[!VAR "IOMModuleAllocationCoreId" = "num:i(0)"!][!//
[!ENDIF!][!//
[!ENDMACRO!][!//

[!ENDNOCODE!][!//
