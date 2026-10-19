/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_spinlock.c
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
#include "Platform_Types.h"
#include "Os_spinlock_types.h"
#include "Os_spinlock.h"
#include "Os_spinlock_hal.h"
#include "Os_spinlock_Cfg.h"
#include "Os_spinlock_Lcfg.h"
#include "Os_application_types.h"
#include "Os_application.h"
#include "Os_isr.h"
#include "Os_task.h"
#include "Os_kernel.h"
#include "Os_lock.h"
#include "Os_hook.h"
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
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : OsSpinlock_Internal_GetSpinlock
*   Service ID              : None.
*   Description             : Private function of GetSpinlock.
*   Parameters in           : SpinlockId: ID of spinlock to get.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSpinlock_Internal_GetSpinlock
(
    SpinlockIdType SpinlockId
);

/****************************************************************************************************
*   Function Name           : OsSpinlock_Internal_TryToGetSpinlock
*   Service ID              : None.
*   Description             : Private function of TryToGetSpinlock.
*   Parameters in           : SpinlockId: ID of spinlock to get.
*   Parameters inout        : None.
*   Parameters out          : Success: Indicate the result of function.
                                       Success: TRYTOGETSPINLOCK_SUCCESS
                                       Failed: TRYTOGETSPINLOCK_NOSUCCESS
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSpinlock_Internal_TryToGetSpinlock
(
    SpinlockIdType SpinlockId,
    P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success
);

/****************************************************************************************************
*   Function Name           : OsSpinlock_Internal_ReleaseSpinlock
*   Service ID              : None.
*   Description             : Private function of ReleaseSpinlock.
*   Parameters in           : SpinlockId: ID of spinlock to release.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSpinlock_Internal_ReleaseSpinlock
(
    SpinlockIdType SpinlockId
);

/****************************************************************************************************
*   Function Name           : OsSpinlock_Internal_CheckSuccessorOrder
*   Service ID              : None.
*   Description             : Check if nesting order of spinlock is consistent with configuration.
*   Parameters in           : SpinlockSuccessorID: Index of spinlock in a configured nesting order.
                              SpinlockSuccessorListID: ID of the nesting order.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSpinlock_Internal_CheckSuccessorOrder
(
    uint32 SpinlockSuccessorID,
    uint32 SpinlockSuccessorListID
);

/****************************************************************************************************
*   Function Name           : OsSpinlock_Internal_ApplicationAccessCheck
*   Service ID              : None.
*   Description             : Check if current app can access spinlock.
*   Parameters in           : ApplicationMask: AppId mask of apps that can access specific spinlock.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSpinlock_Internal_ApplicationAccessCheck
(
    uint32 ApplicationMask
);

/****************************************************************************************************
*   Function Name           : OsSpinlock_Internal_CheckInterferenceDeadlock
*   Service ID              : None.
*   Description             : Check if this spinlock is already occupied by a task/isr2 on the same core.
*   Parameters in           : SpinlockId: ID of spinlock
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSpinlock_Internal_CheckInterferenceDeadlock
(
    SpinlockIdType SpinlockId
);

/****************************************************************************************************
*   Function Name           : OsSpinlock_Internal_ListPush
*   Service ID              : None.
*   Description             : Push a spinlock into nesting recording FIFO.
*   Parameters in           : SpinlockListPtr: Pointer to FIFO.
                              SpinlockId: ID of spinlock to be pushed.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsSpinlock_Internal_ListPush
(
    P2VAR(Os_SpinlockConfigRefType, TYPEDEF, OS_VAR) SpinlockListPtr,
    SpinlockIdType SpinlockId
);

/****************************************************************************************************
*   Function Name           : OsSpinlock_Internal_ListPop
*   Service ID              : None.
*   Description             : Pop a spinlock from nesting recording FIFO.
*   Parameters in           : SpinlockListPtr: Pointer to FIFO.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsSpinlock_Internal_ListPop
(
    P2VAR(Os_SpinlockConfigRefType, TYPEDEF, OS_VAR) SpinlockListPtr
);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSpinlock_Internal_GetSpinlock
(
    SpinlockIdType SpinlockId
)
{
    StatusType Status;
    boolean Result;
    Os_IsrLevelType IntLevel;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObject;
    P2VAR(Os_LockConfigRefType, AUTOMATIC, OS_VAR) LockList;
    P2VAR(Os_SpinlockConfigRefType, AUTOMATIC, OS_VAR) SpinlockList;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_GETSPINLOCK);
    OS_ARTI_SC_BEGIN(GetSpinlock, SpinlockId);

    CurrentObject = OsApp_GetCurrent_ObjectInfo();
    /* [SWS_Os_00689] The function GetSpinlock shall return E_OS_ID if the parameter
       SpinlockID refers to a spinlock that does not exist. */
    if(OsService_ExtendedErrorCheck(SpinlockId >= OS_SPINLOCK_USER_CFG_NUM))
    {
        Status = E_OS_ID;
    }
    /* Check if function is called in correct context, Task or Isr2 */
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_GETSPINLOCK)))
    {
        Status = E_OS_CALLEVEL;
    }
    /* [SWS_Os_00692] Check the accessing OS-Application */
    else if(OsService_ExtendedErrorCheck(OsSpinlock_Internal_ApplicationAccessCheck(Os_SpinlockConfigSet[SpinlockId]->AccessApplicationIdMask) == E_NOT_OK))
    {
        Status = E_OS_ACCESS;
    }
    /* [SWS_Os_00690] Check if this spinlock is already occupied by a task/isr2 on the same core */
    else if(OsService_ExtendedErrorCheck(OsSpinlock_Internal_CheckInterferenceDeadlock(SpinlockId) == E_NOT_OK))
    {
        Status = E_OS_INTERFERENCE_DEADLOCK;
    }
    /* [SWS_Os_00691] Check if spinlock is nested in order */
    else if(OsService_ExtendedErrorCheck(OsSpinlock_Internal_CheckSuccessorOrder(Os_SpinlockConfigSet[SpinlockId]->SpinlockSuccessorID,
                                                    Os_SpinlockConfigSet[SpinlockId]->SpinlockSuccessorListID) == E_NOT_OK))
    {
        Status = E_OS_NESTING_DEADLOCK;
    }
    else
    {
        Status = E_OK;
        /* Do method according to lockmethod */
        switch(Os_SpinlockConfigSet[SpinlockId]->OsSpinlockLockMethod)
        {
            case LOCK_ALL_INTERRUPTS:
            {
                OsIsr_SuspendAllInterrupts();
                break;
            }
            case LOCK_CAT2_INTERRUPTS:
            {
                OsIsr_SuspendOSInterrupts();
                break;
            }
            case LOCK_WITH_RES_SCHEDULER:
            {
                /* Record current task priority and increase task priority */
                OsTask_LevelUpTaskPriority(0xFFFFFFFFUL, &Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->PreviousTaskPriority);
                break;
            }
            case LOCK_NOTHING:
            {
                break;
            }
            default:
                break;
        }

        /* [SWS_Os_00687] Wait spinlock is free */
        do
        {
            OsIsr_SuspendISR(&IntLevel);
            Result = OsSpinlock_Hal_Getlock(Os_SpinlockConfigSet[SpinlockId]->LockStatus);
            if(Result == TRUE)
            {
                /* If current object is Isr */
                if(CurrentObject->ObjectType == OBJECT_ISR)
                {
                    /* Get lock list */
                    OsIsr_GetLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &LockList);
                    /* Get spinlock list */
                    OsIsr_GetSpinLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &SpinlockList);
                }
                /* If current object is Task */
                else
                {
                    /* Get lock list */
                    OsTask_GetLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &LockList);
                    /* Get spinlock list */
                    OsTask_GetSpinLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &SpinlockList);
                }
                /* Push lock list */
                OsLock_ListPush(LockList, Os_SpinlockConfigSet[SpinlockId]->Lock);
                /* Push spinlock list */
                OsSpinlock_Internal_ListPush(SpinlockList, SpinlockId);
                /* Set owner object ID info */
                Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->OwnerObjectID = CurrentObject->ObjectIDIndex;
#if (OS_ARTI_TRACE_SPINLOCK == STD_ON)
                {
                    /* Reported when the lock is obtained, not while spinning */
                    CoreIdType ArtiCore = Os_Inf_GetCoreId();
                    OS_ARTI_SPINLOCK_LOCKED(ArtiCore, SpinlockId);
                    (void)ArtiCore;
                }
#endif
            }
            OsIsr_ResumeISR(IntLevel);
        } while(Result != TRUE);
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&IntLevel);
        OsHook_SetErrorParameterOne(OS_SERVICEID_GETSPINLOCK, (InputParaType)SpinlockId);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(IntLevel);
    }

    OS_ARTI_SC_END(GetSpinlock, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_GETSPINLOCK);

    return Status;
}

static FUNC(StatusType, OS_CODE) OsSpinlock_Internal_TryToGetSpinlock
(
    SpinlockIdType SpinlockId,
    P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success
)
{
    StatusType Status;
    boolean Result;
    Os_IsrLevelType IntLevel;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObject;
    P2VAR(Os_LockConfigRefType, AUTOMATIC, OS_VAR) LockList;
    P2VAR(Os_SpinlockConfigRefType, AUTOMATIC, OS_VAR) SpinlockList;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_TRYTOGETSPINLOCK);
    OS_ARTI_SC_BEGIN(TryToGetSpinlock, SpinlockId);

    /* [SWS_Os_00707] */
    if(OsService_ExtendedErrorCheck(SpinlockId >= OS_SPINLOCK_USER_CFG_NUM))
    {
        Status = E_OS_ID;
    }
    /* Check if function is called in correct context, Task or Isr2 */
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_TRYTOGETSPINLOCK)))
    {
        Status = E_OS_CALLEVEL;
    }
    /* [SWS_Os_00710] Check accessing application */
    else if(OsService_ExtendedErrorCheck(OsSpinlock_Internal_ApplicationAccessCheck(Os_SpinlockConfigSet[SpinlockId]->AccessApplicationIdMask) == E_NOT_OK))
    {
        Status = E_OS_ACCESS;
    }
    /* [SWS_Os_00708] Check if this spinlock is already occupied by a task/isr2 on the same core */
    else if(OsService_ExtendedErrorCheck(OsSpinlock_Internal_CheckInterferenceDeadlock(SpinlockId) == E_NOT_OK))
    {
        Status = E_OS_INTERFERENCE_DEADLOCK;
    }
    /* [SWS_Os_00709] Check if spinlock is nested in order */
    else if(OsService_ExtendedErrorCheck(OsSpinlock_Internal_CheckSuccessorOrder(Os_SpinlockConfigSet[SpinlockId]->SpinlockSuccessorID,
                                                    Os_SpinlockConfigSet[SpinlockId]->SpinlockSuccessorListID) == E_NOT_OK))
    {
        Status = E_OS_NESTING_DEADLOCK;
    }
    else
    {
        Status = E_OK;
        CurrentObject = OsApp_GetCurrent_ObjectInfo();
        /* Do method according to lockmethod */
        switch(Os_SpinlockConfigSet[SpinlockId]->OsSpinlockLockMethod)
        {
            case LOCK_ALL_INTERRUPTS:
            {
                OsIsr_SuspendAllInterrupts();
                break;
            }
            case LOCK_CAT2_INTERRUPTS:
            {
                OsIsr_SuspendOSInterrupts();
                break;
            }
            case LOCK_WITH_RES_SCHEDULER:
            {
                /* Record current task priority and increase task priority */
                OsTask_LevelUpTaskPriority(0xFFFFFFFFUL, &Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->PreviousTaskPriority);
                break;
            }
            case LOCK_NOTHING:
            {
                break;
            }
            default:
                break;
        }

        OsIsr_SuspendISR(&IntLevel);
        /* [SWS_Os_00704] Atomically test the availability of the spinlock and if available occupy it */
        Result = OsSpinlock_Hal_Getlock(Os_SpinlockConfigSet[SpinlockId]->LockStatus);
        if(Result == TRUE)
        {
            /* [SWS_Os_00705] Set result */
            *Success = TRYTOGETSPINLOCK_SUCCESS;
            /* If current object is Isr */
            if(CurrentObject->ObjectType == OBJECT_ISR)
            {
                /* Get lock list */
                OsIsr_GetLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &LockList);
                /* Get spinlock list */
                OsIsr_GetSpinLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &SpinlockList);
            }
            /* If current object is Task */
            else
            {
                /* Get lock list */
                OsTask_GetLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &LockList);
                /* Get spinlock list */
                OsTask_GetSpinLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &SpinlockList);
            }
            /* Push lock list */
            OsLock_ListPush(LockList, Os_SpinlockConfigSet[SpinlockId]->Lock);
            /* Push spinlock list */
            OsSpinlock_Internal_ListPush(SpinlockList, SpinlockId);
            /* Set owner object ID info */
            Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->OwnerObjectID = CurrentObject->ObjectIDIndex;
#if (OS_ARTI_TRACE_SPINLOCK == STD_ON)
            {
                CoreIdType ArtiCore = Os_Inf_GetCoreId();
                OS_ARTI_SPINLOCK_LOCKED(ArtiCore, SpinlockId);
                (void)ArtiCore;
            }
#endif
        }
        else
        {
            /* [SWS_Os_00705][SWS_Os_00706] Set result */
            *Success = TRYTOGETSPINLOCK_NOSUCCESS;
        }
        OsIsr_ResumeISR(IntLevel);
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&IntLevel);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_TRYTOGETSPINLOCK, (InputParaType)SpinlockId, (InputParaType)Success);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(IntLevel);
    }

    OS_ARTI_SC_END(TryToGetSpinlock, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_TRYTOGETSPINLOCK);

    return Status;
}

static FUNC(StatusType, OS_CODE) OsSpinlock_Internal_ReleaseSpinlock
(
    SpinlockIdType SpinlockId
)
{
    StatusType Status;
    Os_IsrLevelType IntLevel;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObject;
    P2VAR(Os_LockConfigRefType, AUTOMATIC, OS_VAR) LockList;
    P2VAR(Os_SpinlockConfigRefType, AUTOMATIC, OS_VAR) SpinlockList;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_RELEASESPINLOCK);
    OS_ARTI_SC_BEGIN(ReleaseSpinlock, SpinlockId);

    CurrentObject = OsApp_GetCurrent_ObjectInfo();
    /* [SWS_Os_00698] Check SpinlockID */
    if(OsService_ExtendedErrorCheck(SpinlockId >= OS_SPINLOCK_USER_CFG_NUM))
    {
        Status = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_RELEASESPINLOCK)))
    {
        Status = E_OS_CALLEVEL;
    }
    /* [SWS_Os_00700] Check accessing app */
    else if(OsService_ExtendedErrorCheck(OsSpinlock_Internal_ApplicationAccessCheck(Os_SpinlockConfigSet[SpinlockId]->AccessApplicationIdMask) == E_NOT_OK))
    {
        Status = E_OS_ACCESS;
    }
    /* [SWS_Os_00699] Check if the spinlock is not occupied by the calling object */
    else if(OsService_ExtendedErrorCheck(CurrentObject->ObjectIDIndex != Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->OwnerObjectID))
    {
        Status = E_OS_STATE;
    }
    else
    {
        Status = E_OK;

        OsIsr_SuspendISR(&IntLevel);

        if(CurrentObject->ObjectType == OBJECT_ISR)
        {
            /* Get lock list */
            OsIsr_GetLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &LockList);
            /* Get spinlock list */
            OsIsr_GetSpinLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &SpinlockList);
        }
        /* If current object is Task */
        else
        {
            /* Get lock list */
            OsTask_GetLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &LockList);
            /* Get spinlock list */
            OsTask_GetSpinLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &SpinlockList);
        }
        /* [SWS_Os_00701] Check if spinlock is released in order */
        if(*LockList != Os_SpinlockConfigSet[SpinlockId]->Lock)
        {
            Status = E_OS_NOFUNC;
        }
        else
        {
#if (OS_ARTI_TRACE_SPINLOCK == STD_ON)
            {
                /* Before the hardware release: afterwards another core may already have emitted Locked */
                CoreIdType ArtiCore = Os_Inf_GetCoreId();
                OS_ARTI_SPINLOCK_RELEASED(ArtiCore, SpinlockId);
                (void)ArtiCore;
            }
#endif
            OsSpinlock_Hal_Releaselock(Os_SpinlockConfigSet[SpinlockId]->LockStatus);
            /* Pop lock list */
            OsLock_ListPop(LockList);
            /* Pop spinlock list */
            OsSpinlock_Internal_ListPop(SpinlockList);
            /* Clear owner object ID info */
            Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->OwnerObjectID = 0xFFFFFFFFUL;
            OsIsr_ResumeISR(IntLevel);

            /* [SWS_Os_00696] Resume according to lockmethod */
            switch(Os_SpinlockConfigSet[SpinlockId]->OsSpinlockLockMethod)
            {
                case LOCK_ALL_INTERRUPTS:
                {
                    OsIsr_ResumeAllInterrupts();
                    break;
                }
                case LOCK_CAT2_INTERRUPTS:
                {
                    OsIsr_ResumeOSInterrupts();
                    break;
                }
                case LOCK_WITH_RES_SCHEDULER:
                {
                    /* Resume task priority */
                    OsTask_LevelDownTaskPriority(Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->PreviousTaskPriority);
                    /* Reschedule if needed */
                    OsTask_DoScheduling(SAVING_CONTEXT);
                    break;
                }
                case LOCK_NOTHING:
                {
                    break;
                }
                default:
                    break;
            }
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&IntLevel);
        OsHook_SetErrorParameterOne(OS_SERVICEID_RELEASESPINLOCK, (InputParaType)SpinlockId);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(IntLevel);
    }

    OS_ARTI_SC_END(ReleaseSpinlock, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_RELEASESPINLOCK);

    return Status;
}

static FUNC(StatusType, OS_CODE) OsSpinlock_Internal_CheckSuccessorOrder
(
    uint32 SpinlockSuccessorID,
    uint32 SpinlockSuccessorListID
)
{
    StatusType Status;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObject;
    P2VAR(Os_SpinlockConfigRefType, AUTOMATIC, OS_VAR) SpinlockList;

    Status = E_OK;
    CurrentObject = OsApp_GetCurrent_ObjectInfo();
    /* If current object is task */
    if(CurrentObject->ObjectType == OBJECT_TASK)
    {
        /* Get spinlock list */
        OsTask_GetSpinLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &SpinlockList);
    }
    /* If current object is isr2 */
    else
    {
        /* Get spinlock list */
        OsIsr_GetSpinLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &SpinlockList);
    }

    if(*SpinlockList != NULL_PTR)
    {
        if((*SpinlockList)->SpinlockSuccessorListID != SpinlockSuccessorListID)
        {
            Status = E_NOT_OK;
        }
        else if((*SpinlockList)->SpinlockSuccessorID >= SpinlockSuccessorID)
        {
            Status = E_NOT_OK;
        }
    }
    return Status;
}

static FUNC(StatusType, OS_CODE) OsSpinlock_Internal_ApplicationAccessCheck
(
    uint32 ApplicationMask
)
{
    ApplicationType CurrentApplicationId;

    CurrentApplicationId = OsApp_GetCurrentApplicationID();
    CurrentApplicationId = 1UL << CurrentApplicationId;
    return (ApplicationMask & CurrentApplicationId) ? E_OK : E_NOT_OK;
}

static FUNC(StatusType, OS_CODE) OsSpinlock_Internal_CheckInterferenceDeadlock
(
    SpinlockIdType SpinlockId
)
{
    StatusType Status;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) OwnerObject;
    CoreIdType OwnerCoreId;

    if(Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->OwnerObjectID == 0xFFFFFFFFUL)
    {
        Status = E_OK;
    }
    else
    {
        OwnerObject = OsApp_GetSpecific_ObjectInfo(Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->OwnerObjectID);
        if(OwnerObject->ObjectType == OBJECT_ISR)
        {
            OwnerCoreId = OsIsr_GetOwnerCoreId(OwnerObject->AppObjIDInfo & OBJECTID_MASK);
        }
        else
        {
            OwnerCoreId = (OwnerObject->AppObjIDInfo & COREID_MASK) >> 24;
        }
        if(OwnerCoreId == Os_Inf_CompilerGetCoreID())
        {
            Status = E_NOT_OK;
        }
        else
        {
            Status = E_OK;
        }
    }
    return Status;
}

static FUNC(void, OS_CODE) OsSpinlock_Internal_ListPush
(
    P2VAR(Os_SpinlockConfigRefType, TYPEDEF, OS_VAR) SpinlockListPtr,
    SpinlockIdType SpinlockId
)
{
    Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->Previous = (struct Os_SpinlockCfgType *)*SpinlockListPtr;
    *SpinlockListPtr = Os_SpinlockConfigSet[SpinlockId];
}

static FUNC(void, OS_CODE) OsSpinlock_Internal_ListPop
(
    P2VAR(Os_SpinlockConfigRefType, TYPEDEF, OS_VAR) SpinlockListPtr
)
{
    Os_SpinlockConfigRefType SpinlockRef;

    SpinlockRef = *SpinlockListPtr;
    *SpinlockListPtr = SpinlockRef->SpinlockRunningData->Previous;
    SpinlockRef->SpinlockRunningData->Previous = NULL_PTR;
}
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
FUNC(StatusType, OS_CODE) GetSpinlock
(
    SpinlockIdType SpinlockId
)
{
    StatusType Status;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsSpinlock_Internal_GetSpinlock(SpinlockId);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsSpinlock_Internal_GetSpinlock(SpinlockId);
    }

    return Status;
}

FUNC(StatusType, OS_CODE) TryToGetSpinlock
(
    SpinlockIdType SpinlockId,
    P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success
)
{
    StatusType Status;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsSpinlock_Internal_TryToGetSpinlock(SpinlockId, Success);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsSpinlock_Internal_TryToGetSpinlock(SpinlockId, Success);
    }

    return Status;
}

FUNC(StatusType, OS_CODE) ReleaseSpinlock
(
    SpinlockIdType SpinlockId
)
{
    StatusType Status;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsSpinlock_Internal_ReleaseSpinlock(SpinlockId);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsSpinlock_Internal_ReleaseSpinlock(SpinlockId);
    }

    return Status;
}

FUNC(void, OS_CODE) OsSpinlock_SpinlockInit
(
    SpinlockIdType SpinlockId
)
{
    if(SpinlockId < OS_SPINLOCK_USER_CFG_NUM)
    {
        Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->OwnerObjectID = 0xFFFFFFFFUL;
        Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->PreviousTaskPriority = 0UL;
        Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->Previous = NULL_PTR;
        Os_SpinlockConfigSet[SpinlockId]->Lock->LockType = OS_LOCKTYPE_SPINLOCK;
        Os_SpinlockConfigSet[SpinlockId]->Lock->LockId = SpinlockId;
        Os_SpinlockConfigSet[SpinlockId]->Lock->Previous = OS_LOCK_FREE;
    }
    Os_SpinlockConfigSet[SpinlockId]->LockStatus->lockStatus = 0UL;
}

FUNC(void, OS_CODE) OsSpinlock_GetInternalSpinlock
(
    SpinlockIdType SpinlockId
)
{
    boolean Result;

    do
    {
        Result = OsSpinlock_Hal_Getlock(Os_SpinlockConfigSet[SpinlockId]->LockStatus);
    } while(Result != TRUE);
}

FUNC(void, OS_CODE) OsSpinlock_ReleaseInternalSpinlock
(
    SpinlockIdType SpinlockId
)
{
    OsSpinlock_Hal_Releaselock(Os_SpinlockConfigSet[SpinlockId]->LockStatus);
}

FUNC(void, OS_CODE) OsSpinlock_SpinlockDeInit
(
    SpinlockIdType SpinlockId
)
{
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObject;
    P2VAR(Os_SpinlockConfigRefType, AUTOMATIC, OS_VAR) SpinlockList;

    CurrentObject = OsApp_GetCurrent_ObjectInfo();
#if (OS_ARTI_TRACE_SPINLOCK == STD_ON)
    /* Released on behalf of a terminated object, before the hardware release (see ReleaseSpinlock). Also
       reached without the kernel lock (OsTask_ErrorReturn), so interrupts are suspended here (NOSUSP) */
    if(0xFFFFFFFFUL != Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->OwnerObjectID)
    {
        Os_IsrLevelType ArtiLevel;
        CoreIdType ArtiCore;
        OsIsr_SuspendISR(&ArtiLevel);
        ArtiCore = Os_Inf_GetCoreId();
        OS_ARTI_SPINLOCK_RELEASED(ArtiCore, SpinlockId);
        (void)ArtiCore;
        OsIsr_ResumeISR(ArtiLevel);
    }
#endif
    OsSpinlock_Hal_Releaselock(Os_SpinlockConfigSet[SpinlockId]->LockStatus);
    if(CurrentObject->ObjectType == OBJECT_ISR)
    {
        /* Get spinlock list */
        OsIsr_GetSpinLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &SpinlockList);
    }
    /* If current object is Task */
    else
    {
        /* Get spinlock list */
        OsTask_GetSpinLockList((CurrentObject->AppObjIDInfo & OBJECTID_MASK), &SpinlockList);
    }
    /* Pop spinlock list */
    OsSpinlock_Internal_ListPop(SpinlockList);
    /* Clear owner object ID */
    Os_SpinlockConfigSet[SpinlockId]->SpinlockRunningData->OwnerObjectID = 0xFFFFFFFFUL;

    /* Resume according to lockmethod */
    switch(Os_SpinlockConfigSet[SpinlockId]->OsSpinlockLockMethod)
    {
        case LOCK_ALL_INTERRUPTS:
        {
            OsIsr_ResumeAllInterrupts();
            break;
        }
        case LOCK_CAT2_INTERRUPTS:
        {
            OsIsr_ResumeOSInterrupts();
            break;
        }
        case LOCK_WITH_RES_SCHEDULER:
        {
            break;
        }
        case LOCK_NOTHING:
        {
            break;
        }
        default:
            break;
    }
}
