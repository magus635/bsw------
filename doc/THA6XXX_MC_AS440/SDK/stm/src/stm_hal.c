/***************************************************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:  stm_hal.c
 * Author:    30037
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all implementations of requirements of OVC module
 ************************************************************************************************/
/*
* #Violation Summary
*
* #stm_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
* #stm_hal_c_REF_2:MISRAC2012-Dir-1.1;
* Justification:Inline assembly for CPU-specific operations.
*
* #stm_hal_c_REF_3:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
* #stm_hal_c_REF_4:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity.
*
* #stm_hal_c_REF_5:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core, Boolean can only be represents as uint8.
*
* #stm_hal_c_REF_6:MISRAC2012-Rule-19.2;
* Justification:Define a union type to assign a one-time value to a register.
*
* #stm_hal_c_REF_7:MISRAC2012-Rule-2.2;
* Justification:Value used in assembly code.
*
* #stm_hal_c_REF_8:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
* #stm_hal_c_REF_9:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/
/**********************************************************************************************************************
 *                                                     Includes                                                        
 *********************************************************************************************************************/
#include "stm_hal.h"
#include "stm_register.h"
#include "cpuwdt_hal.h"

#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
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
/* #Violation: stm_hal_c_REF_8 */
#define STM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: stm_hal_c_REF_9 */
#include "Stm_MemMap.h"

/* #Violation: stm_hal_c_REF_1 */
boolean Stm_Hal_Start(void)
{
    boolean ret = TRUE;

    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();

    /* Start system counter. */
    /* #Violation: stm_hal_c_REF_3 */
    STM0->CNTCR.B.EN = 1U;

    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();

    /* #Violation: stm_hal_c_REF_3 */
    ret = Stm_Register_ReadBack_Check(ret, (uint32)1U, STM0->CNTCR.B.EN);

    return ret;
}

/* #Violation: stm_hal_c_REF_1 */
boolean Stm_Hal_Stop(void)
{
    boolean ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();

    /* Stop system counter. */
    /* #Violation: stm_hal_c_REF_3 */
    STM0->CNTCR.B.EN = 0U;

    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();

    /* #Violation: stm_hal_c_REF_3 */
    ret = Stm_Register_ReadBack_Check(ret, (uint32)0U, STM0->CNTCR.B.EN);

    return ret;
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
boolean Stm_Hal_SetValue(uint64 value)
{
    boolean ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();

    /* You need stop stm before use this function!!! */
    /* #Violation: stm_hal_c_REF_3 */
    STM0->CNTCVL.U = (uint32)value;  /* set low 32-bits stm value */
    /* #Violation: stm_hal_c_REF_3 */
    STM0->CNTCVU.U = (uint32)(value >> 32U);    /* set upper 32-bits stm value */

    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();

    /* #Violation: stm_hal_c_REF_2 */
    DSB();
    /* #Violation: stm_hal_c_REF_2 */
    ISB();

    return ret;
   
}

/* #Violation: stm_hal_c_REF_1 */
void Stm_Hal_InitPhyEL1Timer(const Stm_Timer_Config *const pTimerConfig)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pTimerConfig is null pointer */
    /* #Violation: stm_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pTimerConfig ));
#endif

    Stm_Std_SetPhyEL1TimerInterrupt(pTimerConfig->intr);
    Stm_Std_SetPhyEL1TimerEvent(pTimerConfig->pEvent_cfg);
}

/* #Violation: stm_hal_c_REF_1 */
void Stm_Hal_InitPhyEL2Timer(const Stm_Timer_Config *const pTimerConfig)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pTimerConfig is null pointer */
    /* #Violation: stm_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pTimerConfig ));
#endif

    Stm_Std_SetPhyEL2TimerInterrupt(pTimerConfig->intr);
    Stm_Std_SetPhyEL2TimerEvent(pTimerConfig->pEvent_cfg);
}

/* #Violation: stm_hal_c_REF_1 */
void Stm_Hal_InitVirtualTimer(const Stm_Timer_Config *const pTimerConfig)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pTimerConfig is null pointer */
    /* #Violation: stm_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pTimerConfig ));
#endif

    Stm_Std_SetVirtualTimerInterrupt(pTimerConfig->intr);
    Stm_Std_SetVirtualTimerEvent(pTimerConfig->pEvent_cfg);
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
uint32 Stm_Hal_Get32BitPhyEL1TimerValue(void)
{
    uint32 result;
    result = 0U;

    /* Get EL1 physical timer */
    /* #Violation: stm_hal_c_REF_2 */
    GET_CP(15, 0, (result), 14, 2, 0);
    return result;
}


/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
uint32 Stm_Hal_Get32BitPhyEL2TimerValue(void)
{
    uint32 result;
    result = 0U;

    /* Get EL2 physical timer */
    /* #Violation: stm_hal_c_REF_2 */
    GET_CP(15, 4, (result), 14, 2, 0);
    return result;
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
uint32 Stm_Hal_Get32BitVirtualTimerValue(void)
{
    uint32 result;
    result = 0U;

    /* Get virtual timer */
    /* #Violation: stm_hal_c_REF_2 */
    GET_CP(15, 0, (result), 14, 3, 0);
    return result;
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
uint64 Stm_Hal_Get64BitPhyEL1TimerCompareValue(void)
{
    uint64 CompareValue;
    CompareValue = 0U;

    /* Get EL1 physical Compare value */
    /* #Violation: stm_hal_c_REF_2 */
    GET_CP64(15, 2, (CompareValue), 14);
    return CompareValue;
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
uint64 Stm_Hal_Get64BitPhyEL2TimerCompareValue(void)
{
    uint64 CompareValue;
    CompareValue = 0U;

    /* Get EL2 physical Compare value */
    /* #Violation: stm_hal_c_REF_2 */
    GET_CP64(15, 6, (CompareValue), 14);
    return CompareValue;
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
uint64 Stm_Hal_Get64BitVirtualTimerCompareValue(void)
{
    uint64 CompareValue;
    CompareValue = 0U;

    /* Get virtual Compare value */
    /* #Violation: stm_hal_c_REF_2 */
    GET_CP64(15, 3, (CompareValue), 14);
    return CompareValue;
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
void Stm_Hal_Set32BitPhyEL1TimerValue(uint32 value)
{
    (void) value;
    /* Set EL1 physical timer */
    /* #Violation: stm_hal_c_REF_2 */
    SET_CP(15, 0, (value), 14, 2, 0);
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
void Stm_Hal_Set32BitPhyEL2TimerValue(uint32 value)
{
    (void) value;
    /* Set EL2 physical timer */
    /* #Violation: stm_hal_c_REF_2 */
    SET_CP(15, 4, (value), 14, 2, 0);
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
void Stm_Hal_Set32BitVirtualTimerValue(uint32 value)
{
    (void) value;
    /* Set virtual timer */
    /* #Violation: stm_hal_c_REF_2 */
    SET_CP(15, 0, (value), 14, 3, 0);
}


/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
void Stm_Hal_Set64BitPhyEL1TimerCompareValue(uint64 value)
{
    (void) value;
    /* Set EL1 physical Compare value */
    /* #Violation: stm_hal_c_REF_2 */
    /* #Violation: stm_hal_c_REF_7 */
    /* #Violation: stm_hal_c_REF_7 */
    SET_CP64(15, 2, (value), 14);
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
void Stm_Hal_Set64BitPhyEL2TimerCompareValue(uint64 value)
{
    (void) value;
    /* Set EL2 physical Compare value */
    /* #Violation: stm_hal_c_REF_2 */
    /* #Violation: stm_hal_c_REF_7 */
    /* #Violation: stm_hal_c_REF_7 */
    SET_CP64(15, 6, (value), 14);
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
void Stm_Hal_Set64BitVirtualTimerCompareValue(uint64 value)
{
    (void) value;
    /* Set virtual Compare value */
    /* #Violation: stm_hal_c_REF_2 */
    /* #Violation: stm_hal_c_REF_7 */
    /* #Violation: stm_hal_c_REF_7 */
    SET_CP64(15, 3, (value), 14);

}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
void Stm_Hal_EnablePhyEL1Timer(void)
{
    /* #Violation: stm_hal_c_REF_6 */
    TIMER_CTL uCNTPCTL;

    /* Enable EL1 physical Timer output signal */
    /* #Violation: stm_hal_c_REF_2 */
    GET_CP(15, 0, (uCNTPCTL.U), 14, 2, 1);
    uCNTPCTL.B.ENABLE = 1U;
    (void)uCNTPCTL.U;
    /* #Violation: stm_hal_c_REF_2 */
    SET_CP(15, 0, (uCNTPCTL.U), 14, 2, 1);
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
void Stm_Hal_EnablePhyEL2Timer(void)
{
    /* #Violation: stm_hal_c_REF_6 */
    TIMER_CTL uCNTHPCTL;

    /* Enable EL2 physical Timer output signal */
    /* #Violation: stm_hal_c_REF_2 */
    GET_CP(15, 4, (uCNTHPCTL.U), 14, 2, 1);
    uCNTHPCTL.B.ENABLE = 1U;
    (void)uCNTHPCTL.U;
    /* #Violation: stm_hal_c_REF_2 */
    SET_CP(15, 4, (uCNTHPCTL.U), 14, 2, 1);
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
void Stm_Hal_EnableVirtualTimer(void)
{
    /* #Violation: stm_hal_c_REF_6 */
    TIMER_CTL uCNTVCTL;

    /* Enable virtual Timer output signal */
    /* #Violation: stm_hal_c_REF_2 */
    GET_CP(15, 0, (uCNTVCTL.U), 14, 3, 1);
    uCNTVCTL.B.ENABLE = 1U;
    (void)uCNTVCTL.U;
    /* #Violation: stm_hal_c_REF_2 */
    SET_CP(15, 0, (uCNTVCTL.U), 14, 3, 1);
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
void Stm_Hal_DisablePhyEL1Timer(void)
{
    /* #Violation: stm_hal_c_REF_6 */
    TIMER_CTL uCNTPCTL;

    /* Disable EL1 physical Timer output signal */
    /* #Violation: stm_hal_c_REF_2 */
    GET_CP(15, 0, (uCNTPCTL.U), 14, 2, 1);
    uCNTPCTL.B.ENABLE = 0U;
    (void)uCNTPCTL.U;
    /* #Violation: stm_hal_c_REF_2 */
    SET_CP(15, 0, (uCNTPCTL.U), 14, 2, 1);
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
void Stm_Hal_DisablePhyEL2Timer(void)
{
    /* #Violation: stm_hal_c_REF_6 */
    TIMER_CTL uCNTHPCTL;

    /* Disable EL2 physical Timer output signal */
    /* #Violation: stm_hal_c_REF_2 */
    GET_CP(15, 4, (uCNTHPCTL.U), 14, 2, 1);
    uCNTHPCTL.B.ENABLE = 0U;
    (void)uCNTHPCTL.U;
    /* #Violation: stm_hal_c_REF_2 */
    SET_CP(15, 4, (uCNTHPCTL.U), 14, 2, 1);
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
void Stm_Hal_DisableVirtualTimer(void)
{
    /* #Violation: stm_hal_c_REF_6 */
    TIMER_CTL uCNTVCTL;

    /* Disable virtual Timer output signal */
    /* #Violation: stm_hal_c_REF_2 */
    GET_CP(15, 0, (uCNTVCTL.U), 14, 3, 1);
    uCNTVCTL.B.ENABLE = 0U;
    (void)uCNTVCTL.U;
    /* #Violation: stm_hal_c_REF_2 */
    SET_CP(15, 0, (uCNTVCTL.U), 14, 3, 1);
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
Stm_TimerStatus Stm_Hal_GetPhyEL1TimerStatus(void)
{
    /* #Violation: stm_hal_c_REF_6 */
    TIMER_CTL uCNTPCTL;
    Stm_TimerStatus status;
    uCNTPCTL.U = 0U;

    /* #Violation: stm_hal_c_REF_2 */
    GET_CP(15, 0, (uCNTPCTL.U), 14, 2, 1);

    /* Judgment timer status */
    if(0x1U == uCNTPCTL.B.ISTATUS)
    {
        status = STM_TIMER_MET;
    }
    else
    {
        status = STM_TIMER_NOT_MET;
    }

    return status;
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
Stm_TimerStatus Stm_Hal_GetPhyEL2TimerStatus(void)
{
    /* #Violation: stm_hal_c_REF_6 */
    TIMER_CTL uCNTHPCTL;
    Stm_TimerStatus status;
    uCNTHPCTL.U = 0U;

    /* #Violation: stm_hal_c_REF_2 */
    GET_CP(15, 4, (uCNTHPCTL.U), 14, 2, 1);

    /* Judgment timer status */
    if(0x1U == uCNTHPCTL.B.ISTATUS)
    {
        status = STM_TIMER_MET;
    }
    else
    {
        status = STM_TIMER_NOT_MET;
    }

    return status;
}

/* #Violation: stm_hal_c_REF_1 */
/* #Violation: stm_hal_c_REF_4 */
Stm_TimerStatus Stm_Hal_GetVitualTimerStatus(void)
{
    /* #Violation: stm_hal_c_REF_6 */
    TIMER_CTL uCNTVCTL;
    Stm_TimerStatus status;
    uCNTVCTL.U = 0U;

    /* #Violation: stm_hal_c_REF_2 */
    GET_CP(15, 0, (uCNTVCTL.U), 14, 3, 1);

    /* Judgment timer status */
    if(0x1U == uCNTVCTL.B.ISTATUS)
    {
        status = STM_TIMER_MET;
    }
    else
    {
        status = STM_TIMER_NOT_MET;
    }

    return status;
}

/* #Violation: stm_hal_c_REF_8 */
#define STM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: stm_hal_c_REF_9 */
#include "Stm_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File                                                     
 *********************************************************************************************************************/

