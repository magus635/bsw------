/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    saradc_hal.c
 * Author:      30037
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of SARADC module.
 *********************************************************************************************************************/

/*
*#Violation Summary
*#saradc_hal_c_REF_1:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#saradc_hal_c_REF_2:MISRAC2012-Rule-19.2;
* Justification: Using unions for bit-field access to registers.
*
*#saradc_hal_c_REF_3:MISRAC2012-Dir-1.1;
* Justification: Inline assembly for CPU-specific operations.
*
*#saradc_hal_c_REF_4:MISRAC2012-Dir-4.3;
* Justification: Mixing inline assembly with C code reduces code complexity.
*
*#saradc_hal_c_REF_5:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#saradc_hal_c_REF_6:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#saradc_hal_c_REF_7:EXP37-C;
* Justification: The Macro need to be used in different chip.
*
*#saradc_hal_c_REF_8:MISRAC2012-Rule-20.1;
*Justification: Imposes the specification of the section in which certain parts of the driver must be placed.
*
*#saradc_hal_c_REF_9:MISRAC2012-Rule-10.5
*Justification:Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
*#saradc_hal_c_REF_10:MISRAC2012-Rule-1.2;
* Justification: Inline assembly for CPU-specific operations.
*
*#saradc_hal_c_REF_11:MISRAC2012-Dir-4.2;
*Justification:Inline assembly for CPU-specific operations.
*
* #saradc_hal_c_REF_12:MISRAC2012-Rule-2.3;
* Justification:The members of the type are used in configuration-generated code.
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "saradc_hal.h"
#include "Platform_Types.h"
#include "saradc_register.h"
#include "cpuwdt_hal.h"
#include "rcc_hal.h"
#include "saradc_std.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
#define SARADC_ADCCNTSTS_TIMEOUT_MAX     (0x2A800U)
#define SARADC_DIVIDER_MAX               (0x9FU)
#define SARADC_CLEAR_INTERRUPT_VAL       (0xFFFFU)
#define SARADC_QINCFG_MASK               (0xFFFFU)
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
#define ADC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Adc_MemMap.h"
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: saradc_hal_c_REF_6 */
/* #Violation: saradc_hal_c_REF_4 */
boolean Saradc_Hal_InitModule(SARADC_MODULE *const pSaradc, const Saradc_ModuleConfig *const pConfig)
{
    uint8 num;
    boolean retSts;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
    /* Check whether the configure parameter pointer is null pointer */
    /* #Violation: saradc_hal_c_REF_9 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* Check whether analog divider less than SARADC_DIVIDER_MAX */
    /* #Violation: saradc_hal_c_REF_9 */
    Assert((boolean)(pConfig->divider <= SARADC_DIVIDER_MAX));
#endif

    retSts = TRUE;
    Saradc_RequestSource const reqSource[SARADC_QUEUE_NUM] = {
        SARADC_REQUESTSOURCE_QUEUE0, 
        SARADC_REQUESTSOURCE_QUEUE1,
        SARADC_REQUESTSOURCE_QUEUE2
    };

    /* Config queue Config specified queue arbiter priority startmode refill queue enable/disable and diagnostic
    option */
    /* Set Saradc QUEUE0 ~ 2 */
    for(num = 0; num < SARADC_QUEUE_NUM; num++)
    {   
        /* Queue is enable  */
        if(1U == pConfig->requestQueueConfig[num].enable)
        {
            /* Bound the maximum number num can take */
            retSts &= Saradc_Std_SetQueueCommonConfig(pSaradc, &pConfig->requestQueueConfig[num], reqSource[num]);
        }
    }
    /* Enable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();
    
    /* Select saradc sample time */
    retSts &= Saradc_Std_SetSampleTime(pSaradc, pConfig->sampleTime);

    /* Set saradc synchronous converter source */
    retSts &= Saradc_Std_SetConverterSource(pSaradc, pConfig->converterSource);

    /* Select saradc converter resolution */
    retSts &= Saradc_Std_SetResolution(pSaradc, pConfig->resolution);

    /* Select saradc converter divider */
    retSts &= Saradc_Std_SetDivider(pSaradc, pConfig->divider);

    /* Enable SARADC analog IP */
    retSts &= Saradc_Std_AnalogConvertControl(pSaradc, 1U);
    /* Set cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    
#if defined (THA6_THA6206)
    /* #Violation: saradc_hal_c_REF_12 */
    volatile uint32 delayCnt = 267U; 
    /* Wait 2us for ADC initialization to complete. */
    /* #Violation: saradc_hal_c_REF_11 */
    ASM_VOLATILE(
        "1:               \n"
        " SUBS %0, %0, #1 \n"
        " NOP             \n"
#ifdef __TASKING__
        " BNE 1p          \n" 
#else
        " BNE 1b          \n"
#endif
        : "+r" (delayCnt)
        :                        
        : "cc"
    );
#endif
    return retSts;
}

/* #Violation: saradc_hal_c_REF_6 */
/* #Violation: saradc_hal_c_REF_4 */
boolean Saradc_Hal_DeInitModule(SARADC_MODULE *const pSaradc)
{
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_CHCTRL chctrlVla;
    Rcc_ModuleRst moduleAdcRst;
    Rcc_ErrorFlag errorFlg;
    uint8 i;
    uint32 channelID;
    uint32 channelResult;
    boolean retSts;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    retSts = TRUE;
    /* Get reset SARADC index nodule */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    moduleAdcRst = GET_SARADC_RCC_RST_NUM(pSaradc);
    /* Disable queue interrupt and external trigger and internal timer */
    /* Set SARADC QUEUE0 ~ 2 */
    for (i=0U; i<SARADC_QUEUE_NUM; i++)
    {   
        /* Disable internal timer */
        pSaradc->QTRICTRL[i].B.TRIMODE = 0U;
        /* Disable external trigger */
        pSaradc->QMODE[i].B.EXTTRIEN = 0U;
        /* Disable gate */
        pSaradc->QMODE[i].B.GATEEN = 0U;
        /* Flush queue */
        pSaradc->QMODE[i].B.FLUQU = 1U;
        /* Disable External rtigger timer */
        pSaradc->QREQTM[i].B.EXTTRITEN = 0U;
        /* Disable source interrupt */
        pSaradc->QINCFG[i].B.QIEN = 0U;
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->QTRICTRL[i].B.TRIMODE, 0U);
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->QMODE[i].U, 0U);
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->QREQTM[i].B.EXTTRITEN, 0U);
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->QINCFG[i].B.QIEN, 0U);
    }
    
    
    /* Traverse SARADC all the channels */
    for (channelID = 0U; channelID < SARADC_CHANNEL_NUM; channelID++)
    {
        chctrlVla.U = pSaradc->CHCTRL[channelID].U;
        chctrlVla.U &= (uint32)(~(0x700003U));
        /* Disable HDI and channel interrupt */
        pSaradc->CHCTRL[channelID].U = chctrlVla.U;
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CHCTRL[channelID].U, chctrlVla.U);
    }
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();
   
    /* Traverse SARADC all the result register */
    for (channelResult = 0U; channelResult < SARADC_RESULT_REG_NUM; channelResult++)
    {
        /* Disable result interrupt */
        pSaradc->RESCTRL[channelResult].B.NRINTEN = 0U;
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->RESCTRL[channelResult].B.NRINTEN, 0U);
    }
    
    /* Traverse SARADC all the channels */
    for (channelID = 0U; channelID < SARADC_CHANNEL_NUM; channelID++)
    {   
        /* Use global related register */
        if(pSaradc->CHCTRL[channelID].B.RESSTTAR == 1U)
        {   
            /* Disable global DMA */
            pSaradc->GLODMA.U = 0U;
            /* Disable global result interrupt */
            pSaradc->GLOINTCTRL.B.GMASK = 3U;
            /* Check register readback check value meet expectation */
            retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->GLODMA.U, 0U);
            /* Check register readback check value meet expectation */
            retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->GLOINTCTRL.B.GMASK, 3U);
        }
    }
    /* Set cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    /* Disable DMA translate SARADC */
    pSaradc->DMAEN.U = 0U;
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->DMAEN.U, 0U);
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();
    /* Disable analog part of saradc */
    retSts &= Saradc_Std_AnalogConvertControl(pSaradc, FALSE);
    /* Set cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();

    /* #Violation: saradc_hal_c_REF_3 */
    /* #Violation: saradc_hal_c_REF_10 */
    /* #Violation: saradc_hal_c_REF_11 */
    DSB();

    /* SARADC module reset */
    errorFlg = Rcc_Hal_TrigModuleRst((Rcc_ModuleRst)moduleAdcRst);
    /* Flag is error */
    if(RCC_ERRORFLAG_SUCCESS != errorFlg)
    {
        retSts &= FALSE;
    }
    return retSts;
}

/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_OpenCalibration(SARADC_MODULE *const pSaradc)
{
    boolean retSts;
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_ANACFG anacfgVla;
    /* #Violation: saradc_hal_c_REF_2 */
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_ARBCTRL arbctrlVal, arbctrlValBack;
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_QMODE qmodeBack;
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_RESCTRL resctrlBack;
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_SAMCTRL samctrlBack;
    uint32 timeoutCnt;
    uint32 CalcNums;
    uint32 resultVal;
    sint32 offsetVal;
    uint32 restemp;
    uint32 maskBits;
    retSts = TRUE;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    /* reacd ARBCTRL and QMODE[0] to tempt variable */
    arbctrlValBack.U = pSaradc->ARBCTRL.U;
    qmodeBack.U = pSaradc->QMODE[0].U;
    resctrlBack.U = pSaradc->RESCTRL[0].U;
    samctrlBack.U = pSaradc->SAMCTRL.U;

    offsetVal = 0;
    anacfgVla.U = pSaradc->ANACFG.U;

    anacfgVla.B.CALIC = 1U;
    anacfgVla.B.OFFSET = 0U;
    anacfgVla.B.DISHEN = 0U;
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();

    /* Config calibration */
    pSaradc->ANACFG.U = (uint32)anacfgVla.U;
    /* Config calibration sample time */
    pSaradc->SAMCTRL.U = (uint32)9U;
    /* Set cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    maskBits = (~(0x80000002U));
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, (pSaradc->ANACFG.U & maskBits), (anacfgVla.U & maskBits));
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->SAMCTRL.U, 9U);

    arbctrlVal.U = pSaradc->ARBCTRL.U;

    /* Set queue 0 priority */
    arbctrlVal.B.PRIOL0 = (uint32)SARADC_QUEUEPRIORITY_HIGH;
    /* Set queue 0 start mode */
    arbctrlVal.B.CONSMODE0 = (uint32)SARADC_STARTMODE_CANCELINJECTREPEAT;
    /* Arbitration queue 0 enable */
    arbctrlVal.B.ARBEN0 = (uint32)1U;

    pSaradc->ARBCTRL.U = arbctrlVal.U;
    /* Set always gating mode */
    pSaradc->QMODE[0].B.GATEEN = 1U;

    maskBits = (~(0x38F70000U));
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, (pSaradc->ARBCTRL.U & maskBits), (arbctrlVal.U & maskBits));
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->QMODE[0].B.GATEEN, 1U);
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();

    /* Set storage mode(overwrite/wait-for-read) */
    pSaradc->RESCTRL[0].B.WFRMODE = (uint32)1U;
    /* Set cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->RESCTRL[0].B.WFRMODE, 1U);
    /* Caculate 'SARADC_CALC_COUNTER' times */
    for (CalcNums = 0; CalcNums < SARADC_CALC_COUNTER; CalcNums++)
    {
        timeoutCnt = 0;
        /* Fill Channel to queue */
        pSaradc->QINCFG[0].U = 0x8FU;
        /* Trigger by software */
        pSaradc->QMODE[0].B.STRIGEN = 1U;
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->QINCFG[0].U, 0x8FU);
        /* Read and calculate result */
        do
        {
            timeoutCnt++;
            resultVal = pSaradc->RESULT[0].U;
            /* resultVal = 2048 -20; +13 -> 6'h33,  -20 -> 6'h14  DEBUG CODE */
        /* Result is invalid and timeing counting not overflow */
        }while (((resultVal & SARADC_RESULT_VALID) == 0U) && (timeoutCnt < SARADC_ADCCNTSTS_TIMEOUT_MAX));
        /* Timeing counting overflow */
        if(timeoutCnt >= SARADC_ADCCNTSTS_TIMEOUT_MAX)
        {
            retSts &= FALSE;
        }
        restemp = (resultVal & 0xFFFFU);
        offsetVal += ((sint32)2048U - (sint32)restemp);
    }

    /* Restore and configure calc and offsetVal */
    offsetVal = offsetVal / (sint32)SARADC_CALC_COUNTER;

    anacfgVla.B.OFFSET = (uint32)offsetVal;
    anacfgVla.B.CALIC = 0U;
    anacfgVla.B.DISHEN = 1U;
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();

    /* Enable calibration */
    pSaradc->ANACFG.U = (uint32)anacfgVla.U;
    pSaradc->RESCTRL[0].U = resctrlBack.U;
    pSaradc->SAMCTRL.U = samctrlBack.U;
    /* Set cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->RESCTRL[0].U, resctrlBack.U);
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->SAMCTRL.U, samctrlBack.U);
    maskBits = (~(0x80000002U));
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, (pSaradc->ANACFG.U & maskBits), (anacfgVla.U & maskBits));
    pSaradc->ARBCTRL.U  = arbctrlValBack.U;
    pSaradc->QMODE[0].U  = qmodeBack.U;
    maskBits = (~(0xF8FF1444U));
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, (pSaradc->ARBCTRL.U & maskBits), (arbctrlValBack.U & maskBits));
    maskBits = (~(0xFFFFFFECU));
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, (pSaradc->QMODE[0].U & maskBits), (qmodeBack.U & maskBits));

    return retSts;
}

/* #Violation: saradc_hal_c_REF_6 */
uint32 Saradc_Hal_GetInterruptStatus(const SARADC_MODULE *const pSaradc, Saradc_InterruptSource interruptSource)
{
    uint32 status;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    /* Interrupt source is QUEUE */
    if(SARADC_INTERRUPTSOURCE_QUEUE == interruptSource)
    {
        /* Get all source interrupt status */
        status = pSaradc->SINTCTRL.U;
    }
    /* Interrupt source is channel */
    else if(SARADC_INTERRUPTSOURCE_CHANNEL == interruptSource)
    {
        /* Get all channel interrupt status */
        status = pSaradc->CINTCTRL.U;
    }
    /* Interrupt source is result register */
    else
    {
        /* Get all result interrupt status */
        status = pSaradc->RINTCTRL.U;
    }

    return status;
}

/* #Violation: saradc_hal_c_REF_6 */
void Saradc_Hal_ClearInterruptStatus(SARADC_MODULE *const pSaradc, Saradc_InterruptSource interruptSource,
                                     uint32 interruptID)
{
    uint32 intflg;
    uint8 checkCnt;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
    /* Check whether clear intreeupt out of range */
    /* #Violation: saradc_hal_c_REF_9 */
    Assert((boolean)(interruptID <= SARADC_CLEAR_INTERRUPT_VAL));
#endif
    checkCnt = 5U;
    /* Interrupt source is QUEUE */
    if(SARADC_INTERRUPTSOURCE_QUEUE == interruptSource)
    {
        do
        {
            /* Clear all source interrupt status */
            pSaradc->SINTCLR.U = interruptID;
            /* Readback and check wether source interrupt status was cleared */
            intflg =  (pSaradc->SINTCTRL.U & interruptID);
            checkCnt--;
        /* flag not equal to 0 and execute count not equal to 0 */
        }while ((0U != intflg) && (0U != checkCnt));         
    }
    /* Interrupt source is channel */
    else if(SARADC_INTERRUPTSOURCE_CHANNEL == interruptSource)
    {
        do
        {
            /* Clear all channel interrupt status */
            pSaradc->CINTCLR.U = interruptID;
            /* Readback and check and check wether channel interrupt status was cleared */
            intflg =  (pSaradc->CINTCTRL.U & interruptID);
            checkCnt--;
        /* flag not equal to 0 and execute count not equal to 0 */
        }while ((0U != intflg) && (0U != checkCnt));
    }
    /* Interrupt source is result register */
    else
    {
        do
        {
            /* Clear all result interrupt status */
            pSaradc->RINTCLR.U = interruptID;
            /* Readback and check and check wether result interrupt status was cleared */  
            intflg =  (pSaradc->RINTCTRL.U & interruptID);
            checkCnt--;
        /* flag not equal to 0 and execute count not equal to 0 */
        }while ((0U != intflg) && (0U != checkCnt));
    }
}

/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_InitChannel(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID,
                            const Saradc_ChannelConfig *const pchannelConfig)
{
    boolean retSts;
    retSts = TRUE;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    /* Input parameter is not NULL pointer */
    if(NULL_PTR != pchannelConfig)
    {
       /* Channel result select */
       retSts &= Saradc_Std_SetStoreResult(pSaradc, channelID, pchannelConfig->channelResult);
        /* Disable all interrupt */
        DISABLE_ALL_INTERRUPTS();
        /* Clear cpuwdt ENDINIT */
        retSts &= Cpuwdt_Hal_ClearEndinit();
 
        /* Channel storage mode config */
        retSts &= Saradc_Std_SetStorageMode(pSaradc, pchannelConfig->channelResult, pchannelConfig->storageMode);
        /* Set the channel conversion result left/right alignment */
        retSts &= Saradc_Std_SetAlign(pSaradc, pchannelConfig->channelResult, pchannelConfig->rightAlignedStorage);
        /* Set cpuwdt ENDINIT */
        retSts &= Cpuwdt_Hal_SetEndinit();
        /* Enable all interrupt */
        ENABLE_ALL_INTERRUPTS();
    
        /* Channel result dma enable control  */
        retSts &= Saradc_Std_EnableDma(pSaradc, pchannelConfig->channelResult, pchannelConfig->enableDma);

        /* Channel Boundary Range */
        retSts &= Saradc_Std_SetBoundaryRange(pSaradc, channelID, pchannelConfig->boundaryRange);

        /* Boundary Result control */
        retSts &= Saradc_Std_SetBoundaryResultCtrl(pSaradc, channelID, pchannelConfig->boundaryResultControl);

        /* Set the Synchronize conversion channel */
        retSts &= Saradc_Std_SetSynchronizeRequest(pSaradc, channelID, pchannelConfig->enableSynchronize);

        /* HDI enable */
        retSts &= Saradc_Std_SetHdiIf(pSaradc, channelID, pchannelConfig->hdiIfEn);
    }
    /* Input parameter is NULL pointer */
    else
    {
        retSts &= FALSE; 
    }
    return retSts;
}


/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_DynamicChannelConfig(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID,
                            const Saradc_DynaChannleConfig *const pChannelConfig)
{
    boolean retSts;
    retSts = TRUE;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_CHCTRL chctrlVal;
    chctrlVal.U = pSaradc->CHCTRL[channelID].U;
    /* Set channel store register */
    chctrlVal.B.RESSTREG = (uint32)pChannelConfig->channelResult;
    /* Config synchronous conversion request */
    chctrlVal.B.SYNCREQ = pChannelConfig->enableSynchronize;
    /* Boundary selection */
    chctrlVal.B.BOUNDRS = pChannelConfig->boundaryRange;
    /* Discard or Retain out of range result */
    chctrlVal.B.BOUNDDR = pChannelConfig->boundaryResultControl;
    /* Select HDI function */
    switch (pChannelConfig->hdiIfEn)
    {
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
        /* Select HDI FC function */
        case SARADC_HDI_FC:   
            chctrlVal.B.HDIFCEN = 0x1U;
            break;
        /* Select HDI RDC function */
        case SARADC_HDI_RDC:
            chctrlVal.B.HDIRDCEN = 0x1U;
            break;
#endif /* End THA6_THA6206 || THA6_THA6412 || THA6_THA6206D */
        /* Select HDI GTM function */
        case SARADC_HDI_GTM:
            chctrlVal.B.HDIGTMEN = 0x1U;
            break;
        case SARADC_HDI_OFF:
            chctrlVal.U &= ~(0x700000U);
            break;   
        default:
            retSts = FALSE;
            break;
    }
    pSaradc->CHCTRL[channelID].U = chctrlVal.U;
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CHCTRL[channelID].U, chctrlVal.U); 

    /* Channel result dma enable control  */
    retSts &= Saradc_Std_EnableDma(pSaradc, pChannelConfig->channelResult, pChannelConfig->enableDma);

    return retSts;
}


/* #Violation: saradc_hal_c_REF_6 */
uint16 Saradc_Hal_GetResult(const SARADC_MODULE *const pSaradc, Saradc_ChannelResult resultRegisterID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    /* Get result */
    return pSaradc->RESULT[resultRegisterID].B.CONRESULT;
}


/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_GetResultValid(const SARADC_MODULE *const pSaradc, Saradc_ChannelResult resultRegisterID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    /* Get result valid flag */
    return pSaradc->RESULT[resultRegisterID].B.VFLAG;
}

/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_FillQueue(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID, 
                                Saradc_RequestSource requestSource, uint32 option)
{
    boolean retSts;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
    /* Check the input parameter is not out of the range */
    /* #Violation: saradc_hal_c_REF_9 */
    Assert((boolean)(option <= SARADC_QINCFG_MASK));
#endif

    retSts = TRUE;
    /* Add channel to queue and set queue option */
    pSaradc->QINCFG[requestSource].U = (uint32)((uint32)channelID | option);
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->QINCFG[requestSource].U, ((uint32)channelID | option));
    return retSts;
}

/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_FlushQueue(SARADC_MODULE *const pSaradc, Saradc_RequestSource requestSource)
{
    boolean retSts;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    retSts = TRUE;
    /* Flush queue */
    pSaradc->QMODE[requestSource].U = SARADC_QUEUE_MODE_CLEAR;

    pSaradc->QTRICTRL[requestSource].U = (SARADC_QUEUE_CTRL_CLEAR | (uint32)0x808000U);
    pSaradc->QTRICTRL[requestSource].U = SARADC_QUEUE_CTRL_CLEAR; 

    pSaradc->QREQTM[requestSource].U = SARADC_QUEUE_TIME_CLEAR;
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, (pSaradc->QTRICTRL[requestSource].U & (~(0x101000U))), SARADC_QUEUE_CTRL_CLEAR);
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->QREQTM[requestSource].U, SARADC_QUEUE_TIME_CLEAR);
    return retSts;
}

/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_SetBoundary(SARADC_MODULE *const pSaradc, const Saradc_BoundaryConfig *const pBoundaryConfig)
{
    boolean retSts;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    retSts = TRUE;
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_FUNBOUND funboundVal;
    
    funboundVal.U = pSaradc->FUNBOUND.U;
    /* Input parameter is not NULL pointer */
    if(NULL_PTR != pBoundaryConfig)
    {
        /* Set boundary */
        funboundVal.B.BOUNDU = pBoundaryConfig->highBoundary;
        funboundVal.B.BOUNDL = pBoundaryConfig->lowBoundary;
        /* Disable all interrupt */
        DISABLE_ALL_INTERRUPTS();
        /* Clear cpuwdt ENDINIT */
        retSts &= Cpuwdt_Hal_ClearEndinit();
 
        pSaradc->FUNBOUND.U = funboundVal.U;
        /* Set cpuwdt ENDINIT */
        retSts &= Cpuwdt_Hal_SetEndinit();
        /* Enable all interrupt */
        ENABLE_ALL_INTERRUPTS();
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->FUNBOUND.U, funboundVal.U);
    }
    /* Input parameter is NULL pointer */
    else
    {
        retSts &= FALSE;
    }
    return retSts;
}

/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_SetTriggerGating(SARADC_MODULE *const pSaradc, const Saradc_GatingTriggerConfig *const pTriggerConfig,
                                 Saradc_RequestSource requestSource)
{
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_QTRICTRL qtrictrlVal;
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_QMODE qmodeVal;
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_QREQTM qreqtmVal;
    uint32 maskBits;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif

    boolean retSts;
    retSts = TRUE;

    qtrictrlVal.U = pSaradc->QTRICTRL[requestSource].U;
    qmodeVal.U = pSaradc->QMODE[requestSource].U;
    qreqtmVal.U = pSaradc->QREQTM[requestSource].U;

    /* Gating register write enable */
    qtrictrlVal.B.GSWE = 1U;
    /* Trigger register write enable */
    qtrictrlVal.B.TRWE = 1U;

    pSaradc->QTRICTRL[requestSource].U = qtrictrlVal.U;
    /* Input parameter is not NULL pointer */
    if(NULL_PTR != pTriggerConfig)
    {
        /* Set gating source */
        qtrictrlVal.B.GATESEL = (uint32)pTriggerConfig->gatingSource;
        /* Set gating mode */
        qmodeVal.B.GATEEN = (uint32)pTriggerConfig->gatingMode;
        /* Trigger mode isn't external trigger */
        if(SARADC_TRIGGERMODE_NOEXTERNALTRIGGER != pTriggerConfig->triggerMode)
        {
            /* Enable external trigger */
            qmodeVal.B.EXTTRIEN = 1U;
            /* Set trigger mode */
            qtrictrlVal.B.TRIMODE = (uint32)pTriggerConfig->triggerMode;
        }
        /* Set trigger source */
        qtrictrlVal.B.EXTTRISEL = (uint32)pTriggerConfig->triggerSource;

        pSaradc->QTRICTRL[requestSource].U = qtrictrlVal.U;

        pSaradc->QMODE[requestSource].U = qmodeVal.U;

        maskBits = (~(0x101000U));
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, (pSaradc->QTRICTRL[requestSource].U & maskBits), (qtrictrlVal.U & maskBits));
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->QMODE[requestSource].U, qmodeVal.U);
        /* Not select deactivate internal timer mode */
        if(SARADC_TIMERMODE_STOP != pTriggerConfig->timerConfig.timermode)
        {
            /* Sequence timer value set */
            qreqtmVal.B.SEQTVALUE = pTriggerConfig->timerConfig.sequence;
            /* External trigger timer enable */
            qreqtmVal.B.EXTTRITEN = pTriggerConfig->timerConfig.enable;
            /* Sequence timer mode set */
            qreqtmVal.B.SEQTMOD = (uint32)pTriggerConfig->timerConfig.timermode;

            pSaradc->QREQTM[requestSource].U = qreqtmVal.U;
            /* Check register readback check value meet expectation */
            retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->QREQTM[requestSource].U, qreqtmVal.U);
        }
    }
    /* Input parameter is NULL pointer */
    else
    {
        retSts &= FALSE;
    }
    return retSts;
}

/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_SetSourceInterrupt(SARADC_MODULE *const pSaradc, Saradc_InterruptMapping sourceInterruptMapping,
                                   Saradc_RequestSource requestSource)
{
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_SINTNP sintnpVal;
    boolean retSts;
    retSts = TRUE;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();

    /* Get SINTNP value */
    sintnpVal.U = pSaradc->SINTNP.U;
    /* Glear source interrupt mapping */
    sintnpVal.U &= (uint32)(~((uint32)0xFU << ((uint32)requestSource << 2U)));
    /* Set source interrupt mapping */
    sintnpVal.U |= (uint32)sourceInterruptMapping << ((uint32)requestSource << 2U);
    pSaradc->SINTNP.U = sintnpVal.U;
    /* Set cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->SINTNP.U, sintnpVal.U);
    return retSts;
}


/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_SetResultInterrupt(SARADC_MODULE *const pSaradc, Saradc_ChannelResult channelResult,
                                   const Saradc_InterruptConfig *const pResultInterruptConfig)
{
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_RINTNP0 pintnp0Val;
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_RINTNP1 pintnp1Val;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif

    boolean retSts;
    retSts = TRUE;
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();

    /* Set result interrupt enable */
    pSaradc->RESCTRL[channelResult].B.NRINTEN = (uint32)pResultInterruptConfig->interruptEnable;
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->RESCTRL[channelResult].B.NRINTEN, pResultInterruptConfig->interruptEnable);
    /* Select result register less than result8 */
    if(SARADC_CHANNELRESULT8 > channelResult)
    {
        /* Get RINTNP0 value */
        pintnp0Val.U = pSaradc->RINTNP0.U;
        /* Glear result mapping */
        pintnp0Val.U &= (uint32)(~((uint32)0xFU << ((uint32)channelResult << 2U)));
        /* Set result mapping */
        pintnp0Val.U |= (uint32)pResultInterruptConfig->interruptMapping << ((uint32)channelResult << 2U);
        pSaradc->RINTNP0.U = pintnp0Val.U;
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->RINTNP0.U, pintnp0Val.U);
    }
    /* Select result register more than or equal to result8 */
    else
    {
        /* Get RINTNP1 value */
        pintnp1Val.U = pSaradc->RINTNP1.U;
        /* Glear result mapping */
        pintnp1Val.U &= (uint32)(~((uint32)0xFU << ((uint32)((uint32)channelResult - (uint32)8U) << 2U)));
        /* Set result mapping */
        pintnp1Val.U |= (uint32)pResultInterruptConfig->interruptMapping << ((uint32)((uint32)channelResult - (uint32)8U) << 2U);
        pSaradc->RINTNP1.U = pintnp1Val.U;
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->RINTNP1.U, pintnp1Val.U);
    }
    /* Set cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    return retSts;
}

/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_SetChannelInterrupt(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID,
                                   const Saradc_ChannelInterruptConfig *const pChannelInterruptConfig)
{
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_CINTNP0 cintnp0Val;
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_CINTNP1 cintnp1Val;
    boolean retSts;
    retSts = TRUE;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    /* Set channel interrupt enable */
    pSaradc->CHCTRL[channelID].B.CHINTMODE = (uint32)pChannelInterruptConfig->channelInterruptEnable;
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CHCTRL[channelID].B.CHINTMODE, (uint32)pChannelInterruptConfig->channelInterruptEnable);
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();

    /* Select channel less than channel8 */
    if(SARADC_CHANNELID_8 > channelID)
    {
        /* Get CINTNP0 value*/
        cintnp0Val.U = pSaradc->CINTNP0.U;
        /* Glear channel mapping */
        cintnp0Val.U &= (uint32)(~((uint32)0xFU << ((uint32)((uint32)channelID << 2U))));

        /* Set channel mapping */
        cintnp0Val.U |= (uint32)pChannelInterruptConfig->interruptMapping << ((uint32)((uint32)channelID << 2U));
        pSaradc->CINTNP0.U = cintnp0Val.U;
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CINTNP0.U, cintnp0Val.U);
    }
    /* Select channel more than or equal to channel8 */
    else
    {
        /* Get CINTNP1 value */
        cintnp1Val.U = pSaradc->CINTNP1.U;
        /* Glear channel mapping */
        cintnp1Val.U &= (uint32)(~((uint32)0xFU << ((uint32)((uint32)channelID - (uint32)8U) << 2U)));
        /* Set channel mapping */
        cintnp1Val.U |= (uint32)pChannelInterruptConfig->interruptMapping << ((uint32)((uint32)channelID - (uint32)8U) << 2U);
        pSaradc->CINTNP1.U = cintnp1Val.U;
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CINTNP1.U, cintnp1Val.U);
    }
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    
    return retSts;
}

/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_MaskSourceInterrupt(SARADC_MODULE *const pSaradc, boolean mask)
{
    boolean retSts;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif

    retSts = TRUE;
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();
    /* Masking is enable */
    if(1U == mask)
    {
        /* Mask source interrupt */
        pSaradc->SINTCTRL.U |= (uint32)SARADC_SOURCE_MASK;
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->SINTCTRL.B.SMASK, 3U);
    }
    /* Masking is disable */
    else
    {
        /* Unmask source interrupt */
        pSaradc->SINTCTRL.U &= (uint32)SARADC_SOURCE_UNMASK;
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->SINTCTRL.B.SMASK, 0U);
    }
    /* Set cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    return retSts;
}

/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_MaskResultInterrupt(SARADC_MODULE *const pSaradc, boolean mask)
{

    boolean retSts;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    retSts = TRUE;
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();
    /* Masking is enable */
    if(1U == mask)
    {
        /* Mask result interrupt */
        pSaradc->RINTCTRL.U |= (uint32)SARADC_RESULT_MASK;
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->RINTCTRL.B.RMASK, 3U);
    }
    /* Masking is disable */
    else
    {
        /* Unmask result interrupt */
        pSaradc->RINTCTRL.U &= (uint32)SARADC_RESULT_UNMASK;
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->RINTCTRL.B.RMASK, 0U);
    }
    /* Set cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    return retSts;
}

/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_MaskChannelInterrupt(SARADC_MODULE *const pSaradc, boolean mask)
{
    boolean retSts;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif
    retSts = TRUE;
    /* Disable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();
    /* Masking is enable */
    if(1U == mask)
    {
        /* Mask channel interrupt*/
        pSaradc->CINTCTRL.U |= (uint32)SARADC_CHANNEL_MASK;
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CINTCTRL.B.CMASK, 3U);
    }
    /* Masking is disable */
    else
    {
        /* Unmask channel interrupt */
        pSaradc->CINTCTRL.U &= (uint32)SARADC_CHANNEL_UNMASK;
        /* Check register readback check value meet expectation */
        retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CINTCTRL.B.CMASK, 0U);
    }
    /* Set cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    return retSts;
}


/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_SetQueueStartMode(SARADC_MODULE *const pSaradc,Saradc_StartMode startMode,
                                    Saradc_RequestSource requestSource)
{
    /* #Violation: saradc_hal_c_REF_2 */
    SARADC_ARBCTRL arbctrlVal;
    boolean retSts;
    uint32 maskBist;
    retSts = TRUE;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif

    arbctrlVal.U = pSaradc->ARBCTRL.U;
    /* Request is QUEUE0 */
    if(SARADC_REQUESTSOURCE_QUEUE0 == requestSource)
    {
        /* Set queue 0 start mode */
        arbctrlVal.B.CONSMODE0 = (uint32)startMode;
    }
    /* Request is QUEUE1 */
    else if(SARADC_REQUESTSOURCE_QUEUE1 == requestSource)
    {
        /* Set queue 1 start mode */
        arbctrlVal.B.CONSMODE1 = (uint32)startMode;
    }
    /* Request is QUEUE2 */
    else
    {
        /* Set queue 2 start mode */
        arbctrlVal.B.CONSMODE2 = (uint32)startMode;
    }
    maskBist = 0x700EBBBU;
    pSaradc->ARBCTRL.U = arbctrlVal.U;
    /* Check register readback check value meet expectation */
    retSts = Saradc_Register_ReadBack_Check(retSts, (pSaradc->ARBCTRL.U & maskBist), (arbctrlVal.U & maskBist));
    return retSts;
}

#if defined (THA6_THA6206D)
/* #Violation: saradc_hal_c_REF_6 */
boolean Saradc_Hal_Ch2StrongPullDownSet(SARADC_MODULE *const pSaradc, boolean enDisCfg)
{
    boolean retSts;
    retSts = TRUE;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check whether the module pointer is a valid pointer */
    /* Check SARADC base address */
    /* #Violation: saradc_hal_c_REF_1 */
    /* #Violation: saradc_hal_c_REF_5 */
    Assert((boolean)(CHECK_SARADC_BASE(pSaradc)));
#endif

    /* Enable all interrupt */
    DISABLE_ALL_INTERRUPTS();
    /* Clear cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_ClearEndinit();  
    /* En/disable CH2 global strong pull-down diagnostic */
    pSaradc->ANACFG.B.CH2PDDEN = (uint32)enDisCfg; 
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->ANACFG.B.CH2PDDEN, (uint32)(enDisCfg));
    /* Set cpuwdt ENDINIT */
    retSts &= Cpuwdt_Hal_SetEndinit();
    /* Enable all interrupt */
    ENABLE_ALL_INTERRUPTS();
    return retSts;
}
#endif

#define ADC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: saradc_hal_c_REF_8 */
#include "Adc_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
