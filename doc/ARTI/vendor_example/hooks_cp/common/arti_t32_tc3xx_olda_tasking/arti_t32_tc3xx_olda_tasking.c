
/**********************************************************************************************************************
	@Copyright: (C) 1989-2021 Lauterbach GmbH, licensed for use with TRACE32(R) only
**********************************************************************************************************************/

/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  arti_t32_tc3xx_olda_tasking.c
 *  Description:  ARTI Trace Implementation for tracing OS and RTE with TRACE32 on TC3xx over OLDA, Tasking compiler.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * TASKING TRICORE COMPILER (V6.2R1, V6.3R1)
 *********************************************************************************************************************/

/* following fails for dependency check in Vector environment; so we skip it. */
/***
#if !defined(__TASKING__)
#error this file needs Tasking compiler
#endif
***/

/* someone defines "ACCESS" which is used as structure element in IfxGtm_regdef.h.
   Undefine it before including Ifx_reg.h. */
#ifdef ACCESS
#undef ACCESS
#endif
#include "Ifx_reg.h"    /* DOM0_BRCON */

/**********************************************************************************************************************
 *  Infineon TriCore TC3xx OLDA Base Addresses(non_cached): 0xAFE00000
 *********************************************************************************************************************/

#ifndef TRACE32_TASKEVENT_BASE
#define TRACE32_TASKEVENT_BASE __at(0xAFE00000)  /* OLDA Base Address */
#endif

#ifndef TRACE32_RUNNABLE_BASE
#define TRACE32_RUNNABLE_BASE  __at(0xAFE00008)  /* OLDA Base Address + 0x08 */
#endif

#ifndef TRACE32_SYSCALL_BASE
#define TRACE32_SYSCALL_BASE   __at(0xAFE00010) /* OLDA Base Address + 0x10 */
#endif

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* prevent variables from being initialized by C init, */
/* this would write to OLDA before OLDAEN is set.      */
#pragma noclear

volatile unsigned int arti_os_trace  TRACE32_TASKEVENT_BASE;
volatile unsigned int arti_rte_trace TRACE32_RUNNABLE_BASE;
volatile unsigned int arti_sc_trace  TRACE32_SYSCALL_BASE;

#pragma clear

unsigned int arti_enabled = 0;

/**********************************************************************************************************************
 *  ARTI MODULE API IMPLEMENTATION
 *********************************************************************************************************************/

void Arti_Init (void)
{
    /* Activate OLDA memory */
    DOM0_BRCON.B.OLDAEN = 1;

    /* If system is attached to a debugger */
    /* if (CBS_OSTATE.B.OEN == 1) { */
        /* Suspend STMX_Channel to halt the timer while debugging. */
        /* STM0_OCS.U  = 0x12000000; */
        /* STM1_OCS.U  = 0x12000000; */
    /* } */

    /* enable ARTI trace hooks */
    arti_enabled = 1;
}

/**********************************************************************************************************************
 *  END OF FILE: arti_t32_tc3xx_olda_tasking.c
 *********************************************************************************************************************/
