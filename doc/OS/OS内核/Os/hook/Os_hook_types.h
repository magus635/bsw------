/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_hook_types.h
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
#ifndef OS_HOOK_TYPES_H_
#define OS_HOOK_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Os_GeneralTypes.h"
#include "Os_application_Cfg.h"
#include "Os_kernel_Cfg.h"
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
#define PRO_MAXCOUNT            (5U)
/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    PRO_IGNORE = 0U,
    PRO_TERMINATETASKISR,
    PRO_TERMINATEAPPL,
    PRO_TERMINATEAPPL_RESTART,
    PRO_SHUTDOWN
}ProtectionReturnType;

typedef enum
{
    STARTUPHOOK = 1U,
    ERRORHOOK = 2U,
    PROTECTIONHOOK = 4U,
    SHUTDOWNHOOK = 8U
} HookType;

typedef enum
{
    TASKSCHEDULING = 0U,
    TOCALLEROBJECT
} HookReturnType;

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/
typedef void* InputParaType;
/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/

typedef struct
{
    uint32 ObjectID;
    HookType HookName;
}Os_HookConstType;
typedef struct
{
    Os_ServiceType ServiceID;
    InputParaType InputParameter[4];
}Os_HookErrorDetail;

typedef struct
{
    boolean PreTaskHookIndication;
    boolean PostTaskHookIndication;
    uint32 RunningHookMask;
    Os_HookErrorDetail ErrorDetailInfo;
    ProtectionReturnType ProtectionReaction;
}Os_HookDynamicType;

typedef struct
{
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) StartupHookConfigType;
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) ShutdownHookConfigType;
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) ErrorHookConfigType;
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) ProtectionHookConfigType;
}Os_CoreHooksType;

typedef struct
{
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) AppStartupHookConfigType;
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) AppShutdownHookConfigType;
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) AppErrorHookConfigType;
}Os_AppHooksType;

typedef struct
{
    P2CONST(Os_AppHooksType, TYPEDEF, OS_CONST) AppHooks[OS_APPLICATION_TOTAL_NUM + 1];
}Os_AppHooksConfigType;

#endif /* OS_HOOK_TYPES_H_ */
/****************************************************************************************************
**     End of File: Os_hook_types.h                                                                **
****************************************************************************************************/

