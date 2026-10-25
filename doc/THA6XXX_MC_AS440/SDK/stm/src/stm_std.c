/***************************************************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:  stm_std.c
 * Author:    30037
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all implementations of requirements of OVC module
 ************************************************************************************************/
/*
* #Violation Summary
*
* #stm_std_c_REF_1:MISRAC2012-Dir-1.1;
* Justification:Inline assembly for CPU-specific operations.
*
* #stm_std_c_REF_2:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity.
*
* #stm_std_c_REF_3:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core, Boolean can only be represents as uint8.
*
* #stm_std_c_REF_4:MISRAC2012-Rule-19.2;
* Justification:Define a union type to assign a one-time value to a register.
*
* #stm_std_c_REF_5:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
* #stm_std_c_REF_6:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*
*/
/**********************************************************************************************************************
 *                                                     Includes                                                        
 *********************************************************************************************************************/
#include "stm_std.h"
#include "stm_register.h"

/**********************************************************************************************************************
 *                                              Private Macro Definitions                                              
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Declarations                                            
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions                                             
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions                                             
 *********************************************************************************************************************/
/* #Violation: stm_std_c_REF_5 */
#define STM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: stm_std_c_REF_6 */
#include "Stm_MemMap.h"

/* #Violation: stm_std_c_REF_2 */
void Stm_Std_SetPhyEL1TimerInterrupt(boolean intr)
{
    /* #Violation: stm_std_c_REF_4 */
    TIMER_CTL uCNTPCTL;

    /* #Violation: stm_std_c_REF_1 */
    GET_CP(15, 0, (uCNTPCTL.U), 14, 2, 1);

    /* Set timer interrupt in bits 1 */
    uCNTPCTL.B.IMASK = intr;
    (void)uCNTPCTL.U;
    /* #Violation: stm_std_c_REF_1 */
    SET_CP(15, 0, (uCNTPCTL.U), 14, 2, 1);
}

/* #Violation: stm_std_c_REF_2 */
void Stm_Std_SetPhyEL2TimerInterrupt(boolean intr)
{
    /* #Violation: stm_std_c_REF_4 */
    TIMER_CTL uCNTHPCTL;

    /* #Violation: stm_std_c_REF_1 */
    GET_CP(15, 4, (uCNTHPCTL.U), 14, 2, 1);

    /* Set timer interrupt in bits 1 */
    uCNTHPCTL.B.IMASK = intr;
    (void)uCNTHPCTL.U;
    /* #Violation: stm_std_c_REF_1 */
    SET_CP(15, 4, (uCNTHPCTL.U), 14, 2, 1);
}

/* #Violation: stm_std_c_REF_2 */
void Stm_Std_SetVirtualTimerInterrupt(boolean intr)
{
    /* #Violation: stm_std_c_REF_4 */
    TIMER_CTL uCNTVCTL;

    /* #Violation: stm_std_c_REF_1 */
    GET_CP(15, 0, (uCNTVCTL.U), 14, 3, 1);

    /* Set timer interrupt in bits 1 */
    uCNTVCTL.B.IMASK = intr;
    (void)uCNTVCTL.U;
    /* #Violation: stm_std_c_REF_1 */
    SET_CP(15, 0, (uCNTVCTL.U), 14, 3, 1);
}

/* #Violation: stm_std_c_REF_2 */
void Stm_Std_SetPhyEL1TimerEvent(const Stm_Event_Config *const pEvent)
{
    /* #Violation: stm_std_c_REF_4 */
    EVENT_CTL event; 

    /* #Violation: stm_std_c_REF_1 */
    GET_CP(15, 0, (event.U), 14, 1, 0);

    /* Set event stream */
    event.B.EVNTI = pEvent->generate_bit;
    event.B.EVNTDIR = pEvent->transition;
    event.B.EVNTEN = pEvent->enable;
    (void)event.U;
    /* #Violation: stm_std_c_REF_1 */
    SET_CP(15, 0, (event.U), 14, 1, 0);
}

/* #Violation: stm_std_c_REF_2 */
void Stm_Std_SetPhyEL2TimerEvent(const Stm_Event_Config *const pEvent)
{
    /* #Violation: stm_std_c_REF_4 */
    EVENT_CTL event; 

    /* #Violation: stm_std_c_REF_1 */
    GET_CP(15, 4, (event.U), 14, 1, 0);

    /* Set event stream */
    event.B.EVNTI = pEvent->generate_bit;
    event.B.EVNTDIR = pEvent->transition;
    event.B.EVNTEN = pEvent->enable;
    (void)event.U;
    /* #Violation: stm_std_c_REF_1 */
    SET_CP(15, 4, (event.U), 14, 1, 0);
}

/* #Violation: stm_std_c_REF_2 */
void Stm_Std_SetVirtualTimerEvent(const Stm_Event_Config *const pEvent)
{
    /* #Violation: stm_std_c_REF_4 */
    EVENT_CTL event; 

    /* #Violation: stm_std_c_REF_1 */
    GET_CP(15, 0, (event.U), 14, 1, 0);

    /* Set event stream */
    event.B.EVNTI = pEvent->generate_bit;
    event.B.EVNTDIR = pEvent->transition;
    event.B.EVNTEN = pEvent->enable;
    (void)event.U;
    /* #Violation: stm_std_c_REF_1 */
    SET_CP(15, 0, (event.U), 14, 1, 0);
}
/* #Violation: stm_std_c_REF_5 */
#define STM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: stm_std_c_REF_6 */
#include "Stm_MemMap.h"
