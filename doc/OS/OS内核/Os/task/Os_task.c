/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_task.c
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
#include "Os_task.h"
#include "Os_kernel.h"
#include "Os_hook.h"
#include "Os_resource.h"
#include "Os_spinlock.h"
#include "Os_lock.h"
#include "Os_task_Lcfg.h"

#include "Os_isr_Cfg.h"
#include "Os_isr.h"
#include "Os.h"
#include "Os_services.h"
#include "Os_application.h"
#include "Os_compiler_types.h"
#include "Os_hook_Cfg.h"
#include "Os_hook_Lcfg.h"
#include "Os_lock_types.h"
#include "Os_context.h"
#include "Os_timingprotection.h"
#include "Os_ioc.h"
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
#define OS_START_SEC_CODE_QM_GLOBAL
#include "Os_memmap.h"
/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : OsTask_Internal_ActivateTask
*   Service ID              : None.
*   Description             : Activate Task under kernel
*   Parameters in           : TaskID
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsTask_Internal_ActivateTask
(
    TaskType TaskID
);

/****************************************************************************************************
*   Function Name           : OsTask_Internal_ActivateTask
*   Service ID              : None.
*   Description             : Terminate Task under kernel
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsTask_Internal_TerminateTask
(
    void
);

/****************************************************************************************************
*   Function Name           : OsTask_Internal_ChainTask
*   Service ID              : None.
*   Description             : Chain Task under kernel
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsTask_Internal_ChainTask
(
    TaskType TaskID
);

/****************************************************************************************************
*   Function Name           : OsTask_Internal_GetTaskID
*   Service ID              : None.
*   Description             : Get Task ID under kernel
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsTask_Internal_GetTaskID
(
    TaskRefType TaskID
);

/****************************************************************************************************
*   Function Name           : OsTask_Internal_GetTaskState
*   Service ID              : None.
*   Description             : Get Task State under kernel
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsTask_Internal_GetTaskState
(
    TaskType TaskID,
    TaskStateRefType State
);

/****************************************************************************************************
*   Function Name           : OsTask_Internal_ActivateTaskAsyn
*   Service ID              : None.
*   Description             : Activate Task Asyn Task under kernel
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsTask_Internal_ActivateTaskAsyn
(
    TaskType TaskID
);

/****************************************************************************************************
*   Function Name           : OsTask_Internal_ReducePriority
*   Service ID              : None.
*   Description             : Reduce the Current Task Priority back to RunningPriority.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsTask_Internal_ReducePriority
(
    void
);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
#if (OS_ARTI_TRACE_TASK == STD_ON)
/****************************************************************************************************
*   ARTI task events (openspec add-arti-hook-tracing, design D4/D5). The event of a dispatch is chosen
*   from the ARTI shadow state ArtiState, not from the kernel State: entering an ISR2 sets the
*   interrupted task READY (OsTask_LeaveTaskLevel), and READY does not tell why a task is ready.
*   All callers hold the kernel lock (interrupts suspended): context NOSUSP.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsTask_Internal_ArtiActivate
(
    TaskType TaskID
)
{
    CoreIdType ArtiCore;
    Os_IsrLevelType ArtiLevel;

    /* Also reached from the cross-core service ISR: suspend here so that the NOSUSP context holds */
    OsIsr_SuspendISR(&ArtiLevel);
    ArtiCore = Os_Inf_GetCoreId();
    OsTask_GetTaskDyn(TaskID)->ArtiState = OS_ARTI_TASK_ACTIVATED;
    OS_ARTI_TASK_ACTIVATE(ArtiCore, TaskID);
    OsIsr_ResumeISR(ArtiLevel);
}

static FUNC(void, OS_CODE) OsTask_Internal_ArtiTerminate
(
    TaskType TaskID
)
{
    CoreIdType ArtiCore;
    Os_IsrLevelType ArtiLevel;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;

    OsIsr_SuspendISR(&ArtiLevel);
    ArtiCore = Os_Inf_GetCoreId();
    TaskDynPtr = OsTask_GetTaskDyn(TaskID);
    OS_ARTI_TASK_TERMINATE(ArtiCore, TaskID);
    /* Pending activations: the next instance is ready at once; its Activate was reported when it was activated */
    if(0U != TaskDynPtr->ActivationCount)
    {
        TaskDynPtr->ArtiState = OS_ARTI_TASK_ACTIVATED;
    }
    else
    {
        TaskDynPtr->ArtiState = OS_ARTI_TASK_SUSPENDED;
    }
    OsIsr_ResumeISR(ArtiLevel);
}

/* The running task loses the CPU without terminating or waiting: Preempt */
static FUNC(void, OS_CODE) OsTask_Internal_ArtiLeave
(
    TaskType CurrentTaskID,
    TaskType NextTaskID
)
{
    CoreIdType ArtiCore;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;

    TaskDynPtr = OsTask_GetTaskDyn(CurrentTaskID);
    if((CurrentTaskID != NextTaskID) && (OS_ARTI_TASK_RUNNING == TaskDynPtr->ArtiState))
    {
        Os_IsrLevelType ArtiLevel;
        OsIsr_SuspendISR(&ArtiLevel);
        ArtiCore = Os_Inf_GetCoreId();
        TaskDynPtr->ArtiState = OS_ARTI_TASK_PREEMPTED;
        OS_ARTI_TASK_PREEMPT(ArtiCore, CurrentTaskID);
        OsIsr_ResumeISR(ArtiLevel);
    }
}

/* The task gets the CPU: Start, Resume or Continue by the reason it is ready. Nothing when it was
   running already (return from an ISR2 or a hook to the same task). */
static FUNC(void, OS_CODE) OsTask_Internal_ArtiEnter
(
    TaskType TaskID
)
{
    CoreIdType ArtiCore;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;

    TaskDynPtr = OsTask_GetTaskDyn(TaskID);
    if(OS_ARTI_TASK_RUNNING != TaskDynPtr->ArtiState)
    {
        Os_IsrLevelType ArtiLevel;
        OsIsr_SuspendISR(&ArtiLevel);
        ArtiCore = Os_Inf_GetCoreId();
        switch(TaskDynPtr->ArtiState)
        {
            case OS_ARTI_TASK_PREEMPTED:
                OS_ARTI_TASK_RESUME(ArtiCore, TaskID);
                break;
            case OS_ARTI_TASK_RELEASED:
                OS_ARTI_TASK_CONTINUE(ArtiCore, TaskID);
                break;
            default:
                /* Activated; any other state is an inconsistency the event stream check reports */
                OS_ARTI_TASK_START(ArtiCore, TaskID);
                break;
        }
        TaskDynPtr->ArtiState = OS_ARTI_TASK_RUNNING;
        OsIsr_ResumeISR(ArtiLevel);
    }
}
#endif

FUNC(StatusType, OS_CODE) OsTask_Internal_ActivateTask
(
    TaskType TaskID
)
{
    StatusType Status;
    Os_IsrLevelType Level;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) CurrentObjectInfo;
    Os_IocInterCoreServiceCallType ServiceCallCfg;

    CurrentObjectInfo = OsApp_GetCurrent_ObjectInfo();
    Status = E_OK;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_ACTIVATETASK);
    OS_ARTI_SC_BEGIN(ActivateTask, TaskID);

    if(OsService_ExtendedErrorCheck(TaskID >= TOTAL_TASK_NUM))
    {
        /* Task <TaskID> is invalid */
        Status =  E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_ACTIVATETASK)))
    {
        Status =  E_OS_CALLEVEL;
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
            /* Internal Activate Task on core */
            Status = OsTask_ActivateTask(TaskID);
            /* Save the context and do scheduling */
            if(Status == E_OK && (CurrentObjectInfo->ObjectType == OBJECT_TASK))
            {
                OsTask_DoScheduling(SAVING_CONTEXT);
            }
               OsIsr_ResumeISR(Level);
        }
        else
        {
            /* Cross core service call */
            ServiceCallCfg.ServiceId = OS_SERVICEID_ACTIVATETASK;
            ServiceCallCfg.EntryAddress = (uint32)OsTask_ActivateTask;
            ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(OsTask_GetTaskConst(TaskID)->ObjectID);
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)TaskID;
            ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
            Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterOne(OS_SERVICEID_ACTIVATETASK, (InputParaType)TaskID);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(ActivateTask, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_ACTIVATETASK);

    return Status;
}

#if (OS_ARTI_TRACE_SERVICECALLS == STD_ON)
static FUNC(StatusType, OS_CODE) OsTask_TerminateTaskBody
(
    void
);

/* TerminateTask called by the application. OsTask_ErrorReturn (task returned without TerminateTask) is
   not a service call and calls OsTask_TerminateTaskBody directly. */
FUNC(StatusType, OS_CODE) OsTask_Internal_TerminateTask
(
    void
)
{
    StatusType Status;
    TaskType ArtiTask;
    OS_ARTI_SC_DECL

    ArtiTask = OsTask_GetSchedulerDyn()->CurrentTask;
    OS_ARTI_SC_BEGIN(TerminateTask, ArtiTask);
    /* returns only on error */
    Status = OsTask_TerminateTaskBody();
    OS_ARTI_SC_END(TerminateTask, Status);
    return Status;
}
#else
#define OsTask_TerminateTaskBody OsTask_Internal_TerminateTask
#endif

FUNC(StatusType, OS_CODE) OsTask_TerminateTaskBody
(
    void
)
{
    StatusType Status = E_OK;
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;
    Os_IsrLevelType Level;

    OsOrti_ServiceStart(OS_SERVICEID_TERMINATETASK);

    SchedulerPtr = OsTask_GetSchedulerDyn();
    TaskDynPtr = OsTask_GetTaskDyn(SchedulerPtr->CurrentTask);

    if(OsService_ExtendedErrorCheck((NULL_PTR != TaskDynPtr->LockList) && (OS_LOCKTYPE_RESOURCE == TaskDynPtr->LockList->LockType)))
    {
        /* Calling task still occupies resources */
        Status = E_OS_RESOURCE;
    }
    else if(OsService_ExtendedErrorCheck((NULL_PTR != TaskDynPtr->LockList) && (OS_LOCKTYPE_SPINLOCK == TaskDynPtr->LockList->LockType)))
    {
        Status = E_OS_SPINLOCK;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_TERMINATETASK)))
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
        OsIsr_SuspendISR(&Level);
        TaskDynPtr->ActivationCount--;
        /* Reset event flag */
        TaskDynPtr->EventSet = 0;
        TaskDynPtr->EventWait = 0;
        /* if the activation count is not zero it still should be ready State */
        if(0 == TaskDynPtr->ActivationCount)
        {
            TaskDynPtr->State = SUSPENDED;
        }
#if (OS_ARTI_TRACE_TASK == STD_ON)
        OsTask_Internal_ArtiTerminate(SchedulerPtr->CurrentTask);
#endif
        /* Remove the task from Scheduler */
        OsTask_RemoveTaskFromScheduler();
        /* Reload the context to origin and scheduling */
        OsTask_DoScheduling(NOT_SAVING_CONTEXT);
        OsIsr_ResumeISR(Level);
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterZero(OS_SERVICEID_TERMINATETASK);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OsOrti_ServiceEnd(OS_SERVICEID_TERMINATETASK);

    return Status;
}

FUNC(StatusType, OS_CODE) OsTask_Internal_ChainTask
(
    TaskType TaskID
)
{
    /* This code is similar to ActivateTask + TerminateTask */
    StatusType Status;
    boolean DoSchedule;
    Os_IsrLevelType Level;
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskCurrentDynPtr;
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskConPtr;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) ObjectInfo;
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_CONST)  ObjectTpCfg;
    Os_IocInterCoreServiceCallType ServiceCallCfg;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_CHAINTASK);
    OS_ARTI_SC_BEGIN(ChainTask, TaskID);

    Status = E_OK;
    DoSchedule = TRUE;
    SchedulerPtr = OsTask_GetSchedulerDyn();
    TaskCurrentDynPtr = OsTask_GetTaskDyn(SchedulerPtr->CurrentTask);

    if(OsService_ExtendedErrorCheck(TaskID >= TOTAL_TASK_NUM))
    {
        /* Task <TaskID> is invalid */
        Status =  E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck((NULL_PTR != TaskCurrentDynPtr->LockList) && (OS_LOCKTYPE_RESOURCE == TaskCurrentDynPtr->LockList->LockType)))
    {
        /* Calling task still occupies resources */
        Status = E_OS_RESOURCE;
    }
    else if(OsService_ExtendedErrorCheck((NULL_PTR != TaskCurrentDynPtr->LockList) && (OS_LOCKTYPE_SPINLOCK == TaskCurrentDynPtr->LockList->LockType)))
    {
        Status = E_OS_SPINLOCK;
    }
    else if(TRUE != OsApp_CheckObjectAccessingAppMask(OsTask_GetTaskConst(TaskID)->ObjectID) ||
            TRUE != OsApp_CheckObjectAppIsAccessiable(OsTask_GetTaskConst(TaskID)->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_CHAINTASK)))
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
        OsIsr_SuspendISR(&Level);
        TaskConPtr = OsTask_GetTaskConst(TaskID);
        ObjectInfo = OsApp_GetSpecific_ObjectInfo(TaskConPtr->ObjectID);
        ObjectTpCfg = (*(ObjectInfo->ObjectDataInfo.ObjectContextInfoPtr))->TpInfoPtr;
        if(SchedulerPtr->CurrentTask == TaskID)
        {
            /*Check Time Frame.*/
            if (OsTp_PassTimeFrameCheck(ObjectTpCfg))
            {
                /* Reset event flag */
                TaskCurrentDynPtr->EventSet = 0;
                TaskCurrentDynPtr->EventWait = 0;
                /*Reset Task TP Configurations.*/
                OsTp_KillObject(ObjectTpCfg);
                /* Remove then add to the scheduler */
                OsTask_RemoveTaskFromScheduler();
                OsTask_AddTaskToScheduler(TaskID);
#if (OS_ARTI_TRACE_TASK == STD_ON)
                /* ChainTask to itself: this instance terminates, a new one is activated */
                OsTask_Internal_ArtiTerminate(TaskID);
                OsTask_Internal_ArtiActivate(TaskID);
#endif
            }
            else
            {
                DoSchedule = FALSE;/* TimeFrameCheck failed, do not schedule Task.*/
            }
        }
        else
        {
            if(TRUE == OsKernel_CheckObjectBelongToCurrentCore(OsTask_GetTaskConst(TaskID)->ObjectID))
            {
                Status = OsTask_ActivateTask(TaskID);
            }
            else
            {
                /* Cross core service call */
                ServiceCallCfg.ServiceId = OS_SERVICEID_ACTIVATETASK;
                ServiceCallCfg.EntryAddress = (uint32)OsTask_ActivateTask;
                ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(OsTask_GetTaskConst(TaskID)->ObjectID);
                ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)TaskID;
                ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
                ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
                Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
            }
            if(E_OK == Status)
            {
                TaskCurrentDynPtr->ActivationCount--;
                OsTask_RemoveTaskFromScheduler();
                /* Change the task State to Suspended and remove the task if current task has no activation count */
                if(0 == TaskCurrentDynPtr->ActivationCount)
                {
                    TaskCurrentDynPtr->State = SUSPENDED;
                }
#if (OS_ARTI_TRACE_TASK == STD_ON)
                /* The target was reported as activated (on its core) before the caller terminates */
                OsTask_Internal_ArtiTerminate(SchedulerPtr->CurrentTask);
#endif
            }
        }

        if (DoSchedule && (E_OK == Status))
        {
            /* Reload the context for the current Task and scheduling */
            OsTask_DoScheduling(NOT_SAVING_CONTEXT);
        }
        OsIsr_ResumeISR(Level);
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterOne(OS_SERVICEID_CHAINTASK, (InputParaType)TaskID);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(ChainTask, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_CHAINTASK);

    return Status;
}

FUNC(StatusType, OS_CODE) OsTask_Internal_Schedule
(
    void
)
{
    StatusType Status;
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_SCHEDULE);
    OS_ARTI_SC_BEGIN(Schedule, 0U);

    Status = E_OK;
    SchedulerPtr = OsTask_GetSchedulerDyn();
    TaskDynPtr =OsTask_GetTaskDyn(SchedulerPtr->CurrentTask);

    if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_SCHEDULE)))
    {
        /* Call at interrupt level */
        Status = E_OS_CALLEVEL;
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
        /* Reduce current priority to home priority*/
        OsTask_Internal_ReducePriority();
        /* Do not Change the context of the current task and scheduling */
        OsTask_DoScheduling(SAVING_CONTEXT);
        OsIsr_ResumeISR(Level);
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterZero(OS_SERVICEID_SCHEDULE);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(Schedule, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_SCHEDULE);

    return Status;
}

FUNC(StatusType, OS_CODE) OsTask_Internal_GetTaskState
(
    TaskType TaskID,
    TaskStateRefType State
)
{
    StatusType Status;
    Os_IsrLevelType Level;
    Os_IocInterCoreServiceCallType ServiceCallCfg;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_GETTASKSTATE);
    OS_ARTI_SC_BEGIN(GetTaskState, TaskID);

    Status = E_OK;

    if(OsService_ExtendedErrorCheck(TaskID >= TOTAL_TASK_NUM))
    {
        /* Task <TaskID> is invalid */
        Status =  E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_GETTASKSTATE)))
    {
        /* Call at interrupt level */
        Status = E_OS_CALLEVEL;
    }
    else if(TRUE != OsApp_CheckObjectAccessingAppMask(OsTask_GetTaskConst(TaskID)->ObjectID) ||
            TRUE != OsApp_CheckObjectAppIsAccessiable(OsTask_GetTaskConst(TaskID)->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if(OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(OsService_ExtendedErrorCheck(NULL_PTR == State))
    {
        Status = E_OS_ILLEGAL_ADDRESS;
    }
    else
    {
        if(TRUE == OsKernel_CheckObjectBelongToCurrentCore(OsTask_GetTaskConst(TaskID)->ObjectID))
        {
            OsIsr_SuspendISR(&Level);
            Status = OsTask_GetTaskState(TaskID, State);
            OsIsr_ResumeISR(Level);
        }
        else
        {
            /* Cross core service call */
            ServiceCallCfg.ServiceId = OS_SERVICEID_GETTASKSTATE;
            ServiceCallCfg.EntryAddress = (uint32)OsTask_GetTaskState;
            ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(OsTask_GetTaskConst(TaskID)->ObjectID);
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)TaskID;
            ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)State;
            ServiceCallCfg.OutputParmMask = OS_IOC_OUTPUT_PARM1_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
            Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
            *State = (TaskStateType)ServiceCallCfg.OutParameter.OutParm[0];
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_GETTASKSTATE, (InputParaType)TaskID, (InputParaType)State);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(GetTaskState, (E_OK == Status) ? (uint32)(*State) : OS_ARTI_SC_INVALID);
    OsOrti_ServiceEnd(OS_SERVICEID_GETTASKSTATE);

    return Status;
}

FUNC(StatusType, OS_CODE) OsTask_Internal_GetTaskID
(
    TaskRefType TaskID
)
{
    StatusType Status;
    Os_IsrLevelType Level;
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_GETTASKID);
    OS_ARTI_SC_BEGIN(GetTaskID, 0U);

    Status = E_OK;
    *TaskID = INVALID_TASK;

    if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_GETTASKID)))
    {
        Status = E_OS_CALLEVEL;
    }
    else if(OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(OsService_ExtendedErrorCheck(NULL_PTR == TaskID))
    {
        Status = E_OS_ILLEGAL_ADDRESS;
    }
    else
    {
        /* Get the current object if it is not task return INVALID_TASK */
        SchedulerPtr = OsTask_GetSchedulerDyn();
        *TaskID = SchedulerPtr->CurrentTask;
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterOne(OS_SERVICEID_GETTASKID, (InputParaType)TaskID);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(GetTaskID, (E_OK == Status) ? (uint32)(*TaskID) : OS_ARTI_SC_INVALID);
    OsOrti_ServiceEnd(OS_SERVICEID_GETTASKID);

    return Status;
}

FUNC(void, OS_CODE) OsTask_Internal_ActivateTaskAsyn
(
    TaskType TaskID
)
{
    StatusType Status;
    Os_IsrLevelType Level;
    Os_IocInterCoreServiceCallType ServiceCallCfg;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_ACTIVATETASKASYN);
    OS_ARTI_SC_BEGIN(ActivateTaskAsyn, TaskID);

    Status = E_OK;

    if(OsService_ExtendedErrorCheck(TaskID >= TOTAL_TASK_NUM))
    {
        /* Task <TaskID> is invalid */
        Status =  E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_ACTIVATETASKASYN)))
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
        /* Cross core service call */
        ServiceCallCfg.ServiceId = OS_SERVICEID_ACTIVATETASK;
        ServiceCallCfg.EntryAddress = (uint32)OsTask_ActivateTask;
        ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(OsTask_GetTaskConst(TaskID)->ObjectID);
        ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)TaskID;
        ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
        ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_ASYNC;
        Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterOne(OS_SERVICEID_ACTIVATETASKASYN, (InputParaType)TaskID);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(ActivateTaskAsyn, 0U);
    OsOrti_ServiceEnd(OS_SERVICEID_ACTIVATETASKASYN);
}

static FUNC(void, OS_CODE) OsTask_Internal_ReducePriority
(
    void
)
{
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskConPtr;

    SchedulerPtr = OsTask_GetSchedulerDyn();
    TaskConPtr = OsTask_GetTaskConst(SchedulerPtr->CurrentTask);
    /* Reduce the current Priority to task home priority */
    SchedulerPtr->CurrentPriority = TaskConPtr->HomePriority;
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* OSEK 13.2.3.1 ActivateTask */
FUNC(StatusType, OS_CODE) ActivateTask
(
    TaskType TaskID
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsTask_Internal_ActivateTask(TaskID);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsTask_Internal_ActivateTask(TaskID);
    }

    return Status;
}

/* OSEK 13.2.3.2 TerminateTask */
FUNC(StatusType, OS_CODE) TerminateTask
(
    void
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsTask_Internal_TerminateTask();
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsTask_Internal_TerminateTask();
    }

    return Status;
}

/* OSEK 13.2.3.3 ChaintTask */
FUNC(StatusType, OS_CODE) ChainTask
(
    TaskType TaskID
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsTask_Internal_ChainTask(TaskID);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsTask_Internal_ChainTask(TaskID);
    }

    return Status;
}

/* OSEK 13.2.3.4 Schedule */
FUNC(StatusType, OS_CODE) Schedule
(
    void
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsTask_Internal_Schedule();
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsTask_Internal_Schedule();
    }

    return Status;
}

/* OSEK 13.2.3.5 GetTaskID */
FUNC(StatusType, OS_CODE) GetTaskID
(
    TaskRefType TaskID
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsTask_Internal_GetTaskID(TaskID);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsTask_Internal_GetTaskID(TaskID);
    }

    return Status;
}

FUNC(StatusType, OS_CODE) GetTaskState
(
    TaskType TaskID,
    TaskStateRefType State
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsTask_Internal_GetTaskState(TaskID, State);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsTask_Internal_GetTaskState(TaskID, State);
    }

    return Status;
}

/* [SWS_Os_91022] */
FUNC(void, OS_CODE) ActivateTaskAsyn
(
    TaskType TaskID
)
{

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        OsTask_Internal_ActivateTaskAsyn(TaskID);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        OsTask_Internal_ActivateTaskAsyn(TaskID);
    }
}

FUNC(void, OS_CODE) OsTask_DoScheduling
(
    Os_SchedulingChoiceType SchedulingChoice
)
{
    uint32 Popi;
    TaskType NextTaskID;
    uint32 PriorityLevel;
    TaskType CurrentTaskID;
    uint32 CalculatePriority;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) NextObjectInfo;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) CurrentObjectInfo;

    P2VAR(Os_FifoQueueType, TYPEDEF,OS_VAR) CurrentPriorityQueue;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynCurrentPtr;
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskConNextPtr;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynNextPtr;
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;

    /* pointer to Os_SchedulerProperty */
    SchedulerPtr = OsTask_GetSchedulerDyn();
    /* indicate current Task */
    CurrentTaskID = SchedulerPtr->CurrentTask;
    /* indicate priority queue */
    CurrentPriorityQueue =  SchedulerPtr->FifoQueue;
    /* indicate current task dynamic variable */
    TaskDynCurrentPtr = OsTask_GetTaskDyn(CurrentTaskID);
    /* the parent level of task priority */
    PriorityLevel = 31 - Os_Inf_clz(SchedulerPtr->PriorityUpperArray);
    /* the real priority of the highest task */
    CalculatePriority = (31 - (Os_Inf_clz(SchedulerPtr->PriorityLowerArray[PriorityLevel])))
        + 32 * PriorityLevel;
    /* indicate the current object */
    CurrentObjectInfo = OsApp_GetCurrent_ObjectInfo();

    /* Check whether it need to Switch to another task */
    if((CalculatePriority > SchedulerPtr->CurrentPriority)
        || (0u == CalculatePriority)
        || (NOT_SAVING_CONTEXT == SchedulingChoice)
        || (WAITING == TaskDynCurrentPtr->State))
    {
        /* set the new calculated priority to global variable */
        if(((OBJECT_ISR == CurrentObjectInfo->ObjectType)||(OBJECT_KERNELHOOK == CurrentObjectInfo->ObjectType)
                ||(OBJECT_APPHOOK == CurrentObjectInfo->ObjectType))
                && (0xFFFFFFFF == SchedulerPtr->CurrentPriority))
        {
            NextTaskID = SchedulerPtr->CurrentTask;
        }
        else
        {
            SchedulerPtr->CurrentPriority = CalculatePriority;
            Popi = (CurrentPriorityQueue[SchedulerPtr->CurrentPriority].PopIndex) %
                    (CurrentPriorityQueue[SchedulerPtr->CurrentPriority].QueueSize);
            /* Get the NextTaskID and change the ID on global structure */
            NextTaskID = CurrentPriorityQueue[SchedulerPtr->CurrentPriority].Buffer[Popi];

        }

        if(OBJECT_TASK == CurrentObjectInfo->ObjectType)
        {
            OsHook_CallPostTaskHook();
            OsOrti_TaskEnd();
        }
#if (OS_ARTI_TRACE_TASK == STD_ON)
        OsTask_Internal_ArtiLeave(CurrentTaskID, NextTaskID);
#endif
        /* Change the ID on global structure */
        SchedulerPtr->CurrentTask = NextTaskID;
        /* Get the next task Config and dynamic Structure */
        TaskConNextPtr =  OsTask_GetTaskConst(NextTaskID);
        TaskDynNextPtr = OsTask_GetTaskDyn(NextTaskID);

        /* Change the current priority to task Running Priority */
        if(TaskConNextPtr->HomePriority < TaskConNextPtr->RunningPriority)
        {
            SchedulerPtr->CurrentPriority = TaskConNextPtr->RunningPriority;
        }
        /* Change the next task status to running(Do not change waiting and suspended State), change current task status to ready */
        if(RUNNING == TaskDynCurrentPtr->State)
        {
            TaskDynCurrentPtr->State = READY;
        }
        TaskDynNextPtr->State = RUNNING;
        /* Change the running ObjectID */
        OsApp_ChangeCurrent_AppInfo(TaskConNextPtr->ObjectID);
        NextObjectInfo = OsApp_GetCurrent_ObjectInfo();
#if (OS_ARTI_TRACE_TASK == STD_ON)
        OsTask_Internal_ArtiEnter(NextTaskID);
#endif

        if(OBJECT_TASK == NextObjectInfo->ObjectType)
        {
            OsHook_CallPreTaskHook();
            OsOrti_TaskStart(NextTaskID);
        }
        if(SchedulingChoice == NOT_SAVING_CONTEXT)
        {
            /* Init the current task context and switch to next task */
            if(OBJECT_TASK == CurrentObjectInfo->ObjectType)
            {
                Os_Hal_ContextInit(*(CurrentObjectInfo->ObjectDataInfo.ObjectContextInfoPtr),
                    (*(CurrentObjectInfo->ObjectDataInfo.ObjectContextInfoPtr))->ContextInfoPtr);
            }
        }

        /* Save previous task context and change to the next task */
        Os_Hal_ContextSwitch(NextObjectInfo, CurrentObjectInfo, SchedulingChoice);
    }
}

FUNC(void, OS_CODE) OsTask_AddTaskToScheduler
(
    TaskType TaskID
)
{
    uint32 InsertTaskPriority;
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;
    P2VAR(Os_FifoQueueType, TYPEDEF, OS_VAR) FifoQueuePtr;
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskConPtr;

    SchedulerPtr = OsTask_GetSchedulerDyn();
    TaskConPtr = OsTask_GetTaskConst(TaskID);
    FifoQueuePtr = &SchedulerPtr->FifoQueue[TaskConPtr->HomePriority];

    /* Insert the priority into the priority Array */
    InsertTaskPriority = TaskConPtr->HomePriority;
    SchedulerPtr->PriorityUpperArray |= (1 << (InsertTaskPriority/32UL));
    SchedulerPtr->PriorityLowerArray[InsertTaskPriority/32UL] |= (1<<(InsertTaskPriority % 32UL));

    /* Push task in to Scheduler list*/
    OsTask_FifoPush(FifoQueuePtr, TaskID);
}

FUNC(void, OS_CODE) OsTask_RemoveTaskFromScheduler
(
    void
)
{

    uint32 RemoveTaskPriority;
    TaskType RemoveTask;
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskConPtr;
    P2VAR(Os_FifoQueueType, TYPEDEF, OS_VAR) FifoQueuePtr;

    SchedulerPtr = OsTask_GetSchedulerDyn();
    TaskConPtr = OsTask_GetTaskConst(SchedulerPtr->CurrentTask);

    /* Get the priority of the task to be removed */
    RemoveTaskPriority = TaskConPtr->HomePriority;
    FifoQueuePtr = &SchedulerPtr->FifoQueue[RemoveTaskPriority];

    /* Pop the task from the scheduler's buffer and update the pushIndex and popIndex */
    OsTask_FifoPop(FifoQueuePtr, &RemoveTask);

    /* If the queue is empty, update the PriorityArray to clear the bit for the given priority */
    if(FifoQueuePtr->PushIndex == FifoQueuePtr->PopIndex)
    {
        SchedulerPtr->PriorityLowerArray[RemoveTaskPriority/32UL] &= ~(1<<(RemoveTaskPriority % 32UL));
        if(0 == (SchedulerPtr->PriorityLowerArray[RemoveTaskPriority/32UL]))
        {
        	Os_AtomicBitClear(&SchedulerPtr->PriorityUpperArray, RemoveTaskPriority/32UL);
        }
    }
}

FUNC(void, OS_CODE) OsTask_TaskInit
(
    TaskType TaskID,
    AppModeType AppMode
)
{
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskConPtr;

    TaskDynPtr = OsTask_GetTaskDyn(TaskID);
    TaskConPtr = OsTask_GetTaskConst(TaskID);

    /* Set the Task Dynamic Variable to 0 */
    TaskDynPtr->ActivationCount = 0;
    TaskDynPtr->EventSet = 0;
    TaskDynPtr->EventWait = 0;
    TaskDynPtr->LockList = NULL_PTR;
    TaskDynPtr->SpinlockOccupied = NULL_PTR;

    /* According to AutoStart, Add to the Scheduler and init the state of Task*/
    if(AppMode & TaskConPtr->AutoStart)
    {
        TaskDynPtr->State = READY;
        TaskDynPtr->ActivationCount++;
#if (OS_ARTI_TRACE_TASK == STD_ON)
        OsTask_Internal_ArtiActivate(TaskID);
#endif
        OsTask_AddTaskToScheduler(TaskID);
    }
    else
    {
        TaskDynPtr->State = SUSPENDED;
#if (OS_ARTI_TRACE_TASK == STD_ON)
        TaskDynPtr->ArtiState = OS_ARTI_TASK_SUSPENDED;
#endif
    }
}

FUNC(void, OS_CODE) OsTask_SchedulerInit
(
    void
)
{
    uint32 Level;
    uint32 Index;
    uint32 BufferIndex;
    uint32 TotalPriorityLowerArrayNum;
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;

    TotalPriorityLowerArrayNum = (OsKernel_GetCurrentCoreTotalTaskPriorityNum() >> 5UL) + 1UL;
    SchedulerPtr = OsTask_GetSchedulerDyn();
    SchedulerPtr->CurrentPriority = 0;
    SchedulerPtr->CurrentTask = OsKernel_GetCoreIdleTask();
    SchedulerPtr->PriorityUpperArray = 0;
    SchedulerPtr->PriorityLowerArray = OsKernel_GetCurrentCoreAddressofBitArray();
    SchedulerPtr->FifoQueue = OsKernel_GetCurrentCoreTaskFifoQueuePtr();

    /* Init Scheduler variable */
    for(Index = 0; Index < TotalPriorityLowerArrayNum; Index++)
    {
        SchedulerPtr->PriorityLowerArray[Index] = 0;
    }

    for(Level = 0; Level < OsKernel_GetCurrentCoreTotalTaskPriorityNum(); Level++)
    {
        /* Set all buffers in Scheduler to INVALID_TASK */
        SchedulerPtr->FifoQueue[Level].Buffer = (uint32 *)OsKernel_GetCurrentCoreTaskPriBufferPtr()[Level];
        SchedulerPtr->FifoQueue[Level].QueueSize = OsKernel_GetCurrentCoreTaskQueueSizePtr()[Level];
        for(BufferIndex = 0; BufferIndex < OsKernel_GetCurrentCoreTaskQueueSizePtr()[Level]; BufferIndex++)
        {
            SchedulerPtr->FifoQueue[Level].Buffer[BufferIndex] = INVALID_TASK;
        }
        SchedulerPtr->FifoQueue[Level].PopIndex= 0;
        SchedulerPtr->FifoQueue[Level].PushIndex= 0;

    }
}

FUNC(void, OS_CODE) OsTask_FifoPush
(
    P2VAR(Os_FifoQueueType, TYPEDEF, OS_VAR) FifoQueuePtr,
    uint32 InputItem
)
{
    /* Check if buffer is full */
    if (((FifoQueuePtr->PushIndex + 1) % (FifoQueuePtr->QueueSize)) == FifoQueuePtr->PopIndex) {
        /* Buffer is full, return failure status */
        CodeFreeze();
    }
    else
    {
        /* Insert data into the buffer */
        FifoQueuePtr->Buffer[FifoQueuePtr->PushIndex] = InputItem;
        /* Update pushIndex and wrap around using the buffer size queueSize*/
        FifoQueuePtr->PushIndex = (FifoQueuePtr->PushIndex + 1) % (FifoQueuePtr->QueueSize);
        /* Operation successful, return success status */
    }
}

FUNC(void, OS_CODE) OsTask_FifoPop
(
    P2VAR(Os_FifoQueueType, TYPEDEF, OS_VAR) FifoQueuePtr,
    P2VAR(uint32, TYPEDEF, OS_VAR) OutputItemPtr
)
{

    /* Check if the buffer is empty */
    if (FifoQueuePtr->PushIndex == FifoQueuePtr->PopIndex)
    {
        CodeFreeze();
    }
    else
    {
        /* Pop data from the buffer */
        *OutputItemPtr = FifoQueuePtr->Buffer[FifoQueuePtr->PopIndex];
        FifoQueuePtr->Buffer[FifoQueuePtr->PopIndex] = INVALID_TASK;
        /* Update popIndex and wrap around using the buffer size */
        FifoQueuePtr->PopIndex = (FifoQueuePtr->PopIndex + 1) % (FifoQueuePtr->QueueSize);
        /* Operation successful, return success status */
    }
}

FUNC(void, OS_CODE) OsTask_ErrorReturn
(
    void
)
{
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;
    P2VAR(Os_LockConfigRefType, TYPEDEF, OS_VAR) LockListPtr;

    SchedulerPtr = OsTask_GetSchedulerDyn();
    TaskDynPtr = OsTask_GetTaskDyn(SchedulerPtr->CurrentTask);
    LockListPtr = &(TaskDynPtr->LockList);

    OsHook_SetErrorParameterZero(OS_SERVICEID_TERMINATETASK);
    OsHook_CallErrorHook(E_OS_MISSINGEND);
    while(*LockListPtr != NULL_PTR)
    {

        if((*LockListPtr)->LockType == OS_LOCKTYPE_RESOURCE)
        {
            OsResource_ResourceDeInit((*LockListPtr)->LockId);
        }
        else
        {
            OsSpinlock_SpinlockDeInit((*LockListPtr)->LockId);
        }
        OsLock_ListPop(LockListPtr);
    }
    OsTask_Internal_TerminateTask();
}

FUNC(void, OS_CODE) OsTask_LeaveTaskLevel
(
    void
)
{
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;

    OsHook_CallPostTaskHook();
    OsOrti_TaskEnd();

    SchedulerPtr = OsTask_GetSchedulerDyn();
    TaskDynPtr = OsTask_GetTaskDyn(SchedulerPtr->CurrentTask);

    /* Set the Task to Ready since it's ISR2 running */
    TaskDynPtr->State = READY;
}

FUNC(TaskType, OS_CODE) OsTask_GetCurrentTask
(
    void
)
{
    TaskType CurrentTask;
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;

    SchedulerPtr =  OsTask_GetSchedulerDyn();
    CurrentTask = SchedulerPtr->CurrentTask;

    return CurrentTask;
}

FUNC(P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR), OS_CODE) OsTask_GetTaskDyn
(
    TaskType TaskID
)
{
    return (Os_TaskConfigSet.TaskConfigPtr[TaskID]->Os_TaskRunningData);
}

FUNC(P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST), OS_CODE) OsTask_GetTaskConst
(
    TaskType TaskID
)
{
    return Os_TaskConfigSet.TaskConfigPtr[TaskID];
}

FUNC(P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR), OS_CODE) OsTask_GetSchedulerDyn
(
    void
)
{

    return OsKernel_GetCurrentCoreSchedulerDataInfo();
}

FUNC(StatusType, OS_CODE) OsTask_ActivateTask
(
    TaskType TaskID
)
{
    StatusType Status;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskConPtr;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) ObjectInfo;
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_CONST)  ObjectTpCfg;

    Status = E_OK;
    TaskDynPtr = OsTask_GetTaskDyn(TaskID);
    TaskConPtr = OsTask_GetTaskConst(TaskID);

    if(TaskConPtr->MaxActivationCount == TaskDynPtr->ActivationCount)
    {
        /* Too many task activations of <TaskID> */
        Status = E_OS_LIMIT;
    }
    else
    {
        ObjectInfo = OsApp_GetSpecific_ObjectInfo(TaskConPtr->ObjectID);
        ObjectTpCfg = (*(ObjectInfo->ObjectDataInfo.ObjectContextInfoPtr))->TpInfoPtr;
        if (OsTp_PassTimeFrameCheck(ObjectTpCfg))
        {
            TaskDynPtr->ActivationCount++;
            /* Check if the State is Suspend since wait, ready and running do not need to change the State */
            if(SUSPENDED == TaskDynPtr->State)
            {
                /* According to OSEK change the State of the task */
                TaskDynPtr->State = READY;
#if (OS_ARTI_TRACE_TASK == STD_ON)
                /* Before the task is queued; a multiple activation is not reported (state unchanged) */
                OsTask_Internal_ArtiActivate(TaskID);
#endif
            }
            /* Add task to the FIFO list */
            OsTask_AddTaskToScheduler(TaskID);
        }
    }
    return Status;
}

FUNC(StatusType, OS_CODE) OsTask_GetTaskState
(
    TaskType TaskID,
    TaskStateRefType State
)
{
    StatusType Status;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;

    Status = E_OK;
    TaskDynPtr = OsTask_GetTaskDyn(TaskID);
    *State = TaskDynPtr->State;

    return Status;
};

FUNC(void, OS_CODE) OsTask_GetLockList
(
    TaskType TaskID,
    P2P2VAR(Os_LockConfigRefType, TYPEDEF, OS_VAR)LockListPtr
)
{
    *LockListPtr = &(OsTask_GetTaskDyn(TaskID)->LockList);
}

FUNC(void,OS_CODE)OsTask_GetSpinLockList
(
    TaskType TaskID,
    P2P2VAR(Os_SpinlockConfigRefType, TYPEDEF, OS_VAR)SpinLockListPtr
)
{
    *SpinLockListPtr = &(OsTask_GetTaskDyn(TaskID)->SpinlockOccupied);
}

FUNC(void, OS_CODE)OsTask_LevelUpTaskPriority
(
    uint32 NewPriority,
    P2VAR(uint32, TYPEDEF, OS_VAR) CurrentPriorityPtr
)
{
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;
    P2VAR(Os_FifoQueueType, TYPEDEF, OS_VAR) CurrentPriorityQueue;

    SchedulerPtr = OsTask_GetSchedulerDyn();
    *CurrentPriorityPtr = SchedulerPtr->CurrentPriority;
    if (SchedulerPtr->CurrentPriority < NewPriority)
    {
        SchedulerPtr->CurrentPriority = NewPriority;
        if(0xFFFFFFFF != NewPriority)
        {
            /* indicate priority queue */
            CurrentPriorityQueue =  SchedulerPtr->FifoQueue;
            SchedulerPtr->PriorityUpperArray |= (1 << (NewPriority / 32UL));
            SchedulerPtr->PriorityLowerArray[NewPriority / 32UL] |= (1 << (NewPriority % 32UL));

            OsTask_FifoPush(&CurrentPriorityQueue[NewPriority], SchedulerPtr->CurrentTask);
        }
    }
}

FUNC(void, OS_CODE)OsTask_LevelDownTaskPriority
(
    uint32 NewPriority
)
{
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;
    P2VAR(Os_FifoQueueType, TYPEDEF, OS_VAR) CurrentPriorityQueue;
    P2VAR(Os_FifoQueueType, TYPEDEF, OS_VAR) FifoQueuePtr;

    TaskType PopTask;
    uint32 PreviousPriority;

    SchedulerPtr = OsTask_GetSchedulerDyn();
    /* indicate priority queue */
    CurrentPriorityQueue =  SchedulerPtr->FifoQueue;
    PreviousPriority = SchedulerPtr->CurrentPriority;
    SchedulerPtr->CurrentPriority = NewPriority;

    if((PreviousPriority != NewPriority) && (0xFFFFFFFF != PreviousPriority))
    {
        OsTask_FifoPop(&CurrentPriorityQueue[PreviousPriority], &PopTask);
        /* If the queue is empty, update the PriorityArray to clear the bit for the given priority */
        FifoQueuePtr = &SchedulerPtr->FifoQueue[PreviousPriority];
        if(FifoQueuePtr->PushIndex == FifoQueuePtr->PopIndex)
        {
            SchedulerPtr->PriorityLowerArray[PreviousPriority/32UL] &= ~(1<<(PreviousPriority % 32UL));
            if(0 == SchedulerPtr->PriorityLowerArray[PreviousPriority/32UL])
            {
                Os_AtomicBitClear(&SchedulerPtr->PriorityUpperArray, PreviousPriority / 32UL);
            }
        }
    }

}

FUNC(uint32 ,OS_CODE)OsTask_GetHomePriority
(
    TaskType TaskID
)
{
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskConPtr;

    TaskConPtr = OsTask_GetTaskConst(TaskID);
    return (TaskConPtr->HomePriority);
}

FUNC(void ,OS_CODE)OsTask_ActivateRestartTask
(
    TaskType TaskID
)
{
    StatusType Status;
    Os_IocInterCoreServiceCallType ServiceCallCfg;
    if(TaskID == INVALID_TASK)
    {
        CodeFreeze();
    }
    if(TRUE == OsKernel_CheckObjectBelongToCurrentCore(OsTask_GetTaskConst(TaskID)->ObjectID))
    {
        /* Internal Activate Task on core */
        Status = OsTask_ActivateTask(TaskID);
    }
    else
    {
        /* Cross core service call */
        ServiceCallCfg.ServiceId = OS_SERVICEID_ACTIVATETASK;
        ServiceCallCfg.EntryAddress = (uint32)OsTask_ActivateTask;
        ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(OsTask_GetTaskConst(TaskID)->ObjectID);
        ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)TaskID;
        ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
        ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
        Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
    }
    if (Status != E_OK)
    {
        CodeFreeze();
    }
}

FUNC(void ,OS_CODE)OsTask_TaskDeinit
(
    TaskType TaskID
)
{
    uint32 FifoEndPop;
    uint32 FifoOutput;
    Os_AppObjectRefType ObjectInfo;
    P2VAR(Os_FifoQueueType, TYPEDEF, OS_VAR) FifoList;
    P2VAR(Os_TaskDynamicType, TYPEDEF, OS_VAR) TaskDynPtr;
    P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) SchedulerPtr;
    P2VAR(Os_LockConfigRefType, TYPEDEF, OS_VAR) LockListPtr;
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskConPtr;
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_CONST) ObjectTpCfgPtr;

    SchedulerPtr = OsTask_GetSchedulerDyn();
    TaskDynPtr = OsTask_GetTaskDyn(TaskID);
    TaskConPtr = OsTask_GetTaskConst(TaskID);
    LockListPtr = &(TaskDynPtr->LockList);
    OsIoc_ClearSyncServiceCallFlag(TaskConPtr->ObjectID);
    ObjectInfo = OsApp_GetSpecific_ObjectInfo(TaskConPtr->ObjectID);

    /*Deinit TP Object.*/
    ObjectTpCfgPtr = (*(ObjectInfo->ObjectDataInfo.ObjectContextInfoPtr))->TpInfoPtr;
    OsTp_KillObject(ObjectTpCfgPtr);

    OsIsr_ResetIntApiCount(TaskConPtr->ObjectID);

    if(SUSPENDED != TaskDynPtr->State)
    {
        if(WAITING != TaskDynPtr->State)
        {
            FifoList = &SchedulerPtr->FifoQueue[TaskConPtr->HomePriority];
            FifoEndPop = FifoList->PushIndex;
            while(FifoList->PopIndex != FifoEndPop)
            {

                OsTask_FifoPop(FifoList, &FifoOutput);
                if(FifoOutput != TaskID)
                {
                    OsTask_FifoPush(FifoList, FifoOutput);
                }
            }
            /* If the queue is empty, update the PriorityArray to clear the bit for the given priority */
            if(FifoList->PushIndex == FifoList->PopIndex)
            {
                SchedulerPtr->PriorityLowerArray[TaskConPtr->HomePriority/32UL] &= ~(1<<(TaskConPtr->HomePriority % 32UL));
                if(0 == (SchedulerPtr->PriorityLowerArray[TaskConPtr->HomePriority/32UL]))
                {
                    Os_AtomicBitClear(&SchedulerPtr->PriorityUpperArray, TaskConPtr->HomePriority/32UL);
                }
            }
        }

        while(*LockListPtr != NULL_PTR)
        {
            FifoList = &SchedulerPtr->FifoQueue[OsResource_GetCeilingPriority((*LockListPtr)->LockId)];

            FifoEndPop = FifoList->PopIndex;
            while(FifoList->PushIndex != FifoEndPop)
            {
                OsTask_FifoPop(FifoList, &FifoOutput);
                if(FifoOutput != TaskID)
                {
                    OsTask_FifoPush(FifoList, FifoOutput);
                }
            }
            if((*LockListPtr)->LockType == OS_LOCKTYPE_RESOURCE)
            {
                OsResource_ResourceDeInit((*LockListPtr)->LockId);
            }
            else
            {
                OsSpinlock_SpinlockDeInit((*LockListPtr)->LockId);
            }
            OsLock_ListPop(LockListPtr);
        }

        TaskDynPtr->State = SUSPENDED;
        TaskDynPtr->ActivationCount = 0;
        TaskDynPtr->EventSet = 0;
        TaskDynPtr->EventWait = 0;
#if (OS_ARTI_TRACE_TASK == STD_ON)
        /* Forced termination (TerminateApplication, protection): Terminate from any state (design D10) */
        OsTask_Internal_ArtiTerminate(TaskID);
#endif
        Os_Hal_ContextInit(*(ObjectInfo->ObjectDataInfo.ObjectContextInfoPtr),
                (*(ObjectInfo->ObjectDataInfo.ObjectContextInfoPtr))->ContextInfoPtr);
    }
}

#define OS_STOP_SEC_CODE_QM_GLOBAL
#include "Os_memmap.h"
