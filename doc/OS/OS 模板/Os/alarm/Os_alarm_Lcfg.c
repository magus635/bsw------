/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_alarm_Lcfg.c
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
[!//
[!NOCODE!][!//
[!INCLUDE "Os_AppCommon.m"!][!//
[!ENDNOCODE!][!//
[!//
#include "Os_alarm_Lcfg.h"
#include "Os_alarm.h"
#include "Os_counter_Cfg.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Type Definitions                                                **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!LOOP "node:order(./OsCoreIdMappingConfig/*,'@index')"!][!//
        [!VAR "CurrentCoreID" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
        [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
            [!IF "$CurrentCoreID = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                [!IF "node:value(./OsTrusted) = 'true'"!][!//
        #define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h"
                    [!LOOP "node:order(./OsAppAlarmRef/*,'@index')"!][!//
                        static Os_AlarmDynamicType [!"node:name(node:ref(.))"!]_RunningData;
                    [!ENDLOOP!][!//
        #define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h"

                [!ELSE!][!//
        #define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h" 
                    [!LOOP "node:order(./OsAppAlarmRef/*,'@index')"!][!//
                        static Os_AlarmDynamicType [!"node:name(node:ref(.))"!]_RunningData;
                    [!ENDLOOP!][!//
        #define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h"
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Private Structure Definitions                                           **
****************************************************************************************************/
[!VAR "AllAlarmInApp" = "','"!][!//
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!VAR "CurrentAppObjectCnt"="0"!][!//
[!VAR "AlarmObjectID" = "0"!][!//

[!LOOP "node:order(./OsApplication/*,'@index')"!][!//
    [!VAR "AlarmCoreID" = "node:name(node:ref(./OsApplicationCoreRef))"!][!//
    [!VAR "AlarmObjectID" = "num:i($AlarmObjectID + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*))"!][!//
    [!LOOP "node:order(./OsAppAlarmRef/*,'@index')"!][!//
        [!VAR "AlarmRefCounter" = "node:name(node:ref(node:ref(.)/OsAlarmCounterRef))"!][!//
        [!VAR "AlarmName" = "node:name(node:ref(.))"!][!//
        [!IF "contains($AllAlarmInApp, concat(',', node:name(node:ref(.)), ','))"!][!//
            [!ERROR!][!//
                ERROR:The [!"node:name(node:ref(.))"!] Alarm is multi referenced in [!"node:name(./../..)"!].
            [!ENDERROR!][!//
        [!ENDIF!][!//
        [!VAR "AllAlarmInApp" = "concat($AllAlarmInApp, node:name(node:ref(.)), ',')"!][!//
        const Os_AlarmConstType Alarm_[!"node:name(node:ref(.))"!]_ConfigRef =
        {
        [!INDENT "4"!][!//
        [!"num:i($AlarmObjectID)"!]UL,                                   /* ObjectID */
        [!VAR "AlarmObjectID" = "$AlarmObjectID + 1"!][!//
        [!VAR "alarmAction" = "node:ref(.)/OsAlarmAction"!][!//
        [!IF "$alarmAction = 'OsAlarmActivateTask'"!][!//
        ALARM_ACTIVATETASK,      /* AlarmActionType */
        {
            [!INDENT "8"!][!//
            [!"text:toupper(node:name(node:ref(node:ref(.)/OsAlarmAction/OsAlarmActivateTaskRef)))"!],           /* TaskID */
            0,                    /* EventMask */
            INVALID_COUNTER,           /* CounterID */
            NULL_PTR            /* AlarmCallback */ 
            [!ENDINDENT!][!//
        [!ELSEIF "$alarmAction = 'OsAlarmSetEvent'"!][!//
        ALARM_SETEVENT,          /* AlarmActionType */
        {
            [!INDENT "8"!][!//
            [!"text:toupper(node:name(node:ref(node:ref(.)/OsAlarmAction/OsAlarmSetEventTaskRef)))"!],              /* TaskID */
            [!"text:toupper(node:name(node:ref(node:ref(.)/OsAlarmAction/OsAlarmSetEventRef)))"!],          /* EventMask */
            INVALID_COUNTER,           /* CounterID */
            NULL_PTR            /* AlarmCallback */ 
            [!ENDINDENT!][!//
        [!ELSEIF "$alarmAction = 'OsAlarmIncrementCounter'"!][!//
        ALARM_INCREMENTCOUNTER,  /* AlarmActionType */
        {
            [!INDENT "8"!][!//
            INVALID_TASK,        /* TaskID */
            0,                    /* EventMask */
            [!"text:toupper(node:name(node:ref(node:ref(.)/OsAlarmAction/OsAlarmIncrementCounterRef)))"!],               /* CounterID */
            [!VAR "AlarmIncrementCounter" = "node:name(node:ref(node:ref(.)/OsAlarmAction/OsAlarmIncrementCounterRef))"!][!//
            [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication/*,'@index')"!][!//
                [!LOOP "node:order(./OsAppCounterRef/*,'@index')"!][!//
                    [!IF "$AlarmIncrementCounter = node:name(node:ref(.))"!][!//
                        [!IF "$AlarmCoreID != node:name(node:ref(./../../OsApplicationCoreRef))"!][!//
                            [!ERROR!][!//
                                ERROR:The [!"$AlarmName"!] Alarm and Increment [!"$AlarmRefCounter"!] do not belong to the same core.
                            [!ENDERROR!][!//
                        [!ENDIF!][!//            
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
            NULL_PTR            /* AlarmCallback */ 
            [!ENDINDENT!][!//
        [!ELSEIF "$alarmAction = 'OsAlarmCallback'"!][!//
        ALARM_CALLBACK,          /* AlarmActionType */
        {
            [!INDENT "8"!][!//
            INVALID_TASK,        /* TaskID */
            0,                    /* EventMask */
            INVALID_COUNTER,           /* CounterID */ 
            [!"node:ref(.)/OsAlarmAction/OsAlarmCallbackName"!],               /* AlarmCallback */
            [!ENDINDENT!][!//
        [!ENDIF!][!//
        },                       /* AlarmActionInfo */
        {
            [!INDENT "8"!][!//
            [!IF "node:ref(.)/OsAlarmUseAutostart = 'true'"!][!//
                [!VAR "AllAppMode" = "''"!][!//
                [!LOOP "node:order(node:ref(.)/OsAlarmAutostartAppModeRef/*,'@index')"!][!//
                    [!IF "num:i(@index) = 0"!][!//
                        [!VAR "AllAppMode" = "node:name(node:ref(.))"!][!//
                    [!ELSE!][!//
                        [!VAR "AllAppMode" = "concat($AllAppMode, '|', node:name(node:ref(.)))"!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!"$AllAppMode"!],              /* AutoStart */
                [!IF "'RELATIVE' = node:ref(.)/OsAlarmAutostart/OsAlarmAutostartType"!][!//
                    ALARM_REL,           /* ActivationType */
                [!ELSE!][!//
                    ALARM_ABS,           /* ActivationType */
                [!ENDIF!][!//
                [!"node:ref(.)/OsAlarmAutostart/OsAlarmAlarmTime"!]UL,                     /* Start */
                [!"node:ref(.)/OsAlarmAutostart/OsAlarmCycleTime"!]UL                      /* Cycle*/
            [!ELSE!][!//
                0UL,              /* AutoStart */
                ALARM_REL,           /* ActivationType */
                0UL,                     /* Start */
                0UL                      /* Cycle*/
            [!ENDIF!][!//
            [!ENDINDENT!][!//
        },                        /* AutoStartInfo */
        &[!"node:name(node:ref(.))"!]_RunningData
        [!ENDINDENT!][!//
        }; 
    [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication/*,'@index')"!][!//
        [!LOOP "node:order(./OsAppCounterRef/*,'@index')"!][!//
            [!IF "$AlarmRefCounter = node:name(node:ref(.))"!][!//
                [!IF "$AlarmCoreID != node:name(node:ref(./../../OsApplicationCoreRef))"!][!//
                    [!ERROR!][!//
                        ERROR:The [!"$AlarmName"!] Alarm and Referenced [!"$AlarmRefCounter"!] do not belong to the same core.
                    [!ENDERROR!][!//
                [!ENDIF!][!//            
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!VAR "AppID"="num:i(./@index)"!][!//
    [!VAR "IocCbkObjectIDCount"="0"!][!//
    [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$AppID","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
    [!VAR "HookObjectIDCount"="0"!][!//
    [!CALL "Os_Calculate_Hook_ObjectCount", "AppID"= "$AppID","HookObjectIDCount" ="$HookObjectIDCount"!][!//
    [!VAR "CurrentAppObjectCnt" = "num:i($CurrentAppObjectCnt + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*) + count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*) + num:i($HookObjectIDCount) + num:i($IocCbkObjectIDCount))"!][!//
    [!VAR "AlarmObjectID" = "$CurrentAppObjectCnt"!][!//

[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
const Os_AlarmConfigType Os_AlarmConfigSet =
{
    {
        [!INDENT "8"!][!//
        [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsAlarm"!][!//
            [!VAR "AlarmNumber" = "num:i(count(./*)) - 1"!][!//
            [!LOOP "node:order(./*,'@index')"!][!//
                [!VAR "AlarmName" = "concat(',',node:name(.),',')"!][!//
                [!IF "contains($AllAlarmInApp, $AlarmName)"!][!//
                [!ELSE!][!//
                    [!ERROR!][!//
                        ERROR:The [!"node:name(.)"!] Alarm is not referenced in any application.
                    [!ENDERROR!][!//
                [!ENDIF!][!//
                    &Alarm_[!"node:name(.)"!]_ConfigRef,
            [!ENDLOOP!][!//
        [!ENDSELECT!][!//
        NULL_PTR
        [!ENDINDENT!][!//
    }
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





