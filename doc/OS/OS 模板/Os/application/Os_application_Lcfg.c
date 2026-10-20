/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_application_Lcfg.c
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
[!VAR "CurrentAppID"="0"!][!//
[!VAR "CurrentObjectContextID"="0"!][!//
[!ENDNOCODE!][!//
[!//
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_application_Cfg.h"
#include "Os_application_Lcfg.h"
#include "Os_context_Lcfg.h"
#include "Os_hook_types.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Type Definitions                                                **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Structure Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
[!VAR "PreviousObjectInfoNum"="0"!][!//
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!LOOP "node:order(./OsCoreIdMappingConfig/*,'@index')"!][!//
        [!VAR "CurrentCoreID" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
            [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
                [!IF "node:value(./OsTrusted) = 'true'"!][!//
                    [!IF "num:i($CurrentCoreID) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                        static ApplicationStateType [!"node:name(.)"!]_StatusCfg;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"

                    [!ENDIF!][!//
                [!ELSE!][!//
                    [!IF "num:i($CurrentCoreID) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
#define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h" 
                        static ApplicationStateType [!"node:name(.)"!]_StatusCfg;
#define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"

                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
            [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
                [!IF "node:value(./OsTrusted) = 'true'"!][!//
                    [!IF "num:i($CurrentCoreID) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                        [!IF "num:i(count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*)) != num:i(0)"!][!//
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                            static TickType Application[!"num:i(./@index)"!]_NodeRunningData[APPLICATION[!"num:i(./@index)"!]_ALARM_SCHEDULETABLE_NUMBER];
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                        [!ENDIF!][!//
                        [!VAR "AppID"="num:i(./@index)"!][!//
                        [!VAR "IocCbkObjectIDCount"="0"!][!//
                        [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$AppID","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
                        [!VAR "HookObjectIDCount"="0"!][!//
                        [!CALL "Os_Calculate_Hook_ObjectCount", "AppID"= "$AppID","HookObjectIDCount" ="$HookObjectIDCount"!][!//
                    [!ENDIF!][!//
                [!ELSE!][!//
                    [!IF "num:i($CurrentCoreID) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                        [!IF "num:i(count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*)) != num:i(0)"!][!//
#define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                            static TickType Application[!"num:i(./@index)"!]_NodeRunningData[APPLICATION[!"num:i(./@index)"!]_ALARM_SCHEDULETABLE_NUMBER];
#define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                        [!ENDIF!][!//
                        [!VAR "AppID"="num:i(./@index)"!][!//
                        [!VAR "IocCbkObjectIDCount"="0"!][!//
                        [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$AppID","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
                        [!VAR "HookObjectIDCount"="0"!][!//
                        [!CALL "Os_Calculate_Hook_ObjectCount", "AppID"= "$AppID","HookObjectIDCount" ="$HookObjectIDCount"!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
            [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
            [!IF "num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId) = $CurrentCoreID"!][!//
                [!IF "node:value(./OsTrusted) = 'true'"!][!//
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                [!ELSE!][!//
#define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                [!ENDIF!][!//
                [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
                    [!IF "node:ref(.)/OsIsrCategory = 'CATEGORY_2'"!][!//
                        static Os_AppObjectRefType Core[!"num:i($CurrentCoreID)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!];
                        [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!IF "node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) != node:name(.)"!][!//
                    [!IF "(node:exists(./OsApplicationHooks/OsAppErrorHook)) and (node:value(./OsApplicationHooks/OsAppErrorHook) = 'true')"!][!//
                        static Os_AppObjectRefType Core[!"num:i($CurrentCoreID)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!];
                        [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!ENDIF!][!//
                    [!IF "(node:exists(./OsApplicationHooks/OsAppStartupHook)) and (node:value(./OsApplicationHooks/OsAppStartupHook) = 'true')"!][!//
                        static Os_AppObjectRefType Core[!"num:i($CurrentCoreID)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!];
                        [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!ENDIF!][!//
                    [!IF "(node:exists(./OsApplicationHooks/OsAppShutdownHook)) and (node:value(./OsApplicationHooks/OsAppShutdownHook) = 'true')"!][!//
                        static Os_AppObjectRefType Core[!"num:i($CurrentCoreID)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!];
                        [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!ENDIF!][!//
                [!ELSE!][!//
                    [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsErrorHook) = 'true'"!][!//
                        static Os_AppObjectRefType Core[!"num:i($CurrentCoreID)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!];
                        [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!ENDIF!][!//
                    [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsStartupHook) = 'true'"!][!//
                        static Os_AppObjectRefType Core[!"num:i($CurrentCoreID)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!];
                        [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!ENDIF!][!//
                    [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsShutdownHook) = 'true'"!][!//
                        static Os_AppObjectRefType Core[!"num:i($CurrentCoreID)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!];
                        [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!ENDIF!][!//
                    [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsProtectionHook) = 'true'"!][!//
                        static Os_AppObjectRefType Core[!"num:i($CurrentCoreID)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!];
                        [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
                [!IF "node:value(./OsTrusted) = 'true'"!][!//
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                [!ELSE!][!//
#define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                [!ENDIF!][!//

                [!IF "node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) = node:name(.)"!][!//
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                    static Os_AppObjectRefType Core[!"num:i($CurrentCoreID)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!];
                    [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!ENDLOOP!][!//
            [!VAR "PreviousObjectIoc"="0"!][!//
            [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
                [!VAR "CurrentAppID"="./@index"!][!//
                [!IF "$CurrentCoreID = num:i(node:value(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId))"!]
                [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsIoc/*/OsIocCommunication/*,'@index')"!][!//
                    [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
                        [!IF "(node:value(./OsIocReceiveCallbackEnable) = 'true') and ($CurrentAppID = node:ref(./OsIocReceivingOsApplicationRef)/@index)"!][!//
                            [!IF "node:value(node:ref(./OsIocReceivingOsApplicationRef)/OsTrusted) = 'true'"!][!//
        #define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i($CurrentCoreID)"!]_32
        #include "Os_memmap.h"
                                static Os_AppObjectRefType Core[!"num:i($CurrentCoreID)"!]_Ioc_PreviousObjectInfoPtr[!"num:i($PreviousObjectIoc)"!];
                                [!VAR "PreviousObjectIoc"="$PreviousObjectIoc + 1"!][!//
        #define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i($CurrentCoreID)"!]_32
        #include "Os_memmap.h"
                            [!ELSE!][!//
        #define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i($CurrentCoreID)"!]_32
        #include "Os_memmap.h"
                                static Os_AppObjectRefType Core[!"num:i($CurrentCoreID)"!]_Ioc_PreviousObjectInfoPtr[!"num:i($PreviousObjectIoc)"!];
                                [!VAR "PreviousObjectIoc"="$PreviousObjectIoc + 1"!][!//
        #define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i($CurrentCoreID)"!]_32
        #include "Os_memmap.h"
                            [!ENDIF!][!//

                        [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
            [!ENDIF!][!//
            [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!LOOP "node:order(./OsApplication/*,'@index')"!][!//
#define OS_START_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"
        [!IF "num:i(count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*)) != num:i(0)"!][!//
static const Os_NodeConfigType Application[!"num:i(./@index)"!]_NodeConfig[APPLICATION[!"num:i(./@index)"!]_ALARM_SCHEDULETABLE_NUMBER] =
{
    [!INDENT "4"!][!//
    [!VAR "CurrentAppNodeIndex"="num:i(0)"!][!//
    [!LOOP "node:order(./OsAppAlarmRef/*,'@index')"!][!//
    {
        [!INDENT "8"!][!//
        [!"num:i(node:ref(node:ref(.)/OsAlarmCounterRef)/@index)"!]UL,               /* CounterID */
        &Application[!"../../@index"!]_NodeRunningData[[!"num:i($CurrentAppNodeIndex)"!]]        /* &NodeInfo */
        [!VAR "CurrentAppNodeIndex" = "$CurrentAppNodeIndex + 1"!][!//
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!LOOP "node:order(./OsAppScheduleTableRef/*,'@index')"!][!//
    {
        [!INDENT "8"!][!//
        [!"num:i(node:ref(node:ref(.)/OsScheduleTableCounterRef)/@index)"!]UL,               /* CounterID */
        &Application[!"../../@index"!]_NodeRunningData[[!"num:i($CurrentAppNodeIndex)"!]]        /* &NodeInfo */
        [!VAR "CurrentAppNodeIndex" = "$CurrentAppNodeIndex + 1"!][!//
        [!VAR "ObjectID" = "$ObjectID + 1"!][!//
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
        [!ENDIF!][!//

#define OS_STOP_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h" 
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!VAR "ObjectID"="0"!][!//
[!VAR "AccessApplicationMask"="0"!][!//
[!VAR "CurrentCoreLevelIndex"="0"!][!//
[!VAR "CurrentCoreIndex"="0"!][!//
[!VAR "NextCoreIndex"="0"!][!//

[!VAR "PreviousObjectInfoNum"="0"!][!//
[!VAR "PreviousObjectIoc"="0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
#define OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
static const Os_AppObjectType Application_ObjectConfiglist[TOTALNUM_OF_OBJECT] = 
{
    [!INDENT "4"!][!//
        [!LOOP "node:order(./OsApplication/*,'@index')"!][!//
            [!VAR "NextCoreIndex"="num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
            [!IF "num:i(./@index) != num:i(0)"!][!//
                [!IF "num:i($NextCoreIndex) != num:i($CurrentCoreIndex)"!][!//
                    [!VAR "CurrentCoreLevelIndex"="num:i(0)"!][!//
                [!ENDIF!][!//
            [!ELSE!][!//
                [!VAR "CurrentCoreLevelIndex"="num:i(0)"!][!//
            [!ENDIF!][!//
        /* Current Application is App[!"num:i(./@index)"!]  */
            [!VAR "CurrentAppNodeIndex"="num:i(0)"!][!//
            [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
            {
                [!INDENT "8"!][!//
                (uint32)[!"num:i($ObjectID)"!],                 /* ObjectIDIndex */
                [!"node:ref(.)/@index"!]UL|APPLICATION[!"../../@index"!]_ID_MASK|CORE[!"num:i(node:ref(node:ref(../../OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ID_MASK,                   /* TaskID_[!"node:ref(.)/@index"!]: AppObjIDInfo[!"num:i($ObjectID)"!] */
                OBJECT_TASK,                                /* ObjectType: Task */
                {
                    [!INDENT "12"!][!//
                    .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[[!"num:i($CurrentObjectContextID)"!]]    /* &[!"node:name(node:ref(.))"!]_Context_Config */
                    [!ENDINDENT!][!//
                },
                [!VAR "CurrentObjectContextID" = "$CurrentObjectContextID + 1"!][!//
                [!VAR "AccessApplicationMask"="0"!][!//
                [!LOOP "node:order(node:ref(.)/OsTaskAccessingApplication/*,'@index')"!][!//
                    [!VAR "AccessApplicationMask" = "bit:or(num:i($AccessApplicationMask),num:i(bit:shl(1,num:i(node:ref(.)/@index))))"!][!//
                [!ENDLOOP!][!//
                (uint32)[!"num:inttohex($AccessApplicationMask,8)"!]UL,                        /* [!"node:name(node:ref(.))"!] access application bit mask. */
                NULL_PTR
                [!VAR "ObjectID" = "$ObjectID + 1"!][!//
                [!ENDINDENT!][!//
            },
            [!ENDLOOP!][!//
            [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
            {
                [!INDENT "8"!][!//
                [!VAR "CurrentNodePath" = "node:value(.)"!][!//
                [!VAR "CurrentISR2Index" = "node:ref(.)/@index"!][!//
                [!VAR "JudgeISR2IsCounter" = "'false'"!][!//
                (uint32)[!"num:i($ObjectID)"!],                 /* ObjectIDIndex */
                [!LOOP "node:order(../../OsAppCounterRef/*,'@index')"!][!//
                    [!IF "($CurrentNodePath = node:value(node:ref(.)/OsTimerTypeIsrRef)) and ('SOFTWARE' != node:value(node:ref(.)/OsCounterType))"!][!//
                        [!"num:i($CurrentISR2Index)"!]UL|APPLICATION[!"../../@index"!]_ID_MASK|APPLICATION_COUNTER[!"num:i(node:ref(.)/@index)"!]_ID_MASK,   /* ISRID_[!"num:i(node:ref(.)/@index)"!]: AppObjIDInfo[!"num:i($ObjectID)"!] */
                        [!VAR "JudgeISR2IsCounter" = "'true'"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!IF "$JudgeISR2IsCounter = 'false'"!][!//
                    [!"num:i($CurrentISR2Index)"!]UL|APPLICATION[!"../../@index"!]_ID_MASK|APPLICATION_COUNTER_INVALID_ID_MASK,    /* ISRID_[!"node:ref(.)/@index"!]: AppObjIDInfo[!"num:i($ObjectID)"!] */
                [!ENDIF!][!//
                OBJECT_ISR,                                 /* ObjectType: ISR */
                {
                    [!INDENT "12"!][!//
                    [!IF "node:value(node:ref(.)/OsIsrCategory) = 'CATEGORY_2'"!][!//
                    .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[[!"num:i($CurrentObjectContextID)"!]]    /* &[!"node:name(node:ref(.))"!]_Context_Config */
                    [!VAR "CurrentObjectContextID" = "$CurrentObjectContextID + 1"!][!//
                    [!ELSE!][!//
                    NULL_PTR
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                },
                [!VAR "AccessApplicationMask"="0"!][!//
                [!LOOP "node:order(node:ref(.)/OsIsrAccessingApplication/*,'@index')"!][!//
                    [!VAR "AccessApplicationMask" = "bit:or(num:i($AccessApplicationMask),num:i(bit:shl(1,num:i(node:ref(.)/@index))))"!][!//
                [!ENDLOOP!][!//
                (uint32)[!"num:inttohex($AccessApplicationMask,8)"!]UL,                        /* [!"node:name(node:ref(.))"!] access application bit mask. */
                [!IF "node:value(node:ref(.)/OsIsrCategory) = 'CATEGORY_2'"!][!//
                    &Core[!"num:i(node:ref(node:ref(../../OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!]       /* Os_AppObjectRefType* */
                    [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!IF "num:i($NextCoreIndex) = num:i(node:ref(node:ref(../../OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                        [!VAR "CurrentCoreLevelIndex" = "$CurrentCoreLevelIndex + 1"!][!//
                    [!ENDIF!][!//
                [!ELSE!][!//
                    NULL_PTR
                [!ENDIF!][!//
                [!VAR "ObjectID" = "$ObjectID + 1"!][!//
                [!ENDINDENT!][!//
            },
            [!ENDLOOP!][!//
            [!LOOP "node:order(./OsAppCounterRef/*,'@index')"!][!//
            {
                [!INDENT "8"!][!//
                (uint32)[!"num:i($ObjectID)"!],                 /* ObjectIDIndex */
                [!"node:ref(.)/@index"!]UL|APPLICATION[!"../../@index"!]_ID_MASK|CORE[!"num:i(node:ref(node:ref(../../OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ID_MASK,                   /* Counter_[!"node:ref(.)/@index"!]: AppObjIDInfo[!"num:i($ObjectID)"!] */
                OBJECT_COUNTER,                             /* ObjectType: Counter */
                {
                    [!INDENT "12"!][!//
                    NULL_PTR                                    /* &NULL_PTR */
                    [!ENDINDENT!][!//
                },
                [!VAR "AccessApplicationMask"="0"!][!//
                [!LOOP "node:order(node:ref(.)/OsCounterAccessingApplication/*,'@index')"!][!//
                    [!VAR "AccessApplicationMask" = "bit:or(num:i($AccessApplicationMask),num:i(bit:shl(1,num:i(node:ref(.)/@index))))"!][!//
                [!ENDLOOP!][!//
                (uint32)[!"num:inttohex($AccessApplicationMask,8)"!]UL,                        /* [!"node:name(node:ref(.))"!] access application bit mask. */                
                NULL_PTR
                [!VAR "ObjectID" = "$ObjectID + 1"!][!//
                [!ENDINDENT!][!//
            },
            [!ENDLOOP!][!//
            [!LOOP "node:order(./OsAppAlarmRef/*,'@index')"!][!//
            {
                [!INDENT "8"!][!//
                (uint32)[!"num:i($ObjectID)"!],                 /* ObjectIDIndex */
                [!"node:ref(.)/@index"!]UL|APPLICATION[!"../../@index"!]_ID_MASK|CORE[!"num:i(node:ref(node:ref(../../OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ID_MASK,                   /* Alarm_[!"node:ref(.)/@index"!]: AppObjIDInfo[!"num:i($ObjectID)"!] */
                OBJECT_ALARM,                               /* ObjectType: Alarm */
                {
                    [!INDENT "12"!][!//
                    .NodeInfo = &Application[!"../../@index"!]_NodeConfig[[!"num:i($CurrentAppNodeIndex)"!]]                 /* &NodeInfo */ 
                    [!ENDINDENT!][!//
                },
                [!VAR "CurrentAppNodeIndex" = "$CurrentAppNodeIndex + 1"!][!//
                [!VAR "AccessApplicationMask"="0"!][!//
                [!LOOP "node:order(node:ref(.)/OsAlarmAccessingApplication/*,'@index')"!][!//
                    [!VAR "AccessApplicationMask" = "bit:or(num:i($AccessApplicationMask),num:i(bit:shl(1,num:i(node:ref(.)/@index))))"!][!//
                [!ENDLOOP!][!//
                (uint32)[!"num:inttohex($AccessApplicationMask,8)"!]UL,                        /* [!"node:name(node:ref(.))"!] access application bit mask. */                  
                NULL_PTR
                [!VAR "ObjectID" = "$ObjectID + 1"!][!//
                [!ENDINDENT!][!//
            },
            [!ENDLOOP!][!//
            [!LOOP "node:order(./OsAppScheduleTableRef/*,'@index')"!][!//
            {
                [!INDENT "8"!][!//
                (uint32)[!"num:i($ObjectID)"!],                 /* ObjectIDIndex */
                [!"node:ref(.)/@index"!]UL|APPLICATION[!"../../@index"!]_ID_MASK|CORE[!"num:i(node:ref(node:ref(../../OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ID_MASK,                   /* ScheduleTable_[!"node:ref(.)/@index"!]: AppObjIDInfo[!"num:i($ObjectID)"!] */
                OBJECT_SCHEDULETABLE,                       /* ObjectType: ScheduleTable */
                {
                    [!INDENT "12"!][!//
                    .NodeInfo = &Application[!"../../@index"!]_NodeConfig[[!"num:i($CurrentAppNodeIndex)"!]]                 /* &NodeInfo */
                    [!ENDINDENT!][!//
                },
                [!VAR "CurrentAppNodeIndex" = "$CurrentAppNodeIndex + 1"!][!//
                [!VAR "AccessApplicationMask"="0"!][!//
                [!LOOP "node:order(node:ref(.)/OsSchTblAccessingApplication/*,'@index')"!][!//
                    [!VAR "AccessApplicationMask" = "bit:or(num:i($AccessApplicationMask),num:i(bit:shl(1,num:i(node:ref(.)/@index))))"!][!//
                [!ENDLOOP!][!//
                (uint32)[!"num:inttohex($AccessApplicationMask,8)"!]UL,                        /* [!"node:name(node:ref(.))"!] access application bit mask. */                 
                NULL_PTR
                [!VAR "ObjectID" = "$ObjectID + 1"!][!//
                [!ENDINDENT!][!//
            },
            [!ENDLOOP!][!//
            [!IF "node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) != node:name(.)"!][!//
                [!IF "(node:exists(./OsApplicationHooks/OsAppErrorHook)) and (node:value(./OsApplicationHooks/OsAppErrorHook) = 'true')"!][!//
                {
                    [!INDENT "8"!][!//
                    (uint32)[!"num:i($ObjectID)"!],                 /* ObjectIDIndex */
                    (uint32)ERRORHOOK|APPLICATION[!"./@index"!]_ID_MASK|CORE[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ID_MASK,                   /* App[!"./@index"!]ErrorHook: AppObjIDInfo[!"num:i($ObjectID)"!] */
                    OBJECT_APPHOOK,                             /* ObjectType: OBJECT_APPHOOK */
                    {
                        [!INDENT "12"!][!//
                        .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[[!"num:i($CurrentObjectContextID)"!]]   /* &[!"node:name(.)"!]_ErrorHook_Context_Config */
                        [!ENDINDENT!][!//
                    },
                    [!VAR "CurrentObjectContextID" = "$CurrentObjectContextID + 1"!][!//
                    (uint32)0x00000000UL,                        /* Hooks don't care the accessing app mask */
                    
                    &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!]       /* Os_AppObjectRefType* */
                    [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!IF "num:i($NextCoreIndex) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                        [!VAR "CurrentCoreLevelIndex" = "$CurrentCoreLevelIndex + 1"!][!//
                    [!ENDIF!][!//
                    [!VAR "ObjectID" = "$ObjectID + 1"!][!//
                    [!ENDINDENT!][!//
                },
                [!ENDIF!][!//
                [!IF "(node:exists(./OsApplicationHooks/OsAppStartupHook)) and (node:value(./OsApplicationHooks/OsAppStartupHook) = 'true')"!][!//
                {
                    [!INDENT "8"!][!//
                    (uint32)[!"num:i($ObjectID)"!],                 /* ObjectIDIndex */
                    (uint32)STARTUPHOOK|APPLICATION[!"./@index"!]_ID_MASK|CORE[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ID_MASK,                   /* App[!"./@index"!]StartupHook: AppObjIDInfo[!"num:i($ObjectID)"!] */
                    OBJECT_APPHOOK,                             /* ObjectType: OBJECT_APPHOOK */
                    {
                        [!INDENT "12"!][!//
                        .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[[!"num:i($CurrentObjectContextID)"!]]   /* &[!"node:name(.)"!]_StartupHook_Context_Config */
                        [!ENDINDENT!][!//
                    },
                    [!VAR "CurrentObjectContextID" = "$CurrentObjectContextID + 1"!][!//
                    (uint32)0x00000000UL,                        /* Hooks don't care the accessing app mask */
                    &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!]       /* Os_AppObjectRefType* */
                    [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!IF "num:i($NextCoreIndex) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                        [!VAR "CurrentCoreLevelIndex" = "$CurrentCoreLevelIndex + 1"!][!//
                    [!ENDIF!][!//
                    [!VAR "ObjectID" = "$ObjectID + 1"!][!//
                    [!ENDINDENT!][!//
                },
                [!ENDIF!][!//
                [!IF "(node:exists(./OsApplicationHooks/OsAppShutdownHook)) and (node:value(./OsApplicationHooks/OsAppShutdownHook) = 'true')"!][!//
                {
                    [!INDENT "8"!][!//
                    (uint32)[!"num:i($ObjectID)"!],                 /* ObjectIDIndex */
                    (uint32)SHUTDOWNHOOK|APPLICATION[!"./@index"!]_ID_MASK|CORE[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ID_MASK,                   /* App[!"./@index"!]ShutdownHook: AppObjIDInfo[!"num:i($ObjectID)"!] */
                    OBJECT_APPHOOK,                             /* ObjectType: OBJECT_APPHOOK */
                    {
                        [!INDENT "12"!][!//
                        .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[[!"num:i($CurrentObjectContextID)"!]]   /* &[!"node:name(.)"!]_ShutdownHook_Context_Config */
                        [!ENDINDENT!][!//
                    },
                    [!VAR "CurrentObjectContextID" = "$CurrentObjectContextID + 1"!][!//
                    (uint32)0x00000000UL,                        /* Hooks don't care the accessing app mask */
                    &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!]       /* Os_AppObjectRefType* */
                    [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!IF "num:i($NextCoreIndex) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                        [!VAR "CurrentCoreLevelIndex" = "$CurrentCoreLevelIndex + 1"!][!//
                    [!ENDIF!][!//
                    [!VAR "ObjectID" = "$ObjectID + 1"!][!//
                    [!ENDINDENT!][!//
                },
                [!ENDIF!][!//
            [!ELSE!][!//
                [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsErrorHook) = 'true'"!][!//
                {
                    [!INDENT "8"!][!//
                    (uint32)[!"num:i($ObjectID)"!],                 /* ObjectIDIndex */
                    (uint32)ERRORHOOK|APPLICATION[!"./@index"!]_ID_MASK|CORE[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ID_MASK,                   /* Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]ErrorHook: AppObjIDInfo[!"num:i($ObjectID)"!] */
                    OBJECT_KERNELHOOK,                          /* ObjectType: OBJECT_KERNELHOOK */
                    {
                        [!INDENT "12"!][!//
                        .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[[!"num:i($CurrentObjectContextID)"!]]    /* &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]_ErrorHook_Context_Config */
                        [!ENDINDENT!][!//
                    },
                    [!VAR "CurrentObjectContextID" = "$CurrentObjectContextID + 1"!][!//
                    (uint32)0x00000000UL,                        /* Hooks don't care the accessing app mask */
                    &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!]       /* Os_AppObjectRefType* */
                    [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!IF "num:i($NextCoreIndex) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                        [!VAR "CurrentCoreLevelIndex" = "$CurrentCoreLevelIndex + 1"!][!//
                    [!ENDIF!][!//
                    [!VAR "ObjectID" = "$ObjectID + 1"!][!//
                    [!ENDINDENT!][!//
                },
                [!ENDIF!][!//
                [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsStartupHook) = 'true'"!][!//
                {
                    [!INDENT "8"!][!//
                    (uint32)[!"num:i($ObjectID)"!],                 /* ObjectIDIndex */
                    (uint32)STARTUPHOOK|APPLICATION[!"./@index"!]_ID_MASK|CORE[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ID_MASK,                   /* Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]StartupHook: AppObjIDInfo[!"num:i($ObjectID)"!] */
                    OBJECT_KERNELHOOK,                          /* ObjectType: OBJECT_KERNELHOOK */
                    {
                        [!INDENT "12"!][!//
                        .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[[!"num:i($CurrentObjectContextID)"!]]    /* &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]_StartupHook_Context_Config */
                        [!ENDINDENT!][!//
                    },
                    [!VAR "CurrentObjectContextID" = "$CurrentObjectContextID + 1"!][!//
                    (uint32)0x00000000UL,                        /* Hooks don't care the accessing app mask */
                    &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!]      /* Os_AppObjectRefType* */
                    [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!IF "num:i($NextCoreIndex) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                        [!VAR "CurrentCoreLevelIndex" = "$CurrentCoreLevelIndex + 1"!][!//
                    [!ENDIF!][!//
                    [!VAR "ObjectID" = "$ObjectID + 1"!][!//
                    [!ENDINDENT!][!//
                },
                [!ENDIF!][!//
                [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsShutdownHook) = 'true'"!][!//
                {
                    [!INDENT "8"!][!//
                    (uint32)[!"num:i($ObjectID)"!],                 /* ObjectIDIndex */
                    (uint32)SHUTDOWNHOOK|APPLICATION[!"./@index"!]_ID_MASK|CORE[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ID_MASK,                   /* Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]ShutdownHook: AppObjIDInfo[!"num:i($ObjectID)"!] */
                    OBJECT_KERNELHOOK,                          /* ObjectType: OBJECT_KERNELHOOK */
                    {
                        [!INDENT "12"!][!//
                        .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[[!"num:i($CurrentObjectContextID)"!]]    /* &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]_ShutdownHook_Context_Config */
                        [!ENDINDENT!][!//
                    },
                    [!VAR "CurrentObjectContextID" = "$CurrentObjectContextID + 1"!][!//
                    (uint32)0x00000000UL,                        /* Hooks don't care the accessing app mask */
                    &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!]       /* Os_AppObjectRefType* */
                    [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!IF "num:i($NextCoreIndex) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                        [!VAR "CurrentCoreLevelIndex" = "$CurrentCoreLevelIndex + 1"!][!//
                    [!ENDIF!][!//
                    [!VAR "ObjectID" = "$ObjectID + 1"!][!//
                    [!ENDINDENT!][!//
                },
                [!ENDIF!][!//
                [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsProtectionHook) = 'true'"!][!//
                {
                    [!INDENT "8"!][!//
                    (uint32)[!"num:i($ObjectID)"!],                 /* ObjectIDIndex */
                    (uint32)PROTECTIONHOOK|APPLICATION[!"./@index"!]_ID_MASK|CORE[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ID_MASK,                   /* Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]ProtectionHook: AppObjIDInfo[!"num:i($ObjectID)"!] */
                    OBJECT_KERNELHOOK,                          /* ObjectType: OBJECT_KERNELHOOK */
                    {
                        [!INDENT "12"!][!//
                        .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[[!"num:i($CurrentObjectContextID)"!]]   /* &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]_ProtectionHook_Context_Config */
                        [!ENDINDENT!][!//
                    },
                    [!VAR "CurrentObjectContextID" = "$CurrentObjectContextID + 1"!][!//
                    (uint32)0x00000000UL,                        /* Hooks don't care the accessing app mask */
                    &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!]       /* Os_AppObjectRefType* */
                    [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!IF "num:i($NextCoreIndex) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                        [!VAR "CurrentCoreLevelIndex" = "$CurrentCoreLevelIndex + 1"!][!//
                    [!ENDIF!][!//
                    [!VAR "ObjectID" = "$ObjectID + 1"!][!//
                    [!ENDINDENT!][!//
                },
                [!ENDIF!][!//
                {
                    [!INDENT "8"!][!//
                    (uint32)[!"num:i($ObjectID)"!],                 /* ObjectIDIndex */
                    0UL|APPLICATION[!"./@index"!]_ID_MASK|CORE[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ID_MASK,                   /* Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartOsInitFunction_Context_Config: AppObjIDInfo[!"num:i($ObjectID)"!] */
                    OBJECT_STARTOSINITFUNCTION,                          /* ObjectType: OBJECT_STARTOSINITFUNCTION */
                    {
                        [!INDENT "12"!][!//
                        .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[[!"num:i($CurrentObjectContextID)"!]]   /* &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartOsInitFunction_Context_Config */
                        [!ENDINDENT!][!//
                    },
                    [!VAR "CurrentObjectContextID" = "$CurrentObjectContextID + 1"!][!//
                    (uint32)0x00000000UL,                        /* StartOS Init function don't care the accessing app mask */
                    &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_PreviousObjectInfoPtr[!"num:i($PreviousObjectInfoNum)"!]       /* Os_AppObjectRefType* */
                    [!VAR "PreviousObjectInfoNum"="$PreviousObjectInfoNum + 1"!][!//
                    [!IF "num:i($NextCoreIndex) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                        [!VAR "CurrentCoreLevelIndex" = "$CurrentCoreLevelIndex + 1"!][!//
                    [!ENDIF!][!//
                    [!VAR "ObjectID" = "$ObjectID + 1"!][!//
                    [!ENDINDENT!][!//
                },                
            [!ENDIF!][!//
            [!VAR "CurrentAppID"="./@index"!][!//
            [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsIoc/*/OsIocCommunication/*,'@index')"!][!//
                [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
                    [!IF "(node:value(./OsIocReceiveCallbackEnable) = 'true') and ($CurrentAppID = node:ref(./OsIocReceivingOsApplicationRef)/@index)"!][!//
            {
                    [!INDENT "8"!][!//
                    (uint32)[!"num:i($ObjectID)"!],                 /* ObjectIDIndex */
                    [!"../../@index"!]UL|APPLICATION[!"num:i($CurrentAppID)"!]_ID_MASK|CORE[!"num:i(node:ref(node:ref(node:ref(./OsIocReceivingOsApplicationRef)/OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ID_MASK,                   /* IOC_ChID_[!"../../@index"!]: AppObjIDInfo[!"num:i($ObjectID)"!] */
                    OBJECT_APPIOCCALLBACK,                      /* ObjectType: IOCCALLBACK */
                    {
                        [!INDENT "12"!][!//
                        .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[[!"num:i($CurrentObjectContextID)"!]],  /* &[!"node:name(.)"!]_Context_Config */
                        [!ENDINDENT!][!//
                    },
                    [!VAR "CurrentObjectContextID" = "$CurrentObjectContextID + 1"!][!//
                    (uint32)0x00000000UL,                        /* Ioc don't care the accessing app mask */
                    &Core[!"num:i(node:ref(node:ref(node:ref(./OsIocReceivingOsApplicationRef)/OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_Ioc_PreviousObjectInfoPtr[!"num:i($PreviousObjectIoc)"!]       /* Os_AppObjectRefType* */
                    [!VAR "PreviousObjectIoc"="$PreviousObjectIoc + 1"!][!//
                    [!IF "num:i($NextCoreIndex) = num:i(node:ref(node:ref(node:ref(./OsIocReceivingOsApplicationRef)/OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                        [!VAR "CurrentCoreLevelIndex" = "$CurrentCoreLevelIndex + 1"!][!//
                    [!ENDIF!][!//
                    [!VAR "ObjectID" = "$ObjectID + 1"!][!//
                    [!ENDINDENT!][!//
            },
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
        [!VAR "CurrentCoreIndex"="num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
        [!ENDLOOP!][!//
        [!IF "num:i($ObjectID) = num:i(0)"!]
            [!ERROR!][!//
            000-000-ERROR:The OS not configured with any Application Object. Currently, the OS is not able to run. Please check the configuration of the OS. 
            [!ENDERROR!][!//
        [!ENDIF!][!//
    [!ENDINDENT!][!//
};
#define OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//


[!LOOP "node:order(./OsApplication/*,'@index')"!][!//
#define OS_START_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"
static const Os_ApplicationConfigType [!"node:name(.)"!]_ConfigRef = 
{
    [!INDENT "4"!][!//
    (uint32)[!"num:i(@index)"!]UL,                                   /* ApplicationID */
    (uint32)[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]UL,                                   /* Logical Core ID */
    (uint32)[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]UL,                                   /* Physical Core ID */    
    (uint32)APPLICATION[!"num:i(@index)"!]_OBJECT_START_NUMBER,      /* application0 ObjectID start number of ObjectID_StartNum */    
    (uint32)APPLICATION[!"num:i(@index)"!]_OBJECTCOUNT_NUMBER,       /* ObjectCount */
    [!IF "count(./OsRestartTask/*) = 0"!][!//
    INVALID_TASK,                                                    /* RestartTask */
    [!ELSE!][!//
    [!"text:toupper(node:name(node:ref(./OsRestartTask/*[1])))"!],                           /* RestartTask */
    [!ENDIF!][!//
    [!"text:toupper(node:value(./OsTrusted))"!],                                   /* AppIsTrusted */
    [!"text:toupper(node:value(./OsTrustedApplicationDelayTimingViolationCall))"!],                 /* OsTrustedApplicationDelayTimingViolationCall */
    &[!"node:name(.)"!]_StatusCfg
    [!ENDINDENT!][!//
};

#define OS_STOP_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"   
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
#define OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
const Os_AppConfigType Os_AppConfigSet = 
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        [!LOOP "node:order(./OsApplication/*,'@index')"!][!//
            &[!"node:name(.)"!]_ConfigRef,
        [!ENDLOOP!][!//
        [!ENDINDENT!][!//
    },
    &Application_ObjectConfiglist[0]        /* ObjectRef */
    [!ENDINDENT!][!//
};
#define OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/


