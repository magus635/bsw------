/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_task.h
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
#ifndef OS_TASK_H_
#define OS_TASK_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_task_types.h"

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
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                            **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : OsTask_DoScheduling
*   Service ID              : None.
*   Description             : Schedule due to Task Priority.
*   Parameters in           : SchedulingChoice: Indicate whether need to Save previous Context
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTask_DoScheduling
(
    Os_SchedulingChoiceType SchedulingChoice
);

/****************************************************************************************************
*   Function Name           : OsTask_AddTaskToScheduler
*   Service ID              : None.
*   Description             : Add the given task to Scheduler and calculate the current Priority.
*   Parameters in           : TaskID: the task to add to Scheduler.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTask_AddTaskToScheduler
(
    TaskType TaskID
);

/****************************************************************************************************
*   Function Name           : OsTask_RemoveTaskFromScheduler
*   Service ID              : None.
*   Description             : Remove the given task from Scheduler and calculate the current Priority.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTask_RemoveTaskFromScheduler
(
    void
);

/****************************************************************************************************
*   Function Name           : OsTask_FifoPush
*   Service ID              : None.
*   Description             : Push the give item into fifo (the fifo buffer size is 32).
*   Parameters in           : InputItem:
*   Parameters inout        : FifoQueuePtr:
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTask_FifoPush
(
    P2VAR(Os_FifoQueueType, TYPEDEF,OS_VAR) FifoQueuePtr,
    uint32 InputItem
);

/****************************************************************************************************
*   Function Name           : OsTask_FifoPop
*   Service ID              : None.
*   Description             : Pop the give item into fifo (the fifo buffer size is 32).
*   Parameters in           : None.
*   Parameters inout        : FifoQueuePtr:
*                             OutputItemPtr:
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTask_FifoPop
(
    P2VAR(Os_FifoQueueType, TYPEDEF,OS_VAR) FifoQueuePtr,
    P2VAR(uint32, TYPEDEF,OS_VAR) OutputItemPtr
);

/****************************************************************************************************
*   Function Name           : OsTask_TaskInit
*   Service ID              : None.
*   Description             : Initialize task
*   Parameters in           : TaskID: the task to add to be initialized
*                           : AppMode: The running app mode
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTask_TaskInit
(
    TaskType TaskID,
    AppModeType AppMode
);

/****************************************************************************************************
*   Function Name           : OsTask_SchedulerInit
*   Service ID              : None.
*   Description             : Initialize scheduler
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTask_SchedulerInit
(
    void
);

/****************************************************************************************************
*   Function Name           : OsTask_ErrorReturn
*   Service ID              : None.
*   Description             : Task finished without terminate
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTask_ErrorReturn
(
        void
);

/****************************************************************************************************
*   Function Name           : OsTask_LeaveTaskLevel
*   Service ID              : None.
*   Description             : Change task state to READY, change scheduler current task to invalid
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTask_LeaveTaskLevel
(
        void
);

/****************************************************************************************************
*   Function Name           : OsTask_ActivateTask
*   Service ID              : None.
*   Description             : Activate task locally
*   Parameters in           : TaskID: task to be activate on local core
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE)OsTask_ActivateTask
(
        TaskType TaskID
);

/****************************************************************************************************
*   Function Name           : OsTask_GetTaskState
*   Service ID              : None.
*   Description             : Get task state locally
*   Parameters in           : TaskID: task to be activate on local core
*                           : State
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsTask_GetTaskState
(
    TaskType TaskID,
    TaskStateRefType State
);

/****************************************************************************************************
*   Function Name           : OsTask_GetTaskDyn
*   Service ID              : None.
*   Description             : Get task dynamic structure pointer
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(P2VAR(Os_TaskDynamicType, TYPEDEF,OS_VAR), OS_CODE) OsTask_GetTaskDyn
(
    TaskType TaskID
);

/****************************************************************************************************
*   Function Name           : OsTask_GetTaskConst
*   Service ID              : None.
*   Description             : Get task constant structure pointer
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(P2CONST(Os_TaskConstType, TYPEDEF, OS_CONST), OS_CODE) OsTask_GetTaskConst
(
    TaskType TaskID
);

/****************************************************************************************************
*   Function Name           : OsTask_GetSchedulerDyn
*   Service ID              : None.
*   Description             : Get Scheduler dynamic structure pointer
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(P2VAR(Os_SchedulerType, TYPEDEF,OS_VAR), OS_CODE) OsTask_GetSchedulerDyn
(
    void
);

/****************************************************************************************************
*   Function Name           : OsTask_GetLockList
*   Service ID              : None.
*   Description             : Get Task lock list
*   Parameters in           : TaskID :
*                             LockListPtr :
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTask_GetLockList
(
    TaskType TaskID,
    P2P2VAR(Os_LockConfigRefType, TYPEDEF, OS_VAR)LockListPtr
);

/****************************************************************************************************
*   Function Name           : OsTask_GetspinLockList
*   Service ID              : None.
*   Description             : Get Task Spin list
*   Parameters in           : TaskID :
*                             SpinLockListPtr :
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void,OS_CODE) OsTask_GetSpinLockList
(
    TaskType TaskID,
    P2P2VAR(Os_SpinlockConfigRefType, TYPEDEF, OS_VAR)SpinLockListPtr
);

/****************************************************************************************************
*   Function Name           : OsTask_LevelUpTaskPriority
*   Service ID              : None.
*   Description             : Level up the priority for the current task when using GetResource
*   Parameters in           : NewPriority :
*                             CurrentPriority :
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE)OsTask_LevelUpTaskPriority
(
    uint32 NewPriority,
    P2VAR(uint32, TYPEDEF, OS_VAR) CurrentPriorityPtr
);

/****************************************************************************************************
*   Function Name           : OsTask_LevelDownTaskPriority
*   Service ID              : None.
*   Description             : Level down the priority for the current task when using ReleaseResource
*   Parameters in           : NewPriority :
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE)OsTask_LevelDownTaskPriority
(
    uint32 NewPriority
);

/****************************************************************************************************
*   Function Name           : OsTask_GetHomePriority
*   Service ID              : None.
*   Description             : Return the homepriority of the task
*   Parameters in           : TaskID :
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(uint32 ,OS_CODE)OsTask_GetHomePriority
(
    TaskType TaskID
);

/****************************************************************************************************
*   Function Name           : OsTask_ActivateRestartTask
*   Service ID              : None.
*   Description             : Activate Restart Task
*   Parameters in           : TaskID :
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void ,OS_CODE)OsTask_ActivateRestartTask
(
    TaskType TaskID
);
/****************************************************************************************************
*   Function Name           : OsTask_TaskDeinit
*   Service ID              : None.
*   Description             : Deinit the specific Task
*   Parameters in           : TaskID :
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void ,OS_CODE)OsTask_TaskDeinit
(
    TaskType TaskID
);
#endif /* OS_TASK_H_ */
/****************************************************************************************************
**     End of File: Os_Task.h                                                                      **
****************************************************************************************************/
