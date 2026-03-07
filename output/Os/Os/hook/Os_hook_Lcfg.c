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
*   Genaration Time       : 2026-03-05 20:16:08
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
/* AppID 0*/
static const Os_HookConstType ErrorHookConfig_Core0 =
{
    26U,         /* ObjectID */
    ERRORHOOK,         /* HookName */
};

static const Os_HookConstType StartupHookConfig_Core0 =
{
    27U,         /* ObjectID */
    STARTUPHOOK,         /* HookName */
};

static const Os_HookConstType ProtectionHookConfig_Core0 =
{
    28U,                /* ObjectID */
    PROTECTIONHOOK,         /* HookName */
};

const Os_CoreHooksType Os_Core0Hooks =
{
    &StartupHookConfig_Core0,    /* StartupHookConfigType */
    NULL_PTR,                /* ShutdownHookConfigType */
    &ErrorHookConfig_Core0,        /* ErrorHookConfigType */
    &ProtectionHookConfig_Core0    /* ProtectionHookConfigType */
};    

static const Os_AppHooksType Os_App0Hooks =
{
    NULL_PTR,    /* AppStartupHook */
    NULL_PTR,    /* AppShutdownHook */
    NULL_PTR     /* AppErrorHook */
};

/* AppID 1*/
static const Os_AppHooksType Os_App1Hooks =
{
    NULL_PTR,    /* AppStartupHook */
    NULL_PTR,    /* AppShutdownHook */
    NULL_PTR    /* AppErrorHook */
};

/* AppID 2*/
static const Os_AppHooksType Os_App2Hooks =
{
    NULL_PTR,    /* AppStartupHook */
    NULL_PTR,    /* AppShutdownHook */
    NULL_PTR    /* AppErrorHook */
};

/* AppID 3*/
static const Os_HookConstType ErrorHookConfig_Core1 =
{
    57U,         /* ObjectID */
    ERRORHOOK,         /* HookName */
};

static const Os_HookConstType StartupHookConfig_Core1 =
{
    58U,         /* ObjectID */
    STARTUPHOOK,         /* HookName */
};

static const Os_HookConstType ProtectionHookConfig_Core1 =
{
    59U,                /* ObjectID */
    PROTECTIONHOOK,         /* HookName */
};

const Os_CoreHooksType Os_Core1Hooks =
{
    &StartupHookConfig_Core1,    /* StartupHookConfigType */
    NULL_PTR,                /* ShutdownHookConfigType */
    &ErrorHookConfig_Core1,        /* ErrorHookConfigType */
    &ProtectionHookConfig_Core1    /* ProtectionHookConfigType */
};    

static const Os_AppHooksType Os_App3Hooks =
{
    NULL_PTR,    /* AppStartupHook */
    NULL_PTR,    /* AppShutdownHook */
    NULL_PTR     /* AppErrorHook */
};

/* Overall App Hooks */
const Os_AppHooksConfigType Os_AppHooksConfigSet =
{
    {
        &Os_App0Hooks,
        &Os_App1Hooks,
        &Os_App2Hooks,
        &Os_App3Hooks,
        NULL_PTR
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
