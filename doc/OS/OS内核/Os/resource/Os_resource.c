/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_resource.c
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
#include "Os_resource.h"
#include "Os_compiler_types.h"
#include "Os_GeneralTypes.h"
#include "Os_lock.h"
#include "Os_resource_Cfg.h"
#include "Os_resource_Lcfg.h"
#include "Os_isr.h"
#include "Os_task.h"
#include "Os_hook.h"
#include "Os_application.h"
#include "Os_timingprotection.h"
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
*   Function Name           : OsResource_Internal_GetResource
*   Service ID              : None.
*   Description             : Private function of GetResource.
*   Parameters in           : ResID: Resource id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsResource_Internal_GetResource
(
    ResourceType ResID
);

/****************************************************************************************************
*   Function Name           : OsResource_Internal_ReleaseResource
*   Service ID              : None.
*   Description             : Private function of ReleaseResource.
*   Parameters in           : ResID: Resource id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsResource_Internal_ReleaseResource
(
    ResourceType ResID
);

/****************************************************************************************************
*   Function Name           : OsResource_Internal_CheckPriority
*   Service ID              : None.
*   Description             : Check if priority of current task/isr is lower than ceiling priority.
*   Parameters in           : ResID: Resource id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsResource_Internal_CheckPriority
(
    ResourceType ResID
);

/****************************************************************************************************
*   Function Name           : OsResource_Internal_CheckAccessObject
*   Service ID              : None.
*   Description             : Check if current task/isr can access current resource.
*   Parameters in           : ResID: Resource id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsResource_Internal_CheckAccessObject
(
    ResourceType ResID
);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsResource_Internal_GetResource
(
    ResourceType ResID
)
{
    StatusType Status;
    Os_IsrLevelType SuspendLevel;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObject;
    P2VAR(Os_LockConfigRefType, AUTOMATIC, OS_VAR) LockList;
    P2CONST(Os_TpObjectConfigTypeRef, AUTOMATIC, OS_CONST) TaskTpConfig;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_GETRESOURCE);
    OS_ARTI_SC_BEGIN(GetResource, ResID);

    CurrentObject = OsApp_GetCurrent_ObjectInfo();
    Status = E_OK;
    if(OsService_ExtendedErrorCheck(ResID >= OS_RESOURCE_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    /* Check if resource is already occupied */
    else if(OsService_ExtendedErrorCheck(Os_ResourceConfigSet[ResID]->Lock->Previous != OS_LOCK_FREE))
    {
        Status = E_OS_ACCESS;
    }
    /* Check if function is called in correct context, Task or Isr2 */
    else if(!(OsKernel_GetCurrentRunningContext() & OS_CALL_GETRESOURCE))
    {
        Status = E_OS_CALLEVEL;
    }
    /* Check priority of task/isr is lower than ceiling priority */
    else if(OsService_ExtendedErrorCheck(E_NOT_OK == OsResource_Internal_CheckPriority(ResID)))
    {
        Status = E_OS_ACCESS;
    }
    /* Check if current task/isr can access current resource */
    else if(OsResource_Internal_CheckAccessObject(ResID) == E_NOT_OK)
    {
        Status = E_OS_ACCESS;
    }
    else
    {
        /* If resource is assigned to Isr */
        if(Os_ResourceConfigSet[ResID]->CeilingIsrLevel != OS_RESOURCE_INVALID_CEILING)
        {
            /* Increase interrupt level */
            OsIsr_SaveAndIncreaseLevel(&Os_ResourceConfigSet[ResID]->RunningData->PreviousIsrLevel, Os_ResourceConfigSet[ResID]->CeilingIsrLevel);
        }
        OsIsr_SuspendISR(&SuspendLevel);
        /* Tp start */
        TaskTpConfig = (*(CurrentObject->ObjectDataInfo.ObjectContextInfoPtr))->TpInfoPtr;
        OsTp_StartLockResource(TaskTpConfig, ResID);

        /* Trace start */

        /* If current object is Isr */
        if(CurrentObject->ObjectType == OBJECT_ISR)
        {
            /* Get lock list */
            OsIsr_GetLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &LockList);
        }
        /* If current object is Task */
        else
        {
            /* Get lock list */
            OsTask_GetLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &LockList);
            /* Increase task priority */
            OsTask_LevelUpTaskPriority(Os_ResourceConfigSet[ResID]->CeilingPriority, &Os_ResourceConfigSet[ResID]->RunningData->PreviousTaskPriority);
        }
        /* Push lock list */
        OsLock_ListPush(LockList, Os_ResourceConfigSet[ResID]->Lock);
        Os_ResourceConfigSet[ResID]->RunningData->OwnerObjectID = CurrentObject->ObjectIDIndex;

        OsIsr_ResumeISR(SuspendLevel);
    }

    if(E_OK != Status)
    {
        OsHook_SetErrorParameterOne(OS_SERVICEID_GETRESOURCE, (InputParaType)ResID);
        OsHook_CallErrorHook(Status);
    }

    OS_ARTI_SC_END(GetResource, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_GETRESOURCE);

    return Status;
}

static FUNC(StatusType, OS_CODE) OsResource_Internal_ReleaseResource
(
    ResourceType ResID
)
{
    StatusType Status;
    Os_IsrLevelType SuspendLevel;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObject;
    P2VAR(Os_LockConfigRefType, AUTOMATIC, OS_VAR) LockList;
    P2CONST(Os_TpObjectConfigTypeRef, AUTOMATIC, OS_CONST) TaskTpConfig;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_RELEASERESOURCE);
    OS_ARTI_SC_BEGIN(ReleaseResource, ResID);

    CurrentObject = OsApp_GetCurrent_ObjectInfo();

    Status = E_OK;
    if(OsService_ExtendedErrorCheck(ResID >= OS_RESOURCE_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    /* Check if resource is not occupied */
    else if(OsService_ExtendedErrorCheck(Os_ResourceConfigSet[ResID]->Lock->Previous == OS_LOCK_FREE))
    {
        Status = E_OS_NOFUNC;
    }
    /* Check if function is called in correct context, Task or Isr2 */
    else if(!(OsKernel_GetCurrentRunningContext() & OS_CALL_RELEASERESOURCE))
    {
        Status = E_OS_CALLEVEL;
    }
    /* Check if current task/isr can access current resource */
    else if(OsResource_Internal_CheckAccessObject(ResID) == E_NOT_OK)
    {
        Status = E_OS_ACCESS;
    }
    /* Check priority of task/isr is lower than ceiling priority */
    else if(OsService_ExtendedErrorCheck(E_NOT_OK == OsResource_Internal_CheckPriority(ResID)))
    {
        Status = E_OS_ACCESS;
    }
    else
    {
        /* If current object is Isr */
        if(CurrentObject->ObjectType == OBJECT_ISR)
        {
            /* Get lock list */
            OsIsr_GetLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &LockList);
        }
        /* If current object is Task */
        else
        {
            /* Get lock list */
            OsTask_GetLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &LockList);
        }
        /* Check if resource is released in order */
        if(OsService_ExtendedErrorCheck(*LockList != Os_ResourceConfigSet[ResID]->Lock))
        {
            Status = E_OS_NOFUNC;
        }
        else
        {
            OsIsr_SuspendISR(&SuspendLevel);
            /* Trace stop */

            /* Pop lock list */
            OsLock_ListPop(LockList);

            /* Tp stop */
            TaskTpConfig = (*(CurrentObject->ObjectDataInfo.ObjectContextInfoPtr))->TpInfoPtr;
            OsTp_StopLockResource(TaskTpConfig, ResID);
            /* Clear owner object ID */
            Os_ResourceConfigSet[ResID]->RunningData->OwnerObjectID = 0xFFFFFFFFU;
            /* If current object is Task */
            if(CurrentObject->ObjectType == OBJECT_TASK)
            {
                /* Restore task priority */
                OsTask_LevelDownTaskPriority(Os_ResourceConfigSet[ResID]->RunningData->PreviousTaskPriority);
                /* Reschedule if needed */
                OsTask_DoScheduling(SAVING_CONTEXT);
            }
            /* If resource is assigned to Isr */
            if(Os_ResourceConfigSet[ResID]->CeilingIsrLevel != OS_RESOURCE_INVALID_CEILING)
            {
                /* Restore interrupt level */
                OsIsr_ResumeISR(Os_ResourceConfigSet[ResID]->RunningData->PreviousIsrLevel);
            }
            else
            {
                OsIsr_ResumeISR(SuspendLevel);
            }
        }
    }

    if(E_OK != Status)
    {
        OsHook_SetErrorParameterOne(OS_SERVICEID_RELEASERESOURCE, (InputParaType)ResID);
        OsHook_CallErrorHook(Status);
    }

    OS_ARTI_SC_END(ReleaseResource, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_RELEASERESOURCE);

    return Status;
}

static FUNC(StatusType, OS_CODE) OsResource_Internal_CheckPriority
(
    ResourceType ResID
)
{
    StatusType Status;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObject;
    uint32 CeilingPriority;

    Status = E_OK;
    CurrentObject = OsApp_GetCurrent_ObjectInfo();

    /* If current object is Isr */
    if(CurrentObject->ObjectType == OBJECT_ISR)
    {
        CeilingPriority = Os_ResourceConfigSet[ResID]->CeilingIsrLevel;
        if(OS_RESOURCE_INVALID_CEILING == CeilingPriority)
        {
            Status = E_NOT_OK;
        }
        else
        {
            /* Get isr priority and compare */
            if(OsIsr_GetPriroity(CurrentObject->AppObjIDInfo & OBJECTID_MASK) < CeilingPriority)
            {
                Status = E_NOT_OK;
            }
        }
    }
    /* If current object is Task */
    else
    {
        CeilingPriority = Os_ResourceConfigSet[ResID]->CeilingPriority;
        /* Get task priority and compare */
        if(OsTask_GetHomePriority(CurrentObject->AppObjIDInfo & OBJECTID_MASK) > CeilingPriority)
        {
            Status = E_NOT_OK;
        }
    }
    return Status;
}

static FUNC(StatusType, OS_CODE) OsResource_Internal_CheckAccessObject
(
    ResourceType ResID
)
{
    StatusType Status;
    uint32 CurrentObjectId;
    uint32 count;

    Status = E_OK;
    CurrentObjectId = OsApp_GetCurrent_ObjectID();
    for(count = 0UL; count < Os_ResourceConfigSet[ResID]->AccessObjectList.AccessObjectIdNum; count++)
    {
        if(CurrentObjectId == Os_ResourceConfigSet[ResID]->AccessObjectList.AccessObjectIdList[count])
        {
            break;
        }
    }
    if(count == Os_ResourceConfigSet[ResID]->AccessObjectList.AccessObjectIdNum)
    {
        Status = E_NOT_OK;
    }
    return Status;
}
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
FUNC(StatusType, OS_CODE) GetResource
(
    ResourceType ResID
)
{
    StatusType Status;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsResource_Internal_GetResource(ResID);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsResource_Internal_GetResource(ResID);
    }

    return Status;
}

FUNC(StatusType, OS_CODE) ReleaseResource
(
    ResourceType ResID
)
{
    StatusType Status;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsResource_Internal_ReleaseResource(ResID);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsResource_Internal_ReleaseResource(ResID);
    }

    return Status;
}

FUNC(void, OS_CODE) OsResource_ResourceInit
(
    ResourceType ResID
)
{
    Os_ResourceConfigSet[ResID]->RunningData->PreviousTaskPriority = 0U;
    Os_ResourceConfigSet[ResID]->RunningData->PreviousIsrLevel = 0U;
    Os_ResourceConfigSet[ResID]->RunningData->OwnerObjectID = 0xFFFFFFFFU;
    Os_ResourceConfigSet[ResID]->Lock->LockType = OS_LOCKTYPE_RESOURCE;
    Os_ResourceConfigSet[ResID]->Lock->LockId = ResID;
    Os_ResourceConfigSet[ResID]->Lock->Previous = OS_LOCK_FREE;
}

FUNC(void, OS_CODE) OsResource_ResourceDeInit
(
    ResourceType ResID
)
{
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObject;
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_VAR) ObjectTpConfig;

    CurrentObject = OsApp_GetCurrent_ObjectInfo();
    /* Tp stop */
    ObjectTpConfig = (*(CurrentObject->ObjectDataInfo.ObjectContextInfoPtr))->TpInfoPtr;
    OsTp_StopLockResource(ObjectTpConfig, ResID);

    /* Clear owner object ID */
    Os_ResourceConfigSet[ResID]->RunningData->OwnerObjectID = 0xFFFFFFFFU;
    if(Os_ResourceConfigSet[ResID]->CeilingIsrLevel != OS_RESOURCE_INVALID_CEILING)
    {
        /* Restore interrupt level */
        OsIsr_ResumeISR(Os_ResourceConfigSet[ResID]->RunningData->PreviousIsrLevel);
    }
}

FUNC(uint32, OS_CODE) OsResource_GetCeilingPriority
(
    ResourceType ResID
)
{
    return Os_ResourceConfigSet[ResID]->CeilingPriority;
}
