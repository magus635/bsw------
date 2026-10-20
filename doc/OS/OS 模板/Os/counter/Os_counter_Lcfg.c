/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_counter_Lcfg.c
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


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_counter_types.h"
#include "Os_timer_Lcfg.h"
#include "Os_counter_Cfg.h"
#include "Os_counter_Lcfg.h"
[!//
[!NOCODE!][!//
[!INCLUDE "Os_AppCommon.m"!][!//
[!ENDNOCODE!][!//
[!//
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

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
[!VAR "AllCounterInApp" = "','"!][!//
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
[!VAR "CurrentAppObjectCnt"="0"!][!//
[!VAR "CounterObjectID" = "0"!][!//
[!LOOP "node:order(./*,'@index')"!][!//
    [!IF "node:value(./OsTrusted) = 'true'"!][!//
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
    [!ELSE!][!//
#define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
    [!ENDIF!][!//
        [!VAR "CounterObjectID" = "num:i($CounterObjectID + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*))"!][!//
        [!LOOP "node:order(./OsAppCounterRef/*)"!][!//
        [!VAR "AllCounterInApp" = "concat($AllCounterInApp, node:name(node:ref(.)), ',')"!][!//
            [!IF "node:ref(.)/OsCounterType = 'SOFTWARE'"!][!//
                static Os_CounterRunningDataType    [!"node:name(node:ref(.))"!]RunningData;
                static Os_CounterNodeQueueDataType  [!"node:name(node:ref(.))"!]NodeQueueData[OS_CFG_COUNTER_NUM_[!"text:toupper(node:name(node:ref(.)))"!]_OBJECTS + 1];
                static Os_CounterNodeQueueType      [!"node:name(node:ref(.))"!]NodeQueue;
            [!ELSEIF "node:ref(.)/OsTimerHighResolution = 'true'"!][!//
                static Os_CounterNodeQueueDataType  [!"node:name(node:ref(.))"!]NodeQueueData[OS_CFG_COUNTER_NUM_[!"text:toupper(node:name(node:ref(.)))"!]_OBJECTS + 1];
                static Os_CounterNodeQueueType      [!"node:name(node:ref(.))"!]NodeQueue;
            [!ELSEIF "node:ref(node:ref(.)/OsTimerTypeIsrRef)/OsIsrInterruptSource = 27 or node:ref(node:ref(.)/OsTimerTypeIsrRef)/OsIsrInterruptSource = 30"!][!//
                static Os_CounterFrtRunningDataType  [!"node:name(node:ref(.))"!]RunningData;
                static Os_CounterNodeQueueDataType  [!"node:name(node:ref(.))"!]NodeQueueData[OS_CFG_COUNTER_NUM_[!"text:toupper(node:name(node:ref(.)))"!]_OBJECTS + 1];
                static Os_CounterNodeQueueType      [!"node:name(node:ref(.))"!]NodeQueue;
            [!ELSE!][!//
                static Os_CounterRunningDataType  [!"node:name(node:ref(.))"!]RunningData;
                static Os_CounterNodeQueueDataType  [!"node:name(node:ref(.))"!]NodeQueueData[OS_CFG_COUNTER_NUM_[!"text:toupper(node:name(node:ref(.)))"!]_OBJECTS + 1];
                static Os_CounterNodeQueueType      [!"node:name(node:ref(.))"!]NodeQueue;
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!VAR "AppID"="num:i(./@index)"!][!//
        [!VAR "IocCbkObjectIDCount"="0"!][!//
        [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$AppID","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
        [!VAR "HookObjectIDCount"="0"!][!//
        [!CALL "Os_Calculate_Hook_ObjectCount", "AppID"= "$AppID","HookObjectIDCount" ="$HookObjectIDCount"!][!//
        [!VAR "CurrentAppObjectCnt" = "num:i($CurrentAppObjectCnt + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*) + count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*) + num:i($HookObjectIDCount) + num:i($IocCbkObjectIDCount))"!][!//
        [!VAR "CounterObjectID" = "$CurrentAppObjectCnt"!][!//
    [!IF "node:value(./OsTrusted) = 'true'"!][!//
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
    [!ELSE!][!//
#define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
    [!ENDIF!][!//

[!ENDLOOP!][!//
[!ENDSELECT!][!//
/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/

[!VAR "AllCounterInApp" = "','"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
[!VAR "CurrentAppObjectCnt"="0"!][!//
[!VAR "CounterObjectID" = "0"!][!//
[!LOOP "node:order(./*,'@index')"!][!//
    #define OS_START_SEC_CONST_QM_CORE[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_UNSPECIFIED
    #include "Os_memmap.h"
    [!VAR "CounterObjectID" = "num:i($CounterObjectID + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*))"!][!//
    [!LOOP "node:order(./OsAppCounterRef/*)"!][!//
    [!IF "contains($AllCounterInApp, concat(',', node:name(node:ref(.)), ','))"!][!//
        [!ERROR!][!//
            ERROR:The [!"node:name(node:ref(.))"!] Counter is multi referenced in [!"node:name(./../..)"!].
        [!ENDERROR!][!//
    [!ENDIF!][!//
    [!VAR "AllCounterInApp" = "concat($AllCounterInApp, node:name(node:ref(.)), ',')"!][!//
        [!IF "node:ref(.)/OsCounterType = 'SOFTWARE'"!][!//
            
            const Os_CounterQueueMemConfigType [!"node:name(node:ref(.))"!]QueueMemCfg =
            {
                [!INDENT "4"!][!//
                OS_CFG_COUNTER_NUM_[!"text:toupper(node:name(node:ref(.)))"!]_OBJECTS + 1,             /* Size */
                &[!"node:name(node:ref(.))"!]NodeQueueData[0]                /* FreeQueueHead */ 
                [!ENDINDENT!][!//
            };

            const Os_CounterConfigType Os_[!"node:name(node:ref(.))"!]ConfigSet =
            {
                [!INDENT "4"!][!//
                {
                    [!INDENT "8"!][!//
                    [!"num:i(node:value(node:ref(.)/OsCounterMaxAllowedValue))"!]ul,           /* MaxAllowedCountValue */
                    [!"num:i(node:value(node:ref(.)/OsCounterMaxAllowedValue))"!]ul,            /* MaxDifferenceValue */
                    [!"node:value(node:ref(.)/OsCounterMinCycle)"!]ul,           /* MinCyle */
                    [!"node:value(node:ref(.)/OsCounterTicksPerBase)"!]ul,       /* TicksPerBase */
                    [!ENDINDENT!][!//
                },            /* CounterAttr */
                [!"num:i($CounterObjectID)"!]ul,              /* ObjectID */
                [!VAR "CounterObjectID" = "$CounterObjectID + 1"!][!//
                COUNTER_DRIVER_SOFTERWARE,               /* DriverType */
                &[!"node:name(node:ref(.))"!]NodeQueue,            /* NodeQueue */
                &[!"node:name(node:ref(.))"!]RunningData,          /* RunningData */
                &[!"node:name(node:ref(.))"!]QueueMemCfg,          /* QueueMemCfg */
                NULL_PTR               /* HwCfg */
                [!ENDINDENT!][!//
            };
        [!ELSEIF "node:ref(.)/OsTimerHighResolution = 'true'"!][!//

            const Os_CounterQueueMemConfigType [!"node:name(node:ref(.))"!]QueueMemCfg =
            {
                [!INDENT "4"!][!//
                OS_CFG_COUNTER_NUM_[!"text:toupper(node:name(node:ref(.)))"!]_OBJECTS + 1,
                &[!"node:name(node:ref(.))"!]NodeQueueData[0]
                [!ENDINDENT!][!//
            };

            static const Os_CounterHwConfigType [!"node:name(node:ref(.))"!]HwCfg =
            {
                [!INDENT "4"!][!//
                TIMER_DRIVER_HRTTIMER,
                {
                    [!INDENT "8"!][!//
                    .HrtCfg = &OsTimer_Hal_[!"node:name(node:ref(.))"!]HwCfg
                    [!ENDINDENT!][!//
                }
                [!ENDINDENT!][!//
            };

            const Os_CounterConfigType Os_[!"node:name(node:ref(.))"!]ConfigSet =
            {
                [!INDENT "4"!][!//
                {
                    [!INDENT "8"!][!//
                    [!"num:i(node:value(node:ref(.)/OsCounterMaxAllowedValue))"!]ul,           /* MaxAllowedCountValue */
                    [!"num:i(node:value(node:ref(.)/OsCounterMaxAllowedValue))"!]ul,            /* MaxDifferenceValue */
                    [!"node:value(node:ref(.)/OsCounterMinCycle)"!]ul,           /* MinCyle */
                    [!"node:value(node:ref(.)/OsCounterTicksPerBase)"!]ul       /* TicksPerBase */
                    [!ENDINDENT!][!//
                },            /* CounterAttr */
                [!"num:i($CounterObjectID)"!]ul,             /* ObjectID */
                [!VAR "CounterObjectID" = "$CounterObjectID + 1"!][!//
                COUNTER_DRIVER_HARDWARE,               /* DriverType */
                &[!"node:name(node:ref(.))"!]NodeQueue,            /* NodeQueue */
                NULL_PTR ,          /* RunningData */
                &[!"node:name(node:ref(.))"!]QueueMemCfg,          /* QueueMemCfg */
                &[!"node:name(node:ref(.))"!]HwCfg               /* HwCfg */
                [!ENDINDENT!][!//
            };
        [!ELSEIF "node:ref(node:ref(.)/OsTimerTypeIsrRef)/OsIsrInterruptSource = 27 or node:ref(node:ref(.)/OsTimerTypeIsrRef)/OsIsrInterruptSource = 30"!][!//

            static const Os_CounterQueueMemConfigType [!"node:name(node:ref(.))"!]QueueMemCfg =
            {
                [!INDENT "4"!][!//
                OS_CFG_COUNTER_NUM_[!"text:toupper(node:name(node:ref(.)))"!]_OBJECTS + 1,
                &[!"node:name(node:ref(.))"!]NodeQueueData[0]
                [!ENDINDENT!][!//
            };

            static const Os_CounterHwConfigType [!"node:name(node:ref(.))"!]HwCfg =
            {
                [!INDENT "4"!][!//
                TIMER_DRIVER_FRTTIMER,
                {
                    [!INDENT "8"!][!//
                    .FrtCfg = &OsTimer_Hal_[!"node:name(node:ref(.))"!]HwCfg
                    [!ENDINDENT!][!//Z
                }
                [!ENDINDENT!][!//
            };

            static const Os_CounterConfigType Os_[!"node:name(node:ref(.))"!]ConfigSet =
            {
                [!INDENT "4"!][!//
                {
                    [!INDENT "8"!][!//
                    [!"num:i(node:value(node:ref(.)/OsCounterMaxAllowedValue))"!]ul,           /* MaxAllowedCountValue */
                    [!"num:i(node:value(node:ref(.)/OsCounterMaxAllowedValue))"!]ul,            /* MaxDifferenceValue */
                    [!"node:value(node:ref(.)/OsCounterMinCycle)"!]ul,           /* MinCyle */
                    [!"node:value(node:ref(.)/OsCounterTicksPerBase)"!]ul        /* TicksPerBase */
                    [!ENDINDENT!][!//
                },            /* CounterAttr */
                [!"num:i($CounterObjectID)"!]ul,               /* ObjectID */
                [!VAR "CounterObjectID" = "$CounterObjectID + 1"!][!//
                COUNTER_DRIVER_HARDWARE,               /* DriverType */
                &[!"node:name(node:ref(.))"!]NodeQueue,            /* NodeQueue */
                (Os_CounterRunningDataRefType)&[!"node:name(node:ref(.))"!]RunningData,          /* RunningData */
                &[!"node:name(node:ref(.))"!]QueueMemCfg,          /* QueueMemCfg */
                &[!"node:name(node:ref(.))"!]HwCfg               /* HwCfg */
                [!ENDINDENT!][!//
            };
        [!ELSE!][!//

            static const Os_CounterQueueMemConfigType [!"node:name(node:ref(.))"!]QueueMemCfg =
            {
                [!INDENT "4"!][!//
                OS_CFG_COUNTER_NUM_[!"text:toupper(node:name(node:ref(.)))"!]_OBJECTS + 1,
                &[!"node:name(node:ref(.))"!]NodeQueueData[0],
                [!ENDINDENT!][!//
            };

            static const Os_CounterHwConfigType [!"node:name(node:ref(.))"!]HwCfg =
            {
                [!INDENT "4"!][!//
                TIMER_DRIVER_PITTIMER,
                {
                    .PitCfg = &OsTimer_Hal_[!"node:name(node:ref(.))"!]HwCfg  
                }
                [!ENDINDENT!][!//
            };

            static const Os_CounterConfigType Os_[!"node:name(node:ref(.))"!]ConfigSet =
            {
                [!INDENT "4"!][!//
                {
                    [!INDENT "8"!][!//
                    [!"num:i(node:value(node:ref(.)/OsCounterMaxAllowedValue))"!]ul,           /* MaxAllowedCountValue */
                    [!"num:i(node:value(node:ref(.)/OsCounterMaxAllowedValue))"!]ul,           /* MaxDifferenceValue */
                    [!"node:value(node:ref(.)/OsCounterMinCycle)"!]ul,           /* MinCyle */
                    [!"node:value(node:ref(.)/OsCounterTicksPerBase)"!]ul,           /* TicksPerBase */
                    [!ENDINDENT!][!//
                },            /* CounterAttr */
                [!"num:i($CounterObjectID)"!]ul,               /* ObjectID */
                [!VAR "CounterObjectID" = "$CounterObjectID + 1"!][!//
                COUNTER_DRIVER_HARDWARE,               /* DriverType */
                &[!"node:name(node:ref(.))"!]NodeQueue,            /* NodeQueue */
                &[!"node:name(node:ref(.))"!]RunningData,          /* RunningData */
                &[!"node:name(node:ref(.))"!]QueueMemCfg,          /* QueueMemCfg */
                &[!"node:name(node:ref(.))"!]HwCfg               /* HwCfg */
                [!ENDINDENT!][!//
            };        
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!VAR "AppID"="num:i(./@index)"!][!//
    [!VAR "IocCbkObjectIDCount"="0"!][!//
    [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$AppID","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
    [!VAR "HookObjectIDCount"="0"!][!//
    [!CALL "Os_Calculate_Hook_ObjectCount", "AppID"= "$AppID","HookObjectIDCount" ="$HookObjectIDCount"!][!//
    [!VAR "CurrentAppObjectCnt" = "num:i($CurrentAppObjectCnt + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*) + count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*) + num:i($HookObjectIDCount) + num:i($IocCbkObjectIDCount))"!][!//
    [!VAR "CounterObjectID" = "$CurrentAppObjectCnt"!][!// 
#define OS_STOP_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"

[!ENDLOOP!][!//
[!ENDSELECT!][!//


/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
#define OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
CONSTP2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) Os_CounterConfigSet[OS_COUNTER_TOTAL_NUM] =
{
    [!INDENT "4"!][!//
    [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCounter"!][!//
    [!VAR "CounterNumber" = "num:i(count(./*)) - 1"!][!//
        [!LOOP "node:order(./*,'@index')"!][!//
            [!VAR "CounterName" = "concat(',',node:name(.),',')"!][!//
            [!IF "contains($AllCounterInApp, $CounterName)"!][!//
            [!ELSE!][!//
                [!ERROR!][!//
                    ERROR:The [!"node:name(.)"!] Counter is not referenced in any application.
                [!ENDERROR!][!//
            [!ENDIF!][!//
            [!IF "num:i($CounterNumber) = num:i(@index)"!][!//
                &Os_[!"node:name(.)"!]ConfigSet
            [!ELSE!][!//
                &Os_[!"node:name(.)"!]ConfigSet,
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!ENDINDENT!][!//
};
#define OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/





