/**********************************************************************************************************
 * Arti.h - EXAMPLE of the ARTI trace macro (SWS ARTI 7.2, SWS_Arti_00018) and of the Arti API.
 * To be replaced by the file of the trace tool; places a vendor has to adapt are marked "VENDOR".
 **********************************************************************************************************/
#ifndef ARTI_H_
#define ARTI_H_

#include "Std_Types.h"                  /* uint32, Std_VersionInfoType */

/* VENDOR: identification of the module (SWS_Arti_91005); use the real vendor and module IDs and version */
#define ARTI_VENDOR_ID          (0xFFFFU)
#define ARTI_MODULE_ID          (0xFFFFU)
#define ARTI_SW_MAJOR_VERSION   (1U)
#define ARTI_SW_MINOR_VERSION   (0U)
#define ARTI_SW_PATCH_VERSION   (0U)

/* Arti.c */
extern void Arti_Init(void);                                            /* SWS_Arti_91004 */
extern void Arti_GetVersionInfo(Std_VersionInfoType *VersionInfoPtr);   /* SWS_Arti_91005 */

/* SWS_Arti_00018.  _contextName, _className, _instanceName and _eventName are literal tokens, they must not be
 * macro-expanded before they are pasted.  The kernel calls
 *     ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, OsOS, <core>, OsTask_Activate, <task id>)
 * which expands to ARTI_TRACE_AR_CP_OSARTI_TASK_OsTask_Activate((<core>), (<task id>)), defined in Os_Arti.h.
 * This example does not need the context and the instance name.
 * VENDOR: if the tool needs them (e.g. to tell several OS instances apart, or to tell service calls from
 * the other contexts), paste them into the name as well: ARTI_TRACE_##_contextName##_##_className##... and
 * define Os_Arti.h accordingly. */
#define ARTI_TRACE(_contextName, _className, _instanceName, instanceParameter, _eventName, eventParameter) \
    ARTI_TRACE_##_className##_##_eventName((instanceParameter), (eventParameter))

#endif /* ARTI_H_ */
