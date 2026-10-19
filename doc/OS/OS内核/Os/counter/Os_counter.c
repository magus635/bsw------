/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_counter.c
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
#include "Os_GeneralTypes.h"
#include "Os_counter_Lcfg.h"
#include "Os_isr.h"
#include "Os_task.h"
#include "Os_counter.h"
#include "Os_timer.h"
#include "Os_application.h"
#include "Os_hook.h"
#include "Os_alarm.h"
#include "Os_scheduletable.h"
#include "Os_services.h"
#include "Os_orti.h"
#include "Os_ArtiHooks.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define CASTCOUNTERNODEQUEUEDATATYPE(ptr)   ((P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR))ptr)

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
*   Function Name           : OsCounter_Internal_TickAdd
*   Service ID              : None.
*   Description             : Do tick add action and process overflow case.
*   Parameters in           : MaxAllowedValue : Max allowed counter value.
*   Parameters in           : Value : Add value.
*   Parameters in           : AddValue. Added parameter.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : TickType: Result of two ticks added with overflow processing.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(TickType, OS_CODE) OsCounter_Internal_TickAdd
(
    TickType MaxAllowedValue,
    TickType Value,
    TickType AddValue
);

/****************************************************************************************************
*   Function Name           : OsCounter_Internal_TickSub
*   Service ID              : None.
*   Description             : Do tick subtraction and process overflow case.
*   Parameters in           : MaxAllowedValue : Max allowed counter value.
*   Parameters in           : Value :  Subtracted Value.
*   Parameters inout        : SubValue. Subtraction Value.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : TickType: Result of two ticks subtraction with overflow processing
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(TickType, OS_CODE) OsCounter_Internal_TickSub
(
    TickType MaxAllowedValue,
    TickType Value,
    TickType SubValue
);

/****************************************************************************************************
*   Function Name           : OsCounter_Internal_UpdateCompareValue
*   Service ID              : None.
*   Description             : Update counter compare value to specified value.
*   Parameters in           : CounterCfg : Specified counter configuration pointer.
*   Parameters in           : Tick : The value to be updated to compareValue of counter.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsCounter_Internal_UpdateCompareValue
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg,
    TickType Tick
);

/****************************************************************************************************
*   Function Name           : OsCounter_Internal_GetCounterCfgInfo
*   Service ID              : None.
*   Description             : Get specified counter configuration pointer by CounterID.
*   Parameters in           : CounterID : Specified counter configuration pointer.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Specified counter configuration pointer.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST)
OsCounter_Internal_GetCounterCfgInfo
(
    CounterType CounterID
);

/****************************************************************************************************
*   Function Name           : OsCounter_Internal_QueueInit
*   Service ID              : None.
*   Description             : Initialize counter queue.
*   Parameters in           : CounterCfg: Counter configuration pointer.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE)OsCounter_Internal_QueueInit
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg
);

/****************************************************************************************************
*   Function Name           : OsCounter_Internal_AllocateNodeFromQueueHead
*   Service ID              : None.
*   Description             : Allocated one element node from specified queue.
*   Parameters in           : QueueHead :Pointer of queue head which will release one queue element.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Os_CounterNodeQueueDataType* : Pointer of queue element.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Os_CounterNodeQueueDataType*, OS_CODE) OsCounter_Internal_AllocateNodeFromQueueHead
(
    P2VAR(Os_CounterNodeQueueDataType*, TYPEDEF, OS_VAR) QueueHead
);

/****************************************************************************************************
*   Function Name           : OsCounter_Internal_InsertNodeToQueueHead
*   Service ID              : None.
*   Description             : Insert one queue element node to specified queue Head.
*   Parameters in           : QueueHead :Pointer of queue head which will add one queue element.
*   Parameters in           : InsertNode :Pointer of queue element to be add to queueHead.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsCounter_Internal_InsertNodeToQueueHead
(
    P2VAR(Os_CounterNodeQueueDataType*, TYPEDEF, OS_VAR) QueueHead,
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR) InsertNode
);

/****************************************************************************************************
*   Function Name           : OsCounter_Internal_RemoveNodeFromQueue
*   Service ID              : None.
*   Description             : Remove one queue node from specified queue by Object.
*   Parameters in           : QueueHead :Pointer of queue head.
*   Parameters in           : Object : Specified value of node element.
*   Parameters inout        : None.
*   Parameters out          : HeadChanged: TRUE indicates queue head has changed and
*                                          FALSE indicates queue head hasn't changed
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Os_CounterNodeQueueDataType*. Pointer of removed queue element.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Os_CounterNodeQueueDataType*, OS_CODE) OsCounter_Internal_RemoveNodeFromQueue
(
    P2VAR(Os_CounterNodeQueueDataType*, TYPEDEF, OS_VAR)  QueueHead,
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) Object,
    uint32* HeadChanged
);

/****************************************************************************************************
*   Function Name           : OsCounter_Internal_IsFutureValue
*   Service ID              : None.
*   Description             : Judge value is later fefValue or not.
*   Parameters in           : CounterCfg :Pointer of counter configuration.
*   Parameters in           : Value :
*   Parameters in           : ReferenceValue : Reference value
*   Parameters inout        : None.
*   Parameters out          : None:
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : boolean. TRUE indicates value is later ReferenceValue.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, OS_CODE) OsCounter_Internal_IsFutureValue
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg,
    TickType Value,
    TickType ReferenceValue
);

/****************************************************************************************************
*   Function Name           : OsCounter_Internal_GetCurrentValue
*   Service ID              : None.
*   Description             : Get specified counter value.
*   Parameters in           : CounterCfg :Pointer of counter configuration.
*   Parameters inout        : None.
*   Parameters out          : None:
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : TickType. Return count value.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(TickType, OS_CODE) OsCounter_Internal_GetCurrentValue
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg
);

/****************************************************************************************************
*   Function Name           : OsCounter_Internal_GetCountLimitedValue
*   Service ID              : None.
*   Description             : Get the limited counter value of specified counter.
*   Parameters in           : CounterCfg :Pointer of counter configuration.
*   Parameters inout        : None.
*   Parameters out          : None:
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : TickType. Return limited counter value.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(TickType, OS_CODE) OsCounter_Internal_GetCountLimitedValue
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg
);

/****************************************************************************************************
*   Function Name           : OsCounter_Internal_DoObject
*   Service ID              : None.
*   Description             : Do object callback if object expiration is reached.
*   Parameters in           : CounterCfg :Pointer of counter configuration.
*   Parameters inout        : None.
*   Parameters out          : None:
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsCounter_Internal_DoObject
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg
);

/****************************************************************************************************
*   Function Name           : OsCounter_Internal_ProcessOverFlowObject
*   Service ID              : None.
*   Description             : When counter value is set to 0, adjust all node expiration time to
*                             [0, MaxAllowedValue] if related node expiration is larger than
*                             MaxAllowedValue. When OsCounetr_AddRelObject/OsCounter_AddAbsObject is
*                             called, related object expiration is set to [0, 2*MaxAllowedValue + 1].
*   Parameters in           : CounterCfg :Pointer of counter configuration.
*   Parameters inout        : None.
*   Parameters out          : None:
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsCounter_Internal_ProcessOverFlowObject
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg
);

/****************************************************************************************************
*   Function Name           : OsCounter_Internal_IncrementCounter
*   Service ID              : None.
*   Description             : Increment counter and call related callback. When parameter DoTaskSchedule
*                             is set to True, do Task schedule at this function. When stack flow is
*                             from IncrementCounter service, DoSchedule should be set to TRUE, other stack
*                             flow should be set to FALSE.
*   Parameters in           : CounterID :counter identification.
*   Parameters in           : DoTaskSchedule: TRUE indicates to do task schedule at this function.
*   Parameters inout        : None.
*   Parameters out          : None:
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType. E_OK indicates success and others indicate failure.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsCounter_Internal_IncrementCounter
(
    CounterType CounterID
);
/****************************************************************************************************
**                          End Private Function Definitions                                       **
****************************************************************************************************/
static FUNC(TickType, OS_CODE) OsCounter_Internal_TickAdd
(
    TickType MaxAllowedValue,
    TickType Value,
    TickType AddValue
)
{
    TickType Tick;
    if(Value > MaxAllowedValue - AddValue)
    {
        Tick = Value - MaxAllowedValue + AddValue + 1;
    }
    else
    {
        Tick = Value + AddValue;
    }
    return Tick;
}

static FUNC(TickType, OS_CODE) OsCounter_Internal_TickSub
(
    TickType MaxAllowedValue,
    TickType Value,
    TickType SubValue
)
{
    TickType Result;
    if (Value >= SubValue)
    {
        Result = Value - SubValue;
    }
    else
    {
        Result = MaxAllowedValue - SubValue + Value + 1;
    }
    return Result;
}

static FUNC(void, OS_CODE) OsCounter_Internal_UpdateCompareValue
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg,
    TickType Tick
)
{
    Os_TickType Now;
    Os_TickType Mask;
    Os_TickType CompareRegVale;
    if (NULL_PTR != CounterCfg->HwCfg
        && TIMER_DRIVER_HRTTIMER == CounterCfg->HwCfg->HwTimerType)
    {
        Mask = (Os_TickType)CounterCfg->CounterAttr.MaxAllowedCountValue;
        OsTimer_HrtGetCurrentValue(CounterCfg->HwCfg->TimerCfg.HrtCfg, &Now);
        CompareRegVale = (Now & (~Mask)) + Tick;
        OsTimer_HrtSetCompareRegValue(CounterCfg->HwCfg->TimerCfg.HrtCfg, CompareRegVale);
    }
    else
    {
        /*For Software, PIT and FRT timer*/
        if (Tick > CounterCfg->CounterAttr.MaxAllowedCountValue)
        {
            Tick -= (CounterCfg->CounterAttr.MaxAllowedCountValue + 1);
        }
        CounterCfg->RunningData->CompareValue = Tick;
    }
}

static P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST)
OsCounter_Internal_GetCounterCfgInfo
(
    CounterType CounterID
)
{
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg;

    if (CounterID < OS_COUNTER_TOTAL_NUM)
    {
        CounterCfg = Os_CounterConfigSet[CounterID];
    }
    else
    {
        /*panic here.*/
        CounterCfg = NULL_PTR;
    }

   return CounterCfg;
}

static FUNC(Os_CounterNodeQueueDataType*, OS_CODE)
OsCounter_Internal_AllocateNodeFromQueueHead
(
    P2VAR(Os_CounterNodeQueueDataType*, TYPEDEF, OS_VAR) QueueHead
)
{
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR) AllocatedQueue;
    AllocatedQueue          = (*QueueHead);
    (*QueueHead)            = AllocatedQueue->Next;
    AllocatedQueue->Next    = NULL_PTR;
    return AllocatedQueue;
}

static FUNC(void, OS_CODE) OsCounter_Internal_InsertNodeToQueueHead
(
    P2VAR(Os_CounterNodeQueueDataType*, TYPEDEF, OS_VAR) QueueHead,
    P2VAR(Os_CounterNodeQueueDataType  , TYPEDEF, OS_VAR) InsertNode
)
{
    InsertNode->Next = (*QueueHead);
    (*QueueHead) = InsertNode;
}

static FUNC(boolean, OS_CODE) OsCounter_Internal_InsertNodeToPrioQueue
(
    P2VAR(Os_CounterNodeQueueDataType*, TYPEDEF, OS_VAR)  QueueHead,
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR)   NewNode
)
{
    TickType Tick;
    boolean HeadChanged;
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR) TempNode;
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR) PrevNode;

    if (NULL_PTR == *QueueHead)
    {
        (*QueueHead) = NewNode;
        HeadChanged = TRUE;
    }
    else
    {
        PrevNode = NULL_PTR;
        TempNode = *QueueHead;
        Tick = *(NewNode->Object->ObjectDataInfo.NodeInfo->ExpTime);

        while(NULL_PTR != TempNode
              && (*(TempNode->Object->ObjectDataInfo.NodeInfo->ExpTime) <= Tick))
        {
            PrevNode = TempNode;
            TempNode = TempNode->Next;
        }

        NewNode->Next = TempNode;
        if (NULL_PTR == PrevNode)
        {
            *QueueHead  = NewNode;
            HeadChanged = TRUE;
        }
        else
        {
            PrevNode->Next = NewNode;
            HeadChanged    = FALSE;
        }
    }
    return HeadChanged;
}

static FUNC(Os_CounterNodeQueueDataType*, OS_CODE) OsCounter_Internal_RemoveNodeFromQueue
(
    P2VAR(Os_CounterNodeQueueDataType*, TYPEDEF, OS_VAR)  QueueHead,
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) Object,
    uint32* HeadChanged
)
{
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR) TempNode;
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR) PrevNode;

    *HeadChanged = FALSE;
    PrevNode = NULL_PTR;
    TempNode = *QueueHead;
    /* Look up the specified node. */
    while(NULL_PTR != TempNode && TempNode->Object != Object)
    {
        PrevNode = TempNode;
        TempNode = TempNode->Next;
    }

    /* Find out the Node*/
    if (NULL_PTR != TempNode && TempNode->Object == Object)
    {
        /*Remove Node from Queue Head.*/
        if (NULL_PTR == PrevNode)
        {
            *QueueHead = TempNode->Next;
            *HeadChanged = TRUE;
        }
        else
        {
            PrevNode->Next = TempNode->Next;
        }
        TempNode->Next = NULL_PTR;
    }
    else
    {
        TempNode = NULL_PTR;
    }
    return TempNode;
}

static FUNC(void, OS_CODE)OsCounter_Internal_QueueInit
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg
)
{
    uint32 Index;
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR)  FreeQueueHead;

    /*Initialize Element Relationship*/
    FreeQueueHead = CASTCOUNTERNODEQUEUEDATATYPE(CounterCfg->QueueMemCfg->FreeQueueHead);

    for (Index = 0; Index < CounterCfg->QueueMemCfg->Size - 1; Index++)
    {
        FreeQueueHead[Index].Next = &FreeQueueHead[Index + 1];
    }
    FreeQueueHead[Index].Next  = NULL_PTR;

    /*Set Counter NodeQueue Head.*/
    CounterCfg->NodeQueue->UsedQueue = NULL_PTR;
    CounterCfg->NodeQueue->FreeQueue = FreeQueueHead;
}

static FUNC(boolean, OS_CODE) OsCounter_Internal_IsFutureValue
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg,
    TickType Value,
    TickType ReferenceValue
)
{
    boolean Result;
    TickType Difference;
    if (Value > ReferenceValue)
    {
        Difference = Value - ReferenceValue;
        Result = (boolean)(Difference <= CounterCfg->CounterAttr.MaxDifferenceValue);
    }
    else if (Value < ReferenceValue)
    {
        Difference = ReferenceValue - Value;
        Result = (boolean)(Difference > CounterCfg->CounterAttr.MaxDifferenceValue);
    }
    else
    {
        Result = FALSE;
    }
    return Result;
}

static FUNC(TickType, OS_CODE) OsCounter_Internal_GetCountLimitedValue
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg
)
{
    TickType Result = 0;
    Os_TickType Tick = 0;

    if((COUNTER_DRIVER_SOFTERWARE == CounterCfg->DriverType)
      ||(TIMER_DRIVER_FRTTIMER == CounterCfg->HwCfg->HwTimerType)
      ||(TIMER_DRIVER_PITTIMER == CounterCfg->HwCfg->HwTimerType))
    {
        Result = CounterCfg->RunningData->CountValue;
    }
    else if (TIMER_DRIVER_HRTTIMER == CounterCfg->HwCfg->HwTimerType)
    {
        OsTimer_HrtGetCurrentValue(CounterCfg->HwCfg->TimerCfg.HrtCfg, &Tick);
        Result = (TickType)(Tick & (2*CounterCfg->CounterAttr.MaxAllowedCountValue + 1));
    }
    else
    {
        /*panic here.*/
        while(1);
    }
    return Result;
}

static FUNC(TickType, OS_CODE) OsCounter_Internal_GetCurrentValue
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg
)
{
    TickType Result = 0;
    Os_TickType Tick = 0;

    if((COUNTER_DRIVER_SOFTERWARE == CounterCfg->DriverType)
      ||(TIMER_DRIVER_FRTTIMER == CounterCfg->HwCfg->HwTimerType)
      ||(TIMER_DRIVER_PITTIMER == CounterCfg->HwCfg->HwTimerType))
    {
        Result = CounterCfg->RunningData->CountValue;
    }
    else if (TIMER_DRIVER_HRTTIMER == CounterCfg->HwCfg->HwTimerType)
    {
        OsTimer_HrtGetCurrentValue(CounterCfg->HwCfg->TimerCfg.HrtCfg, &Tick);
        Result = (TickType)(Tick & CounterCfg->CounterAttr.MaxAllowedCountValue);
    }
    else
    {
        /*panic here.*/
       CodeFreeze();
    }
    return Result;
}

static FUNC(void, OS_CODE) OsCounter_Internal_CalAbsExpirationTime
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg,
    TickType Now,
    TickRefType Tick
)
{
    if (*Tick < Now)
    {
        *Tick += ( CounterCfg->CounterAttr.MaxAllowedCountValue + 1);
    }
}

static FUNC(void, OS_CODE) OsCounter_Internal_DoObject
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg
)
{
    TickType Now;
    TickType ExpTime;
    uint32 ObjectCount;
    Os_IsrLevelType Level;
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR) Node;
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR) RemovedNode;

    ObjectCount = 0;
    RemovedNode = NULL_PTR;
    OsIsr_SuspendISR(&Level);
    Node = CounterCfg->NodeQueue->UsedQueue;

    while (NULL_PTR != Node)
    {
        /*Get Queue Head Expiration TIme.*/
        ExpTime = *(Node->Object->ObjectDataInfo.NodeInfo->ExpTime);
        /*Get Counter Current Value.*/
        Now = OsCounter_Internal_GetCountLimitedValue(CounterCfg);
        /*Save for next loop here.*/
        Node = Node->Next;
        /*Call related Callback if ExpirationTime is Reached.*/
        if (!OsCounter_Internal_IsFutureValue(CounterCfg, ExpTime, Now))
        {
            /*Remove Node from UsedQueue.*/
            RemovedNode = OsCounter_Internal_AllocateNodeFromQueueHead(&CounterCfg->NodeQueue->UsedQueue);
            /* call related callback. this callback may insert Object. */
            if (OBJECT_ALARM == RemovedNode->Object->ObjectType)
            {
                 OsAlarm_DoAlarm(RemovedNode->Object);
            }
            else if (OBJECT_SCHEDULETABLE == RemovedNode->Object->ObjectType)
            {
                OsSchedT_DoSchedulTable(RemovedNode->Object);
            }
            else
            {
                /*panic here.*/
            }
            /*Insert RemovedNode to FreeQueue. */
            OsCounter_Internal_InsertNodeToQueueHead(&CounterCfg->NodeQueue->FreeQueue, RemovedNode);
            /* Enable Interrupt if process more than OS_COUNTER_MAX_OBJECT_EXECS_PER_LOCK objects */
            ObjectCount++;
            if (ObjectCount > OS_COUNTER_MAX_OBJECT_EXECS_PER_LOCK)
            {
                ObjectCount = 0;
                /* Enable Interrupt for a short time for high interrupt preemption here.*/
                OsIsr_ResumeISR(Level);
                OsIsr_SuspendISR(&Level);
            }
        }
        else
        {
            break;
        }
    }

    /* update compare value if necessary. */
    Node = CounterCfg->NodeQueue->UsedQueue;
    if (NULL_PTR != Node)
    {
        ExpTime = *(Node->Object->ObjectDataInfo.NodeInfo->ExpTime);
        OsCounter_Internal_UpdateCompareValue(CounterCfg, ExpTime);
    }
    else
    {
        /* set compare value far from here .*/
        ExpTime = CounterCfg->CounterAttr.MaxAllowedCountValue
                + CounterCfg->RunningData->CountValue;
        OsCounter_Internal_UpdateCompareValue(CounterCfg, ExpTime);
    }

    OsIsr_ResumeISR(Level);
    Os_Inf_Dsync();
}

static FUNC(void, OS_CODE) OsCounter_Internal_ProcessOverFlowObject
(
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg
)
{
    TickRefType Tick;
    Os_IsrLevelType Level;
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR) Node;

    OsIsr_SuspendISR(&Level);
    Node = CounterCfg->NodeQueue->UsedQueue;
    while (NULL_PTR != Node)
    {
        Tick = Node->Object->ObjectDataInfo.NodeInfo->ExpTime;
        if (*Tick > CounterCfg->CounterAttr.MaxAllowedCountValue)
        {
            *Tick -= (CounterCfg->CounterAttr.MaxAllowedCountValue + 1);
        }
        Node = Node->Next;
    }
    OsIsr_ResumeISR(Level);
}

static FUNC(StatusType, OS_CODE) OsCounter_Internal_IncrementCounter
(
    CounterType CounterID
)
{
    StatusType Status;
    P2CONST(Os_CounterConfigType, TYPEDEF, CONST) CounterCfg;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_INCREMENTCOUNTER);
    OS_ARTI_SC_BEGIN(IncrementCounter, CounterID);

    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);

    if (OsService_ExtendedErrorCheck(CounterID >= OS_COUNTER_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(COUNTER_DRIVER_SOFTERWARE != CounterCfg->DriverType))
    {
        Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_INCREMENTCOUNTER)))
    {
        Status = E_OS_CALLEVEL;
    }
    else if (TRUE != OsApp_CheckObjectAccessingAppMask(CounterCfg->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if (OsService_ExtendedErrorCheck(FALSE == OsKernel_CheckObjectBelongToCurrentCore(CounterCfg->ObjectID)))
    {
        Status = E_OS_CORE;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(TRUE != OsApp_CheckObjectAppIsAccessiable(CounterID))
    {
        Status = E_OS_ACCESS;
    }
    else
    {
        Status = E_OK;
        OsCounter_IncrementCounter(CounterID, TRUE);
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterOne(OS_SERVICEID_INCREMENTCOUNTER, (InputParaType)CounterID);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(IncrementCounter, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_INCREMENTCOUNTER);

    return Status;
}

static FUNC(StatusType, OS_CODE) OsCounter_Internal_GetCounterValue
(
    CounterType CounterID,
    TickRefType Value
)
{
    StatusType Status;
    P2CONST(Os_CounterConfigType, TYPEDEF, CONST) CounterCfg;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_GETCOUNTERVALUE);
    OS_ARTI_SC_BEGIN(GetCounterValue, CounterID);

    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);
    if (OsService_ExtendedErrorCheck(CounterID >= OS_COUNTER_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_GETCOUNTERVALUE)))
    {
        Status = E_OS_CALLEVEL;
    }
    else if (TRUE != OsApp_CheckObjectAccessingAppMask(CounterCfg->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if (OsService_ExtendedErrorCheck(FALSE == OsKernel_CheckObjectBelongToCurrentCore(CounterCfg->ObjectID)))
    {
        Status = E_OS_CORE;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(TRUE != OsApp_CheckObjectAppIsAccessiable(CounterID))
    {
        Status = E_OS_ACCESS;
    }
    else
    {
        Status = E_OK;
        OsCounter_GetCounterValue(CounterID, Value);
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_GETCOUNTERVALUE, (InputParaType)CounterID, (InputParaType)Value);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(GetCounterValue, (E_OK == Status) ? (uint32)(*Value) : OS_ARTI_SC_INVALID);
    OsOrti_ServiceEnd(OS_SERVICEID_GETCOUNTERVALUE);

    return Status;
}

static FUNC(StatusType, OS_CODE) OsCounter_Internal_GetElapsedValue
(
    CounterType CounterID,
    TickRefType Value,
    TickRefType ElapsedValue
)
{
    StatusType Status;
    Os_IsrLevelType Level;
    P2CONST(Os_CounterConfigType, TYPEDEF, CONST) CounterCfg;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_GETELAPSEDVALUE);
    OS_ARTI_SC_BEGIN(GetElapsedValue, CounterID);

    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);

    if (OsService_ExtendedErrorCheck(CounterID >= OS_COUNTER_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_GETELAPSEDVALUE)))
    {
        Status = E_OS_CALLEVEL;
    }
    else if (TRUE != OsApp_CheckObjectAccessingAppMask(CounterCfg->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if (OsService_ExtendedErrorCheck(FALSE == OsKernel_CheckObjectBelongToCurrentCore(CounterCfg->ObjectID)))
    {
        Status = E_OS_CORE;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if (OsService_ExtendedErrorCheck(*Value > CounterCfg->CounterAttr.MaxAllowedCountValue))
    {
        Status = E_OS_VALUE;
    }
    else if(TRUE != OsApp_CheckObjectAppIsAccessiable(CounterID))
    {
        Status = E_OS_ACCESS;
    }
    else
    {
        Status = OsCounter_GetElapsedValue(CounterID, Value, ElapsedValue);
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterThree(OS_SERVICEID_GETCOUNTERVALUE, (InputParaType)CounterID, (InputParaType)Value, (InputParaType)ElapsedValue);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(GetElapsedValue, (E_OK == Status) ? (uint32)(*ElapsedValue) : OS_ARTI_SC_INVALID);
    OsOrti_ServiceEnd(OS_SERVICEID_GETELAPSEDVALUE);

    return Status;
}

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
FUNC(void, OS_CODE) OsCounter_Init
(
    CounterType CounterID
)
{
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_VAR) CounterCfg;
    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);

    OsTimer_Init(CounterCfg->HwCfg);
    /*For HRT, RunningData is configured to zero.*/
    if (NULL_PTR != CounterCfg->RunningData)
    {
        CounterCfg->RunningData->CountValue = 0;
        OsCounter_Internal_UpdateCompareValue(CounterCfg, 0);
    }

    OsCounter_Internal_QueueInit(CounterCfg);
}

FUNC(void, OS_CODE) OsCounter_Start
(
    CounterType CounterID
)
{
    Os_IsrLevelType Level;
    P2CONST(Os_TimerFrtHwConfigType, TYPEDEF, OS_CONST)   FrtCfg;
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg;
    P2VAR(Os_CounterFrtRunningDataType, TYPEDEF, OS_VAR) FrtRunningData;

    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);

    if (COUNTER_DRIVER_HARDWARE == CounterCfg->DriverType)
    {
        OsIsr_SuspendISR(&Level);
        if (TIMER_DRIVER_FRTTIMER == CounterCfg->HwCfg->HwTimerType)
        {
            /*Record start time.*/
            FrtCfg = CounterCfg->HwCfg->TimerCfg.FrtCfg;
            FrtRunningData = (P2VAR(Os_CounterFrtRunningDataType, TYPEDEF, OS_VAR))
                 CounterCfg->RunningData;
            /*Get current Counter Value*/
            OsTimer_PfrtGetCounterRegValue(FrtCfg, &FrtRunningData->CompareRegValue);
            /*Start timer and enable interrupt.*/
            OsTimer_Start(CounterCfg->HwCfg);
            /*Calculate Next Compare Register Value*/
            OsTimer_PfrtCalNextTickCompareValue(FrtCfg, &FrtRunningData->CompareRegValue);
            /*Set Next Compare Register Value for Next Tick Interrupt.*/
            OsTimer_PfrtSetNextTickCompareValue(FrtCfg, FrtRunningData->CompareRegValue);
        }
        else
        {
            OsTimer_Start(CounterCfg->HwCfg);
        }

        OsIsr_ResumeISR(Level);
    }
}

FUNC(void, OS_CODE) OsCounter_AddAbsObject
(
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) Object
)
{
    TickType Now;
    TickRefType Tick;

    boolean HeadChanged;
    Os_IsrLevelType Level;
    CounterType CounterID;

    P2CONST(Os_CounterConfigType, TYPEDEF, OS_VAR) CounterCfg;
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR) Node;

    CounterID = Object->ObjectDataInfo.NodeInfo->CounterID;
    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);

    OsIsr_SuspendISR(&Level);
    /*Allocate a Node from Free Queue.*/
    Node = OsCounter_Internal_AllocateNodeFromQueueHead(&CounterCfg->NodeQueue->FreeQueue);
    if (NULL_PTR != Node)
    {
        /*Fill Object information*/
        Node->Object = Object;
        /* Adjust Expiration according to setting.*/
        Tick = Object->ObjectDataInfo.NodeInfo->ExpTime;
        Now = OsCounter_Internal_GetCurrentValue(CounterCfg);
        OsCounter_Internal_CalAbsExpirationTime(CounterCfg, Now, Tick);

        /*Insert Node to UsedQueue.*/
        HeadChanged = OsCounter_Internal_InsertNodeToPrioQueue(&CounterCfg->NodeQueue->UsedQueue, Node);
        if (HeadChanged)
        {
            OsCounter_Internal_UpdateCompareValue(CounterCfg, *Tick);
        }
        Os_Inf_Dsync();
    }
    else
    {
        CodeFreeze();
    }

    OsIsr_ResumeISR(Level);

}

FUNC(void, OS_CODE) OsCounter_AddRelObject
(
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) Object
)
{
    TickType  Now;
    TickRefType  Tick;

    Os_IsrLevelType Level;
    CounterType CounterID;
    boolean HeadChanged;
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_VAR) CounterCfg;
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR) Node;

    Tick = Object->ObjectDataInfo.NodeInfo->ExpTime;
    CounterID = Object->ObjectDataInfo.NodeInfo->CounterID;
    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);
    /*Change to Absolute Tick, range [0, 2*MaxAllowedValue + 1].*/
    OsIsr_SuspendISR(&Level);
    /*Get Current Timer Value.*/
    Now = OsCounter_Internal_GetCurrentValue(CounterCfg);
    /*Calculate Expiration Time of Object.*/
    *Tick = OsCounter_Internal_TickAdd(2 * CounterCfg->CounterAttr.MaxAllowedCountValue + 1,
            Now, *Tick);

    /*Allocate a Node from Free Queue.*/
    Node = OsCounter_Internal_AllocateNodeFromQueueHead(&CounterCfg->NodeQueue->FreeQueue);
    if (NULL_PTR != Node)
    {
        /*Fill Object information*/
        Node->Object = Object;

        /*Insert Node to UsedQueue.*/
        HeadChanged = OsCounter_Internal_InsertNodeToPrioQueue(&CounterCfg->NodeQueue->UsedQueue, Node);
        if (HeadChanged)
        {
            OsCounter_Internal_UpdateCompareValue(CounterCfg, *Tick);
        }
        Os_Inf_Dsync();
    }
    else
    {
        CodeFreeze();
    }

    OsIsr_ResumeISR(Level);
}

FUNC(StatusType, OS_CODE) OsCounter_RemoveObject
(
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) Object
)
{
    TickType Tick;
    StatusType Status;
    uint32 HeadChanged;
    CounterType CounterID;
    Os_IsrLevelType Level;
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_VAR) CounterCfg;
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR) Node;
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR) NodeHead;

    Status = E_NOT_OK;
    CounterID = Object->ObjectDataInfo.NodeInfo->CounterID;
    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);

    OsIsr_SuspendISR(&Level);
    /*Remove Object from UsedQueue.*/
    Node = OsCounter_Internal_RemoveNodeFromQueue(&CounterCfg->NodeQueue->UsedQueue,
            Object, &HeadChanged);

    if (NULL_PTR != Node)
    {
        Status = E_OK;
        /*Add Node to FreeQueue.*/
        OsCounter_Internal_InsertNodeToQueueHead(&CounterCfg->NodeQueue->FreeQueue, Node);
        /*update Compare Value if Head Changed.*/
        NodeHead = CounterCfg->NodeQueue->UsedQueue;
        if (HeadChanged)
        {
            if (NULL_PTR != NodeHead)
            {
                Tick = *(NodeHead->Object->ObjectDataInfo.NodeInfo->ExpTime);
                OsCounter_Internal_UpdateCompareValue(CounterCfg, Tick);
            }
            else
            {
                /* set compare value far from now .*/
                Tick = CounterCfg->CounterAttr.MaxAllowedCountValue
                        + CounterCfg->RunningData->CountValue;
                OsCounter_Internal_UpdateCompareValue(CounterCfg, Tick);
            }
            Os_Inf_Dsync();
        }
        else
        {
            /*Do nothing here.*/
        }
    }

    OsIsr_ResumeISR(Level);
    return Status;
}

FUNC(StatusType, OS_CODE) OsCounter_GetObjectRelTick
(
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) Object,
    TickRefType Tick
)
{
    TickType Now;
    StatusType Status;
    CounterType CounterID;
    Os_IsrLevelType Level;
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg;
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR) Node;

    Status = E_NOT_OK;
    CounterID = Object->ObjectDataInfo.NodeInfo->CounterID;
    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);

    OsIsr_SuspendISR(&Level);
    Node = CounterCfg->NodeQueue->UsedQueue;
    while (NULL_PTR != Node)
    {
        if (Node->Object == Object)
        {
            Status = E_OK;
            Now = OsCounter_Internal_GetCurrentValue(CounterCfg);
            *Tick = OsCounter_Internal_TickSub(CounterCfg->CounterAttr.MaxAllowedCountValue,
                    *(Object->ObjectDataInfo.NodeInfo->ExpTime),
                    Now);
            break;
        }
        else
        {
            Node = Node->Next;
        }
    }

    OsIsr_ResumeISR(Level);
    return Status;
}

FUNC(void, OS_CODE) OsCounter_IncrementCounter
(
    CounterType CounterID,
    boolean     DoSchedule
)
{
    Os_IsrLevelType Level;
    P2CONST(Os_CounterConfigType, TYPEDEF, CONST) CounterCfg;

    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);
    if (CounterCfg->RunningData->CountValue == CounterCfg->CounterAttr.MaxAllowedCountValue)
    {
        CounterCfg->RunningData->CountValue = 0;
        OsCounter_Internal_ProcessOverFlowObject(CounterCfg);
    }
    else
    {
        (CounterCfg->RunningData->CountValue)++;
    }
    Os_Inf_Dsync();

    if (CounterCfg->RunningData->CountValue == CounterCfg->RunningData->CompareValue)
    {
        OsCounter_Internal_DoObject(CounterCfg);
        if (DoSchedule)
        {
            OsIsr_SuspendISR(&Level);
            OsTask_DoScheduling(SAVING_CONTEXT);
            OsIsr_ResumeISR(Level);
        }
    }
    else
    {
        /*Do nothing here.*/
    }
}

FUNC(void, OS_CODE) OsCounter_GetCounterValue
(
    CounterType CounterID,
    TickRefType Value
)
{
    Os_IsrLevelType Level;
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg;

    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);
    OsIsr_SuspendISR(&Level);
    *Value = OsCounter_Internal_GetCurrentValue(CounterCfg);
    OsIsr_ResumeISR(Level);
}

FUNC(StatusType, OS_CODE) OsCounter_GetElapsedValue
(
    CounterType CounterID,
    TickRefType Value,
    TickRefType ElapsedValue
)
{
    TickType Now;
    Os_IsrLevelType Level;
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg;

    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);

    OsIsr_SuspendISR(&Level);

    Now = OsCounter_Internal_GetCurrentValue(CounterCfg);
    *ElapsedValue = OsCounter_Internal_TickSub(CounterCfg->CounterAttr.MaxAllowedCountValue,
          Now, *Value);
    *Value = Now;

    OsIsr_ResumeISR(Level);

    return E_OK;
}

FUNC(P2CONST(Os_CounterAttributeConfigType, TYPEDEF, OS_CONST), OS_CODE) OsCounter_GetBaseInfo
(
    CounterType CounterID
)
{
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg;

    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);
    return (P2CONST(Os_CounterAttributeConfigType, TYPEDEF, OS_CONST)) &(CounterCfg->CounterAttr);
}

FUNC(StatusType, OS_CODE) IncrementCounter
(
    CounterType CounterID
)
{
    StatusType Status;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsCounter_Internal_IncrementCounter(CounterID);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsCounter_Internal_IncrementCounter(CounterID);
    }

    return Status;
}

FUNC(StatusType, OS_CODE) GetCounterValue
(
    CounterType CounterID,
    TickRefType Value
)
{
    StatusType Status;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsCounter_Internal_GetCounterValue(CounterID, Value);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsCounter_Internal_GetCounterValue(CounterID, Value);
    }

    return Status;
}

FUNC(StatusType, OS_CODE) GetElapsedValue
(
    CounterType CounterID,
    TickRefType Value,
    TickRefType ElapsedValue
)
{
    StatusType Status;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsCounter_Internal_GetElapsedValue(CounterID, Value, ElapsedValue);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsCounter_Internal_GetElapsedValue(CounterID, Value, ElapsedValue);
    }

    return Status;
}

ISR(OsCounter_PitService)
{
    CounterType CounterID;
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST)  ObjectInfo;
    P2CONST(Os_TimerPitHwConfigType, TYPEDEF, OS_CONST) PitCfg;

    ObjectInfo = OsApp_GetCurrent_ObjectInfo();
    CounterID = (ObjectInfo->AppObjIDInfo & COUNTERID_MASK) >> 24;
    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);
    PitCfg = CounterCfg->HwCfg->TimerCfg.PitCfg;

    /*Acknowledge Interrupt and Reload for Next Interrupt.*/
    OsTimer_PitAckAndReloadInterrupt(PitCfg);

    /*Increment Count and call related callback if necessary.*/
    OsCounter_IncrementCounter(CounterID, FALSE);
}

ISR(OsCounter_PfrtService)
{
    CounterType CounterID;
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST)  ObjectInfo;
    P2CONST(Os_TimerFrtHwConfigType, TYPEDEF, OS_CONST) FrtCfg;
    P2VAR(Os_CounterFrtRunningDataType, TYPEDEF, OS_VAR) FrtRunningData;

    ObjectInfo = OsApp_GetCurrent_ObjectInfo();
    CounterID = (ObjectInfo->AppObjIDInfo & COUNTERID_MASK) >> 24;
    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);
    FrtCfg = CounterCfg->HwCfg->TimerCfg.FrtCfg;
    FrtRunningData = (P2VAR(Os_CounterFrtRunningDataType, TYPEDEF, OS_VAR))CounterCfg->RunningData;

    /*Acknowledge PRT Interrupt.*/
    OsTimer_FrtAckInterrupt(FrtCfg);

    /*Increment Counter and call related function if necessary, do not schedule task/ISR here.*/
    OsCounter_IncrementCounter(CounterID, FALSE);

    /*Calculate Next Compare Register Value*/
    OsTimer_PfrtCalNextTickCompareValue(FrtCfg, &FrtRunningData->CompareRegValue);

    /*Set Next Compare Register Value for Next Tick Interrupt.*/
    OsTimer_PfrtSetNextTickCompareValue(FrtCfg, FrtRunningData->CompareRegValue);
}

ISR(OsCounter_HrtService)
{
    CounterType CounterID;
    boolean ReachHrtLimitedTime;
    P2CONST(Os_CounterConfigType, TYPEDEF, OS_CONST) CounterCfg;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST)  ObjectInfo;
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST) HrtCfg;

    ObjectInfo = OsApp_GetCurrent_ObjectInfo();
    CounterID = (ObjectInfo->AppObjIDInfo & COUNTERID_MASK) >> 24;
    CounterCfg = OsCounter_Internal_GetCounterCfgInfo(CounterID);
    /*Get HRT Timer Handler.*/
    HrtCfg = CounterCfg->HwCfg->TimerCfg.HrtCfg;
    /*Acknowledge HRT Interrupt.*/
    OsTimer_HrtAckInterrupt(HrtCfg);

    /*Judge HRT timer whether reached Limited Time.*/
    ReachHrtLimitedTime = OsTimer_HrtReachedLimitedTime(HrtCfg);

    if (ReachHrtLimitedTime)
    {
        /* call related callback function.*/
        OsCounter_Internal_DoObject(CounterCfg);
    }
    else
    {
        /*set compare register value according to the logical compare value. */
        OsTimer_HrtSetCompareRegValue(HrtCfg, HrtCfg->RunningData->Compare);
    }
}
#define OS_STOP_SEC_CODE_QM_GLOBAL
#include "Os_memmap.h"
