/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    asi_hal.c
 * Author:      00101
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of ASI module.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #asi_hal_c_REF_1:MISRAC2012-Rule-19.2;
* Justification:Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by
*               code review.
*
* #asi_hal_c_REF_2:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
* #asi_hal_c_REF_3:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity
*
* #asi_hal_c_REF_4:MISRAC2012-Dir-1.1;
* Justification:Inline assembly for CPU-specific operations.
*
* #asi_hal_c_REF_5:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8.
*
* #asi_hal_c_REF_6:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
* #asi_hal_c_REF_7:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
* #asi_hal_c_REF_8:MISRAC2012-Rule-1.2;
* Justification:Inline assembly for CPU-specific operations.
*
* #asi_hal_c_REF_9:MISRAC2012-Dir-4.2;
* Justification:Inline assembly for CPU-specific operations.
*
* #asi_hal_c_REF_10:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
* #asi_hal_c_REF_11:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "asi_std.h"
#include "asi_hal.h"
#include "Platform_Types.h"
#include "asi_register.h"
#include "rcc_hal.h"
#include "stm_hal.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* #Violation: asi_hal_c_REF_10 */
#define ASI_LIN_SLAVE_FILTER_COUNTER_MAX (16U)
#define ASI_LIN_SLAVE_RESPONSE_TIME_CFG  (0x0FU)
#define ASI_BDRL_REGISTER_MAX_LEVEL      (4U)
#define ASI_UART_CSP_RECOMMEND_VALUE     (3U)
#define ASI_UART_BYTE_WIDTH_OFFSET       (8U)
#define ASI_LIN_IDLE                     (0x2U)
#define ASI_LIN_DLC_MAX                  (8U)
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/* #Violation: asi_hal_c_REF_10 */
#define ASI_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: asi_hal_c_REF_11 */
#include "Asi_MemMap.h"

/**********************************************************************************************************************
 * Function:     void Asi_Lin_Hal_SetIdFilter
 * Description:  Set ID Filter for Slave Node
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pLin: pointer to ASI(LIN) module
 *               pFilter: pointer to the frame identifier filter configuration structure
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       Filter 2N and 2N+1 must be configured with the same filter mode.
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
static void Asi_Lin_Hal_SetIdFilter(ASI_MODULE *const pLin,const Asi_Lin_IdFilterConfig* const pFilter);
/**********************************************************************************************************************
 * Function:     void Asi_Hal_WaitLinFlagUntilTimeout
 * Description:  Wait until flag is set or reset or timeout.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAsi: pointer to ASI module
 *               flag: User can use the macros UART Flag to specify flag(s).
 *               exStatus: specify the expected flag is set or reset
 *               timeout: timeout value, system timer counter
 * Inout:        None
 * Output:       None
 * Return:       uint8: 0 - successful; 1 - failed
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
static uint8 Asi_Hal_WaitLinFlagUntilTimeout(const ASI_MODULE *const pAsi, uint32 flag, uint32 exStatus, uint32 timeout);

/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static uint8 Asi_Hal_WaitLinFlagUntilTimeout(const ASI_MODULE *const pAsi, uint32 flag, uint32 exStatus, uint32 timeout)
{
    uint64 initCounter;
    uint32 curStatus;
    uint8 runState;

    initCounter = Stm_Hal_GetValue();
    do
    {
        runState = ((Stm_Hal_GetValue() - initCounter) < timeout) ? ASI_RUNSTATE_OK : ASI_RUNSTATE_NOT_OK;
        curStatus = ((0U == (pAsi->LINSR.U & flag)) ? ASI_FLAG_RESET : ASI_FLAG_SET);
    }while((curStatus != exStatus) && (ASI_RUNSTATE_OK == runState));

    return runState;
}

static void Asi_Lin_Hal_SetIdFilter(ASI_MODULE *const pLin,const Asi_Lin_IdFilterConfig* const pFilter)
{
    uint32 loopCount;
    /* #Violation: asi_hal_c_REF_1 */
    ASI_IFER iferReg;
    /* #Violation: asi_hal_c_REF_1 */
    ASI_IFMR ifmrReg;
    /* #Violation: asi_hal_c_REF_1 */
    ASI_IFCR ifcrReg;
    const Asi_Lin_FrameControl* pFrameControl;
    Asi_Lin_IdFilterMode filterMode;
    uint8 filterCount;

    iferReg.U = 0x0U;
    ifmrReg.U = 0x0U;
    filterCount = pFilter->idFilterCount;

    for(loopCount = 0; loopCount < filterCount; loopCount++)
    {
        pFrameControl = &pFilter->pIdFilter[loopCount].FilterControl;
        filterMode = pFilter->pIdFilter[loopCount].filterMode;
        /* enable filter */
        iferReg.U |= (1UL << loopCount);

        /* set filter mode */
        ifmrReg.U |= ((uint32)filterMode << (loopCount >> 1U));

        /* set filter control */
        ifcrReg.U = 0x0U;
        ifcrReg.B.CCS = (uint32)pFrameControl->checksum;
        ifcrReg.B.DFL = (pFrameControl->dataLength - ASI_LIN_DFL_DEVIATION);
        ifcrReg.B.DIR = (uint32)pFrameControl->dir;
        ifcrReg.B.ID = pFrameControl->frameID;
        pLin->IFCR[loopCount].U = ifcrReg.U;
    }

    pLin->IFER.U = iferReg.U;
    pLin->IFMR.U = ifmrReg.U;
}

/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: asi_hal_c_REF_6 */
uint8 Asi_Lin_Hal_InitModule(ASI_MODULE *const pLin, const Asi_Lin_Config *const pConfig, uint32 timeout)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pLin));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pConfig));
    if((ASI_LIN_MODE_MASTER != pConfig->mode) && (NULL_PTR != pConfig->pIdFilterConfig))
    {
        /* #Violation: asi_hal_c_REF_5 */
        Assert((boolean)(NULL_PTR != pConfig->pIdFilterConfig->pIdFilter));
        /* #Violation: asi_hal_c_REF_5 */
        Assert((boolean)(1U <= pConfig->pIdFilterConfig->pIdFilter->FilterControl.dataLength));
        /* #Violation: asi_hal_c_REF_5 */
        Assert((boolean)(8U >= pConfig->pIdFilterConfig->pIdFilter->FilterControl.dataLength));
    }
#endif

    /* #Violation: asi_hal_c_REF_1 */
    ASI_LINCR1 lincr1Reg;
    uint8 runState;

    Asi_Std_EnterInitMode(pLin);

    runState = Asi_Hal_WaitLinFlagUntilTimeout(pLin, ASI_LIN_INIT_STATE_FLAG, ASI_FLAG_SET, timeout);

    /* Initialize LIN */
    if(ASI_RUNSTATE_OK == runState)
    {
        lincr1Reg.U = pLin->LINCR1.U;

        /* Set LIN Mode */
        pLin->UARTCR.U = ASI_LIN_ENABLE_LIN_MODE;

        /* Configure Baud Rate */
        Asi_Std_SetFractionalBaudRate(pLin,pConfig->FractionalBaudRate);
        Asi_Std_SetIntegerBaudRate(pLin,pConfig->IntegerBaudRate);

        if(TRUE == pConfig->isAutoWakeUp)
        {
            lincr1Reg.B.AUTOWU = ASI_FUNCTION_ENABLE;
        }
        else
        {
            lincr1Reg.B.AUTOWU = ASI_FUNCTION_DISABLE;
        }

        if(ASI_LIN_MODE_MASTER == pConfig->mode)
        {
            lincr1Reg.B.MME = 1U;/* master mode */
            lincr1Reg.B.MBL = (uint32)pConfig->breakLength;

            if(TRUE == pConfig->isMasterRxDmaEnabled)
            {
                pLin->DMARXE.U = ASI_FUNCTION_ENABLE;
                pLin->DMATXE.U = ASI_FUNCTION_ENABLE;
            }
            pLin->LINTOCR.B.RTO = pConfig->frameTimeout;
        }
        else
        {
            if(ASI_LIN_BREAKLEN_10BIT == pConfig->breakLength)
            {
                lincr1Reg.B.SSBL = 1U;
            }
            else
            {
                lincr1Reg.B.SSBL = 0U;
            }

            lincr1Reg.B.LASE = ASI_FUNCTION_ENABLE; /* Enable auto-synchronization */
            lincr1Reg.B.BF = 1U; /* Bypass Filter */

            if(NULL_PTR != pConfig->pIdFilterConfig)
            {
                Asi_Lin_Hal_SetIdFilter(pLin, pConfig->pIdFilterConfig);
            }

            pLin->LINTOCR.B.HTO = pConfig->frameTimeout;
            pLin->LINTOCR.B.RTO = ASI_LIN_SLAVE_RESPONSE_TIME_CFG;
        }

        if(TRUE == pConfig->isRxBufferLockEnabled)
        {
            lincr1Reg.B.RBLM = ASI_FUNCTION_ENABLE;
        }
        else
        {
            lincr1Reg.B.RBLM = ASI_FUNCTION_DISABLE;
        }

        /* Write LINCR1 register */
        pLin->LINCR1.U = lincr1Reg.U;

        /* Timeout Counter Mode: LIN Mode */
        pLin->LINOCR.U = ASI_OUTPUT_COMPARE_MAX_COUNTER;

        /* Timeout Counter Mode: Lin Mode */
        pLin->LINTCSR.B.MODE = 0U;

        /* Lin state machine resets to idle on timeout event */
        pLin->LINTCSR.B.IOT = 1U;

        /* Clear Flag Status */
        pLin->LINSR.U = ASI_LIN_ALL_FLAGS;
        pLin->LINESR.U = ASI_LIN_ALL_ERROR_FLAGS;

        /* Enable Interrupt */
        pLin->LINIER.U = pConfig->enableInterrupt;
        pLin->AINTENR.U = 0x01U;

        Asi_Std_EnterNormalMode(pLin);
    }

    return runState;
}

/* #Violation: asi_hal_c_REF_6 */
void Asi_Lin_Hal_SendHeader(ASI_MODULE *const pLin, const Asi_Lin_FrameControl *const pFrameHeader)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pLin));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pFrameHeader));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(1U <= pFrameHeader->dataLength));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(8U >= pFrameHeader->dataLength));
#endif

    /* #Violation: asi_hal_c_REF_1 */
    ASI_BIDR bidrReg; 

    bidrReg.U = 0U;
    bidrReg.B.CCS = (uint32)pFrameHeader->checksum;
    bidrReg.B.DFL = (pFrameHeader->dataLength - 1U);
    bidrReg.B.ID = pFrameHeader->frameID;

    if(ASI_LIN_DATADIR_NODATA == pFrameHeader->dir)
    {
        /* Data Discard Request*/
        pLin->LINCR2.B.DDRQ = 1U;
    }
    else
    {
        bidrReg.B.DIR = (uint32)pFrameHeader->dir;
    }
    
    /* Write Frame Header into register*/
    pLin->BIDR.U = bidrReg.U;

    /* Request Header transmission */
    pLin->LINCR2.B.HTRQ = 1U;
}

/* #Violation: asi_hal_c_REF_6 */
uint8 Asi_Lin_Hal_SendData(ASI_MODULE *const pLin, const uint8 *const pData, uint32 length)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pLin));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pData));
#endif

    uint32 loopCount;
    uint8 runState;
    runState = ASI_RUNSTATE_NOT_OK;
    /* #Violation: asi_hal_c_REF_1 */
    ASI_BDRL bdrlReg; 
    /* #Violation: asi_hal_c_REF_1 */
    ASI_BDRM bdrmReg; 

    bdrlReg.U = 0U;
    bdrmReg.U = 0U;

    for(loopCount = 0U; loopCount < length; loopCount++)
    {
        if(loopCount < ASI_BDRL_REGISTER_MAX_LEVEL)
        {
            runState = ASI_RUNSTATE_OK;
            bdrlReg.B[loopCount] = pData[loopCount];
        }
        else if(loopCount < ASI_LIN_DLC_MAX)
        {
            runState = ASI_RUNSTATE_OK;
            bdrmReg.B[loopCount - ASI_BDRL_REGISTER_MAX_LEVEL] = pData[loopCount];
        }
        else
        {
            runState = ASI_RUNSTATE_NOT_OK;
            break;
        }        
    }

    if(runState == ASI_RUNSTATE_OK)
    {
        /* Write Data Into Register */
        pLin->BDRL.U = bdrlReg.U;
        if(loopCount > ASI_REG_BDRLM_BYTE_SHIFT_OFFSET)
        {
            pLin->BDRM.U = bdrmReg.U;
        }

        /* Data Transmission Request, only for slave mode */
        if((uint32)ASI_LIN_MODE_SLAVE == pLin->LINCR1.B.MME)
        {
            pLin->LINCR2.B.DTRQ = 1U;
        }
    }

    return runState;


}

/* #Violation: asi_hal_c_REF_6 */
void Asi_Lin_Hal_ReceiveHeader(const ASI_MODULE *const pLin,  uint8* const pFrameID)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pLin));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pFrameID));
#endif

    *pFrameID = (uint8)(pLin->BIDR.B.ID);
}

/* #Violation: asi_hal_c_REF_6 */
uint32 Asi_Lin_Hal_ReceiveData(const ASI_MODULE *const pLin, uint8* const pData, uint8 length)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pLin));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pData));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(1U <= length));
#endif

    /* #Violation: asi_hal_c_REF_1 */
    ASI_BDRL bdrlReg; 
    /* #Violation: asi_hal_c_REF_1 */
    ASI_BDRM bdrmReg; 
    uint8 loopCount;

    bdrlReg.U = pLin->BDRL.U;
    bdrmReg.U = pLin->BDRM.U;
    
    for(loopCount = 0; loopCount < length; loopCount++)
    {
        if(loopCount < ASI_BDRL_REGISTER_MAX_LEVEL)
        {
            pData[loopCount] =  bdrlReg.B[loopCount];
        }
        else if(loopCount < ASI_LIN_DLC_MAX)
        {
            pData[loopCount] =  bdrmReg.B[loopCount - ASI_BDRL_REGISTER_MAX_LEVEL];
        }
        else
        {
            break;
        }
    }   

    return pLin->BIDR.B.DFL;
}

/* #Violation: asi_hal_c_REF_6 */
void Asi_Lin_Hal_SetInterrupt(ASI_MODULE *const pLin, uint32 interrupt, boolean isEnabled)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pLin));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(0x0000FFFFU >= interrupt));
#endif

    Asi_Std_SetInterupt(pLin,interrupt,isEnabled);
}

/* #Violation: asi_hal_c_REF_6 */
uint32 Asi_Lin_Hal_GetFlagStatus(const ASI_MODULE *const pLin, uint32 flag)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pLin));
#endif

    uint32 flagStatus;

    if(ASI_LIN_IS_ERR_FLAG == (flag & ASI_LIN_IS_ERR_FLAG))
    {
        flagStatus = ((pLin->LINESR.U & flag) | ASI_LIN_IS_ERR_FLAG);
    }
    else
    {
        flagStatus = (pLin->LINSR.U & flag);
    }
    return flagStatus;
}

/* #Violation: asi_hal_c_REF_6 */
void Asi_Lin_Hal_ClearFlagStatus(ASI_MODULE *const pLin, uint32 flag)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pLin));
#endif

    if(ASI_LIN_IS_ERR_FLAG == (flag & ASI_LIN_IS_ERR_FLAG))
    {
        pLin->LINESR.U = flag; /* Clear specified error flags in LINESR register */
    }
    else
    {
        pLin->LINSR.U = (flag & ASI_LIN_MASK_RO_FLAGS); /* Clear specified flags in LINSR register */
    }
}

/* #Violation: asi_hal_c_REF_6 */
void Asi_Lin_Hal_SendWakeupRequest(ASI_MODULE *const pLin)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pLin));
#endif

    pLin->LINCR2.B.WURQ = 1U;
}

/* #Violation: asi_hal_c_REF_6 */
void Asi_Lin_Hal_DataDiscardRequest(ASI_MODULE *const pLin)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pLin));
#endif
    pLin->LINCR2.B.DDRQ = 1U;
}

/* #Violation: asi_hal_c_REF_6 */
void Asi_Lin_Hal_SetBufferIdentifier(ASI_MODULE *const pLin, const Asi_Lin_FrameControl *const pFrameHeader)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pLin));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pFrameHeader));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(1U <= pFrameHeader->dataLength));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(8U >= pFrameHeader->dataLength));
#endif

    /* #Violation: asi_hal_c_REF_1 */
    ASI_BIDR bidrReg;

    bidrReg.U = 0U;
    bidrReg.B.CCS = (uint32)pFrameHeader->checksum;
    bidrReg.B.DFL = (pFrameHeader->dataLength - 1U);
    bidrReg.B.ID = pFrameHeader->frameID;
    bidrReg.B.DIR = (uint32)pFrameHeader->dir;

    /* Write Frame Header into register*/
    pLin->BIDR.U = bidrReg.U;
}

/* #Violation: asi_hal_c_REF_6 */
uint8 Asi_Uart_Hal_InitModule(ASI_MODULE *const pUart, const Asi_Uart_Config *const pConfig, uint32 timeout)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pUart));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif

    /* #Violation: asi_hal_c_REF_1 */
    ASI_UARTCR uartcrReg;
    uint8 runState;

    Asi_Std_EnterInitMode(pUart);

    /* Wait the module is in INIT State */
    runState = Asi_Hal_WaitLinFlagUntilTimeout(pUart, ASI_LIN_INIT_STATE_FLAG, ASI_FLAG_SET, timeout);

    if(ASI_RUNSTATE_OK == runState)
    {
        /* Set Mode: UART */
        pUart->UARTCR.U = ASI_UART_ENABLE_UART_MODE;
        uartcrReg.U = pUart->UARTCR.U;

        Asi_Std_SetFractionalBaudRate(pUart,pConfig->FractionalBaudRate);
        Asi_Std_SetIntegerBaudRate(pUart,pConfig->IntegerBaudRate);

        /* Timeout Counter Mode: Output compare mode */
        pUart->LINTCSR.B.MODE = 1U;

        /* Set Parity*/
        uartcrReg.U |= (uint32)pConfig->parity;

        /* Set Stop Bits */
        uartcrReg.U |= (uint32)pConfig->stopBits;

        /* Set Data bits */
        uartcrReg.U |= (uint32)pConfig->dataBits;

        /* enable IDLE monitor */
        uartcrReg.B.MIS = 1U;

        if(pConfig->dataBits > ASI_UART_DATATBITS_8)
        {
            uartcrReg.B.RDFL_RFC = 0x01;/* the number of bytes to be received */
            uartcrReg.B.TDFL_TFC = 0x01;/* the number of bytes to be transmitted */
        }

        /* Set Sample number */
        if(ASI_UART_SAMPLENUM_16 != pConfig->sampleNumber)
        {
            uartcrReg.B.OSR = (uint32)pConfig->sampleNumber;
            uartcrReg.B.CSP = ASI_UART_CSP_RECOMMEND_VALUE;/* sample pointer */
            uartcrReg.B.ROSE = 1U;
        }
        else
        {
            uartcrReg.B.ROSE = 0U;
        }

        /* FIFO or Buffer mode */
        if(TRUE == pConfig->isEnableFIFO)
        {
            uartcrReg.B.TFBM = 1U;
            uartcrReg.B.RFBM = 1U;
        }

        /* Enable TX & RX */
        uartcrReg.B.RxEn = 1U;
        uartcrReg.B.TxEn = 1U;

        if(TRUE == pConfig->isRxBufferLockEnabled)
        {
            pUart->LINCR1.B.RBLM = ASI_FUNCTION_ENABLE;
        }
        else
        {
            pUart->LINCR1.B.RBLM = ASI_FUNCTION_DISABLE;
        }

        /* Write UARTCR register */
        pUart->UARTCR.U = uartcrReg.U;

        /* Clear Interrupt Status */
        pUart->UARTSR.U = ASI_UART_CLEAR_ALL_FLAGS;

        /* Enable Interrupt */
        pUart->LINIER.U = pConfig->enableInterrupt;

        Asi_Std_EnterNormalMode(pUart);
    }

    return runState;
}

/* #Violation: asi_hal_c_REF_6 */
void Asi_Uart_Hal_SendData(ASI_MODULE *const pUart, const uint8 *const pData)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pUart));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pData));
#endif

    uint32 pAddress;
    /* #Violation: asi_hal_c_REF_2 */
    pAddress = (uint32)pData;
    /* Send Data */
    if(ASI_UART_WORDLENGTH_IS_7_8_BITS == pUart->UARTCR.B.WL1)
    {
        pUart->BDRL.B[0] = pData[0];
    }
    else
    {
        /* #Violation: asi_hal_c_REF_2 */
        /* #Violation: asi_hal_c_REF_9 */
        pUart->BDRL.S[0] = (((uint16)(*(volatile uint8 *)(pAddress + 1U)) << ASI_UART_BYTE_WIDTH_OFFSET) | pData[0]);
    }
}

/* #Violation: asi_hal_c_REF_6 */
void Asi_Uart_Hal_ReceiveData(const ASI_MODULE *const pUart, uint8 *const pData)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pUart));
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pData));
#endif

    uint32 data;
    uint32 pAddress;

    /* #Violation: asi_hal_c_REF_2 */
    pAddress = (uint32)pData;
    data = (pUart->BDRM.U & ASI_SHORT_MASK);

    pData[0] = (uint8)data;

    /* Data type: short */
    if(ASI_UART_WORDLENGTH_IS_7_8_BITS != pUart->UARTCR.B.WL1)
    {
        /* #Violation: asi_hal_c_REF_2 */
        /* #Violation: asi_hal_c_REF_9 */
        *(volatile uint8 *)(pAddress + 1U) = (uint8)(data >> ASI_UART_BYTE_WIDTH_OFFSET);
    }
}

/* #Violation: asi_hal_c_REF_6 */
void Asi_Uart_Hal_SetInterrupt(ASI_MODULE *const pUart, uint32 interrupt, boolean isEnabled)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pUart));
#endif /* INPUT_ARG_DETECT == STD_ON */

    Asi_Std_SetInterupt(pUart,interrupt,isEnabled);
}

/* #Violation: asi_hal_c_REF_6 */
uint32 Asi_Uart_Hal_GetFlagStatus(const ASI_MODULE *const pUart, uint32 flag)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pUart));
#endif /* INPUT_ARG_DETECT == STD_ON */

    uint32 flagStatus;

    if(ASI_UART_IS_MODE_FLAG == (flag & ASI_UART_IS_MODE_FLAG))
    {
        flagStatus = (ASI_UART_IS_MODE_FLAG | (pUart->LINSR.B.LINS));
    }
    else
    {
        flagStatus = (pUart->UARTSR.U & flag);
    }
    
    return flagStatus;
}

/* #Violation: asi_hal_c_REF_6 */
void Asi_Uart_Hal_ClearFlagStatus(ASI_MODULE *const pUart, uint32 flag)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pUart));
#endif /* INPUT_ARG_DETECT == STD_ON */

    if(ASI_UART_IS_MODE_FLAG != (flag & ASI_UART_IS_MODE_FLAG))
    {
        pUart->UARTSR.U = flag;
    }
}

/* #Violation: asi_hal_c_REF_6 */
void Asi_Uart_Hal_SetTxRxWithDMA(ASI_MODULE *const pUart, Asi_Uart_DmaCtrl txRx, boolean isEnabled)
{
    uint32 config;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pUart));
#endif /* INPUT_ARG_DETECT == STD_ON */

    config = (TRUE == isEnabled) ? ASI_FUNCTION_ENABLE : ASI_FUNCTION_DISABLE;

    if(ASI_UART_DMACTRL_TXRX == txRx)
    {
        pUart->DMARXE.U = config;
        pUart->DMATXE.U = config;
    }
    else if (ASI_UART_DMACTRL_TX == txRx)
    {
        pUart->DMATXE.U = config;
    }
    else
    {
        pUart->DMARXE.U = config;
    }
}

/* #Violation: asi_hal_c_REF_6 */
void Asi_Hal_EnterSleepMode(ASI_MODULE *const pAsi)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pAsi));
#endif /* INPUT_ARG_DETECT == STD_ON */

    /* Enter Sleep Mode */
    pAsi->LINCR1.U |= ASI_LINCR1_SLEEP_MODE_REQUEST; 
}

/* #Violation: asi_hal_c_REF_6 */
uint8 Asi_Hal_ExitSleepMode(ASI_MODULE *const pAsi)
{
    uint8 runState;
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pAsi));
#endif /* INPUT_ARG_DETECT == STD_ON */

    /* Exit Sleep Mode */
    pAsi->LINCR1.U &= ~ASI_LINCR1_SLEEP_MODE_REQUEST; 
    runState = Asi_Hal_WaitLinFlagUntilTimeout(pAsi, ASI_LIN_IDLE_STATE_FLAG, ASI_FLAG_SET, 0x0FFFU);

    return runState;
}

/* #Violation: asi_hal_c_REF_3 */
/* #Violation: asi_hal_c_REF_6 */
uint8 Asi_Hal_ResetModule(ASI_MODULE *const pAsi) 
{
    Rcc_ErrorFlag errFlag;
    Rcc_ModuleRst rstModule;
    uint8 preErrFlag = 0U;

    errFlag = RCC_ERRORFLAG_TIMEOUT;

    /* #Violation: asi_hal_c_REF_2 */
    /* #Violation: asi_hal_c_REF_7 */
    rstModule = ASI_GET_RCC_RST_NUM(pAsi);

    /* Matched - the Module */
    if(RCC_MODULERST_MAX > rstModule)
    {
        /* CPU as master */
        if((1U == pAsi->LINSR.B.DRF) || (1U == pAsi->LINSR.B.DTF))
        {
            /* Disable all interrupt */
            pAsi->LINIER.U = 0U;
            /* Disable bus error report */
            pAsi->APBEMR.U = 0U;
        }
        else
        {
            if(ASI_LIN_IDLE == pAsi->LINSR.B.LINS)
            {
                /* Disable all interrupt */
                pAsi->LINIER.U = 0U;
                /* Disable bus error report */
                pAsi->APBEMR.U = 0U;
            }
            else
            {
                preErrFlag = 1U;
            }
        }

        if(0U == preErrFlag)
        {
            /* #Violation: asi_hal_c_REF_4 */
            /* #Violation: asi_hal_c_REF_8 */
            /* #Violation: asi_hal_c_REF_9 */
            DSB();
            /* Reset Module */
            errFlag = Rcc_Hal_TrigModuleRst(rstModule);
        }
    }

    return (RCC_ERRORFLAG_SUCCESS == errFlag) ? ASI_RUNSTATE_OK : ASI_RUNSTATE_NOT_OK;
}

/* #Violation: asi_hal_c_REF_6 */
uint8 Asi_Hal_SoftReset(ASI_MODULE *const pAsi, uint32 timeout)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: asi_hal_c_REF_5 */
    Assert((boolean)(NULL_PTR != pAsi));
#endif /* INPUT_ARG_DETECT == STD_ON */

    uint8 runState;

    /* Abort Transmission */
    pAsi->LINCR2.B.ABRQ = 1U;

    Asi_Std_EnterInitMode(pAsi);

    runState = Asi_Hal_WaitLinFlagUntilTimeout(pAsi, ASI_LIN_INIT_STATE_FLAG, ASI_FLAG_SET, timeout);

    if(ASI_RUNSTATE_OK == runState)
    {
        /* Soft Reset */
        pAsi->GCR.B.SR = 1U;
        pAsi->GCR.B.SR = 0U;
    }

    Asi_Std_EnterNormalMode(pAsi);

    return runState;
}

/* #Violation: asi_hal_c_REF_10 */
#define ASI_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: asi_hal_c_REF_11 */
#include "Asi_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
