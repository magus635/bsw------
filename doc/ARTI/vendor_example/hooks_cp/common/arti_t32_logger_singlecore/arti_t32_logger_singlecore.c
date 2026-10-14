
/**********************************************************************************************************************
	@Copyright: (C) 1989-2021 Lauterbach GmbH, licensed for use with TRACE32(R) only
**********************************************************************************************************************/

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  arti_t32_logger_singlecore.c
 *  Description:  ARTI Trace Implementation for tracing OS and RTE with TRACE32 LOGGER feature.
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  STANDARD INCLUDES
 *********************************************************************************************************************/

#include "stdint.h"
#include "arti_t32_logger_singlecore.h"
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

static T32_LoggerStruct_t T32_LoggerStruct;
static int readIndex;


void T32_LoggerInit(void)
{
    int i;

    T32_LoggerStruct.ptr    = T32_LoggerStruct.buffer;
    T32_LoggerStruct.index  = 0;
    T32_LoggerStruct.size   = T32_LOGGER_SIZE;

    for (i = 0; i < T32_LOGGER_SIZE; i++)
        T32_LoggerStruct.buffer[i].tshigh = 0;  // mark as not used
    readIndex = 0;

    // to start recording from startup:
    T32_LoggerStruct.iflags = T32_LOGGER_ACTIVATED;

    T32_TimerInit();
}


static int checkIndex (void)
{
    if (T32_LoggerStruct.index >= T32_LOGGER_SIZE) {
        if (T32_LoggerStruct.iflags & T32_LOGGER_STACKMODE) {
            return -1;
        }
        T32_LoggerStruct.oflags |= T32_LOGGER_OVERFLOW;
        T32_LoggerStruct.index = 0;
    }
    return T32_LoggerStruct.index;
}


void T32_LoggerData(Arti_ContextType context, int cycletype, void* address, uint32_t data)
{
    int         nIndex;
    uint32_t    interruptState;
    uint64_t    nTimer;

    if (!(T32_LoggerStruct.iflags & T32_LOGGER_ACTIVATED)) {
        return;
    }

    // block interrupts while dealing with time based indices
    if (context != NOSUSP)
        interruptState = T32_ARTI_SUSPENDINT();

    nIndex = checkIndex();
    if (nIndex == -1) {
        if (context != NOSUSP)
            T32_ARTI_RESUMEINT(interruptState);
        return;
    }

    nIndex = T32_LoggerStruct.index;
    nTimer = T32_TimerGet();
    T32_LoggerStruct.ptr[nIndex].tslow  = (uint32_t)(nTimer & 0xffffffffll);
    T32_LoggerStruct.ptr[nIndex].tshigh = (((uint32_t)cycletype) << 24) | ((uint32_t)((nTimer>>32)&0xffffll));
    T32_LoggerStruct.ptr[nIndex].address= (uint32_t) address;
    T32_LoggerStruct.ptr[nIndex].data   = data;
    T32_LoggerStruct.index = nIndex + 1;

    if (context != NOSUSP)
        T32_ARTI_RESUMEINT(interruptState);
    return;
}


/**********************************************************************************************************************
 *  END OF FILE: arti_t32_logger_singlecore.c
 *********************************************************************************************************************/
