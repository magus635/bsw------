/**********************************************************************************************************************
 * Arti.h - baseline of the ARTI trace macro and the ARTI API (AUTOSAR CP SWS ARTI 7.2, SWS_Arti_00018).
 *
 * One of the three files every trace tool vendor starts from (Arti.h, Os_Arti.h, Arti.c).  It is complete and
 * works as it is: an ARTI event is one write of a 32 bit word to a global variable, which a trace tool can
 * capture (data trace of the debug interface, or any software buffer that is filled by that write).
 * Places a vendor may adapt are marked "VENDOR".
 *
 * Layout of the traced words (the same as the one of the Lauterbach ARTI implementation, so that the TRACE32
 * ARTI decoding applies; the numbers are in Os_Arti.h):
 *
 *   arti_os_trace   [0:7]   core index (instanceParameter)
 *                   [8:14]  event number
 *                   [15]    valid bit, always 1 (tells a write of the OS from the C start-up initialisation)
 *                   [16:31] object ID: task, ISR2, spinlock, application; hooks: the event parameter
 *   arti_sc_trace   [0:7]   core index
 *                   [8:14]  service call number
 *                   [15]    set on return from the service call
 *                   [16:31] 0 (the service call parameter is not recorded)
 **********************************************************************************************************************/
#ifndef ARTI_H_
#define ARTI_H_

#include "Std_Types.h"                  /* uint32, Std_VersionInfoType, STD_ON, STD_OFF */

/*********************************************************************************************************************
 * Configuration.  The kernel has its own switches per event class (OsVendorArtiTrace<Class> of the OS
 * configuration, OS_ARTI_TRACE_<CLASS> in Os_ArtiCfg.h) and emits only the events that are switched on.  These
 * switches only make the macros of a class empty, they never add events.
 ********************************************************************************************************************/
#ifndef ARTI_ENABLE_OS_TASK
#define ARTI_ENABLE_OS_TASK             (STD_ON)    /* AR_CP_OS_TASK, AR_CP_OSARTI_TASK */
#endif
#ifndef ARTI_ENABLE_OS_CAT2ISR
#define ARTI_ENABLE_OS_CAT2ISR          (STD_ON)    /* AR_CP_OS_CAT2ISR, AR_CP_OSARTI_CAT2ISR */
#endif
#ifndef ARTI_ENABLE_OS_CAT1ISR
#define ARTI_ENABLE_OS_CAT1ISR          (STD_ON)    /* AR_CP_ARTI_CAT1ISR, AR_CP_ARTIEXT_CAT1ISR: placed by the user */
#endif
#ifndef ARTI_ENABLE_OS_SPINLOCK
#define ARTI_ENABLE_OS_SPINLOCK         (STD_ON)    /* AR_CP_OS_SPINLOCK */
#endif
#ifndef ARTI_ENABLE_OS_APPLICATION
#define ARTI_ENABLE_OS_APPLICATION      (STD_ON)    /* AR_CP_OS_APPLICATION */
#endif
#ifndef ARTI_ENABLE_OS_HOOK
#define ARTI_ENABLE_OS_HOOK             (STD_ON)    /* AR_CP_OS_HOOK */
#endif
#ifndef ARTI_ENABLE_OS_SERVICECALLS
#define ARTI_ENABLE_OS_SERVICECALLS     (STD_ON)    /* AR_CP_OS_SERVICECALLS */
#endif

/* STD_ON: Arti.c reports ARTI_E_PARAM_POINTER to the Det (SWS_Arti_00010); needs Det.h and Det_ReportError() */
#ifndef ARTI_DEV_ERROR_DETECT
#define ARTI_DEV_ERROR_DETECT           (STD_OFF)
#endif

/* VENDOR: identification of the module (SWS_Arti_91005); use the real vendor ID, module ID and version */
#define ARTI_VENDOR_ID                  (0xFFFFU)
#define ARTI_MODULE_ID                  (0xFFFFU)
#define ARTI_SW_MAJOR_VERSION           (1U)
#define ARTI_SW_MINOR_VERSION           (0U)
#define ARTI_SW_PATCH_VERSION           (0U)

#define ARTI_E_INIT_FAILED              (0x01U)
#define ARTI_E_PARAM_POINTER            (0x02U)

/*********************************************************************************************************************
 * API (Arti.c)
 ********************************************************************************************************************/
extern void Arti_Init(void);                                            /* SWS_Arti_91004 */
extern void Arti_GetVersionInfo(Std_VersionInfoType *VersionInfoPtr);   /* SWS_Arti_91005 */

/*********************************************************************************************************************
 * Trace variables (Arti.c).  The trace tool watches these addresses.
 * VENDOR: place them in the memory the tool needs (for example with the project's MemMap).
 ********************************************************************************************************************/
extern volatile uint32 arti_os_trace;
extern volatile uint32 arti_sc_trace;

/* Contexts of the event macros (SWS_Arti_00018): the macro argument is the literal token */
typedef enum
{
    NOSUSP = 0,                         /* interrupts masked up to OS_ISR_TP_DISABLE_LEVEL */
    SPRVSR = 1,                         /* supervisor context: service calls */
    USER   = 2
} Arti_ContextType;

/* VENDOR: called after every write of a trace variable, with the context token, the written variable and the core
 * index.  Empty for a data trace, where the write itself is the event.  A software trace (buffer in memory,
 * transfer to the host) puts its code here. */
#ifndef ARTI_EMIT
#define ARTI_EMIT(contextName, traceVariable, coreIndex)    ((void)0)
#endif

/* The word of an OS event, layout see the head of this file */
#define ARTI_VALID_OS_SIGNALING         (0x80U)
#define ARTI_OS_WORD(objectId, eventNumber, coreIndex) \
    ((((uint32)(objectId) & 0xFFFFU) << 16) | ((uint32)ARTI_VALID_OS_SIGNALING << 8) | \
     (((uint32)(eventNumber) & 0x7FU) << 8) | ((uint32)(coreIndex) & 0xFFU))

/*********************************************************************************************************************
 * ARTI_TRACE (SWS_Arti_00018).  _contextName, _className, _instanceName and _eventName are literal tokens and
 * must not be macro-expanded before they are pasted.  The kernel calls, for example,
 *     ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, OsOS, <core>, OsTask_Activate, <task id>)
 * which becomes ARTI_TRACE_AR_CP_OSARTI_TASK(NOSUSP, OsTask_Activate, <core>, <task id>), a macro of Os_Arti.h.
 * The event name is an enumerator of Os_Arti.h that holds the event number.
 * VENDOR: if the tool needs the instance name (several OS instances in one image), paste it into the name too.
 ********************************************************************************************************************/
#define ARTI_TRACE(_contextName, _className, _instanceName, instanceParameter, _eventName, eventParameter) \
    ARTI_TRACE_##_className((_contextName), (_eventName), (instanceParameter), (eventParameter))

#endif /* ARTI_H_ */
