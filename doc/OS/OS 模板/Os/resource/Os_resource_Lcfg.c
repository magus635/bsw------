/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_resource_Lcfg.c
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
[!//
[!NOCODE!][!//
[!INCLUDE "Os_AppCommon.m"!][!//
[!ENDNOCODE!][!//
[!//

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_lock.h"
#include "Os_resource_Cfg.h"
#include "Os_resource_Lcfg.h"
#include "Os_resource_types.h"
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!LOOP "node:order(./OsApplication/*,'@index')"!][!//
    [!VAR "CurrentCore" = "node:name(node:ref(OsApplicationCoreRef))"!][!//
    [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
        [!IF "count(node:ref(.)/OsTaskResourceRef/*) > 0"!][!//
            [!VAR "CurrentTask" = "node:name(node:ref(.))"!][!//
            [!LOOP "node:order(node:ref(.)/OsTaskResourceRef/*,'@index')"!][!//
                [!IF "node:name(node:ref(node:ref(.)/OsResourceCoreRef)) != $CurrentCore"!][!//
                    [!ERROR!][!//
                        ERROR:Task can only reference resources within the same core! See [!"$CurrentTask"!] and [!"node:name(node:ref(.))"!].
                    [!ENDERROR!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Type Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Structure Definitions                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!LOOP "node:order(./OsCoreIdMappingConfig/*,'OsPhysicalCoreId')"!][!//
    [!VAR "CurrentPhysicalCoreId" = "OsPhysicalCoreId"!][!//
    [!VAR "CurrentCoreId" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
    #define OS_START_SEC_VAR_CLEARED_QM_CORE[!"num:i($CurrentPhysicalCoreId)"!]_32
    #include "Os_memmap.h"
    [!LOOP "node:order(../../OsResource/*,'@index')"!][!//
        [!IF "(OsResourceProperty = 'LINKED') and (OsResourceLinkedToResScheduler = 'false')"!][!//
            [!IF "node:ref(node:ref(OsResourceLinkedResourceRef)/OsResourceCoreRef)/OsPhysicalCoreId = $CurrentPhysicalCoreId"!][!//
                static Os_ResourceRunningDataType Os_[!"node:name(.)"!]_RunningData;
                static Os_LockConfigType Os_LockConfig_[!"node:name(.)"!];
            [!ENDIF!][!//
        [!ELSE!][!//
            [!IF "node:ref(OsResourceCoreRef)/OsPhysicalCoreId = $CurrentPhysicalCoreId"!][!//
                static Os_ResourceRunningDataType Os_[!"node:name(.)"!]_RunningData;
                static Os_LockConfigType Os_LockConfig_[!"node:name(.)"!];
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "../../OsOS/OsUseResScheduler = 'true'"!][!//
        static Os_ResourceRunningDataType Os_Core[!"num:i($CurrentCoreId)"!]ResSchedulerResource_RunningData;
        static Os_LockConfigType Os_LockConfig_Core[!"num:i($CurrentCoreId)"!]ResSchedulerResource;
    [!ENDIF!][!//
    #define OS_STOP_SEC_VAR_CLEARED_QM_CORE[!"num:i($CurrentPhysicalCoreId)"!]_32
    #include "Os_memmap.h"

[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!VAR "TotalResourceNum" = "num:i(count(./OsResource/*))"!][!//
[!LOOP "node:order(./OsResource/*,'@index')"!][!//
    [!IF "(OsResourceProperty != 'LINKED') or (OsResourceLinkedToResScheduler = 'true')"!][!//
        [!VAR "CurrentResourceName" = "node:name(.)"!][!//
        [!VAR "CurrentResAccessObjId" = "0"!][!//
        [!VAR "CurrentAppObjectCnt"="0"!][!//
        [!VAR "Count" = "0"!][!//
        static const uint32 Os_[!"node:name(.)"!]_AccessObjectIdList[OS_RESOURCE_[!"text:toupper(node:name(.))"!]_ACCESS_OBJECT_NUM] =
        {
            [!INDENT "4"!][!//
            [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
            [!LOOP "node:order(./OsApplication/*,'@index')"!][!//
                [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                    [!LOOP "node:order(node:ref(.)/OsTaskResourceRef/*,'@index')"!][!//
                        [!IF "node:name(node:ref(.)) = $CurrentResourceName"!][!//
                            [!IF "$Count > 0"!][!//
                                ,
                            [!ENDIF!][!//
                            [!VAR "Count" = "$Count + 1"!][!//
                            [!"num:i($CurrentResAccessObjId)"!]UL[!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ENDLOOP!][!//
                    [!VAR "CurrentResAccessObjId" = "$CurrentResAccessObjId + 1"!][!//
                [!ENDLOOP!][!//
                [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
                    [!LOOP "node:order(node:ref(.)/OsIsrResourceRef/*,'@index')"!][!//
                        [!IF "node:name(node:ref(.)) = $CurrentResourceName"!][!//
                            [!IF "$Count > 0"!][!//
                                ,
                            [!ENDIF!][!//
                            [!VAR "Count" = "$Count + 1"!][!//
                            [!"num:i($CurrentResAccessObjId)"!]UL[!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ENDLOOP!][!//
                    [!VAR "CurrentResAccessObjId" = "$CurrentResAccessObjId + 1"!][!//
                [!ENDLOOP!][!//
                [!VAR "AppID"="num:i(./@index)"!][!//
                [!VAR "IocCbkObjectIDCount"="0"!][!//
                [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$AppID","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
                [!VAR "HookObjectIDCount"="0"!][!//
                [!CALL "Os_Calculate_Hook_ObjectCount", "AppID"= "$AppID","HookObjectIDCount" ="$HookObjectIDCount"!][!//
                [!VAR "CurrentAppObjectCnt" = "num:i($CurrentAppObjectCnt + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*) + count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*) + num:i($HookObjectIDCount) + num:i($IocCbkObjectIDCount))"!][!//
                [!VAR "CurrentResAccessObjId" = "$CurrentAppObjectCnt"!][!//
            [!ENDLOOP!][!//
            [!ENDSELECT!][!//
            [!ENDINDENT!][!//
        [!CR!][!//
        };

    [!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "OsOS/OsUseResScheduler = 'true'"!][!//
    [!VAR "CurrentResAccessObjId" = "0"!][!//
    [!VAR "CurrentAppObjectCnt"="0"!][!//
    [!LOOP "node:order(./OsCoreIdMappingConfig/*,'num:i(node:ref(./OsCoreId)/EcucCoreId)')"!][!//
        [!VAR "Count" = "0"!][!//
        [!VAR "CoreId" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
        static const uint32 Os_Core[!"num:i($CoreId)"!]ResSchedulerResource_AccessObjectIdList[OS_RESOURCE_CORE[!"num:i($CoreId)"!]_RESSCHEDULER_ACCESS_OBJECT_NUM] =
        {
            [!INDENT "4"!][!//
            [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
            [!LOOP "node:order(./OsApplication/*,'@index')"!][!//
                [!IF "$CoreId = node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId"!][!//
                    [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                        [!IF "$Count > 0"!][!//
                            ,
                        [!ENDIF!][!//
                        [!VAR "Count" = "$Count + 1"!][!//
                        [!"num:i($CurrentResAccessObjId)"!]UL[!//
                        [!VAR "CurrentResAccessObjId" = "$CurrentResAccessObjId + 1"!][!//
                    [!ENDLOOP!][!//
                    [!VAR "AppID"="num:i(./@index)"!][!//
                    [!VAR "IocCbkObjectIDCount"="0"!][!//
                    [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$AppID","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
                    [!VAR "HookObjectIDCount"="0"!][!//
                    [!CALL "Os_Calculate_Hook_ObjectCount", "AppID"= "$AppID","HookObjectIDCount" ="$HookObjectIDCount"!][!//
                    [!VAR "CurrentAppObjectCnt" = "num:i($CurrentAppObjectCnt + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*) + count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*) + num:i($HookObjectIDCount) + num:i($IocCbkObjectIDCount))"!][!//
                    [!VAR "CurrentResAccessObjId" = "$CurrentAppObjectCnt"!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
            [!ENDSELECT!][!//
            [!ENDINDENT!][!//
        [!CR!][!//
        };

    [!ENDLOOP!][!//
[!ENDIF!][!//
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
            [!IF "(OsResourceProperty = 'LINKED') and (OsResourceLinkedToResScheduler = 'false')"!][!//
                [!VAR "CurrentResourceName" = "node:name(node:ref(OsResourceLinkedResourceRef))"!][!//
            [!ELSE!][!//
                [!VAR "CurrentResourceName" = "node:name(.)"!][!//
            [!ENDIF!][!//
            static const Os_ResourceConfigType Os_ResourceConfig_[!"node:name(.)"!] =
            {
                [!INDENT "4"!][!//
                [!"num:i($ResourceId)"!]UL,                     /* ResID */
                OS_RESOURCETYPE_[!"OsResourceProperty"!],    /* ResourceType */
                [!IF "OsResourceLinkedToResScheduler = 'false'"!][!//
                    [!VAR "FindAssignedIsr" = "'false'"!][!//
                    [!VAR "CeilingIsrLevel" = "31"!][!//
                    [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsIsr/*,'@index')"!][!//
                        [!LOOP "node:order(./OsIsrResourceRef/*,'@index')"!][!//
                            [!IF "node:name(node:ref(.)) = $CurrentResourceName"!][!//
                                [!VAR "FindAssignedIsr" = "'true'"!][!//
                                [!IF "node:value(../../OsIsrPriority) < $CeilingIsrLevel"!][!//
                                    [!VAR "CeilingIsrLevel" = "num:i(../../OsIsrPriority)"!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                        [!ENDLOOP!][!//
                    [!ENDLOOP!][!//
                    [!VAR "CeilingPriority" = "0"!][!//
                    [!CALL "Os_Calculate_Resource_CeilingPriority", "ResourceName"= "$CurrentResourceName", "CeilingPriority" = "$CeilingPriority"!][!//
                    [!"$CeilingPriority"!]UL,                   /* CeilingPriority */
                    [!IF "$FindAssignedIsr = 'false'"!][!//
                        OS_RESOURCE_INVALID_CEILING,                /* CeilingIsrLevel */
                    [!ELSE!][!//
                        [!"num:i($CeilingIsrLevel)"!]UL,                   /* CeilingIsrLevel */
                    [!ENDIF!][!//
                [!ELSE!][!//
                    0xFFFFFFFFUL,                   /* CeilingPriority */
                    OS_RESOURCE_INVALID_CEILING,                /* CeilingIsrLevel */
                [!ENDIF!][!//
                &Os_LockConfig_[!"node:name(.)"!],                  /* Lock */
                /* AccessObjectList */
                {
                    [!INDENT "8"!][!//
                    Os_[!"$CurrentResourceName"!]_AccessObjectIdList,
                    OS_RESOURCE_[!"text:toupper($CurrentResourceName)"!]_ACCESS_OBJECT_NUM
                    [!ENDINDENT!][!//
                },
                &Os_[!"node:name(.)"!]_RunningData              /* RunningData */
                [!ENDINDENT!][!//
            };
            [!CR!][!//
            [!VAR "ResourceId" = "$ResourceId + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "../../OsOS/OsUseResScheduler = 'true'"!][!//
        static const Os_ResourceConfigType Os_ResourceConfig_Core[!"$CurrentCoreId"!]ResSchedulerResource =
        {
            [!INDENT "4"!][!//
            [!"num:i($ResourceId)"!]UL,                     /* ResID */
            OS_RESOURCETYPE_STANDARD,   /* ResourceType */
            0xFFFFFFFFUL,                   /* CeilingPriority */
            OS_RESOURCE_INVALID_CEILING,                /* CeilingIsrLevel */
            &Os_LockConfig_Core[!"$CurrentCoreId"!]ResSchedulerResource,                  /* Lock */
            {
                [!INDENT "8"!][!//
                Os_Core[!"$CurrentCoreId"!]ResSchedulerResource_AccessObjectIdList,
                OS_RESOURCE_CORE[!"$CurrentCoreId"!]_RESSCHEDULER_ACCESS_OBJECT_NUM
                [!ENDINDENT!][!//
            },
            &Os_Core[!"$CurrentCoreId"!]ResSchedulerResource_RunningData              /* RunningData */
            [!ENDINDENT!][!//
        };
        [!VAR "ResourceId" = "$ResourceId + 1"!][!//
        [!CR!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
const Os_ResourceConfigRefType Os_ResourceConfigSet[OS_RESOURCE_TOTAL_NUM + 1U] = 
{
[!INDENT "4"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!LOOP "node:order(./OsCoreIdMappingConfig/*,'num:i(node:ref(./OsCoreId)/EcucCoreId)')"!][!//
    [!VAR "CurrentCoreId" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
    [!LOOP "node:order(../../OsResource/*,'@index')"!][!//
        [!IF "(OsResourceProperty = 'LINKED') and (OsResourceLinkedToResScheduler = 'false')"!][!//
            [!VAR "ResourceCoreRef" = "node:ref(node:ref(node:ref(OsResourceLinkedResourceRef)/OsResourceCoreRef)/OsCoreId)/EcucCoreId"!][!//
        [!ELSE!][!//
            [!VAR "ResourceCoreRef" = "node:ref(node:ref(OsResourceCoreRef)/OsCoreId)/EcucCoreId"!][!//
        [!ENDIF!][!//
        [!IF "$ResourceCoreRef = $CurrentCoreId"!][!//
            &Os_ResourceConfig_[!"node:name(.)"!],
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "../../OsOS/OsUseResScheduler = 'true'"!][!//
        &Os_ResourceConfig_Core[!"$CurrentCoreId"!]ResSchedulerResource,
    [!ENDIF!][!//
[!ENDLOOP!][!//
    NULL_PTR
[!ENDSELECT!][!//
[!ENDINDENT!][!//
};

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/





