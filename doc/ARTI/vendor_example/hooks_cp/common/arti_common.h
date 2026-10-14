/**********************************************************************************************************************
	@Copyright: (C) 1989-2022 Lauterbach GmbH, licensed for use with TRACE32(R) only
**********************************************************************************************************************/

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *         File:  arti_common.h
 *  Description:  Common ARTI implementation file, to be included by arti.h
 *********************************************************************************************************************/

#if !defined(ARTI_COMMON_H)
#define ARTI_COMMON_H


/**********************************************************************************************************************
 * ARTI module API prototypes
 ********************************************************************************************************************/

#define ARTI_E_INIT_FAILED      0x01
#define ARTI_E_PARAM_POINTER    0x02

extern void Arti_Init (void);

#if (STD_VERSION_INFO_TYPE_DEFINED != STD_OFF)
extern void Arti_GetVersionInfo (Std_VersionInfoType* VersionInfoPtr);
#endif


/**********************************************************************************************************************
 * ARTI globals and definitions - do not modify
 ********************************************************************************************************************/

/*! arti_os_trace endcoding
 *
 *  [0:7]  : Core ID
 *  [8:14] : OS State ID
 *  [15]   : Valid bit, always 1 ("ARTI_VALID_OS_SIGNALING")
 *  [16:31]: Task/ISR ID
 *
 *  0000 80 00
 *  ---- -- --
 *    |  ||  |
 *    |  ||  \ Core ID
 *    |  ||
 *    |  |\ State ID
 *    |  \  Bit 15: valid bit (always 1)
 *    \ Thread ID (16-bit)
 *
 **********************************************************************************************************************/
extern volatile unsigned int arti_os_trace;

/*! arti_rte_trace endcoding:
 *
 *  [0:7]  : Core ID
 *  [8:31] : Runnable ID
 *
 * 000000 00
 * ------ --
 *       | |
 *       | \ CoreId
 *       |
 *       \ RunnableId
 *
 **********************************************************************************************************************/
extern volatile unsigned int arti_rte_trace;

/*! arti_sc_trace endcoding:
 *
 *  [0:7]  : Core ID
 *  [8:14] : service call ID
 *  [15]   : set on return
 *  [16:31]: service call parameter
 *
 **********************************************************************************************************************/
extern volatile unsigned int arti_sc_trace;

/** ARTI context definitions **/
typedef enum {
    NOSUSP  = 0,
    SPRVSR  = 1,
    USER    = 2
} Arti_ContextType;

/** Bit 16 of arti_os_trace is always written to 1 in order to identify a valid write of the OS (not by e.g. data init routine of C-startup). **/
#define ARTI_VALID_OS_SIGNALING 0x80

/** ARTI OS Task state transitions **/
typedef enum {
	OsTask_Activate     = 0,
	OsTask_Start        = 1,
	OsTask_Wait         = 2,
	OsTask_Release      = 3,
	OsTask_Preempt      = 4,
	OsTask_Terminate    = 5,
	OsTask_Resume       = 6,
	OsTask_Continue     = 7
} Arti_OsTaskEventType;

/** ARTI OS ISR2 state transitions **/
typedef enum {
	OsCat2Isr_Start     = 16,
	OsCat2Isr_Stop      = 17,
	OsCat2Isr_Activate  = 18,
	OsCat2Isr_Preempt   = 19,
	OsCat2Isr_Resume    = 20
} Arti_OsCat2IsrEventType;

/** ARTI ISR1 state transitions **/
typedef enum {
	OsCat1Isr_Start     = 22,
	OsCat1Isr_Stop      = 23,
//	OsCat1Isr_Activate  = 0,
//	OsCat1Isr_Preempt   = 0,
//	OsCat1Isr_Resume    = 0
} Arti_OsCat1IsrEventType;

/** ARTI OS spinlock state transitions **/
typedef enum {
	OsSpinlock_Locked   = 24,
	OsSpinlock_Released = 25
} Arti_OsSpinlockEventType;

/** ARTI OS resource state transitions **/
typedef enum {
	OsResource_Locked   = 26,
	OsResource_Unlocked = 27
} Arti_OsResourceEventType;

/** ARTI OS application state transitions **/
typedef enum {
	OsApplication_Start         = 32,
	OsApplication_Restart       = 33,
	OsApplication_AllowAccess   = 34,
	OsApplication_Terminate     = 35,
} Arti_OsApplicationEventType;

/** ARTI OS hook events **/
typedef enum {
	OsHook_ErrorHook_Start      = 40,
	OsHook_ErrorHook_Return     = 41,
	OsHook_PostTaskHook_Start   = 42,
	OsHook_PostTaskHook_Return  = 43,
	OsHook_PreTaskHook_Start    = 44,
	OsHook_PreTaskHook_Return   = 45,
	OsHook_ProtectionHook_Start = 46,
	OsHook_ProtectionHook_Return= 47,
	OsHook_StartupHook_Start    = 48,
	OsHook_StartupHook_Return   = 49,
	OsHook_ShutdownHook_Start   = 50,
	OsHook_ShutdownHook_Return  = 51,
} Arti_OsHookEventType;

/** ARTI OS service call events **/

#define ARTI_OSSC_START             0x00
#define ARTI_OSSC_RETURN            0x80

#define ARTI_OSSC_OSEK  0x00    // OSEK SCs starting with 0
#define ARTI_OSSC_AR    0x20    // AUTOSAR SCs starting with 32

typedef enum {
	// numbering according to SWS_OS R20-11 chapter 7.17.4, starting with 1
	OsServiceCall_EnableAllInterrupts_Start     = (ARTI_OSSC_OSEK +  7) | ARTI_OSSC_START,
	OsServiceCall_EnableAllInterrupts_Return    = (ARTI_OSSC_OSEK +  7) | ARTI_OSSC_RETURN,
	OsServiceCall_DisableAllInterrupts_Start    = (ARTI_OSSC_OSEK +  8) | ARTI_OSSC_START,
	OsServiceCall_DisableAllInterrupts_Return   = (ARTI_OSSC_OSEK +  8) | ARTI_OSSC_RETURN,
	OsServiceCall_ResumeAllInterrupts_Start     = (ARTI_OSSC_OSEK +  9) | ARTI_OSSC_START,
	OsServiceCall_ResumeAllInterrupts_Return    = (ARTI_OSSC_OSEK +  9) | ARTI_OSSC_RETURN,
	OsServiceCall_SuspendAllInterrupts_Start    = (ARTI_OSSC_OSEK +  10)| ARTI_OSSC_START,
	OsServiceCall_SuspendAllInterrupts_Return   = (ARTI_OSSC_OSEK +  10)| ARTI_OSSC_RETURN,
	OsServiceCall_ResumeOSInterrupts_Start      = (ARTI_OSSC_OSEK +  11)| ARTI_OSSC_START,
	OsServiceCall_ResumeOSInterrupts_Return     = (ARTI_OSSC_OSEK +  11)| ARTI_OSSC_RETURN,
	OsServiceCall_SuspendOSInterrupts_Start     = (ARTI_OSSC_OSEK +  12)| ARTI_OSSC_START,
	OsServiceCall_SuspendOSInterrupts_Return    = (ARTI_OSSC_OSEK +  12)| ARTI_OSSC_RETURN,
	OsServiceCall_TryToGetSpinlock_Start        = (ARTI_OSSC_AR   +  29)| ARTI_OSSC_START,
	OsServiceCall_TryToGetSpinlock_Return       = (ARTI_OSSC_AR   +  29)| ARTI_OSSC_RETURN,
} Arti_OsServiceCallEventType;

/** ARTI RTE runnable transitions **/
typedef enum {
	RteRunnable_Start   = 0,
	RteRunnable_Return  = 1
} Arti_RteRunnableEventType;

#define ARTI_COMMON_RUNNABLE_RETURN_ID (0x0)


/**********************************************************************************************************************
 * Trace specific includes
 ********************************************************************************************************************/

#ifdef ARTI_T32_DATA_TRACE
#include "arti_t32_data_trace/arti_t32_data_trace.h"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_LOGGER
#include "arti_t32_logger/arti_t32_logger.h"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_LOGGER_SINGLECORE
#include "arti_t32_logger_singlecore/arti_t32_logger_singlecore.h"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_FDX
#include "arti_t32_fdx/arti_t32_fdx.h"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_FDX_SINGLECORE
#include "arti_t32_fdx_singlecore/arti_t32_fdx_singlecore.h"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_TC2xx_LMU_HIGHTEC
#include "arti_t32_tc2xx_lmu_hightec/arti_t32_tc2xx_lmu_hightec.h"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_TC2xx_LMU_TASKING
#include "arti_t32_tc2xx_lmu_tasking/arti_t32_tc2xx_lmu_tasking.h"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_TC3xx_OLDA_GHS
#include "arti_t32_tc3xx_olda_ghs/arti_t32_tc3xx_olda_ghs.h"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_TC3xx_OLDA_HIGHTEC
#include "arti_t32_tc3xx_olda_hightec/arti_t32_tc3xx_olda_hightec.h"
#define ARTI_T32_INCLUDED
#endif

#ifdef ARTI_T32_TC3xx_OLDA_TASKING
#include "arti_t32_tc3xx_olda_tasking/arti_t32_tc3xx_olda_tasking.h"
#define ARTI_T32_INCLUDED
#endif

#ifndef ARTI_T32_INCLUDED
#error "Select an environment in arti.h!"
#endif


/**********************************************************************************************************************
 * Common ARTI Hook Implementation
 ********************************************************************************************************************/

typedef unsigned int arti_uint32;

#define ARTI_TRACE(_contextName, _className, _instanceName, instanceParameter, _eventName, eventParameter) \
	ARTI_TRACE ## _ ## _className((_contextName), (_eventName), (instanceParameter), (eventParameter))

#ifdef ARTI_ENABLE_OS_TASK
#define ARTI_TRACE_AR_CP_OS_TASK(_contextName, _eventName, CoreId, TaskId)  { \
	arti_os_trace = (TaskId<<16) | (ARTI_VALID_OS_SIGNALING<<8) | (((arti_uint32)(_eventName))<<8) | CoreId; \
	T32_ARTI_TRACE(_contextName, arti_os_trace, CoreId); \
	}
#define ARTI_TRACE_AR_CP_OSARTI_TASK(_contextName, _eventName, CoreId, TaskId) { \
	arti_os_trace = (TaskId<<16) | (ARTI_VALID_OS_SIGNALING<<8) | (((arti_uint32)(_eventName))<<8) | CoreId; \
	T32_ARTI_TRACE(_contextName, arti_os_trace, CoreId); \
	}
#else
#define ARTI_TRACE_AR_CP_OS_TASK(_contextName, _eventName, CoreId, TaskId)
#define ARTI_TRACE_AR_CP_OSARTI_TASK(_contextName, _eventName, CoreId, TaskId)
#endif

#ifdef ARTI_ENABLE_OS_CAT2ISR
#define ARTI_TRACE_AR_CP_OS_CAT2ISR(_contextName, _eventName, CoreId, IsrId) { \
	arti_os_trace = (IsrId<<16) | (ARTI_VALID_OS_SIGNALING<<8) | (((arti_uint32)(_eventName))<<8) | CoreId; \
	T32_ARTI_TRACE(_contextName, arti_os_trace, CoreId); \
	}
#define ARTI_TRACE_AR_CP_OSARTI_CAT2ISR(_contextName, _eventName, CoreId, IsrId) { \
	arti_os_trace = (IsrId<<16) | (ARTI_VALID_OS_SIGNALING<<8) | (((arti_uint32)(_eventName))<<8) | CoreId; \
	T32_ARTI_TRACE(_contextName, arti_os_trace, CoreId); \
	}
#else
#define ARTI_TRACE_AR_CP_OS_CAT2ISR(_contextName, _eventName, CoreId, IsrId)
#define ARTI_TRACE_AR_CP_OSARTI_CAT2ISR(_contextName, _eventName, CoreId, IsrId)
#endif

#ifdef ARTI_ENABLE_OS_CAT1ISR
#define ARTI_TRACE_AR_CP_ARTI_CAT1ISR(_contextName, _eventName, CoreId, IsrId) { \
	arti_os_trace = (IsrId<<16) | (ARTI_VALID_OS_SIGNALING<<8) | (((arti_uint32)(_eventName))<<8) | CoreId; \
	T32_ARTI_TRACE(_contextName, arti_os_trace, CoreId); \
	}
#define ARTI_TRACE_AR_CP_ARTIEXT_CAT1ISR(_contextName, _eventName, CoreId, IsrId) { \
	arti_os_trace = (IsrId<<16) | (ARTI_VALID_OS_SIGNALING<<8) | (((arti_uint32)(_eventName))<<8) | CoreId; \
	T32_ARTI_TRACE(_contextName, arti_os_trace, CoreId); \
	}
#else
#define ARTI_TRACE_AR_CP_ARTI_CAT1ISR(_contextName, _eventName, CoreId, IsrId)
#define ARTI_TRACE_AR_CP_ARTIEXT_CAT1ISR(_contextName, _eventName, CoreId, IsrId)
#endif

#ifdef ARTI_ENABLE_OS_SPINLOCK
#define ARTI_TRACE_AR_CP_OS_SPINLOCK(_contextName, _eventName, CoreId, SpinlockId) { \
	arti_os_trace = (SpinlockId<<16) | (ARTI_VALID_OS_SIGNALING<<8) | (((arti_uint32)(_eventName))<<8) | CoreId; \
	T32_ARTI_TRACE(_contextName, arti_os_trace, CoreId); \
	}
#else
#define ARTI_TRACE_AR_CP_OS_SPINLOCK(_contextName, _eventName, CoreId, SpinlockId)
#endif

#ifdef ARTI_ENABLE_OS_APPLICATION
#define ARTI_TRACE_AR_CP_OS_APPLICATION(_contextName, _eventName, CoreId, AppId) { \
	arti_os_trace = (AppId<<16) | (ARTI_VALID_OS_SIGNALING<<8) | (((arti_uint32)(_eventName))<<8) | CoreId; \
	T32_ARTI_TRACE(_contextName, arti_os_trace, CoreId); \
	}
#else
#define ARTI_TRACE_AR_CP_OS_APPLICATION(_contextName, _eventName, CoreId, AppId)
#endif

#ifdef ARTI_ENABLE_OS_HOOK
#define ARTI_TRACE_AR_CP_OS_HOOK(_contextName, _eventName, CoreId, eventParameter) { \
	arti_os_trace = (((arti_uint32)(eventParameter))<<16) | (ARTI_VALID_OS_SIGNALING<<8) | (((arti_uint32)(_eventName))<<8) | CoreId; \
	T32_ARTI_TRACE(_contextName, arti_os_trace, CoreId); \
	}
#else
#define ARTI_TRACE_AR_CP_OS_HOOK(_contextName, _eventName, CoreId, eventParameter)
#endif

#ifdef ARTI_ENABLE_OS_SERVICECALLS
#define ARTI_TRACE_AR_CP_OS_SERVICECALLS(_contextName, _eventName, CoreId, zero) { \
	arti_sc_trace = (ARTI_OSSC_START<<8) | (((arti_uint32)(_eventName))<<8) | CoreId; \
	T32_ARTI_TRACE(_contextName, arti_sc_trace, CoreId); \
	}
#else
#define ARTI_TRACE_AR_CP_OS_SERVICECALLS(_contextName, _eventName, CoreId, zero)
#endif

#ifdef ARTI_ENABLE_RTE_RUNNABLE
#define ARTI_TRACE_AR_CP_RTE_RUNNABLE(_contextName, _eventName, CtsPtr, RunnableId) { \
	arti_uint32 CoreId = (arti_uint32) T32_ARTI_GETCOREID(); \
	arti_rte_trace = (_eventName == RteRunnable_Start) ? \
			(RunnableId<<8) | CoreId : \
			(ARTI_COMMON_RUNNABLE_RETURN_ID<<8) | CoreId; \
	T32_ARTI_TRACE(_contextName, arti_rte_trace, CoreId); \
	}
#else
#define ARTI_TRACE_AR_CP_RTE_RUNNABLE(_contextName, _eventName, CtsPtr, RunnableId)
#endif


#endif /* ARTI_COMMON_H */

/**********************************************************************************************************************
 *  END OF FILE: arti_common.h
 *********************************************************************************************************************/
