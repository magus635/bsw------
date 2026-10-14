
/**********************************************************************************************************************
	@Copyright: (C) 1989-2021 Lauterbach GmbH, licensed for use with TRACE32(R) only
**********************************************************************************************************************/

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  arti_t32_fdx.c
 *  Description:  ARTI Trace Implementation for tracing OS and RTE with TRACE32 FDX feature.
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  STANDARD INCLUDES
 *********************************************************************************************************************/

#define ARTI_T32_C
#include "stdint.h"
#include "arti_t32_fdx_singlecore.h"
#ifdef ARTI_AUTOSAR
#  include <Os.h>
#endif


/**********************************************************************************************************************
 *  APPLICATION SPECIFIC DEFINES
 *  TO BE ADAPTED FOR EACH APPLICATION!
*********************************************************************************************************************/

#ifndef T32_FDX_COPY
/*** memcpy implementations, if necessary ***/

/*** Elektrobit tresos ***/
//#include <private/Ioc_memcpy.h>
//#define T32_FDX_COPY(t,s,l)   IOC_MemCpy((t),(s),(l))

/*** Vector MICROSAR VStdLib ***/
//#include "vstdlib.h"
//#define T32_FDX_COPY(t,s,l)   VStdLib_MemCpy((t),(s),(l))

/*** Vector MICROSAR C stdlib ***/
// do nothing - use std memcpy

#endif // ifndef T32_FDX_COPY


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

static int fdxIsInitialized = 0;

void Arti_Init (void)
{
    T32_Fdx_TraceInit();
    fdxIsInitialized = 1;
    arti_enabled = 1;
}


/**********************************************************************************************************************
 *  FDX TRACE IMPLEMENTATION
 *********************************************************************************************************************/

static void     T32_Fdx_TraceData2      (unsigned char cycletype, void* address, uint32_t data, uint64_t timestamp);
static uint64_t T32_Fdx_GetTimebase     (void);


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


void T32_FdxTraceData (Arti_ContextType context, unsigned char cycletype, void* address,uint32_t data)
{
    if (!fdxIsInitialized || !T32_FdxTraceEnabled())
        return;

    // block interrupts while dealing with global data
    if (context != NOSUSP)
        SuspendAllInterrupts();

    T32_Fdx_TraceData2(cycletype, address, data, T32_Fdx_GetTimebase());

    if (context != NOSUSP)
        ResumeAllInterrupts();
}


static uint64_t T32_Fdx_GetTimebase(void)
{
    return T32_TimerGet();
}


#ifndef T32_FDX_COPY
# include "string.h"
# define T32_FDX_COPY(t,s,l)   memcpy((t),(s),(l))
#endif

void * T32_Fdx_SendingChannel;
void * T32_Fdx_ReceivingChannel;

void T32_Fdx_Waiting()
{
	/* place a breakpoint here to stop debugger for BufferE/BufferC/BufferS polling */
}


typedef unsigned int  T32_FDX_PARAMETERTYPE;
typedef unsigned char T32_FDX_DATATYPE;

typedef struct {
	volatile T32_FDX_PARAMETERTYPE enable;
	volatile T32_FDX_PARAMETERTYPE size;
	volatile T32_FDX_PARAMETERTYPE hostindex;
	volatile T32_FDX_PARAMETERTYPE targetindex;
	volatile T32_FDX_PARAMETERTYPE stall;
	volatile T32_FDX_PARAMETERTYPE pending;
	volatile T32_FDX_PARAMETERTYPE transferlen;
	volatile T32_FDX_PARAMETERTYPE transferchannel;
} T32_FDX_BUFFER;

#define T32_Fdx_DefineChannel(channel,size)                 struct { T32_FDX_BUFFER header; volatile T32_FDX_DATATYPE data[size]; } channel
#define T32_Fdx_InitChannel(channel)                        ((channel).header.enable = 0, (channel).header.size = 0, (channel).header.hostindex = 0, (channel).header.targetindex = 0, (channel).header.stall = 0, (channel).header.pending = 0, (channel).header.transferchannel = 0x1, (channel).data[0] = 0)
#define T32_Fdx_EnableChannel(channel)                      ((channel).header.size = sizeof((channel).data))
#define T32_Fdx_DisableChannel(channel)                     ((channel).header.size = 0)


/**************************************************************************
	DCC polling functions
**************************************************************************/

#if defined(T32_FDX_DCC)||defined(T32_FDX_DCC3)

#ifdef T32_FDX_DCC

/*imports from t32fdxarm.c*/
extern unsigned long T32_TsMon_SendStatus(void);
extern void          T32_TsMon_SendWord(unsigned long data);
extern unsigned long T32_TsMon_ReceiveStatus(void);
extern unsigned long T32_TsMon_ReceiveWord(void);

# define T32_DCCX_WORDLEN 4
# define T32_DCCX_SENDSTATUS(_TRANSFERCHANNEL_)                T32_TsMon_SendStatus()
# define T32_DCCX_SENDWORD(_TRANSFERCHANNEL_, _SENDWORD_)      T32_TsMon_SendWord(_SENDWORD_)
# define T32_DCCX_RECEIVESTATUS(_TRANSFERCHANNEL_)             T32_TsMon_ReceiveStatus()
# define T32_DCCX_RECEIVEWORD(_TRANSFERCHANNEL_, _RETWORDPTR_) (*(_RETWORDPTR_) = T32_TsMon_ReceiveWord())

#else

/*imports from t32dcc3.c*/
extern unsigned long T32DCC3_SendStatus(int nChannel);
extern void          T32DCC3_SendWord(int nChannel, unsigned int nLength, unsigned int nData3);
extern unsigned long T32DCC3_ReceiveStatus(int DCCChannel);
extern void          T32DCC3_ReceiveWord(int nChannel, unsigned long *pLength, unsigned long *pData3);

# define T32_DCCX_WORDLEN 3
# define T32_DCCX_SENDSTATUS(_TRANSFERCHANNEL_)                T32DCC3_SendStatus(_TRANSFERCHANNEL_)
# define T32_DCCX_SENDWORD(_TRANSFERCHANNEL_, _SENDWORD_)      T32DCC3_SendWord(_TRANSFERCHANNEL_, T32_DCCX_WORDLEN ,_SENDWORD_)
# define T32_DCCX_RECEIVESTATUS(TRANSFERCHANNEL)               T32DCC3_ReceiveStatus(TRANSFERCHANNEL)
# define T32_DCCX_RECEIVEWORD(_TRANSFERCHANNEL_, _RETWORDPTR_) T32DCC3_ReceiveWord(_TRANSFERCHANNEL_, (unsigned long*) 0, _RETWORDPTR_)

#endif

static void T32_Fdx_SendDCC(void * channel)
{
	int             len, headerlen;
	unsigned long   data = 0;
	unsigned int    wordlen;
	volatile T32_FDX_DATATYPE *fdxptr;
	T32_FDX_BUFFER *fdxchannel;

	fdxchannel = channel;
	if (fdxchannel == NULL) {
		return;
	}

	if (T32_DCCX_SENDSTATUS(fdxchannel->transferchannel)) {
		return;
	}

	if (fdxchannel->hostindex == fdxchannel->targetindex) {
		T32_Fdx_SendingChannel = NULL;
		return;
	}
	fdxptr = ((T32_FDX_DATATYPE *)(fdxchannel + 1)) + fdxchannel->hostindex;

	if (!fdxchannel->pending) {

		if (!fdxptr[0])
			return;

		if (*fdxptr == (T32_FDX_DATATYPE)-1) {
			fdxchannel->hostindex = 0;

			fdxptr = ((T32_FDX_DATATYPE *)(fdxchannel + 1)) + fdxchannel->hostindex;

			if (!fdxptr[0])
				return;
		}
		headerlen = 1;
		if (*fdxptr == (T32_FDX_DATATYPE)-2) {
			len = fdxptr[1] | (fdxptr[2] << 8);
			headerlen = 3;
		}
		else if (*fdxptr == (T32_FDX_DATATYPE)-3) {
			len = 0;
		}
		else {
			len = *fdxptr;
		}

		fdxchannel->pending = headerlen + len;
	}
	if (fdxchannel->pending > T32_DCCX_WORDLEN)
		wordlen = T32_DCCX_WORDLEN;
	else
		wordlen = fdxchannel->pending;
	switch (wordlen) {
	case 1:
		data = (unsigned long)fdxptr[0];
		break;
	case 2:
		data = ((unsigned long)fdxptr[0]) | (((unsigned long)fdxptr[1]) << 8);
		break;
	case 3:
		data = ((unsigned long)fdxptr[0]) | (((unsigned long)fdxptr[1]) << 8) | (((unsigned long)fdxptr[2]) << 16);
		break;
	case 4:
		data = ((unsigned long)fdxptr[0]) | (((unsigned long)fdxptr[1]) << 8) | (((unsigned long)fdxptr[2]) << 16) | (((unsigned long)fdxptr[3]) << 24);
		break;
	}

	T32_DCCX_SENDWORD(fdxchannel->transferchannel, data);

	fdxchannel->hostindex += wordlen;
	fdxchannel->pending -= wordlen;
	T32_Fdx_SendingChannel = channel;
}

#define T32_FDX_SENDPOLL(channel)    T32_Fdx_SendDCC(channel)
#define T32_FDX_POLL()               { if (T32_Fdx_SendingChannel) T32_Fdx_SendDCC(T32_Fdx_SendingChannel); }

#endif /* T32_FDX_DCC || T32_FDX_DCC3 */


/**************************************************************************
	generic polling macros (polling is not used)
**************************************************************************/

#ifndef T32_FDX_SENDPOLL
# define T32_FDX_SENDPOLL(channel)
#endif

#ifndef T32_FDX_POLL
# define T32_FDX_POLL()
#endif



/**************************************************************************
	Send packet to ringbuffer or check state of ringbuffer
**************************************************************************/

static int T32_Fdx_SendToBuffer(void * channel, void * buf, int size)
{
	int                        hsize;
	T32_FDX_PARAMETERTYPE      targetindex;
	T32_FDX_BUFFER            *fdxchannel;
	volatile T32_FDX_DATATYPE *fdxptr, *fdxptr2;

	fdxchannel = channel;

	if ((T32_FDX_PARAMETERTYPE)size > fdxchannel->size - 4 || size <= 0)
		return -1;

	hsize = 1;
	if ((unsigned int)size > (unsigned int)((T32_FDX_DATATYPE)-5))
		hsize = 3;
	targetindex = fdxchannel->targetindex;
	if (targetindex + hsize + size + 2 > fdxchannel->size) {	/* wrap around ? */
		if (fdxchannel->hostindex > targetindex || fdxchannel->hostindex <= 1)
			goto stall;
		fdxptr2 = (T32_FDX_DATATYPE *)(fdxchannel + 1);
		*fdxptr2 = (T32_FDX_DATATYPE)0;
		fdxptr = ((T32_FDX_DATATYPE *)(fdxchannel + 1)) + targetindex;
		*fdxptr = (T32_FDX_DATATYPE)-1;
		targetindex = 0;
		fdxchannel->targetindex = targetindex;
	}
	if (fdxchannel->hostindex > targetindex && targetindex + hsize + size + 2 > fdxchannel->hostindex)
		goto stall;

	if (buf) {			/* just polling state ? */

		fdxptr = ((T32_FDX_DATATYPE *)(fdxchannel + 1)) + targetindex;
		T32_FDX_COPY((void *)(fdxptr + hsize), buf, size);	/* copy payload data */

		fdxptr2 = fdxptr + hsize + size;
		*fdxptr2 = 0;		/* mark next packet as not ready */

		if (hsize == 3) {	/* large packet size ? */
			fdxptr[2] = (T32_FDX_DATATYPE)(size >> 8);
			fdxptr[1] = (T32_FDX_DATATYPE)size;
			fdxptr[0] = (T32_FDX_DATATYPE)-2;
		}
		else {
			fdxptr[0] = (T32_FDX_DATATYPE)size;
		}

		fdxchannel->targetindex = targetindex + hsize + size;
		fdxchannel->stall = 0;
	}
	return size;

stall:
	if (buf && !fdxchannel->stall) {
		fdxptr = ((T32_FDX_DATATYPE *)(fdxchannel + 1)) + targetindex;
		fdxptr2 = fdxptr + 1;
		*fdxptr2 = (T32_FDX_DATATYPE)0;
		*fdxptr = (T32_FDX_DATATYPE)-3;
		fdxchannel->targetindex = targetindex + 1;
		fdxchannel->stall = 1;
	}
	return 0;
}


/**************************************************************************
	Send packet to ringbuffer, wait till packet can be saved
**************************************************************************/

int T32_Fdx_Send(void * channel, void * buf, int size)
{
	int             result;

	while ((result = T32_Fdx_SendToBuffer(channel, buf, size)) == 0) {
		T32_Fdx_Waiting();
		T32_FDX_POLL();
	}

	T32_FDX_SENDPOLL(channel);

	return result;
}

#if defined(T32_FDX_TRACE_COMPRESSED) || defined(T32_FDX_TRACE_UNCOMPRESSED)

/**************************************************************************
	FDX Tracing functions
**************************************************************************/

T32_Fdx_DefineChannel(FdxTraceSendBuffer, T32_FDX_TRACE_BUFSIZE);

void T32_Fdx_TraceData(unsigned char cycletype, void* address, unsigned long data)
{
	unsigned long long timestamp = T32_Fdx_GetTimebase();
	T32_Fdx_TraceData2(cycletype, address, data, timestamp);
}

int T32_FdxTraceEnabled(void)
{
    return FdxTraceSendBuffer.header.enable;
}


#ifdef T32_FDX_TRACE_COMPRESSED

static int      T32_Fdx_LastCycle;
static uint64_t T32_Fdx_LastTimestamp;
static uint32_t T32_Fdx_LastAddress;
static uint32_t T32_Fdx_LastData;

void T32_Fdx_TraceInit(void)
{
	T32_Fdx_LastCycle = 0;
	T32_Fdx_LastTimestamp = 0;
	T32_Fdx_LastAddress = 0;
	T32_Fdx_LastData = 0;

	T32_Fdx_InitChannel(FdxTraceSendBuffer);
	T32_Fdx_EnableChannel(FdxTraceSendBuffer);
}

static void T32_Fdx_TraceData2(unsigned char cycletype, void* address, uint32_t data, uint64_t timestamp)
{
	int             len;
	int             ctrlidx;
	unsigned long   addr;
	unsigned char   ctrl;
	unsigned char   buf[16+5];

	len = 0;
	ctrlidx = 0;

	ctrl = 0x00;
	len += 1; //space for ctrl
	if (cycletype != T32_Fdx_LastCycle) {
		buf[len] = cycletype;
		len++;
		ctrl |= 0x80;
		T32_Fdx_LastCycle = cycletype;
	}

	if (timestamp != T32_Fdx_LastTimestamp) {
		if ((timestamp & 0xffffffffffffff00ull) == (T32_Fdx_LastTimestamp & 0xffffffffffffff00ull)) {
			buf[len] = timestamp & 0xff;
			len += 1;
			ctrl |= 0x20;
		}
		else if ((timestamp & 0xffffffffffff0000ull) == (T32_Fdx_LastTimestamp & 0xffffffffffff0000ull)) {
			buf[len] = timestamp & 0xff;
			buf[len + 1] = (timestamp >> 8) & 0xff;
			len += 2;
			ctrl |= 0x40;
		}
		else {
			buf[len] = timestamp & 0xff;
			buf[len + 1] = (timestamp >> 8) & 0xff;
			buf[len + 2] = (timestamp >> 16) & 0xff;
			buf[len + 3] = (timestamp >> 24) & 0xff;
			buf[len + 4] = (timestamp >> 32) & 0xff;
			buf[len + 5] = (timestamp >> 40) & 0xff;;
			len += 6;
			ctrl |= 0x60;
		}
		T32_Fdx_LastTimestamp = timestamp;
	}

	addr = (unsigned long)address;
	if (addr != T32_Fdx_LastAddress) {
		if ((addr & 0xffffff00) == (T32_Fdx_LastAddress & 0xffffff00)) {
			switch ((int)(addr - T32_Fdx_LastAddress)) {
			case 0:
				break;
			case 1:
				ctrl |= 0x04;
				break;
			case 2:
				ctrl |= 0x08;
				break;
			case 4:
				ctrl |= 0x0c;
				break;
			case 8:
				ctrl |= 0x10;
				break;
			default:
				buf[len] = addr & 0xff;
				len += 1;
				ctrl |= 0x14;
			}
		}
		else if ((addr & 0xffff0000) == (T32_Fdx_LastAddress & 0xffff0000)) {
			buf[len] = addr & 0xff;
			buf[len + 1] = (addr >> 8) & 0xff;
			len += 2;
			ctrl |= 0x18;
		}
		else {
			buf[len] = addr & 0xff;
			buf[len + 1] = (addr >> 8) & 0xff;
			buf[len + 2] = (addr >> 16) & 0xff;
			buf[len + 3] = (addr >> 24) & 0xff;
			len += 4;
			ctrl |= 0x1c;
		}

		T32_Fdx_LastAddress = addr;
	}

	if (data != T32_Fdx_LastData) {
		if ((data & 0xffffff00) == (T32_Fdx_LastData & 0xffffff00)) {
			buf[len] = data & 0xff;
			len += 1;
			ctrl |= 0x01;
		}
		else if ((data & 0xffff0000) == (T32_Fdx_LastData & 0xffff0000)) {
			buf[len] = data & 0xff;
			buf[len + 1] = (data >> 8) & 0xff;
			len += 2;
			ctrl |= 0x02;
		}
		else {
			buf[len] = data & 0xff;
			buf[len + 1] = (data >> 8) & 0xff;
			buf[len + 2] = (data >> 16) & 0xff;
			buf[len + 3] = (data >> 24) & 0xff;
			len += 4;
			ctrl |= 0x03;
		}

		T32_Fdx_LastData = data;
	}

	buf[ctrlidx] = ctrl;
	T32_Fdx_Send(&FdxTraceSendBuffer, buf, len);
}

#endif /* T32_FDX_TRACE_COMPRESSED */

#ifdef T32_FDX_TRACE_UNCOMPRESSED

void T32_Fdx_TraceInit(void)
{
	T32_Fdx_InitChannel(FdxTraceSendBuffer);
	T32_Fdx_EnableChannel(FdxTraceSendBuffer);
}

void T32_Fdx_TraceData2(unsigned char cycletype, void* address, uint32_t data, unsigned long long timestamp)
{
	struct {
		unsigned char   align;
		unsigned char   cycletype;
		unsigned short  tsupper;
		unsigned long   tslower;
		unsigned long   address;
		unsigned long   data;
		unsigned long   core;
	} traceframe;

	int  len = sizeof(traceframe);

	len--;

	traceframe.cycletype = cycletype;
	traceframe.tsupper = (timestamp >> 32) & 0xFFFF;
	traceframe.tslower = timestamp & 0xFFFFFFFF;
	traceframe.address = (unsigned long)address;
	traceframe.data = data;
	traceframe.core = 0;

	T32_FDX_SEND(&FdxTraceSendBuffer, &traceframe.cycletype, len);

	T32_FDX_SENDPOLL(&FdxTraceSendBuffer);
}

#endif /* T32_FDX_TRACE_UNCOMPRESSED */

#endif /* T32_FDX_TRACE_COMPRESSED || T32_FDX_TRACE_UNCOMPRESSED */


/**********************************************************************************************************************
 *  END OF FILE: arti_t32_fdx_singlecore.c
 *********************************************************************************************************************/

