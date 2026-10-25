/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    msc_hal.c
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of MSC module.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#msc_hal_c_REF_1:MISRAC2012-Rule-2.1; 
* Justification:Reserved API for user access.
*
*#msc_hal_c_REF_2:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity.
*
*#msc_hal_c_REF_3:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#msc_hal_c_REF_4:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
*#msc_hal_c_REF_5:MISRAC2012-Dir-4.2;
* Justification:The assembler statements is used to synchronize the data of the ARM core.
*
*#msc_hal_c_REF_6:MISRAC2012-Rule-10.5
* Justification:Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8.
*
*#msc_hal_c_REF_7:MISRAC2012-Rule-19.2;
* Justification:Using unions for bit-field access to registers.
*
*#msc_hal_c_REF_8:MISRAC2012-Rule-8.7; 
* Justification:The function is used by other file.
*
*#msc_hal_c_REF_9:CertC-DCL15-C; 
* Justification:Reserved API for user access.
*
*#msc_hal_c_REF_10:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "msc_hal.h"
#include "msc_std.h"
#include "Platform_Types.h"
#include "compilertypes.h"
#include "msc_register.h"
#include "tha6_cfg.h"
#include "cpuwdt_hal.h"
#include "rcc_hal.h"
#include "rcc_register.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
#define MSC_CLEAR_INTERRUPT_FLAG (0xFU)
#define MSC_MIN_DOWNSTREAM_BAUDRATE (50000U)
#define MSC_MAX_DELAY_TICK (0xBF680U)
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
/* #Violation: msc_hal_c_REF_10 */
#include "Msc_MemMap.h"

/* #Violation: msc_hal_c_REF_1 */
/* #Violation: msc_hal_c_REF_2 */
Rcc_ErrorFlag Msc_Hal_DeInitModule(const MSC_MODULE *const pMsc)
{
    Rcc_ErrorFlag flag = RCC_ERRORFLAG_TIMEOUT;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    if((0U == (uint32)pMsc->DSTS.B.DATFA) && (0U == (uint32)pMsc->DSTS.B.COMFA))
    {
        /* #Violation: msc_hal_c_REF_5 */
        DSB();

        /* #Violation: msc_hal_c_REF_3 */
        if(MSC0_HAL == pMsc)
        {
            /* Trigger MSC0 module reset */
            flag = Rcc_Hal_TrigModuleRst(RCC_MODULERST_MSC0);
        }
#if defined(THA6_THA6412)
        /* #Violation: msc_hal_c_REF_3 */
        else if(MSC1_HAL == pMsc)
        {
            /* Trigger MSC1 module reset */
            flag = Rcc_Hal_TrigModuleRst(RCC_MODULERST_MSC1);
        }
        else
        {
            /* Trigger MSC2 module reset */
            flag = Rcc_Hal_TrigModuleRst(RCC_MODULERST_MSC2);
        }
#endif /* THA6_THA6412 */
    }

    return flag;
}

/* #Violation: msc_hal_c_REF_1 */
boolean Msc_Hal_InitModule(MSC_MODULE *const pMsc, const Msc_ModuleConfig *const pConfig)
{
    boolean ret;
    float32 fsys;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_6 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
    /* #Violation: msc_hal_c_REF_6 */
    Assert((boolean)(MSC_MIN_DOWNSTREAM_BAUDRATE <= pConfig->clockConfig.baud)); /* To avoid FDIV.B.STEP being less than 0 */
#endif

    ret = TRUE;
    /* Disable downstream before configuration */
    Msc_Hal_ControlDownstream(pMsc, MSC_DOWNSTREAMEN_DISABLED);

    /* Configure upstream channel frame layout */
    if(MSC_UPDIV_DISABLED != pConfig->upstreamConfig.upDiv)
    {
        Msc_Std_InitUpstream(pMsc, &pConfig->upstreamConfig);
    }

    /* Get MSC module frequency */
    fsys = Rcc_Hal_GetAhbApbClkFreq();

    /* #Violation: msc_hal_c_REF_5 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();

    /* Configure MSC hardware enable and set the divider mode and baud rate */
    Msc_Std_InitBaudRate(pMsc, &pConfig->clockConfig, fsys);

    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: msc_hal_c_REF_5 */
    ENABLE_ALL_INTERRUPTS();

    /* Configure downstream channel frame layout and operation mode */
    Msc_Std_InitDownstream(pMsc, &pConfig->downstreamConfig);

    /* Control downstream for channel communication */
    Msc_Hal_ControlDownstream(pMsc, pConfig->downstreamConfig.downstreamEn);

    return ret;
}

/* #Violation: msc_hal_c_REF_1 */
void Msc_Hal_InitInterrupt(MSC_MODULE *const pMsc, const Msc_IntrConfig *const pConfig)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_6 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    Msc_Std_InitInterrupt(pMsc, pConfig);
}

/* #Violation: msc_hal_c_REF_1 */
void Msc_Hal_InitDma(MSC_MODULE *const pMsc, const Msc_DmaConfig *const pConfig)
{
    /* #Violation: msc_hal_c_REF_7 */
    MSC_INTCON intconValue;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_6 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    /* #Violation: msc_hal_c_REF_2 */
    intconValue.U = pMsc->INTCON.U;

    /* Read the INTCON register contents */
    intconValue.B.SELDMA = (uint32)pConfig->dmaEn;
    /* Enable or disable mirror register */
    intconValue.B.SELMIR = (uint32)pConfig->mirrorEn;

    pMsc->INTCON.U = intconValue.U;
}

/* #Violation: msc_hal_c_REF_1 */
void Msc_Hal_StartTimeoutDetection(MSC_MODULE *const pMsc, const Msc_TimeoutConfig *const pConfig, Msc_IntrEn enable)
{
    /* #Violation: msc_hal_c_REF_7 */
    MSC_UCONE uconeValue;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_6 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    uconeValue.U = pMsc->UCONE.U;

    /* Upstream timeout interrupt mode */
    uconeValue.B.UTIE = (uint32)enable;
    /* Upstream timeout value */
    uconeValue.B.UTV = (uint32)pConfig->timeoutValue;
    /* Upstream timeout prescaler */
    uconeValue.B.UTP = (uint32)pConfig->timeoutPrescaler;
    /* Must write 0 to bit UTC, otherwise bit UTF will never be set */
    uconeValue.B.UTC = 0U;

    /* Additional interrupt configured in USCE for Upstream Interrupt node SR4 */
    if(MSC_ALINTRNODE_SR4 == pConfig->node)
    {
        uconeValue.B.UTIP = 0U;
        uconeValue.B.UTASR = 1U;
    }
    else
    {
        uconeValue.B.UTIP = (uint32)pConfig->node;
        uconeValue.B.UTASR = 0U;
    }

    pMsc->UCONE.U = uconeValue.U;
}

/* #Violation: msc_hal_c_REF_1 */
void Msc_Hal_EnableInterrupt(MSC_MODULE *const pMsc, uint32 flag)
{

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
    /* #Violation: msc_hal_c_REF_6 */
    Assert((boolean)(0U == (flag & (~MSC_INTR_ENABLE_FLAG_ALL))));
#endif

    /* Clear all interrupt flags */
    pMsc->UCONE.B.UTC = 1U;
    pMsc->INTSC.U = MSC_CLEAR_INTERRUPT_FLAG;

    /* Enable selected interrupt */
    pMsc->INTCON.U |= flag;
}

/* #Violation: msc_hal_c_REF_1 */
void Msc_Hal_DisableInterrupt(MSC_MODULE *const pMsc, uint32 flag)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
    /* #Violation: msc_hal_c_REF_6 */
    Assert((boolean)(0U == (flag & (~MSC_INTR_ENABLE_FLAG_ALL))));
#endif

    /* Disable selected interrupt */
    pMsc->INTCON.U &= (~flag);
}

/* #Violation: msc_hal_c_REF_1 */
void Msc_Hal_SendCommand(MSC_MODULE *const pMsc, uint32 command)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    if(0U == pMsc->INTCON.B.SELMIR)
    {
        pMsc->DC.U = command;
    }
    else
    {
        pMsc->DCRM.U = command;
    }
}

#if defined(THA6_THA6206D)
boolean Msc_Hal_SyncSendCommand(MSC_MODULE *const pMsc, uint32 command)
{
	boolean retState;
    uint32 AhbDiv;
    uint32 delayTime;
    volatile uint32 currentTick;
    volatile uint32 delayCnt;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    currentTick = 0U;
    AhbDiv = RCC_CLOCK->SYSCLKCON2.B.AHB_DIV + 1U;
    delayTime = 8U*(1024U - (uint32)pMsc->FDIV.B.STEP) * AhbDiv;
    delayCnt = (delayTime + 2U) / 3U;

    /* #Violation: msc_hal_c_REF_5 */
    DISABLE_ALL_INTERRUPTS();

    pMsc->INTSC.B.CCFIF = 1U;

    if(0U == pMsc->INTCON.B.SELMIR)
    {
        pMsc->DC.U = command;
    }
    else
    {
        pMsc->DCRM.U = command;
    }

    do
    {
    	currentTick++;
    } while((currentTick < (uint32)MSC_MAX_DELAY_TICK) && (1U != pMsc->INTSTS.B.CFIF));

    if(currentTick < (uint32)MSC_MAX_DELAY_TICK)
    {
        pMsc->DCON.B.TRM = 0U;

        DSB();

        /* #Violation: msc_hal_c_REF_5 */
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
        pMsc->DCON.B.TRM = 1U;

        retState = TRUE;
    }
    else
    {
    	retState = FALSE;
    }

    /* #Violation: msc_hal_c_REF_5 */
    ENABLE_ALL_INTERRUPTS();

    return retState;
}
#endif

/* #Violation: msc_hal_c_REF_1 */
void Msc_Hal_SendData(MSC_MODULE *const pMsc, uint32 data)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    if(0U == pMsc->INTCON.B.SELMIR)
    {
        pMsc->DD.U = data;
    }
    else
    {
        pMsc->DDRM.U = data;
    }
}

/* #Violation: msc_hal_c_REF_1 */
Msc_RxStatus Msc_Hal_ReceiveData(MSC_MODULE *const pMsc, Msc_UpstreamRegType upstreamIdx, uint8 *const pData)
{
    Msc_RxStatus status;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_6 */
    Assert((boolean)(NULL_PTR != pData));
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    /* Acquire the upstream reception status */
    status = Msc_Std_GetRxStatus(pMsc, upstreamIdx);

    /* If the right data received */
    if(MSC_RXSTATUS_RECEIVED == status)
    {
        /* Clear the flag */
        Msc_Std_ClearUpstreamValidFlag(pMsc, upstreamIdx);

        /* Read the received data */
        *pData = Msc_Std_GetData(pMsc, upstreamIdx);
    }

    return status;
}

/* #Violation: msc_hal_c_REF_8 */
/* #Violation: msc_hal_c_REF_9 */
void Msc_Hal_ControlDownstream(MSC_MODULE *const pMsc, Msc_DownstreamEn downstreamEn)
{
    /* #Violation: msc_hal_c_REF_7 */
    MSC_INTSC intscValue;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    intscValue.U = pMsc->INTSC.U;

    if(MSC_DOWNSTREAMEN_ENABLED == downstreamEn)
    {
        intscValue.B.CDDIS = 1U;
    }
    else
    {
        intscValue.B.SDDIS = 1U;
    }

    pMsc->INTSC.U = intscValue.U;
}

/* #Violation: msc_hal_c_REF_1 */
void Msc_Hal_ControlUpstream(MSC_MODULE *const pMsc, Msc_UpDiv upDiv)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    /* Configure upstream receiving rate */
    pMsc->UPSTS.B.UCRR = (uint32)upDiv;
}

/* #Violation: msc_hal_c_REF_1 */
void Msc_Hal_SetDataTarget(MSC_MODULE *const pMsc, Msc_Target enXHigh, Msc_Target enXLow)
{
    /* #Violation: msc_hal_c_REF_7 */
    MSC_OCON oconValue;
    
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    oconValue.U = pMsc->OCON.U;

    /* Chip Enable Selection for ENL */
    oconValue.B.CSENL = (uint32)enXLow;
    /* Chip Enable Selection for ENH */
    oconValue.B.CSENH = (uint32)enXHigh;

    pMsc->OCON.U = oconValue.U;
}

/* #Violation: msc_hal_c_REF_1 */
void Msc_Hal_SetCommandTarget(MSC_MODULE *const pMsc, Msc_Target enX)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    /* Chip Enable Selection for ENC */
    pMsc->OCON.B.CSENC = (uint32)enX;
}

/* #Violation: msc_hal_c_REF_1 */
void Msc_Hal_SelectReceivingDevice(MSC_MODULE *const pMsc, Msc_Sdi sdi)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));

#if defined(THA6_THA6412)
    /* #Violation: msc_hal_c_REF_3 */
    if(MSC1_HAL == pMsc)
    {
        /* #Violation: msc_hal_c_REF_6 */
        Assert((boolean)((MSC_SDI_0 == sdi) || (MSC_SDI_1 == sdi) || (MSC_SDI_2 == sdi)));
    }
    /* #Violation: msc_hal_c_REF_3 */
    else if(MSC2_HAL == pMsc)
    {
        /* #Violation: msc_hal_c_REF_6 */
        Assert((boolean)((MSC_SDI_0 == sdi) || (MSC_SDI_1 == sdi)));
    }
    else
    {
        /* None assert, the range is as enum definition */
    }
#endif /* THA6_THA6412 */

#endif

    /* Serial data input selection */
    pMsc->OCON.B.SDIS = (uint32)sdi;
}

/* #Violation: msc_hal_c_REF_1 */
Msc_Status Msc_Hal_GetIntrStatusFlag(const MSC_MODULE *const pMsc, Msc_IntrStsFlag flag)
{
    uint32 status;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    switch(flag)
    {
        /* The status to be obtained is the data frame interrupt status */
        case MSC_INTRSTSFLAG_DF:
        {
            /* Get downstream data frame interrupt flag */
            status = (uint32)pMsc->INTSTS.B.DFIF;
            break;
        }
        /* The status to be obtained is the command frame interrupt status */
        case MSC_INTRSTSFLAG_CF:
        {
            /* Get downstream command frame interrupt flag */
            status = (uint32)pMsc->INTSTS.B.CFIF;
            break;
        }
        /* The status to be obtained is the time frame interrupt status */
        case MSC_INTRSTSFLAG_TF:
        {
            /* Get downstream time frame interrupt flag */
            status = (uint32)pMsc->INTSTS.B.TFIF;
            break;
        }
        /* The status to be obtained is the upstream channel receive frame interrupt status */
        case MSC_INTRSTSFLAG_RX:
        {
            /* Get upstream receive data interrupt flag */
            status = (uint32)pMsc->INTSTS.B.RDIF;
            break;
        }
        /* The status to be obtained is the upstream channel timeout interrupt status */
        case MSC_INTRSTSFLAG_TO:
        {
            /* Get upstream timeout interrupt flag */
            status = (uint32)pMsc->UCONE.B.UTF;
            break;
        }
        default:
        {
            status = 0U;
            break;
        }
    }

    return (1U == status) ? MSC_STATUS_SET : MSC_STATUS_RESET;
}

/* #Violation: msc_hal_c_REF_1 */
Msc_Status Msc_Hal_GetTransmitStatusFlag(const MSC_MODULE *const pMsc, Msc_TransmitStsFlag flag)
{
    uint32 status;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    switch(flag)
    {
        case MSC_TRANSMITSTSFLAG_DATP:
        {
            status = (uint32)pMsc->DCON.B.DATP;
            /* Data pending */
            if(0U == status)
            {
                status = (uint32)pMsc->DSTS.B.DATFA;
            }
            break;
        }
        case MSC_TRANSMITSTSFLAG_COMP:
        {
            status = (uint32)pMsc->DCON.B.COMP;
            /* Command pending */
            if(0U == status)
            {
                status = (uint32)pMsc->DSTS.B.COMFA;
            }
            break;
        }
        default:
        {
            /* Downstream disabled */
            status = (uint32)pMsc->DCON.B.DDIS;
            break;
        }
    }

    return (1U == status) ? MSC_STATUS_SET : MSC_STATUS_RESET;
}

/* #Violation: msc_hal_c_REF_1 */
Msc_IntrEn Msc_Hal_GetInterruptEnabledStatus(const MSC_MODULE *const pMsc, Msc_IntrStsFlag flag)
{
    uint32 status;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    switch(flag)
    {
        case MSC_INTRSTSFLAG_DF:
        {
            /* Get downstream data frame interrupt enabled status */
            status = (uint32)pMsc->INTCON.B.DFIE;
            break;
        }
        case MSC_INTRSTSFLAG_CF:
        {
            /* Get downstream command frame interrupt enabled status */
            status = (uint32)pMsc->INTCON.B.CFIE;
            break;
        }
        case MSC_INTRSTSFLAG_TF:
        {
            /* Get downstream time frame interrupt enabled status */
            status = (uint32)pMsc->INTCON.B.TFINTE;
            break;
        }
        case MSC_INTRSTSFLAG_RX:
        {
            /* Get upstream receive interrupt enabled status */
            status = (uint32)pMsc->INTCON.B.RDIE;
            break;
        }
        default:
        {
            /* Get upstream timeout interrupt enabled status */
            status = (uint32)pMsc->UCONE.B.UTIE;
            break;
        }
    }

    return (1U == status) ? MSC_INTREN_ENABLED : MSC_INTREN_DISABLED;
}

/* #Violation: msc_hal_c_REF_1 */
uint8 Msc_Hal_GetServiceNodeNumber(const MSC_MODULE *const pMsc, Msc_IntrStsFlag flag)
{
    uint8 serviceNum;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    switch(flag)
    {
        case MSC_INTRSTSFLAG_DF:
        {
            /* Get downstream data frame interrupt service node */
            serviceNum = pMsc->INTCON.B.DFIP;
            break;
        }
        case MSC_INTRSTSFLAG_CF:
        {
            /* Get downstream command frame interrupt service node */
            serviceNum = pMsc->INTCON.B.CFIP;
            break;
        }
        case MSC_INTRSTSFLAG_TF:
        {
            /* Get downstream time frame interrupt service node */
            serviceNum = pMsc->INTCON.B.TFINTP;
            break;
        }
        case MSC_INTRSTSFLAG_RX:
        {
            /* Get upstream receive interrupt service node */
            serviceNum = pMsc->INTCON.B.RDIP;
            break;
        }
        default:
        {
            /* Get upstream timeout interrupt service node */
            serviceNum = (1U == pMsc->UCONE.B.UTASR) ? (uint8)MSC_ALINTRNODE_SR4 : pMsc->UCONE.B.UTIP;
            break;
        }
    }

    return serviceNum;
}

/* #Violation: msc_hal_c_REF_1 */
void Msc_Hal_ClearIntrStatusFlag(MSC_MODULE *const pMsc, Msc_IntrStsFlag flag)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: msc_hal_c_REF_3 */
    /* #Violation: msc_hal_c_REF_4 */
    Assert((boolean)(CHECK_MSC_BASE(pMsc)));
#endif

    switch(flag)
    {
        case MSC_INTRSTSFLAG_DF:
        {
            /* Clear downstream data frame interrupt flag */
            pMsc->INTSC.B.CDFIF = 1U;
            break;
        }
        case MSC_INTRSTSFLAG_CF:
        {
            /* Clear downstream command frame interrupt flag */
            pMsc->INTSC.B.CCFIF = 1U;
            break;
        }
        case MSC_INTRSTSFLAG_TF:
        {
            /* Clear downstream time frame interrupt flag */
            pMsc->INTSC.B.CTFIF = 1U;
            break;
        }
        case MSC_INTRSTSFLAG_RX:
        {
            /* Clear upstream receive data interrupt flag */
            pMsc->INTSC.B.CRDIF = 1U;
            break;
        }
        default:
        {
            /* Clear upstream timeout interrupt flag */
            pMsc->UCONE.B.UTC = 1U;
            break;
        }
    }
}

#define MSC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: msc_hal_c_REF_10 */
#include "Msc_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
