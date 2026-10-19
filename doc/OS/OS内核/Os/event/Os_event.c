/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_event.c
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
#include "Os.h"
#include "Os_isr.h"
#include "Os_hook.h"
#include "Os_event.h"
#include "Os_task.h"
#include "Os_task_Lcfg.h"
#include "Os_isr_Cfg.h"
#include "Os_application.h"
#include "Os_compiler_types.h"
#include "Os_timingprotection.h"
#include "Os_ioc.h"
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
*   Function Name           : OsEvent_Internal_SetEvent
*   Service ID              : None.
*   Description             : Set event under kernel
*   Parameters in           : TaskID
*                             Mask
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsEvent_Internal_SetEvent
(
    TaskType TaskID,
    EventMaskType Mask
);

/****************************************************************************************************
*   Function Name           : OsEvent_Internal_SetEventAsyn
*   Service ID              : None.
*   Description             : Set event under kernel
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsEvent_Internal_SetEventAsyn
(
    TaskType TaskID,
    EventMaskType Mask
);

/****************************************************************************************************
*   Function Name           : OsEvent_Internal_ClearEvent
*   Service ID              : None.
*   Description             : Clear event under kernel
*   Parameters in           : Mask
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsEvent_Internal_ClearEvent
(
    EventMaskType Mask
);

/****************************************************************************************************
*   Function Name           : OsEvent_Internal_GetEvent
*   Service ID              : None.
*   Description             : Get event under kernel
*   Parameters in           : TaskID
*   Parameters inout        : Event
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsEvent_Internal_GetEvent
(
    TaskType TaskID,
    EventMaskRefType Event
);

/****************************************************************************************************
*   Function Name           : OsEvent_Internal_WaitEvent
*   Service ID              : None.
*   Description             : Wait event under kernel
*   Parameters in           : Mask
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsEvent_Internal_WaitEvent
(
    EventMaskType Mask
);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
FUNC(StatusType, OS_CODE) OsEvent_Internal_SetEvent
(
    TaskType TaskID,
    EventMaskType Mask
)
{
    StatusType Status;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) CurrentObjectInfo;
    Os_IsrLevelType Level;
    Os_IocInterCoreServiceCallType ServiceCallCfg;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_SETEVENT);
    OS_ARTI_SC_BEGIN(SetEvent, TaskID);

    Status = E_OK;
    CurrentObjectInfo = OsApp_GetCurrent_ObjectInfo();

    if(OsService_ExtendedErrorCheck(TaskID >= TOTAL_TASK_NUM))
    {
        /* Task <TaskID> is invalid */
        Status =  E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(FALSE == OsTask_GetTaskConst(TaskID)->IsExtended))
    {
        /* Referenced task is no extended task */
        Status = E_OS_ACCESS;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_SETEVENT)))
    {
        /* Call at interrupt level */
        Status = E_OS_CALLEVEL;
    }
    else if(TRUE != OsApp_CheckObjectAccessingAppMask(OsTask_GetTaskConst(TaskID)->ObjectID) ||
            TRUE != OsApp_CheckObjectAppIsAccessiable(OsTask_GetTaskConst(TaskID)->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else
    {
        if(TRUE == OsKernel_CheckObjectBelongToCurrentCore(OsTask_GetTaskConst(TaskID)->ObjectID))
        {
            OsIsr_SuspendISR(&Level);
            Status = OsEvent_SetEvent(TaskID, Mask);
            if(Status == E_OK && (CurrentObjectInfo->ObjectType == OBJECT_TASK))
            {
                OsTask_DoScheduling(SAVING_CONTEXT);
            }
            OsIsr_ResumeISR(Level);
        }
        else
        {
            /* Cross core service call */
            ServiceCallCfg.ServiceId = OS_SERVICEID_SETEVENT;
            ServiceCallCfg.EntryAddress = (uint32)OsEvent_SetEvent;
            ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(OsTask_GetTaskConst(TaskID)->ObjectID);
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)TaskID;
            ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)Mask;
            ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
            Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
        }

    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_SETEVENT, (InputParaType)TaskID, (InputParaType)Mask);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(SetEvent, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_SETEVENT);

    return Status;
}

FUNC(StatusType, OS_CODE) OsEvent_Internal_SetEventAsyn
(
    TaskType TaskID,
    EventMaskType Mask
)
{
    StatusType Status;
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskConPtr;
    Os_IsrLevelType Level;
    Os_IocInterCoreServiceCallType ServiceCallCfg;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_SETEVENTASYN);
    OS_ARTI_SC_BEGIN(SetEventAsyn, TaskID);

    Status = E_OK;
    TaskConPtr = OsTask_GetTaskConst(TaskID);

    if(OsService_ExtendedErrorCheck(FALSE == TaskConPtr->IsExtended))
    {
        /* Referenced task is no extended task */
        Status = E_OS_ACCESS;
    }
    else if(TRUE != OsApp_CheckObjectAccessingAppMask(OsTask_GetTaskConst(TaskID)->ObjectID) ||
            TRUE != OsApp_CheckObjectAppIsAccessiable(OsTask_GetTaskConst(TaskID)->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if(OsService_ExtendedErrorCheck(TaskID >= TOTAL_TASK_NUM))
    {
        /* Task <TaskID> is invalid */
        Status =  E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_SETEVENTASYN)))
    {
        /* Call at interrupt level */
        Status = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else
    {
        /* Cross core service call */
        ServiceCallCfg.ServiceId = OS_SERVICEID_SETEVENT;
        ServiceCallCfg.EntryAddress = (uint32)OsEvent_SetEvent;
        ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(OsTask_GetTaskConst(TaskID)->ObjectID);
        ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)TaskID;
        ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)Mask;
        ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
        ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_ASYNC;
        Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_SETEVENTASYN, (InputParaType)TaskID, (InputParaType)Mask);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(SetEventAsyn, 0U);
    OsOrti_ServiceEnd(OS_SERVICEID_SETEVENTASYN);
    return Status;
}

FUNC(StatusType, OS_CODE) OsEvent_Internal_ClearEvent
(
    EventMaskType Mask
)
{

    StatusType Status;
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskConPtr;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_CLEAREVENT);
    OS_ARTI_SC_BEGIN(ClearEvent, Mask);

    Status = E_OK;
    SchedulerPtr = OsTask_GetSchedulerDyn();
    TaskConPtr = OsTask_GetTaskConst(SchedulerPtr->CurrentTask);

    if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_CLEAREVENT)))
    {
        /* Call at interrupt level */
        Status = E_OS_CALLEVEL;
    }
    else if(OsService_ExtendedErrorCheck(FALSE == TaskConPtr->IsExtended))
    {
        /* Referenced task is no extended task */
        Status = E_OS_ACCESS;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else
    {
        OsIsr_SuspendISR(&Level);
        TaskDynPtr = OsTask_GetTaskDyn(SchedulerPtr->CurrentTask);
        TaskDynPtr->EventSet &= ~Mask;
        OsIsr_ResumeISR(Level);
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterOne(OS_SERVICEID_CLEAREVENT, (InputParaType)Mask);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(ClearEvent, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_CLEAREVENT);

    return Status;
}

FUNC(StatusType, OS_CODE) OsEvent_Internal_GetEvent
(
    TaskType TaskID,
    EventMaskRefType Event
)
{
    StatusType Status;
    Os_IsrLevelType Level;
    Os_IocInterCoreServiceCallType ServiceCallCfg;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_GETEVENT);
    OS_ARTI_SC_BEGIN(GetEvent, TaskID);

    Status = E_OK;
    if(OsService_ExtendedErrorCheck(TaskID >= TOTAL_TASK_NUM))
    {
        /* Task <TaskID> is invalid */
        Status =  E_OS_ID;
    }
    else if(TRUE != OsApp_CheckObjectAccessingAppMask(OsTask_GetTaskConst(TaskID)->ObjectID) ||
            TRUE != OsApp_CheckObjectAppIsAccessiable(OsTask_GetTaskConst(TaskID)->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if(OsService_ExtendedErrorCheck(FALSE == OsTask_GetTaskConst(TaskID)->IsExtended))
    {
        /* Referenced task is no extended task */
        Status = E_OS_ACCESS;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if (OsService_ExtendedErrorCheck(NULL_PTR == Event))
    {
        Status = E_OS_ILLEGAL_ADDRESS;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_GETEVENT)))
    {
        /* Call at interrupt level */
        Status = E_OS_CALLEVEL;
    }
    else
    {
        if(TRUE == OsKernel_CheckObjectBelongToCurrentCore(OsTask_GetTaskConst(TaskID)->ObjectID))
        {
            OsIsr_SuspendISR(&Level);
            Status = OsEvent_GetEvent(TaskID, Event);
            OsIsr_ResumeISR(Level);
        }
        else
        {
            /* Cross core service call */
            ServiceCallCfg.ServiceId = OS_SERVICEID_GETEVENT;
            ServiceCallCfg.EntryAddress = (uint32)OsEvent_GetEvent;
            ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(OsTask_GetTaskConst(TaskID)->ObjectID);
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)TaskID;
            ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)Event;
            ServiceCallCfg.OutputParmMask = OS_IOC_OUTPUT_PARM1_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
            Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
            *Event = (EventMaskType)ServiceCallCfg.OutParameter.OutParm[0];
        }

    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_GETEVENT, (InputParaType)TaskID, (InputParaType)Event);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(GetEvent, (E_OK == Status) ? (uint32)(*Event) : OS_ARTI_SC_INVALID);
    OsOrti_ServiceEnd(OS_SERVICEID_GETEVENT);

    return Status;
}

FUNC(StatusType, OS_CODE) OsEvent_Internal_WaitEvent
(
    EventMaskType Mask
)
{
    StatusType Status;
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskConPtr;
    P2CONST(Os_AppObjectType, TYPEDEF,  OS_CONST) CurrentObject;
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF,  OS_CONST) TaskTpConfig;
    Os_IsrLevelType Level;
    boolean TaskEnterWaitState;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_WAITEVENT);
    OS_ARTI_SC_BEGIN(WaitEvent, Mask);

    Status = E_OK;
    TaskEnterWaitState = TRUE;
    SchedulerPtr = OsTask_GetSchedulerDyn();
    TaskDynPtr = OsTask_GetTaskDyn(SchedulerPtr->CurrentTask);
    TaskConPtr = OsTask_GetTaskConst(SchedulerPtr->CurrentTask);
    CurrentObject = OsApp_GetCurrent_ObjectInfo();
    TaskTpConfig = (*(CurrentObject->ObjectDataInfo.ObjectContextInfoPtr))->TpInfoPtr;

    if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_WAITEVENT)))
    {
        /* Call at interrupt level */
        Status = E_OS_CALLEVEL;
    }
    else if(OsService_ExtendedErrorCheck(FALSE == TaskConPtr->IsExtended))
    {
        /* Referenced task is no extended task */
        Status = E_OS_ACCESS;
    }
    else if(OsService_ExtendedErrorCheck((NULL_PTR != TaskDynPtr->LockList) && (OS_LOCKTYPE_RESOURCE == TaskDynPtr->LockList->LockType)))
    {
        /* Calling task still occupies resources */
        Status = E_OS_RESOURCE;
    }
    else if(OsService_ExtendedErrorCheck((NULL_PTR != TaskDynPtr->LockList) && (OS_LOCKTYPE_SPINLOCK == TaskDynPtr->LockList->LockType)))
    {
        Status = E_OS_SPINLOCK;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else
    {
        OsIsr_SuspendISR(&Level);

        TaskDynPtr->EventWait = Mask;
        if(0 != (TaskDynPtr->EventWait & TaskDynPtr->EventSet))
        {
            if (OsTp_PassTimeFrameCheck(TaskTpConfig))
            {
                TaskEnterWaitState = FALSE;
                TaskDynPtr->EventWait = 0;
                OsTp_ResetAndResume(TaskTpConfig, TaskTpConfig);
            }
        }

        if (TaskEnterWaitState)
        {
            OsTask_RemoveTaskFromScheduler();
            TaskDynPtr->State = WAITING;
#if (OS_ARTI_TRACE_TASK == STD_ON)
            {
                /* within OsIsr_SuspendISR of WaitEvent: NOSUSP */
                CoreIdType ArtiCore = Os_Inf_GetCoreId();
                TaskDynPtr->ArtiState = OS_ARTI_TASK_WAITING;
                OS_ARTI_TASK_WAIT(ArtiCore, SchedulerPtr->CurrentTask);
            }
#endif
            OsTask_DoScheduling(SAVING_CONTEXT);
            /*Tp Reset.*/
            OsTp_ResetAfterWait(TaskTpConfig);
        }

        OsIsr_ResumeISR(Level);
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterOne(OS_SERVICEID_WAITEVENT, (InputParaType)Mask);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(WaitEvent, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_WAITEVENT);

    return Status;
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* OSEK 13.5.3.1 SetEvent */
FUNC(StatusType, OS_CODE) SetEvent
(
    TaskType TaskID,
    EventMaskType Mask
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsEvent_Internal_SetEvent(TaskID, Mask);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsEvent_Internal_SetEvent(TaskID, Mask);
    }

    return Status;
}

/* [SWS_Os_91023] */
FUNC(void, OS_CODE) SetEventAsyn
(
    TaskType TaskID,
    EventMaskType Mask
)
{

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        OsEvent_Internal_SetEventAsyn(TaskID, Mask);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        OsEvent_Internal_SetEventAsyn(TaskID, Mask);
    }

}

/* OSEK 13.5.3.2 ClearEvent */
FUNC(StatusType, OS_CODE) ClearEvent
(
    EventMaskType Mask
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsEvent_Internal_ClearEvent(Mask);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsEvent_Internal_ClearEvent(Mask);
    }

    return Status;
}

/* OSEK 13.5.3.3 GetEvent */
FUNC(StatusType, OS_CODE) GetEvent
(
    TaskType TaskID,
    EventMaskRefType Event
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsEvent_Internal_GetEvent(TaskID, Event);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsEvent_Internal_GetEvent(TaskID, Event);
    }

    return Status;
}

/* OSEK 13.5.3.4 WaitEvent */
FUNC(StatusType, OS_CODE) WaitEvent
(
    EventMaskType Mask
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsEvent_Internal_WaitEvent(Mask);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsEvent_Internal_WaitEvent(Mask);
    }

    return Status;
}

FUNC(StatusType, OS_CODE) OsEvent_SetEvent
(
    TaskType TaskID,
    EventMaskType Mask
)
{
    StatusType Status;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskConPtr;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) ObjectInfo;
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_CONST)  ObjectTpCfg;

    Status = E_OK;
    TaskDynPtr = OsTask_GetTaskDyn(TaskID);

    if(OsService_ExtendedErrorCheck(SUSPENDED == TaskDynPtr->State))
    {
        /* Events can not be set as the referenced task is in the suspended State */
        Status =  E_OS_STATE;
    }
    else
    {
        TaskDynPtr->EventSet |= Mask;
        if((0 != (TaskDynPtr->EventSet & TaskDynPtr->EventWait)) && (WAITING == TaskDynPtr->State))
        {
            /*Time Frame Check.*/
            TaskConPtr = OsTask_GetTaskConst(TaskID);
            ObjectInfo = OsApp_GetSpecific_ObjectInfo(TaskConPtr->ObjectID);
            ObjectTpCfg = (*(ObjectInfo->ObjectDataInfo.ObjectContextInfoPtr))->TpInfoPtr;
            if (OsTp_PassTimeFrameCheck(ObjectTpCfg))
            {
#if (OS_ARTI_TRACE_TASK == STD_ON)
                {
                    /* Executed on the task's core (cross-core SetEvent is a service call to that core, run by
                       the service ISR2): suspend here so that the NOSUSP context holds */
                    Os_IsrLevelType ArtiLevel;
                    CoreIdType ArtiCore;
                    OsIsr_SuspendISR(&ArtiLevel);
                    ArtiCore = Os_Inf_GetCoreId();
                    TaskDynPtr->ArtiState = OS_ARTI_TASK_RELEASED;
                    OS_ARTI_TASK_RELEASE(ArtiCore, TaskID);
                    OsIsr_ResumeISR(ArtiLevel);
                }
#endif
                /*Do Time Frame at OsTask_AddTaskToScheduler.*/
                OsTask_AddTaskToScheduler(TaskID);
                TaskDynPtr->EventWait = 0UL;
                TaskDynPtr->State = READY;
            }
        }
    }
    return Status;
}

FUNC(StatusType, OS_CODE) OsEvent_GetEvent
(
    TaskType TaskID,
    EventMaskRefType Event
)
{
    StatusType Status;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;

    Status = E_OK;
    TaskDynPtr = OsTask_GetTaskDyn(TaskID);

    if(OsService_ExtendedErrorCheck(SUSPENDED == TaskDynPtr->State))
    {
        /* Events can not be set as the referenced task is in the suspended State */
        Status =  E_OS_STATE;
    }
    else
    {
        *Event = TaskDynPtr->EventSet;
    }
    return Status;
}

