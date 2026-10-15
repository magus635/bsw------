/**********************************************************************************************************************
 * Os_Arti.h - baseline of the OS specific ARTI hook macros (AUTOSAR CP SWS ARTI 7.2, SWS OS R21-11 7.17).
 *
 * One of the three files every trace tool vendor starts from (Arti.h, Os_Arti.h, Arti.c).  The kernel includes it
 * through Os_ArtiHooks.h, when OS_ARTI_USE_MOCK is not defined.  It is complete and works as it is.
 * Places a vendor may adapt are marked "VENDOR".
 *
 * The kernel calls ARTI_TRACE(<context>, <class>, <OS short name>, <core>, <event>, <parameter>) (Arti.h), which
 * becomes ARTI_TRACE_<class>(<context>, <event>, <core>, <parameter>) below.  The event is an enumerator that
 * holds the event number.  Numbers and traced words are the same as those of the Lauterbach ARTI implementation
 * (hooks_cp/common/arti_common.h of TRACE32), so that the TRACE32 ARTI decoding applies.
 *
 * Parameter of the classes:
 *   AR_CP_OS(ARTI)_TASK, _CAT2ISR, AR_CP_ARTI(EXT)_CAT1ISR : task ID, ISR ID
 *   AR_CP_OS_SPINLOCK                                      : spinlock ID
 *   AR_CP_OS_APPLICATION                                   : application ID
 *   AR_CP_OS_HOOK                                          : error code; ProtectionHook: fatal error / reaction
 *   AR_CP_OS_SERVICECALLS                                  : not recorded
 * Events that depend on the configuration (the hooks of the OS-Applications: OsHook_<Hook>_<Application>_Start /
 * _Return) are numbered from 64 on in the generated Os_ArtiHooks.h.
 *
 * Context: NOSUSP events are emitted with interrupts masked up to OS_ISR_TP_DISABLE_LEVEL, SPRVSR events (service
 * calls) are not.  A higher priority Cat1 ISR can interrupt either, so the macros must be reentrant and must not
 * call OS services.
 **********************************************************************************************************************/
#ifndef OS_ARTI_H_
#define OS_ARTI_H_

#include "Arti.h"                       /* SWS ARTI 7.2: first, before any module specific macro */

/* VENDOR: the event numbers.  The trace tool must know them; change them only together with the tool. */

/* AR_CP_OS_TASK, AR_CP_OSARTI_TASK (the standard model uses Activate, Start, Preempt, Wait, Release, Terminate) */
typedef enum
{
    OsTask_Activate  = 0,
    OsTask_Start     = 1,
    OsTask_Wait      = 2,
    OsTask_Release   = 3,
    OsTask_Preempt   = 4,
    OsTask_Terminate = 5,
    OsTask_Resume    = 6,
    OsTask_Continue  = 7
} Arti_OsTaskEventType;

/* AR_CP_OS_CAT2ISR, AR_CP_OSARTI_CAT2ISR (the standard model uses Start and Stop) */
typedef enum
{
    OsCat2Isr_Start    = 16,
    OsCat2Isr_Stop     = 17,
    OsCat2Isr_Activate = 18,
    OsCat2Isr_Preempt  = 19,
    OsCat2Isr_Resume   = 20
} Arti_OsCat2IsrEventType;

/* AR_CP_ARTI_CAT1ISR, AR_CP_ARTIEXT_CAT1ISR: Cat1 ISRs do not pass the OS, the user places these hooks */
typedef enum
{
    OsCat1Isr_Start = 22,
    OsCat1Isr_Stop  = 23
} Arti_OsCat1IsrEventType;

/* AR_CP_OS_SPINLOCK */
typedef enum
{
    OsSpinlock_Locked   = 24,
    OsSpinlock_Released = 25
} Arti_OsSpinlockEventType;

/* AR_CP_OS_APPLICATION */
typedef enum
{
    OsApplication_Start       = 32,
    OsApplication_Restart     = 33,
    OsApplication_AllowAccess = 34,
    OsApplication_Terminate   = 35
} Arti_OsApplicationEventType;

/* AR_CP_OS_HOOK: the hooks of the OS */
typedef enum
{
    OsHook_ErrorHook_Start       = 40,
    OsHook_ErrorHook_Return      = 41,
    OsHook_PostTaskHook_Start    = 42,
    OsHook_PostTaskHook_Return   = 43,
    OsHook_PreTaskHook_Start     = 44,
    OsHook_PreTaskHook_Return    = 45,
    OsHook_ProtectionHook_Start  = 46,
    OsHook_ProtectionHook_Return = 47,
    OsHook_StartupHook_Start     = 48,
    OsHook_StartupHook_Return    = 49,
    OsHook_ShutdownHook_Start    = 50,
    OsHook_ShutdownHook_Return   = 51
} Arti_OsHookEventType;

/* AR_CP_OS_SERVICECALLS: bits [8:14] of arti_sc_trace.  The number is the position of the service in the table of
 * SWS OS R21-11 7.17.4 (the services of OSEK from 1, the AUTOSAR services from 1 plus 0x20); bit 7 (0x80) marks the
 * return.  StartNonAutosarCore keeps its number but is not emitted by this kernel. */
#define ARTI_OSSC_START     (0x00U)
#define ARTI_OSSC_RETURN    (0x80U)
#define ARTI_OSSC_OSEK      (0x00U)
#define ARTI_OSSC_AR        (0x20U)

typedef enum
{
    OsServiceCall_ActivateTask_Start                  = (ARTI_OSSC_OSEK +  1U) | ARTI_OSSC_START,
    OsServiceCall_ActivateTask_Return                 = (ARTI_OSSC_OSEK +  1U) | ARTI_OSSC_RETURN,
    OsServiceCall_TerminateTask_Start                 = (ARTI_OSSC_OSEK +  2U) | ARTI_OSSC_START,
    OsServiceCall_TerminateTask_Return                = (ARTI_OSSC_OSEK +  2U) | ARTI_OSSC_RETURN,
    OsServiceCall_ChainTask_Start                     = (ARTI_OSSC_OSEK +  3U) | ARTI_OSSC_START,
    OsServiceCall_ChainTask_Return                    = (ARTI_OSSC_OSEK +  3U) | ARTI_OSSC_RETURN,
    OsServiceCall_Schedule_Start                      = (ARTI_OSSC_OSEK +  4U) | ARTI_OSSC_START,
    OsServiceCall_Schedule_Return                     = (ARTI_OSSC_OSEK +  4U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetTaskID_Start                     = (ARTI_OSSC_OSEK +  5U) | ARTI_OSSC_START,
    OsServiceCall_GetTaskID_Return                    = (ARTI_OSSC_OSEK +  5U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetTaskState_Start                  = (ARTI_OSSC_OSEK +  6U) | ARTI_OSSC_START,
    OsServiceCall_GetTaskState_Return                 = (ARTI_OSSC_OSEK +  6U) | ARTI_OSSC_RETURN,
    OsServiceCall_EnableAllInterrupts_Start           = (ARTI_OSSC_OSEK +  7U) | ARTI_OSSC_START,
    OsServiceCall_EnableAllInterrupts_Return          = (ARTI_OSSC_OSEK +  7U) | ARTI_OSSC_RETURN,
    OsServiceCall_DisableAllInterrupts_Start          = (ARTI_OSSC_OSEK +  8U) | ARTI_OSSC_START,
    OsServiceCall_DisableAllInterrupts_Return         = (ARTI_OSSC_OSEK +  8U) | ARTI_OSSC_RETURN,
    OsServiceCall_ResumeAllInterrupts_Start           = (ARTI_OSSC_OSEK +  9U) | ARTI_OSSC_START,
    OsServiceCall_ResumeAllInterrupts_Return          = (ARTI_OSSC_OSEK +  9U) | ARTI_OSSC_RETURN,
    OsServiceCall_SuspendAllInterrupts_Start          = (ARTI_OSSC_OSEK + 10U) | ARTI_OSSC_START,
    OsServiceCall_SuspendAllInterrupts_Return         = (ARTI_OSSC_OSEK + 10U) | ARTI_OSSC_RETURN,
    OsServiceCall_ResumeOSInterrupts_Start            = (ARTI_OSSC_OSEK + 11U) | ARTI_OSSC_START,
    OsServiceCall_ResumeOSInterrupts_Return           = (ARTI_OSSC_OSEK + 11U) | ARTI_OSSC_RETURN,
    OsServiceCall_SuspendOSInterrupts_Start           = (ARTI_OSSC_OSEK + 12U) | ARTI_OSSC_START,
    OsServiceCall_SuspendOSInterrupts_Return          = (ARTI_OSSC_OSEK + 12U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetResource_Start                   = (ARTI_OSSC_OSEK + 13U) | ARTI_OSSC_START,
    OsServiceCall_GetResource_Return                  = (ARTI_OSSC_OSEK + 13U) | ARTI_OSSC_RETURN,
    OsServiceCall_ReleaseResource_Start               = (ARTI_OSSC_OSEK + 14U) | ARTI_OSSC_START,
    OsServiceCall_ReleaseResource_Return              = (ARTI_OSSC_OSEK + 14U) | ARTI_OSSC_RETURN,
    OsServiceCall_SetEvent_Start                      = (ARTI_OSSC_OSEK + 15U) | ARTI_OSSC_START,
    OsServiceCall_SetEvent_Return                     = (ARTI_OSSC_OSEK + 15U) | ARTI_OSSC_RETURN,
    OsServiceCall_ClearEvent_Start                    = (ARTI_OSSC_OSEK + 16U) | ARTI_OSSC_START,
    OsServiceCall_ClearEvent_Return                   = (ARTI_OSSC_OSEK + 16U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetEvent_Start                      = (ARTI_OSSC_OSEK + 17U) | ARTI_OSSC_START,
    OsServiceCall_GetEvent_Return                     = (ARTI_OSSC_OSEK + 17U) | ARTI_OSSC_RETURN,
    OsServiceCall_WaitEvent_Start                     = (ARTI_OSSC_OSEK + 18U) | ARTI_OSSC_START,
    OsServiceCall_WaitEvent_Return                    = (ARTI_OSSC_OSEK + 18U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetAlarmBase_Start                  = (ARTI_OSSC_OSEK + 19U) | ARTI_OSSC_START,
    OsServiceCall_GetAlarmBase_Return                 = (ARTI_OSSC_OSEK + 19U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetAlarm_Start                      = (ARTI_OSSC_OSEK + 20U) | ARTI_OSSC_START,
    OsServiceCall_GetAlarm_Return                     = (ARTI_OSSC_OSEK + 20U) | ARTI_OSSC_RETURN,
    OsServiceCall_SetRelAlarm_Start                   = (ARTI_OSSC_OSEK + 21U) | ARTI_OSSC_START,
    OsServiceCall_SetRelAlarm_Return                  = (ARTI_OSSC_OSEK + 21U) | ARTI_OSSC_RETURN,
    OsServiceCall_SetAbsAlarm_Start                   = (ARTI_OSSC_OSEK + 22U) | ARTI_OSSC_START,
    OsServiceCall_SetAbsAlarm_Return                  = (ARTI_OSSC_OSEK + 22U) | ARTI_OSSC_RETURN,
    OsServiceCall_CancelAlarm_Start                   = (ARTI_OSSC_OSEK + 23U) | ARTI_OSSC_START,
    OsServiceCall_CancelAlarm_Return                  = (ARTI_OSSC_OSEK + 23U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetActiveApplicationMode_Start      = (ARTI_OSSC_OSEK + 24U) | ARTI_OSSC_START,
    OsServiceCall_GetActiveApplicationMode_Return     = (ARTI_OSSC_OSEK + 24U) | ARTI_OSSC_RETURN,
    OsServiceCall_StartOS_Start                       = (ARTI_OSSC_OSEK + 25U) | ARTI_OSSC_START,
    OsServiceCall_StartOS_Return                      = (ARTI_OSSC_OSEK + 25U) | ARTI_OSSC_RETURN,
    OsServiceCall_ShutdownOS_Start                    = (ARTI_OSSC_OSEK + 26U) | ARTI_OSSC_START,
    OsServiceCall_ShutdownOS_Return                   = (ARTI_OSSC_OSEK + 26U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetApplicationID_Start              = (ARTI_OSSC_AR +  1U) | ARTI_OSSC_START,
    OsServiceCall_GetApplicationID_Return             = (ARTI_OSSC_AR +  1U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetCurrentApplicationID_Start       = (ARTI_OSSC_AR +  2U) | ARTI_OSSC_START,
    OsServiceCall_GetCurrentApplicationID_Return      = (ARTI_OSSC_AR +  2U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetISRID_Start                      = (ARTI_OSSC_AR +  3U) | ARTI_OSSC_START,
    OsServiceCall_GetISRID_Return                     = (ARTI_OSSC_AR +  3U) | ARTI_OSSC_RETURN,
    OsServiceCall_CallTrustedFunction_Start           = (ARTI_OSSC_AR +  4U) | ARTI_OSSC_START,
    OsServiceCall_CallTrustedFunction_Return          = (ARTI_OSSC_AR +  4U) | ARTI_OSSC_RETURN,
    OsServiceCall_CheckISRMemoryAccess_Start          = (ARTI_OSSC_AR +  5U) | ARTI_OSSC_START,
    OsServiceCall_CheckISRMemoryAccess_Return         = (ARTI_OSSC_AR +  5U) | ARTI_OSSC_RETURN,
    OsServiceCall_CheckTaskMemoryAccess_Start         = (ARTI_OSSC_AR +  6U) | ARTI_OSSC_START,
    OsServiceCall_CheckTaskMemoryAccess_Return        = (ARTI_OSSC_AR +  6U) | ARTI_OSSC_RETURN,
    OsServiceCall_CheckObjectAccess_Start             = (ARTI_OSSC_AR +  7U) | ARTI_OSSC_START,
    OsServiceCall_CheckObjectAccess_Return            = (ARTI_OSSC_AR +  7U) | ARTI_OSSC_RETURN,
    OsServiceCall_CheckObjectOwnership_Start          = (ARTI_OSSC_AR +  8U) | ARTI_OSSC_START,
    OsServiceCall_CheckObjectOwnership_Return         = (ARTI_OSSC_AR +  8U) | ARTI_OSSC_RETURN,
    OsServiceCall_StartScheduleTableRel_Start         = (ARTI_OSSC_AR +  9U) | ARTI_OSSC_START,
    OsServiceCall_StartScheduleTableRel_Return        = (ARTI_OSSC_AR +  9U) | ARTI_OSSC_RETURN,
    OsServiceCall_StartScheduleTableAbs_Start         = (ARTI_OSSC_AR + 10U) | ARTI_OSSC_START,
    OsServiceCall_StartScheduleTableAbs_Return        = (ARTI_OSSC_AR + 10U) | ARTI_OSSC_RETURN,
    OsServiceCall_StopScheduleTable_Start             = (ARTI_OSSC_AR + 11U) | ARTI_OSSC_START,
    OsServiceCall_StopScheduleTable_Return            = (ARTI_OSSC_AR + 11U) | ARTI_OSSC_RETURN,
    OsServiceCall_NextScheduleTable_Start             = (ARTI_OSSC_AR + 12U) | ARTI_OSSC_START,
    OsServiceCall_NextScheduleTable_Return            = (ARTI_OSSC_AR + 12U) | ARTI_OSSC_RETURN,
    OsServiceCall_StartScheduleTableSynchron_Start    = (ARTI_OSSC_AR + 13U) | ARTI_OSSC_START,
    OsServiceCall_StartScheduleTableSynchron_Return   = (ARTI_OSSC_AR + 13U) | ARTI_OSSC_RETURN,
    OsServiceCall_SyncScheduleTable_Start             = (ARTI_OSSC_AR + 14U) | ARTI_OSSC_START,
    OsServiceCall_SyncScheduleTable_Return            = (ARTI_OSSC_AR + 14U) | ARTI_OSSC_RETURN,
    OsServiceCall_SetScheduleTableAsync_Start         = (ARTI_OSSC_AR + 15U) | ARTI_OSSC_START,
    OsServiceCall_SetScheduleTableAsync_Return        = (ARTI_OSSC_AR + 15U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetScheduleTableStatus_Start        = (ARTI_OSSC_AR + 16U) | ARTI_OSSC_START,
    OsServiceCall_GetScheduleTableStatus_Return       = (ARTI_OSSC_AR + 16U) | ARTI_OSSC_RETURN,
    OsServiceCall_IncrementCounter_Start              = (ARTI_OSSC_AR + 17U) | ARTI_OSSC_START,
    OsServiceCall_IncrementCounter_Return             = (ARTI_OSSC_AR + 17U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetCounterValue_Start               = (ARTI_OSSC_AR + 18U) | ARTI_OSSC_START,
    OsServiceCall_GetCounterValue_Return              = (ARTI_OSSC_AR + 18U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetElapsedValue_Start               = (ARTI_OSSC_AR + 19U) | ARTI_OSSC_START,
    OsServiceCall_GetElapsedValue_Return              = (ARTI_OSSC_AR + 19U) | ARTI_OSSC_RETURN,
    OsServiceCall_TerminateApplication_Start          = (ARTI_OSSC_AR + 20U) | ARTI_OSSC_START,
    OsServiceCall_TerminateApplication_Return         = (ARTI_OSSC_AR + 20U) | ARTI_OSSC_RETURN,
    OsServiceCall_AllowAccess_Start                   = (ARTI_OSSC_AR + 21U) | ARTI_OSSC_START,
    OsServiceCall_AllowAccess_Return                  = (ARTI_OSSC_AR + 21U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetApplicationState_Start           = (ARTI_OSSC_AR + 22U) | ARTI_OSSC_START,
    OsServiceCall_GetApplicationState_Return          = (ARTI_OSSC_AR + 22U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetNumberOfActivatedCores_Start     = (ARTI_OSSC_AR + 23U) | ARTI_OSSC_START,
    OsServiceCall_GetNumberOfActivatedCores_Return    = (ARTI_OSSC_AR + 23U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetCoreID_Start                     = (ARTI_OSSC_AR + 24U) | ARTI_OSSC_START,
    OsServiceCall_GetCoreID_Return                    = (ARTI_OSSC_AR + 24U) | ARTI_OSSC_RETURN,
    OsServiceCall_StartCore_Start                     = (ARTI_OSSC_AR + 25U) | ARTI_OSSC_START,
    OsServiceCall_StartCore_Return                    = (ARTI_OSSC_AR + 25U) | ARTI_OSSC_RETURN,
    OsServiceCall_StartNonAutosarCore_Start           = (ARTI_OSSC_AR + 26U) | ARTI_OSSC_START,
    OsServiceCall_StartNonAutosarCore_Return          = (ARTI_OSSC_AR + 26U) | ARTI_OSSC_RETURN,
    OsServiceCall_GetSpinlock_Start                   = (ARTI_OSSC_AR + 27U) | ARTI_OSSC_START,
    OsServiceCall_GetSpinlock_Return                  = (ARTI_OSSC_AR + 27U) | ARTI_OSSC_RETURN,
    OsServiceCall_ReleaseSpinlock_Start               = (ARTI_OSSC_AR + 28U) | ARTI_OSSC_START,
    OsServiceCall_ReleaseSpinlock_Return              = (ARTI_OSSC_AR + 28U) | ARTI_OSSC_RETURN,
    OsServiceCall_TryToGetSpinlock_Start              = (ARTI_OSSC_AR + 29U) | ARTI_OSSC_START,
    OsServiceCall_TryToGetSpinlock_Return             = (ARTI_OSSC_AR + 29U) | ARTI_OSSC_RETURN,
    OsServiceCall_ShutdownAllCores_Start              = (ARTI_OSSC_AR + 30U) | ARTI_OSSC_START,
    OsServiceCall_ShutdownAllCores_Return             = (ARTI_OSSC_AR + 30U) | ARTI_OSSC_RETURN,
    OsServiceCall_ControlIdle_Start                   = (ARTI_OSSC_AR + 31U) | ARTI_OSSC_START,
    OsServiceCall_ControlIdle_Return                  = (ARTI_OSSC_AR + 31U) | ARTI_OSSC_RETURN,
    OsServiceCall_ReadPeripheral8_Start               = (ARTI_OSSC_AR + 32U) | ARTI_OSSC_START,
    OsServiceCall_ReadPeripheral8_Return              = (ARTI_OSSC_AR + 32U) | ARTI_OSSC_RETURN,
    OsServiceCall_ReadPeripheral16_Start              = (ARTI_OSSC_AR + 33U) | ARTI_OSSC_START,
    OsServiceCall_ReadPeripheral16_Return             = (ARTI_OSSC_AR + 33U) | ARTI_OSSC_RETURN,
    OsServiceCall_ReadPeripheral32_Start              = (ARTI_OSSC_AR + 34U) | ARTI_OSSC_START,
    OsServiceCall_ReadPeripheral32_Return             = (ARTI_OSSC_AR + 34U) | ARTI_OSSC_RETURN,
    OsServiceCall_WritePeripheral8_Start              = (ARTI_OSSC_AR + 35U) | ARTI_OSSC_START,
    OsServiceCall_WritePeripheral8_Return             = (ARTI_OSSC_AR + 35U) | ARTI_OSSC_RETURN,
    OsServiceCall_WritePeripheral16_Start             = (ARTI_OSSC_AR + 36U) | ARTI_OSSC_START,
    OsServiceCall_WritePeripheral16_Return            = (ARTI_OSSC_AR + 36U) | ARTI_OSSC_RETURN,
    OsServiceCall_WritePeripheral32_Start             = (ARTI_OSSC_AR + 37U) | ARTI_OSSC_START,
    OsServiceCall_WritePeripheral32_Return            = (ARTI_OSSC_AR + 37U) | ARTI_OSSC_RETURN,
    OsServiceCall_ModifyPeripheral8_Start             = (ARTI_OSSC_AR + 38U) | ARTI_OSSC_START,
    OsServiceCall_ModifyPeripheral8_Return            = (ARTI_OSSC_AR + 38U) | ARTI_OSSC_RETURN,
    OsServiceCall_ModifyPeripheral16_Start            = (ARTI_OSSC_AR + 39U) | ARTI_OSSC_START,
    OsServiceCall_ModifyPeripheral16_Return           = (ARTI_OSSC_AR + 39U) | ARTI_OSSC_RETURN,
    OsServiceCall_ModifyPeripheral32_Start            = (ARTI_OSSC_AR + 40U) | ARTI_OSSC_START,
    OsServiceCall_ModifyPeripheral32_Return           = (ARTI_OSSC_AR + 40U) | ARTI_OSSC_RETURN,
    OsServiceCall_EnableInterruptSource_Start         = (ARTI_OSSC_AR + 41U) | ARTI_OSSC_START,
    OsServiceCall_EnableInterruptSource_Return        = (ARTI_OSSC_AR + 41U) | ARTI_OSSC_RETURN,
    OsServiceCall_DisableInterruptSource_Start        = (ARTI_OSSC_AR + 42U) | ARTI_OSSC_START,
    OsServiceCall_DisableInterruptSource_Return       = (ARTI_OSSC_AR + 42U) | ARTI_OSSC_RETURN,
    OsServiceCall_ClearPendingInterrupt_Start         = (ARTI_OSSC_AR + 43U) | ARTI_OSSC_START,
    OsServiceCall_ClearPendingInterrupt_Return        = (ARTI_OSSC_AR + 43U) | ARTI_OSSC_RETURN,
    OsServiceCall_ActivateTaskAsyn_Start              = (ARTI_OSSC_AR + 44U) | ARTI_OSSC_START,
    OsServiceCall_ActivateTaskAsyn_Return             = (ARTI_OSSC_AR + 44U) | ARTI_OSSC_RETURN,
    OsServiceCall_SetEventAsyn_Start                  = (ARTI_OSSC_AR + 45U) | ARTI_OSSC_START,
    OsServiceCall_SetEventAsyn_Return                 = (ARTI_OSSC_AR + 45U) | ARTI_OSSC_RETURN
} Arti_OsServiceCallEventType;

/*********************************************************************************************************************
 * The macros of the classes.
 * VENDOR: this is where the event is recorded.  Here: ARTI_OS_WORD (Arti.h) is written to arti_os_trace and
 * ARTI_EMIT (Arti.h) is called, which stays empty for a data trace.  Replace the body for another recording method.
 * A class that is switched off in Arti.h compiles to nothing.
 ********************************************************************************************************************/

#if (ARTI_ENABLE_OS_TASK == STD_ON)
#define ARTI_TRACE_AR_CP_OS_TASK(contextName, eventName, core, objectId) \
    do { arti_os_trace = ARTI_OS_WORD((objectId), (eventName), (core)); \
         ARTI_EMIT(contextName, arti_os_trace, (core)); } while (0)
#else
#define ARTI_TRACE_AR_CP_OS_TASK(contextName, eventName, core, objectId)    ((void)(objectId))
#endif

#if (ARTI_ENABLE_OS_TASK == STD_ON)
#define ARTI_TRACE_AR_CP_OSARTI_TASK(contextName, eventName, core, objectId) \
    do { arti_os_trace = ARTI_OS_WORD((objectId), (eventName), (core)); \
         ARTI_EMIT(contextName, arti_os_trace, (core)); } while (0)
#else
#define ARTI_TRACE_AR_CP_OSARTI_TASK(contextName, eventName, core, objectId)    ((void)(objectId))
#endif

#if (ARTI_ENABLE_OS_CAT2ISR == STD_ON)
#define ARTI_TRACE_AR_CP_OS_CAT2ISR(contextName, eventName, core, objectId) \
    do { arti_os_trace = ARTI_OS_WORD((objectId), (eventName), (core)); \
         ARTI_EMIT(contextName, arti_os_trace, (core)); } while (0)
#else
#define ARTI_TRACE_AR_CP_OS_CAT2ISR(contextName, eventName, core, objectId)    ((void)(objectId))
#endif

#if (ARTI_ENABLE_OS_CAT2ISR == STD_ON)
#define ARTI_TRACE_AR_CP_OSARTI_CAT2ISR(contextName, eventName, core, objectId) \
    do { arti_os_trace = ARTI_OS_WORD((objectId), (eventName), (core)); \
         ARTI_EMIT(contextName, arti_os_trace, (core)); } while (0)
#else
#define ARTI_TRACE_AR_CP_OSARTI_CAT2ISR(contextName, eventName, core, objectId)    ((void)(objectId))
#endif

#if (ARTI_ENABLE_OS_CAT1ISR == STD_ON)
#define ARTI_TRACE_AR_CP_ARTI_CAT1ISR(contextName, eventName, core, objectId) \
    do { arti_os_trace = ARTI_OS_WORD((objectId), (eventName), (core)); \
         ARTI_EMIT(contextName, arti_os_trace, (core)); } while (0)
#else
#define ARTI_TRACE_AR_CP_ARTI_CAT1ISR(contextName, eventName, core, objectId)    ((void)(objectId))
#endif

#if (ARTI_ENABLE_OS_CAT1ISR == STD_ON)
#define ARTI_TRACE_AR_CP_ARTIEXT_CAT1ISR(contextName, eventName, core, objectId) \
    do { arti_os_trace = ARTI_OS_WORD((objectId), (eventName), (core)); \
         ARTI_EMIT(contextName, arti_os_trace, (core)); } while (0)
#else
#define ARTI_TRACE_AR_CP_ARTIEXT_CAT1ISR(contextName, eventName, core, objectId)    ((void)(objectId))
#endif

#if (ARTI_ENABLE_OS_SPINLOCK == STD_ON)
#define ARTI_TRACE_AR_CP_OS_SPINLOCK(contextName, eventName, core, objectId) \
    do { arti_os_trace = ARTI_OS_WORD((objectId), (eventName), (core)); \
         ARTI_EMIT(contextName, arti_os_trace, (core)); } while (0)
#else
#define ARTI_TRACE_AR_CP_OS_SPINLOCK(contextName, eventName, core, objectId)    ((void)(objectId))
#endif

#if (ARTI_ENABLE_OS_APPLICATION == STD_ON)
#define ARTI_TRACE_AR_CP_OS_APPLICATION(contextName, eventName, core, objectId) \
    do { arti_os_trace = ARTI_OS_WORD((objectId), (eventName), (core)); \
         ARTI_EMIT(contextName, arti_os_trace, (core)); } while (0)
#else
#define ARTI_TRACE_AR_CP_OS_APPLICATION(contextName, eventName, core, objectId)    ((void)(objectId))
#endif

#if (ARTI_ENABLE_OS_HOOK == STD_ON)
#define ARTI_TRACE_AR_CP_OS_HOOK(contextName, eventName, core, objectId) \
    do { arti_os_trace = ARTI_OS_WORD((objectId), (eventName), (core)); \
         ARTI_EMIT(contextName, arti_os_trace, (core)); } while (0)
#else
#define ARTI_TRACE_AR_CP_OS_HOOK(contextName, eventName, core, objectId)    ((void)(objectId))
#endif

/* AR_CP_OS_SERVICECALLS: the service call parameter (objectId) is not recorded.  It is still evaluated with
 * (void): the kernel passes local variables that are used for nothing else, and a macro that drops its argument
 * would make the compiler warn about them. */
#if (ARTI_ENABLE_OS_SERVICECALLS == STD_ON)
#define ARTI_TRACE_AR_CP_OS_SERVICECALLS(contextName, eventName, core, objectId) \
    do { arti_sc_trace = ((uint32)(eventName) << 8) | ((uint32)(core) & 0xFFU); \
         ARTI_EMIT(contextName, arti_sc_trace, (core)); (void)(objectId); } while (0)
#else
#define ARTI_TRACE_AR_CP_OS_SERVICECALLS(contextName, eventName, core, objectId)    ((void)(objectId))
#endif

#endif /* OS_ARTI_H_ */
