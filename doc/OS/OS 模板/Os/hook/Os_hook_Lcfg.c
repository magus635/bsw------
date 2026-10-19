/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_hook_Lcfg.c
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
#include "Os_hook_types.h"
#include "Os_hook_Lcfg.h"
#include "Os_hook.h"
#include "Os_hook_Cfg.h"
#include "Os_GeneralTypes.h"
#include "common.h"
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

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
[!VAR "CurrentAppObjectCnt"="0"!][!//
[!VAR "HookObjectID" = "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
        [!VAR "HookObjectID" = "num:i($HookObjectID + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*)) + count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*)"!][!//
            /* AppID [!"./@index"!]*/
            [!IF "node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) != node:name(.)"!][!//
                [!IF "(node:exists(./OsApplicationHooks/OsAppErrorHook)) and (node:value(./OsApplicationHooks/OsAppErrorHook) = 'true')"!][!//
                    static const Os_HookConstType ErrorHookConfig_[!"node:name(.)"!] =
                    {
                        [!INDENT "4"!][!//
                        [!"num:i($HookObjectID)"!]U,               /* ObjectID */
                        [!VAR "HookObjectID" = "$HookObjectID + 1"!][!//
                        ERRORHOOK,         /* HookName */
                        [!ENDINDENT!][!//
                    };

                [!ENDIF!][!//
                [!IF "(node:exists(./OsApplicationHooks/OsAppStartupHook)) and (node:value(./OsApplicationHooks/OsAppStartupHook) = 'true')"!][!//
                    static const Os_HookConstType StartupHookConfig_[!"node:name(.)"!] =
                    {
                        [!INDENT "4"!][!//
                        [!"num:i($HookObjectID)"!]U,         /* ObjectID */
                        [!VAR "HookObjectID" = "$HookObjectID + 1"!][!//
                        STARTUPHOOK,         /* HookName */
                        [!ENDINDENT!][!//
                    };

                [!ENDIF!][!//
                [!IF "(node:exists(./OsApplicationHooks/OsAppShutdownHook)) and (node:value(./OsApplicationHooks/OsAppShutdownHook) = 'true')"!][!//
                    static const Os_HookConstType ShutdownHookConfig_[!"node:name(.)"!] =
                    {
                        [!INDENT "4"!][!//
                        [!"num:i($HookObjectID)"!]U,         /* ObjectID */
                        [!VAR "HookObjectID" = "$HookObjectID + 1"!][!//
                        SHUTDOWNHOOK,         /* HookName */                      
                        [!ENDINDENT!][!//
                    };

                [!ENDIF!][!//
            [!ELSE!][!//
                [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsErrorHook) = 'true'"!][!//
                    static const Os_HookConstType ErrorHookConfig_Core[!"node:value(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!] =
                    {
                        [!INDENT "4"!][!//
                        [!"num:i($HookObjectID)"!]U,         /* ObjectID */
                        [!VAR "HookObjectID" = "$HookObjectID + 1"!][!//
                        ERRORHOOK,         /* HookName */
                        [!ENDINDENT!][!//
                    };

                [!ENDIF!][!//
                [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsStartupHook) = 'true'"!][!//
                    static const Os_HookConstType StartupHookConfig_Core[!"node:value(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!] =
                    {
                        [!INDENT "4"!][!//
                        [!"num:i($HookObjectID)"!]U,         /* ObjectID */
                        [!VAR "HookObjectID" = "$HookObjectID + 1"!][!//
                        STARTUPHOOK,         /* HookName */
                        [!ENDINDENT!][!//
                    };

                [!ENDIF!][!//
                [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsShutdownHook) = 'true'"!][!//
                    static const Os_HookConstType ShutdownHookConfig_Core[!"node:value(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!] =
                    {
                        [!INDENT "4"!][!//
                        [!"num:i($HookObjectID)"!]U,         /* ObjectID */
                        [!VAR "HookObjectID" = "$HookObjectID + 1"!][!//
                        SHUTDOWNHOOK,         /* HookName */
                        [!ENDINDENT!][!//
                    };

                [!ENDIF!][!//
                [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsProtectionHook) = 'true'"!][!//
                    static const Os_HookConstType ProtectionHookConfig_Core[!"node:value(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!] =
                    {
                        [!INDENT "4"!][!//
                        [!"num:i($HookObjectID)"!]U,                /* ObjectID */
                        [!VAR "HookObjectID" = "$HookObjectID + 1"!][!//
                        PROTECTIONHOOK,         /* HookName */
                        [!ENDINDENT!][!//
                    };

                [!ENDIF!][!//
                const Os_CoreHooksType Os_Core[!"node:value(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]Hooks =
                {
                    [!INDENT "4"!][!//
                    [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsStartupHook) = 'true'"!][!//
                        &StartupHookConfig_Core[!"node:value(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!],    /* StartupHookConfigType */
                    [!ELSE!][!//
                        NULL_PTR,               /* StartupHookConfigType */
                    [!ENDIF!][!//
                    [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsShutdownHook) = 'true'"!][!//
                        &ShutdownHookConfig_Core[!"node:value(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!],    /* ShutdownHookConfigType */
                    [!ELSE!][!//
                        NULL_PTR,                /* ShutdownHookConfigType */
                    [!ENDIF!][!//
                    [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsErrorHook) = 'true'"!][!//
                        &ErrorHookConfig_Core[!"node:value(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!],        /* ErrorHookConfigType */
                    [!ELSE!][!//
                        NULL_PTR,             /* ErrorHookConfigType */
                    [!ENDIF!][!//
                    [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsProtectionHook) = 'true'"!][!//
                        &ProtectionHookConfig_Core[!"node:value(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]    /* ProtectionHookConfigType */
                    [!ELSE!][!//
                        NULL_PTR,             /* ProtectionHookConfigType */
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                };    

            [!ENDIF!][!//
            [!IF "node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) = node:name(.)"!][!//
                static const Os_AppHooksType Os_App[!"./@index"!]Hooks =
                {
                    [!INDENT "4"!][!//
                    NULL_PTR,    /* AppStartupHook */
                    NULL_PTR,    /* AppShutdownHook */
                    NULL_PTR     /* AppErrorHook */
                    [!ENDINDENT!][!//
                };

            [!ELSE!][!//
                static const Os_AppHooksType Os_App[!"./@index"!]Hooks =
                {
                    [!INDENT "4"!][!//
                    [!IF "(node:exists(./OsApplicationHooks/OsAppStartupHook)) and (node:value(./OsApplicationHooks/OsAppStartupHook) = 'true')"!][!//
                        &StartupHookConfig_[!"node:name(.)"!],    /* AppStartupHook */
                    [!ELSE!][!//
                        NULL_PTR,    /* AppStartupHook */
                    [!ENDIF!][!//
                    [!IF "(node:exists(./OsApplicationHooks/OsAppShutdownHook)) and (node:value(./OsApplicationHooks/OsAppShutdownHook) = 'true')"!][!//
                        &ShutdownHookConfig_[!"node:name(.)"!],     /* AppShutdownHook */
                    [!ELSE!][!//
                        NULL_PTR,    /* AppShutdownHook */
                    [!ENDIF!][!//
                    [!IF "(node:exists(./OsApplicationHooks/OsAppErrorHook)) and (node:value(./OsApplicationHooks/OsAppErrorHook) = 'true')"!][!//
                        &ErrorHookConfig_[!"node:name(.)"!],     /* AppErrorHook */
                    [!ELSE!][!//
                        NULL_PTR    /* AppErrorHook */
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                };

            [!ENDIF!][!//
    [!VAR "AppID"="num:i(./@index)"!][!//
    [!VAR "IocCbkObjectIDCount"="0"!][!//
    [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$AppID","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
    [!VAR "HookObjectIDCount"="0"!][!//
    [!CALL "Os_Calculate_Hook_ObjectCount", "AppID"= "$AppID","HookObjectIDCount" ="$HookObjectIDCount"!][!//
    [!VAR "CurrentAppObjectCnt" = "num:i($CurrentAppObjectCnt + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*) + count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*) + num:i($HookObjectIDCount) + num:i($IocCbkObjectIDCount))"!][!//
    [!VAR "HookObjectID" = "$CurrentAppObjectCnt"!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/* Overall App Hooks */
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
    const Os_AppHooksConfigType Os_AppHooksConfigSet =
    {
        [!INDENT "4"!][!//
        {
            [!INDENT "8"!][!//
            [!LOOP "node:order(./*,'@index')"!][!//
                &Os_App[!"./@index"!]Hooks,
            [!ENDLOOP!][!//
                NULL_PTR
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    };
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
