/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:  stm_register.h
 * Author:    30037
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all definitions of STM module registers
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #stm_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification:Using unions for bit-field access to registers.
*
*/
#ifndef  STM_REGISTER_H_
#define  STM_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes                                                        
 *********************************************************************************************************************/
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions                                                
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        STM Register Bit-Fields Definitions                                         
 *********************************************************************************************************************/
/* Counter Control register */
typedef struct
{
    ureg32 EN:1;          /* [0:0] Counter enable control. */
    ureg32 HDBG:1;        /* [1:1] Halt on debug. */
    ureg32 reserved_2:30; /* [31:2] Reserved. */
} STM_CNTCR_Bits;

/* Counter status register */
typedef struct
{
    ureg32 reserved_0:1;  /* [0:0] Reserved. */
    ureg32 DBGH:1;        /* [1:1] Debug halted. */
    ureg32 reserved_2:30; /* [31:3] Reserved. */
} STM_CNTSR_Bits;

/* Low 32-bits counter value register */
typedef struct
{
    ureg32 CNTCVL:32; /* [31:0] Low 32-bits counter value. */
} STM_CNTCVL_Bits;

/* Upper 32-bits counter value register */
typedef struct
{
    ureg32 CNTCVU:32; /* [31:0] Upper 32-bits counter value. */
} STM_CNTCVU_Bits;

/* Timer Control register */
typedef struct
{
    ureg32 ENABLE:1;        /* [0:0] Timer enable control. */
    ureg32 IMASK:1;         /* [1:1] Interrupt mask. */
    ureg32 ISTATUS:1;       /* [2:2] Timer status. */
    ureg32 reserved_3:29;   /* [31:3] Reserved. */
} TIMER_CTL_Bits;

/* Counter Control register */
typedef struct
{
    ureg32 PL1PCTEN:1;          /* [0:0] Traps Non-secure EL0 and EL1 accesses to the physical
                                         counter register to Hyp mode. */
    ureg32 PL1PCEN:1;           /* [1:1] Traps Non-secure EL0 and EL1 accesses to the physical
                                         timer registers to Hyp mode. */
    ureg32 EVNTEN:1;            /* [2:2] Enables the generation of an event stream from CNTPCT as seen from EL2. */
    ureg32 EVNTDIR:1;           /* [3:3] Controls which transition of the CNTPCT trigger bit, as seen from EL2 and
                                         defined by EVNTI,generates an event when the event stream is enabled. */
    ureg32 EVNTI:4;             /* [7:4] Selects which bit of CNTPCT, as seen from EL2, is the trigger for the
                                         event stream generated from that counter when that stream is enabled. */
    ureg32 reserved_8:24;       /* [31:8] Reserved. */
} EVENT_CTL_Bits;

/**********************************************************************************************************************
 *                                              STM Register Definitions                                              
 *********************************************************************************************************************/
/* Counter Control register */
typedef union
/* #Violation: stm_register_h_REF_1 */
{
    ureg32 U;         /* Unsigned access */
    STM_CNTCR_Bits B; /* Bit-Field access */
} STM_CNTCR;

/* Counter status register */
typedef union
/* #Violation: stm_register_h_REF_1 */
{
    ureg32 U;         /* Unsigned access */
    STM_CNTSR_Bits B; /* Bit-Field access */
} STM_CNTSR;

/* Low 32-bits counter value register */
typedef union
/* #Violation: stm_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    STM_CNTCVL_Bits B; /* Bit-Field access */
} STM_CNTCVL;

/* Upper 32-bits counter value register */
typedef union
/* #Violation: stm_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    STM_CNTCVU_Bits B; /* Bit-Field access */
} STM_CNTCVU;

/* Timer Control register */
typedef union
/* #Violation: stm_register_h_REF_1 */
{
    ureg32 U;         /* Unsigned access */
    TIMER_CTL_Bits B; /* Bit-Field access */
} TIMER_CTL;

/* Event Control register */
typedef union
/* #Violation: stm_register_h_REF_1 */
{
    ureg32 U;         /* Unsigned access */
    EVENT_CTL_Bits B; /* Bit-Field access */
} EVENT_CTL;

/**********************************************************************************************************************
 *                                        STM Register Configuration Structure                                        
 *********************************************************************************************************************/
/* STM module object register group */
typedef volatile struct
{
    STM_CNTCR CNTCR;    /* 0x0 Counter Control Register  */
    STM_CNTSR CNTSR;    /* 0x4 Counter Status  Register  */
    STM_CNTCVL CNTCVL;  /* 0x8 Current Counter Value Lower Register */
    STM_CNTCVU CNTCVU;  /* 0xC Current Counter Value Upper Register */
} STM_MODULE;

#endif /* STM_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File                                                     
 *********************************************************************************************************************/
