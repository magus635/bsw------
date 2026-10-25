/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    tslp_hal.c
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all implementations of requirements of TSENSOR module.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#tsensor_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification:reason 1503 Reserved API for user access.
*
*#tsensor_hal_c_REF_2:MISRAC2012-Rule-2.5;
* Justification:reason 1534 The macros are reserved for upper layers
*
*#tsensor_hal_c_REF_3:MISRAC2012-Rule-10.5;
* Justification:reason 4304 Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8.
*
*#tsensor_hal_c_REF_4:MISRAC2012-Rule-19.2;
* Justification:reason 0759 Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by code review.
*
*#tsensor_hal_c_REF_5:MISRAC2012-Rule-11.4;
* Justification:reason 0303 Converting integers to object pointers to reduce register access complexity.
*
*#tsensor_hal_c_REF_6:MISRAC2012-Rule-10.5;
* Justification:reason 3469 Function like macros are used to reduce code complexity.
*
*#tsensor_hal_c_REF_7:MISRAC2012-Rule-20.1;
*Justification: Imposes the specification of the section in which certain parts of the driver must be placed.
*
*#tsensor_hal_c_REF_8:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
* #tsensor_hal_c_REF_9:MISRAC2012-Rule-2.2
* Justification:Code review ensures the compliance with rule.
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "tsensor_hal.h"
#include "safewdt_hal.h"
#include "Platform_Types.h"
#include "rcc_hal.h"
#include "tha6_cfg.h"
#include "Platform_Types.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /*INPUT_ARG_DETECT*/
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* ^INTERVAL_MIN^ Minimum sampling interval */
/* #Violation: tsensor_hal_c_REF_2 */
#define INTERVAL_MIN (0x7D0U)
/* ^LIM_MASK^ Threshold mask */
/* #Violation: tsensor_hal_c_REF_2 */
#define LIM_MASK (0xFFFU)
/* ^TSENSOR_AHB_CLK_MHZ_MASK^ 1MHz AHB clock frequency mask */
#define TSENSOR_AHB_CLK_MHZ_MASK ((uint32)1000000U)

/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
#define TSENSOR_START_SEC_CODE_ASIL_D_GLOBAL
#include "Tsensor_MemMap.h"
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: tsensor_hal_c_REF_1 */
boolean Tsensor_Hal_Init(TSENSOR_MODULE *const pTsensor, const Tsensor_Config *const pConfig)
{
    /* #Violation: tsensor_hal_c_REF_4 */
    TSENSOR_SAMP regSamp;
    /* #Violation: tsensor_hal_c_REF_4 */
    TSENSOR_LIM regLim;
    float32 offsetValue;
    float32 slopeValue;
    float32 tempUpper;
    float32 tempLower;
    Rcc_ErrorFlag rcc_errflag;
    boolean retSts;
    retSts = TRUE;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Ckeck the input parameter pointer is not NULL pointer */
    /* #Violation: tsensor_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* Check whether the module pointer is a valid pointer */
    /* Check Tsensor base address */
    /* #Violation: tsensor_hal_c_REF_5 */
    /* #Violation: tsensor_hal_c_REF_8 */
    Assert((boolean)(CHECK_TSENSOR_BASE(pTsensor)));
    /* Ckeck the input parameter more than INTERVAL_MIN */
    /* #Violation: tsensor_hal_c_REF_3 */
    Assert((boolean)(INTERVAL_MIN <= pConfig->interval));
    /* Check the high limit value more than the low limit value */
    /* #Violation: tsensor_hal_c_REF_3 */
    Assert((boolean)(pConfig->highLimit > pConfig->lowLimit));
#endif
    /* #Violation: tsensor_hal_c_REF_9 */
    tempUpper = 0.00F;
    /* #Violation: tsensor_hal_c_REF_9 */
    tempLower = 0.00F;
    /* Read calibration offset and slope */
    offsetValue = pTsensor->OFFSET.F;
    slopeValue = pTsensor->SLOPE.F;
    /* The SENSOR module is TSENSOR0 */
    /* #Violation: tsensor_hal_c_REF_5 */
    if(TSENSOR0 == pTsensor)
    {
        /* Set TSENSOR0 working clock */
        retSts &= Rcc_Hal_SetModuleClk(RCC_MODULECLKTYPE_TSENSOR0CLK, RCC_MODULECLK_ENABLE);
        /* Trigger TSENSOR0 to module reset */
        rcc_errflag = Rcc_Hal_TrigModuleRst(RCC_MODULERST_TSENSOR0);
        if(rcc_errflag == RCC_ERRORFLAG_FAIL)
        {
            retSts &= FALSE;
        }       
    }
    /* The SENSOR module is TSENSOR1 */
    else
    {
        /* Set TSENSOR1 working clock */
        retSts &= Rcc_Hal_SetModuleClk(RCC_MODULECLKTYPE_TSENSOR1CLK, RCC_MODULECLK_ENABLE);
        /* Trigger TSENSOR1 to module reset */
        rcc_errflag =Rcc_Hal_TrigModuleRst(RCC_MODULERST_TSENSOR1);
        if(rcc_errflag == RCC_ERRORFLAG_FAIL)
        {
            retSts &= FALSE;
        }
    }
    /* Disable TSENSOR module */
    pTsensor->SAMP.U = 0U;
    /* Register readback check */
    retSts = Tsensor_Register_ReadBack_Check(retSts, pTsensor->SAMP.U, 0U);
    regSamp.U = pTsensor->SAMP.U;
    regSamp.B.AVRTIMES = (uint32)pConfig->avrTimes;                          /* Set the number of sampling */
    /* Get APB clock frequency */
    regSamp.B.USDIV = (uint32)Rcc_Hal_GetAhbApbClkFreq() / TSENSOR_AHB_CLK_MHZ_MASK; 
    regSamp.B.INTEN = (uint32)pConfig->intEn;                                /* Interrupt enable */
    pTsensor->SAMP.U = regSamp.U;
    /* Register readback check */
    retSts = Tsensor_Register_ReadBack_Check(retSts, pTsensor->SAMP.U, regSamp.U);
    /* Set the temperature sampling time interval */
    pTsensor->INTERVAL.B.INTERVAL = (uint32)pConfig->interval;
    /* Register readback check */
    retSts = Tsensor_Register_ReadBack_Check(retSts, pTsensor->INTERVAL.B.INTERVAL, pConfig->interval);
    regLim.U = pTsensor->LIM.U;
    
    /* If the slop value is not zero */
    /* #Violation: tsensor_hal_c_REF_8 */
    if (!IS_ZERO_FLT(slopeValue))
    {
        tempUpper = (pConfig->highLimit - offsetValue) / slopeValue;
        tempLower = (pConfig->lowLimit - offsetValue) / slopeValue;
        regLim.B.UPPER = (uint32)tempUpper; /* Configure high threshold */
        regLim.B.LOWER = (uint32)tempLower;  /* Configure low threshold */
        pTsensor->LIM.U = regLim.U;
        /* Register readback check */
        retSts = Tsensor_Register_ReadBack_Check(retSts, pTsensor->LIM.U, regLim.U);

    }
    else
    {
        retSts = FALSE;
    }
    /* Alarm mask is unmasking */
    if(TSENSOR_ALARM_UNMASK == pConfig->alarmMask)
    {
        DISABLE_ALL_INTERRUPTS();
        /* Clear safewdt ENDINIT */
        retSts &= Safewdt_Hal_ClearSafetyEndinit();

        pTsensor->MASK.B.ALMMSK = 0U; /* Select whether to mask alarm signals */
        /* Set safewdt ENDINIT */
        retSts &= Safewdt_Hal_SetSafetyEndinit();
        ENABLE_ALL_INTERRUPTS();
    }

    /* TSENSOR use analog output pulse/dout signals */
    pTsensor->ANGCFG.U = 0U;

    /* Start temperature sampling */
    regSamp.U = pTsensor->SAMP.U;
    regSamp.B.EN = 1U;
    pTsensor->SAMP.U = regSamp.U;
    /* Register readback check */
    retSts = Tsensor_Register_ReadBack_Check(retSts, pTsensor->SAMP.U, regSamp.U );
    return retSts;
}

/* #Violation: tsensor_hal_c_REF_1 */
void Tsensor_Hal_GetResult(const TSENSOR_MODULE *const pTsensor, float32 *const pTemperature)
{
    /* #Violation: tsensor_hal_c_REF_4 */
    TSENSOR_RESULT rst;
    float32 offsetValue;
    float32 slopeValue;

#if(STD_ON == INPUT_ARG_DETECT)
    /* Check whether the module pointer is a valid pointer */
    /* Check Tsensor base address */
    /* #Violation: tsensor_hal_c_REF_5 */
    /* #Violation: tsensor_hal_c_REF_8 */
    Assert((boolean)(CHECK_TSENSOR_BASE(pTsensor)));
    /* Ckeck the input parameter pointer is not NULL pointer */
    /* #Violation: tsensor_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pTemperature));
#endif

    /* Read temperature code sample result */
    rst.U = pTsensor->RESULT.U;

    offsetValue = pTsensor->OFFSET.F;
    slopeValue = pTsensor->SLOPE.F;

    /* Get temperature result */
    *pTemperature = (float32)(slopeValue * (float32)(rst.B.RES)) + offsetValue;
}

#define TSENSOR_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: tsensor_hal_c_REF_7 */
#include "Tsensor_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
