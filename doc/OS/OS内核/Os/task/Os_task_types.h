/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_task_types.h
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
#ifndef OS_TASK_TYPES_H_
#define OS_TASK_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Os_GeneralTypes.h"
#include "Os_application_Cfg.h"
#include "Os_event_types.h"
#include "Os_task_Cfg.h"
#include "Os_isr_types.h"
#include "Os_kernel_Cfg.h"

#include "Os_lock_types.h"
#include "Os_spinlock_types.h"
#include "Os_ArtiCfg.h"
/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    RUNNING,
    READY,
    WAITING,
    SUSPENDED
} TaskStateType;

typedef enum
{
    NOT_SAVING_CONTEXT,
    SAVING_CONTEXT
} Os_SchedulingChoiceType;
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
typedef uint32 TaskType;
typedef TaskType* TaskRefType;
typedef TaskStateType* TaskStateRefType;

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
typedef struct
{
    P2VAR(uint32, TYPEDEF, OS_VAR) Buffer;
    uint32 PushIndex;
    uint32 PopIndex;
    uint32 QueueSize;
}Os_FifoQueueType;

typedef struct
{
    TaskType CurrentTask;
    uint32 CurrentPriority;
    P2VAR(uint32, AUTOMATIC, OS_VAR) PriorityLowerArray;
    uint32 PriorityUpperArray;
    P2VAR(Os_FifoQueueType, AUTOMATIC, OS_VAR) FifoQueue;
}Os_SchedulerType;

typedef struct
{
    uint32 ActivationCount;
    TaskStateType State;
    EventMaskType EventSet;
    EventMaskType EventWait;
    /* Resource/Spinlock used by ISR */
    Os_LockConfigRefType LockList;
    /* Spinlock used by ISR */
    Os_SpinlockConfigRefType SpinlockOccupied;
#if (OS_ARTI_TRACE_TASK == STD_ON)
    /* ARTI shadow state (OS_ARTI_TASK_*): the task state as described by the ARTI trace events */
    uint8 ArtiState;
#endif
}Os_TaskDynamicType;

typedef struct
{
    uint32 ObjectID;
    uint32 HomePriority;
    uint32 RunningPriority;
    uint32 AutoStart;
    uint32 MaxActivationCount;
    boolean IsExtended;
    P2VAR(Os_TaskDynamicType, AUTOMATIC, OS_VAR) Os_TaskRunningData;
}Os_TaskConstType;

typedef struct
{
    P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST) TaskConfigPtr[TOTAL_TASK_NUM + 1];
}Os_TaskConfigType;

#endif /* OS_TASK_TYPES_H_ */
/****************************************************************************************************
**     End of File: Os_task_types.h                                                                      **
****************************************************************************************************/

