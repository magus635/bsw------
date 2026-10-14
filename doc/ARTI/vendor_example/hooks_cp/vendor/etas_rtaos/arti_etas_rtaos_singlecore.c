/**********************************************************************************************************************
	@Copyright: (C) 1989-2021 Lauterbach GmbH, licensed for use with TRACE32(R) only
**********************************************************************************************************************/

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  rta-os-singlecore.c
 *  Description:  ARTI Implementation for tracing RTA-OS
 *********************************************************************************************************************/

#include "Os.h"
#include "common/arti.h"


/** Macros for index calculations **/

#define ARTI_ISR_INDEX(isr) (OS_ISRTYPE_TO_INDEX(isr)+OS_NUM_TASKS)


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
    int         taskindex = 0;

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
                if (Os_ReadyTasks.p0 & task->pset.p0) {
                    t32_taskevent[i] = T32_TASKEVENT_POSTTOREADY;
                    ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Release, i);
                }
            }
        }
    }
#endif

    ARTI_TRACE(NOSUSP, AR_CP_OS_CAT2ISR, Os, 0, OsCat2Isr_Stop, ARTI_ISR_INDEX(isr));
    if (taskid) {
        ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Resume, taskindex);
    }
}

void Os_Cbk_ISRStart(ISRType isr)
{
    TaskType    taskid;
    int         taskindex = 0;

    GetTaskID (&taskid);
    if (taskid) {
        taskindex = OS_TASKTYPE_TO_INDEX(taskid);
    }

    ARTI_TRACE(NOSUSP, AR_CP_OS_CAT2ISR, Os, 0, OsCat2Isr_Start, ARTI_ISR_INDEX(isr));
    if (taskid) {
        ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Preempt, taskindex);
    }
}


/** Task callbacks **/

void Os_Cbk_TaskEnd(TaskType task) {
    int         taskindex = OS_TASKTYPE_TO_INDEX(task);

    if (t32_taskevent[taskindex] == T32_TASKEVENT_TERMINATE) {
        t32_taskevent[taskindex] = T32_TASKEVENT_ENDTOTERMINATE;
        // ARTI message handled in Os_Cbk_TaskTerminated
        // ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Terminate, taskindex);
    } else {
        t32_taskevent[taskindex] = T32_TASKEVENT_ENDTOWAIT;
         ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Wait, taskindex);
    }
}

void Os_Cbk_TaskStart(TaskType task) {
    t32_taskevent[OS_TASKTYPE_TO_INDEX(task)] = T32_TASKEVENT_START;
    // ARTI message handled in PreTaskHook
    // ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Start, OS_TASKTYPE_TO_INDEX(task));
}

void Os_Cbk_TaskActivated(TaskType task) {
    t32_taskevent[OS_TASKTYPE_TO_INDEX(task)] = T32_TASKEVENT_ACTIVATE;
    ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Activate, OS_TASKTYPE_TO_INDEX(task));
}

void Os_Cbk_TaskTerminated(TaskType task) {
    t32_taskevent[OS_TASKTYPE_TO_INDEX(task)] = T32_TASKEVENT_TERMINATE;
    ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Terminate, OS_TASKTYPE_TO_INDEX(task));
}

FUNC(void, OS_CALLOUT_CODE) PreTaskHook(void)
{
    TaskType    taskid;
    int         taskindex;

    GetTaskID (&taskid);
    taskindex = OS_TASKTYPE_TO_INDEX(taskid);

    switch (t32_taskevent[taskindex]) {
        case T32_TASKEVENT_ACTIVATE:
            t32_taskevent[taskindex] = T32_TASKEVENT_PRETOSTART;
            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Start, OS_TASKTYPE_TO_INDEX(taskid));
            break;
        case T32_TASKEVENT_POSTTOPREEMPT:
            t32_taskevent[taskindex] = T32_TASKEVENT_PRETORESUME;
            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Resume, OS_TASKTYPE_TO_INDEX(taskid));
            break;
        case T32_TASKEVENT_POSTTOREADY:
            t32_taskevent[taskindex] = T32_TASKEVENT_PRETOCONTINUE;
            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Continue, OS_TASKTYPE_TO_INDEX(taskid));
            break;
        default:
            // actually a state machine error
            t32_taskevent[taskindex] = T32_TASKEVENT_PRETOUNKNOWN;
            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Resume, OS_TASKTYPE_TO_INDEX(taskid));
            break;
    }
}

FUNC(void, OS_CALLOUT_CODE) PostTaskHook(void)
{
    TaskType    taskid;
    int         taskindex;

    GetTaskID (&taskid);
    taskindex = OS_TASKTYPE_TO_INDEX(taskid);

#if OS_NUM_EVENTS > 0
    {
        int i;
        for (i = 0; i < OS_NUM_TASKS; i++) {
            if ((i != taskindex) && (t32_taskevent[i] == T32_TASKEVENT_ENDTOWAIT)) {
                TaskType task = OS_INDEX_TO_TASKTYPE(i);
                if (Os_ReadyTasks.p0 & task->pset.p0) {
                    t32_taskevent[i] = T32_TASKEVENT_POSTTOREADY;
                    ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Release, i);
                }
            }
        }
    }
#endif

    switch (t32_taskevent[taskindex]) {
        case T32_TASKEVENT_START:
        case T32_TASKEVENT_PRETOSTART:
        case T32_TASKEVENT_PRETORESUME:
        case T32_TASKEVENT_PRETOCONTINUE:
            t32_taskevent[OS_TASKTYPE_TO_INDEX(taskid)] = T32_TASKEVENT_POSTTOPREEMPT;
            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Preempt, taskindex);
            break;
        case T32_TASKEVENT_ENDTOWAIT:
            // ARTI message handled in Os_Cbk_TaskEnd
            // ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Wait, taskindex);
            break;
        case T32_TASKEVENT_ENDTOTERMINATE:
        case T32_TASKEVENT_TERMINATE:
            t32_taskevent[OS_TASKTYPE_TO_INDEX(taskid)] = T32_TASKEVENT_POSTTOTERMINATE;
            // ARTI message handled in Os_Cbk_TaskTerminated
            // ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Terminate, taskindex);
            break;
        default:
            // actually a state machine error
            t32_taskevent[OS_TASKTYPE_TO_INDEX(taskid)] = T32_TASKEVENT_POSTTOUNKNOWN;
            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, 0, OsTask_Terminate, OS_TASKTYPE_TO_INDEX(taskid));
            break;
    }
}
