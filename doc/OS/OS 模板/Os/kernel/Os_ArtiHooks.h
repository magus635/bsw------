/****************************************************************************************************
*   FileName              : Os_ArtiHooks.h
*
*   BSW Module            : Os
*
*   brief                 : OS-internal ARTI hook wrapper macros (SWS OS R21-11 7.17), generated from the
*                           same event list (Os_ArtiEvents.m) as the ArtiHook containers of Os_Arti.arxml.
*                           The kernel only calls the OS_ARTI_* macros below, never ARTI_TRACE directly.
*                           openspec/changes/add-arti-hook-tracing/design.md D2, D3, D6, D7, D8.
*
*   Not exported: include it from kernel sources only.
****************************************************************************************************/
#ifndef OS_ARTIHOOKS_H_
#define OS_ARTIHOOKS_H_

#include "Os_ArtiCfg.h"         /* switches and shadow-state values */
[!//
[!NOCODE!][!//
[!VAR "ArtiEventsLoaded" = "'false'"!][!//
[!INCLUDE "Os_ArtiEvents.m"!][!//
[!ENDNOCODE!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!IF "$ArtiEventsLoaded = 'true'"!][!CALL "Os_ArtiEventList"!][!ELSE!][!//
#error "Os_ArtiHooks.h: Os_ArtiEvents.m was not found next to the Os templates"
[!VAR "ArtiOn" = "'false'"!][!VAR "ArtiEnhanced" = "'false'"!][!VAR "ArtiEvents" = "''"!][!VAR "ArtiServices" = "''"!][!VAR "ArtiAppHooks" = "''"!][!//
[!VAR "ArtiTraceApplication" = "'false'"!][!VAR "ArtiTraceTask" = "'false'"!][!VAR "ArtiTraceCat2Isr" = "'false'"!][!//
[!VAR "ArtiTraceServiceCalls" = "'false'"!][!VAR "ArtiTraceSpinlock" = "'false'"!][!VAR "ArtiTraceHook" = "'false'"!][!//
[!ENDIF!][!//
[!/* Semantic macro Name(Args) -> OS_ARTI_EV_<Ev>(Call) when Ev is in the event list, else ((void)0) */!][!//
[!MACRO "ArtiMap", "Name" = "", "Ev" = "", "Args" = "", "Call" = ""!][!//
[!IF "contains($ArtiEvents, concat(':', $Ev, ':'))"!][!//
#define [!"$Name"!]([!"$Args"!])    OS_ARTI_EV_[!"$Ev"!]([!"$Call"!])
[!ELSE!][!//
#define [!"$Name"!]([!"$Args"!])    ((void)0)
[!ENDIF!][!//
[!ENDMACRO!][!//

[!/* The hook implementation is only needed when some event is traced: with OsUseArti on and every
     OsVendorArtiTrace<Class> off (static ARTI debugging only) no trace tool header is required. */!][!//
[!IF "$ArtiOn = 'true' and $ArtiEvents != ''"!][!//
/* ================================ Hook implementation ========================================== */
/* Os_Arti.h (and Arti.h) come from the trace tool (SWS ARTI 7.2). OS_ARTI_USE_MOCK selects the strict
   mock generated next to this file instead (design D8, D9): not for production code. */
#if defined(OS_ARTI_USE_MOCK)
#include "Os_Arti_Mock.h"
#else
#include "Os_Arti.h"
#endif
[!IF "$ArtiTraceHook = 'true' and $ArtiAppHooks != ''"!][!//

/* Event numbers of the hooks of the OS-Applications.  They depend on the configuration, so they are not in
   Os_Arti.h; they follow the numbers of the OS hooks there (40..51), start at 64 and stay below 128 (the event
   number has 7 bits in the traced word).  The mock does not use them. */
#if !defined(OS_ARTI_USE_MOCK)
enum
{
[!VAR "ArtiEvNo" = "64"!][!//
[!LOOP "text:split($ArtiAppHooks, ',')"!]    OsHook_[!"text:split(., '/')[1]"!]_[!"text:split(., '/')[2]"!]_Start = [!"num:i($ArtiEvNo)"!],
    OsHook_[!"text:split(., '/')[1]"!]_[!"text:split(., '/')[2]"!]_Return = [!"num:i($ArtiEvNo + 1)"!],
[!VAR "ArtiEvNo" = "num:i($ArtiEvNo + 2)"!][!//
[!ENDLOOP!][!//
    OS_ARTI_APPHOOK_EVENT_END = [!"num:i($ArtiEvNo)"!]    /* first number that is not used */
};
[!IF "$ArtiEvNo > 128"!][!//
#error "Os_ArtiHooks.h: too many application hooks for the 7 bit event number of the traced word"
[!ENDIF!][!//
#endif
[!ENDIF!][!//

/* One macro per described hook: ARTI_TRACE(_contextName, _className, _instanceName, instanceParameter,
   _eventName, eventParameter), SWS_Arti_00018 order, literal tokens as in the ArtiHook containers. */
[!LOOP "text:split($ArtiEvents, ';')"!][!//
#define OS_ARTI_EV_[!"text:split(., ':')[3]"!](core, param) \
    ARTI_TRACE([!"text:split(., ':')[1]"!], [!"text:split(., ':')[2]"!], [!"$ArtiOsName"!], (core), [!"text:split(., ':')[3]"!], (param))
[!ENDLOOP!][!//
[!ENDIF!][!//

/* ================================ Kernel wrapper macros ======================================== */
/* core: OS core index (Os_Inf_GetCoreId()) of the core executing the transition. Pass local variables
   only: no function calls or side effects in the arguments (SWS_Arti_00018). */

/* AR_CP_OS_TASK / AR_CP_OSARTI_TASK. Standard model: Resume and Continue are reported as Start. */
[!LOOP "text:split('ACTIVATE:Activate,START:Start,PREEMPT:Preempt,WAIT:Wait,RELEASE:Release,TERMINATE:Terminate', ',')"!][!//
[!CALL "ArtiMap", "Name" = "concat('OS_ARTI_TASK_', text:split(., ':')[1])", "Ev" = "concat('OsTask_', text:split(., ':')[2])", "Args" = "'core, task'", "Call" = "'core, task'"!][!//
[!ENDLOOP!][!//
[!IF "$ArtiEnhanced = 'true'"!][!//
[!CALL "ArtiMap", "Name" = "'OS_ARTI_TASK_RESUME'", "Ev" = "'OsTask_Resume'", "Args" = "'core, task'", "Call" = "'core, task'"!][!//
[!CALL "ArtiMap", "Name" = "'OS_ARTI_TASK_CONTINUE'", "Ev" = "'OsTask_Continue'", "Args" = "'core, task'", "Call" = "'core, task'"!][!//
[!ELSE!][!//
[!CALL "ArtiMap", "Name" = "'OS_ARTI_TASK_RESUME'", "Ev" = "'OsTask_Start'", "Args" = "'core, task'", "Call" = "'core, task'"!][!//
[!CALL "ArtiMap", "Name" = "'OS_ARTI_TASK_CONTINUE'", "Ev" = "'OsTask_Start'", "Args" = "'core, task'", "Call" = "'core, task'"!][!//
[!ENDIF!][!//

/* AR_CP_OS_CAT2ISR / AR_CP_OSARTI_CAT2ISR. Standard model: only Start and Stop. */
[!LOOP "text:split('ACTIVATE:Activate,START:Start,PREEMPT:Preempt,RESUME:Resume,STOP:Stop', ',')"!][!//
[!CALL "ArtiMap", "Name" = "concat('OS_ARTI_ISR2_', text:split(., ':')[1])", "Ev" = "concat('OsCat2Isr_', text:split(., ':')[2])", "Args" = "'core, isr'", "Call" = "'core, isr'"!][!//
[!ENDLOOP!][!//

/* AR_CP_OS_APPLICATION */
[!LOOP "text:split('START:Start,RESTART:Restart,ALLOWACCESS:AllowAccess,TERMINATE:Terminate', ',')"!][!//
[!CALL "ArtiMap", "Name" = "concat('OS_ARTI_APPLICATION_', text:split(., ':')[1])", "Ev" = "concat('OsApplication_', text:split(., ':')[2])", "Args" = "'core, app'", "Call" = "'core, app'"!][!//
[!ENDLOOP!][!//

/* AR_CP_OS_SPINLOCK: actual state changes, not the service calls */
[!CALL "ArtiMap", "Name" = "'OS_ARTI_SPINLOCK_LOCKED'", "Ev" = "'OsSpinlock_Locked'", "Args" = "'core, id'", "Call" = "'core, id'"!][!//
[!CALL "ArtiMap", "Name" = "'OS_ARTI_SPINLOCK_RELEASED'", "Ev" = "'OsSpinlock_Released'", "Args" = "'core, id'", "Call" = "'core, id'"!][!//

/* AR_CP_OS_HOOK, OS-level hooks. A hook that is not configured expands to nothing. */
[!LOOP "text:split('ErrorHook,PreTaskHook,PostTaskHook,ProtectionHook,StartupHook,ShutdownHook', ',')"!][!//
[!CALL "ArtiMap", "Name" = "concat('OS_ARTI_HOOK_', text:toupper(.), '_START')", "Ev" = "concat('OsHook_', ., '_Start')", "Args" = "'core, param'", "Call" = "'core, param'"!][!//
[!CALL "ArtiMap", "Name" = "concat('OS_ARTI_HOOK_', text:toupper(.), '_RETURN')", "Ev" = "concat('OsHook_', ., '_Return')", "Args" = "'core, param'", "Call" = "'core, param'"!][!//
[!ENDLOOP!][!//

/* AR_CP_OS_HOOK, application-specific hooks: the event name contains the application name, so the
   application ID (ApplicationType) selects the literal token at run time (design D7). */
[!LOOP "text:split('ErrorHook,StartupHook,ShutdownHook', ',')"!][!//
[!VAR "Hk" = "."!][!//
[!LOOP "text:split('START:Start,RETURN:Return', ',')"!][!//
[!VAR "Ph" = "text:split(., ':')[2]"!][!//
[!IF "$ArtiTraceHook = 'true' and contains($ArtiAppHooks, concat($Hk, '/'))"!][!//
#define OS_ARTI_APPHOOK_[!"text:toupper($Hk)"!]_[!"text:split(., ':')[1]"!](core, app, param) \
    do { \
        switch (app) \
        { \
[!LOOP "text:split($ArtiAppHooks, ',')"!][!IF "text:split(., '/')[1] = $Hk"!][!//
            case [!"text:split(., '/')[3]"!]U: OS_ARTI_EV_OsHook_[!"$Hk"!]_[!"text:split(., '/')[2]"!]_[!"$Ph"!]((core), (param)); break; \
[!ENDIF!][!ENDLOOP!][!//
            default: break; \
        } \
    } while (0)
[!ELSE!][!//
#define OS_ARTI_APPHOOK_[!"text:toupper($Hk)"!]_[!"text:split(., ':')[1]"!](core, app, param)    ((void)0)
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDLOOP!][!//

/* AR_CP_OS_SERVICECALLS: entry and exit of the OS services, from application context only */
[!LOOP "text:split($ArtiServices, ',')"!][!//
[!VAR "Api" = "text:split(., '/')[1]"!][!//
[!CALL "ArtiMap", "Name" = "concat('OS_ARTI_SC_', $Api, '_START')", "Ev" = "concat('OsServiceCall_', $Api, '_Start')", "Args" = "'core, param'", "Call" = "'core, param'"!][!//
[!IF "text:split(., '/')[3] != 'x'"!][!//
[!CALL "ArtiMap", "Name" = "concat('OS_ARTI_SC_', $Api, '_RETURN')", "Ev" = "concat('OsServiceCall_', $Api, '_Return')", "Args" = "'core, param'", "Call" = "'core, param'"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
/* eventParameter of a failed service whose return value is not a StatusType (SWS OS 7.17.4) */
#define OS_ARTI_SC_INVALID              (0xFFFFFFFFUL)

/* Kernel service functions use the helpers below rather than the macros above:
     OS_ARTI_SC_DECL              among the declarations: the core index of the calling core
     OS_ARTI_SC_BEGIN(Api, param) on entry, OS_ARTI_SC_END(Api, param) before returning
   Api is the service name (ActivateTask); it only selects the wrapper macro, the ARTI tokens stay literal. */
#if (OS_ARTI_TRACE_SERVICECALLS == STD_ON)
#define OS_ARTI_SC_DECL                 CoreIdType OsArtiScCore = Os_Inf_GetCoreId();
#define OS_ARTI_SC_BEGIN(Api, param)    OS_ARTI_SC_##Api##_START(OsArtiScCore, (uint32)(param))
#define OS_ARTI_SC_END(Api, param)      OS_ARTI_SC_##Api##_RETURN(OsArtiScCore, (uint32)(param))
#else
#define OS_ARTI_SC_DECL
#define OS_ARTI_SC_BEGIN(Api, param)    ((void)0)
#define OS_ARTI_SC_END(Api, param)      ((void)0)
#endif
[!ENDSELECT!][!//

#endif /* OS_ARTIHOOKS_H_ */
