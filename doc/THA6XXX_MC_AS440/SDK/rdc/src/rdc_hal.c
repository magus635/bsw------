/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    rdc_hal.c
 * Author:      00915
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: RDC hardware abstraction layer source file.
 *              This file contains implementations for RDC hardware abstraction layer.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #rdc_hal_c_REF_1:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core, Boolean can only be represents as uint8.
*
* #rdc_hal_c_REF_2:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
* #rdc_hal_c_REF_3:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
* #rdc_hal_c_REF_4:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
* #rdc_hal_c_REF_5:MISRAC2012-Rule-15.7;
* Justification: MISRAC2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
* #rdc_hal_c_REF_6:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #rdc_hal_c_REF_7:MISRAC2012-Dir-4.3;
* Justification: The interface is called by the application layer.
*
* #rdc_hal_c_REF_10:MISRAC2012-Rule-8.7; 
* Justification:The function is used by other file.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "rdc_hal.h"
#include "Platform_Types.h"
#include "rdc_register.h"
#include "rdc_std.h"
#include "rcc_hal.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
#define RDC_23TH_POWER_OF2 (8388608.0f)
#define RDC_2_PI (6.28318530718f)
#define FLOAT32_MAX (3.40282347e+38f)
#define FLOAT32_MIN (-3.40282347e+38f)

#if defined(THA6_THA6412)
#define SINT18_MAX (131071)
#define SINT18_MIN (-131072)
#endif
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/

#define RDC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: rdc_hal_c_REF_6 */
#include "Rdc_MemMap.h"

/* #Violation: rdc_hal_c_REF_2 */
boolean Rdc_Hal_Init(RDC_MODULE *const pModule, const Rdc_InitialConfig *const pConfig)
{
    boolean ret = TRUE;
    
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pModule is null pointer */
    /* #Violation: rdc_hal_c_REF_3 */
    /* #Violation: rdc_hal_c_REF_4 */
    Assert((boolean)(CHECK_RDC_BASE(pModule)));
    /* Check if the pConfig is null pointer */
    /* #Violation: rdc_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* Check if the dpllKp is in the normal range */
    /* #Violation: rdc_hal_c_REF_1 */
    Assert((boolean)((pConfig->dpllKp <= 1.0f) && (pConfig->dpllKp >= 0.0f)));
    /* Check if the dpllKi is in the normal range */
    /* #Violation: rdc_hal_c_REF_1 */
    Assert((boolean)((pConfig->dpllKi <= 1.0f) && (pConfig->dpllKi >= 0.0f)));
    /* Check if the mainKp is in the normal range */
    /* #Violation: rdc_hal_c_REF_1 */
    Assert((boolean)((pConfig->mainKp <= 1.0f) && (pConfig->mainKp >= 0.0f)));
    /* Check if the mainKi is in the normal range */
    /* #Violation: rdc_hal_c_REF_1 */
    Assert((boolean)((pConfig->mainKi <= 1.0f) && (pConfig->mainKi >= 0.0f)));
    /* Check if the gainOffset is in the normal range */
    /* #Violation: rdc_hal_c_REF_1 */
    Assert((boolean)((pConfig->gainOffset < 2.0f) && (pConfig->gainOffset > 0.0f)));
#endif /* INPUT_ARG_DETECT */

    /* Set PI parameters for carrier recovery loop */
    ret &= Rdc_Std_SetDpllPidConfig(pModule, pConfig->dpllKp, pConfig->dpllKi);
    /* Set the PI parameters of the main loop */
    ret &= Rdc_Std_SetMainPidConfig(pModule, pConfig->mainKp, pConfig->mainKi);
 
    /* Set the excitation carrier output mode is PWM or SVPWM */
    ret &= Rdc_Std_ExcitationCarrierMode(pConfig->excitationCarrierMode);
    /* Set the excitation carrier frequency */
    ret &= Rdc_Std_SetExcitationCarrierFreq(pConfig->excitationCarrierFreq);
    /* Hardware mode*/
    if(pConfig->excitationCarrierMode == RDC_EXCITATIONCARRIERMODE_HARDWARE)
    {
        ret &= Rdc_Std_SetWaveMode(pConfig->waveMode);
    }
    /* Software mode*/
    else
    {
        /* Software mode only supports SPWM mode */
        ret &= Rdc_Std_SetWaveMode(RDC_WAVEMODECONFIG_SPWM);
        ret &= Rdc_Std_SetSoftExcitationCarrierDuty(pConfig->points);
    }

    ret &= Rdc_Std_SelSignalType(pModule, pConfig->signalType);

    if(pConfig->signalType == RDC_SIGTYPE_MIX)  /* resolver signal */
    {
        /* Set carrier recovery data source */
        ret &= Rdc_Std_SetCarrierRecoverSource(pModule, pConfig->carrierRecoverSource);
    }

#if defined(THA6_THA6412)
    ret &= Rdc_Hal_SetReferencePhase(pModule, pConfig->isEnableRefPhase, pConfig->refPhase);
#endif

    ret &= Rdc_Std_SetExcitationCarrierEn(pConfig->excitationCarrierEn);
    /* Set RDC trigger source */
    ret &= Rdc_Std_SetTriggerSource(pModule, pConfig->triggerSource);
    /* Set RDC data source */
    ret &= Rdc_Std_SetDataSource(pModule, pConfig->i_dataSource,pConfig->q_dataSource);
    /* Set sampling rate configuration */
    ret &= Rdc_Std_SetSamplingRate(pModule, pConfig->samplingRate);
    
    /* Set RDC data compensation parameters */
    ret &= Rdc_Std_SetDcCompensation(pModule, pConfig->dcCompensationEn, pConfig->dcOffsetI, pConfig->dcOffsetQ);
    ret &= Rdc_Std_SetGainCompensation(pModule, pConfig->gainCompensationEn, pConfig->gainOffset);
    ret &= Rdc_Std_SetHighPassCompensation(pModule, pConfig->highPassCompensationEn, pConfig->filterCutoffFrequency);

    return ret;
}


/* #Violation: rdc_hal_c_REF_2 */
Rcc_ErrorFlag Rdc_Hal_DeInit(Rdc_IdxSel idxSel)
{
    Rcc_ErrorFlag deInitFlag;

    switch (idxSel)
    {
    case RDC_IdxSel_0:
        deInitFlag = Rcc_Hal_TrigModuleRst(RCC_MODULERST_RDC0);
        break;
#if defined(THA6_THA6412)
    case RDC_IdxSel_1:
        deInitFlag = Rcc_Hal_TrigModuleRst(RCC_MODULERST_RDC1);
        break;
    case RDC_IdxSel_All:
        deInitFlag = Rcc_Hal_TrigModuleRst(RCC_MODULERST_RDC1);
        if (RCC_ERRORFLAG_SUCCESS == deInitFlag)
        {
            deInitFlag = Rcc_Hal_TrigModuleRst(RCC_MODULERST_RDC0);
        }
        break;
#endif /* THA6_THA6412 */
    default:
        deInitFlag = RCC_ERRORFLAG_NULLPTR;
        break;
    }

    return deInitFlag;
}

/* #Violation: rdc_hal_c_REF_2 */
float32 Rdc_Hal_ConvertToSpeed(sint32 speed, float32 fs)
{
    float64 f_speed;

    f_speed = (float64)speed;
    f_speed = f_speed / RDC_23TH_POWER_OF2 / RDC_2_PI * fs;

    if((f_speed > FLOAT32_MAX) || (f_speed < FLOAT32_MIN))
    {
        f_speed = (f_speed > 0.0F) ? (float64)FLOAT32_MAX : (float64)FLOAT32_MIN;
    }

    return (float32)f_speed;

}

#if defined(THA6_THA6412)
/* #Violation: rdc_hal_c_REF_7 */
/* #Violation: rdc_hal_c_REF_10 */
boolean Rdc_Hal_SetReferencePhase(RDC_MODULE *const pRdc, boolean enable, sint32 phaseEstimation)
{
    boolean ret;
    sint32 value;
    
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pRdc is null pointer */
    /* #Violation: rdc_hal_c_REF_3 */
    /* #Violation: rdc_hal_c_REF_4 */
    Assert((boolean)(CHECK_RDC_BASE(pRdc)));
    /*Check if the phaseEstimation less than 0x3FFFFU*/
    /* #Violation: rdc_hal_c_REF_1 */
    Assert((boolean)(SINT18_MIN <= phaseEstimation));
    /* #Violation: rdc_hal_c_REF_1 */
    Assert((boolean)(SINT18_MAX >= phaseEstimation));
#endif /* INPUT_ARG_DETECT */

    ret = TRUE;

    pRdc->REFPHASEEN.B.EN = enable;
    ret = Rdc_Register_ReadBack_Check(ret, (uint32)enable, pRdc->REFPHASEEN.B.EN);

    if((phaseEstimation > SINT18_MAX) || (phaseEstimation < SINT18_MIN))
    {
        value = (phaseEstimation > 0) ? SINT18_MAX : SINT18_MIN;
        pRdc->REFPHASE.B.PHASE = value;
        /* #Violation: rdc_hal_c_REF_3 */
        ret = Rdc_Register_ReadBack_Check(ret, (uint32)value, (uint32)pRdc->REFPHASE.B.PHASE);
    }
    else
    {
        pRdc->REFPHASE.B.PHASE = phaseEstimation;
        /* #Violation: rdc_hal_c_REF_3 */
        ret = Rdc_Register_ReadBack_Check(ret, (uint32)phaseEstimation, (uint32)pRdc->REFPHASE.B.PHASE);
    }
    return ret;
}

#endif /* THA6_THA6412 */

#define RDC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: rdc_hal_c_REF_6 */
#include "Rdc_MemMap.h"

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
