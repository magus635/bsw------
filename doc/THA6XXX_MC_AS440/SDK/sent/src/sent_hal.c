/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    sent_hal.c
 * Author:      01321
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of SENT module.
 *********************************************************************************************************************/

/*
* #Violation Summary
* #sent_hal_c_REF_1:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by code review.
*
* #sent_hal_c_REF_2:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
* #sent_hal_c_REF_3:MISRAC2012-Rule-10.5;
* Justification: Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8.
*
* #sent_hal_c_REF_4:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #sent_hal_c_REF_5:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
* #sent_hal_c_REF_6:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
* #sent_hal_c_REF_7:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "sent_register.h"
#include "sent_hal.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* Mask RCDF.RX_SYNC_RST when read back register */
#define SENT_RX_SYNC_RST_MASK (0xFFF7FFFFU)
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: sent_hal_c_REF_6 */
#define SENT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: sent_hal_c_REF_7 */
#include "Sent_MemMap.h"

/* #Violation: sent_hal_c_REF_2 */
boolean Sent_Hal_Init(const Sent_Config *const pSentConfig, SENT_MODULE *const pSentModule)
{
    boolean ret;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pIntList is null pointer */
    /* #Violation: sent_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pSentConfig));
    /* #Violation: sent_hal_c_REF_4 */
    /* #Violation: sent_hal_c_REF_5 */
    Assert((boolean)SENT_CHECK_MODULE(pSentModule));
#endif /* INPUT_ARG_DETECT */
    ret = TRUE;
    /* #Violation: sent_hal_c_REF_1 */
    SENT_RCFG revCfg;
    revCfg.U = pSentModule->RCFG.U;
    if(SENT_CRC_ENABLE_ON == pSentConfig->crcConfig.crcEnable)
    {
        revCfg.B.RX_CRCTYPE = (uint32)pSentConfig->crcConfig.crcType;
        revCfg.B.RX_CRC_WITH_STATUS = (uint32)pSentConfig->crcConfig.crcWith;
        revCfg.B.RX_CRCENB = (uint32)SENT_CRC_ENABLE_ON;
    }
    else
    {
        revCfg.B.RX_CRCENB = (uint32)SENT_CRC_ENABLE_OFF;
    }

    revCfg.B.RX_DNIB = (uint32)pSentConfig->nibbleNum;
    revCfg.B.RX_PPENB = (uint32)pSentConfig->pause;
    revCfg.B.RX_IDLEPOL = (uint32)pSentConfig->polarity;
    revCfg.B.RX_SYNC_RST = 1U;
    /* Set the Configuration Register */
    pSentModule->RCFG.U = revCfg.U;
    ret = Sent_Register_ReadBack_Check(ret, revCfg.U & SENT_RX_SYNC_RST_MASK, pSentModule->RCFG.U);
    /* Set the Synchronous Pulse receiving range */
    pSentModule->RSYNC.B.RSYNC_MIN = pSentConfig->rsynMin;
    pSentModule->RSYNC.B.RSYNC_MAX = pSentConfig->rsynMax;
    ret = Sent_Register_ReadBack_Check(ret, (uint32)pSentConfig->rsynMin | ((uint32)pSentConfig->rsynMax << 16U), pSentModule->RSYNC.U);
#if defined(THA6_THA6104)
    /* #Violation: sent_hal_c_REF_1 */
    SENT_INTMASK intmask;
    intmask.U = pSentModule->INTMASK.U;
    intmask.B.VLDMASK = (uint32)pSentConfig->validIntSta;
    intmask.B.ERRMASK = (uint32)pSentConfig->errorIntSta;
    pSentModule->INTMASK.U = intmask.U;
    ret = Sent_Register_ReadBack_Check(ret, intmask.U, pSentModule->INTMASK.U);
#endif
    return ret;
}

/* #Violation: sent_hal_c_REF_2 */
boolean Sent_Hal_Enable(SENT_MODULE *const pSentModule)
{
    boolean ret;
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: sent_hal_c_REF_4 */
    /* #Violation: sent_hal_c_REF_5 */
    Assert((boolean)SENT_CHECK_MODULE(pSentModule));
#endif /* INPUT_ARG_DETECT */
    /* Enable Sent Module */
    ret = TRUE;
    /* #Violation: sent_hal_c_REF_1 */
    SENT_RCFG revCfg;
    revCfg.U = pSentModule->RCFG.U;
    revCfg.B.RX_ENB = 1U;
    /* Set the Configuration Register */
    pSentModule->RCFG.U = revCfg.U;
    ret = Sent_Register_ReadBack_Check(ret, revCfg.U, pSentModule->RCFG.U);
    return ret;
}

/* #Violation: sent_hal_c_REF_2 */
boolean Sent_Hal_Disable(SENT_MODULE *const pSentModule)
{
    boolean ret;
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: sent_hal_c_REF_4 */
    /* #Violation: sent_hal_c_REF_5 */
    Assert((boolean)SENT_CHECK_MODULE(pSentModule));
#endif /* INPUT_ARG_DETECT */
    /* Enable Sent Module */
    ret = TRUE;
    /* #Violation: sent_hal_c_REF_1 */
    SENT_RCFG revCfg;
    revCfg.U = pSentModule->RCFG.U;
    revCfg.B.RX_ENB = 0U;
    /* Set the Configuration Register */
    pSentModule->RCFG.U = revCfg.U;
    ret = Sent_Register_ReadBack_Check(ret, revCfg.U, pSentModule->RCFG.U);
    return ret;
}

/* #Violation: sent_hal_c_REF_2 */
boolean Sent_Hal_InitSpc(const Sent_Spc_Config *const pSpcConfig, SENT_MODULE *const pSentModule)
{
    boolean ret;
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: sent_hal_c_REF_4 */
    /* #Violation: sent_hal_c_REF_5 */
    Assert((boolean)SENT_CHECK_MODULE(pSentModule));
    /* #Violation: sent_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pSpcConfig));
    /* #Violation: sent_hal_c_REF_3 */
    Assert((boolean)(0U !=  pSpcConfig->timeOut));
#endif /* INPUT_ARG_DETECT */

    ret = TRUE;
    /* Set external or internal Spc trigger */
    if(SENT_TRIGGER_MODE_SPC == pSpcConfig->triggerMode)
    {
        /* Define value of tick/clock for SPC transmission */
        /* #Violation: sent_hal_c_REF_1 */
        SENT_RCFG revCfg;
        revCfg.U = pSentModule->RCFG.U;
        revCfg.B.TTCLK_SPC = pSpcConfig->tickTime;
        revCfg.B.SPC_MODE = 1U;
        /* Set the Configuration Register */
        pSentModule->RCFG.U = revCfg.U;
        ret = Sent_Register_ReadBack_Check(ret, revCfg.U, pSentModule->RCFG.U);
        pSentModule->MSEL.U = SENT_MSEL_INTERNAL_TRIGGER;
    }
    else
    {
        /* Define value of tick/clock for SPC transmission */
        uint32 tempVal;
        /* #Violation: sent_hal_c_REF_1 */
        SENT_RCFG revCfg;
        revCfg.U = pSentModule->RCFG.U;
        revCfg.B.TTCLK_SPC = pSpcConfig->tickTime;
        revCfg.B.RX_ENB = 1U;
        revCfg.B.SPC_MODE = 0U;
        /* Set the Configuration Register */
        pSentModule->RCFG.U = revCfg.U;
        ret = Sent_Register_ReadBack_Check(ret, revCfg.U, pSentModule->RCFG.U);

        pSentModule->MSEL.U = SENT_MSEL_GTM_TRIGGER;
        ret = Sent_Register_ReadBack_Check(ret, SENT_MSEL_GTM_TRIGGER, pSentModule->MSEL.U);
        tempVal = pSentModule->ETCFG.U | ((uint32)0x1U << (uint32)pSpcConfig->gtmChannel);
        pSentModule->ETCFG.U = tempVal;
        ret = Sent_Register_ReadBack_Check(ret, tempVal, pSentModule->ETCFG.U);
        pSentModule->TTMOUT.U = pSpcConfig->timeOut;
        ret = Sent_Register_ReadBack_Check(ret, pSpcConfig->timeOut, pSentModule->TTMOUT.U);
    }
    return ret;
}

/* #Violation: sent_hal_c_REF_2 */
void Sent_Hal_GetFastMessage(Sent_Fast_Messagebuffer *const pFastMessage, const SENT_MODULE *const pSentModule)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: sent_hal_c_REF_4 */
    /* #Violation: sent_hal_c_REF_5 */
    Assert((boolean)SENT_CHECK_MODULE(pSentModule));
    /* #Violation: sent_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pFastMessage));
#endif /* INPUT_ARG_DETECT */
    /* #Violation: sent_hal_c_REF_1 */
    SENT_RFDATA revFastData;
    /* Get fast message through Register */
    revFastData.U = pSentModule->RFDATA.U;
    pFastMessage->status = revFastData.B.STAT;
    pFastMessage->crc = revFastData.B.CRC;
    pFastMessage->data = (revFastData.U & SENT_RFDATA_DATA_MASK) >> SENT_RFDATA_DATA_OFFSET;
}

/* #Violation: sent_hal_c_REF_2 */
void Sent_Hal_GetSlowMessage(Sent_Slow_Messagebuffer *const pSlowMessage, const SENT_MODULE *const pSentModule)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: sent_hal_c_REF_4 */
    /* #Violation: sent_hal_c_REF_5 */
    Assert((boolean)SENT_CHECK_MODULE(pSentModule));
    /* #Violation: sent_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pSlowMessage));
#endif /* INPUT_ARG_DETECT */
    /* #Violation: sent_hal_c_REF_1 */
    uint32 revSlowData;
    /* Check if it received a valid slow message */
    if (1U == pSentModule->RSTAT.B.RXSLOW_DN)
    {
        /* Get slow message through Register*/
        pSlowMessage->slowType = SENT_SLOW_TYPE_ALL;
    }
    else
    {
        /* Do not receive a slow message */
        pSlowMessage->slowType = SENT_SLOW_TYPE_NO;
    }
    revSlowData = pSentModule->RSDATA.U;
    pSlowMessage->messageID = (uint8)(revSlowData >> 24U);
    pSlowMessage->data = (uint16)((revSlowData >> 8U) & 0xFFFFU);
    pSlowMessage->crc = (uint8)(revSlowData & 0x3FU);
}

/* #Violation: sent_hal_c_REF_2 */
boolean Sent_Hal_EnableSpc(SENT_MODULE *const pSentModule, uint8 tickPeriod)
{
    boolean ret;
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: sent_hal_c_REF_4 */
    /* #Violation: sent_hal_c_REF_5 */
    Assert((boolean)SENT_CHECK_MODULE(pSentModule));
#endif /* INPUT_ARG_DETECT */
    ret = TRUE;
    /* Disable Sent module to change the Spc total tick time */
    /* #Violation: sent_hal_c_REF_1 */
    SENT_RCFG revCfg;
    revCfg.U = pSentModule->RCFG.U;
    if(1U == pSentModule->MSEL.B.MODE)
    {
        revCfg.B.RX_ENB = 1U;
        revCfg.B.RX_SPCENB = 0U;
    }
    else
    {
        revCfg.B.RX_ENB = 0U;
        revCfg.B.RX_SPCENB = 1U;
    }
    revCfg.B.RX_SPCMTP = tickPeriod;
    pSentModule->RCFG.U = revCfg.U;
    ret = Sent_Register_ReadBack_Check(ret, revCfg.U, pSentModule->RCFG.U);

    return ret;
}

/* #Violation: sent_hal_c_REF_2 */
uint32 Sent_Hal_GetStatus(const SENT_MODULE *const pSentModule)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: sent_hal_c_REF_4 */
    /* #Violation: sent_hal_c_REF_5 */
    Assert((boolean)SENT_CHECK_MODULE(pSentModule));
#endif /* INPUT_ARG_DETECT */
    uint32 sentStatus;
    /* Get the status bit to sentStatus*/
    sentStatus  = SENT_STATUS_MASK & (pSentModule->RSTAT.U);
    return sentStatus;
}

/* #Violation: sent_hal_c_REF_2 */
Sent_Enable_Status Sent_Hal_ChannelUsing(const SENT_MODULE *const pSentModule)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: sent_hal_c_REF_4 */
    /* #Violation: sent_hal_c_REF_5 */
    Assert((boolean)SENT_CHECK_MODULE(pSentModule));
#endif /* INPUT_ARG_DETECT */
    Sent_Enable_Status enableStatus;
    enableStatus = SENT_MODULE_DISABLED;
    /* Check if Sent is using */
    if ((1U == pSentModule->RCFG.B.RX_ENB)||(1U == pSentModule->RCFG.B.RX_SPCENB))
    {
        enableStatus = SENT_MODULE_ENABLED;
    }

    return enableStatus;
}

/* #Violation: sent_hal_c_REF_2 */
Sent_Message_Status Sent_Hal_GetGTMReceiveStatus(const SENT_MODULE *const pSentModule)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: sent_hal_c_REF_4 */
    /* #Violation: sent_hal_c_REF_5 */
    Assert((boolean)SENT_CHECK_MODULE(pSentModule));
#endif /* INPUT_ARG_DETECT */
    Sent_Message_Status messageStatus;
    if(1U == pSentModule->EXTSTAT.B.DATAMIS)
    {
        messageStatus = SENT_MESSAGE_MISSED;
    }
    else if(1U == pSentModule->EXTSTAT.B.DATAREC)
    {
        messageStatus = SENT_MESSAGE_RECEIVED;
    }
    else
    {
        messageStatus = SENT_MESSAGE_NONE;
    }

    return messageStatus;
}

#if defined(THA6_THA6104)
/* #Violation: sent_hal_c_REF_2 */
uint32 Sent_Hal_GetSyncPulErrStatus(const SENT_MODULE *const pSentModule)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: sent_hal_c_REF_4 */
    /* #Violation: sent_hal_c_REF_5 */
    Assert((boolean)SENT_CHECK_MODULE(pSentModule));
#endif /* INPUT_ARG_DETECT */
    uint32 sentStatus;
    /* Get the status bit to sent Status*/
    sentStatus  = SENT_SYNCPULERRSTATUS_MASK & (pSentModule->RSTAT2.U);
    return sentStatus;
}
#endif

/* #Violation: sent_hal_c_REF_6 */
#define SENT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: sent_hal_c_REF_7 */
#include "Sent_MemMap.h"

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
