/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_application.c
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
*  V0.1.0   28-May-2024    Pony(00412)                           Add Initial Code
****************************************************************************************************/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os.h"
#include "Os_isr.h"
#include "Os_ioc.h"
#include "Os_hook.h"
#include "Os_application_Lcfg.h"
#include "Os_application.h"
#include "Os_kernel_Cfg.h"
#include "Os_application.h"
#include "Os_kernel.h"
#include "Os_task.h"
#include "Os_alarm.h"
#include "Os_scheduletable.h"
#include "Os_context.h"
#include "Os_mpu.h"
#include "Os_mpu_Lcfg.h"
#include "Os_services.h"
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
*   Function Name           : OsApp_Internal_GetApplicationID
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(ApplicationType, OS_CODE) OsApp_Internal_GetApplicationID
(
    void
);

/****************************************************************************************************
*   Function Name           : OsApp_Internal_CheckObjectOwnership
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(ApplicationType, OS_CODE) OsApp_Internal_CheckObjectOwnership
(
    ObjectTypeType ObjectType,
    uint32 ObjectID
);
/****************************************************************************************************
*   Function Name           : OsApp_Internal_CheckObjectAccess
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(ObjectAccessType, OS_CODE) OsApp_Internal_CheckObjectAccess
(
    ApplicationType ApplID,
    ObjectTypeType ObjectType,
    uint32 ObjectID
);

/****************************************************************************************************
*   Function Name           : OsApp_Internal_GetApplicationState
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsApp_Internal_GetApplicationState
(
    ApplicationType Application,
    ApplicationStateRefType Value
);

/****************************************************************************************************
*   Function Name           : OsApp_Internal_AllowAccess
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsApp_Internal_AllowAccess
(
    void
);

/****************************************************************************************************
*   Function Name           : OsApp_Internal_TerminateApplication
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsApp_Internal_TerminateApplication
(
    ApplicationType Application,
    RestartType RestartOption
);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

#if (OS_ARTI_TRACE_APPLICATION == STD_ON)
/****************************************************************************************************
*   ARTI application events (openspec add-arti-hook-tracing, design D5). Emitted on the core the
*   application runs on (TerminateApplication is a service call to that core), with interrupts
*   suspended (NOSUSP) whatever the caller's state.
****************************************************************************************************/
#define OS_ARTI_APP_EV_START            (0U)
#define OS_ARTI_APP_EV_RESTART          (1U)
#define OS_ARTI_APP_EV_ALLOWACCESS      (2U)
#define OS_ARTI_APP_EV_TERMINATE        (3U)
static FUNC(void, OS_CODE) OsApp_Internal_Arti
(
    ApplicationType ApplicationID,
    uint8 Event
)
{
    Os_IsrLevelType ArtiLevel;
    CoreIdType ArtiCore;

    OsIsr_SuspendISR(&ArtiLevel);
    ArtiCore = Os_Inf_GetCoreId();
    switch(Event)
    {
        case OS_ARTI_APP_EV_START:
            OS_ARTI_APPLICATION_START(ArtiCore, ApplicationID);
            break;
        case OS_ARTI_APP_EV_RESTART:
            OS_ARTI_APPLICATION_RESTART(ArtiCore, ApplicationID);
            break;
        case OS_ARTI_APP_EV_ALLOWACCESS:
            OS_ARTI_APPLICATION_ALLOWACCESS(ArtiCore, ApplicationID);
            break;
        default:
            OS_ARTI_APPLICATION_TERMINATE(ArtiCore, ApplicationID);
            break;
    }
    OsIsr_ResumeISR(ArtiLevel);
}
#endif

static FUNC(ApplicationType, OS_CODE) OsApp_Internal_GetApplicationID
(
    void
)
{

    OsOrti_ServiceStart(OS_SERVICEID_GETAPPLICATIONID);
#if (OS_ARTI_TRACE_SERVICECALLS == STD_ON)
    {
        OS_ARTI_SC_DECL
        ApplicationType ArtiApp = OsKernel_GetCurrentCoreAppDataInfo()->Current_Config_ApplicationID;
        OS_ARTI_SC_BEGIN(GetApplicationID, 0U);
        OS_ARTI_SC_END(GetApplicationID, ArtiApp);
    }
#endif
    OsOrti_ServiceEnd(OS_SERVICEID_GETAPPLICATIONID);
    /* Set the Current_ApplicationID and Current_Config_ApplicationID to the Next_AppID */
    return OsKernel_GetCurrentCoreAppDataInfo()->Current_Config_ApplicationID;

}

static FUNC(ApplicationType, OS_CODE) OsApp_Internal_CheckObjectOwnership
(
    ObjectTypeType ObjectType,
    uint32 ObjectID
)
{
    ApplicationType AppID;
    uint32 LoopID;
    boolean FindObjectFlag;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_CHECKOBJECTOWNERSHIP);
    OS_ARTI_SC_BEGIN(CheckObjectOwnership, ObjectType);

    LoopID = 0u;
    FindObjectFlag = FALSE;

    /* Check the object whether in Objectlist or not. */
    do
    {
        if((Os_AppConfigSet.ObjectRef[LoopID].ObjectType == ObjectType)
            &&((Os_AppConfigSet.ObjectRef[LoopID].AppObjIDInfo & OBJECTID_MASK) == ObjectID))
        {
            FindObjectFlag = TRUE;
        }
        else
        {
            LoopID++;
        }

    }while((LoopID < TOTALNUM_OF_OBJECT)&&(FindObjectFlag != TRUE));

    /* Get the AppID from the ObjectInfo. */
    if(FindObjectFlag != TRUE)
    {
        AppID = INVALID_OSAPPLICATION;
    }
    else
    {
        /*return the Object ownership configuration in the object array*/
        AppID = (Os_AppConfigSet.ObjectRef[LoopID].AppObjIDInfo & APPLICATIONID_MASK) >> 16u;
    }

    OS_ARTI_SC_END(CheckObjectOwnership, AppID);
    OsOrti_ServiceEnd(OS_SERVICEID_CHECKOBJECTOWNERSHIP);

    return AppID;
}

static FUNC(ObjectAccessType, OS_CODE) OsApp_Internal_CheckObjectAccess
(
    ApplicationType ApplID,
    ObjectTypeType ObjectType,
    uint32 ObjectID
)
{
    ObjectAccessType result;
    uint32 LoopID;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_CHECKOBJECTACCESS);
    OS_ARTI_SC_BEGIN(CheckObjectAccess, ApplID);

    LoopID = 0u;

    if(OsService_ExtendedErrorCheck(ApplID >= OS_APPLICATION_TOTAL_NUM))
    {
        result = NO_ACCESS;
    }
    else
    {
        result = NO_ACCESS;
        /* Check the object whether in Object list or not. */
        do
        {
            if((Os_AppConfigSet.ObjectRef[LoopID].ObjectType == ObjectType)
                &&((Os_AppConfigSet.ObjectRef[LoopID].AppObjIDInfo & OBJECTID_MASK) == ObjectID)
                &&(ApplID == (Os_AppConfigSet.ObjectRef[LoopID].AppObjIDInfo & APPLICATIONID_MASK) >> 16u))
            {
                result = ACCESS;
            }
            else
            {
                LoopID++;
            }

        }while((LoopID < TOTALNUM_OF_OBJECT)&&(result != ACCESS));
    }

    OS_ARTI_SC_END(CheckObjectAccess, result);
    OsOrti_ServiceEnd(OS_SERVICEID_CHECKOBJECTACCESS);

    return result;
}

static FUNC(StatusType, OS_CODE) OsApp_Internal_GetApplicationState
(
    ApplicationType Application,
    ApplicationStateRefType Value
)
{
    StatusType result;
    CoreIdType CurrentCoreID;
    CoreIdType TargetCoreID;
    Os_IocInterCoreServiceCallType ServiceCallCfg;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_GETAPPLICATIONSTATE);
    OS_ARTI_SC_BEGIN(GetApplicationState, Application);

    CurrentCoreID = Os_Inf_GetCoreId();

    if(OsService_ExtendedErrorCheck((OsKernel_GetCurrentRunningContext() & OS_CALL_GETAPPLICATIONSTATE) == 0UL))
    {
        /* The context is error*/
        result = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        result = E_OS_DISABLEDINT;
    }
    else if(OsService_ExtendedErrorCheck(Application >= OS_APPLICATION_TOTAL_NUM))
    {
        /* SWS_Os_00493 */
        result =  E_OS_ID;
    }
    else
    {
        TargetCoreID = Os_AppConfigSet.AppConfigPtr[Application]->LogicalCoreID;

        if(CurrentCoreID != TargetCoreID)
        {
            /* Cross core service call */
            ServiceCallCfg.ServiceId = OS_SERVICEID_TERMINATEAPPLICATION;
            ServiceCallCfg.EntryAddress = (uint32)OsApp_GetApplicationState;
            ServiceCallCfg.TargetCoreId = Os_AppConfigSet.AppConfigPtr[Application]->PhysicalCoreID;
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)(Application);
            ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)Value;
            ServiceCallCfg.OutputParmMask = OS_IOC_OUTPUT_PARM1_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();

            result = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
        }
        else
        {
            result = OsApp_GetApplicationState(Application,Value);
        }
    }

    /*Error Processing*/
    if(E_OK != result)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_CONTROLIDLE, (InputParaType)(Application), (InputParaType)Value);
        OsHook_CallErrorHook(result);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(GetApplicationState, (E_OK == result) ? (uint32)(*Value) : OS_ARTI_SC_INVALID);
    OsOrti_ServiceEnd(OS_SERVICEID_GETAPPLICATIONSTATE);

    return result;
}

static FUNC(StatusType, OS_CODE) OsApp_Internal_AllowAccess
(
    void
)
{
    StatusType result;
    /* Get the Current_AppID */
    ApplicationType Current_AppID;
    CoreIdType LocalCoreID;
    CoreIdType AppCoreID;
    
    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_ALLOWACCESS);
    OS_ARTI_SC_BEGIN(AllowAccess, 0U);
    Current_AppID = OsKernel_GetCurrentCoreAppDataInfo()->Current_ApplicationID;

    if(OsService_ExtendedErrorCheck((OsKernel_GetCurrentRunningContext() & OS_CALL_CONTROLIDLE) == 0UL))
    {
        /* The context is error*/
        result = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        result = E_OS_DISABLEDINT;
    }
    else if(OsService_ExtendedErrorCheck(APPLICATION_RESTARTING != *Os_AppConfigSet.AppConfigPtr[Current_AppID]->AppStatusRef))
    {
        /* SWS_Os_00497 */
        result = E_OS_STATE;
    }
    else
    {
        AppCoreID = OsApp_GetOwnerCoreID(Current_AppID);
        LocalCoreID = Os_Inf_GetCoreId();
        if(OsService_ExtendedErrorCheck(AppCoreID != LocalCoreID))
        {
            result = E_OS_CORE;
        }
        else
        {
            /*Set application can be accessible*/
            *Os_AppConfigSet.AppConfigPtr[Current_AppID]->AppStatusRef = APPLICATION_ACCESSIBLE;
#if (OS_ARTI_TRACE_APPLICATION == STD_ON)
            OsApp_Internal_Arti(Current_AppID, OS_ARTI_APP_EV_ALLOWACCESS);
#endif
            result = E_OK;
        }
    }

    OS_ARTI_SC_END(AllowAccess, result);
    OsOrti_ServiceEnd(OS_SERVICEID_ALLOWACCESS);

    return result;
}

static FUNC(StatusType, OS_CODE) OsApp_Internal_TerminateApplication
(
    ApplicationType Application,
    RestartType RestartOption
)
{
    StatusType result;
    CoreIdType CurrentCoreID;
    CoreIdType TargetCoreID;
    Os_IocInterCoreServiceCallType ServiceCallCfg;
    Os_IsrLevelType Level;
    ApplicationType CurrentAppID;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_TERMINATEAPPLICATION);
    OS_ARTI_SC_BEGIN(TerminateApplication, Application);

    CurrentCoreID = Os_Inf_GetCoreId();

    if(OsService_ExtendedErrorCheck((OsKernel_GetCurrentRunningContext() & OS_CALL_TERMINATEAPPLICATION) == 0UL))
    {
        /*  */
        result = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        result = E_OS_DISABLEDINT;
    }
    else if(OsService_ExtendedErrorCheck(Application >= OS_APPLICATION_TOTAL_NUM))
    {
        /* SWS_Os_00493 */
        result =  E_OS_ID;
    }
    else
    {
        CurrentAppID = OsKernel_GetCurrentCoreAppDataInfo()->Current_ApplicationID;
        /*pony added 'the caller belongs to a non-trusted OS-Application AND the caller does not belong to <Application>'*/
        if(OsService_ExtendedErrorCheck(!OsApp_CheckCurrentAppIsTrusted()&&(CurrentAppID != Application)))
        {
            /* SWS_Os_00494 */
            result = E_OS_ACCESS;
        }
        TargetCoreID = Os_AppConfigSet.AppConfigPtr[Application]->LogicalCoreID;

        if(CurrentCoreID != TargetCoreID)
        {
            /* Cross core service call */
            ServiceCallCfg.ServiceId = OS_SERVICEID_TERMINATEAPPLICATION;
            ServiceCallCfg.EntryAddress = (uint32)OsApp_TerminateApplication;
            ServiceCallCfg.TargetCoreId = Os_AppConfigSet.AppConfigPtr[Application]->PhysicalCoreID;
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)(Application);
            ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)RestartOption;
            ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();

            result = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
        }
        else
        {
            result = OsApp_TerminateApplication(Application,RestartOption);
        }
    }

    /*Error Processing*/
    if(E_OK != result)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_CONTROLIDLE, (InputParaType)(Application), (InputParaType)RestartOption);
        OsHook_CallErrorHook(result);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(TerminateApplication, result);
    OsOrti_ServiceEnd(OS_SERVICEID_TERMINATEAPPLICATION);

    return result;
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
FUNC(void, OS_CODE) OsApp_ChangeCurrent_AppInfo
(
    uint32 TargetObjectID
)
{
    /* Get the Current_AppID */
    ApplicationType Current_AppID;
    /* Get the Next_AppID */
    ApplicationType Next_AppID;
    /* Get the CurrentObjectID */ 
    uint32 CurrentObjectID;

    /* Get the CurrentObjectID */
    CurrentObjectID = OsKernel_GetCurrentCoreAppDataInfo()->Current_RunningObjectID;

    if(TargetObjectID != CurrentObjectID)
    {
        /* Get the Current_AppID */
        Current_AppID = (Os_AppConfigSet.ObjectRef[CurrentObjectID].AppObjIDInfo & APPLICATIONID_MASK) >> 16u;
        /* Get the Next_AppID */
        Next_AppID = (Os_AppConfigSet.ObjectRef[TargetObjectID].AppObjIDInfo & APPLICATIONID_MASK) >> 16u;

        /* Check if the Current_AppID is not equal to the Next_AppID */
        if(Current_AppID != Next_AppID)
        {
            /* Set the Current_ApplicationID and Current_Config_ApplicationID to the Next_AppID */
            OsKernel_GetCurrentCoreAppDataInfo()->Current_ApplicationID = Next_AppID;
            OsKernel_GetCurrentCoreAppDataInfo()->Current_Config_ApplicationID = Next_AppID;
            /* Application Mp Region Switch. Always change App level mpu region when app changed. */
            OsMpu_AppSwitchTo(Next_AppID);
        }
        else
        {
            /* Do nothing */
        }

        /* The current Object is ISR or Hook */
        if(OBJECT_TASK != Os_AppConfigSet.ObjectRef[TargetObjectID].ObjectType)
        {
            if((Os_AppObjectRefType)&Os_AppConfigSet.ObjectRef[TargetObjectID] == *Os_AppConfigSet.ObjectRef[CurrentObjectID].PreviousObjectInfoRef)
            {
                /* The normal object switch  */
                *Os_AppConfigSet.ObjectRef[CurrentObjectID].PreviousObjectInfoRef = NULL_PTR;
            }
            else
            {
                /*There are nested object*/
                *Os_AppConfigSet.ObjectRef[TargetObjectID].PreviousObjectInfoRef = (Os_AppObjectRefType)&Os_AppConfigSet.ObjectRef[CurrentObjectID];
            }
        }

        /* Always change object level mpu region when object changed. */
        OsMpu_ObjectSwitchTo((*Os_AppConfigSet.ObjectRef[TargetObjectID].ObjectDataInfo.ObjectContextInfoPtr)->MpuInfoPtr);

        /* Set the Current_RunningObjectID to the NextObjectID */
        OsKernel_GetCurrentCoreAppDataInfo()->Current_RunningObjectID = TargetObjectID;
    }
    else
    {
        /* Do nothing */
    }
    Os_Inf_Isync();
}

FUNC(uint32, OS_CODE) OsApp_GetCurrent_ObjectID
(
    void
)
{
    /* Return the Current_RunningObjectID */
    return OsKernel_GetCurrentCoreAppDataInfo()->Current_RunningObjectID;
}

FUNC(Os_AppObjectRefType, OS_CODE) OsApp_GetCurrent_ObjectInfo
(
    void
)
{
    uint32 ObjectID;
    /* Get the Current Running ObjectID */
    ObjectID = OsKernel_GetCurrentCoreAppDataInfo()->Current_RunningObjectID;

    /* Return the Current_RunningObjectID */
    return &(Os_AppConfigSet.ObjectRef[ObjectID]);
}

FUNC(Os_AppObjectRefType, OS_CODE) OsApp_GetPrevious_ObjectInfo
(
    void
)
{
    uint32 ObjectID;
    /* Get the Current Running ObjectID */
    ObjectID = OsKernel_GetCurrentCoreAppDataInfo()->Current_RunningObjectID;

    /* Return the previous Object data information */
    return *Os_AppConfigSet.ObjectRef[ObjectID].PreviousObjectInfoRef;
}

FUNC(Os_AppObjectRefType, OS_CODE) OsApp_GetSpecific_ObjectInfo
(
    uint32 ObjectID
)
{
    /* Return the Object ID */
    return &(Os_AppConfigSet.ObjectRef[ObjectID]);
}

FUNC(CoreIdType, OS_CODE) OsApp_GetOwnerCoreID
(
    uint32 ApplicationID
)
{
    /*Return the logical Core ID*/
    return Os_AppConfigSet.AppConfigPtr[ApplicationID]->LogicalCoreID;
}

FUNC(ApplicationType, OS_CODE) OsApp_GetCurrentApplicationID
(
    void
)
{
    return OsKernel_GetCurrentCoreAppDataInfo()->Current_ApplicationID;
}

FUNC(void, OS_CODE) OsApp_SetAppTerminateStatus
(
    ApplicationType ApplicationID
)
{
#if (OS_ARTI_TRACE_APPLICATION == STD_ON)
    if(APPLICATION_TERMINATED != *Os_AppConfigSet.AppConfigPtr[ApplicationID]->AppStatusRef)
    {
        OsApp_Internal_Arti(ApplicationID, OS_ARTI_APP_EV_TERMINATE);
    }
#endif
    /*Set application state to terminated */
    *Os_AppConfigSet.AppConfigPtr[ApplicationID]->AppStatusRef = APPLICATION_TERMINATED;
}

FUNC(CoreIdType, OS_CODE) OsApp_GetPhysicalCoreIDFromObjectInfo
(
    uint32 ObjectID
)
{
    CoreIdType PhysicalCoreID;
    /*Get the physical core ID from Object data */
    PhysicalCoreID = (Os_AppConfigSet.ObjectRef[ObjectID].AppObjIDInfo & COREID_MASK) >> 24;

    return PhysicalCoreID;
}

FUNC(StatusType, OS_CODE) OsApp_GetApplicationState
(
    ApplicationType Application,
    ApplicationStateRefType Value
)
{
    /*return the application state from application data*/
    *Value = *((ApplicationStateRefType)Os_AppConfigSet.AppConfigPtr[Application]->AppStatusRef);
    return E_OK;
}

FUNC(TaskType, OS_CODE) OsApp_GetAppRestartTaskID
(
    ApplicationType ApplicationID
)
{
    /*Get the application restart task if the application has been configured restart task*/
    return Os_AppConfigSet.AppConfigPtr[ApplicationID]->RestartTask;
}

FUNC(boolean, OS_CODE) OsApp_CheckObjectAccessingAppMask
(
    uint32 ObjectID
)
{
    boolean result;
    ApplicationType AppID;
    uint32 AppIDMask;

    AppID = OsKernel_GetCurrentCoreAppDataInfo()->Current_ApplicationID;
    AppIDMask = (uint32)(1UL << AppID);

    /*check the current application ID in the accessing application mask*/
    if((Os_AppConfigSet.ObjectRef[ObjectID].AccessingAppMask & AppIDMask) != 0UL)
    {
        result = TRUE;
    }
    else
    {
        result = FALSE;
    }

    return result;
}

FUNC(boolean, OS_CODE) OsApp_CheckObjectAppIsAccessiable
(
    uint32 ObjectID
)
{
    boolean result;
    ApplicationType AppID;

    AppID = (Os_AppConfigSet.ObjectRef[ObjectID].AppObjIDInfo & APPLICATIONID_MASK) >> 16u;

    /*Check the object status is accessible or not */
    if(APPLICATION_ACCESSIBLE == *Os_AppConfigSet.AppConfigPtr[AppID]->AppStatusRef)
    {
        result = TRUE;
    }
    else
    {
        result = FALSE;
    }

    return result;
}

FUNC(boolean, OS_CODE) OsApp_CheckCurrentAppIsTrusted
(
    void
)
{
    ApplicationType AppID;

    AppID = OsKernel_GetCurrentCoreAppDataInfo()->Current_ApplicationID;
    /*return the current application being trusted or not*/
    return Os_AppConfigSet.AppConfigPtr[AppID]->AppIsTrusted;
}

FUNC(boolean, OS_CODE) OsApp_GetCurrentAppTpDelay
(
    void
)
{
    ApplicationType AppID;

    AppID = OsKernel_GetCurrentCoreAppDataInfo()->Current_ApplicationID;
    /*return the current application whether configured TP delay or not*/
    return Os_AppConfigSet.AppConfigPtr[AppID]->OsTrustedApplicationDelayTimingViolationCall;
}

FUNC(void, OS_CODE) OsApp_SetCurrent_ConfigApplicationID
(
    ApplicationType ApplicationID
)
{
    /* Set the Current_ApplicationID and Current_Config_ApplicationID to the Next_AppID */
    OsKernel_GetCurrentCoreAppDataInfo()->Current_ApplicationID = ApplicationID;
}

FUNC(boolean, OS_CODE) OsApp_CheckTrustedFunctionIsCalled
(
    void
)
{
    /*Check current application has been the process of calling trusted function*/
    return OsKernel_GetCurrentCoreAppDataInfo()->TrustFunctionIsCalled;
}

FUNC(StatusType, OS_CODE) OsApp_TerminateApplication
(
    ApplicationType Application,
    RestartType RestartOption
)
{
    uint32 ObjectIndexID;
    P2CONST(Os_ApplicationConfigType, TYPEDEF, OS_CONST) AppData;
    uint32 AppObjectTypeID_Index;
    StatusType result;
    Os_IsrLevelType Level;
    boolean SchedulerCheckFlag;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) CurrentObjectInfo;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) SpecficObjectInfo;

    SchedulerCheckFlag = FALSE;
    CurrentObjectInfo = &Os_AppConfigSet.ObjectRef[OsKernel_GetCurrentCoreAppDataInfo()->Current_RunningObjectID];

    if(OsService_ExtendedErrorCheck((RestartOption != OS_OSAPPLICATION_RESTART) && (RestartOption != OS_OSAPPLICATION_NO_RESTART)))
    {
        /* SWS_Os_00459 the <RestartOption> is invalid*/
        result = E_OS_VALUE;
    }
    else if(OsService_ExtendedErrorCheck(APPLICATION_TERMINATED == *Os_AppConfigSet.AppConfigPtr[Application]->AppStatusRef))
    {
        /* SWS_Os_00507 the state of <Application> is APPLICATION_TERMINATED */
        result = E_OS_STATE;
    }
    else if(OsService_ExtendedErrorCheck(Application == OsKernel_GetCurrentCoreKernelAppID()))
    {
        /* Kernel Application can't be terminated.  */
        result = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck((RestartOption == OS_OSAPPLICATION_RESTART) && (INVALID_TASK == Os_AppConfigSet.AppConfigPtr[Application]->RestartTask)))
    {
        /* pony added :If no OsRestartTask is configured, no restart shall happen  */
        result = E_OS_NO_PRE_TASK;
    }
    else
    {
        OsIsr_SuspendISR(&Level);

        if(OsService_ExtendedErrorCheck((APPLICATION_RESTARTING == *Os_AppConfigSet.AppConfigPtr[Application]->AppStatusRef)
            && (Application != OsKernel_GetCurrentCoreAppDataInfo()->Current_ApplicationID)))
        {
            /* SWS_Os_00508  the state of Application is APPLICATION_RESTARTING */
            result = E_OS_STATE;
        }
        else if(OsService_ExtendedErrorCheck((APPLICATION_RESTARTING == *Os_AppConfigSet.AppConfigPtr[Application]->AppStatusRef)
            && (RestartOption == OS_OSAPPLICATION_RESTART)))
        {
            /* SWS_Os_00548 the state of Application is APPLICATION_RESTARTING*/
            result = E_OS_STATE;
        }
        else
        {
            /* Get the Application Data */
            AppData = Os_AppConfigSet.AppConfigPtr[Application];

            /*  Initialize each task in application */
            for(ObjectIndexID = AppData->ObjectID_StartNum;
                    ObjectIndexID < (AppData->ObjectIDCount + AppData->ObjectID_StartNum); ObjectIndexID++ )
            {
                /* Get the ObjectTypeID. */
                AppObjectTypeID_Index = Os_AppConfigSet.ObjectRef[ObjectIndexID].AppObjIDInfo & OBJECTID_MASK;

                /* Check if the current object is needed deinit */
                if(ObjectIndexID == OsKernel_GetCurrentCoreAppDataInfo()->Current_RunningObjectID)
                {
                    SchedulerCheckFlag = TRUE;
                }

                /* DeInitialize each object in application */
                switch (Os_AppConfigSet.ObjectRef[ObjectIndexID].ObjectType)
                {
                    case OBJECT_TASK:
                        OsTask_TaskDeinit(AppObjectTypeID_Index);
                        break;

                    case OBJECT_ISR:
                        OsIsr_IsrDeInit(AppObjectTypeID_Index);
                        break;

                    case OBJECT_ALARM:
                        OsAlarm_AlarmDeinit(AppObjectTypeID_Index);
                        break;

                    case OBJECT_SCHEDULETABLE:
                        OsSchT_DeInit(AppObjectTypeID_Index);
                        break;

                    case OBJECT_APPIOCCALLBACK:
                        OsIoc_CallbackDeInit(ObjectIndexID);
                        break;

                    case OBJECT_APPHOOK:
                        SpecficObjectInfo = &Os_AppConfigSet.ObjectRef[ObjectIndexID];
                        Os_Hal_ContextAbort(*SpecficObjectInfo->ObjectDataInfo.ObjectContextInfoPtr,
                                            (*SpecficObjectInfo->ObjectDataInfo.ObjectContextInfoPtr)->ContextInfoPtr);
                        break;
                    default:
                        /* Assert UnExpected ObjectType */
                        break;
                }
            }

            if(OS_OSAPPLICATION_RESTART == RestartOption)
            {
                /* Set the application state */
                *AppData->AppStatusRef = APPLICATION_RESTARTING;
#if (OS_ARTI_TRACE_APPLICATION == STD_ON)
                OsApp_Internal_Arti(Application, OS_ARTI_APP_EV_RESTART);
#endif
                /* call the restart task of application  */
                OsTask_ActivateRestartTask(AppData->RestartTask);
            }
            else
            {
#if (OS_ARTI_TRACE_APPLICATION == STD_ON)
                OsApp_Internal_Arti(Application, OS_ARTI_APP_EV_TERMINATE);
#endif
                /* Set the application state */
                *AppData->AppStatusRef = APPLICATION_TERMINATED;
            }
            /*if need to terminate current object*/
            if(SchedulerCheckFlag == TRUE)
            {
                if(OBJECT_TASK == CurrentObjectInfo->ObjectType)
                {
                    /*If the object is task , start scheduling */
                    OsTask_DoScheduling(NOT_SAVING_CONTEXT);
                }
                else if(OBJECT_ISR == CurrentObjectInfo->ObjectType)
                {
                    /*If the object is ISR , start post processing to complete the ISR  */
                    OsIsr_PostISR();
                }
                else if(OBJECT_APPHOOK == CurrentObjectInfo->ObjectType)
                {
                    /*If the object is Hook , then complete the hook process  */
                    OsHook_Hookreturn();
                }
                else if(OBJECT_APPIOCCALLBACK == CurrentObjectInfo->ObjectType)
                {
                    /*If the object is IOC Hook , then complete the hook process  */
                    OsIoc_CallbackReturn();
                }
                else
                {
                    CodeFreeze();
                }
            }
            else
            {
                /*Though current object need not to terminate, but the current object is task, still need to check
                 * whether need to scheduling*/
                if(OBJECT_TASK == CurrentObjectInfo->ObjectType)
                {
                    OsTask_DoScheduling(SAVING_CONTEXT);
                }
            }

            result = E_OK;
        }

        OsIsr_ResumeISR(Level);
    }

    return result;
}

FUNC(void, OS_CODE) OsApp_ApplicationInit
(
    ApplicationType ApplicationID,
    AppModeType Mode
)
{
    uint32 ObjectIndexID;
    P2CONST(Os_ApplicationConfigType, TYPEDEF, OS_CONST) AppData;
    uint32 AppObjectTypeID_Index;

    /* Get the Application Data */
    AppData = Os_AppConfigSet.AppConfigPtr[ApplicationID];

    /*  Initialize each task in application */
    for(ObjectIndexID = AppData->ObjectID_StartNum;
            ObjectIndexID < (AppData->ObjectIDCount + AppData->ObjectID_StartNum); ObjectIndexID++ )
    {
        /* Get the ObjectTypeID. */
        AppObjectTypeID_Index = Os_AppConfigSet.ObjectRef[ObjectIndexID].AppObjIDInfo & OBJECTID_MASK;

        /* Initialize each object in application */
        switch (Os_AppConfigSet.ObjectRef[ObjectIndexID].ObjectType)
        {
            case OBJECT_TASK:
                OsTask_TaskInit(AppObjectTypeID_Index, Mode);
            break;

            case OBJECT_ISR:
                OsIsr_IsrInit(AppObjectTypeID_Index);
                *(Os_AppConfigSet.ObjectRef[ObjectIndexID].PreviousObjectInfoRef) = NULL_PTR;
            break;

            case OBJECT_ALARM:
                OsAlarm_AlarmInit(AppObjectTypeID_Index, Mode);
            break;

            case OBJECT_SCHEDULETABLE:
                OsSchT_Init(AppObjectTypeID_Index, Mode);
            break;

            case OBJECT_KERNELHOOK:
                *(Os_AppConfigSet.ObjectRef[ObjectIndexID].PreviousObjectInfoRef) = NULL_PTR;
            break;

            case OBJECT_APPHOOK:
                *(Os_AppConfigSet.ObjectRef[ObjectIndexID].PreviousObjectInfoRef) = NULL_PTR;
            break;

            case OBJECT_APPIOCCALLBACK:
                *(Os_AppConfigSet.ObjectRef[ObjectIndexID].PreviousObjectInfoRef) = NULL_PTR;
            break;

            default:
                /* Assert UnExpected ObjectType */
              break;
        }
    }
    /* [SWS_Os_00500] The Operating System module shall set the state of all OS Applications
     * after the call of StartOS and before any StartupHook is called to APPLICATION_ACCESSIBLE */
    *AppData->AppStatusRef = APPLICATION_ACCESSIBLE;
#if (OS_ARTI_TRACE_APPLICATION == STD_ON)
    OsApp_Internal_Arti(ApplicationID, OS_ARTI_APP_EV_START);
#endif
}

FUNC(void, OS_CODE) OsApp_ApplicationDeInit
(
    ApplicationType ApplicationID
)
{
    uint32 ObjectIndexID;
    P2CONST(Os_ApplicationConfigType, TYPEDEF, OS_CONST) AppData;
    uint32 AppObjectTypeID_Index;

    /* Get the Application Data */
    AppData = Os_AppConfigSet.AppConfigPtr[ApplicationID];

    /*  Initialize each task in application */
    for(ObjectIndexID = AppData->ObjectID_StartNum;
            ObjectIndexID < (AppData->ObjectIDCount + AppData->ObjectID_StartNum); ObjectIndexID++ )
    {
        /* Get the ObjectTypeID. */
        AppObjectTypeID_Index = Os_AppConfigSet.ObjectRef[ObjectIndexID].AppObjIDInfo & OBJECTID_MASK;

        /* DeInitialize each object in application */
        switch (Os_AppConfigSet.ObjectRef[ObjectIndexID].ObjectType)
        {
            case OBJECT_TASK:
                OsTask_TaskDeinit(AppObjectTypeID_Index);
            break;

            case OBJECT_ISR:
                OsIsr_IsrDeInit(AppObjectTypeID_Index);
            break;

            case OBJECT_ALARM:
                OsAlarm_AlarmDeinit(AppObjectTypeID_Index);
            break;

            case OBJECT_SCHEDULETABLE:
                OsSchT_DeInit(AppObjectTypeID_Index);
            break;

            case OBJECT_APPIOCCALLBACK:
                OsIoc_CallbackDeInit(ObjectIndexID);
            break;

            default:
                /* Assert UnExpected ObjectType */
              break;
        }
    }

#if (OS_ARTI_TRACE_APPLICATION == STD_ON)
    if(APPLICATION_TERMINATED != *AppData->AppStatusRef)
    {
        OsApp_Internal_Arti(ApplicationID, OS_ARTI_APP_EV_TERMINATE);
    }
#endif
    /*  */
    *AppData->AppStatusRef = APPLICATION_TERMINATED;
}
/****************************************************************************************************
**                          AUTOSAR Function Definitions                                           **
****************************************************************************************************/
FUNC(ApplicationType, OS_CODE) GetApplicationID
(
    void
)
{
    ApplicationType AppID;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        /*   */
        AppID = OsApp_Internal_GetApplicationID();
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        AppID = OsApp_Internal_GetApplicationID();
    }

    return AppID;
}

FUNC(ApplicationType, OS_CODE) GetCurrentApplicationID
(
    void
)
{
    ApplicationType AppID;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();

        OsOrti_ServiceStart(OS_SERVICEID_GETCURRENTAPPLICATIONID);

        /*   */
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(GetCurrentApplicationID, 0U);
            AppID = OsKernel_GetCurrentCoreAppDataInfo()->Current_ApplicationID;
            OS_ARTI_SC_END(GetCurrentApplicationID, AppID);
        }
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        OsOrti_ServiceStart(OS_SERVICEID_GETCURRENTAPPLICATIONID);
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(GetCurrentApplicationID, 0U);
            AppID = OsKernel_GetCurrentCoreAppDataInfo()->Current_ApplicationID;
            OS_ARTI_SC_END(GetCurrentApplicationID, AppID);
        }
    }

    OsOrti_ServiceEnd(OS_SERVICEID_GETCURRENTAPPLICATIONID);

    return AppID;
}

FUNC(ApplicationType, OS_CODE) CheckObjectOwnership
(
    ObjectTypeType ObjectType,
    uint32 ObjectID
)
{
    ApplicationType AppID;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        /*   */
        AppID = OsApp_Internal_CheckObjectOwnership(ObjectType, ObjectID);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        AppID = OsApp_Internal_CheckObjectOwnership(ObjectType, ObjectID);
    }

    return AppID;
}

FUNC(ObjectAccessType, OS_CODE) CheckObjectAccess
(
    ApplicationType ApplID,
    ObjectTypeType ObjectType,
    uint32 ObjectID
)
{
    ObjectAccessType result;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        /*   */
        result = OsApp_Internal_CheckObjectAccess(ApplID, ObjectType, ObjectID);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        result = OsApp_Internal_CheckObjectAccess(ApplID, ObjectType, ObjectID);
    }

    return result;
}

FUNC(StatusType, OS_CODE) GetApplicationState
(
    ApplicationType Application,
    ApplicationStateRefType Value
)
{
    StatusType result;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        /*   */
        result = OsApp_Internal_GetApplicationState(Application, Value);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        result = OsApp_Internal_GetApplicationState(Application, Value);
    }

    return result;
}

FUNC(StatusType, OS_CODE) TerminateApplication
(
    ApplicationType Application,
    RestartType RestartOption
)
{
    StatusType result;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        /*   */
        result = OsApp_Internal_TerminateApplication(Application, RestartOption);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        result = OsApp_Internal_TerminateApplication(Application, RestartOption);
    }

    return result;

}

FUNC(StatusType, OS_CODE) AllowAccess
(
    void
)
{
    StatusType result;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        /*   */
        result = OsApp_Internal_AllowAccess();
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        result = OsApp_Internal_AllowAccess();
    }

    return result;
}

