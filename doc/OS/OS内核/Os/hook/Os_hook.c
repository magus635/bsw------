/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_hook.c
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

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_hook.h"
#include "Os_GeneralTypes.h"
#include "Os_hook_Lcfg.h"
#include "Os_kernel.h"
#include "Os_context.h"
#include "Os_application.h"
#include "Os_isr.h"
#include "Os_task.h"
#include "Os_hook_Cfg.h"
#include "Os_orti.h"
#include "Os_ArtiHooks.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
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

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : OsHook_Internal_CallHook
*   Service ID              : None.
*   Description             : Internal Call Hook Function.
*   Parameters in           : Os_HookConPtr:
*                           : Error:
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsHook_Internal_CallHook
(
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) Os_HookConPtr,
    StatusType Error
);

/****************************************************************************************************
*   Function Name           : OsHook_Internel_VerifyProtectionReaction
*   Service ID              : None.
*   Description             : Check if the protection reaction is valid.
*   Parameters in           : ProtectionReaction:
*                           : FatalError:
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(ProtectionReturnType, OS_CODE) OsHook_Internel_VerifyProtectionReaction
(
    ProtectionReturnType ProtectionReaction,
    StatusType FatalError
);

/****************************************************************************************************
*   Function Name           : OsHook_Internal_HandleProtectionReaction
*   Service ID              : None.
*   Description             : Handle the reaction from Protection Hook
*   Parameters in           : ProtectionReaction:
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsHook_Internal_HandleProtectionReaction
(
    ProtectionReturnType ProtectionReaction,
    StatusType FatalError
);

/****************************************************************************************************
*   Function Name           : OsHook_Internal_HookNestedCheck
*   Service ID              : None.
*   Description             : nested hook check
*   Parameters in           : NestedHooks:
*                           : CurrentHook:
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, OS_CODE) OsHook_Internal_HookNestedCheck
(
    uint32 NestedHooks,
    HookType CurrentHook
);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
static FUNC(boolean, OS_CODE) OsHook_Internal_HookNestedCheck
(
    uint32 NestedHooks,
    HookType CurrentHook
)
{
    boolean NestedCheck;
    uint32 HookMaskIndication;
    HookType LastestHookNested;

    NestedCheck = FALSE;
    if (0 != NestedHooks)
    {
        HookMaskIndication = Os_Inf_clz(NestedHooks);
        LastestHookNested = 1 << (31 - HookMaskIndication);
        if(LastestHookNested < CurrentHook)
        {
            NestedCheck = TRUE;
        }
    }
    else
    {
        NestedCheck = TRUE;
    }

    return NestedCheck;
}

#if (OS_ARTI_TRACE_HOOK == STD_ON)
/****************************************************************************************************
*   ARTI hook events (openspec add-arti-hook-tracing, design D5/D7): Start before the switch to the hook
*   object, Return when it is back. An application-specific hook has its own event token, chosen by
*   the application ID in Os_ArtiHooks.h.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsHook_Internal_Arti
(
    HookType Hook,
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) HookObjectInfo,
    uint32 Param,
    boolean Start
)
{
    CoreIdType ArtiCore;
    ApplicationType ArtiApp;
    Os_IsrLevelType ArtiLevel;

    /* Reached from hook calls and from OsHook_Hookreturn: suspend so that the NOSUSP context holds */
    OsIsr_SuspendISR(&ArtiLevel);
    ArtiCore = Os_Inf_GetCoreId();
    if(OBJECT_APPHOOK == HookObjectInfo->ObjectType)
    {
        ArtiApp = (HookObjectInfo->AppObjIDInfo & APPLICATIONID_MASK) >> 16u;
        switch(Hook)
        {
            case ERRORHOOK:
                if(TRUE == Start) { OS_ARTI_APPHOOK_ERRORHOOK_START(ArtiCore, ArtiApp, Param); }
                else { OS_ARTI_APPHOOK_ERRORHOOK_RETURN(ArtiCore, ArtiApp, Param); }
                break;
            case STARTUPHOOK:
                if(TRUE == Start) { OS_ARTI_APPHOOK_STARTUPHOOK_START(ArtiCore, ArtiApp, Param); }
                else { OS_ARTI_APPHOOK_STARTUPHOOK_RETURN(ArtiCore, ArtiApp, Param); }
                break;
            case SHUTDOWNHOOK:
                if(TRUE == Start) { OS_ARTI_APPHOOK_SHUTDOWNHOOK_START(ArtiCore, ArtiApp, Param); }
                else { OS_ARTI_APPHOOK_SHUTDOWNHOOK_RETURN(ArtiCore, ArtiApp, Param); }
                break;
            default:
                break;
        }
        (void)ArtiApp;
    }
    else
    {
        switch(Hook)
        {
            case ERRORHOOK:
                if(TRUE == Start) { OS_ARTI_HOOK_ERRORHOOK_START(ArtiCore, Param); }
                else { OS_ARTI_HOOK_ERRORHOOK_RETURN(ArtiCore, Param); }
                break;
            case STARTUPHOOK:
                if(TRUE == Start) { OS_ARTI_HOOK_STARTUPHOOK_START(ArtiCore, Param); }
                else { OS_ARTI_HOOK_STARTUPHOOK_RETURN(ArtiCore, Param); }
                break;
            case SHUTDOWNHOOK:
                if(TRUE == Start) { OS_ARTI_HOOK_SHUTDOWNHOOK_START(ArtiCore, Param); }
                else { OS_ARTI_HOOK_SHUTDOWNHOOK_RETURN(ArtiCore, Param); }
                break;
            case PROTECTIONHOOK:
                if(TRUE == Start) { OS_ARTI_HOOK_PROTECTIONHOOK_START(ArtiCore, Param); }
                else { OS_ARTI_HOOK_PROTECTIONHOOK_RETURN(ArtiCore, Param); }
                break;
            default:
                break;
        }
    }
    OsIsr_ResumeISR(ArtiLevel);
    (void)ArtiCore;
    (void)Param;
}
#endif

static FUNC(void, OS_CODE) OsHook_Internal_CallHook
(
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) Os_HookConPtr,
    StatusType Error
)
{
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) HookObjectInfo;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) CurrentObjectInfo;
    P2VAR(Os_HookDynamicType, TYPEDEF, OS_VAR) Os_HookDynPtr;

    /* if hook is not configured then end this function */
    if(NULL_PTR != Os_HookConPtr)
    {
        /* Get Hook Dynamic data */
        Os_HookDynPtr = OsKernel_GetCurrentCoreHookDataInfo();
        /* Get current object info */
        CurrentObjectInfo = OsApp_GetCurrent_ObjectInfo();
        /* Get core Error Hook Configuration */
        HookObjectInfo = OsApp_GetSpecific_ObjectInfo(Os_HookConPtr->ObjectID);

        /* Check the Nested Hook Error or hook Config is NULL_PTR */
        if (FALSE == OsHook_Internal_HookNestedCheck(Os_HookDynPtr->RunningHookMask, Os_HookConPtr->HookName))
        {
            /* Code freeze unexpected reason */
            CodeFreeze();
        }
        else
        {
            /*Need to check if ISR2 or Task */
            if(OBJECT_TASK == CurrentObjectInfo->ObjectType)
            {
                /* leave task level */
                OsTask_LeaveTaskLevel();
            }

            Os_HookDynPtr->RunningHookMask |= Os_HookConPtr->HookName;
        }

        /* Change the current App */
        OsApp_ChangeCurrent_AppInfo(Os_HookConPtr->ObjectID);
        /* Init the Hook context before running, set input parameter and make context switch */
        Os_Hal_ContextInit(*(HookObjectInfo->ObjectDataInfo.ObjectContextInfoPtr),
                (*(HookObjectInfo->ObjectDataInfo.ObjectContextInfoPtr))->ContextInfoPtr);
        Os_Hal_ContextSetParam((*(HookObjectInfo->ObjectDataInfo.ObjectContextInfoPtr))->ContextInfoPtr, (void *)((uint32)Error));
#if (OS_ARTI_TRACE_HOOK == STD_ON)
        OsHook_Internal_Arti(Os_HookConPtr->HookName, HookObjectInfo, (uint32)Error, TRUE);
#endif
        Os_Hal_ContextSwitch(HookObjectInfo, CurrentObjectInfo, SAVING_CONTEXT);
    }
}

static FUNC(ProtectionReturnType, OS_CODE) OsHook_Internel_VerifyProtectionReaction
(
    ProtectionReturnType ProtectionReaction,
    StatusType FatalError
)
{
    ApplicationType CurrentAppID;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) CurrentObjectInfo;

    CurrentObjectInfo = OsApp_GetCurrent_ObjectInfo();
    CurrentAppID = OsApp_GetCurrentApplicationID();
    if(ProtectionReaction >= PRO_MAXCOUNT)
    {
        ProtectionReaction = PRO_SHUTDOWN;
    }
    else if((PRO_IGNORE == ProtectionReaction) && (E_OS_PROTECTION_ARRIVAL != FatalError))
    {
        /* [SWS_Os_00106] */
        ProtectionReaction = PRO_SHUTDOWN;
    }
    else if((PRO_IGNORE != ProtectionReaction) && (E_OS_PROTECTION_ARRIVAL == FatalError))
    {
        /* [SWS_Os_00506] */
        ProtectionReaction = PRO_SHUTDOWN;
    }
    else if(((E_OS_PROTECTION_EXCEPTION == FatalError) || (E_OS_PROTECTION_MEMORY == FatalError)) &&
            (TRUE == OsApp_CheckTrustedFunctionIsCalled()))
    {
        /* [SWS_Os_00860] */
        ProtectionReaction = PRO_SHUTDOWN;
    }
    else if((INVALID_TASK == OsApp_GetAppRestartTaskID(CurrentAppID)) && (PRO_TERMINATEAPPL_RESTART == ProtectionReaction))
    {
        /* [SWS_Os_00555] */
        ProtectionReaction = PRO_SHUTDOWN;
    }
    else if((OBJECT_TASK != CurrentObjectInfo->ObjectType) && (OBJECT_ISR != CurrentObjectInfo->ObjectType) && (PRO_TERMINATETASKISR == ProtectionReaction))
    {
        /* [SWS_Os_00243] */
        if(CurrentAppID >= INVALID_OSAPPLICATION)
        {
            ProtectionReaction = PRO_SHUTDOWN;
        }
        else
        {
            ProtectionReaction = PRO_TERMINATEAPPL;
        }
    }
    else if(CurrentAppID == OsKernel_GetCurrentCoreKernelAppID() &&
            ((PRO_TERMINATEAPPL == ProtectionReaction)||(PRO_TERMINATEAPPL_RESTART == ProtectionReaction)))
    {
        ProtectionReaction = PRO_SHUTDOWN;
    }
    else
    {

    }

    return ProtectionReaction;
}

static FUNC(void, OS_CODE) OsHook_Internal_HandleProtectionReaction
(
    ProtectionReturnType ProtectionReaction,
    StatusType FatalError
)
{
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) CurrentObjectInfo;
    uint32 CurrentAppID;

    CurrentAppID = OsApp_GetCurrentApplicationID();
    CurrentObjectInfo = OsApp_GetCurrent_ObjectInfo();

    switch(ProtectionReaction)
    {
        case PRO_IGNORE:                                                                                                    /* COV_OS_HALPLATFORMTPUNSUPPORTED_XX */
          break;

        case PRO_TERMINATETASKISR:
            if(OBJECT_TASK == CurrentObjectInfo->ObjectType)
            {
                OsTask_TaskDeinit((CurrentObjectInfo->AppObjIDInfo) & OBJECTID_MASK);
                OsIsr_ResetIntApiCount(CurrentAppID);
                OsTask_DoScheduling(NOT_SAVING_CONTEXT);
            }
            else if(OBJECT_ISR == CurrentObjectInfo->ObjectType)
            {
                OsIsr_IsrDeInit((CurrentObjectInfo->AppObjIDInfo) & OBJECTID_MASK);
                OsIsr_ResetIntApiCount(CurrentAppID);
                OsIsr_PostISR();
            }
            else
            {
                CodeFreeze();
            }
            break;

        case PRO_TERMINATEAPPL:
            OsApp_TerminateApplication(CurrentAppID, OS_OSAPPLICATION_NO_RESTART);
            break;

        case PRO_TERMINATEAPPL_RESTART:
            OsApp_TerminateApplication(CurrentAppID, OS_OSAPPLICATION_RESTART);
            break;

        case PRO_SHUTDOWN:
            OsKernel_ShutdownAllCores(FatalError);
            break;

        default:
            CodeFreeze();
            break;
    }
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
FUNC(void, OS_CODE) OsHook_CallErrorHook
(
    StatusType Error
)
{
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) Os_CoreHookConPtr;
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) Os_AppHookConPtr;
    uint32 CurrentAppID;

    /* Record the error for ORTI/ARTI before any hook runs, so it is visible even when no
       ErrorHook is configured and inside the ErrorHook itself. */
    OsOrti_SetLastError(Error);

    /* Get Core Error hook structure pointer */
    Os_CoreHookConPtr = OsKernel_GetCurrentCoreHooksInfoPtr()->ErrorHookConfigType;
    /* Get Current ApplicationID */
    CurrentAppID = OsApp_GetCurrentApplicationID();
    /* Get Application Error hook structure pointer */
    Os_AppHookConPtr = Os_AppHooksConfigSet.AppHooks[CurrentAppID]->AppErrorHookConfigType;

    /* Core Error Hook */
    OsHook_Internal_CallHook(Os_CoreHookConPtr, Error);
    /* App Error Hook */
    OsHook_Internal_CallHook(Os_AppHookConPtr, Error);

}

FUNC(void, OS_CODE) OsHook_Hookreturn
(
     void
)
{
    P2VAR(Os_HookDynamicType, TYPEDEF, OS_VAR) Os_HookDynPtr;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) CurrentObjectInfo;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) PreviousObjectInfo;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) PreviousTaskDyn;
    HookType HookType;
    ApplicationType PreviousApplication;
    ProtectionReturnType ProtectionReaction;

    /* Read return value from register R0 */
    Os_Inf_GetFunctionReturnValue(ProtectionReaction);

    /* Get hook dynamic data */
    Os_HookDynPtr = OsKernel_GetCurrentCoreHookDataInfo();
    CurrentObjectInfo = OsApp_GetCurrent_ObjectInfo();
    PreviousObjectInfo = OsApp_GetPrevious_ObjectInfo();

    /* the upper thread is isr or task then schedule again or directly switch to the upper task or ISR*/
    HookType = CurrentObjectInfo->AppObjIDInfo & OBJECTID_MASK;
#if (OS_ARTI_TRACE_HOOK == STD_ON)
    /* The ProtectionHook returns once its reaction is decided (OsHook_CallProtectionHook) */
    if(PROTECTIONHOOK != HookType)
    {
        OsHook_Internal_Arti(HookType, CurrentObjectInfo, 0U, FALSE);
    }
#endif
    if(HookType == PROTECTIONHOOK)
    {
        Os_HookDynPtr->ProtectionReaction = ProtectionReaction;
    }

    Os_HookDynPtr->RunningHookMask &= ~HookType;
    PreviousApplication = (PreviousObjectInfo->AppObjIDInfo & APPLICATIONID_MASK) >> 16u;

    if (PreviousObjectInfo->ObjectType == OBJECT_TASK)
    {
        if(HookType == ERRORHOOK &&
            ((CurrentObjectInfo->ObjectType == OBJECT_APPHOOK)
            || (Os_AppHooksConfigSet.AppHooks[PreviousApplication]->AppErrorHookConfigType == NULL_PTR)))
        {
            OsTask_DoScheduling(NOT_SAVING_CONTEXT);
        }
        PreviousTaskDyn = OsTask_GetTaskDyn(PreviousObjectInfo->AppObjIDInfo & OBJECTID_MASK);
        PreviousTaskDyn->State = RUNNING;
        OsOrti_TaskStart(PreviousObjectInfo->AppObjIDInfo & OBJECTID_MASK);
    }
    /* Change the current Object Info */
    OsApp_ChangeCurrent_AppInfo(PreviousObjectInfo->ObjectIDIndex);
    Os_Hal_ContextSwitch(PreviousObjectInfo, CurrentObjectInfo, NOT_SAVING_CONTEXT);

}

FUNC(void, OS_CODE) OsHook_InitHook
(
    void
)
{
    P2VAR(Os_HookDynamicType, TYPEDEF, OS_VAR) Os_HookDynPtr;
    uint32 NestLength;

    Os_HookDynPtr = OsKernel_GetCurrentCoreHookDataInfo();

    /* Init all hook dynamic data */
    Os_HookDynPtr->ProtectionReaction = 0;
    Os_HookDynPtr->ErrorDetailInfo.ServiceID = 0;
    Os_HookDynPtr->PreTaskHookIndication = 0;
    Os_HookDynPtr->PostTaskHookIndication = 0;
    Os_HookDynPtr->RunningHookMask = 0;
    for(NestLength = 0; NestLength < 4U; NestLength++)
    {
        Os_HookDynPtr->ErrorDetailInfo.InputParameter[NestLength] = 0;
    }
}

FUNC(void, OS_CODE) OsHook_CallProtectionHook
(
    StatusType FatalError
)
{
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) Os_CoreHookConPtr;
    P2VAR(Os_HookDynamicType, TYPEDEF, OS_VAR) Os_HookDynPtr;
    ProtectionReturnType ProtectionReaction;

    Os_HookDynPtr = OsKernel_GetCurrentCoreHookDataInfo();
    Os_CoreHookConPtr = OsKernel_GetCurrentCoreHooksInfoPtr()->ProtectionHookConfigType;

    /* Core Protection Hook */
    if(Os_CoreHookConPtr != NULL_PTR)
    {
        OsHook_Internal_CallHook(Os_CoreHookConPtr, FatalError);
        ProtectionReaction = Os_HookDynPtr->ProtectionReaction;
    }
    else
    {
        /* [SWS_Os_00107] */
        ProtectionReaction = PRO_SHUTDOWN;
    }
    /* Act on the verified reaction; keep it in the hook data (read by ARTI and for diagnosis) */
    ProtectionReaction = OsHook_Internel_VerifyProtectionReaction(ProtectionReaction, FatalError);
    Os_HookDynPtr->ProtectionReaction = ProtectionReaction;
#if (OS_ARTI_TRACE_HOOK == STD_ON)
    if(Os_CoreHookConPtr != NULL_PTR)
    {
        /* SWS OS 7.17.6: after the return value is checked, with the reaction the OS takes */
        OsHook_Internal_Arti(PROTECTIONHOOK, OsApp_GetSpecific_ObjectInfo(Os_CoreHookConPtr->ObjectID),
                             (uint32)Os_HookDynPtr->ProtectionReaction, FALSE);
    }
#endif
    /* Handle protection hook reaction */
    OsHook_Internal_HandleProtectionReaction(ProtectionReaction, FatalError);
}

FUNC(void, OS_CODE) OsHook_CallCoreStartupHook
(
    void
)
{
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) Os_CoreHookConPtr;

    Os_CoreHookConPtr = OsKernel_GetCurrentCoreHooksInfoPtr()->StartupHookConfigType;

    /* Core Startup Hook */
    OsHook_Internal_CallHook(Os_CoreHookConPtr, E_OK);
}

FUNC(void, OS_CODE) OsHook_CallAppStartupHook
(
    uint32 AppID
)
{
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) Os_AppHookConPtr;

    /* Get Current running object */
    Os_AppHookConPtr = Os_AppHooksConfigSet.AppHooks[AppID]->AppStartupHookConfigType;
    /* Core Startup Hook */
    OsHook_Internal_CallHook(Os_AppHookConPtr, E_OK);
}

FUNC(void, OS_CODE) OsHook_CallCoreShutdownHook
(
    StatusType FatalError
)
{
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) Os_CoreHookConPtr;

    Os_CoreHookConPtr = OsKernel_GetCurrentCoreHooksInfoPtr()->ShutdownHookConfigType;

    /* Core Startup Hook */
    OsHook_Internal_CallHook(Os_CoreHookConPtr, FatalError);
}

FUNC(void, OS_CODE) OsHook_CallAppShutdownHook
(
    StatusType FatalError,
    uint32 AppID
)
{
    P2CONST(Os_HookConstType, TYPEDEF, OS_CONST) Os_AppHookConPtr;

    Os_AppHookConPtr = Os_AppHooksConfigSet.AppHooks[AppID]->AppShutdownHookConfigType;
    /* Core Startup Hook */
    OsHook_Internal_CallHook(Os_AppHookConPtr, FatalError);
}

FUNC(void, OS_CODE) OsHook_CallPreTaskHook
(
    void
)
{
    P2VAR(Os_HookDynamicType, TYPEDEF, OS_VAR) Os_HookDynPtr;

    Os_HookDynPtr = OsKernel_GetCurrentCoreHookDataInfo();
    Os_HookDynPtr->PreTaskHookIndication = TRUE;
#if PRETASKHOOK == STD_ON
#if (OS_ARTI_TRACE_HOOK == STD_ON)
    {
        Os_IsrLevelType ArtiLevel;
        CoreIdType ArtiCore = Os_Inf_GetCoreId();
        OsIsr_SuspendISR(&ArtiLevel);
        OS_ARTI_HOOK_PRETASKHOOK_START(ArtiCore, 0U);
        OsIsr_ResumeISR(ArtiLevel);
        PreTaskHook();
        OsIsr_SuspendISR(&ArtiLevel);
        OS_ARTI_HOOK_PRETASKHOOK_RETURN(ArtiCore, 0U);
        OsIsr_ResumeISR(ArtiLevel);
        (void)ArtiCore;
    }
#else
    PreTaskHook();
#endif
#endif
    Os_HookDynPtr->PreTaskHookIndication = FALSE;
}

FUNC(void, OS_CODE) OsHook_CallPostTaskHook
(
    void
)
{
    P2VAR(Os_HookDynamicType, TYPEDEF, OS_VAR) Os_HookDynPtr;

    Os_HookDynPtr = OsKernel_GetCurrentCoreHookDataInfo();
    Os_HookDynPtr->PostTaskHookIndication = TRUE;
#if POSTTASKHOOK == STD_ON
#if (OS_ARTI_TRACE_HOOK == STD_ON)
    {
        Os_IsrLevelType ArtiLevel;
        CoreIdType ArtiCore = Os_Inf_GetCoreId();
        OsIsr_SuspendISR(&ArtiLevel);
        OS_ARTI_HOOK_POSTTASKHOOK_START(ArtiCore, 0U);
        OsIsr_ResumeISR(ArtiLevel);
        PostTaskHook();
        OsIsr_SuspendISR(&ArtiLevel);
        OS_ARTI_HOOK_POSTTASKHOOK_RETURN(ArtiCore, 0U);
        OsIsr_ResumeISR(ArtiLevel);
        (void)ArtiCore;
    }
#else
    PostTaskHook();
#endif
#endif
    Os_HookDynPtr->PostTaskHookIndication = FALSE;
}

FUNC(void, OS_CODE) OsHook_UnHandledException
(
    uint32 ExceptionAddress,
    boolean SupervisorMode
)
{
    OsHook_CallProtectionHook(E_OS_PROTECTION_EXCEPTION);
}

FUNC(void, OS_CODE) OsHook_MemAccessException
(
    uint32 ExceptionAddress,
    boolean SupervisorMode
)
{
    OsHook_CallProtectionHook(E_OS_PROTECTION_MEMORY);
}

FUNC(void, OS_CODE) GetErrorInformation
(
    P2VAR(Os_HookErrorDetail, TYPEDEF, OS_VAR) ErrorInfoPtr
)
{
#if OSUSEPARAMETERACCESS == STD_ON
    P2VAR(Os_HookDynamicType, TYPEDEF, OS_VAR) Os_HookDynPtr;

    Os_HookDynPtr = OsKernel_GetCurrentCoreHookDataInfo();
#if OSUSEGETSERVICEID == STD_ON
    ErrorInfoPtr->ServiceID = Os_HookDynPtr->ErrorDetailInfo.ServiceID;
#endif
    ErrorInfoPtr->InputParameter[0] = Os_HookDynPtr->ErrorDetailInfo.InputParameter[0];
    ErrorInfoPtr->InputParameter[1] = Os_HookDynPtr->ErrorDetailInfo.InputParameter[1];
    ErrorInfoPtr->InputParameter[2] = Os_HookDynPtr->ErrorDetailInfo.InputParameter[2];
    ErrorInfoPtr->InputParameter[3] = Os_HookDynPtr->ErrorDetailInfo.InputParameter[3];
#endif
}

