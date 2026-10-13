/****************************************************************************************************
*   FileName              : Os_ArtiCfg.h
*
*   BSW Module            : Os
*
*   brief                 : ARTI hook tracing switches and ARTI shadow-state values (openspec
*                           add-arti-hook-tracing, design D3, D4, D6). Included by the kernel type headers,
*                           so it must not include the trace tool's Os_Arti.h (that is Os_ArtiHooks.h).
*                           Generated from the same event list (Os_ArtiEvents.m) as Os_ArtiHooks.h.
****************************************************************************************************/
#ifndef OS_ARTICFG_H_
#define OS_ARTICFG_H_

#include "Std_Types.h"          /* STD_ON / STD_OFF */
[!//
[!NOCODE!][!//
[!VAR "ArtiEventsLoaded" = "'false'"!][!//
[!INCLUDE "Os_ArtiEvents.m"!][!//
[!ENDNOCODE!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!IF "$ArtiEventsLoaded = 'true'"!][!CALL "Os_ArtiEventList"!][!ELSE!][!//
#error "Os_ArtiCfg.h: Os_ArtiEvents.m was not found next to the Os templates"
[!VAR "ArtiOn" = "'false'"!][!VAR "ArtiEnhanced" = "'false'"!][!//
[!VAR "ArtiTraceApplication" = "'false'"!][!VAR "ArtiTraceTask" = "'false'"!][!VAR "ArtiTraceCat2Isr" = "'false'"!][!//
[!VAR "ArtiTraceServiceCalls" = "'false'"!][!VAR "ArtiTraceSpinlock" = "'false'"!][!VAR "ArtiTraceHook" = "'false'"!][!//
[!ENDIF!][!//
[!/* OnOff: 'true' -> STD_ON */!][!//
[!MACRO "ArtiOnOff", "Flag" = ""!][!IF "$Flag = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!][!ENDMACRO!][!//

/* ================================ Switches (Os configuration) ================================== */
/* OsUseArti */
#define OS_ARTI_ON                      ([!CALL "ArtiOnOff", "Flag" = "$ArtiOn"!])
/* OsVendorArtiStateModel = ENHANCED: AR_CP_OSARTI_TASK / AR_CP_OSARTI_CAT2ISR */
#define OS_ARTI_ENHANCED                ([!CALL "ArtiOnOff", "Flag" = "$ArtiEnhanced"!])
/* OsVendorArtiTrace<Class>, already combined with OsUseArti */
#define OS_ARTI_TRACE_APPLICATION       ([!CALL "ArtiOnOff", "Flag" = "$ArtiTraceApplication"!])
#define OS_ARTI_TRACE_TASK              ([!CALL "ArtiOnOff", "Flag" = "$ArtiTraceTask"!])
#define OS_ARTI_TRACE_CAT2ISR           ([!CALL "ArtiOnOff", "Flag" = "$ArtiTraceCat2Isr"!])
#define OS_ARTI_TRACE_SERVICECALLS      ([!CALL "ArtiOnOff", "Flag" = "$ArtiTraceServiceCalls"!])
#define OS_ARTI_TRACE_SPINLOCK          ([!CALL "ArtiOnOff", "Flag" = "$ArtiTraceSpinlock"!])
#define OS_ARTI_TRACE_HOOK              ([!CALL "ArtiOnOff", "Flag" = "$ArtiTraceHook"!])

/* ARTI shadow state of Tasks (design D4); the field exists when OS_ARTI_TRACE_TASK is STD_ON */
#define OS_ARTI_TASK_SUSPENDED          (0U)
#define OS_ARTI_TASK_ACTIVATED          (1U)    /* standard model: Ready */
#define OS_ARTI_TASK_RUNNING            (2U)
#define OS_ARTI_TASK_PREEMPTED          (3U)    /* standard model: Ready */
#define OS_ARTI_TASK_WAITING            (4U)
#define OS_ARTI_TASK_RELEASED           (5U)    /* standard model: Ready */
/* ARTI shadow state of Cat2 ISRs (enhanced model only) */
#define OS_ARTI_ISR_INACTIVE            (0U)
#define OS_ARTI_ISR_RUNNING             (1U)
#define OS_ARTI_ISR_PREEMPTED           (2U)

[!ENDSELECT!][!//

#endif /* OS_ARTICFG_H_ */
