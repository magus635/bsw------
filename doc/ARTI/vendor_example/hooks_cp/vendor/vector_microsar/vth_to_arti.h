
/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2007 - 2023 by Vector Informatik GmbH.                                           All rights reserved.
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  vth_to_arti.h
 *    Component:  MICROSAR Run-Time Interface ARTI
 *
 *  Description:  OS Vector Timing Hooks implementation file for timing measurements with ARTI hooks.
 *                For support needs please contact support@vector.com
 *                Use the keyword: "MICROSAR Run-Time Interface ARTI".
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Rudolf Dienstbeck             RD            Lauterbach GmbH
 *  Sebastian Ziegler             SZ            Vector Informatik GmbH
 *  Juergen Poellinger            JP            Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2021-02-17  RD                    Initial creation
 *  01.01.00  2023-03-23  JP                    Added VTH hooks for spinlocks and for OS service calls for interrupts
 **********************************************************************************************************************/

#if !defined(VTH_TO_ARTI_H)
#define VTH_TO_ARTI_H

#include <arti.h>

/**********************************************************************************************************************
 *  OS_VTH_SCHEDULE()
 *********************************************************************************************************************/
/*! \brief          Trace thread-switches, where thread stands for task or ISR
 *  \details        This hook routine allows external tools to trace all context switches from task to ISR and back as
 *                  well as between tasks and between ISRs. So external tools may visualize the information or measure
 *                  the execution time of tasks and ISRs.
 *                  Mind that measured execution time values may not reflect the worst case, which would be necessary
 *                  for schedulability analysis.
 *
 *                  Callers:
 *                    - Os_TraceThreadSwitch()
 *                    - Os_TraceThreadResetAndResume()
 *                    - Os_TraceThreadCleanupAndResume()
 *                    - Os_TraceThreadSuspendAndStart()
 *
 *  \param[in]      FromThreadId     The ID of the thread which has run until the switch
 *  \param[in]      FromThreadReason Represents the reason why the thread is no longer running:
 *                                   - \ref OS_VTHP_TASK_TERMINATION	1
 *                                   - \ref OS_VTHP_ISR_END				2
 *                                   - \ref OS_VTHP_TASK_WAITEVENT		4
 *                                   - \ref OS_VTHP_TASK_WAITSEMA		8
 *                                   - \ref OS_VTHP_THREAD_PREEMPT		16
 *  \param[in]      ToThreadId       The ID of the thread which will run from now on
 *  \param[in]      ToThreadReason   Represents the reason why the thread runs from now on:
 *                                   - \ref OS_VTHP_TASK_ACTIVATION		1
 *                                   - \ref OS_VTHP_ISR_START			2
 *                                   - \ref OS_VTHP_TASK_SETEVENT		4
 *                                   - \ref OS_VTHP_TASK_GOTSEMA		8
 *                                   - \ref OS_VTHP_THREAD_RESUME		16
 *                                   - \ref OS_VTHP_THREAD_CLEANUP		32
 *  \param[in]      CallerCoreId     The ID of the core where the thread switch occurs
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different cores.
 *  \synchronous    TRUE
 *
 *  \pre          Interrupts locked to TP lock level.
 *
 *  \trace          CREQ-115029
 *
 *********************************************************************************************************************/
#define OS_VTH_SCHEDULE(FromThreadId, FromThreadReason, ToThreadId, ToThreadReason, CallerCoreId)               \
{                                                                                                               \
	switch (FromThreadReason) {                                                                                 \
		case OS_VTHP_TASK_TERMINATION:                                                                          \
			ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, CallerCoreId, OsTask_Terminate, FromThreadId);            \
			break;                                                                                              \
		case OS_VTHP_ISR_END:                                                                                   \
			ARTI_TRACE(NOSUSP, AR_CP_OS_CAT2ISR, Os, CallerCoreId, OsCat2Isr_Stop, FromThreadId);               \
			break;                                                                                              \
		case OS_VTHP_TASK_WAITEVENT:                                                                            \
		case OS_VTHP_TASK_WAITSEMA:                                                                             \
			ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, CallerCoreId, OsTask_Wait, FromThreadId);                 \
			break;                                                                                              \
		case OS_VTHP_THREAD_PREEMPT:                                                                            \
			if (FromThreadId < OS_TASKID_COUNT) {                                                               \
				ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, CallerCoreId, OsTask_Preempt, FromThreadId);          \
			} else {                                                                                            \
				ARTI_TRACE(NOSUSP, AR_CP_OSARTI_CAT2ISR, Os, CallerCoreId, OsCat2Isr_Preempt, FromThreadId);    \
			}                                                                                                   \
			break;                                                                                              \
		default:                                                                                                \
			break;                                                                                              \
	}                                                                                                           \
	switch (ToThreadReason) {                                                                                   \
		case OS_VTHP_TASK_ACTIVATION:                                                                           \
			ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, CallerCoreId, OsTask_Start, ToThreadId);                  \
			break;                                                                                              \
		case OS_VTHP_ISR_START:                                                                                 \
			ARTI_TRACE(NOSUSP, AR_CP_OS_CAT2ISR, Os, CallerCoreId, OsCat2Isr_Start, ToThreadId);                \
			break;                                                                                              \
		case OS_VTHP_TASK_SETEVENT:                                                                             \
		case OS_VTHP_TASK_GOTSEMA:                                                                              \
			ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, CallerCoreId, OsTask_Continue, ToThreadId);               \
			break;                                                                                              \
		case OS_VTHP_THREAD_RESUME:                                                                             \
			if (ToThreadId < OS_TASKID_COUNT) {                                                                 \
				ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, CallerCoreId, OsTask_Resume, ToThreadId);             \
			} else {                                                                                            \
				ARTI_TRACE(NOSUSP, AR_CP_OSARTI_CAT2ISR, Os, CallerCoreId, OsCat2Isr_Resume, ToThreadId);       \
			}                                                                                                   \
			break;                                                                                              \
		case OS_VTHP_THREAD_CLEANUP:                                                                            \
			break;                                                                                              \
		default:                                                                                                \
			break;                                                                                              \
	}                                                                                                           \
}


#ifdef ARTI_ENABLE_OS_TASK
/**********************************************************************************************************************
 *  OS_VTH_ACTIVATION()
 *********************************************************************************************************************/
/*! \brief          Trace the activation of a task.
 *  \details        This hook is called on the caller core when that core has successfully performed the activation of
 *                  TaskId on the destination core. As this OS implementation always performs task activation on the
 *                  destination core, DestCoreId and CallerCoreId are always identical.
 *
 *                  Callers:
 *                    - Os_TraceTaskActivate()
 *
 *  \param[in]      TaskId       The ID of the task which is activated
 *  \param[in]      DestCoreId   The ID of the core where the task will be executed
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *  \trace          CREQ-115010
 *********************************************************************************************************************/
#define OS_VTH_ACTIVATION(TaskId, DestCoreId, CallerCoreId) \
{ ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, DestCoreId, OsTask_Activate, TaskId); }
#endif


#ifdef ARTI_ENABLE_OS_TASK
/**********************************************************************************************************************
 *  OS_VTH_SETEVENT()
 *********************************************************************************************************************/
/*! \brief          Trace the event setting on a task.
 *  \details        This hook is called on the CallerCore when that core has successfully performed the event
 *                  setting on the destination core. As this OS implementation always performs event setting on the
 *                  destination core, DestCoreId and CallerCoreId are always identical.
 *
 *                  Callers:
 *                    - Os_TraceTaskSetEvent()
 *
 *  \param[in]      TaskId       The ID of the task which receives this event
 *  \param[in]      EventMask    A bit mask with the events which have been set
 *  \param[in]      StateChanged
 *                   - !0: The task state has changed from WAITING to READY
 *                   -  0: The task state has not changed
 *  \param[in]      DestCoreId   The ID of the core where the task will be executed
 *  \param[in]      CallerCoreId The ID of the core where this hook is called
 *
 *  \context        OS internal
 *
 *  \reentrant      TRUE for different caller cores.
 *  \synchronous    TRUE
 *
 *  \pre            Interrupts locked to TP lock level.
 *
 *  \trace          CREQ-115028
 *
 *********************************************************************************************************************/
#define OS_VTH_SETEVENT(TaskId, EventMask, StateChanged, DestCoreId, CallerCoreId) \
{ if(StateChanged) { \
	ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, DestCoreId, OsTask_Release, TaskId); \
}}
#endif


#ifdef ARTI_ENABLE_OS_SPINLOCK
/**********************************************************************************************************************
 *  OS_VTH_xxx_SPINLOCK()
 *********************************************************************************************************************/
/*
 * The VTH hooks for Spinlocks cannot be mapped directly to ARTI hooks.
 * Instead the following mapping is used:
 * OS_VTH_REQ_SPINLOCK -> AR_CP_OS_SERVICECALLS/OsServiceCall_TryToGetSpinlock_Start
 * OS_VTH_GOT_SPINLOCK -> AR_CP_OS_SPINLOCK/OsSpinlock_Locked
 * OS_VTH_REL_SPINLOCK -> AR_CP_OS_SPINLOCK/OsSpinlock_Released
*/
#ifdef ARTI_ENABLE_OS_SERVICECALLS
	#define OS_VTH_REQ_SPINLOCK(SpinlockId, CallerCoreId)\
	{\
		ARTI_TRACE(NOSUSP, AR_CP_OS_SERVICECALLS, Os, CallerCoreId, OsServiceCall_TryToGetSpinlock_Start, SpinlockId); \
	}
	#define OS_VTH_REQ_ISPINLOCK(SpinlockId, CallerCoreId)\
	{\
		ARTI_TRACE(NOSUSP, AR_CP_OS_SERVICECALLS, Os, CallerCoreId, OsServiceCall_TryToGetSpinlock_Start, SpinlockId); \
	}
#endif

#define OS_VTH_GOT_SPINLOCK(SpinlockId, CallerCoreId) \
{\
    ARTI_TRACE(NOSUSP, AR_CP_OS_SPINLOCK, Os, CallerCoreId, OsSpinlock_Locked, SpinlockId); \
}
#define OS_VTH_GOT_ISPINLOCK(SpinlockId, CallerCoreId) \
{\
    ARTI_TRACE(NOSUSP, AR_CP_OS_SPINLOCK, Os, CallerCoreId, OsSpinlock_Locked, SpinlockId); \
}

#define OS_VTH_REL_SPINLOCK(SpinlockId, CallerCoreId)\
{\
    ARTI_TRACE(NOSUSP, AR_CP_OS_SPINLOCK, Os, CallerCoreId, OsSpinlock_Released, SpinlockId); \
}
#define OS_VTH_REL_ISPINLOCK(SpinlockId, CallerCoreId)\
{\
    ARTI_TRACE(NOSUSP, AR_CP_OS_SPINLOCK, Os, CallerCoreId, OsSpinlock_Released, SpinlockId); \
}
#endif


#ifdef ARTI_ENABLE_OS_SERVICECALLS
/**********************************************************************************************************************
 *  OS_VTH_xxxINT()
 *********************************************************************************************************************/
/*
 * The OS service calls for interrupts cannot be mapped to VTH hooks.
 * We have to restrict it the the actual enabling and disabling of interrupts.
 * Unfortunately, ARTI doesn't know interrupt enable states, so we have to use service calls again.
 * The following mapping is used:
 * OS_VTH_ENABLEDINT  -> AR_CP_OS_SERVICECALLS/OsServiceCall_EnableAllInterrupts_Start
 * OS_VTH_DISABLEDINT -> AR_CP_OS_SERVICECALLS/OsServiceCall_DisableAllInterrupts_Start
*/
#define OS_VTH_ENABLEDINT(IntLockId, CallerCoreId) \
{\
    ARTI_TRACE(NOSUSP, AR_CP_OS_SERVICECALLS, Os, CallerCoreId, OsServiceCall_EnableAllInterrupts_Start, 0); \
}

#define OS_VTH_DISABLEDINT(IntLockId, CallerCoreId) \
{\
    ARTI_TRACE(NOSUSP, AR_CP_OS_SERVICECALLS, Os, CallerCoreId, OsServiceCall_DisableAllInterrupts_Start, 0); \
}
#endif


#endif /* VTH_TO_ARTI_H */

/**********************************************************************************************************************
 *  END OF FILE: vth_to_arti.h
 *********************************************************************************************************************/