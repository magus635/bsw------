/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_tim_std.h
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 *  Description: This file contains all the data type definitions and function declarations for all the internal
 *                 functions of the TIM module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
*#gtm_tim_std_h_REF_1:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #gtm_tim_std_h_REF_2:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_tim_std_h_REF_3:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
#ifndef GTM_TIM_STD_H_
#define GTM_TIM_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "gtm_register.h"
#include "gtm_cmu_std.h"
#include "gtm.h"
#include "compilertypes.h"
#include "Platform_Types.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* Timeout for edge count reset */
#define GTM_TIM_RESET_EDGE_COUNT_TIMEOUT (5U) 
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Selection for CNTS */
typedef enum
{
    GTM_TIM_CNTSSEL_CNTREG = 0U,    /* Use CNT register as input */
    GTM_TIM_CNTSSEL_TBUTS0            /* Use TBU_TS0 as input */
} Gtm_Tim_CntsSel;

/* Selection for GPRx */
typedef enum
{
    GTM_TIM_GPRSEL_TBUTS0 = 0U,        /* Use TBU_TS0 as input */
    GTM_TIM_GPRSEL_TBUTS1,            /* Use TBU_TS1 as input */
    GTM_TIM_GPRSEL_TBUTS2,            /* Use TBU_TS2 as input */
    GTM_TIM_GPRSEL_CNTS                /* Use CNTS as input */
} Gtm_Tim_GprSel;

/* Filter mode */
typedef enum
{
    GTM_TIM_FLTMODE_IMMEDIATE = 0U,      /* Immediate edge propagation mode */
    GTM_TIM_FLTMODE_DEGLITCHTIMEUPDOWN,  /* Individual deglitch time mode (Up Down) */
    GTM_TIM_FLTMODE_DEGLITCHTIMEHOLD,    /* Individual deglitch time mode (Hold) */
    GTM_TIM_FLTMODE_NONE                 /* No filter */
} Gtm_Tim_FltMode;

/* Selection for Tim Input */
typedef enum
{
    GTM_TIM_INPUT_CURRENTCHANNEL = 0U,    /* Current channel as Tim input */
    GTM_TIM_INPUT_ADJACENTCHANNEL,        /* Adjacent channel as Tim input */
    GTM_TIM_INPUT_AUX                   /* Use the input from the aux */
} Gtm_Tim_Input;

/* TIM Irq Type */
typedef enum
{
    GTM_TIM_IRQTYPE_NEWVAL        = 0U,    /* New measurement value detected by SMU of channel */
    GTM_TIM_IRQTYPE_ECNTOVERFLOW,          /* ECNT counter overflow of channel */
    GTM_TIM_IRQTYPE_CNTOVERFLOW,          /* CNT counter overflow of channel */
    GTM_TIM_IRQTYPE_GPROVERFLOW,          /* GPR0 and GPR1 data overflow */
    GTM_TIM_IRQTYPE_TIMEOUTDETECT,      /* Time out reached for input signal of channel */
    GTM_TIM_IRQTYPE_GLITCHDETECT,          /* A glitch was detected by the TIM filter of channel */
    GTM_TIM_IRQTYPE_ALL              = 63U    /* All irq of channel */
} Gtm_Tim_IrqType;

/* TIM Mode */
typedef enum
{
    GTM_TIM_MODE_PWMMEASUREMENT = 0U,      /* TPWM */
    GTM_TIM_MODE_PULSEINTEGRATION,        /* TPIM */
    GTM_TIM_MODE_INPUTEVENT,              /* TIEM */
    GTM_TIM_MODE_INPUTPRESCALER,          /* TIPM */
    GTM_TIM_MODE_BITCOMPRESSION,          /* TBCM */
    GTM_TIM_MODE_GATEPERIODICSAMPLE,    /* TGPS */
    GTM_TIM_MODE_SERIALSHIFT            /* TSSM */
} Gtm_Tim_Mode;

/* TIM Measurement starts edge */
typedef enum
{
    GTM_TIM_EDGE_CAP_FALL = 0U,            /* Measurement starts with falling edge */
    GTM_TIM_EDGE_CAP_RISE,                /* Measurement starts with rising edge */
    GTM_TIM_EDGE_CAP_BOTH                /* Measurement starts with both edge */
} Gtm_Tim_Edge_Cap;
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/* #Violation: gtm_tim_std_h_REF_3 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_tim_std_h_REF_2 */
#include "Gtm_MemMap.h"

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetClockSource
 * Description:  Sets the channel clock source
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               clk: Channel clock source
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetClockSource(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, Gtm_Cmu_Clk clk);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetChannelMode
 * Description:  Sets the mode of TIM channel x (x:0...7)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               timMode: TIM channel x (x:0...7) mode
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetChannelMode(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, 
                                                                              Gtm_Tim_Mode timMode);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetChannel
 * Description:  Enable / disable TIM channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               enable: Enable/ Disable choice of the feature
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetChannel(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, boolean enable);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetRegsSelector
 * Description:  Set selection for GPR1/GPR0/CNTS registers
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               cntsSel: Selection for CNTS register
 *               gpr0Sel: Selection for GPR0 register
 *               gpr1Sel: Selection for GPR1 register
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetRegsSelector(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint8 cntsSel,
                                                   uint8 gpr0Sel, uint8 gpr1Sel);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetEcntReset
 * Description:  Enable / disable resetting of counter in certain modes
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               enable: Enable/ Disable choice of the feature
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetEcntReset(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, boolean enable);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetStartupType
 * Description:  Set the startup type
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               immediate: Startup type, 0 = start with first active edge the measurement,
 *                                         1 = start immediately after enable (TIM_EN=1) the measurement
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetStartupType(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, boolean immediate);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetFLTParamRiseEdge
 * Description:  Set Filter parameter for rising edge
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               flt: Filter parameter
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetFLTParamRiseEdge(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint32 flt);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetFLTParamFallEdge
 * Description:  Set Filter parameter for falling edge
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               flt: Filter parameter
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetFLTParamFallEdge(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint32 flt);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetFLTModeRiseEdge
 * Description:  Set Filter mode for rising edge
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               mode: Filter mode
 *               counterMode: Filter counter mode
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetFLTModeRiseEdge(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint8 mode,
                                                                                                    uint8 counterMode);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetFLTModeFallEdge
 * Description:  Set Filter mode for falling edge
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               mode: Filter mode
 *               counterMode: Filter counter mode
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetFLTModeFallEdge(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint8 mode,
                                                                                                    uint8 counterMode);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetFLTCounterFreq
 * Description:  Set Filter counter frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               freq: Filter counter frequency select
 *                     0b00 = FLT_CNT counts with CMU_CLK0
 *                     0b01 = FLT_CNT counts with CMU_CLK1
 *                     0b10 = FLT_CNT counts with CMU_CLK6
 *                     0b11 = FLT_CNT counts with CMU_CLK7
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetFLTCounterFreq(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint8 freq);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetFLTEnable
 * Description:  Set filter enable for channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               enable: Enable/ Disable choice of filter
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetFLTEnable(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, boolean enable);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_ResetEdgeCount
 * Description:  Reset the edge counter
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  CNT reset correct
 *                        FALSE: CNT reset incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_ResetEdgeCount(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_ResetChannel
 * Description:  Software reset of channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Gtm_Tim_Std_ResetChannel(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_GetInterruptStatus
 * Description:  Gets specific / all interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               irqType: Interrupt types
 * Inout:        None
 * Output:       None
 * Return:       uint32: Specific / all interrupt status
 *                          bit 0: NEWVAL, bit 1: ECNTOFL, bit 2: CNTOFL, bit 3: ECNTOFL, GPROFL, bit 4: TODET,
 *                          bit 5: ECNTOFL, bit 6: GLITCHDET
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Gtm_Tim_Std_GetInterruptStatus(const GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, 
                                                                                       Gtm_Tim_IrqType irqType);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_GetTimPointer
 * Description:  Gets the TIM pointer
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        timIndex: TIM index
 * Inout:        None
 * Output:       None
 * Return:       GTM_TIM_t *: The pointer of TIM object
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE GTM_TIM_t * Gtm_Tim_Std_GetTimPointer(Gtm_Tim_Index timIndex);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_GetCounterValue
 * Description:  Gets the SMU counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 * Inout:        None
 * Output:       None
 * Return:       uint32: The counter value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Gtm_Tim_Std_GetCounterValue(const GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_GetEdgeCounter
 * Description:  Gets the SMU edge counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 * Inout:        None
 * Output:       None
 * Return:       uint32: The edge counter value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Gtm_Tim_Std_GetEdgeCounter(const GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_GetShadowCounter
 * Description:  Gets the SMU shadow counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 * Inout:        None
 * Output:       None
 * Return:       uint32: The shadow counter value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Gtm_Tim_Std_GetShadowCounter(const GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetShadowCounter
 * Description:  Sets the SMU shadow counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               uint32: The shadow counter value
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/04/12    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetShadowCounter(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint32 cnts);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_GetGPR0
 * Description:  Gets the general purpose 0 register value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 * Inout:        None
 * Output:       None
 * Return:       uint32: The general purpose 0 register
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Gtm_Tim_Std_GetGPR0(const GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_GetGPR1
 * Description:  Gets the general purpose 1 register value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 * Inout:        None
 * Output:       None
 * Return:       uint32: The general purpose 1 register
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/26    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Gtm_Tim_Std_GetGPR1(const GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel);
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetClockSource(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, Gtm_Cmu_Clk clk)
{
    boolean ret;

    ret = TRUE;
    pTim->CH[channel].CTRL.B.CLK_SEL = (uint32)clk;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)clk, pTim->CH[channel].CTRL.B.CLK_SEL);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetChannelMode(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, 
                                                                              Gtm_Tim_Mode timMode)
{
    boolean ret;

    ret = TRUE;
    pTim->CH[channel].CTRL.B.TIM_MODE = (uint32)timMode;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)timMode, pTim->CH[channel].CTRL.B.TIM_MODE);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetChannel(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, boolean enable)
{
    boolean ret;

    ret = TRUE;
    pTim->CH[channel].CTRL.B.TIM_EN = (uint32)enable;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)enable, pTim->CH[channel].CTRL.B.TIM_EN);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetRegsSelector(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint8 cntsSel,
                                                   uint8 gpr0Sel, uint8 gpr1Sel)
{
    boolean ret;

    ret = TRUE;
    pTim->CH[channel].CTRL.B.CNTS_SEL = cntsSel;
    pTim->CH[channel].CTRL.B.GPR0_SEL = gpr0Sel;
    pTim->CH[channel].CTRL.B.GPR1_SEL = gpr1Sel;

    ret = Gtm_Register_ReadBack_Check(ret, (uint32)cntsSel, pTim->CH[channel].CTRL.B.CNTS_SEL);
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)gpr0Sel, pTim->CH[channel].CTRL.B.GPR0_SEL);
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)gpr1Sel, pTim->CH[channel].CTRL.B.GPR1_SEL);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetEcntReset(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, boolean enable)
{
    boolean ret;

    ret = TRUE;
    pTim->CH[channel].CTRL.B.ECNT_RESET = (uint32)enable;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)enable, pTim->CH[channel].CTRL.B.ECNT_RESET);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetFLTParamRiseEdge(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint32 flt)
{
    boolean ret;

    ret = TRUE;
    pTim->CH[channel].FLT_RE.B.FLT_RE = flt;
    ret = Gtm_Register_ReadBack_Check(ret, flt, pTim->CH[channel].FLT_RE.B.FLT_RE);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetFLTParamFallEdge(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint32 flt)
{
    boolean ret;

    ret = TRUE;
    pTim->CH[channel].FLT_FE.B.FLT_FE = flt;
    ret = Gtm_Register_ReadBack_Check(ret, flt, pTim->CH[channel].FLT_FE.B.FLT_FE);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetFLTCounterFreq(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint8 freq)
{
    boolean ret;

    ret = TRUE;
    pTim->CH[channel].CTRL.B.FLT_CNT_FRQ = freq;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)freq, pTim->CH[channel].CTRL.B.FLT_CNT_FRQ);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetFLTEnable(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, boolean enable)
{
    boolean ret;

    ret = TRUE;
    pTim->CH[channel].CTRL.B.FLT_EN = enable;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)enable, pTim->CH[channel].CTRL.B.FLT_EN);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetFLTModeRiseEdge(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint8 mode, 
                                                                                                    uint8 counterMode)
{
    boolean ret;

    ret = TRUE;
    pTim->CH[channel].CTRL.B.FLT_MODE_RE = mode;
    pTim->CH[channel].CTRL.B.FLT_CTR_RE  = counterMode;

    ret = Gtm_Register_ReadBack_Check(ret, (uint32)mode, pTim->CH[channel].CTRL.B.FLT_MODE_RE);
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)counterMode, pTim->CH[channel].CTRL.B.FLT_CTR_RE);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetFLTModeFallEdge(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint8 mode, 
                                                                                                    uint8 counterMode)
{
    boolean ret;

    ret = TRUE;
    pTim->CH[channel].CTRL.B.FLT_MODE_FE = mode;
    pTim->CH[channel].CTRL.B.FLT_CTR_FE  = counterMode;

    ret = Gtm_Register_ReadBack_Check(ret, (uint32)mode, pTim->CH[channel].CTRL.B.FLT_MODE_FE);
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)counterMode, pTim->CH[channel].CTRL.B.FLT_CTR_FE);

    return ret;
}

LOCAL_FORCEINLINE void Gtm_Tim_Std_ResetChannel(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel)
{
    pTim->RST.U = (uint32)1U << (uint32)channel;
}

LOCAL_FORCEINLINE boolean Gtm_Tim_Std_ResetEdgeCount(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel)
{
    uint32 cnt;
    uint32 en;
    uint32 readBack;
    boolean ret;

    ret = TRUE;
    /* Get current channel state (enable / disable) */
    en = pTim->CH[channel].CTRL.B.TIM_EN;
    readBack = pTim->CH[channel].CNT.B.CNT;
    for (cnt = 0U; cnt < GTM_TIM_RESET_EDGE_COUNT_TIMEOUT; cnt++)
    {
        /* Change channel state */
        if (1U == en)
        {
            pTim->CH[channel].CTRL.B.TIM_EN = 0U;
        }
        else
        {
            pTim->CH[channel].CTRL.B.TIM_EN = 1U;
        }
        pTim->CH[channel].CTRL.B.TIM_EN = en;

        if (pTim->CH[channel].CNT.B.CNT <= readBack)
        {
            /* If the edge counter is reset, exit the loop */
            break;
        }
    }

    if (cnt >= GTM_TIM_RESET_EDGE_COUNT_TIMEOUT)
    {
        ret = FALSE;
    }

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetStartupType(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, boolean immediate)
{
    boolean ret;

    ret = TRUE;
    pTim->CH[channel].ECTRL.B.IMM_START = immediate;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)immediate, pTim->CH[channel].ECTRL.B.IMM_START);

    return ret;
}

LOCAL_FORCEINLINE uint32 Gtm_Tim_Std_GetInterruptStatus(const GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, 
                                                                                       Gtm_Tim_IrqType irqType)
{
    uint32 ret;
    if (GTM_TIM_IRQTYPE_ALL != irqType)
    {
        ret = (pTim->CH[channel].IRQ.NOTIFY.U >> (uint32)irqType) & 0x1U;
    }
    else
    {
        ret = (pTim->CH[channel].IRQ.NOTIFY.U & 0x3FU);
    }
    return ret;
}

LOCAL_FORCEINLINE GTM_TIM_t * Gtm_Tim_Std_GetTimPointer(Gtm_Tim_Index timIndex)
{
    /* #Violation: gtm_tim_std_h_REF_1 */
    return (GTM_TIM_t *)&GTM_HAL->GTM_CLUSTER[timIndex].TIM;
}

LOCAL_FORCEINLINE uint32 Gtm_Tim_Std_GetCounterValue(const GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel)
{
    return pTim->CH[channel].CNT.B.CNT;
}

LOCAL_FORCEINLINE uint32 Gtm_Tim_Std_GetEdgeCounter(const GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel)
{
    return pTim->CH[channel].ECNT.B.ECNT;
}

LOCAL_FORCEINLINE uint32 Gtm_Tim_Std_GetShadowCounter(const GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel)
{
    return pTim->CH[channel].CNTS.B.CNTS;
}

LOCAL_FORCEINLINE boolean Gtm_Tim_Std_SetShadowCounter(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint32 cnts)
{
    boolean ret;

    ret = TRUE;
    pTim->CH[channel].CNTS.B.CNTS = cnts;
    ret = Gtm_Register_ReadBack_Check(ret, cnts, pTim->CH[channel].CNTS.B.CNTS);

    return ret;
}

LOCAL_FORCEINLINE uint32 Gtm_Tim_Std_GetGPR0(const GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel)
{
    return pTim->CH[channel].GPR0.B.GPR0;
}

LOCAL_FORCEINLINE uint32 Gtm_Tim_Std_GetGPR1(const GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel)
{
    return pTim->CH[channel].GPR1.B.GPR1;
}

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetInputSource
 * Description:  Sets TIM channel input source
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               input: Input source to Channel
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Tim_Std_SetInputSource(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, Gtm_Tim_Input input);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetCaptureEdge
 * Description:  Sets TIM channel capture edge
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               edge: Capture edge
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Tim_Std_SetCaptureEdge(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, Gtm_Tim_Edge_Cap edge);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetInterruptMode
 * Description:  Sets interrupt mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               mode: Interrupt mode
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Tim_Std_SetInterruptMode(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, Gtm_IrqMode mode);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_SetInterrupt
 * Description:  Enable / disable TIM channel interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               irq: Interrupt enable control
 *                  1<<0    GTM_TIM_IRQ_NEWVAL
 *                  1<<1    GTM_TIM_IRQ_ECNTOVERFLOW
 *                  1<<2    GTM_TIM_IRQ_CNTOVERFLOW
 *                  1<<3    GTM_TIM_IRQ_GPROVERFLOW
 *                  1<<4    GTM_TIM_IRQ_TIMEOUTDETECT
 *                  1<<5    GTM_TIM_IRQ_GLITCHDETECT
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Tim_Std_SetInterrupt(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint8 irq);

/**********************************************************************************************************************
 * Function:     Gtm_Tim_Std_ClearInterruptStatus
 * Description:  Clears specific / all interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTim: Pointer to the TIM object
 *               channel: Channel index
 *               irqType: Interrupt types
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern void Gtm_Tim_Std_ClearInterruptStatus(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, Gtm_Tim_IrqType irqType);

/* #Violation: gtm_tim_std_h_REF_3 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_tim_std_h_REF_2 */
#include "Gtm_MemMap.h"
#endif /* GTM_TIM_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
