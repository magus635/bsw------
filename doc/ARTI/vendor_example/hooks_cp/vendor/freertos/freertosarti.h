/******************************************************************************
 * Trace configuration for ARTI trace
 *****************************************************************************/

#if __IASMARM__==1
# define DO_NOT_INCLUDE_ARTI
#endif /* __IASMARM__==1 */

#ifndef DO_NOT_INCLUDE_ARTI

#include "arti.h"

// trace points see FreeRTOS/Source/include/FreeRTOS.h

#define traceTASK_SWITCHED_IN() { \
          t32_current = pxCurrentTCB->uxTCBNumber; \
          ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Start, pxCurrentTCB->uxTCBNumber) \
        }

#define traceTASK_SWITCHED_OUT() { \
          if (pxCurrentTCB->xStateListItem.pxContainer == pxReadyTasksLists) \
            ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Preempt, pxCurrentTCB->uxTCBNumber) \
        }

#define traceTASK_CREATE(pxNewTCB) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Activate, pxNewTCB->uxTCBNumber)

#define traceTASK_DELETE(pxTaskToDelete) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Terminate, pxTaskToDelete->uxTCBNumber)

#define traceTASK_DELAY() \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Wait, pxCurrentTCB->uxTCBNumber)

#define traceTASK_DELAY_UNTIL(x) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Wait, pxCurrentTCB->uxTCBNumber)

#define traceTASK_SUSPEND(pxTaskToSuspend) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Wait, pxTaskToSuspend->uxTCBNumber)

#define traceTASK_RESUME(pxTaskToResume) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Release, pxTaskToResume->uxTCBNumber)

#define traceBLOCKING_ON_QUEUE_RECEIVE(pxQueue) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Wait, t32_current)

#define traceBLOCKING_ON_QUEUE_RECEIVE(pxQueue) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Wait, t32_current)

#define traceBLOCKING_ON_QUEUE_SEND(pxQueue) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Wait, t32_current)

#define traceBLOCKING_ON_STREAM_BUFFER_SEND(xStreamBuffer) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Wait, t32_current)

#define traceBLOCKING_ON_STREAM_BUFFER_RECEIVE(xStreamBuffer) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, 0, OsTask_Wait, t32_current)

#endif /* DO_NOT_INCLUDE_ARTI */

