/**********************************************************************************************************************
	@Copyright: (C) 1989-2021 Lauterbach GmbH, licensed for use with TRACE32(R) only
**********************************************************************************************************************/

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  rta-os-multicore.c
 *  Description:  ARTI Implementation for tracing RTA-OS
 *********************************************************************************************************************/

#include "Os.h"
#include "common/arti.h"


/** Macros for index calculations **/

#define ARTI_ISR_INDEX(isr) (OS_ISRTYPE_TO_INDEX(isr)+OS_NUM_TASKS)
#define ARTI_CROSSCORE_ISR  (OS_NUM_TASKS+OS_NUM_ISRS+1)

/* Note for CrosscoreISR: in the RTAOS.orti file, extend the RUNNINGISR2 ENUM by a line
   "CROSSCORE_ISR" = "1"
   after the "NO_ISR" = "0" entry. Remember to add a comma after the NO_ISR entry.
*/


/** TRACE32 helper variables **/

typedef enum T32_TaskEventEnum {
    T32_TASKEVENT_ACTIVATE,
    T32_TASKEVENT_START,
    T32_TASKEVENT_PRETOSTART,
    T32_TASKEVENT_PRETORESUME,
    T32_TASKEVENT_PRETOCONTINUE,
    T32_TASKEVENT_POSTTOREADY,
    T32_TASKEVENT_POSTTOPREEMPT,
    T32_TASKEVENT_POSTTOTERMINATE,
    T32_TASKEVENT_ENDTOWAIT,
    T32_TASKEVENT_ENDTOTERMINATE,
    T32_TASKEVENT_TERMINATE,
    T32_TASKEVENT_PRETOUNKNOWN,
    T32_TASKEVENT_POSTTOUNKNOWN,
    T32_TASKEVENT_UNKNOWN
} T32_TaskEventType;
T32_TaskEventType t32_taskevent[OS_NUM_TASKS];


/** ISR callbacks **/

void Os_Cbk_ISREnd(ISRType isr)
{
    TaskType    taskid;
    CoreIdType  coreid;
    int         taskindex = 0;

    coreid = GetCoreID();
    GetTaskID (&taskid);
    if (taskid) {
        taskindex = OS_TASKTYPE_TO_INDEX(taskid);
    }

#if OS_NUM_EVENTS > 0
    {
        int i;
        for (i = 0; i < OS_NUM_TASKS; i++) {
            if (t32_taskevent[i] == T32_TASKEVENT_ENDTOWAIT) {
                TaskType task = OS_INDEX_TO_TASKTYPE(i);
                if (Os_ControlledCoreInfo[task->core_id].ReadyTasks.p0 & task->pset.p0) {
                    t32_taskevent[i] = T32_TASKEVENT_POSTTOREADY;
                    ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, task->core_id, OsTask_Release, i);
                }
            }
        }
    }
#endif

    ARTI_TRACE(NOSUSP, AR_CP_OS_CAT2ISR, Os, coreid, OsCat2Isr_Stop, ARTI_ISR_INDEX(isr));
    if (taskid) {
        ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, coreid, OsTask_Resume, taskindex);
    }
}

void Os_Cbk_ISRStart(ISRType isr)
{
    TaskType    taskid;
    CoreIdType  coreid;
    int         taskindex = 0;

    coreid = GetCoreID();
    GetTaskID (&taskid);
    if (taskid) {
        taskindex = OS_TASKTYPE_TO_INDEX(taskid);
    }

    ARTI_TRACE(NOSUSP, AR_CP_OS_CAT2ISR, Os, coreid, OsCat2Isr_Start, ARTI_ISR_INDEX(isr));
    if (taskid) {
        ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, coreid, OsTask_Preempt, taskindex);
    }
}

void Os_Cbk_CrosscoreISREnd(CoreIdType core_id)
{
    ARTI_TRACE(NOSUSP, AR_CP_OS_CAT2ISR, Os, core_id, OsCat2Isr_Stop, ARTI_CROSSCORE_ISR);
}

void Os_Cbk_CrosscoreISRStart(CoreIdType core_id)
{
    ARTI_TRACE(NOSUSP, AR_CP_OS_CAT2ISR, Os, core_id, OsCat2Isr_Start, ARTI_CROSSCORE_ISR);
}


/** Task callbacks **/

void Os_Cbk_TaskEnd(TaskType task) {
    CoreIdType  coreid    = GetCoreID();
    int         taskindex = OS_TASKTYPE_TO_INDEX(task);

    if (t32_taskevent[taskindex] == T32_TASKEVENT_TERMINATE) {
        t32_taskevent[taskindex] = T32_TASKEVENT_ENDTOTERMINATE;
        // ARTI message handled in Os_Cbk_TaskTerminated
        // ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, coreid, OsTask_Terminate, taskindex);
    } else {
        t32_taskevent[taskindex] = T32_TASKEVENT_ENDTOWAIT;
         ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, coreid, OsTask_Wait, taskindex);
    }
}

void Os_Cbk_TaskStart(TaskType task) {
    // CoreIdType  coreid = GetCoreID();
    t32_taskevent[OS_TASKTYPE_TO_INDEX(task)] = T32_TASKEVENT_START;
    // ARTI message handled in PreTaskHook
    // ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, coreid, OsTask_Start, OS_TASKTYPE_TO_INDEX(task));
}

void Os_Cbk_TaskActivated(TaskType task) {
    t32_taskevent[OS_TASKTYPE_TO_INDEX(task)] = T32_TASKEVENT_ACTIVATE;
    ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, task->core_id, OsTask_Activate, OS_TASKTYPE_TO_INDEX(task));
}

void Os_Cbk_TaskTerminated(TaskType task) {
    t32_taskevent[OS_TASKTYPE_TO_INDEX(task)] = T32_TASKEVENT_TERMINATE;
    ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, task->core_id, OsTask_Terminate, OS_TASKTYPE_TO_INDEX(task));
}

FUNC(void, OS_CALLOUT_CODE) PreTaskHook(void)
{
    TaskType    taskid;
    CoreIdType  coreid;
    int         taskindex;

    GetTaskID (&taskid);
    taskindex = OS_TASKTYPE_TO_INDEX(taskid);
    coreid    = GetCoreID();

    switch (t32_taskevent[taskindex]) {
        case T32_TASKEVENT_ACTIVATE:
            t32_taskevent[taskindex] = T32_TASKEVENT_PRETOSTART;
            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, coreid, OsTask_Start, taskindex);
            break;
        case T32_TASKEVENT_POSTTOPREEMPT:
            t32_taskevent[taskindex] = T32_TASKEVENT_PRETORESUME;
            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, coreid, OsTask_Resume, taskindex);
            break;
        case T32_TASKEVENT_POSTTOREADY:
            t32_taskevent[taskindex] = T32_TASKEVENT_PRETOCONTINUE;
            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, coreid, OsTask_Continue, taskindex);
            break;
        default:
            // actually a state machine error
            t32_taskevent[taskindex] = T32_TASKEVENT_PRETOUNKNOWN;
            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, coreid, OsTask_Resume, taskindex);
            break;
    }
}

FUNC(void, OS_CALLOUT_CODE) PostTaskHook(void)
{
    TaskType    taskid;
    CoreIdType  coreid;
    int         taskindex;

    GetTaskID (&taskid);
    taskindex = OS_TASKTYPE_TO_INDEX(taskid);

#if OS_NUM_EVENTS > 0
    {
        int i;
        for (i = 0; i < OS_NUM_TASKS; i++) {
            if ((i != taskindex) && (t32_taskevent[i] == T32_TASKEVENT_ENDTOWAIT)) {
                TaskType task = OS_INDEX_TO_TASKTYPE(i);
                if (Os_ControlledCoreInfo[task->core_id].ReadyTasks.p0 & task->pset.p0) {
                    t32_taskevent[i] = T32_TASKEVENT_POSTTOREADY;
                    ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, task->core_id, OsTask_Release, i);
                }
            }
        }
    }
#endif

    coreid = GetCoreID();

    switch (t32_taskevent[taskindex]) {
        case T32_TASKEVENT_START:
        case T32_TASKEVENT_PRETOSTART:
        case T32_TASKEVENT_PRETORESUME:
        case T32_TASKEVENT_PRETOCONTINUE:
            t32_taskevent[taskindex] = T32_TASKEVENT_POSTTOPREEMPT;
            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, coreid, OsTask_Preempt, taskindex);
            break;
        case T32_TASKEVENT_ENDTOWAIT:
            // ARTI message handled in Os_Cbk_TaskEnd
            // ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, coreid, OsTask_Wait, taskindex);
            break;
        case T32_TASKEVENT_ENDTOTERMINATE:
        case T32_TASKEVENT_TERMINATE:
            t32_taskevent[taskindex] = T32_TASKEVENT_POSTTOTERMINATE;
            // ARTI message handled in Os_Cbk_TaskTerminated
            // ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, coreid, OsTask_Terminate, taskindex);
            break;
        default:
            // actually a state machine error
            t32_taskevent[taskindex] = T32_TASKEVENT_POSTTOUNKNOWN;
            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, coreid, OsTask_Terminate, taskindex);
            break;
    }
}
