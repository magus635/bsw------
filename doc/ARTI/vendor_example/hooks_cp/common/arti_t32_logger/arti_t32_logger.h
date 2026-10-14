
/**********************************************************************************************************************
	@Copyright: (C) 1989-2022 Lauterbach GmbH, licensed for use with TRACE32(R) only
**********************************************************************************************************************/

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *         File:  arti_t32_logger.h
 *  Description:  ARTI Trace Method Specific Implementation with TRACE32 LOGGER feature.
 *********************************************************************************************************************/

#if !defined(ARTI_T32_H)
#define ARTI_T32_H

#include "stdint.h"

/**********************************************************************************************************************
 *  APPLICATION SPECIFIC DEFINES
 *  TO BE ADAPTED FOR EACH APPLICATION!
*********************************************************************************************************************/

/*** Size of the LOGGER Ringbuffer; must be a power of 2 ***/
/*** Each buffer entry takes 16 bytes!                   ***/
#define T32_LOGGER_SIZE             1024

/*** Size of the LOGGER Ringbuffer *PER CORE*; must be a power of 2 ***/
#define T32_LOGGER_SIZE_PER_CORE    (T32_LOGGER_SIZE/2)

/*** Number of cores used by application ***/
#define T32_CORE_NUMBER             3

/*** Get the current core ID ***/
/* This maps here to the OS call "GetCoreID" and may be replaced by a more efficient variant. */
#ifndef T32_ARTI_GETCOREID
#define T32_ARTI_GETCOREID() GetCoreID()
#endif

/*** Initialize Timer for LOGGER (if necessary) ***/
#ifndef T32_ARTI_TIMERINIT
#define T32_ARTI_TIMERINIT()
#endif

/*** Get a 32bit time stamp ***/
#ifndef T32_ARTI_TIMERGET
/*** PowerPC, STM2 (base=0xF4070000, counter=0x04) ***/
//#define T32_ARTI_TIMERGET() (*(volatile uint32_t*) (0xF4070004uL))
/*** TriCore TC2xx, STM0.TIM0 ***/
//#define T32_ARTI_TIMERGET() (*(volatile uint32_t*) 0xf0000010u)
/*** TriCore TC3xx, STM0.TIM0 ***/
#define T32_ARTI_TIMERGET() (*(volatile uint32_t*) 0xf0001010u)
/*** iMX8QXP-CM4, TSTMR ***/
//#define T32_ARTI_TIMERGET() ((uint32_t)(*(volatile uint64_t*) 0x414100F0))
#endif

/*** Suspend and resume interrupts ***/
#ifndef T32_ARTI_SUSPENDINT
/*** Standard: use OS service calls. This records additional "EnableAllInterrupts" and
     "DisableAllInterrupts" calls for each RTE trace record! ***/
inline uint32_t T32_ARTI_SUSPENDINT (void) {
    SuspendAllInterrupts();
    return 0;
}
inline void T32_ARTI_RESUMEINT (uint32_t intstate) {
    ResumeAllInterrupts();
}
/*** TriCore: Greenhills, Tasking ***/
/*inline uint32_t T32_ARTI_SUSPENDINT (void) {
    uint32_t intstate = (uint32_t) __mfcr (0xFE2C); __disable(); // ICR
    return intstate;
}
inline void T32_ARTI_RESUMEINT (uint32_t intstate) {
    __mtcr (0xFE2C, intstate);  // ICR
    // __isync(); // __mtcr implements an isync
}*/
/*** TriCore: Diab, HighTec ***/
/*inline uint32_t T32_ARTI_SUSPENDINT (void) {
    uint32_t intstate = (uint32_t) _mfcr (0xFE2C); _disable(); // ICR
    return intstate;
}
inline void T32_ARTI_RESUMEINT (uint32_t intstate) {
    _mtcr (0xFE2C, intstate);  // ICR
    // _isync(); // __mtcr implements an isync
}*/
#endif


/**********************************************************************************************************************
 *  ARTI HOOK IMPLEMENTATION
 *********************************************************************************************************************/

#define T32_ARTI_TRACE(arti_context,arti_x_trace,arti_coreid) \
    T32_LoggerData (arti_context, T32_DATAWRITE | T32_LONG, arti_coreid, (void*)(&arti_x_trace), arti_x_trace)


/**********************************************************************************************************************
 *  LOGGER SPECIFIC DEFINES
 *********************************************************************************************************************/

/* cycle parameters */
#define T32_BYTE            0x01    //!< BYTE access - use together with @ref T32_DATAVALUE
#define T32_WORD            0x02    //!< WORD access - use together with @ref T32_DATAVALUE
#define T32_LONG            0x04    //!< LONG access - use together with @ref T32_DATAVALUE

#define T32_FETCH           0x10    //!< FETCH CYCLE,      mark a single program location in the logger
#define T32_DATAREAD        0x20    //!< DATA READ CYCLE,  mark a single data read on address in the logger
#define T32_DATAWRITE       0x30    //!< DATA WRITE CYCLE, mark a single data write on address in the logger
#define T32_EXECUTE         0xf0    //!< EXECUTE CYCLE,    mark a address range starting from address with number of bytes as executed

/**********************************************************************************************************************
 *  LOGGER SPECIFIC PROTOTYPES
 *********************************************************************************************************************/

/* Initialize the LOGGER internal data structures. */
void T32_LoggerInit(void);

/* Add a new event to the LOGGER. */
void T32_LoggerData(Arti_ContextType context, int cycletype, int core, void* address, uint32_t data);

/* Initialize the architecture specific timer. */
void T32_TimerInit();

/* Get current timestamp of architecture specific timer. */
uint64_t T32_TimerGet();

#endif /* ARTI_T32_H */

/**********************************************************************************************************************
 *  END OF FILE: arti_t32_logger.h
 *********************************************************************************************************************/
