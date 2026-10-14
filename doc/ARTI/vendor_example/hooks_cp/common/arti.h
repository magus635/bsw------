/***************************************************************************************
    @Copyright: (C) 1989-2023 Lauterbach GmbH, licensed for use with TRACE32(R) only
***************************************************************************************/

/***************************************************************************************
 *  FILE DESCRIPTION
 *         File:  arti.h
 *  Description:  Standard ARTI include file
 **************************************************************************************/

#if !defined(ARTI_H)
#define ARTI_H


/***************************************************************************************
 * SELECT wether you use and AUTOSAR or ASAM tracing
 **************************************************************************************/

/* AUTOSAR Run-Time Interface */
#define ARTI_AUTOSAR

/* ASAM Run-Time Interface */
//#define ARTI_ASAM


/***************************************************************************************
 * SELECT the correct trace and compiler for your environment
 **************************************************************************************/

/* TRACE32 pure data trace */
#define ARTI_T32_DATA_TRACE

/* TRACE32 trace via LOGGER */
//#define ARTI_T32_LOGGER

/* TRACE32 trace via LOGGER, single core (no SMP) */
//#define ARTI_T32_LOGGER_SINGLECORE

/* TRACE32 trace via FDX */
//#define ARTI_T32_FDX

/* TRACE32 trace via FDX, single core (no SMP) */
//#define ARTI_T32_FDX_SINGLECORE

/* TRACE32 on TC2xx over LMU, Hightec compiler */
//#define ARTI_T32_TC2xx_LMU_HIGHTEC

/* TRACE32 on TC2xx over LMU, Tasking compiler */
//#define ARTI_T32_TC2xx_LMU_TASKING

/* TRACE32 on TC3xx over OLDA, GHS compiler */
//#define ARTI_T32_TC3xx_OLDA_GHS

/* TRACE32 on TC3xx over OLDA, Hightec compiler */
//#define ARTI_T32_TC3xx_OLDA_HIGHTEC

/* TRACE32 on TC3xx over OLDA, Tasking compiler */
//#define ARTI_T32_TC3xx_OLDA_TASKING


/***************************************************************************************
 * SELECT which ARTI class to trace
 **************************************************************************************/

/* trace task state changes */
#define ARTI_ENABLE_OS_TASK

/* trace category 2 ISRs */
#define ARTI_ENABLE_OS_CAT2ISR

/* trace category 1 ISRs */
//#define ARTI_ENABLE_OS_CAT1ISR

/* trace spinlocks */
//#define ARTI_ENABLE_OS_SPINLOCK

/* trace OS application state changes */
//#define ARTI_ENABLE_OS_APPLICATION

/* trace OS hooks */
//#define ARTI_ENABLE_OS_HOOK

/* trace OS service calls */
//#define ARTI_ENABLE_OS_SERVICECALLS

/* trace runnables */
#define ARTI_ENABLE_RTE_RUNNABLE


/***************************************************************************************
 * Sanity checks
 **************************************************************************************/

#if !defined(ARTI_AUTOSAR)&&!defined(ARTI_ASAM)
#error "Select AUTOSAR or ASAM in arti.h!"
#endif

#if defined(ARTI_AUTOSAR)&& defined(ARTI_ASAM)
#error "Select AUTOSAR *or* ASAM in arti.h!"
#endif


/***************************************************************************************
 * Standard includes
 **************************************************************************************/

#ifdef ARTI_AUTOSAR
#include "Std_Types.h"
#endif


/***************************************************************************************
 * Static configuration parameters
 **************************************************************************************/

#ifdef ARTI_AUTOSAR
/*
 * Please make sure that the Det is enabled itself if you turn ARTI_DEV_ERROR_DETECT on.
 */
#define ARTI_DEV_ERROR_DETECT    (STD_ON)   // STD_ON or STD_OFF
#endif


/***************************************************************************************
 * Include the ARTI implementation
 **************************************************************************************/

#include "arti_common.h"


/***************************************************************************************
 * TRACE32 helpers
 **************************************************************************************/

#ifdef ARTI_ASAM
extern unsigned int t32_current;
#endif


#endif /* ARTI_H */

/***************************************************************************************
 *  END OF FILE: arti.h
 **************************************************************************************/
