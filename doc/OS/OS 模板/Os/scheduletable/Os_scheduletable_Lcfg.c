/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_scheduletable_Lcfg.c
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
#include "Compiler.h"
#include "Os_scheduletable_types.h"
#include "Os_scheduletable_Lcfg.h"
#include "Os_scheduletable_Cfg.h"
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
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!LOOP "node:order(./OsCoreIdMappingConfig/*,'OsPhysicalCoreId')"!][!//
    [!VAR "CurrentPhysicalCoreId" = "OsPhysicalCoreId"!][!//
    [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
        [!IF "node:ref(OsApplicationCoreRef)/OsPhysicalCoreId = $CurrentPhysicalCoreId"!][!//
        [!IF "count(./OsAppScheduleTableRef/*) != 0"!][!//
            [!IF "node:value(./OsTrusted) = 'true'"!][!//
    #define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
    #include "Os_memmap.h"
            [!ELSE!][!//
    #define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
    #include "Os_memmap.h"
            [!ENDIF!][!//
                    [!LOOP "node:order(./OsAppScheduleTableRef/*,'@index')"!][!//
                        static OsSchT_Type Os_[!"node:name(node:ref(.))"!]_RunningData;
                    [!ENDLOOP!][!//
            [!IF "node:value(./OsTrusted) = 'true'"!][!//
    #define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
    #include "Os_memmap.h"
            [!ELSE!][!//
    #define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
    #include "Os_memmap.h"
            [!ENDIF!][!//
            
        [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!VAR "CurrentAppObjectCnt"="0"!][!//
[!VAR "SchTObjectID" = "0"!][!//
[!LOOP "node:order(./OsApplication/*,'@index')"!][!//
[!IF "num:i(count(./OsAppScheduleTableRef/*)) != '0'"!][!//
#define OS_START_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"

[!ENDIF!][!//
    [!VAR "SchTObjectID" = "num:i($SchTObjectID + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*) + count(./OsAppAlarmRef/*))"!][!//
    [!VAR "CurrentCore" = "node:name(node:ref(OsApplicationCoreRef))"!][!//
    [!LOOP "node:order(./OsAppScheduleTableRef/*,'@index')"!][!//
        [!VAR "CurrentSchTName" = "node:name(node:ref(.))"!][!//
        [!VAR "CounterName" = "node:name(node:ref(node:ref(.)/OsScheduleTableCounterRef))"!][!//
        [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication/*,'@index')"!][!//
            [!VAR "CounterCore" = "node:name(node:ref(OsApplicationCoreRef))"!][!//
            [!LOOP "node:order(./OsAppCounterRef/*,'@index')"!][!//
                [!IF "node:name(node:ref(.)) = $CounterName"!][!//
                    [!IF "$CounterCore != $CurrentCore"!][!//
                        [!ERROR!][!//
                            ERROR:It shall not be allowed to drive [!"$CurrentSchTName"!] from a Counter, which is assigned to a different core.
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                    [!BREAK!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDLOOP!][!//
        [!VAR "MinCycle" = "node:value(node:ref(node:ref(.)/OsScheduleTableCounterRef)/OsCounterMinCycle)"!][!//
        [!VAR "MaxAllowedValue" = "node:value(node:ref(node:ref(.)/OsScheduleTableCounterRef)/OsCounterMaxAllowedValue)"!][!//
        [!LOOP "node:order(node:ref(.)/OsScheduleTableExpiryPoint/*,'OsScheduleTblExpPointOffset')"!][!//
            [!IF "@index = 0"!][!//
                [!VAR "PreviousOffset" = "num:i(OsScheduleTblExpPointOffset)"!][!//
            [!ELSE!][!//
                [!IF "((num:i(OsScheduleTblExpPointOffset) - num:i($PreviousOffset)) < num:i($MinCycle)) or
                      ((num:i(OsScheduleTblExpPointOffset) - num:i($PreviousOffset)) > num:i($MaxAllowedValue))"!][!//
                    [!ERROR!][!//
                        ERROR:The delay between adjacent expiry points of [!"node:name(../..)"!] shall be in the range Os-CounterMinCycle ..OsCounterMaxAllowedValue of the underlying Counter.
                    [!ENDERROR!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!IF "node:value(../../OsScheduleTblSyncStrategy) = 'EXPLICIT'"!][!//
                [!IF "@index != 0"!][!//
                    [!IF "(num:i(OsScheduleTblExpPointOffset) - num:i(OsScheduleTableMaxShorten)) < (num:i($PreviousOffset) + num:i($MinCycle))"!][!//
                        [!ERROR!][!//
                            ERROR:The value of (Offset - OsScheduleTableMaxShorten) of [!"node:name(.)"!] of [!"node:name(../..)"!] shall be greater than (Offset + OsCounterMinCycle) of the pervious expiry point.
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                    [!IF "(num:i(OsScheduleTblExpPointOffset) - num:i($PreviousOffset) + num:i(OsScheduleTableMaxLengthen)) >= num:i($MaxAllowedValue)"!][!//
                        [!ERROR!][!//
                            ERROR:The value of (OsScheduleTableMaxLengthen + delay_from_previous_EP) of [!"node:name(.)"!] of [!"node:name(../..)"!] shall be less than the OsCounterMaxAllowedValue of the underlying Counter.
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!IF "node:islast(.)"!][!//
                [!IF "node:value(../../OsScheduleTableRepeating) = 'false'"!][!//
                    [!IF "((num:i(node:value(../../OsScheduleTableDuration)) - num:i(OsScheduleTblExpPointOffset)) < 0) or
                          ((num:i(node:value(../../OsScheduleTableDuration)) - num:i(OsScheduleTblExpPointOffset)) > num:i($MaxAllowedValue))"!][!//
                        [!ERROR!][!//
                            ERROR:For single-shot schedule table, final delay of [!"node:name(../..)"!] shall be in the range 0..OsCounterMaxAllowedValue of the underlying Counter.
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ELSE!][!//
                    [!IF "((num:i(node:value(../../OsScheduleTableDuration)) - num:i(OsScheduleTblExpPointOffset)) < num:i($MinCycle)) or
                          ((num:i(node:value(../../OsScheduleTableDuration)) - num:i(OsScheduleTblExpPointOffset)) > num:i($MaxAllowedValue))"!][!//
                        [!ERROR!][!//
                            ERROR:For periodic schedule table, final delay of [!"node:name(../..)"!] shall be in the range OsCounterMinCycle..OsCounterMaxAllowedValue of the underlying Counter.
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!LOOP "node:order(node:ref(.)/OsScheduleTableExpiryPoint/*,'@index')"!][!//
            [!IF "(count(./OsScheduleTableTaskActivation/*) = 0) and (count(./OsScheduleTableEventSetting/*) = 0)"!][!//
                [!ERROR!][!//
                    ERROR:The [!"node:name(.)"!] of [!"node:name(../..)"!] must activate a task or set an event.
                [!ENDERROR!][!//
            [!ENDIF!][!//
            [!IF "count(./OsScheduleTableTaskActivation/*) > 0"!][!//
static const TaskType Os_[!"$CurrentSchTName"!]_[!"node:name(.)"!]_Tasks[OS_[!"text:toupper($CurrentSchTName)"!]_[!"text:toupper(node:name(.))"!]_TASKS] =
{
    [!LOOP "node:order(./OsScheduleTableTaskActivation/*,'@index')"!][!//
    [!INDENT "4"!][!//
    [!"num:i(node:pos(node:ref(./OsScheduleTableActivateTaskRef)))"!]UL,     /* Task */
    [!ENDINDENT!][!//
    [!ENDLOOP!][!//
};

            [!ENDIF!][!//
            [!IF "count(./OsScheduleTableEventSetting/*) > 0"!][!//
static const OsSchT_EPActionEventType Os_[!"$CurrentSchTName"!]_[!"node:name(.)"!]_Events[OS_[!"text:toupper($CurrentSchTName)"!]_[!"text:toupper(node:name(.))"!]_EVENTS] =
{
    [!LOOP "node:order(./OsScheduleTableEventSetting/*,'@index')"!][!//
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        [!"num:i(node:value(node:ref(./OsScheduleTableSetEventRef)/OsEventMask))"!]UL,        /* OsScheduleTableSetEventRef */
        [!"num:i(node:pos(node:ref(./OsScheduleTableSetEventTaskRef)))"!]UL        /* OsScheduleTableSetEventTaskRef */
        [!ENDINDENT!][!//
    }[!IF "not(node:islast())"!],[!ENDIF!]
    [!ENDINDENT!][!//
    [!ENDLOOP!][!//
};

            [!ENDIF!][!//
static const OsSchT_ExPoConfigType Os_[!"$CurrentSchTName"!]_[!"node:name(.)"!] =
{
    [!INDENT "4"!][!//
    [!"num:i(OsScheduleTblExpPointOffset)"!]UL,       /* OsScheduleTableExpPointOffset */
    OS_[!"text:toupper($CurrentSchTName)"!]_[!"text:toupper(node:name(.))"!]_TASKS,        /* TaskCount */
    [!IF "count(./OsScheduleTableTaskActivation/*) > 0"!][!//
    &Os_[!"$CurrentSchTName"!]_[!"node:name(.)"!]_Tasks[0],        /* OsScheduleTableActivateTaskRef */
    [!ELSE!][!//
    NULL_PTR,       /* OsScheduleTableActivateTaskRef */
    [!ENDIF!][!//
    OS_[!"text:toupper($CurrentSchTName)"!]_[!"text:toupper(node:name(.))"!]_EVENTS,        /* EventCount */
    [!IF "count(./OsScheduleTableEventSetting/*) > 0"!][!//
    &Os_[!"$CurrentSchTName"!]_[!"node:name(.)"!]_Events[0],        /* OsScheduleTableSetEventRef */
    [!ELSE!][!//
    NULL_PTR,       /* OsScheduleTableSetEventRef */
    [!ENDIF!][!//
    {
        [!INDENT "8"!][!//
        ((TickType)[!"num:i(OsScheduleTableMaxLengthen)"!]UL),        /* OsScheduleTableMaxLengthen */
        ((TickType)[!"num:i(OsScheduleTableMaxShorten)"!]UL)        /* OsScheduleTableMaxShorten */
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};

        [!ENDLOOP!][!//
static const OsSchT_ExPoConfigRefType Os_[!"$CurrentSchTName"!]_EPRefs[OS_[!"text:toupper($CurrentSchTName)"!]_EP_COUNT] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(node:ref(.)/OsScheduleTableExpiryPoint/*,'@index')"!][!//
        (OsSchT_ExPoConfigRefType)&Os_[!"$CurrentSchTName"!]_[!"node:name(.)"!][!IF "not(node:islast())"!],[!ENDIF!]
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};

static const OsSchT_ConfigType Os_SchT_[!"$CurrentSchTName"!]_Config =
{
    [!INDENT "4"!][!//
    &Os_[!"node:name(node:ref(.))"!]_RunningData,     /* Dyn */
    ((uint64)[!"num:i(node:ref(.)/OsScheduleTableDuration)"!]),        /* OsScheduleTableDuration */
    [!"text:toupper(node:ref(.)/OsScheduleTableRepeating)"!],       /* OsScheduleTableRepeating */
    [!"num:i($SchTObjectID)"!]UL,      /* ObjectID */
    [!VAR "SchTObjectID" = "$SchTObjectID + 1"!][!//
    [!"num:i(node:pos(node:ref(node:ref(.)/OsScheduleTableCounterRef)))"!]UL,       /* CounterID */
    [!"node:ref(.)/@index"!]UL,     /* SchTID */
    /* OsScheduleTableAutostart */
    {
        [!INDENT "8"!][!//
        [!IF "count(node:ref(.)/OsScheduleTableAutostart/*) = 0"!][!//
        SCHEDULTTABLE_AUTOSTART_NONE,       /* OsScheduleTableAutostartType */
        0ULL,           /* OsScheduleTableStartValue */
        0UL             /* OsScheduleTableAppModeRef */
        [!ELSE!][!//
            [!LOOP "node:order(node:ref(.)/OsScheduleTableAutostart/*,'@index')"!][!//
        SCHEDULTTABLE_AUTOSTART_[!"text:toupper(OsScheduleTableAutostartType)"!],       /* OsScheduleTableAutostartType */
        [!"num:i(OsScheduleTableStartValue)"!]ULL,       /* OsScheduleTableStartValue */
                [!LOOP "node:order(./OsScheduleTableAppModeRef/*,'@index')"!][!//
        [!"node:name(node:ref(.))"!] [!//
                    [!IF "not(node:islast())"!][!//
                    | [!//
                    [!ELSE!]        /* OsScheduleTableAppModeRef */
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
        [!ENDINDENT!][!//
    },
    OS_[!"text:toupper($CurrentSchTName)"!]_EP_COUNT,       /* EPCount */
    Os_[!"$CurrentSchTName"!]_EPRefs,       /* OsSchT_ExPoConfigRefType */
    /* OsScheduleTableSync */
    {
        [!INDENT "8"!][!//
            [!"num:i(node:ref(.)/OsScheduleTblExplicitPrecision)"!],        /* OsScheduleTblExplicitPrecision */
            SCHEDULTTABLE_SYNC_[!"node:ref(.)/OsScheduleTblSyncStrategy"!]      /* OsScheduleTblSyncStrategy */
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};

    [!ENDLOOP!][!//
    [!VAR "AppID"="num:i(./@index)"!][!//
    [!VAR "IocCbkObjectIDCount"="0"!][!//
    [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$AppID","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
    [!VAR "HookObjectIDCount"="0"!][!//
    [!CALL "Os_Calculate_Hook_ObjectCount", "AppID"= "$AppID","HookObjectIDCount" ="$HookObjectIDCount"!][!//
    [!VAR "CurrentAppObjectCnt" = "num:i($CurrentAppObjectCnt + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*) + count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*) + num:i($HookObjectIDCount) + num:i($IocCbkObjectIDCount))"!][!//
    [!VAR "SchTObjectID" = "$CurrentAppObjectCnt"!][!//
[!IF "num:i(count(./OsAppScheduleTableRef/*)) != '0'"!][!//
#define OS_STOP_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"

[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
#define OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"

CONSTP2CONST(OsSchT_ConfigType, AUTOMATIC, OS_CONST) Os_SchTConfigSet[OS_SCHT_TOTAL_NUM] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(./OsScheduleTable/*,'@index')"!][!//
        [!VAR "CurrentSchTName" = "node:name(.)"!][!//
    &Os_SchT_[!"$CurrentSchTName"!]_Config[!IF "not(node:islast())"!],[!ENDIF!]
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};

#define OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/





