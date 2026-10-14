/**********************************************************************************************************************
	@Copyright: (C) 1989-2022 Lauterbach GmbH, licensed for use with TRACE32(R) only
**********************************************************************************************************************/

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *         File:  arti_t32_fdx_singlecore.h
 *  Description:  ARTI Trace Method Specific Implementation with TRACE32 FDX feature.
 *********************************************************************************************************************/

#if !defined(ARTI_T32_H)
#define ARTI_T32_H

#include "stdint.h"


/**********************************************************************************************************************
 *  APPLICATION SPECIFIC DEFINES
 *  TO BE ADAPTED FOR EACH APPLICATION!
*********************************************************************************************************************/

/*** Select compressed or uncompressed; if unsure use T32_FDX_TRACE_COMPRESSED ***/
#define T32_FDX_TRACE_COMPRESSED        1   // enable compressed trace
//#define T32_FDX_TRACE_UNCOMPRESSED      1   // enable uncompressed trace

/*** Select DCC based communication, if available; if unsure select none ***/
//#define T32_FDX_DCC                     1   // enable DCC4 based communication
//#define T32_FDX_DCC3                    1   // enable DCC3 based communication

/*** Size of the FDX buffer on target; must be a power of 2 ***/
#define T32_FDX_TRACE_BUFSIZE       512

/*** Initialize Timer for FDX (if necessary) ***/
#ifndef T32_ARTI_TIMERINIT
#define T32_ARTI_TIMERINIT()
/*** Cortex-M0, tick calculation out of SYST_CVR (contact Lauterbach) ***/
//#define T32_ARTI_TIMERINIT() systick32_attach()
#endif

/*** Get a 32bit time stamp ***/
#ifndef T32_ARTI_TIMERGET
/*** PowerPC, STM2 (base=0xF4070000, counter=0x04) ***/
//#define T32_ARTI_TIMERGET() (*(volatile uint32_t*) (0xF4070004uL))
/*** TriCore TC2xx, STM0.TIM0 ***/
//#define T32_ARTI_TIMERGET() (*(volatile uint32_t*) 0xf0000010u)
/*** TriCore TC3xx, STM0.TIM0 ***/
#define T32_ARTI_TIMERGET() (*(volatile uint32_t*) 0xf0001010u)
/*** Cortex-M3/4/7, DWT_CYCCNT ***/
//#define T32_ARTI_TIMERGET() (*(volatile uint32_t*) 0xe0001004u)
/*** Cortex-M0, SYST_CVR, only works with reload value -1! ***/
//#define T32_ARTI_TIMERGET() (1 - (*(volatile uint32_t*) 0xe000e018u))
/*** Cortex-M0, tick calculation out of SYST_CVR (contact Lauterbach) ***/
//#define T32_ARTI_TIMERGET() ((uint32_t)systick64_now_poll())
#endif

/*** Get the current core ID ***/
/* This is singlecore variant. Return core id 0. */
#ifndef T32_ARTI_GETCOREID
#define T32_ARTI_GETCOREID() 0
#endif

/*** See also the application specific definitions in arti_t32_fdx.c! ***/


/**********************************************************************************************************************
 *  ARTI HOOK IMPLEMENTATION
 *********************************************************************************************************************/

#define T32_ARTI_TRACE(arti_context,arti_x_trace,arti_coreid) \
	T32_FdxTraceData (arti_context, T32_FDX_DATAWRITE | T32_LONG, (void*)(&arti_x_trace), arti_x_trace)


/**********************************************************************************************************************
 *  FDX SPECIFIC DEFINES
 *********************************************************************************************************************/

/* cycle parameters */
#define T32_BYTE            0x01
#define T32_WORD            0x02
#define T32_LONG            0x04

#define T32_FDX_PROGFETCH   0x10
#define T32_FDX_DATAREAD    0x20
#define T32_FDX_DATAWRITE   0x30

/**********************************************************************************************************************
 *  FDX SPECIFIC PROTOTYPES
 *********************************************************************************************************************/

/* Initialize the FDX internal data structures. */
void T32_Fdx_TraceInit(void);

/* Check if FDX is enabled */
int T32_FdxTraceEnabled(void);

/* Write a new event to FDX. */
void T32_FdxTraceData(Arti_ContextType context, unsigned char cycletype, void* address, uint32_t data);

/* Initialize the architecture specific timer. */
void T32_TimerInit();

/* Get current timestamp of architecture specific timer. */
uint64_t T32_TimerGet();

#endif /* ARTI_T32_H */

/**********************************************************************************************************************
 *  END OF FILE: arti_t32_logger_singlecore.h
 *********************************************************************************************************************/
