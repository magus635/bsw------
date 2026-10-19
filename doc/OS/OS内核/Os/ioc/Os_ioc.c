/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_ioc.c
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
#include "Os_ioc.h"
#include "Os_ioc_types.h"
#include "Os_ioc_Cfg.h"
#include "Os_ioc_Lcfg.h"
#include "Os_task.h"
#include "Os_application.h"
#include "Os_application_types.h"
#include "Os_kernel.h"
#include "Os_context.h"
#include "Os_spinlock.h"
#include "Os_isr_Cfg.h"
#include "Os_isr.h"
#include "Os_isr_hal.h"
#include "Os_context.h"
#include "Os_context_Lcfg.h"
#include "Os_context_Cfg.h"
#include "Os_hook.h"
#include "Os_compiler_types.h"
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
*   Function Name           : OsIoc_Internal_CallCallback
*   Service ID              : None.
*   Description             : Internal function of ioc call callback.
*   Parameters in           : ObjectID: Callback object id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsIoc_Internal_CallCallback
(
    uint32 ObjectID
);

/****************************************************************************************************
*   Function Name           : OsIoc_Internal_CrossCoreServiceCall
*   Service ID              : None.
*   Description             : Internal function of OsIoc_CrossCoreServiceCall.
*   Parameters in           : ServiceCallCfg: Service call configuration.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsIoc_Internal_CrossCoreServiceCall
(
    Os_IocInterCoreServiceCallType ServiceCallCfg
);

/****************************************************************************************************
*   Function Name           : OsIoc_Internal_SyncServiceCallIsHandled
*   Service ID              : None.
*   Description             : Check whether sync service call request has been processed by receiver.
*   Parameters in           : ResultIndex: Result index of channel.
                              ReadIndex: Read index of channel.
                              TargetIndex: Index in channel of service to be waited.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : uint32: Result, 0: Not finished. 1: Finished.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(uint32, OS_CODE) OsIoc_Internal_SyncServiceCallIsHandled
(
    uint32 ResultIndex,
    uint32 ReadIndex,
    uint32 TargetIndex
);
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
static FUNC(void, OS_CODE) OsIoc_Internal_CallCallback
(
    uint32 ObjectID
)
{
    Os_IsrLevelType SuspendLevel;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CallbackObject;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObject;

    /* Suspend interrupt and save current interrupt level */
    OsIsr_SuspendISR(&SuspendLevel);
    /* Get current object info */
    CurrentObject = OsApp_GetCurrent_ObjectInfo();
    /* Get callback object info */
    CallbackObject = OsApp_GetSpecific_ObjectInfo(ObjectID);
    /* If current object is a task */
    if(OBJECT_TASK == CurrentObject->ObjectType)
    {
        OsTask_LeaveTaskLevel();
    }
    OsApp_ChangeCurrent_AppInfo(ObjectID);
    /* Initialize callback context */
    Os_Hal_ContextInit(*(CallbackObject->ObjectDataInfo.ObjectContextInfoPtr),
        (*(CallbackObject->ObjectDataInfo.ObjectContextInfoPtr))->ContextInfoPtr);
    /* Switch to callback */
    Os_Hal_ContextSwitch(CallbackObject, CurrentObject, SAVING_CONTEXT);
    OsIsr_ResumeISR(SuspendLevel);
}

static FUNC(StatusType, OS_CODE) OsIoc_Internal_CrossCoreServiceCall
(
    Os_IocInterCoreServiceCallType ServiceCallCfg
)
{
    StatusType Status;
    P2CONST(Os_IocInterCoreServiceChannelCfgType, AUTOMATIC, OS_CONST) ServiceChannelCfg;
    Os_IsrLevelType SuspendLevel;
    uint32 WriteIndex;
    uint32 ResultIndex;

    /* Suspend interrupt and save current interrupt level */
    OsIsr_SuspendISR(&SuspendLevel);

    ServiceChannelCfg = OsIoc_GetIocServiceChannelCfgPtr(Os_Inf_CompilerGetCoreID(), ServiceCallCfg.TargetCoreId);
    /* Handle previous unhandled result */
    ResultIndex = ServiceChannelCfg->RunningData->ResultIndex;
    while(ResultIndex != ServiceChannelCfg->RunningData->ReadIndex)
    {
        /* If is asynchronous service call */
        if((ServiceChannelCfg->ServiceContextBuffer[ResultIndex].ServiceType & OS_IOC_SERVICECALL_TYPE_MASK) == OS_IOC_SERVICECALL_ASYNC)
        {
            /* If the status is not E_OK */
            if(ServiceChannelCfg->ServiceContextBuffer[ResultIndex].ReturnVal != E_OK)
            {
                /* Call error hook */
                OsHook_SetErrorParameterFour(ServiceChannelCfg->ServiceContextBuffer[ResultIndex].ServiceId,
                                            (InputParaType)ServiceChannelCfg->ServiceContextBuffer[ResultIndex].R0,
                                            (InputParaType)ServiceChannelCfg->ServiceContextBuffer[ResultIndex].R1,
                                            (InputParaType)ServiceChannelCfg->ServiceContextBuffer[ResultIndex].R2,
                                            (InputParaType)ServiceChannelCfg->ServiceContextBuffer[ResultIndex].R3);
                OsHook_CallErrorHook(ServiceChannelCfg->ServiceContextBuffer[ResultIndex].ReturnVal);
            }
            ServiceChannelCfg->ServiceContextBuffer[ResultIndex].ServiceType = OS_IOC_SERVICECALL_ACK;
        }
        else if((ServiceChannelCfg->ServiceContextBuffer[ResultIndex].ServiceType & OS_IOC_SERVICECALL_TYPE_MASK) == OS_IOC_SERVICECALL_SYNC_UNHANDLED)
        {
            ServiceChannelCfg->ServiceContextBuffer[ResultIndex].ServiceType |= ~OS_IOC_SERVICECALL_TYPE_MASK;
            ServiceChannelCfg->ServiceContextBuffer[ResultIndex].ServiceType &= OS_IOC_SERVICECALL_SYNC_HANDLED;
        }
        else
        {
            /* Do nothing */
        }
        ServiceChannelCfg->RunningData->ResultIndex = (ResultIndex + 1) % ServiceChannelCfg->BufferLength;
        ResultIndex = ServiceChannelCfg->RunningData->ResultIndex;
    }
    WriteIndex = ServiceChannelCfg->RunningData->WriteIndex;
    Os_Inf_Dsync();
    if((WriteIndex + 1) % ServiceChannelCfg->BufferLength == ServiceChannelCfg->RunningData->ReadIndex)
    {
        /* FIFO Full */
        Status = E_OS_LIMIT;

        /* Call error hook */
        OsHook_SetErrorParameterFour(ServiceChannelCfg->ServiceContextBuffer[ResultIndex].ServiceId,
                                    (InputParaType)ServiceChannelCfg->ServiceContextBuffer[ResultIndex].R0,
                                    (InputParaType)ServiceChannelCfg->ServiceContextBuffer[ResultIndex].R1,
                                    (InputParaType)ServiceChannelCfg->ServiceContextBuffer[ResultIndex].R2,
                                    (InputParaType)ServiceChannelCfg->ServiceContextBuffer[ResultIndex].R3);
        OsHook_CallErrorHook(Status);
    }
    /* If there is an unhandled returnVal, it means write too fast or nesting too much */
    else if((ServiceChannelCfg->ServiceContextBuffer[WriteIndex].ServiceType & OS_IOC_SERVICECALL_TYPE_MASK) != OS_IOC_SERVICECALL_ACK)
    {
        /* FIFO Full */
        Status = E_OS_LIMIT;

        /* Call error hook */
        OsHook_SetErrorParameterFour(ServiceChannelCfg->ServiceContextBuffer[ResultIndex].ServiceId,
                                    (InputParaType)ServiceChannelCfg->ServiceContextBuffer[ResultIndex].R0,
                                    (InputParaType)ServiceChannelCfg->ServiceContextBuffer[ResultIndex].R1,
                                    (InputParaType)ServiceChannelCfg->ServiceContextBuffer[ResultIndex].R2,
                                    (InputParaType)ServiceChannelCfg->ServiceContextBuffer[ResultIndex].R3);
        OsHook_CallErrorHook(Status);
    }
    else
    {
        /* Init parameters of service */
        ServiceChannelCfg->ServiceContextBuffer[WriteIndex].R0 = ServiceCallCfg.ParameterIn[0];
        ServiceChannelCfg->ServiceContextBuffer[WriteIndex].R1 = ServiceCallCfg.ParameterIn[1];
        ServiceChannelCfg->ServiceContextBuffer[WriteIndex].R2 = ServiceCallCfg.ParameterIn[2];
        ServiceChannelCfg->ServiceContextBuffer[WriteIndex].R3 = ServiceCallCfg.ParameterIn[3];
        /* Init entry address of service */
        ServiceChannelCfg->ServiceContextBuffer[WriteIndex].R4 = ServiceCallCfg.EntryAddress;
        /* Set service id */
        ServiceChannelCfg->ServiceContextBuffer[WriteIndex].ServiceId = ServiceCallCfg.ServiceId;
        ServiceChannelCfg->ServiceContextBuffer[WriteIndex].ServiceType = ServiceCallCfg.ServiceType;
        ServiceChannelCfg->RunningData->WriteIndex = (WriteIndex + 1) % ServiceChannelCfg->BufferLength;
        /* Trigger interrupt to target core */
        Os_Inf_Dsync();
        OsIsr_TriggerSoftwareInterrupt(ServiceChannelCfg->IntId, ServiceCallCfg.TargetCoreId);
        Status = E_OK;
    }

    /* Resume interrupt level of context to previously saved value */
    OsIsr_ResumeISR(SuspendLevel);

    return Status;
}

static FUNC(uint32, OS_CODE) OsIoc_Internal_SyncServiceCallIsHandled
(
    uint32 ResultIndex,
    uint32 ReadIndex,
    uint32 TargetIndex
)
{
    uint32 res;

    if(ResultIndex == ReadIndex)
    {
        res = 0;
    }
    else if(ReadIndex > ResultIndex)
    {
        res = (TargetIndex >= ResultIndex) && (TargetIndex < ReadIndex);
    }
    else
    {
        res = (TargetIndex >= ResultIndex) || (TargetIndex < ReadIndex);
    }
    return res;
}
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
FUNC(void, OS_CODE) IocInit
(
    uint32 IocID
)
{
    /* Unqueued IOC */
    if(Os_IocConfigSet[IocID]->Type == OS_IOCTYPE_UNQUEUED)
    {
        /* If has initialization function */
        if(Os_IocConfigSet[IocID]->InitDataFunc != NULL_PTR)
        {
            Os_IocConfigSet[IocID]->InitDataFunc();
        }
    }
    *(Os_IocConfigSet[IocID]->CallbackIsUsed) = FALSE;
}

FUNC(void, OS_CODE) OsIoc_GetLock
(
    P2CONST(Os_IocConfigType, AUTOMATIC, OS_CONST) IocChannel,
    P2VAR(Os_IsrLevelType, AUTOMATIC, OS_VAR) Level
)
{
    switch (IocChannel->LockType)
    {
        case OS_IOCLOCKTYPE_NONE:
        {
            break;
        }
        case OS_IOCLOCKTYPE_INTERRUPTLOCK:
        {
            OsIsr_SuspendISR(Level);
            break;
        }
        case OS_IOCLOCKTYPE_SPINLOCK:
        {
            OsSpinlock_GetInternalSpinlock(IocChannel->SpinLock);
            break;
        }
        case OS_IOCLOCKTYPE_ALL:
        {
            OsIsr_SuspendISR(Level);
            OsSpinlock_GetInternalSpinlock(IocChannel->SpinLock);
            break;
        }
        default:
            break;
    }
}

FUNC(void, OS_CODE) OsIoc_ReleaseLock
(
    P2CONST(Os_IocConfigType, AUTOMATIC, OS_CONST) IocChannel,
    Os_IsrLevelType Level
)
{
    switch (IocChannel->LockType)
    {
        case OS_IOCLOCKTYPE_NONE:
        {
            break;
        }
        case OS_IOCLOCKTYPE_INTERRUPTLOCK:
        {
            OsIsr_ResumeISR(Level);
            break;
        }
        case OS_IOCLOCKTYPE_SPINLOCK:
        {
            OsSpinlock_ReleaseInternalSpinlock(IocChannel->SpinLock);
            break;
        }
        case OS_IOCLOCKTYPE_ALL:
        {
            OsIsr_ResumeISR(Level);
            OsSpinlock_ReleaseInternalSpinlock(IocChannel->SpinLock);
            break;
        }
        default:
            break;
    }
}

FUNC(StatusType, OS_CODE) OsIoc_CallCallback
(
    P2CONST(Os_IocCallbackConfigType, AUTOMATIC, OS_CONST) Callback
)
{
    Os_IocInterCoreServiceCallType ServiceCallCfg;
    StatusType Status;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CallbackObject;

    CallbackObject = OsApp_GetSpecific_ObjectInfo(Callback->ObjectID);
    /* Check if this callback has been called and without return */
    if(*(Os_IocConfigSet[CallbackObject->AppObjIDInfo & OBJECTID_MASK]->CallbackIsUsed) == TRUE)
    {
        CodeFreeze();
    }

    *(Os_IocConfigSet[CallbackObject->AppObjIDInfo & OBJECTID_MASK]->CallbackIsUsed) = TRUE;
    /* If receiver is in current core */
    if(TRUE == OsKernel_CheckObjectBelongToCurrentCore(Callback->ObjectID))
    {
        Status = E_OK;
        OsIoc_Internal_CallCallback(Callback->ObjectID);
    }
    /* Receiver is in the other core */
    else
    {
        /* Cross core service call */
        ServiceCallCfg.ServiceId = OS_SERVICEID_IOCCALLCALLBACK;
        ServiceCallCfg.EntryAddress = (uint32)OsIoc_Internal_CallCallback;
        ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(Callback->ObjectID);
        ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)Callback->ObjectID;
        ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
        ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
        Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
    }
    return Status;
}

FUNC(void, OS_CODE) OsIoc_CallbackReturn
(
    void
)
{
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) PreviousObject;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObject;
    Os_IsrLevelType SuspendLevel;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
    }

    /* Suspend interrupt */
    OsIsr_SuspendISR(&SuspendLevel);

    CurrentObject  = OsApp_GetCurrent_ObjectInfo();
    *(Os_IocConfigSet[CurrentObject->AppObjIDInfo & OBJECTID_MASK]->CallbackIsUsed) = FALSE;
    /* Get previous object info */
    PreviousObject = OsApp_GetPrevious_ObjectInfo();
    /* If previous object is task, reschedule */
    if(PreviousObject->ObjectType == OBJECT_TASK)
    {
        OsTask_DoScheduling(NOT_SAVING_CONTEXT);
    }
    else
    {
        OsApp_ChangeCurrent_AppInfo(PreviousObject->ObjectIDIndex);
        /* Switch context back to current object */
        Os_Hal_ContextSwitch(PreviousObject, CurrentObject, NOT_SAVING_CONTEXT);
    }
    OsIsr_ResumeISR(SuspendLevel);
}

FUNC(void, OS_CODE) OsIoc_CallbackDeInit
(
    uint32 ObjectId
)
{
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) ObjectInfo;

    if(ObjectId != OsApp_GetCurrent_ObjectID())
    {
        ObjectInfo = OsApp_GetSpecific_ObjectInfo(ObjectId);
        /* Set context pc to return address */
        Os_Hal_ContextAbort(*ObjectInfo->ObjectDataInfo.ObjectContextInfoPtr,
                            (*ObjectInfo->ObjectDataInfo.ObjectContextInfoPtr)->ContextInfoPtr);
    }
}

FUNC(StatusType, OS_CODE) OsIoc_ApplicationAccessCheck
(
    uint32 ApplicationMask
)
{
    ApplicationType CurrentApplicationId;

    CurrentApplicationId = OsApp_GetCurrentApplicationID();
    CurrentApplicationId = 1UL << CurrentApplicationId;
    return (ApplicationMask & CurrentApplicationId) ? E_OK : E_NOT_OK;
}

FUNC(StatusType, OS_CODE) OsIoc_CrossCoreServiceCall
(
    Os_IocInterCoreServiceCallType* ServiceCallCfg
)
{
    StatusType Status;
    P2CONST(Os_IocInterCoreServiceChannelCfgType, AUTOMATIC, OS_CONST) ServiceChannelCfg;
    uint32 BufferIndex;
    Os_IsrLevelType SuspendLevel;
    uint32 LoopCount;
    uint32 OutputCount;
    uint32 OutputParmMask;
    uint32 Timeout = 0xFFFFFFFF;

    /* Suspend interrupt and save current interrupt level */
    OsIsr_SuspendISR(&SuspendLevel);

    ServiceChannelCfg = OsIoc_GetIocServiceChannelCfgPtr(Os_Inf_CompilerGetCoreID(), ServiceCallCfg->TargetCoreId);
    /* Record position in buffer */
    BufferIndex = ServiceChannelCfg->RunningData->WriteIndex;
    OutputParmMask = ServiceCallCfg->OutputParmMask;
    OutputCount = 0UL;
    for(LoopCount = 0; LoopCount < OS_IOC_SERVICE_CALL_PARM_IN_MAX_NUM; LoopCount++)
    {
        if(1UL == (OutputParmMask & 0x1UL))
        {
            ServiceCallCfg->ParameterIn[LoopCount] = (Os_ServiceCallInputType)&(ServiceChannelCfg->ParameterOut[BufferIndex].OutParm[OutputCount]);
            OutputCount++;
        }
        OutputParmMask = OutputParmMask >> 1;
    }
    Status = OsIoc_Internal_CrossCoreServiceCall(*ServiceCallCfg);

    /* Resume interrupt level of context to previously saved value */
    OsIsr_ResumeISR(SuspendLevel);

    if((ServiceCallCfg->ServiceType & OS_IOC_SERVICECALL_TYPE_MASK) == OS_IOC_SERVICECALL_SYNC_UNHANDLED)
    {
        if(Status == E_OK)
        {
            /* Wait until return value is available */
            while((0UL == OsIoc_Internal_SyncServiceCallIsHandled(ServiceChannelCfg->RunningData->ResultIndex, ServiceChannelCfg->RunningData->ReadIndex, BufferIndex)) &&
                  (OS_IOC_SERVICECALL_SYNC_HANDLED != (ServiceChannelCfg->ServiceContextBuffer[BufferIndex].ServiceType & OS_IOC_SERVICECALL_TYPE_MASK)))
            {
                /* Do nothing */
                Os_Inf_Nop();
                if(Timeout > 0)
                    Timeout--;
                else
                    break;
            }
            Status = ServiceChannelCfg->ServiceContextBuffer[BufferIndex].ReturnVal;
            if(ServiceCallCfg->OutputParmMask != OS_IOC_NO_OUTPUT_PARM_MASK)
            {
                for(LoopCount = 0; LoopCount < OS_IOC_SERVICE_CALL_PARM_OUT_MAX_NUM; LoopCount++)
                {
                    ServiceCallCfg->OutParameter.OutParm[LoopCount] = ServiceChannelCfg->ParameterOut[BufferIndex].OutParm[LoopCount];
                }
            }
        }
        /* Reset service type in FIFO */
        ServiceChannelCfg->ServiceContextBuffer[BufferIndex].ServiceType = OS_IOC_SERVICECALL_ACK;
    }
    Os_Inf_Dsync();
    return Status;
}

FUNC(P2CONST(Os_IocInterCoreServiceChannelCfgType, AUTOMATIC, OS_CONST), OS_CODE) OsIoc_GetIocServiceChannelCfgPtr
(
    CoreIdType SourcePhysicalCore,
    CoreIdType TargetPhysicalCore
)
{
    return Os_IocServiceChannelCfgRef[SourcePhysicalCore].CoreServiceChannelCfgList[TargetPhysicalCore];
}

FUNC(void, OS_CODE) OsIoc_InterCoreServiceCallInit
(
    void
)
{
    uint32 CoreCount;
    uint32 ChannelCount;
    uint32 BufferIndex;
    P2CONST(Os_IocInterCoreServiceChannelCfgType, AUTOMATIC, OS_CONST) ServiceChannelCfg;

    for(CoreCount = 0UL; CoreCount < OS_KERNEL_MAX_CORE_NUM; CoreCount++)
    {
        for(ChannelCount = 0UL; ChannelCount < OS_KERNEL_MAX_CORE_NUM; ChannelCount++)
        {
            ServiceChannelCfg = Os_IocServiceChannelCfgRef[CoreCount].CoreServiceChannelCfgList[ChannelCount];
            if(ServiceChannelCfg != NULL_PTR)
            {
                for(BufferIndex = 0UL; BufferIndex < ServiceChannelCfg->BufferLength; BufferIndex++)
                {
                    ServiceChannelCfg->ServiceContextBuffer[BufferIndex].ServiceType = OS_IOC_SERVICECALL_ACK;
                }
                ServiceChannelCfg->RunningData->ReadIndex = 0UL;
                ServiceChannelCfg->RunningData->ResultIndex = 0UL;
                ServiceChannelCfg->RunningData->WriteIndex = 0UL;
            }
        }
    }
}

FUNC(void, OS_CODE) OsIoc_ClearSyncServiceCallFlag
(
    uint32 ObjectId
)
{
    uint32 ChannelCount;
    uint32 BufferIndex;
    boolean FindFlag;
    P2CONST(Os_IocInterCoreServiceChannelCfgType, AUTOMATIC, OS_CONST) ServiceChannelCfg;

    ChannelCount = 0UL;
    BufferIndex = 0UL;
    FindFlag = FALSE;
    while((ChannelCount < OS_KERNEL_MAX_CORE_NUM) && (FindFlag == FALSE))
    {
        ServiceChannelCfg = Os_IocServiceChannelCfgRef[Os_Inf_CompilerGetCoreID()].CoreServiceChannelCfgList[ChannelCount];
        if(ServiceChannelCfg != NULL_PTR)
        {
            while((BufferIndex < ServiceChannelCfg->BufferLength) && (FindFlag == FALSE))
            {
                if((ServiceChannelCfg->ServiceContextBuffer[BufferIndex].ServiceType & OS_IOC_SERVICECALL_OBJECTID_MASK) == ObjectId)
                {
                    ServiceChannelCfg->ServiceContextBuffer[BufferIndex].ServiceType = OS_IOC_SERVICECALL_ACK;
                    FindFlag = TRUE;
                }
                BufferIndex++;
            }
        }
        ChannelCount++;
    }
}
