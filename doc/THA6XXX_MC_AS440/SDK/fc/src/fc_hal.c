/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    fc_hal.c
 * Author:      01254
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of FC module.
 *********************************************************************************************************************/

/*
* #Violation Summary
* #fc_hal_c_REF_1:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by code review.
*
* #fc_hal_c_REF_2:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access
*
* #fc_hal_c_REF_3:MISRAC2012-Rule-10.5;
* Justification: Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8.
*
* #fc_hal_c_REF_4:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #fc_hal_c_REF_5:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
* #fc_hal_c_REF_6:MISRAC2012-Rule-8.7; 
* Justification: The function is used by other file.
*
* #fc_hal_c_REF_7:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
* #fc_hal_c_REF_8:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "fc_register.h"
#include "fc_hal.h"
#include "cpuwdt_hal.h"
#include "rcc_hal.h"
#include "Platform_Types.h"
#include "tha6_cfg.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* Triggre gate control mode of reference value generating */
/* Trigger gate to ramp */
#define FC_TRIGGERGATE_RAMP (0U)
/* Trigger gate to alternate */
#define FC_TRIGGERGATE_ALTERNATE (1U)
/* Trigger gate to lock */
#define FC_TRIGGERGATE_LOCK (2U)
/* Trigger level mask */
#define FC_TRIGGERLEVEL_MASK (0x30F0E303U)
/* Boundary flag register mask, include CRVF, CR, BFDAT, BFSEL, BDFLAG */
#define FC_BDFL_MASK (0xF033118U)
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: fc_hal_c_REF_7 */
#define FC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: fc_hal_c_REF_8 */
#include "Fc_MemMap.h"
/* #Violation: fc_hal_c_REF_2 */
Rcc_ErrorFlag Fc_Hal_ResetModule(const FC_MODULE *const pFc)
{
    Rcc_ModuleRst moduleFcSel;
    Rcc_ErrorFlag resetResult;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: fc_hal_c_REF_4 */
    /* #Violation: fc_hal_c_REF_5 */
    Assert((boolean)(CHECK_FC_BASE(pFc)));
#endif
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    /* #Violation: fc_hal_c_REF_4 */
    /* #Violation: fc_hal_c_REF_5 */
    moduleFcSel = GET_FC_RCC_RST_NUM(pFc);
#endif
    resetResult = Rcc_Hal_TrigModuleRst(moduleFcSel);
    return resetResult;
}

/* #Violation: fc_hal_c_REF_6 */
boolean Fc_Hal_InitReferenceValue(FC_MODULE *const pFc, const Fc_ReferenceValueConfig *const pConfig)
{
    /* #Violation: fc_hal_c_REF_1 */
    FC_MODE fcModeVal;
    /* #Violation: fc_hal_c_REF_1 */
    FC_CON0 fcCon0Val;
    /* #Violation: fc_hal_c_REF_1 */
    FC_CON1 fcCon1Val;
    /* #Violation: fc_hal_c_REF_1 */
    FC_RAMP0 fcRamp0Val;
    /* #Violation: fc_hal_c_REF_1 */
    FC_HYST fcHystVal;
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: fc_hal_c_REF_4 */
    /* #Violation: fc_hal_c_REF_5 */
    Assert((boolean)(CHECK_FC_BASE(pFc)));
    /* #Violation: fc_hal_c_REF_3 */
    Assert((boolean)(pConfig->alternateValue.value0 < 1024U));
    /* #Violation: fc_hal_c_REF_3 */
    Assert((boolean)(pConfig->alternateValue.value1 < 1024U));
    /* #Violation: fc_hal_c_REF_3 */
    Assert((boolean)(pConfig->rampConfig.startValue < 1024U));
    /* #Violation: fc_hal_c_REF_3 */
    Assert((boolean)(pConfig->rampConfig.endValue < 1024U));
    /* #Violation: fc_hal_c_REF_3 */
    Assert((boolean)(pConfig->referenceValue < 1024U));
#endif
    ret = TRUE;
    /* read register */
    fcModeVal.U = pFc->MODE.U;
    fcCon0Val.U = pFc->CON0.U;
    fcCon1Val.U = pFc->CON1.U;
    fcRamp0Val.U = pFc->RAMP0.U;
    fcHystVal.U = pFc->HYST.U;
    /* configure reference mode */
    fcModeVal.B.REFG = (uint32)pConfig->refMode;
    /* configure reference value */
    if(pConfig->refMode == FC_REFERENCEVALUEMODE_SOFTWARE)
    {
        pFc->REFVAL.B.REFVALSW = pConfig->referenceValue;
    }
    else if(pConfig->refMode == FC_REFERENCEVALUEMODE_ALTERNATE)
    {
        fcRamp0Val.B.RAMPCMP0 = pConfig->alternateValue.value0;
        pFc->RAMP1.U = pConfig->alternateValue.value1;
        /* if reference is alternate mode, the trigger is gate to alternate by default */
        fcCon1Val.B.GCONMODE = (uint32)FC_TRIGGERGATE_ALTERNATE;
    }
    else if(pConfig->refMode == FC_REFERENCEVALUEMODE_RAMP)
    {
        fcRamp0Val.B.RAMPCMP0 = pConfig->rampConfig.startValue;
        fcRamp0Val.B.RAMPSTEP = pConfig->rampConfig.stepWide;
        pFc->RAMP1.U = pConfig->rampConfig.endValue;
        fcModeVal.B.RAMDIR = (uint32)pConfig->rampConfig.dir;
        fcModeVal.B.RAMPON = (uint32)pConfig->rampConfig.runCtrl;
        fcCon0Val.B.TRIMODE = (uint32)pConfig->rampConfig.triggerEdge;
        /* if reference is ramp mode, the trigger is gate to ramp by default */
        fcCon1Val.B.GCONMODE = (uint32)FC_TRIGGERGATE_RAMP;
    }
    else
    {
        /* do noting */
    }
    /* configure hysteresis */
    fcHystVal.B.UPDELTA = pConfig->upDelta;
    fcHystVal.B.LOWDELTA = pConfig->lowDelta;
    /* configure trigger */
    fcCon0Val.B.TRISEL = (uint32)pConfig->trigger.inputSel;
    fcCon1Val.B.TRINV = (uint32)pConfig->trigger.polarity;
    /* write register */
    pFc->MODE.U = fcModeVal.U;
    ret = Fc_Register_ReadBack_Check(ret, fcModeVal.U, pFc->MODE.U);
    pFc->CON0.U = fcCon0Val.U;
    ret = Fc_Register_ReadBack_Check(ret, (fcCon0Val.U & FC_TRIGGERLEVEL_MASK), (pFc->CON0.U & FC_TRIGGERLEVEL_MASK));
    pFc->CON1.U = fcCon1Val.U;
    ret = Fc_Register_ReadBack_Check(ret, fcCon1Val.U, pFc->CON1.U);
    pFc->RAMP0.U = fcRamp0Val.U;
    ret = Fc_Register_ReadBack_Check(ret, fcRamp0Val.U, pFc->RAMP0.U);
    pFc->HYST.U = fcHystVal.U;
    ret = Fc_Register_ReadBack_Check(ret, fcHystVal.U, pFc->HYST.U);

    return ret;
}

/* #Violation: fc_hal_c_REF_6 */
boolean Fc_Hal_InitOutput(FC_MODULE *const pFc, const Fc_OutputConfig *const pConfig)
{
    /* #Violation: fc_hal_c_REF_1 */
    FC_BDFL fcBdflVal;
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: fc_hal_c_REF_4 */
    /* #Violation: fc_hal_c_REF_5 */
    Assert((boolean)(CHECK_FC_BASE(pFc)));
#endif
    ret = TRUE;
    /* read register */
    fcBdflVal.U = pFc->BDFL.U;
    /* configure boundary flag */
    fcBdflVal.B.BFACT = (uint32)pConfig->bfMode;
    fcBdflVal.B.BFINV = (uint32)pConfig->bfpolarity;
    fcBdflVal.B.BFP = (uint32)pConfig->commonOutputSel;
    fcBdflVal.B.BFOUTSEL = (uint32)pConfig->bfOutputSel;
    /* set boundary flag */
    if(FC_BOUNDARYFLAGCONTROL_HARDWARE == pConfig->ctrl)
    {
        fcBdflVal.B.BFHW = 1U;
    }
    else
    {
        fcBdflVal.B.BFHW = 0U;
        fcBdflVal.B.BFSW = (uint32)pConfig->ctrl;
    }
    /* if lock boundary flag  */
    if(TRUE == pConfig->bfLock.bfLockEnable)
    {
        pFc->CON1.B.GCONMODE = (uint32)FC_TRIGGERGATE_LOCK;
        fcBdflVal.B.BFRSW = pConfig->bfLock.bflockValue;
    }
    /* write register */
    pFc->BDFL.U = fcBdflVal.U;
    ret = Fc_Register_ReadBack_Check(ret, (fcBdflVal.U & FC_BDFL_MASK), (pFc->BDFL.U & FC_BDFL_MASK));
    return ret;
}

/* #Violation: fc_hal_c_REF_2 */
Fc_ErrorFlag Fc_Hal_Init(FC_MODULE *const pFc, const Fc_Config *const pConfig)
{
    /* #Violation: fc_hal_c_REF_1 */
    FC_CON0 fcCon0Val;
    /* #Violation: fc_hal_c_REF_1 */
    FC_CON1 fcCon1Val;
    uint32 delayCnt;
    Fc_ErrorFlag ret;
    boolean regRet;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: fc_hal_c_REF_4 */
    /* #Violation: fc_hal_c_REF_5 */
    Assert((boolean)(CHECK_FC_BASE(pFc)));
    /* Check if the quick comparison interval period >= (sampling period + quick comparison period + 1) */
    /* #Violation: fc_hal_c_REF_3 */
    Assert((boolean)((((pConfig->compareConfig.compareInterval == 0U) ? 7U : (pConfig->compareConfig.compareInterval + 1U))
                   << 2U) >= ((((uint8)pConfig->compareConfig.sampleTime + 1U) << 1U) +
                              (((uint8)pConfig->compareConfig.compareTime + 1U) << 1U) + 1U)));
#endif
    regRet = TRUE;
    /* read register */
    fcCon0Val.U = pFc->CON0.U;
    fcCon1Val.U = pFc->CON1.U;
    /* enable analog IP by default */
    /* Unlock cpu endinit protect */
    DISABLE_ALL_INTERRUPTS();
    regRet &= Cpuwdt_Hal_ClearEndinit();
    pFc->ANEN.U = 1U;
    /* Lock cpu endinit protect */
    regRet &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();

    /* configure fc compare */
    fcCon0Val.B.CKDIVA = (uint32)pConfig->compareConfig.clockDiv;
    fcCon0Val.B.STCON = (uint32)pConfig->compareConfig.sampleTime;
    fcCon1Val.B.CTCON = (uint32)pConfig->compareConfig.compareTime;
    pFc->MODE.B.FCINTVL = pConfig->compareConfig.compareInterval;
    pFc->FCINT.B.DMAEN = pConfig->compareConfig.dmaEnable;
    fcCon1Val.B.CVCH = (uint32)pConfig->compareConfig.inputSel;
    /* write register */
    pFc->CON0.U = fcCon0Val.U;
    regRet = Fc_Register_ReadBack_Check(regRet, (fcCon0Val.U & FC_TRIGGERLEVEL_MASK), (pFc->CON0.U & FC_TRIGGERLEVEL_MASK));
    pFc->CON1.U = fcCon1Val.U;
    regRet = Fc_Register_ReadBack_Check(regRet, fcCon1Val.U, pFc->CON1.U);

    /* configure fc reference value */
    regRet &= Fc_Hal_InitReferenceValue(pFc, &(pConfig->reference));
    /* configure fc output */
    regRet &= Fc_Hal_InitOutput(pFc, &(pConfig->output));

    /* wait analog IP initial complete */
    delayCnt = 0UL;
    while((delayCnt < ANALOG_INIT_TIMEOUT) && (0U == pFc->ANSTS.B.ANAINIT))
    {
        delayCnt++;
    }
    /* if analog initialization over time, return fail */
    ret = FC_ERRORFLAG_SUCCESS;
    if(delayCnt >= ANALOG_INIT_TIMEOUT)
    {
        ret = FC_ERRORFLAG_FAIL;
    }

    if(regRet == FALSE)
    {
        ret = FC_ERRORFLAG_FAIL;
    }
    return ret;
}

/* #Violation: fc_hal_c_REF_2 */
boolean Fc_Hal_StartCompare(FC_MODULE *const pFc, boolean enable)
{
    boolean ret;
    uint32 enableCtrl;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: fc_hal_c_REF_4 */
    /* #Violation: fc_hal_c_REF_5 */
    Assert((boolean)(CHECK_FC_BASE(pFc)));
#endif
    ret = TRUE;
    /* Unlock cpu endinit protect */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    if(TRUE == enable)
    {
        enableCtrl = 1U;
    }
    else
    {
        enableCtrl = 0U;
    }
    pFc->FCON.U = enableCtrl;
    /* Lock cpu endinit protect */
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    ret = Fc_Register_ReadBack_Check(ret, enableCtrl, pFc->FCON.U);
    return ret;
}

/* #Violation: fc_hal_c_REF_2 */
boolean Fc_Hal_SetInterrupt(FC_MODULE *const pFc, const Fc_Interrupt *const pConfig)
{
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: fc_hal_c_REF_4 */
    /* #Violation: fc_hal_c_REF_5 */
    Assert((boolean)(CHECK_FC_BASE(pFc)));
#endif
    ret = TRUE;
    pFc->MODE.B.INTG = (uint32)pConfig->mode;
    ret = Fc_Register_ReadBack_Check(ret, (uint32)pConfig->mode, pFc->MODE.B.INTG);
    if(FC_INTERRUTMODE_COMPARE_OVER == pConfig->mode)
    {
        pFc->CON0.B.CHEGMODE = (uint32)pConfig->event;
        ret = Fc_Register_ReadBack_Check(ret, (uint32)pConfig->event, pFc->CON0.B.CHEGMODE);
    }
    return ret;
}

/* #Violation: fc_hal_c_REF_2 */
boolean Fc_Hal_GetInterruptStatus(const FC_MODULE *const pFc)
{
    boolean status;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: fc_hal_c_REF_4 */
    /* #Violation: fc_hal_c_REF_5 */
    Assert((boolean)(CHECK_FC_BASE(pFc)));
#endif
    /* #Violation: fc_hal_c_REF_3 */
    status = (boolean)(1U == pFc->FCINT.B.INTST);
    return status;
}

/* #Violation: fc_hal_c_REF_2 */
void Fc_Hal_ClearInterruptStatus(FC_MODULE *const pFc)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: fc_hal_c_REF_4 */
    /* #Violation: fc_hal_c_REF_5 */
    Assert((boolean)CHECK_FC_BASE(pFc));
#endif
    pFc->FCINT.B.INTST = 1U;
}

/* #Violation: fc_hal_c_REF_2 */
boolean Fc_Hal_SetBoundaryFlag(FC_MODULE *const pFc, Fc_BoundaryFlagControl ctrl)
{
    boolean ret;
    /* #Violation: fc_hal_c_REF_1 */
    FC_BDFL fcBdflVal;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: fc_hal_c_REF_4 */
    /* #Violation: fc_hal_c_REF_5 */
    Assert((boolean)(CHECK_FC_BASE(pFc)));
#endif
    ret = TRUE;
    fcBdflVal.U = pFc->BDFL.U;
    if(FC_BOUNDARYFLAGCONTROL_HARDWARE == ctrl)
    {
        fcBdflVal.B.BFHW = 1U;
    }
    else
    {
        fcBdflVal.B.BFHW = 0U;
        fcBdflVal.B.BFSW = (uint32)ctrl;
    }
    pFc->BDFL.U = fcBdflVal.U;
    ret = Fc_Register_ReadBack_Check(ret, (fcBdflVal.U & FC_BDFL_MASK), (pFc->BDFL.U & FC_BDFL_MASK));
    return ret;
}

/* #Violation: fc_hal_c_REF_2 */
boolean Fc_Hal_SetReferenceValue(FC_MODULE *const pFc, uint16 referVal)
{
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: fc_hal_c_REF_4 */
    /* #Violation: fc_hal_c_REF_5 */
    Assert((boolean)(CHECK_FC_BASE(pFc)));
    /* #Violation: fc_hal_c_REF_3 */
    Assert((boolean)(referVal < 1024U));
#endif
    ret = TRUE;
    pFc->REFVAL.B.REFVALSW = referVal;
    ret = Fc_Register_ReadBack_Check(ret, referVal, pFc->REFVAL.B.REFVALSW);
    return ret;
}

/* #Violation: fc_hal_c_REF_2 */
boolean Fc_Hal_SetRampValue(FC_MODULE *const pFc, uint16 refVal0, uint16 refVal1)
{
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: fc_hal_c_REF_4 */
    /* #Violation: fc_hal_c_REF_5 */
    Assert((boolean)(CHECK_FC_BASE(pFc)));
    /* #Violation: fc_hal_c_REF_3 */
    Assert((boolean)(refVal0 < 1024U));
    /* #Violation: fc_hal_c_REF_3 */
    Assert((boolean)(refVal1 < 1024U));
#endif
    ret = TRUE;
    pFc->RAMP0.B.RAMPCMP0 = refVal0;
    ret = Fc_Register_ReadBack_Check(ret, refVal0, pFc->RAMP0.B.RAMPCMP0);
    pFc->RAMP1.U = refVal1;
    ret = Fc_Register_ReadBack_Check(ret, refVal1, pFc->RAMP1.U);
    return ret;
}

/* #Violation: fc_hal_c_REF_2 */
boolean Fc_Hal_GetCompareStatus(const FC_MODULE *const pFc)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: fc_hal_c_REF_4 */
    /* #Violation: fc_hal_c_REF_5 */
    Assert((boolean)(CHECK_FC_BASE(pFc)));
#endif
    /* #Violation: fc_hal_c_REF_3 */
    return (boolean)(pFc->BDFL.B.CRVF != 0U);
}

/* #Violation: fc_hal_c_REF_2 */
boolean Fc_Hal_GetCompareResult(const FC_MODULE *const pFc)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: fc_hal_c_REF_4 */
    /* #Violation: fc_hal_c_REF_5 */
    Assert((boolean)(CHECK_FC_BASE(pFc)));
#endif
    /* #Violation: fc_hal_c_REF_3 */
    return (boolean)(pFc->BDFL.B.CR != 0U);
}

/* #Violation: fc_hal_c_REF_7 */
#define FC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: fc_hal_c_REF_8 */
#include "Fc_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
