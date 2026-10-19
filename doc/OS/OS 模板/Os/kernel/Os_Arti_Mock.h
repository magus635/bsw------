/****************************************************************************************************
*   FileName              : Os_Arti_Mock.h
*
*   BSW Module            : Os
*
*   brief                 : Strict ARTI hook mock for verifying the kernel instrumentation (openspec
*                           add-arti-hook-tracing, design D9). Selected by Os_ArtiHooks.h when
*                           OS_ARTI_USE_MOCK is defined; NOT production code.
*
*   - ARTI_TRACE pastes all four literal tokens (_contextName, _className, _instanceName, _eventName),
*     and only the combinations described by the ArtiHook containers of Os_Arti.arxml are defined:
*     a wrong token, a wrong parameter order or a hook missing from the description does not compile.
*   - Every event is recorded in a ring buffer per OS core index (the instance parameter), single
*     producer per core. Dump Os_ArtiMockLog / Os_ArtiMockCount and check them with
*     tools/arti/check_event_stream.py, which reads the event table at the end of this file.
*   - Define OS_ARTI_MOCK_TIMESTAMP() (e.g. a read of the global system counter) to order events across
*     cores; the default is 0. OS_ARTI_MOCK_DEPTH sets the records per core (default 512).
****************************************************************************************************/
#ifndef OS_ARTI_MOCK_H_
#define OS_ARTI_MOCK_H_
[!//
[!NOCODE!][!//
[!VAR "ArtiEventsLoaded" = "'false'"!][!//
[!INCLUDE "Os_ArtiEvents.m"!][!//
[!ENDNOCODE!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!IF "$ArtiEventsLoaded = 'true'"!][!CALL "Os_ArtiEventList"!][!ELSE!][!//
#error "Os_Arti_Mock.h: Os_ArtiEvents.m was not found next to the Os templates"
[!VAR "ArtiEvents" = "''"!][!//
[!ENDIF!][!//
[!/* number of buffers = highest OS core index + 1 (core indices as in Os_Arti.arxml, A1) */!][!//
[!VAR "MockCores" = "1"!][!//
[!LOOP "node:order(./OsCoreIdMappingConfig/*,'@index')"!][!//
[!VAR "CoreNo" = "num:i(node:value(./OsPhysicalCoreId))"!][!IF "node:value(./OsCoreId) != ''"!][!VAR "CoreNo" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!ENDIF!][!//
[!IF "$CoreNo + 1 > $MockCores"!][!VAR "MockCores" = "num:i($CoreNo + 1)"!][!ENDIF!][!//
[!ENDLOOP!][!//

#define OS_ARTI_MOCK_CORES              ([!"num:i($MockCores)"!]UL)
#ifndef OS_ARTI_MOCK_DEPTH
#define OS_ARTI_MOCK_DEPTH              (512UL)
#endif
#ifndef OS_ARTI_MOCK_TIMESTAMP
#define OS_ARTI_MOCK_TIMESTAMP()        (0UL)
#endif

typedef struct
{
    unsigned long Seq;          /* per-core sequence number, never wraps in practice */
    unsigned long Time;         /* OS_ARTI_MOCK_TIMESTAMP() */
    unsigned long Event;        /* event ID, see the table at the end of this file */
    unsigned long Instance;     /* instanceParameter: OS core index */
    unsigned long Param;        /* eventParameter */
} Os_ArtiMockRecordType;

extern volatile Os_ArtiMockRecordType Os_ArtiMockLog[OS_ARTI_MOCK_CORES][OS_ARTI_MOCK_DEPTH];
extern volatile unsigned long Os_ArtiMockCount[OS_ARTI_MOCK_CORES];
extern volatile unsigned long Os_ArtiMockBadCore;     /* events whose instance parameter is out of range */

#define OS_ARTI_MOCK_RECORD(ev, ip, ep) \
    do { \
        unsigned long ArtiMockCore_ = (unsigned long)(ip); \
        if (ArtiMockCore_ < OS_ARTI_MOCK_CORES) \
        { \
            unsigned long ArtiMockN_ = Os_ArtiMockCount[ArtiMockCore_]; \
            volatile Os_ArtiMockRecordType *ArtiMockR_ = &Os_ArtiMockLog[ArtiMockCore_][ArtiMockN_ % OS_ARTI_MOCK_DEPTH]; \
            ArtiMockR_->Seq = ArtiMockN_; \
            ArtiMockR_->Time = OS_ARTI_MOCK_TIMESTAMP(); \
            ArtiMockR_->Event = (ev); \
            ArtiMockR_->Instance = ArtiMockCore_; \
            ArtiMockR_->Param = (unsigned long)(ep); \
            Os_ArtiMockCount[ArtiMockCore_] = ArtiMockN_ + 1UL; \
        } \
        else \
        { \
            Os_ArtiMockBadCore++; \
        } \
    } while (0)

/* SWS_Arti_00018 parameter order; every literal token takes part in the macro name */
#define ARTI_TRACE(_contextName, _className, _instanceName, instanceParameter, _eventName, eventParameter) \
    OS_ARTI_MOCK_##_contextName##_##_className##_##_instanceName##_##_eventName((instanceParameter), (eventParameter))

[!VAR "EvId" = "0"!][!//
[!LOOP "text:split($ArtiEvents, ';')"!][!//
[!VAR "EvId" = "$EvId + 1"!][!//
#define OS_ARTI_MOCK_[!"text:split(., ':')[1]"!]_[!"text:split(., ':')[2]"!]_[!"$ArtiOsName"!]_[!"text:split(., ':')[3]"!](ip, ep) OS_ARTI_MOCK_RECORD([!"num:i($EvId)"!]UL, (ip), (ep))
[!ENDLOOP!][!//

/* Event table read by tools/arti/check_event_stream.py: ARTI_MOCK_EVENT <id> <context> <class> <event>
   (state model: [!IF "$ArtiEnhanced = 'true'"!]ENHANCED[!ELSE!]STANDARD[!ENDIF!])
[!VAR "EvId" = "0"!][!//
[!LOOP "text:split($ArtiEvents, ';')"!][!//
[!VAR "EvId" = "$EvId + 1"!][!//
   ARTI_MOCK_EVENT [!"num:i($EvId)"!] [!"text:split(., ':')[1]"!] [!"text:split(., ':')[2]"!] [!"text:split(., ':')[3]"!]
[!ENDLOOP!][!//
*/
[!ENDSELECT!][!//

#endif /* OS_ARTI_MOCK_H_ */
