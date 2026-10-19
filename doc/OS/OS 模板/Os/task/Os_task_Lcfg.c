/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_task_Lcfg.c
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
[!VAR "CurrentTaskID"="0"!][!//
[!VAR "TaskObjectID"="0"!][!//
[!VAR "FindTaskIDFlag"="'false'"!][!//
[!VAR "Separator" = "','"!][!//
[!ENDNOCODE!][!//
[!//
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_task_types.h"
#include "Os_task_Lcfg.h"
#include "Os_task.h"
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
    [!LOOP "node:order(./OsCoreIdMappingConfig/*,'@index')"!][!//
        [!VAR "CurrentCoreID" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
        [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
            [!IF "$CurrentCoreID = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                [!IF "node:value(./OsTrusted) = 'true'"!][!//
        #define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h" 
                    [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                        static Os_TaskDynamicType [!"node:name(node:ref(.))"!]_RunningData;
                    [!ENDLOOP!][!//
        #define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h"

                [!ELSE!][!//
        #define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h" 
                    [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                        static Os_TaskDynamicType [!"node:name(node:ref(.))"!]_RunningData;
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
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!VAR "CurrentAppObjectCnt"="0"!][!//
[!VAR "TaskObjectID" = "0"!][!//
[!VAR "CoreID" = "0"!][!//
[!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCoreIdMappingConfig/*, '@index')"!][!//
    [!VAR "CoreID" = "@index"!][!//
    [!VAR "PriorityCountList" = "''"!][!//
    [!VAR "EveryPriorityCountList" = "''"!][!//
    [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
        [!IF "$CoreID = node:ref(./OsApplicationCoreRef)/@index"!][!//
            [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                [!VAR "EveryPriorityCountList" = "concat($EveryPriorityCountList, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!VAR "PriorityIncludecomma" = "concat($Separator, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!IF "contains($PriorityCountList, $PriorityIncludecomma)"!][!//
                [!ELSE!][!//
                    [!VAR "PriorityCountList" = "concat($PriorityCountList, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!VAR "Total_Priority" = "num:i(count(text:split($PriorityCountList, $Separator)))"!][!//
    [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication/*,'@index')"!][!//
        [!IF "$CoreID = num:i(node:ref(./OsApplicationCoreRef)/@index)"!][!//
        [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
            static const Os_TaskConstType Task_[!"node:name(node:ref(.))"!]_ConfigRef =
            {
                [!INDENT "4"!][!//
                [!"num:i($TaskObjectID)"!]UL,        /* ObjectID */
                [!VAR "TaskObjectID" = "$TaskObjectID + 1"!][!//
                [!FOR "i" = "0" TO "$Total_Priority - 1"!][!//
                    [!IF "num:order(text:split($PriorityCountList, $Separator))[position() = $i+1] = node:ref(.)/OsTaskPriority"!][!//
                        [!"$i"!]UL,        /* HomePriority */
                        [!IF "node:ref(.)/OsTaskSchedule = 'FULL'"!][!//
                        [!"$i"!]UL,        /* RunningPriority */
                        [!ELSE!][!//
                        0xFFFFFFFFUL,   /* RunningPriority */
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDFOR!][!//
                [!IF "node:ref(.)/OsTaskUseAutostart = 'true'"!][!//
                    [!VAR "AllAppMode" = "''"!][!//
                    [!LOOP "node:order(node:ref(.)/OsTaskAutostartAppModeRef/*,'@index')"!][!//
                        [!IF "num:i(@index) = 0"!][!//
                            [!VAR "AllAppMode" = "node:name(node:ref(.))"!][!//
                        [!ELSE!][!//
                            [!VAR "AllAppMode" = "concat($AllAppMode, '|', node:name(node:ref(.)))"!][!//
                        [!ENDIF!][!//
                    [!ENDLOOP!][!//
                    [!"$AllAppMode"!],       /* AutoStart */
                    [!ELSE!][!//
                    0UL,       /* AutoStart */
                [!ENDIF!][!//
                [!"node:ref(.)/OsTaskActivation"!],        /* MaxActivationCount */
                [!IF "node:ref(.)/OsTaskType = 'BASIC'"!][!//
                FALSE,        /* IsExtended */
                [!ELSE!][!//
                TRUE,        /* IsExtended */
                [!ENDIF!][!//
                &[!"node:name(node:ref(.))"!]_RunningData
                [!ENDINDENT!][!//
            };

        [!ENDLOOP!][!//
        [!VAR "AppID"="num:i(./@index)"!][!//
        [!VAR "IocCbkObjectIDCount"="0"!][!//
        [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$AppID","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
        [!VAR "HookObjectIDCount"="0"!][!//
        [!CALL "Os_Calculate_Hook_ObjectCount", "AppID"= "$AppID","HookObjectIDCount" ="$HookObjectIDCount"!][!//
        [!VAR "CurrentAppObjectCnt" = "num:i($CurrentAppObjectCnt + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*) + count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*) + num:i($HookObjectIDCount) + num:i($IocCbkObjectIDCount))"!][!//
        [!VAR "TaskObjectID" = "$CurrentAppObjectCnt"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

const Os_TaskConfigType Os_TaskConfigSet =
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsTask"!][!//
        [!VAR "TaskNumber" = "num:i(count(./*)) - 1"!][!//
            [!LOOP "node:order(./*,'@index')"!][!//
                    &Task_[!"node:name(.)"!]_ConfigRef,
            [!ENDLOOP!][!//
        [!ENDSELECT!][!//
        NULL_PTR
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};

[!VAR "IdleTaskExistsFlag" = "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCoreIdMappingConfig"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
        [!VAR "CoreID" = "node:value(node:ref(./OsCoreId)/EcucCoreId)"!][!//
        [!VAR "IdleTaskString" = "concat('Idle_Task_Core',$CoreID)"!][!//
        [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsTask"!][!//
            [!LOOP "node:order(./*,'@index')"!][!//
                [!IF "$IdleTaskString = node:name(.)"!][!//
                    [!VAR "IdleTaskExistsFlag" = "1"!][!//
                [!ELSE!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
            [!IF "$IdleTaskExistsFlag = 0"!][!//
                [!ERROR!][!//
                    ERROR:The [!"$IdleTaskString"!] need to be configure since Core[!"$CoreID"!] need Idle Task.
                [!ENDERROR!][!//
            [!ENDIF!][!//
        [!ENDSELECT!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
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
