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
          uint32_t t32_coreid = (uint32_t) portGET_CORE_ID(); \
          t32_current = pxCurrentTCBs[t32_coreid]->uxTCBNumber; \
          ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, t32_coreid, OsTask_Start, t32_current) \
        }

#define traceTASK_SWITCHED_OUT() { \
          uint32_t t32_coreid = (uint32_t) portGET_CORE_ID(); \
          if (pxCurrentTCBs[t32_coreid]->xStateListItem.pxContainer == pxReadyTasksLists) \
            ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, t32_coreid, OsTask_Preempt, pxCurrentTCBs[t32_coreid]->uxTCBNumber) \
        }

#define traceTASK_CREATE(pxNewTCB) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, (uint32_t) portGET_CORE_ID(), OsTask_Activate, pxNewTCB->uxTCBNumber)

#define traceTASK_DELETE(pxTaskToDelete) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, (uint32_t) portGET_CORE_ID(), OsTask_Terminate, pxTaskToDelete->uxTCBNumber)

#define traceTASK_DELAY() { \
          uint32_t t32_coreid = (uint32_t) portGET_CORE_ID(); \
          ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, t32_coreid, OsTask_Wait, pxCurrentTCBs[t32_coreid]->uxTCBNumber) \
        }

#define traceTASK_DELAY_UNTIL(x) { \
          uint32_t t32_coreid = (uint32_t) portGET_CORE_ID(); \
          ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, t32_coreid, OsTask_Wait, pxCurrentTCBs[t32_coreid]->uxTCBNumber) \
        }

#define traceTASK_SUSPEND(pxTaskToSuspend) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, (uint32_t) portGET_CORE_ID(), OsTask_Wait, pxTaskToSuspend->uxTCBNumber)

#define traceTASK_RESUME(pxTaskToResume) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, (uint32_t) portGET_CORE_ID(), OsTask_Release, pxTaskToResume->uxTCBNumber)

#define traceBLOCKING_ON_QUEUE_RECEIVE(pxQueue) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, (uint32_t) portGET_CORE_ID(), OsTask_Wait, t32_current)

#define traceBLOCKING_ON_QUEUE_RECEIVE(pxQueue) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, (uint32_t) portGET_CORE_ID(), OsTask_Wait, t32_current)

#define traceBLOCKING_ON_QUEUE_SEND(pxQueue) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, (uint32_t) portGET_CORE_ID(), OsTask_Wait, t32_current)

#define traceBLOCKING_ON_STREAM_BUFFER_SEND(xStreamBuffer) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, (uint32_t) portGET_CORE_ID(), OsTask_Wait, t32_current)

#define traceBLOCKING_ON_STREAM_BUFFER_RECEIVE(xStreamBuffer) \
        ARTI_TRACE(NOSUSP, AR_CP_OSARTI_TASK, Os, (uint32_t) portGET_CORE_ID(), OsTask_Wait, t32_current)

#endif /* DO_NOT_INCLUDE_ARTI */

