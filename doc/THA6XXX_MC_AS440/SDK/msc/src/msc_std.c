/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    msc_std.c
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all internal functions of MSC Driver
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#msc_std_c_REF_1:MISRAC2012-Rule-19.2; 
* Justification:Using unions for bit-field access to registers
*
*#msc_std_c_REF_2:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#msc_std_c_REF_3:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
*#msc_std_c_REF_4:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8
*
*#msc_std_c_REF_5:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity
*
*#msc_std_c_REF_6:MISRAC2012-Dir-4.2;
* Justification:The assembler statements is used to synchronize the data of the ARM core.
*
*#msc_std_c_REF_7:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "msc_std.h"
#include "Platform_Types.h"
#include "compilertypes.h"
#include "msc_register.h"
#include "tha6_cfg.h"
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
#define MSC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: msc_std_c_REF_7 */
#include "Msc_MemMap.h"

void Msc_Std_InitBaudRate(MSC_MODULE *const pMsc, const Msc_ClockConfig *const pConfig, float32 ahbClkFreq)
{
    float32 tempValue;
    
    /* #Violation: msc_std_c_REF_1 */
    MSC_FDIV fdivValue;

    /* Read the FDR register content */
    fdivValue.U = pMsc->FDIV.U;

    /* Enable Hardware Clock Control */
    fdivValue.B.ENHCC = 1U;
    /* Enable Hardware Clock Control Enable */
    fdivValue.B.ECEN = 1U;
    /* Enable MSC clock output */
    fdivValue.B.CLKDIS = 0U;

    if(1U == (uint32)pConfig->divMode)
    {
        /* Initialize downstream baud-rate */
        tempValue = ((ahbClkFreq / (float32)pConfig->baud) / 2.0F);
        fdivValue.B.STEP = 1024U - (uint32)tempValue;
    }
    else
    {
        /* Initialize downstream baud-rate */
        tempValue = (2.0F * ((float32)pConfig->baud / ahbClkFreq) * 1024.0F) - 1.0F;
        /* #Violation: msc_std_c_REF_3 */
        fdivValue.B.STEP = (uint32)tempValue;
    }

    /* Select the divider mode */
    fdivValue.B.DIVM = (uint32)pConfig->divMode;

    /* #Violation: msc_std_c_REF_2 */
    pMsc->FDIV.U = fdivValue.U;
}

void Msc_Std_InitUpstream(MSC_MODULE *const pMsc, const Msc_UpstreamConfig *const pConfig)
{
    /* #Violation: msc_std_c_REF_1 */
    MSC_UPSTS upstsValue;
    /* #Violation: msc_std_c_REF_1 */
    MSC_OCON oconValue;

    /* Read the UPSTS register content */
    upstsValue.U = pMsc->UPSTS.U;
    oconValue.U = pMsc->OCON.U;

    /* Service request delay control */
    upstsValue.B.SRDCON = (uint32)pConfig->reqDelay;
    /* Select parity control Odd - 0, Even - 1 */
    upstsValue.B.PCON = (uint32)pConfig->parity;
    /* Select upstream baud rate fMSC/xx */
    upstsValue.B.UCRR = (uint32)pConfig->upDiv;
    /* Select 12 bit or 16 bit frame */
    upstsValue.B.UCFT = (uint32)pConfig->frameType;
    /* SDI Line Polarity - SDI and SI */
    oconValue.B.SDILP = (uint32)pConfig->sdiPol;

    pMsc->UPSTS.U = upstsValue.U;
    pMsc->OCON.U = oconValue.U;
}

void Msc_Std_InitDownstream(MSC_MODULE *const pMsc, const Msc_DownstreamConfig *const pConfig)
{
    /* #Violation: msc_std_c_REF_1 */
    MSC_DCON dconValue;
    /* #Violation: msc_std_c_REF_1 */
    MSC_DCONE dconeValue;
    /* #Violation: msc_std_c_REF_1 */
    MSC_OCON oconValue;

    /* Read the DCON & DSTS & DCONE register content */
    dconValue.U = pMsc->DCON.U;
    dconeValue.U = pMsc->DCONE.U;
    oconValue.U = pMsc->OCON.U;

    /* Passive phase length */
    dconValue.B.PPLD = (uint32)pConfig->dfPpl;
    /* Number of command bits transmitted */
    dconValue.B.NBCF = (uint32)pConfig->cfLength;
    /* SRL selection bit */
    dconValue.B.SELSRL = (uint32)pConfig->srlSelBit;
    /* SRH selection bit */
    dconValue.B.SELSRH = (uint32)pConfig->srhSelBit;
    /* Number of SRL bits transmitted */
    dconValue.B.NBDFL = (uint32)pConfig->srlDfLength;
    /* Number of SRH bits transmitted */
    dconValue.B.NBDFH = (uint32)pConfig->srhDfLength;
    /* Operation mode */
    dconValue.B.TRM = (uint32)pConfig->transMode;

    /* Number of passive time frames */
    pMsc->DSTS.B.NUMPT = (uint32)pConfig->ptfCount;

    /* Select source for SRL */
    pMsc->DDSL.U = (uint32)pConfig->srcConfig.lowSrc;
    /* Select source for SRH */
    pMsc->DDSH.U = (uint32)pConfig->srcConfig.highSrc;

    /* Emergency stop enable for bits */
    pMsc->EMSR.U = (uint32)pConfig->srcConfig.emsBits;

    /* FCL is activated during active phases or always */
    oconValue.B.CLKCON = (uint32)pConfig->fclValid;
    /* Chip Selection Lines Polarity - EN[0:3, ENL, ENH and ENC */
    oconValue.B.CSP = (uint32)pConfig->cslPol;
    /* Chip Enable Selection for ENL */
    oconValue.B.CSENL = (uint32)MSC_TARGET_EN0;
    /* Chip Enable Selection for ENH */
    oconValue.B.CSENH = (uint32)MSC_TARGET_EN0;
    /* Chip Enable Selection for ENC */
    oconValue.B.CSENC = (uint32)MSC_TARGET_EN0;

    /* Command-Data-Command mode in repetition mode */
    dconeValue.B.CDCM = (uint32)pConfig->cdcMode;
    /* Injection Position of the Pin 0 Signal */
    dconeValue.B.IPP0 = (uint32)pConfig->srcConfig.pin0InjPos;
    /* Injection Enable of the Pin 0 Signal */
    dconeValue.B.IEP0 = (uint32)pConfig->srcConfig.pin0InjEn;
    /* Injection Position of the Pin 1 Signal */
    dconeValue.B.IPP1 = (uint32)pConfig->srcConfig.pin1InjPos;
    /* Injection Enable of the Pin 1 Signal */
    dconeValue.B.IEP1 = (uint32)pConfig->srcConfig.pin1InjEn;

    pMsc->DCON.U = dconValue.U;
    pMsc->OCON.U = oconValue.U;
    pMsc->DCONE.U = dconeValue.U;
}

void Msc_Std_InitInterrupt(MSC_MODULE *const pMsc, const Msc_InterruptConfig *const pConfig)
{
    /* #Violation: msc_std_c_REF_1 */
    MSC_INTCON intconValue;

    /* Read the INTCON register content */
    intconValue.U = pMsc->INTCON.U;

    /* Configure data frame interrupt generation condition and node */
    intconValue.B.DFIE = (uint32)MSC_INTREN_DISABLED;
    intconValue.B.EDII = (uint32)pConfig->dfiType;
    intconValue.B.DFIP = (uint32)pConfig->dfiNode;

    /* Configure receive data interrupt generation condition and node */
    intconValue.B.RDIE = (uint32)MSC_INTREN_DISABLED;
    intconValue.B.RDII = (uint32)pConfig->rdiType;
    intconValue.B.RDIP = (uint32)pConfig->rdiNode;

    /* Configure command frame interrupt node */
    intconValue.B.CFIE = (uint32)MSC_INTREN_DISABLED;
    intconValue.B.CFIP = (uint32)pConfig->cfiNode;

    /* Configure time frame interrupt node */
    intconValue.B.TFINTE = (uint32)MSC_INTREN_DISABLED;
    intconValue.B.TFINTP = (uint32)pConfig->tfiNode;

    pMsc->INTCON.U = intconValue.U;
}

Msc_RxStatus Msc_Std_GetRxStatus(const MSC_MODULE *const pMsc, Msc_UpstreamRegType upstreamIdx)
{
    Msc_RxStatus status;
    uint8 parityFlag;
    uint8 validFlag;

    /* Check if parity error raised */
    parityFlag = pMsc->UDR[upstreamIdx].B.PE;

    /* Check data validation */
    validFlag = pMsc->UDR[upstreamIdx].B.VB;

    if(1U == parityFlag)
    {
        /* Parity check error */
        status = MSC_RXSTATUS_PE;
    }
    else if(1U == validFlag)
    {
        /* Valid data received */
        status = MSC_RXSTATUS_RECEIVED;
    }
    else
    {
        /* No data response */
        status = MSC_RXSTATUS_NORESPONSE;
    }

    return status;
}

uint8 Msc_Std_GetData(const MSC_MODULE *const pMsc, Msc_UpstreamRegType upstreamIdx)
{
    return pMsc->UDR[upstreamIdx].B.RDAT;
}

void Msc_Std_ClearUpstreamValidFlag(MSC_MODULE *const pMsc, Msc_UpstreamRegType upstreamIdx)
{
    pMsc->UDR[upstreamIdx].B.CB = 1U;
}
#define MSC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: msc_std_c_REF_7 */
#include "Msc_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
