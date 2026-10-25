/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_icu_hal.c
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the interface implementations of ICU module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
* #gtm_icu_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
* #gtm_icu_hal_c_REF_2:MISRAC2012-Rule-10.5;
* Justification: Limitation of Cortex-R52+ Core. Boolean can only be representes as uint8.
*
* #gtm_icu_hal_c_REF_3:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #gtm_icu_hal_c_REF_4:CertC-DCL15-C;
* Justification: Reserved API for user access.
*
* #gtm_icu_hal_c_REF_5:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_icu_hal_c_REF_6:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
* #gtm_icu_hal_c_REF_7:MISRAC2012-Rule-8.7;
* Justification:The interface is called by the application layer.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "gtm_icu_hal.h"
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
#ifndef GTM_HAL_MEMMAP
/* #Violation: gtm_icu_hal_c_REF_6 */
#define ICU_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_icu_hal_c_REF_5 */
#include "Icu_MemMap.h"
#else
/* #Violation: gtm_icu_hal_c_REF_6 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_icu_hal_c_REF_5 */
#include "Gtm_MemMap.h"
#endif

/* #Violation: gtm_icu_hal_c_REF_1 */
/* #Violation: gtm_icu_hal_c_REF_4 */
/* #Violation: gtm_icu_hal_c_REF_7 */
boolean Gtm_Icu_Hal_SetTimSrcInMux(uint8 inMux)
{
#if(STD_ON == INPUT_ARG_DETECT)
/* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(inMux <= 1U));
#endif
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_icu_hal_c_REF_3 */
    GTM_HAL->GTM_CLUSTER[0].CFG.B.SRC_IN_MUX = inMux;
    /* #Violation: gtm_icu_hal_c_REF_3 */
    ret = Gtm_Register_ReadBack_Check(ret, inMux, GTM_HAL->GTM_CLUSTER[0].CFG.B.SRC_IN_MUX);
    return ret;
}

/* #Violation: gtm_icu_hal_c_REF_1 */
/* #Violation: gtm_icu_hal_c_REF_4 */
/* #Violation: gtm_icu_hal_c_REF_7 */
boolean Gtm_Icu_Hal_TimAuxIn(const Gtm_TimAux_In *const pTimAuxIn)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pTimAuxIn));
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(pTimAuxIn->src <= 1U));
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(pTimAuxIn->selOutN <= 1U));
#endif
    uint32  value;
    uint32  mask;
    boolean ret;

    ret = TRUE;
    mask  = ((uint32)0x1U << (uint32)pTimAuxIn->channel) | ((uint32)0x1U << ((uint32)pTimAuxIn->channel + 16U));
    value = ((uint32)pTimAuxIn->src << (uint32)pTimAuxIn->channel) |
            ((uint32)pTimAuxIn->selOutN << ((uint32)pTimAuxIn->channel + 16U));

    /* #Violation: gtm_icu_hal_c_REF_3 */
    GTM_HAL->GTM_CLUSTER[pTimAuxIn->tim].CCM.TIM_AUX_IN_SRC.U =
            /* #Violation: gtm_icu_hal_c_REF_3 */
            (GTM_HAL->GTM_CLUSTER[pTimAuxIn->tim].CCM.TIM_AUX_IN_SRC.U & ~mask) | value;
    /* #Violation: gtm_icu_hal_c_REF_3 */
    ret = Gtm_Register_ReadBack_Check(ret, value, GTM_HAL->GTM_CLUSTER[pTimAuxIn->tim].CCM.TIM_AUX_IN_SRC.U & mask);
    return ret;
}

 /* #Violation: gtm_icu_hal_c_REF_1 */
 boolean Gtm_Icu_Hal_SetAuxInput(const Gtm_Icu_Driver *const pDriver, const Gtm_Icu_Config *const pConfig)
{
    GTM_TIM_t     *pTim;
    Gtm_TimAux_In auxIn;
    boolean       ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif

    ret = TRUE;
    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    ret &= Gtm_Tim_Std_SetInputSource(pTim, pDriver->channel, pConfig->input);

    if (GTM_TIM_INPUT_AUX == pConfig->input)
    {
        if (TRUE == pConfig->auxInCfg.isBigger8)
        {
            ret &= Gtm_Icu_Hal_SetTimSrcInMux(0U);
        }
        else
        {
            ret &= Gtm_Icu_Hal_SetTimSrcInMux(1U);
        }

        if (TRUE == pConfig->auxInCfg.isTom)
        {
            auxIn.src = 0U;
        }
        else
        {
            auxIn.src = 1U;
        }

        if (TRUE == pConfig->auxInCfg.isNegtive)
        {
            auxIn.selOutN = 1U;
        }
        else
        {
            auxIn.selOutN = 0U;
        }
        auxIn.tim     = pDriver->tim;
        auxIn.channel = pDriver->channel;
        ret &= Gtm_Icu_Hal_TimAuxIn(&auxIn);
    }
    return ret;
}

/* #Violation: gtm_icu_hal_c_REF_1 */
boolean Gtm_Icu_Hal_InitChannel(const Gtm_Icu_Driver *const pDriver, const Gtm_Icu_Config *const pConfig)
{
    GTM_TIM_t *pTim;
    uint8     counterMode;
    boolean   ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
    if (NULL_PTR != pConfig->filter)
    {
        /* #Violation: gtm_icu_hal_c_REF_2 */
        Assert((boolean)(pConfig->filter->fallingEdgeFilterTime <= 0xFFFFFFU));
        /* #Violation: gtm_icu_hal_c_REF_2 */
        Assert((boolean)(pConfig->filter->risingEdgeFilterTime <= 0xFFFFFFU));
    }
#endif

    ret = TRUE;
    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);

    /* Select channel input source */
    ret &= Gtm_Tim_Std_SetInputSource(pTim, pDriver->channel, pConfig->input);

    ret &= Gtm_Tim_Std_SetClockSource(pTim, pDriver->channel, pConfig->clk);
    ret &= Gtm_Tim_Std_SetCaptureEdge(pTim, pDriver->channel, pConfig->edge);

    /* Filter configuration */
    if (NULL_PTR != pConfig->filter)
    {
        ret &= Gtm_Tim_Std_SetFLTCounterFreq(pTim, pDriver->channel, (uint8)pConfig->filter->clk);
        /* Set filter time */
        ret &= Gtm_Tim_Std_SetFLTParamFallEdge(pTim, pDriver->channel, pConfig->filter->fallingEdgeFilterTime);
        ret &= Gtm_Tim_Std_SetFLTParamRiseEdge(pTim, pDriver->channel, pConfig->filter->risingEdgeFilterTime);

        /* Set filter falling edge mode */
        if (GTM_TIM_FLTMODE_NONE != pConfig->filter->fallingEdgeMode)
        {
            if (GTM_TIM_FLTMODE_IMMEDIATE == pConfig->filter->fallingEdgeMode)
            {
                ret &= Gtm_Tim_Std_SetFLTModeFallEdge(pTim, pDriver->channel, 0U, 0U);
            }
            else
            {
                counterMode = ((pConfig->filter->fallingEdgeMode ==  GTM_TIM_FLTMODE_DEGLITCHTIMEUPDOWN) ? 0U : 1U);
                ret &= Gtm_Tim_Std_SetFLTModeFallEdge(pTim, pDriver->channel, 1U, counterMode);
            }
        }
        else
        {
            ret &= Gtm_Tim_Std_SetFLTModeFallEdge(pTim, pDriver->channel, 0U, 0U);
            ret &= Gtm_Tim_Std_SetFLTParamFallEdge(pTim, pDriver->channel, 0U);
        }

        /* Set filter rising edge mode */
        if (GTM_TIM_FLTMODE_NONE != pConfig->filter->risingEdgeMode)
        {
            if (GTM_TIM_FLTMODE_IMMEDIATE == pConfig->filter->risingEdgeMode)
            {
                ret &= Gtm_Tim_Std_SetFLTModeRiseEdge(pTim, pDriver->channel, 0U, 0U);
            }
            else
            {
                counterMode = ((pConfig->filter->risingEdgeMode ==  GTM_TIM_FLTMODE_DEGLITCHTIMEUPDOWN) ? 0U : 1U);
                ret &= Gtm_Tim_Std_SetFLTModeRiseEdge(pTim, pDriver->channel, 1U, counterMode);
            }
        }
        else
        {
            ret &= Gtm_Tim_Std_SetFLTModeRiseEdge(pTim, pDriver->channel, 0U, 0U);
            ret &= Gtm_Tim_Std_SetFLTParamRiseEdge(pTim, pDriver->channel, 0U);
        }
        ret &= Gtm_Tim_Std_SetFLTEnable(pTim, pDriver->channel, TRUE);
    }

    switch (pConfig->icuMode)
    {
        case ICU_MODE_SIGNAL_EDGE_DETECT:
        {
            ret &= Gtm_Tim_Std_SetRegsSelector(pTim, pDriver->channel, (uint8)GTM_TIM_CNTSSEL_CNTREG, 
                                                (uint8)GTM_TIM_GPRSEL_CNTS, (uint8)GTM_TIM_GPRSEL_CNTS);
            ret &= Gtm_Tim_Std_SetEcntReset(pTim, pDriver->channel, FALSE);
            ret &= Gtm_Tim_Std_SetChannelMode(pTim, pDriver->channel, GTM_TIM_MODE_INPUTEVENT);
            break;
        }

        case ICU_MODE_SIGNAL_MEASUREMENT:
        {
            ret &= Gtm_Tim_Std_SetRegsSelector(pTim, pDriver->channel, (uint8)GTM_TIM_CNTSSEL_CNTREG, 
                                                (uint8)GTM_TIM_GPRSEL_CNTS, (uint8)GTM_TIM_GPRSEL_CNTS);
            ret &= Gtm_Tim_Std_SetEcntReset(pTim, pDriver->channel, pConfig->isEcntReset);
            ret &= Gtm_Tim_Std_SetChannelMode(pTim, pDriver->channel, GTM_TIM_MODE_PWMMEASUREMENT);
            break;
        }

        case ICU_MODE_TIMESTAMP:
        {
            ret &= Gtm_Tim_Std_SetRegsSelector(pTim, pDriver->channel, (uint8)GTM_TIM_CNTSSEL_TBUTS0, 
                                                (uint8)GTM_TIM_GPRSEL_TBUTS0, (uint8)GTM_TIM_GPRSEL_CNTS);
            ret &= Gtm_Tim_Std_SetEcntReset(pTim, pDriver->channel, FALSE);
            ret &= Gtm_Tim_Std_SetChannelMode(pTim, pDriver->channel, GTM_TIM_MODE_INPUTEVENT);
            break;
        }

        case ICU_MODE_EDGE_COUNTER:
        {
            ret &= Gtm_Tim_Std_SetRegsSelector(pTim, pDriver->channel, (uint8)GTM_TIM_CNTSSEL_CNTREG, 
                                                (uint8)GTM_TIM_GPRSEL_CNTS, (uint8)GTM_TIM_GPRSEL_CNTS);
            ret &= Gtm_Tim_Std_SetEcntReset(pTim, pDriver->channel, FALSE);
            ret &= Gtm_Tim_Std_SetChannelMode(pTim, pDriver->channel, GTM_TIM_MODE_INPUTEVENT);
            break;
        }

        case ICU_MODE_UNDEFINE:
        default:
        {
            /* Channel configuration */
            ret &= Gtm_Tim_Std_SetRegsSelector(pTim, pDriver->channel, (uint8)pConfig->ctrlMethodSetPtr->cntsCtrl, 
                            (uint8)pConfig->ctrlMethodSetPtr->gpr0Ctrl, (uint8)pConfig->ctrlMethodSetPtr->gpr1Ctrl);
            ret &= Gtm_Tim_Std_SetEcntReset(pTim, pDriver->channel, pConfig->isEcntReset);
            ret &= Gtm_Tim_Std_SetChannelMode(pTim, pDriver->channel, pConfig->ctrlMethodSetPtr->mode);
            break;
        }
    }

    /* Interrupt configuration */
    ret &= Gtm_Tim_Std_SetInterruptMode(pTim, pDriver->channel, pConfig->interrupt.mode);
    ret &= Gtm_Tim_Std_SetInterrupt(pTim, pDriver->channel, pConfig->interrupt.irq);

    ret &= Gtm_Tim_Std_SetChannel(pTim, pDriver->channel, pConfig->isChannelEnable);
    return ret;
}

/* #Violation: gtm_icu_hal_c_REF_1 */
void Gtm_Icu_Hal_DeinitChannel(const Gtm_Icu_Driver *const pDriver)
{
    GTM_TIM_t    *pTim;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
#endif

    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    Gtm_Tim_Std_ResetChannel(pTim, pDriver->channel);
}

/* #Violation: gtm_icu_hal_c_REF_1 */
boolean Gtm_Icu_Hal_SetCaptureEdge(const Gtm_Icu_Driver *const pDriver, Gtm_Tim_Edge_Cap edge)
{
    GTM_TIM_t *pTim;
    boolean   ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
#endif

    ret = TRUE;
    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    ret &= Gtm_Tim_Std_SetCaptureEdge(pTim, pDriver->channel, edge);
    return ret;
}

/* #Violation: gtm_icu_hal_c_REF_1 */
boolean Gtm_Icu_Hal_SetInterrupt(const Gtm_Icu_Driver *const pDriver, uint8 irq)
{
    GTM_TIM_t *pTim;
    boolean   ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(irq <= 0x3FU));
#endif

    ret = TRUE;
    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    ret &= Gtm_Tim_Std_SetInterrupt(pTim, pDriver->channel, irq);
    return ret;
}

/* #Violation: gtm_icu_hal_c_REF_1 */
boolean Gtm_Icu_Hal_ResetEdgeCount(const Gtm_Icu_Driver *const pDriver)
{
    GTM_TIM_t    *pTim;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
#endif

    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    return Gtm_Tim_Std_ResetEdgeCount(pTim, pDriver->channel);
}

/* #Violation: gtm_icu_hal_c_REF_1 */
boolean Gtm_Icu_Hal_StartCapture(const Gtm_Icu_Driver *const pDriver, uint8 irq, 
                                                Gtm_Tim_Edge_Cap edge, boolean immediate)
{
    GTM_TIM_t *pTim;
    boolean   ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(irq <= 0x3FU));
#endif

    ret = TRUE;
    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    Gtm_Tim_Std_ClearInterruptStatus(pTim, pDriver->channel, GTM_TIM_IRQTYPE_ALL);
    ret &= Gtm_Tim_Std_SetCaptureEdge(pTim, pDriver->channel, edge);
    if (0U != irq)
    {
        ret &= Gtm_Tim_Std_SetInterrupt(pTim, pDriver->channel, irq);
    }

    ret &= Gtm_Tim_Std_SetStartupType(pTim, pDriver->channel, immediate);
    ret &= Gtm_Tim_Std_SetChannel(pTim, pDriver->channel, TRUE);

    return ret;
}

/* #Violation: gtm_icu_hal_c_REF_1 */
boolean Gtm_Icu_Hal_StartEdgeDetect(const Gtm_Icu_Driver *const pDriver, uint8 irq, 
                                                Gtm_Tim_Edge_Cap edge, uint32 cnt)
{
    GTM_TIM_t *pTim;
    boolean   ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(irq <= 0x3FU));
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(cnt <= 0xFFFFFFU));
#endif

    ret = TRUE;
    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    Gtm_Tim_Std_ClearInterruptStatus(pTim, pDriver->channel, GTM_TIM_IRQTYPE_ALL);
    ret &= Gtm_Tim_Std_SetCaptureEdge(pTim, pDriver->channel, edge);
    if (0U != irq)
    {
        ret &= Gtm_Tim_Std_SetInterrupt(pTim, pDriver->channel, irq);
    }

    if (cnt > 1U)
    {
        ret &= Gtm_Tim_Std_SetChannelMode(pTim, pDriver->channel, GTM_TIM_MODE_INPUTPRESCALER);
        ret &= Gtm_Tim_Std_SetShadowCounter(pTim, pDriver->channel, cnt - 1U);
    }
    else
    {
        ret &= Gtm_Tim_Std_SetChannelMode(pTim, pDriver->channel, GTM_TIM_MODE_INPUTEVENT);
    }

    ret &= Gtm_Tim_Std_SetChannel(pTim, pDriver->channel, TRUE);
    return ret;
}

/* #Violation: gtm_icu_hal_c_REF_1 */
boolean Gtm_Icu_Hal_StopCapture(const Gtm_Icu_Driver *const pDriver)
{
    GTM_TIM_t *pTim;
    boolean   ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
#endif

    ret = TRUE;
    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    ret &= Gtm_Tim_Std_SetChannel(pTim, pDriver->channel, FALSE);
    Gtm_Tim_Std_ClearInterruptStatus(pTim, pDriver->channel, GTM_TIM_IRQTYPE_ALL);
    return ret;
}

/* #Violation: gtm_icu_hal_c_REF_1 */
Gtm_SignalState Gtm_Icu_Hal_GetSignalLevel(const Gtm_Icu_Driver *const pDriver)
{
    const GTM_TIM_t *pTim;
    Gtm_SignalState ret;
    uint32          edgeCN;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
#endif

    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    edgeCN = Gtm_Tim_Std_GetEdgeCounter(pTim, pDriver->channel);
    if (1U == (edgeCN & 0x1U))
    {
        ret = GTM_SIGNALSTATE_HIGH;
    }
    else
    {
        ret = GTM_SIGNALSTATE_LOW;
    }
    return ret;
}

/* #Violation: gtm_icu_hal_c_REF_1 */
void Gtm_Icu_Hal_GetUndefinedResult(const Gtm_Icu_Driver *const pDriver, Gtm_Icu_UndefinedResult *const result)
{
    const GTM_TIM_t *pTim;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
#endif

    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    result->GPR1 = Gtm_Tim_Std_GetGPR1(pTim, pDriver->channel);
    result->GPR0 = Gtm_Tim_Std_GetGPR0(pTim, pDriver->channel);
    result->CNT  = Gtm_Tim_Std_GetCounterValue(pTim, pDriver->channel);
    result->CNTS = Gtm_Tim_Std_GetShadowCounter(pTim, pDriver->channel);
    result->ECNT = Gtm_Tim_Std_GetEdgeCounter(pTim, pDriver->channel);
}

/* #Violation: gtm_icu_hal_c_REF_1 */
uint32 Gtm_Icu_Hal_GetTimeStamp(const Gtm_Icu_Driver *const pDriver)
{
    const GTM_TIM_t *pTim;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
#endif

    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    return Gtm_Tim_Std_GetGPR0(pTim, pDriver->channel);
}

/* #Violation: gtm_icu_hal_c_REF_1 */
uint32 Gtm_Icu_Hal_GetEdgeNums(const Gtm_Icu_Driver *const pDriver)
{
    const GTM_TIM_t *pTim;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
#endif

    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    return Gtm_Tim_Std_GetCounterValue(pTim, pDriver->channel);
}

/* #Violation: gtm_icu_hal_c_REF_1 */
uint32 Gtm_Icu_Hal_GetTimeElapsed(const Gtm_Icu_Driver *const pDriver)
{
    const GTM_TIM_t *pTim;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
#endif

    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    return Gtm_Tim_Std_GetGPR1(pTim, pDriver->channel);
}

/* #Violation: gtm_icu_hal_c_REF_1 */
uint32 Gtm_Icu_Hal_GetOverFlowElapsedTime(const Gtm_Icu_Driver *const pDriver)
{
    const GTM_TIM_t *pTim;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
#endif
    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    return Gtm_Tim_Std_GetShadowCounter(pTim, pDriver->channel);
}

/* #Violation: gtm_icu_hal_c_REF_1 */
void Gtm_Icu_Hal_GetDutyCycleValues(const Gtm_Icu_Driver *const pDriver, Gtm_Icu_DutyCycleResult *const dutyCycle)
{
    const GTM_TIM_t *pTim;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
#endif

    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    dutyCycle->PeriodTime = Gtm_Tim_Std_GetGPR1(pTim, pDriver->channel);
    dutyCycle->ActiveTime = Gtm_Tim_Std_GetGPR0(pTim, pDriver->channel);
}

/* #Violation: gtm_icu_hal_c_REF_1 */
uint32 Gtm_Icu_Hal_GetInterruptStatus(const Gtm_Icu_Driver *const pDriver, Gtm_Tim_IrqType irqType)
{
    const GTM_TIM_t *pTim;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
#endif

    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    return Gtm_Tim_Std_GetInterruptStatus(pTim, pDriver->channel, irqType);
}

/* #Violation: gtm_icu_hal_c_REF_1 */
void Gtm_Icu_Hal_ClearInterruptStatus(const Gtm_Icu_Driver *const pDriver, Gtm_Tim_IrqType irqType)
{
    GTM_TIM_t    *pTim;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_icu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
#endif

    pTim = Gtm_Tim_Std_GetTimPointer(pDriver->tim);
    Gtm_Tim_Std_ClearInterruptStatus(pTim, pDriver->channel, irqType);
}

#ifndef GTM_HAL_MEMMAP
/* #Violation: gtm_icu_hal_c_REF_6 */
#define ICU_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_icu_hal_c_REF_5 */
#include "Icu_MemMap.h"
#else
/* #Violation: gtm_icu_hal_c_REF_6 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_icu_hal_c_REF_5 */
#include "Gtm_MemMap.h"
#endif
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
