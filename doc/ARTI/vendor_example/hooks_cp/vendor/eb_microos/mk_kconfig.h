/* Mk_kconfig.h - microkernel static configuration header
 *
 * This file is included by anything that needs to see the static microkernel configuration.
 *
 * This header file enables the OS thread state tracing and activates the ARTI trace
 * to be used with Lauterbach's TRACE32.
 *
 * NOTE: USING THIS FILE INVALIDATES THE SAFETY CERTIFICATION.
 *
 * (c) 2021 Lauterbach GmbH
 *
*/
#ifndef MK_KCONFIG_H
#define MK_KCONFIG_H

/* Use external trace tool
*/
#define MK_USE_TRACE	1

#if MK_USE_TRACE

#ifndef MK_ASM_H

#include <private/Mk_thread.h>
#include <private/Mk_task.h>
#include <private/Mk_isr.h>
/*#include <Mk_gen_config.h>      // MK_CFG_NTASKS */
#include <arti.h>


/* only for debugging purposes
extern mk_objecttype_t  arti_typ;       // mk_thread_t.objectType, Mk_public_types.h, see below
extern int              arti_id;        // mk_thread_t.currentObject, e.g. MK_taskCfg[id], if typ == MK_OBJTYPE_TASK
extern const char*      arti_name;      // mk_thread_t.name
extern mk_threadstate_t arti_old;       // mk_thread_t.state, Mk_thread.h, see below
extern mk_threadstate_t arti_new;       // mk_thread_t.state, Mk_thread.h, see below
*/

extern unsigned int arti_enabled;
extern volatile unsigned int t32_runningtask[MK_MAXCORES];


#define MK_TRACE_STATE_THREAD(typ, id, name, old, new) if (arti_enabled) { \
    /*arti_typ=typ, arti_id=id, arti_name=name, arti_old=old, arti_new=new;*/ \
    mk_objectid_t arti_core; \
    mk_kernelcontrol_t *arti_coreVars = MK_GetCoreVars(); \
    arti_core = arti_coreVars->coreIndexLogical; \
    switch (typ) { \
        case MK_OBJTYPE_KERNEL: \
            if (new == MK_THS_RUNNING) { \
                t32_runningtask[arti_core] = 0; \
            } \
        break; \
        case MK_OBJTYPE_TASK: \
            /* arti_core = MK_taskCfg[id].threadCfg.coreIndex; */ \
            switch (old) { \
                case MK_THS_IDLE: \
                    /* if (new == MK_THS_READY) {  EB says, this cannot happen */ \
                        /*ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, arti_core, OsTask_Activate, id);*/ \
                    /* } else if (new == MK_THS_RUNNING) { is this possible? */ \
                        /*ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, arti_core, OsTask_Start, id);*/ \
                        /*t32_runningtask[arti_core] = id + 1;*/ \
                    /* } else */ if (new == MK_THS_NEW) { /* is this correct? */ \
                        if ((MK_taskCfg[id].eventStatus == MK_NULL) || (MK_taskCfg[id].eventStatus->waitingState == MK_NO_WAIT)) { \
                            /* this assumes that waitingState is set *after* thread state, which confirmed by EB */ \
                            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, arti_core, OsTask_Activate, id); \
                        } else { \
                            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, arti_core, OsTask_Release, id); \
                        } \
                    } \
                break; \
                case MK_THS_READY: \
                    if (new == MK_THS_RUNNING) { \
                        ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, arti_core, OsTask_Start, id); \
                        t32_runningtask[arti_core] = id + 1; \
                    } else if (new == MK_THS_IDLE) { /* EB: "external" termination of a task, e.g. by ProtectionHook() */ \
                        ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, arti_core, OsTask_Terminate, id); \
                    } \
                    /* is there any transition from READY to NEW ??? */ \
                break; \
                case MK_THS_RUNNING: \
                    /* EB says, there's no transition from RUNNING to NEW - it always goes through IDLE */ \
                    if (new == MK_THS_IDLE) { \
                        if ((MK_taskCfg[id].eventStatus == MK_NULL) || (MK_taskCfg[id].eventStatus->waitingState == MK_NO_WAIT)) { \
                            /* this assumes that waitingState is set *before* thread state, yes, see MK_SysWaitEvent() */ \
                            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, arti_core, OsTask_Terminate, id); \
                        } else { \
                            ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, arti_core, OsTask_Wait, id); \
                        } \
                    } else if (new == MK_THS_READY) { \
                        ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, arti_core, OsTask_Preempt, id); \
                    /* } else if (new == MK_THS_NEW) { is there a transition from RUNNING to NEW ??? */ \
                        /*ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, arti_core, OsTask_???, id);*/ \
                    } \
                    if (new != MK_THS_RUNNING) { \
                        t32_runningtask[arti_core] = 0; \
                    } \
                break; \
                case MK_THS_NEW: \
                    if (new == MK_THS_IDLE) { /* forced termination */ \
                        ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, arti_core, OsTask_Terminate, id); \
                    /*} else if (new == MK_THS_READY) {  EB says, there's no transition from NEW to READY */ \
                        /*ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, arti_core, OsTask_Activate, id);*/ \
                    } else if (new == MK_THS_RUNNING) { \
                        ARTI_TRACE(NOSUSP, AR_CP_OS_TASK, Os, arti_core, OsTask_Start, id); \
                        t32_runningtask[arti_core] = id + 1; \
                    } \
                break; \
                default: \
                break; \
            } \
        break; \
        case MK_OBJTYPE_ISR: case MK_OBJTYPE_QMOSISR: \
            /*arti_core = MK_isrCfg[id].threadCfg.coreIndex;*/ \
            switch (old) { \
                case MK_THS_READY: \
                    if (new == MK_THS_RUNNING) { \
                        ARTI_TRACE(NOSUSP, AR_CP_OS_CAT2ISR, Os, arti_core, OsCat2Isr_Start, MK_nTasks + id); \
                        t32_runningtask[arti_core] = MK_nTasks + id + 1; /* MK_CFG_NTASKS */ \
                    } \
                break; \
                case MK_THS_RUNNING: \
                    if (new == MK_THS_IDLE) { \
                        ARTI_TRACE(NOSUSP, AR_CP_OS_CAT2ISR, Os, arti_core, OsCat2Isr_Stop, MK_nTasks + id); \
                    } \
                    if (new != MK_THS_RUNNING) { \
                        t32_runningtask[arti_core] = 0; \
                    } \
                break; \
                case MK_THS_NEW: \
                    if (new == MK_THS_RUNNING) { \
                        ARTI_TRACE(NOSUSP, AR_CP_OS_CAT2ISR, Os, arti_core, OsCat2Isr_Start, MK_nTasks + id); \
                        t32_runningtask[arti_core] =  MK_nTasks + id + 1; /* MK_CFG_NTASKS */ \
                    } \
                break; \
                default: \
                break; \
            } \
        break; \
        default: \
        break; \
    } \
  } do {;} while (0) /* while loop to get the following semicolon eaten up */

#endif  // MK_ASM_H

#else   // MK_USE_TRACE

#define MK_TRACE_STATE_THREAD(typ, id, name, old, new)		do { } while(0)

#endif  // MK_USE_TRACE

#endif  // MK_KCONFIG_H
