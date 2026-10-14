/* Dbg.h - AutoCore OS debug and trace header
 *
 * This file is included by anything that needs to trace OS internal states.
 *
 * This header file enables the OS task state tracing and activates the ARTI trace
 * to be used with Lauterbach's TRACE32.
 *
 * NOTE: USING THIS FILE INVALIDATES THE SAFETY CERTIFICATION.
 *
 * (c) 2021 Lauterbach GmbH
 *
*/
#ifndef DBG_H
#define DBG_H

#include <Os.h>
#include <arti.h>

/* Os_TS_T16D26M6I0R0\include\Os_trace.h, Os_types.h */

#define OS_TRACE_STATE_TASK(StateId, oldValue, newValue) do { \
    os_coreid_t arti_core; \
    /*arti_id=StateId, arti_old=oldValue, arti_new=newValue;*/ \
    arti_core = OS_GetMyCoreId(); \
    switch (newValue) { \
        case OS_TS_NEW: \
            ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, arti_core, OsTask_Activate, StateId); \
            break; \
        case OS_TS_SUSPENDED: \
        case OS_TS_QUARANTINED: \
            ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, arti_core, OsTask_Terminate, StateId); \
            break; \
        case OS_TS_READY_ASYNC: \
            ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, arti_core, OsTask_Preempt, StateId); \
            break; \
        case OS_TS_READY_SYNC: \
            ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, arti_core, OsTask_Release, StateId); \
            break; \
        case OS_TS_WAITING: \
            ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, arti_core, OsTask_Wait, StateId); \
            break; \
        case OS_TS_RUNNING: \
            switch (oldValue) { \
                case OS_TS_NEW: \
                    ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, arti_core, OsTask_Start, StateId); \
                    break; \
                case OS_TS_READY_ASYNC: \
                    ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, arti_core, OsTask_Resume, StateId); \
                    break; \
                case OS_TS_READY_SYNC: \
                    ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, arti_core, OsTask_Continue, StateId); \
                    break; \
            } \
            break; \
    } \
  } while (0) /* while loop to get the following semicolon eaten up */

#define OS_TRACE_STATE_ISR(IsrId, oldValue, newValue) do { \
    os_coreid_t arti_core; \
    /*arti_id=IsrId, arti_old=oldValue, arti_new=newValue;*/ \
    arti_core = OS_GetMyCoreId(); \
    switch (newValue) { \
        case OS_TRACE_ISR_RUNNING: \
            ARTI_TRACE(NOSUSP, AR_CP_OS_CAT2ISR, Os, arti_core, OsCat2Isr_Start, OS_GetNTasks() + IsrId); \
            break; \
        case OS_TRACE_ISR_SUSPENDED: \
            ARTI_TRACE(NOSUSP, AR_CP_OS_CAT2ISR, Os, arti_core, OsCat2Isr_Stop, OS_GetNTasks() + IsrId); \
            break; \
    } \
  } while (0) /* while loop to get the following semicolon eaten up */

#endif  // DBG_H

