
/**********************************************************************************************************************
	@Copyright: (C) 1989-2021 Lauterbach GmbH, licensed for use with TRACE32(R) only
**********************************************************************************************************************/

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  arti_t32_logger.c
 *  Description:  ARTI Trace Implementation for tracing OS and RTE with TRACE32 LOGGER feature.
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  STANDARD INCLUDES
 *********************************************************************************************************************/

#include "stdint.h"
#include "arti_t32_logger.h"
#ifdef ARTI_AUTOSAR
#  include <Os.h>
#endif


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

volatile unsigned int arti_os_trace;
volatile unsigned int arti_sc_trace;
volatile unsigned int arti_rte_trace;

unsigned int arti_enabled = 0;


/**********************************************************************************************************************
 *  ARTI MODULE API IMPLEMENTATION
 *********************************************************************************************************************/

void Arti_Init (void)
{
    T32_LoggerInit();
    arti_enabled = 1;
}


/**********************************************************************************************************************
 *  LOGGER IMPLEMENTATION
 *********************************************************************************************************************/

void T32_TimerInit()
{
   T32_ARTI_TIMERINIT();
}


static uint32_t timer_overrun = 0;
static uint32_t lasttime = 0;

uint64_t T32_TimerGet()
{
    // we need a *free running* 32bit timer that overruns at 0xFFFFFFFF

    uint32_t newtime = T32_ARTI_TIMERGET();

    if (newtime < lasttime)
        timer_overrun++;
    lasttime = newtime;
    return (((uint64_t) timer_overrun) << 32) | ((uint64_t) newtime);
}

// iflags
#define T32_LOGGER_ACTIVATED    0x001
#define T32_LOGGER_STACKMODE    0x100
// oflags
#define T32_LOGGER_OVERFLOW     0x001
#define T32_LOGGER_TRIGGERED    0x100
#define T32_LOGGER_BREAK        0x200


typedef struct
{
    uint32_t tshigh;        //!< high part of timestamp and cycle info
    uint32_t tslow;         //!< low part of timestamp
    uint32_t address;
    uint32_t data;
}
T32_loggerData_t;

typedef struct
{
    T32_loggerData_t * ptr;     //!< pointer to trace data
    uint32_t size;              //!< size of trace buffer
    volatile uint32_t index;    //!< current write pointer
    uint32_t tindex;            //!< index of trigger record
    volatile uint32_t iflags;   //!< incoming flags, Bit 0: ARM, Bit 8: Stack Mode
    uint32_t oflags;            //!< outgoing flags, Bit 0: Overflow, Bit 8: Trigger, Bit 9: Break
    uint32_t reserved1;
    uint32_t reserved2;
    T32_loggerData_t buffer[T32_LOGGER_SIZE];
}
T32_LoggerStruct_t;

typedef struct
{
    T32_loggerData_t * ptr;     //!< pointer to trace data
    uint32_t size;              //!< size of trace buffer
    volatile uint32_t index;    //!< current write pointer
    uint32_t tindex;            //!< index of trigger record
    volatile uint32_t iflags;   //!< incoming flags, Bit 0: ARM, Bit 8: Stack Mode
    uint32_t oflags;            //!< outgoing flags, Bit 0: Overflow, Bit 8: Trigger, Bit 9: Break
    uint32_t reserved1;
    uint32_t reserved2;
    T32_loggerData_t buffer[T32_LOGGER_SIZE_PER_CORE];
}
T32_LoggerStruct_PerCore_t;

static T32_LoggerStruct_t T32_LoggerStruct;
    // Please take care that this variable needs core global visibility!
    //    __attribute__((asection (".T32_LOGGER_STRUCT_GLOBAL","a=4", "f=wz")));

static T32_LoggerStruct_PerCore_t T32_LoggerStruct_PerCore[T32_CORE_NUMBER];
    // Please take care that this variable needs core global visibility!
    //    __attribute__((asection (".T32_LOGGER_STRUCT_PER_CORE","a=4", "f=wz")));

static int readIndex[T32_CORE_NUMBER];


void T32_LoggerInit(void)
{
    int i, j;

    T32_LoggerStruct.ptr    = T32_LoggerStruct.buffer;
    T32_LoggerStruct.index  = 0;
    T32_LoggerStruct.size   = T32_LOGGER_SIZE;

    for (i = 0; i < T32_CORE_NUMBER; i++) {
        T32_LoggerStruct_PerCore[i].ptr     = T32_LoggerStruct_PerCore[i].buffer;
        T32_LoggerStruct_PerCore[i].index   = 0;
        for (j = 0; j < T32_LOGGER_SIZE_PER_CORE; j++)
            T32_LoggerStruct_PerCore[i].buffer[j].tshigh = 0;   // mark as not used
        readIndex[i] = 0;
    }
    // to start recording from startup:
    T32_LoggerStruct.iflags = T32_LOGGER_ACTIVATED;

    T32_TimerInit();
}


static int checkIndex (int core)
{
    if (core == -1) {
        if (T32_LoggerStruct.index >= T32_LOGGER_SIZE) {
            if (T32_LoggerStruct.iflags & T32_LOGGER_STACKMODE) {
                return -1;
            }
            T32_LoggerStruct.oflags |= T32_LOGGER_OVERFLOW;
            T32_LoggerStruct.index = 0;
            }
        return T32_LoggerStruct.index;
    }
    if (T32_LoggerStruct_PerCore[core].index >= T32_LOGGER_SIZE_PER_CORE) {
        if (T32_LoggerStruct.iflags & T32_LOGGER_STACKMODE) {
            return -1;
        }
        T32_LoggerStruct.oflags |= T32_LOGGER_OVERFLOW;
        T32_LoggerStruct_PerCore[core].index = 0;
    }
    return T32_LoggerStruct_PerCore[core].index;
}


static int findEarliest (void)
{
    int i, core;

    core = -1;

    for (i = 0; i < T32_CORE_NUMBER; i++) {
        // check first entry of each core
        if (T32_LoggerStruct_PerCore[i].ptr[readIndex[i]].tshigh) {
            // entry for this core available
            if (core == -1) {
                // first core with an entry
                core = i;
            }
            else {
                uint32_t high_i     = T32_LoggerStruct_PerCore[i].ptr[readIndex[i]].tshigh & 0xffff;
                uint32_t low_i      = T32_LoggerStruct_PerCore[i].ptr[readIndex[i]].tslow;
                uint32_t high_core  = T32_LoggerStruct_PerCore[core].ptr[readIndex[core]].tshigh & 0xffff;
                uint32_t low_core   = T32_LoggerStruct_PerCore[core].ptr[readIndex[core]].tslow;
                // check if entry is younger
                if (high_i < high_core) {
                    // high part is younger
                    core = i;
                }
                else if (high_i == high_core) {
                    // high part is equal
                    if (low_i < low_core) {
                        // low_part is younger
                        core = i;
                    }
                }
            }
        }
    }

    return core;
}


void T32_LoggerData(Arti_ContextType context, int cycletype, int core, void* address, uint32_t data)
{
    int         nIndex, gIndex;
    uint32_t    interruptState;
    uint64_t    nTimer;

    if (core >= T32_CORE_NUMBER)
        return;

    // copy over iflags from global
    T32_LoggerStruct_PerCore[core].iflags = T32_LoggerStruct.iflags;

    if (!(T32_LoggerStruct.iflags & T32_LOGGER_ACTIVATED)) {
        return;
    }

    // block interrupts while dealing with time based indices
    if (context != NOSUSP)
        interruptState = T32_ARTI_SUSPENDINT();

    nIndex = checkIndex(core);
    if (nIndex == -1) {
        if (context != NOSUSP)
            T32_ARTI_RESUMEINT(interruptState);
        return;
    }
    gIndex = checkIndex(-1);
    if (gIndex == -1) {
        if (context != NOSUSP)
            T32_ARTI_RESUMEINT(interruptState);
        return;
    }

    if (core == 0) {
        // primary core copies entries of core specific traces

        int copycore;

        for (copycore = findEarliest(); copycore != -1; copycore = findEarliest())
        {
            T32_LoggerStruct.ptr[gIndex] = T32_LoggerStruct_PerCore[copycore].ptr[readIndex[copycore]];
            T32_LoggerStruct_PerCore[copycore].ptr[readIndex[copycore]].tshigh = 0; // free entry
            T32_LoggerStruct.index++;
            gIndex = checkIndex(-1);
            if (gIndex == -1)
                break;
            readIndex[copycore] = readIndex[copycore] + 1;
            if (readIndex[copycore] >= T32_LOGGER_SIZE_PER_CORE)
                readIndex[copycore] = 0;
        }
    }
    else {
        // check secondary cores if primary core already fetched data
        while (T32_LoggerStruct_PerCore[core].ptr[nIndex].tshigh) {}    // spinlock
    }

    nIndex = T32_LoggerStruct_PerCore[core].index;
    nTimer = T32_TimerGet();
    // The "tshigh" field marks the usage of this slot. So this field should be the last one written!
    T32_LoggerStruct_PerCore[core].ptr[nIndex].tslow  = (uint32_t)(nTimer & 0xffffffffll);
    T32_LoggerStruct_PerCore[core].ptr[nIndex].tshigh = (((uint32_t)cycletype) << 24) | (((uint32_t)core) << 16) | ((uint32_t)((nTimer>>32)&0xffffll));
    T32_LoggerStruct_PerCore[core].ptr[nIndex].address= (uint32_t) address;
    T32_LoggerStruct_PerCore[core].ptr[nIndex].data   = data;
    T32_LoggerStruct_PerCore[core].index = nIndex + 1;

    if (context != NOSUSP)
        T32_ARTI_RESUMEINT(interruptState);
    return;
}


/**********************************************************************************************************************
 *  END OF FILE: arti_t32_logger.c
 *********************************************************************************************************************/
