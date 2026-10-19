/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_resource_Cfg.h
*
*   Platform              : AUTOSAR
*
*   BSW Module            : Os
*
*   brief                 : xxx
*
*   Autosar Version       : R23-11
*
*   Build Version         : Cortex-R52/THA6206
*
*   Genaration Time       : [!"$datetime"!]
*
*   Copyright (c) @#
*   All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
*  -------------------------------------------------------------------------------------------------
*  Version    Date           Author(ID)      SVN_Version         Description
*  -------------------------------------------------------------------------------------------------
*  V0.0.1   22-May-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/
#ifndef OS_RESOURCE_CFG_H_
#define OS_RESOURCE_CFG_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!VAR "ResourceId" = "0"!][!//
[!LOOP "node:order(./OsCoreIdMappingConfig/*,'num:i(node:ref(./OsCoreId)/EcucCoreId)')"!][!//
    [!VAR "CurrentCoreId" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
    [!LOOP "node:order(../../OsResource/*,'@index')"!][!//
        [!IF "(OsResourceProperty = 'LINKED') and (OsResourceLinkedToResScheduler = 'false')"!][!//
            [!VAR "ResourceCoreRef" = "node:ref(node:ref(node:ref(OsResourceLinkedResourceRef)/OsResourceCoreRef)/OsCoreId)/EcucCoreId"!][!//
        [!ELSE!][!//
            [!VAR "ResourceCoreRef" = "node:ref(node:ref(OsResourceCoreRef)/OsCoreId)/EcucCoreId"!][!//
        [!ENDIF!][!//
        [!IF "$ResourceCoreRef = $CurrentCoreId"!][!//
            #define [!"text:toupper(node:name(.))"!]        (ResourceType)([!"num:i($ResourceId)"!])
            [!VAR "ResourceId" = "$ResourceId + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "../../OsOS/OsUseResScheduler = 'true'"!][!//
        #define OS_CORE[!"$CurrentCoreId"!]_RESSCHEDULER_RESOURCE   (ResourceType)([!"num:i($ResourceId)"!])
        [!VAR "ResourceId" = "$ResourceId + 1"!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//

#define OS_RESOURCE_TOTAL_NUM [!IF "OsOS/OsUseResScheduler = 'true'"!]([!"num:i(count(./OsResource/*) + count(./OsCoreIdMappingConfig/*))"!]UL)[!ELSE!]([!"num:i(count(./OsResource/*))"!]UL)[!ENDIF!]
#define OS_RESOURCE_INVALID_CEILING (0xFFFFFFFFUL)

[!LOOP "node:order(./OsResource/*,'@index')"!][!//
    [!IF "(OsResourceProperty != 'LINKED') or (OsResourceLinkedToResScheduler = 'true')"!][!//
        [!VAR "ResourceAccessObjNum" = "0"!][!//
        [!VAR "CurrentResourceName" = "node:name(.)"!][!//
        [!VAR "IsLinkedToRes" = "OsResourceLinkedToResScheduler"!][!//
        [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
            [!LOOP "node:order(./OsTask/*,'@index')"!][!//
                [!LOOP "node:order(./OsTaskResourceRef/*,'@index')"!][!//
                    [!IF "node:name(node:ref(.)) = $CurrentResourceName"!][!//
                        [!VAR "ResourceAccessObjNum" = "$ResourceAccessObjNum + 1"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
            [!LOOP "node:order(./OsIsr/*,'@index')"!][!//
                [!LOOP "node:order(./OsIsrResourceRef/*,'@index')"!][!//
                    [!IF "node:name(node:ref(.)) = $CurrentResourceName"!][!//
                        [!IF "$IsLinkedToRes = 'true'"!][!//
                            [!ERROR!][!//
                                ERROR:[!"$CurrentResourceName"!] is linked to RES_SCHEDULER, it cannot be referenced by Isr [!"node:name(../..)"!].
                            [!ENDERROR!][!//
                        [!ENDIF!][!//
                        [!VAR "ResourceAccessObjNum" = "$ResourceAccessObjNum + 1"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
        [!ENDSELECT!][!//
        #define OS_RESOURCE_[!"text:toupper(node:name(.))"!]_ACCESS_OBJECT_NUM ([!"num:i($ResourceAccessObjNum)"!]UL)
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "OsOS/OsUseResScheduler = 'true'"!][!//
    [!LOOP "node:order(./OsCoreIdMappingConfig/*,'num:i(node:ref(./OsCoreId)/EcucCoreId)')"!][!//
        [!VAR "CoreId" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
        [!VAR "TaskNum" = "0"!][!//
        [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication/*, '@index')"!][!//
            [!IF "$CoreId = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                [!VAR "TaskNum" = "$TaskNum + count(./OsAppTaskRef/*)"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        #define OS_RESOURCE_CORE[!"num:i($CoreId)"!]_RESSCHEDULER_ACCESS_OBJECT_NUM ([!"num:i($TaskNum)"!]UL)
    [!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
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
#endif /* OS_RESOURCE_CFG_H_ */
/****************************************************************************************************
**     End of File: Os_resource_Cfg.h                                                                 **
****************************************************************************************************/

