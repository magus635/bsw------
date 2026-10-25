/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    saradc_std.c
 * Author:      30037
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all internal functions of SARADC Driver
 *********************************************************************************************************************/

/*
*#Violation Summary
*#saradc_std_c_REF_1:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#saradc_std_c_REF_2:MISRAC2012-Rule-19.2;
* Justification: Using unions for bit-field access to registers.
*
*#saradc_std_c_REF_3:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#saradc_std_c_REF_4:EXP37-C;
* Justification: The Macro need to be used in different chip.
*
*#saradc_std_c_REF_5:MISRAC2012-Rule-20.1;
*Justification: Imposes the specification of the section in which certain parts of the driver must be placed.

*
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "saradc_std.h"
#include "Platform_Types.h"
#include "saradc_register.h"
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
#define ADC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Adc_MemMap.h"
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
boolean Saradc_Std_AnalogConvertControl(SARADC_MODULE *const pSaradc, boolean enable)
{
    boolean retSts;
    retSts = TRUE;
    /* Enable saradc */
    pSaradc->ANACFG.B.ANAEN = enable;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->ANACFG.B.ANAEN, enable);
    return retSts;
}

boolean Saradc_Std_SetSampleTime(SARADC_MODULE *const pSaradc, uint8 sampleTime)
{
    boolean retSts;
    retSts = TRUE;
    /* Set sample time */
    pSaradc->SAMCTRL.U = (uint32)sampleTime;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->SAMCTRL.U, sampleTime);
    return retSts;
}

boolean Saradc_Std_SetConverterSource(SARADC_MODULE *const pSaradc, Saradc_ConverterSource converterSource)
{
    uint32 tempValue;
    boolean retSts;
    retSts = TRUE;
    /* Set saradc synchronous converter source. */ 
    if(SARADC_CONVERTER_MASTER == converterSource)
    {
        tempValue = (uint32)converterSource;
    }
    else
    {
        tempValue = (uint32)((uint32)converterSource | ((uint32)8U << (uint32)converterSource));
    }
    pSaradc->SYNCCTRL.U = tempValue;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->SYNCCTRL.U, tempValue);
    return retSts;
}

boolean Saradc_Std_SetQueueCommonConfig(SARADC_MODULE *const pSaradc, const Saradc_QueueCommonConfig *const pCommonConfig,
                                     Saradc_RequestSource requestSource)
{
    /* #Violation: saradc_std_c_REF_2 */
    SARADC_ARBCTRL arbctrlVal;
    boolean retSts;
    retSts = TRUE;
    uint32 maskBits;
    arbctrlVal.U = pSaradc->ARBCTRL.U;
    /* Structure variable is not NULL pointer */
    if (NULL_PTR != pCommonConfig)
    {   /* Request source is QUEUE0 */
        if(SARADC_REQUESTSOURCE_QUEUE0 == requestSource)
        {
            /* Set queue 0 priority */
            arbctrlVal.B.PRIOL0 = (uint32)pCommonConfig->priority;
            /* Set queue 0 start mode */
            arbctrlVal.B.CONSMODE0 = (uint32)pCommonConfig->startMode;
            /* Arbitration queue 0 enable*/
            arbctrlVal.B.ARBEN0 = (uint32)pCommonConfig->enable;
        }
        /* Request source is QUEUE1 */
        else if(SARADC_REQUESTSOURCE_QUEUE1 == requestSource)
        {
            /* Set queue 1 priority */
            arbctrlVal.B.PRIOL1 = (uint32)pCommonConfig->priority;
            /* Set queue 1 start mode */
            arbctrlVal.B.CONSMODE1 = (uint32)pCommonConfig->startMode;
            /* Arbitration queue 1 enable */
            arbctrlVal.B.ARBEN1 = (uint32)pCommonConfig->enable;
        }
        /* Request source is QUEUE2 */
        else
        {
            /* Set queue 2 priority */
            arbctrlVal.B.PRIOL2 = (uint32)pCommonConfig->priority;
            /* Set queue 2 start mode */
            arbctrlVal.B.CONSMODE2 = (uint32)pCommonConfig->startMode;
            /* Arbitration queue 2 enable */
            arbctrlVal.B.ARBEN2 = (uint32)pCommonConfig->enable;
        }
        pSaradc->ARBCTRL.U = arbctrlVal.U;
        maskBits = (~(0x38F70000U));
        /* Register readback check */
        retSts = Saradc_Register_ReadBack_Check(retSts, (pSaradc->ARBCTRL.U & maskBits), (arbctrlVal.U & maskBits));
    }
    return retSts;
}


boolean Saradc_Std_SetStoreResult(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID,
                               Saradc_ChannelResult channelResult)
{
    boolean retSts;
    retSts = TRUE;
    /* Set channel store register */
    pSaradc->CHCTRL[channelID].B.RESSTREG = (uint32)channelResult;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CHCTRL[channelID].B.RESSTREG, (uint32)channelResult);
    return retSts;
}


boolean Saradc_Std_SetStorageMode(SARADC_MODULE *const pSaradc, Saradc_ChannelResult channelResult,
                               Saradc_StorageMode storageMode)
{
    boolean retSts;
    retSts = TRUE;
    pSaradc->RESCTRL[channelResult].B.WFRMODE = (uint32)storageMode;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->RESCTRL[channelResult].B.WFRMODE, (uint32)storageMode);    
    /* Set storage mode(overwrite/wait-for-read) */
    return retSts;
}

boolean Saradc_Std_EnableDma(SARADC_MODULE *const pSaradc, Saradc_ChannelResult channelResult, boolean enableDma)
{
    /* #Violation: saradc_std_c_REF_2 */
    SARADC_DMAEN dmaenVal;
    boolean retSts;
    retSts = TRUE;
    dmaenVal.U = pSaradc->DMAEN.U;   

    /* Disable DMA */
    if(FALSE == enableDma)
    {
        dmaenVal.U &= (uint32)(~((uint32)1U << (uint32)channelResult));
    }
    /* Enable DMA */
    else
    {
        dmaenVal.U |= (uint32)((uint32)1U << (uint32)channelResult);
    }
    /* Write DMA en/disable function */
    pSaradc->DMAEN.U  = dmaenVal.U;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->DMAEN.U, dmaenVal.U);
    return retSts;
}

boolean Saradc_Std_SetAlign(SARADC_MODULE *const pSaradc, Saradc_ChannelResult channelResult, boolean rightAlignedStorage)
{
    boolean retSts;
    retSts = TRUE;
    /* Set align mode(left/right) */
    pSaradc->RESCTRL[channelResult].B.RESALI = rightAlignedStorage;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->RESCTRL[channelResult].B.RESALI, rightAlignedStorage);
    return retSts;
}

boolean Saradc_Std_SetBoundaryRange(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID,
                               boolean boundaryRange)
{
    boolean retSts;
    retSts = TRUE;
    /* Set channel store register*/
    pSaradc->CHCTRL[channelID].B.BOUNDRS = boundaryRange;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CHCTRL[channelID].B.BOUNDRS, boundaryRange);
    return retSts;
}

boolean Saradc_Std_SetBoundaryResultCtrl(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID,
                               boolean boundaryResultControl)
{
    boolean retSts;
    retSts = TRUE;
    /* Set channel store register */
    pSaradc->CHCTRL[channelID].B.BOUNDDR = boundaryResultControl;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CHCTRL[channelID].B.BOUNDDR, boundaryResultControl);
    return retSts;
}


boolean Saradc_Std_SetSynchronizeRequest(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID,
                                      boolean enableSynchronize)
{
    boolean retSts;
    retSts = TRUE;
    /* Set Synchronize conversion channel */
    pSaradc->CHCTRL[channelID].B.SYNCREQ = enableSynchronize;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CHCTRL[channelID].B.SYNCREQ, enableSynchronize);
    return retSts;
}

boolean Saradc_Std_SetHdiIf(SARADC_MODULE *const pSaradc, Saradc_ChannelID channelID, Saradc_Hdi hdiIfEn)
{
    boolean retSts;
    /* #Violation: saradc_std_c_REF_2 */
    SARADC_CHCTRL chctrlVal;
    retSts = TRUE;
    chctrlVal.U = pSaradc->CHCTRL[channelID].U;
    /* HDI function selsection judgement */
    switch (hdiIfEn)
    {
#if  defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
        /* HID_FC enable */
        case SARADC_HDI_FC:
            pSaradc->CHCTRL[channelID].B.HDIFCEN = 0x1U;
            /* Register readback check */
            retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CHCTRL[channelID].B.HDIFCEN, 0x1U);       
            break;
        /* HID_RDC enable */
        case SARADC_HDI_RDC:
            pSaradc->CHCTRL[channelID].B.HDIRDCEN = 0x1U;
            /* Register readback check */
            retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CHCTRL[channelID].B.HDIRDCEN, 0x1U);
            break;
#endif  /* End THA6_THA6206 || THA6_THA6412 || THA6_THA6206D */
        /* HID_GTM enable */
        case SARADC_HDI_GTM:
            pSaradc->CHCTRL[channelID].B.HDIGTMEN = 0x1U;
            /* Register readback check */
            retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CHCTRL[channelID].B.HDIGTMEN, 0x1U);       
            break;
        case SARADC_HDI_OFF:
            chctrlVal.U &= ~(0x700000U);
            pSaradc->CHCTRL[channelID].U = chctrlVal.U;
            retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->CHCTRL[channelID].U, chctrlVal.U);
            break;
        default:
            retSts = FALSE;
            break;
    }
    return retSts;
}

boolean Saradc_Std_SetDivider(SARADC_MODULE *const pSaradc, uint8 divider)
{
    boolean retSts;
    retSts = TRUE;
    /* Set Clock divider */
    pSaradc->ANACFG.B.ANADIVF = (uint32)divider;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->ANACFG.B.ANADIVF, divider);
    return retSts;
}

boolean Saradc_Std_SetResolution(SARADC_MODULE *const pSaradc, Saradc_Resolution resolution)
{
    boolean retSts;
    retSts = TRUE;
    /* Set resolution */
    pSaradc->ANACFG.B.ANARESO = (uint32)resolution;
    /* Register readback check */
    retSts = Saradc_Register_ReadBack_Check(retSts, pSaradc->ANACFG.B.ANARESO, (uint32)resolution);
    return retSts;
}

#define ADC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: saradc_std_c_REF_5 */
#include "Adc_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
